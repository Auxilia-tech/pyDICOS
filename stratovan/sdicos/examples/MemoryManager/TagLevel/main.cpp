//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2019 Stratovan Corporation. All Rights Reserved.
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
// StartTagLevelWithCustomMemoryManager
//
// This example shows how to use IMemoryManager to provide memory allocation and 
// deallocation for the DICOS library's when loading with Module-Level API.
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

int main()
{
	const SDICOS::S_UINT64	nSizeOfBuffer(512 * 512 * sizeof(float));	//Support float volume slices of size 512 x 512
	const SDICOS::S_UINT32	nNumberOfBuffers(500);	//Total number of slices to support
	CustomMemoryManager		customMemoryManager(nSizeOfBuffer, nNumberOfBuffers);	//Memory manager for loading DICOS data

	//Attribute Manager
	{
		SDICOS::AttributeManager manager;	//Modality to load
		SDICOS::Filename filename("../DataFiles/V03_Data/CT/CTUserAPI.dcs"); //Set this to a valid file
		SDICOS::ErrorLog errorlog; //Error log for loading data

		//Set the AttributeManager to use the memory manager for allocating pixel data
		manager.SetPixelDataMemoryManager(&customMemoryManager);

		//Load the DICOS data
		if (manager.Read(filename, errorlog))
		{
			std::cout << "Loaded DICOS data" << std::endl;
			return 0;
		}
		else
		{
			std::cout << "Failed to load DICOS data" << std::endl;
			std::cout << "Error: " <<  errorlog << std::endl;
			return 1;
		}
	}
}

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

// EndTagLevelWithCustomMemoryManager
