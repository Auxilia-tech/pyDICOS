//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2014 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_MEMORYBUFFER_H_
#define _STRATOVAN_DICOS_MEMORYBUFFER_H_

#include "SDICOS/Types.h"

namespace SDICOS
{

///
/// \class MemoryBuffer
/// \brief A grow-only buffer class
///
class MemoryBuffer
{
public:

	/// Enumerations to define data ownership
	typedef enum
	{
		enumPolicy_DoesNotOwnData	= 0,	///< MemoryBuffer does not own the data and will not delete it
		enumPolicy_OwnsData			= 1,	///< MemoryBuffer owns the data and will delete it
	}MEMORY_POLICY;

	/// Initializes memory policy to enumPolicy_OwnsData
	MemoryBuffer();
	/// Initialize as copy
	MemoryBuffer(const MemoryBuffer &obj);

	/// Deletes data if this object owns the data
	virtual ~MemoryBuffer();

	/// Deletes data if ownership was set. Otherwise buffer is set to NULL.
	/// @see SetMemoryPolicy
	virtual void FreeMemory();

	/// Copy operator
	MemoryBuffer& operator=(const MemoryBuffer &obj);

	/// Comparison operator
	bool operator==(const MemoryBuffer &obj) const;

	/// Comparison operator
	bool operator!=(const MemoryBuffer &obj) const;

	/// Sets the memory policy for the buffer.  If the passed in value is unknown, the policy will default to enumPolicy_OwnsData
	void SetMemoryPolicy(const MEMORY_POLICY nPolicy);
	/// @see SetMemoryPolicy
	MEMORY_POLICY GetMemoryPolicy()const;

	/// Returns true if memory policy is set to enumPolicy_OwnsData
	bool OwnsData()const;

	/// Memory policy must be set to enumPolicy_OwnsData to use this function.
	/// Grows buffer to meet designated size. Will not shrink the buffer if the passed in size is less than the current buffer size.
	/// @see SetMemoryPolicy
	bool GrowTo(const S_UINT64 nSize);

	/// Memory policy must be set to enumPolicy_OwnsData to use this function.
	/// Grows buffer to meet designated size while preserving existing data. Will not shrink the buffer if 
	/// the passed in size is less than the current buffer size
	/// @see SetMemoryPolicy
	bool GrowToSafe(const S_UINT64 nSize);

	/// Returns the size of the buffer
	S_UINT64	GetSize()const;

	/// Byte access function
	unsigned char&	operator[](const S_UINT64 n);
	/// Byte access function
	unsigned char	operator[](const S_UINT64 n)const;

	/// Returns a pointer to the buffer
	unsigned char*			GetData();
	/// Returns a pointer to the buffer
	const unsigned char*	GetData()const;

	/// Move data from source to destination buffer. Source's buffer cleared to NULL. 
	/// Source's memory policy also transferred to destination.
	static void Move(MemoryBuffer &membuffDest, MemoryBuffer &membuffSrc);

	/// Replaces the current buffer with the passed in buffer. Memory policy does not change.
	/// @see SetMemoryPolicy
	void SetBuffer(unsigned char* pBuffer, const S_UINT64 nSize);

protected:
	class MemoryBufferImpl;
	MemoryBufferImpl *m_pMemoryBufferImpl;
};

}	// namespace SDICOS


#endif

///	\file
/// A grow-only buffer class.
///

