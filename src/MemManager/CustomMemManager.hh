#ifndef CUSTOMMEMORYMANAGER_FILE_H
#define CUSTOMMEMORYMANAGER_FILE_H

#include "SDICOS/DICOS.h" //Header for DICOS
#include <iostream>
#include <map>
#include "../headers.hh"
#include <pybind11/numpy.h>



using namespace SDICOS;

class CustomMemoryManager : public IMemoryManager
{
public:
	Array1D< std::pair<bool, MemoryBuffer> >			m_vBuffers;	//Array of preallocated buffers
	std::map<const unsigned char*, S_UINT32>			m_mapUsedBuffers; //Simple tracking for which slices are used
	const S_UINT64										m_nBufferSizeInBytes; //Size of each buffer

	 //Constructor preallocates the buffers
	CustomMemoryManager(const S_UINT64 m_nBufferSizeInBytes = (512 * 512 * 8), const S_UINT32 nNumBuffersToAllocated = 500);

	//Override from IMemoryManager to use preallocated buffer. This function will provide a buffer 
	//to the DICOS library and mark that buffer as 'used'.
	virtual bool OnAllocate(MemoryBuffer &mbAllocate, const S_UINT64 nSizeInBytesToAllocate);

	//Override from IMemoryManager to deallocated buffer. This function removes the buffer from the 'used' list
	//and allows it to be used again in OnAllocate()
	virtual bool OnDeallocate(MemoryBuffer &mbDeallocate);

	//Override from IMemoryManager to set the memory policy for the buffer passed to the DICOS library.
	//Since this class owns the data and the DICOS library is borrowing it, this function will be set
	//to return MemoryBuffer::enumPolicy_DoesNotOwnData
	virtual MemoryBuffer::MEMORY_POLICY OnGetSliceMemoryPolicy()const;

	float* getData() {
		std::pair<bool, MemoryBuffer> *pBuffer(m_vBuffers.GetBuffer());
		MemoryBuffer& MemBuf = pBuffer->second;
    	float* floatData = reinterpret_cast<float*>(MemBuf.GetData());
    	return floatData;
	}

};
#endif