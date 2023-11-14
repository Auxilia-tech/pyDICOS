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
#ifndef _STRATOVAN_DICOS_IMEMORY_MANAGER_H_
#define	_STRATOVAN_DICOS_IMEMORY_MANAGER_H_

#include "SDICOS/MemoryBuffer.h"

namespace SDICOS
{

/// \class IMemoryManager
/// \brief	Memory management interface primarily to provide users with allocation and deallocation 
///			management used within the DICOS library
class IMemoryManager
{
public:

	/// Provide pre-allocated memory to mbAllocate with MemoryBuffer::SetBuffer()
	/// Calls OnAllocate, if it returns false, calls MemoryBuffer::GrowTo
	///
	/// @param mbAllocate Buffer to provide allocated memory
	/// @param nSizeInBytesToAllocate Bytes to allocate for the buffer
	bool Allocate(MemoryBuffer &mbAllocate, const S_UINT64 nSizeInBytesToAllocate);

	/// Calls OnDeallocate, if it returns false, calls MemoryBuffer::FreeMemory()
	///
	/// @param mbDeallocate Buffer to deallocate
	bool Deallocate(MemoryBuffer &mbDeallocate);

	/// The memory policy for MemoryBuffer objects passed into Allocate().
	/// Calls OnGetSliceMemoryPolicy().
	MemoryBuffer::MEMORY_POLICY GetSliceMemoryPolicy()const;

protected:
	/// Derive to provide a method for allocating the requested memory
	/// Can be used to move data into the buffer. Use memory policy to control data ownership.
	virtual bool OnAllocate(MemoryBuffer &mbAllocate, const S_UINT64 nSizeInBytesToAllocate) = 0;

	/// Derive to provide a method for deallocating the provided memory
	virtual bool OnDeallocate(MemoryBuffer &mbDeallocate) = 0;

	/// Derive to provide a default memory policy for MemoryBuffer objects passed into Allocate()
	virtual MemoryBuffer::MEMORY_POLICY OnGetSliceMemoryPolicy()const = 0;
};

}

#endif //_STRATOVAN_DICOS_IMEMORY_MANAGER_H_