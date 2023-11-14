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
#ifndef _STRATOVAN_DICOS_MEMORYBUFFER_CONST_H_
#define _STRATOVAN_DICOS_MEMORYBUFFER_CONST_H_

#include "SDICOS/Types.h"

namespace SDICOS
{

///
/// \class MemoryBufferConst
/// \brief A buffer that can only reference other data. Does not take ownership of data.
///
class MemoryBufferConst
{
public:
	/// Initializes memory policy to enumPolicy_OwnsData
	MemoryBufferConst();
	/// Initialize as copy
	MemoryBufferConst(const MemoryBufferConst &obj);

	/// Deletes data if this object owns the data
	virtual ~MemoryBufferConst();

	/// Sets buffer to NULL.
	virtual void FreeMemory();

	/// Copy operator
	MemoryBufferConst& operator=(const MemoryBufferConst &obj);

	/// Comparison operator
	bool operator==(const MemoryBufferConst &obj) const;

	/// Comparison operator
	bool operator!=(const MemoryBufferConst &obj) const;

	/// Returns the size of the buffer
	S_UINT64	GetSize()const;

	/// Byte access function
	unsigned char	operator[](const S_UINT64 n)const;

	/// Returns a pointer to the buffer
	const unsigned char*	GetData()const;

	/// Replaces the current buffer with the passed in buffer
	void SetBuffer(const unsigned char* pBuffer, const S_UINT64 nSize);

protected:
	class MemoryBufferImpl;
	MemoryBufferImpl *m_pMemoryBufferImpl;
};

}	// namespace SDICOS


#endif

