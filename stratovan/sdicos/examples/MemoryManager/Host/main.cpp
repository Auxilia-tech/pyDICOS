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
 // StartDicosHostWithCustomMemoryManager
 //
// This example shows how to use IMemoryManager to provide memory allocation and 
// deallocation for the DICOS library's DcsServer.
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
// This class derives from the callback interface class. Override callback functions to process DICOS 
// data received by the DICOS server. The overridden functions should at least correspond to the API preference
// selected by the server. The function 'OnReceiveDicosFileError()', which receives errors that occurred 
// during the transmission, and 'OnReceiveDicosFile(DicosData<AttributeManager> &, const ErrorLog &)', which is called
// if DcsServer::PreferTagAPI() is called or if an unknown modality is received, must always be overridden.
//
class DataProcessing : public SDICOS::Network::IReceiveCallback
{
public:

protected:
	virtual void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata);

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog);

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog);
};

int main()
{
	const SDICOS::S_UINT64		nSizeOfBuffer(512 * 512 * sizeof(float));	//Support float volume slices of size 512 x 512
	const SDICOS::S_UINT32		nNumberOfBuffers(500);	//Total number of slices to support
	CustomMemoryManager			customMemoryManager(nSizeOfBuffer, nNumberOfBuffers);	//Memory manager for the DICOS server
	DataProcessing				icallback;	// Callback interface
	SDICOS::Network::DcsServer	server;		// DICOS server

	//Set the server to use the memory manager.
	//The allocation and deallocation calls from within the DICOS library originate
	//from a single thread and does not require a mutex lock within OnAllocate() or OnDeallocate()
	server.SetMemoryManager(&customMemoryManager);

	// Set the IP Address to listen on for incoming connections.
	//SDICOS::DcsString IPAddress("127.0.0.1");
	//server.SetIP(IPAddress);
		
	// Set the port to listen on for incoming connections
	server.SetPort(1000);

	// Set the name of this application. Must be no longer than 16 letters.
	server.SetApplicationName("ServerExample");

	// Start the server using the specified callback interface using default preferred API to User-Level.
	// This is a non-blocking function call. This function starts a separate thread for connection processing.
	// The first parameter is the callback interface that is used by the server to send the user data 
	// as received by the server. All connections share the same callback interface; therefore, the 
	// function must exit in order to receive more data. The callback interface can be changed
	// after StartListening() has been called by calling UpdateCallback() and passing in the new
	// interface.
	// The second parameter sets the callback interface for verifying client's application names, user names,
	// and passcodes.
	// The third parameter, default SDICOS::Network::DcsServer::enumMethodUserAPI, sets the preferred API
	// to use in the callback interface. If the preferred API cannot be used, then the Tag-Level API is called.
	// The preferred API can be changed after StartListening() has been called by calling UpdateCallback() and
	// passing in an SDICOS::Network::DcsServer::RETRIEVE_METHOD enumeration.
	if(!server.StartListening(icallback))
	{
		std::cout<<"Failed to start DICOS server"<<std::endl;
		return 1;
	}

	// Print message for manually stopping the server
	std::cout<<"\nPress enter to stop server";
	std::cin.get(); //Pause here until user presses the 'Enter' key

	// Stop the server
	server.StopListening();

	return 0;
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

	std::pair<bool, SDICOS::MemoryBuffer> *pBuffer(m_vBuffers.GetBuffer());
	for (SDICOS::S_UINT32 n(0); n < m_vBuffers.GetSize(); ++n, ++pBuffer)
	{
		if (pBuffer->first)
		{
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// [User-Level API] Process all CT modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'ct->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'ct.TakeOwnership()'
	// -Gain ownership of Tag-Level API with original data using the function 'ct.TakeOwnershipOriginal()'

	//Gain ownership of data for processing later using the function 'ct.TakeOwnership()'
	//If ownership is not taken with this function, the data is deleted when the function exits.
	SDICOS::CT *pCT = S_NULL;
	ct.TakeOwnership(pCT);
	DELETE_POINTER(pCT);

	//Gain ownership of original Tag-Level API data for processing later using the function 'ct.TakeOwnershipOriginal()'
	//If ownership is not taken with this function, the data is deleted when the function exits.
	SDICOS::AttributeManager *pmanagerOriginal = S_NULL;
	ct.TakeOwnershipOriginal(pmanagerOriginal);
	DELETE_POINTER(pmanagerOriginal);

	//Print connection information
	std::cout<<ct.GetClientIP().Get()<<std::endl;	//Client IP address that sent the data
	std::cout<<ct.GetServerIP().Get()<<std::endl;	//Server IP address that received the data
	std::cout<<ct.GetServerPort()<<std::endl;		//Server port number
}

// [User-Level API] Process all DX modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'dx->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'dx.TakeOwnership()'
	// -Gain ownership of Tag-Level API with original data using the function 'dx.TakeOwnershipOriginal()'
}

// [User-Level API] Process all AIT 2D modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'ait->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'ait.TakeOwnership()'
}

// [User-Level API] Process all AIT 3D modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'ait->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'ait.TakeOwnership()'
	// -Gain ownership of Tag-Level API with original data using the function 'ait.TakeOwnershipOriginal()'
}

// [User-Level API] Process all TDR modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'tdr->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'tdr.TakeOwnership()'
	// -Gain ownership of Tag-Level API with original data using the function 'ait.TakeOwnershipOriginal()'
}

// This function is only called when an error occurred during the DICOS network session
// that prevented any modalities from being processed. Overriding this function is required by any derived class.
void DataProcessing::OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata)
{
	//Check the error log for errors and warnings with 'errorlog.GetErrorLog()'
	//or write error log to file 'errorlog.WriteLog()'
	//or print out the error
	std::cout<<errorlog<<std::endl;
}

// [Tag-Level API] Process DICOS data at received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'manager->Write()'
	// -Access data using the 'manager->FindAttribute()' functions
}

// EndDicosHostWithCustomMemoryManager
