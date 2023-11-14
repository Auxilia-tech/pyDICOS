//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2015 Stratovan Corporation. All Rights Reserved.
///
/// Permission to use, copy, modify, and distribute this software and its
/// documentation without a signed licensing agreement, is hereby granted,
/// provided that this copyright notice, this paragraph and the following two
/// paragraphs appear in all copies, modifications, and distributions.
///
/// IN NO EVENT SHALL STRATOVAN BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
/// SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
/// ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
/// STRATOVAN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// STRATOVAN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
/// TO, THE IMPLIED WARRANTIES OF USE AND FITNESS FOR A PARTICULAR PURPOSE. THE
/// SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
/// PROVIDED "AS IS". STRATOVAN HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
/// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS UNLESS DIRECTED BY THE
/// U.S. GOVERNMENT'S TRANSPORTATION SECURITY ADMINISTRATION (TSA).
///
//////////////////////////////////////////////////////////////////////////////
// StartDicosLoaderWithCustomMemoryManager
//
// This example shows how to use IMemoryManager to provide memory allocation and 
// deallocation for the DICOS library's DicosLoader.
//
#include "SDICOS/DICOS.h" //Header for DICOS
#include <iostream>
#include <map>

//
// This class derives from the IMemoryManager interface class and will handle allocating and 
// deallocating memory for the DICOS library.
// This class preallocates a fixed number of buffers which are passed to the DICOS library for
// its pixel data.
// When the DICOS library needs to delete the allocated data, this class's deallocation function
// is called with the buffer passed as a parameter allowing it to be recycled without actually deleting it.
//
class CustomMemoryManager : public SDICOS::IMemoryManager
{
public:
	SDICOS::Array1D< std::pair<bool, SDICOS::MemoryBuffer> >	m_vBuffers;	//Array of preallocated buffers
	std::map<const unsigned char*, SDICOS::S_UINT32>			m_mapUsedBuffers; //Simple tracking for which slices are used
	const SDICOS::S_UINT64										m_nBufferSizeInBytes; //Size of each buffer

	//Constructor preallocates the buffers
	CustomMemoryManager(const SDICOS::S_UINT64 m_nBufferSizeInBytes = (512 * 512 * 8), const SDICOS::S_UINT32 nNumBuffersToAllocated = 500);

	//Override from IMemoryManager to use preallocated buffer. This function will provide a buffer 
	//to the DICOS library and mark that buffer as 'used'.
	virtual bool OnAllocate(SDICOS::MemoryBuffer &mbAllocate, const SDICOS::S_UINT64 nSizeInBytesToAllocate);

	//Override from IMemoryManager to deallocated buffer. This function removes the buffer from the 'used' list
	//and allows it to be used again in OnAllocate()
	virtual bool OnDeallocate(SDICOS::MemoryBuffer &mbDeallocate);

	//Override from IMemoryManager to set the memory policy for the buffer passed to the DICOS library.
	//Since this class owns the data and the DICOS library is borrowing it, this function will be set
	//to return MemoryBuffer::enumPolicy_DoesNotOwnData
	virtual SDICOS::MemoryBuffer::MEMORY_POLICY OnGetSliceMemoryPolicy()const;
};

//
// This class derives from the callback interface and is used by the 
// DICOS loading object.
//
// Both versions of the OnReceiveDicosFileError(...) function must be overridden.
// Override the overloaded OnReceiveDicosFile(...) to receive callbacks when files are loaded.
//
class DicosLoadingCallback : public SDICOS::IRetrieveCallback
{
protected:
	virtual void OnReceiveDicosFileError(const SDICOS::Filename &filename, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFileError(const SDICOS::Array1D<SDICOS::Filename> &vfilenames, const SDICOS::ErrorLog &errorlog);

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QR> &qr, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog);
};

