#include "CustomMemManager.hh"

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

