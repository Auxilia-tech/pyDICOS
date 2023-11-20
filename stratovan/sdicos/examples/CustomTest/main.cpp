
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

int main()
{
	const SDICOS::S_UINT64	nSizeOfBuffer(512 * 512 * sizeof(float));	//Support float volume slices of size 512 x 512
	const SDICOS::S_UINT32	nNumberOfBuffers(500);	//Total number of slices to support
	//Memory manager for loading DICOS data
	CustomMemoryManager		customMemoryManager(nSizeOfBuffer, nNumberOfBuffers);	
	bool bRes = true;

	{
		SDICOS::CT ct;	//Modality to load
		SDICOS::Filename filename("../DataFiles/V02_Data/CT/CTUserAPI.dcs"); //Set this to a valid file
		SDICOS::ErrorLog errorlog; //Error log for loading data

		//Call the read function with the added IMemoryManager parameter
		if (ct.Read(filename, errorlog, &customMemoryManager)){
			std::cout << "Loaded CT" << std::endl;
			std::cout << "size of each buffer" << customMemoryManager.m_nBufferSizeInBytes <<std::endl;

			std::pair<bool, SDICOS::MemoryBuffer> *pBuffer(customMemoryManager.m_vBuffers.GetBuffer());

			SDICOS::MemoryBuffer& MemBuf = pBuffer->second;
    		float* floatData = reinterpret_cast<float*>(MemBuf.GetData());


			std::map<const unsigned char*, SDICOS::S_UINT32>::iterator it;

			//Check if the buffer was provided by this class
			it = customMemoryManager.m_mapUsedBuffers.begin();
			// Iterate through the map and print the elements
    		while (it != customMemoryManager.m_mapUsedBuffers.end()) {

				const unsigned char* firstKey = it->first;
				const float* floatData = reinterpret_cast<const float*>(firstKey);
				for(int i = 0; i <100; i++)
					std::cout << "Key: " << floatData[i] << std::endl ;
        		std::cout << "track_number: " << it->second << std::endl;
        		++it;
    		}


			//std::cout << nSizeOfBuffer << MemBuf.GetSize() << std::endl;

			//std::cout << nNumberOfBuffers << customMemoryManager.m_vBuffers.GetSize() << std::endl;
   	
			//for(int i = 0; i< 1; i++){
			//	std::cout << "first " << pBuffer->first << " " << i << std::endl;
			//	for(int j = 0; j < 100; j++)
			//		std::cout << "data " << floatData[j] << std::endl;
			//}
		}
		else
		{
			std::cout << "Failed to load CT" << std::endl;
			std::cout << "ERROR: " << errorlog << std::endl;
			bRes = false;
		}
	}

	return bRes ? 0 : 1;
}