int main()
{
	const SDICOS::S_UINT64	nSizeOfBuffer(512 * 512 * sizeof(float));	//Support float volume slices of size 512 x 512
	const SDICOS::S_UINT32	nNumberOfBuffers(500);	//Total number of slices to support
	CustomMemoryManager		customMemoryManager(nSizeOfBuffer, nNumberOfBuffers);	//Memory manager for the DICOS loader
	SDICOS::DicosLoader		dcsloader;		// DICOS loading class
	DicosLoadingCallback	dcscallback;	// Callback interface for passing loaded files
	SDICOS::Folder			folder;			// Folder object
	int retvar(0);

	// Set the folder with DICOS files
	folder.GetCurrentWorkingFolder();
	folder.Set(folder.GetFullFolder() + "../DataFiles/V03_Data");

	//Set the loader to use the memory manager.
	//The allocation and deallocation calls from within the DICOS library originate
	//from a single thread and does not require a mutex lock within OnAllocate() or OnDeallocate()
	dcsloader.SetMemoryManager(&customMemoryManager);

	// Set the callback function to use after each file is loaded.
	// By default, this callback interface will only check files
	// with no extension or a '*.dcs' extension. To load DICOS files with other extensions, call
	// DicosLoadingCallback::IncludeFileExtension with a case sensitive extension (ie. ".dicos").
	// To load non-DICOS files that share the same format, like DICOM, add the override 
	// function "virtual bool OnLoadOnlyDICOS()const" to the callback interface and set 
	// the function to return 'false'.
	dcsloader.SetCallback(&dcscallback);

	// Set the preferred callback API. User-Level API is set by default.
	dcsloader.PreferUserLevelAPI();

	std::cout << "Loading files from folder " << folder.GetFullFolder().c_str() << std::endl;
		
	// Find all the DICOS files in the target folder and all sub folders
	if(dcsloader.Load(folder, true))
	{
		std::cout<<"\nAll files loaded"<<std::endl;
	} else {
		std::cout<<"\nFailed to load all files"<<std::endl;
		retvar=1;
	}

	return retvar;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CustomMemoryManager::CustomMemoryManager(const SDICOS::S_UINT64 m_nBufferSizeInBytes, const SDICOS::S_UINT32 nNumBuffersToAllocated)
	: m_nBufferSizeInBytes(m_nBufferSizeInBytes)
{
	m_vBuffers.SetSize(nNumBuffersToAllocated); //Allocate a set number of buffers

	std::pair<bool, SDICOS::MemoryBuffer> *pBuffer(m_vBuffers.GetBuffer());

	//Initialize each buffer to the indicated size and mark them as available
	for (SDICOS::S_UINT32 n(0); n < nNumBuffersToAllocated; ++n, ++pBuffer)
	{
		pBuffer->first = true;
		pBuffer->second.GrowTo(m_nBufferSizeInBytes);
	}
}

bool CustomMemoryManager::OnAllocate(SDICOS::MemoryBuffer &mbAllocate, const SDICOS::S_UINT64 nSizeInBytesToAllocate)
{
	//Check if the requested buffer size is too large. This will tell the DICOS library to
	//allocate a buffer itself.
	if (m_nBufferSizeInBytes <= nSizeInBytesToAllocate)
	{
		return false;
	}

	//Find an available buffer
	std::pair<bool, SDICOS::MemoryBuffer> *pBuffer(m_vBuffers.GetBuffer());
	for (SDICOS::S_UINT32 n(0); n < m_vBuffers.GetSize(); ++n, ++pBuffer)
	{
		if (pBuffer->first)
		{
			std::cout << "Allocated slice " << n << std::endl; //Print out the index of the buffer

			//Even though the buffer allocated may be larger, only state the requested size
			//has been provided.
			pBuffer->first = false; //Indicate buffer is no longer available
			mbAllocate.SetBuffer(pBuffer->second.GetData(), nSizeInBytesToAllocate);
			m_mapUsedBuffers[pBuffer->second.GetData()] = n;	//Track the used memory buffer

			//Return true to tell the DICOS library this class provided a buffer of the requested size
			return true;
		}
	}

	//No more buffers available, return false so the DICOS library handls allocation
	return false;
}

bool CustomMemoryManager::OnDeallocate(SDICOS::MemoryBuffer &mbDeallocate)
{
	//If memory policy does match, then the buffer was not allocated by this class
	if (GetSliceMemoryPolicy() != mbDeallocate.GetMemoryPolicy())
		return false; //Returning false allows the DICOS library to delete the buffer based on its memory policy

	std::map<const unsigned char*, SDICOS::S_UINT32>::iterator it;

	//Check if the buffer was provided by this class
	it = m_mapUsedBuffers.find(mbDeallocate.GetData());
	if (m_mapUsedBuffers.end() == it)
		return false; //Returning false allows the DICOS library to delete the buffer based on its memory policy

	std::cout << "Deallocated slice " << it->second << std::endl; //Print out the index of the buffer

	m_vBuffers[it->second].first = true; //Mark the buffer as available for use in OnAllocate()
	m_mapUsedBuffers.erase(it); //Remove buffer from the 'used' list

	//Returning true tells the DICOS library this class has deallocated the buffer
	return true;
}

SDICOS::MemoryBuffer::MEMORY_POLICY CustomMemoryManager::OnGetSliceMemoryPolicy()const
{
	//Tell the DICOS library it does not own the data. This prevents the DICOS library
	//from deleting the preallocated buffers.
	return SDICOS::MemoryBuffer::enumPolicy_DoesNotOwnData;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function is called when a DICOS file failed to load. The parameter 'filename' contains the file name
// of the file that failed to load. The parameter 'errorlog' contains all the errors and warnings encountered
// while loading the file.
void DicosLoadingCallback::OnReceiveDicosFileError(const SDICOS::Filename &filename, const SDICOS::ErrorLog &errorlog)
{
	// Print the name of the file name
	std::cout<<"\n-------------------";
	std::cout<<"\nError loading file "<<filename.GetFullPath();
	std::cout<<"\nError Log:\n";
	std::cout<<errorlog<<std::endl;

}

// This function is called when a set of DICOS files failed to load. This is invoked when the User-Level API
// is used by the DICOS loader. The parameter 'filename' contains the file name of the file that failed
// to load. The parameter 'errorlog' contains all the errors and warnings encountered while loading the file.
void DicosLoadingCallback::OnReceiveDicosFileError(const SDICOS::Array1D<SDICOS::Filename> &vfilenames, const SDICOS::ErrorLog &errorlog)
{
	SDICOS::S_UINT32 n(0);

	std::cout<<"\n-------------------";
	std::cout<<"\nError loading files: "<<std::endl;

	for(n = 0 ; n < vfilenames.GetSize() ; ++n)
		std::cout<<vfilenames[n].GetFullPath()<<std::endl;

	std::cout<<"\nError Log:\n";
	std::cout<<errorlog<<std::endl;
}

//
// The 'OnReceiveDicosFile()' functions serve as callback functions for passing in the loaded DICOS data as a parameter
//
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a CT DICOS file is loaded and the preferred API is set to User-Level API
	std::cout << "OnReceiveDicosFile(SDICOS::CT) SopInstanceUID: " << ct->GetSopInstanceUID().Get() << " " << errorlog << std::endl;

	// Send data over the network using ct->SendOverNetwork().
	SDICOS::ErrorLog errorlogNetwork;
	ct->SendOverNetwork(1000, "1.2.3", "SourceApp", "DestApp", errorlogNetwork);

	// Gain ownership of the CT object by calling ct.TakeOwnership()
	// and passing a pointer to a CT object.
	SDICOS::CT *pct = S_NULL;
	ct.TakeOwnership(pct);
	DELETE_POINTER(pct); //Internally calls CustomMemoryManager::OnDeallocate() for each slice
}

void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a DX DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using dx->SendOverNetwork().
	// Gain ownership of the DX object by calling dx.TakeOwnership()
	// and passing a pointer to a DX object.
	
	std::cout << "OnReceiveDicosFile(SDICOS::DX) SopInstanceUID: " << dx->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a AIT2D DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using ait->SendOverNetwork().
	// Gain ownership of the AIT2D object by calling ait.TakeOwnership()
	// and passing a pointer to a AIT2D object.
	std::cout << "OnReceiveDicosFile(SDICOS::AIT2D) SopInstanceUID: " << ait->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a AIT3D DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using ait->SendOverNetwork().
	// Gain ownership of the AIT3D object by calling ait.TakeOwnership()
	// and passing a pointer to a AIT3D object.
	std::cout << "OnReceiveDicosFile(SDICOS::AIT3D) SopInstanceUID: " << ait->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QR> &qr, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a QR DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using qr->SendOverNetwork().
	// Gain ownership of the QR object by calling qr.TakeOwnership()
	// and passing a pointer to a QR object.
	std::cout << "OnReceiveDicosFile(SDICOS::QR) SopInstanceUID: " << qr->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
}
void DicosLoadingCallback::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
{
	// This function is called after a TDR DICOS file is loaded and the preferred API is set to User-Level API

	// Send data over the network using tdr->SendOverNetwork().
	// Gain ownership of the TDR object by calling tdr.TakeOwnership()
	// and passing a pointer to a TDR object.
	std::cout << "OnReceiveDicosFile(SDICOS::TDR) SopInstanceUID: " << tdr->GetSopInstanceUID().Get() << " " << errorlog << std::endl;
}
// EndDicosLoaderWithCustomMemoryManager
