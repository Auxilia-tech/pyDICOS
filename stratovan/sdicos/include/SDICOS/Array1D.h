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
#ifndef _STRATOVAN_DICOS_ARRAY_1D_H__
#define _STRATOVAN_DICOS_ARRAY_1D_H__

#include "SDICOS/Memory.h"
#include "SDICOS/Types.h"
#include "SDICOS/ToolsLight.h"

#pragma push_macro("new")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace SDICOS
{

	/// Allocates memory on a single contiguous block for efficient access
	template < class CType >
	class Array1D
	{
	public:
		typedef Array1D< CType > CThisClass;

		Array1D()
		{
			Init();
		}

		Array1D(const S_UINT32 size)
		{
			Init();
			SetSize(size);
		}

		Array1D(const CThisClass &obj)
		{
			Init();
			*this = obj;
		}

		virtual ~Array1D()
		{
			Array1D::FreeMemory();
		}

		Array1D< CType >& operator=(const Array1D< CType > &obj)
		{
			if(this == &obj)
				return *this;

			SetSize(obj.GetSize());

			const CType *pBufRhs = obj.GetBuffer();
			for(S_UINT32 n = 0; n < m_nSize; ++n)
				m_pData[n] = pBufRhs[n];

			return *this;
		}

		bool operator==(const Array1D< CType > &obj)const
		{
			if(GetSize() != obj.GetSize()){
				return false;
			}

			if(GetBuffer() && obj.GetBuffer()) {
				const CType *pBufRhs = obj.GetBuffer();
				for(unsigned int i = 0; i < GetSize(); ++i) {
					// CType objects only need operator==
					if(!(m_pData[i] == pBufRhs[i])) {
						return false;
					}
				}
			}

			// All items are equal or one or both buffers are NULL
			// and the size if 0;
			return true;
		}

		bool operator!=(const Array1D< CType > &obj)const
		{
			return !operator==(obj);
		}

		bool Empty() const
		{
			return (0 == m_nSize);
		}

		void Clear()
		{
			m_nSize = 0;
		}
				
		bool SetSize(S_UINT32 nSize, const bool bAllocateExtraCapacity = false)
		{
			if(m_nSize == nSize)
				return true;

			FreeMemory();

			m_nSize			= nSize;
						
			if(bAllocateExtraCapacity)
				m_nCapacity = (nSize > 1) ? (SDICOS::S_UINT32(nSize + (nSize >> 1))) : 2; // minimum capacity is 2, otherwise size*1.5;
			else
				m_nCapacity = nSize; // no extra space is allocated

			try
			{
				m_pData			= new CType[m_nCapacity];	// Allocated space to hold capacity
			}
			catch(const std::bad_alloc &)
			{
				m_nSize = 0; // Memory allocation error...
				m_nCapacity = 0;
			}
			catch(...)
			{
				m_nSize = 0; // Memory allocation error...
				m_nCapacity = 0;
			}
			if(NULL == m_pData)
				return false;

			m_bDeleteBuffer = true;
			return true;
		}

		/// Delete the existing array and reserve memory for an array of the indicated size.
		/// @param reserveCapacity The number of elements to allocate memory for
		/// @return true/false
		bool Reserve(const S_UINT32 reserveCapacity)
		{
			FreeMemory(); // Deletes all existing data
			return (this->Reallocate(reserveCapacity, false));
		}
		
		/// Extend the size (up to the allocated capacity) of the array and copy elements to the new one.
		/// Once capacity is reached, additional calls to Extend() will return false
		/// @param numAdditionalElements Number of additional elements to add
		/// @return true/false
		bool Extend(const S_UINT32 numAdditionalElements)
		{
			if(0 == numAdditionalElements)
				return true;
			return (this->Reallocate((m_nCapacity+numAdditionalElements), false));
		}

		bool SetOverlay(S_UINT8 pBuf[], S_UINT32 nSize)
		{
			FreeMemory();

			m_nSize			= SDICOS::Max(S_UINT32(0), nSize);
			m_nCapacity		= nSize + (nSize >> 1); // Capacity = size * 1.5
			m_pData			= (CType*)(pBuf);
			m_bDeleteBuffer = false;

			return true;
		}

		void Zero(const CType &zero)
		{
			for(S_UINT32 n = 0; n < m_nSize; ++n)
				m_pData[n] = zero;
		}

		virtual void FreeMemory()
		{
			if(m_bDeleteBuffer)
				DELETE_ARRAY(m_pData);
			m_pData			= NULL;
			m_nSize			= 0;
			m_nCapacity		= 0;
			m_bDeleteBuffer = false;
		}

		// Computes an estimate of how much memory this object takes up in RAM...
		virtual S_UINT32 EstimateCoreFootprint()const
		{
			return sizeof(CType) * m_nSize;
		}

		/// Get the number of elements that are used.
		inline S_UINT32 GetSize()const
		{
			return m_nSize;
		}
				
		/// Get the number of elements that are used.
		inline void GetSize(S_UINT32 &nSize)const
		{
			nSize = m_nSize;
		}
		
		/// Get the number of elements that have been allocated.
		inline S_UINT32 GetCapacity()const
		{
			return m_nCapacity;
		}
				
		/// Get the number of elements that have been allocated.
		inline void GetCapacity(S_UINT32& nCapacity)const
		{
			nCapacity = m_nCapacity;
		}
		
		/// Get the difference between capacity and size clamped at 0.
		/// @return (capacity - size) or 0
		inline S_UINT32 GetNumUnusedElements() const
		{
			return (m_nCapacity > m_nSize) ? (m_nCapacity - m_nSize) : 0;
		}
				
		const CType& operator[](S_UINT32 n)const
		{
			S_ASSERT((n < m_nSize));
			return m_pData[n];
		}

		CType& operator[](S_UINT32 n)
		{
			S_ASSERT((n < m_nSize));
			return m_pData[n];
		}

		bool Add(const CType& t)
		{
			// If there is no more space, reallocate and increase capacity
			if(m_nSize < m_nCapacity || this->Reallocate())
			{
				m_pData[m_nSize] = t;
				++ m_nSize;
				return true;
			}
			return false;
		}
		
		bool Add(const CThisClass& t)
		{
			if((m_nSize + t.GetSize()) <= m_nCapacity)
			{
				for(S_UINT32 i = 0; i < t.GetSize(); ++i)
				{
					m_pData[m_nSize+i] = t[i];
				}
				m_nSize += t.GetSize();
				return true;
			}

			 // Make sure that at least t.GetSize() elements plus extra capacity are allocated
			if(this->Reallocate(t.GetSize()))
			{
				try {
					for(S_UINT32 i = 0; i < t.GetSize(); ++i)
						m_pData[m_nSize+i] = t[i];
					m_nSize += t.GetSize();
					return true;
				}
				catch(...)
				{
					// A copy failed so return false
					return false;
				}
			}
			return false;
		}
		
		inline const CType* GetBuffer()const
		{
			return m_pData;
		}

		inline CType* GetBuffer()
		{
			return m_pData;
		}

		/// Move the data in source to dest and set source to NULL
		static void Move(CThisClass &source, CThisClass& dest)
		{
			dest.FreeMemory();
			dest.m_pData = source.m_pData;
			dest.m_nSize = source.m_nSize;
			dest.m_nCapacity = source.m_nCapacity;
			dest.m_bDeleteBuffer = source.m_bDeleteBuffer;
			source.Init();
		}

		////////////////////////////////
		////////////////////////////////

	protected:
		
		static S_UINT32 CalcNewCapacity(const S_UINT32 minSize)
		{
			return (minSize > 1) ? (minSize + (minSize >> 1)) : 2; // capacity = min*1.5 or 2 if min = 1.
		}
				
		// Allocate a new buffer according to the capacity indicated by the current size
		// and copy existing data to the new buffer if the new size is >= existing size. 
		// Adjust capacity accordingly.
		bool Reallocate(const S_UINT32 nResizeAmount = 2, const bool bAllocateExtraCapacity = true)
		{
			CType * pOldData = m_pData;
			const S_UINT32 nOldCapacity(m_nCapacity);

			// Adjust capacity so that at least nResizeAmount of space is available
			// capacity = size * 1.5. Minimum nNewCapacity is 2.
			const S_UINT32 nNewCapacity(bAllocateExtraCapacity ? CalcNewCapacity(SDICOS::Max(nResizeAmount, m_nSize)) : nResizeAmount);

			try
			{
				m_pData = new CType[nNewCapacity];
			}
			catch(std::bad_alloc&)
			{
				m_pData = NULL;
			}

			if(m_pData)
			{
				try 
				{
					m_nCapacity = nNewCapacity;

					// If the new capacity is >= old size, copy elements
					if(nNewCapacity >= m_nSize) 
					{
						for(S_UINT32 i = 0; i < m_nSize; ++i)
							m_pData[i] = pOldData[i];
					} 
					else
						m_nSize = 0;

					if(pOldData)
						DELETE_ARRAY( pOldData );

					m_bDeleteBuffer = true;
					return true;
				}
				catch(...)
				{
					DELETE_ARRAY( m_pData );
					m_pData = pOldData;
					m_nCapacity = nOldCapacity;
					return false;
				}
			}

			m_pData = pOldData;
			return false;
		}

		void Init()
		{
			m_pData			= NULL;
			m_nSize			= 0;
			m_nCapacity		= 0;
			m_bDeleteBuffer = false;
		}

		CType	*m_pData;
		S_UINT32	m_nSize;		// Number of elements used in m_pData
		S_UINT32	m_nCapacity;	// Total number of elements allocated in m_pData
		bool	m_bDeleteBuffer;	// If it's an overlay, this is false so we don't delete the memory...
	};

}//namespace SDICOS

#pragma pop_macro("new")


#endif

