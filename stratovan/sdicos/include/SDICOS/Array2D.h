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
#ifndef _STRATOVAN_DICOS_ARRAY_2D_H__
#define _STRATOVAN_DICOS_ARRAY_2D_H__

#include <cstring>

#include "SDICOS/Types.h"
#include "SDICOS/Memory.h"
#include "SDICOS/ToolsLight.h"

#pragma push_macro("new")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace SDICOS
{

	/// Allocates memory on a single contiguous block for efficient access. Use Array2DLarge for large arrays, i.e., over 100MB in size.
	template < class CType >
	class Array2D
	{
	public:
		typedef Array2D< CType > CThisClass;

		Array2D()
		{
			Init();
		}
				
		Array2D(const S_UINT32 nWidth, const S_UINT32 nHeight)
		{
			Init();
			SetSize(nWidth, nHeight);
		}

		Array2D(const CThisClass &obj)
		{
			Init();
			*this = obj;
		}

		virtual ~Array2D()
		{
			Array2D::FreeMemory();
		}

		Array2D< CType >& operator=(const Array2D< CType > &obj)
		{
			if(this == &obj)
				return *this;

			if(SetSize(obj.GetWidth(), obj.GetHeight()) && m_ppData && obj.m_ppData)
			{
				for(S_UINT32 j = 0; j < m_nHeight; ++j)
				for(S_UINT32 i = 0; i < m_nWidth; ++i)
					m_ppData[j][i] = obj.m_ppData[j][i];
			}

			return *this;
		}

		bool operator==(const Array2D< CType > &rhs)const
		{
			if(this == &rhs)				return true;
			if(GetWidth() != rhs.GetWidth() || GetHeight() != rhs.GetHeight())	return false;

			if(m_pBuffer && rhs.m_pBuffer)
			{
				return 0 == memcmp(m_pBuffer, rhs.m_pBuffer, m_nWidth*m_nHeight*sizeof(CType));
			}

			if(m_ppData && rhs.m_ppData)
			{
				for(S_UINT32 j = 0; j < m_nHeight; ++j)
				for(S_UINT32 i = 0; i < m_nWidth; ++i)
					if(m_ppData[j][i] != rhs.m_ppData[j][i])
						return false;
			}

			return true;
		}

		bool operator!=(const Array2D< CType > &rhs)const	{return !operator==(rhs);}

		virtual bool SetSize(S_UINT32 nWidth, S_UINT32 nHeight)
		{
			if((m_nWidth == nWidth) && (m_nHeight == nHeight))
				return true;

			FreeMemory();

			m_nWidth	= SDICOS::Max(S_UINT32(0), nWidth);
			m_nHeight	= SDICOS::Max(S_UINT32(0), nHeight);

			try
			{
				m_pBuffer	= new CType[m_nWidth*m_nHeight];
				m_ppData	= new CType*[m_nHeight];
			}
			catch(const std::bad_alloc &)
			{
				m_nWidth	= 0; // Memory allocation error...
				m_nHeight	= 0;
			}
			catch(...)
			{
				m_nWidth	= 0; // Memory allocation error...
				m_nHeight	= 0;
			}
			if((NULL == m_pBuffer) || (NULL == m_ppData))
			{
				DELETE_ARRAY(m_pBuffer);
				DELETE_ARRAY(m_ppData);
				return false;
			}

			for(S_UINT32 j = 0; j < m_nHeight; ++j)
				m_ppData[j] = &(m_pBuffer[j*m_nWidth]);

			m_bDeleteBuffer = true;

			return true;
		}

		virtual bool SetOverlay(S_UINT8 pBuf[], const S_UINT32 nWidth, const S_UINT32 nHeight)
		{
			FreeMemory();

			m_nWidth	= SDICOS::Max(S_UINT32(0), nWidth);
			m_nHeight	= SDICOS::Max(S_UINT32(0), nHeight);
			m_pBuffer	= (CType*)(pBuf);
			m_ppData	= new CType*[m_nHeight];
			for(S_UINT32 j = 0; j < m_nHeight; ++j)
				m_ppData[j] = &(m_pBuffer[j*m_nWidth]);
			m_bDeleteBuffer = false;

			return true;
		}

		/// Move owner of data from pSource to Array2D
		virtual void MoveData(CType *pSource, const S_UINT32 nWidth, const S_UINT32 nHeight)
		{
			FreeMemory();

			m_nWidth	= SDICOS::Max(S_UINT32(0), nWidth);
			m_nHeight	= SDICOS::Max(S_UINT32(0), nHeight);
			m_pBuffer	= pSource;
			m_ppData	= new CType*[m_nHeight];
			for(S_UINT32 j = 0; j < m_nHeight; ++j)
				m_ppData[j] = &(m_pBuffer[j*m_nWidth]);
			m_bDeleteBuffer = true;
		}

		/// Move owner of data from vSrc to Array2D
		virtual void MoveData(Array2D<CType> &vSrc)
		{
			FreeMemory();

			m_nWidth	= SDICOS::Max(S_UINT32(0), vSrc.m_nWidth);
			m_nHeight	= SDICOS::Max(S_UINT32(0), vSrc.m_nHeight);
			m_pBuffer	= vSrc.m_pBuffer;
			m_ppData	= vSrc.m_ppData;
			m_bDeleteBuffer = true;

			vSrc.m_pBuffer = NULL;
			vSrc.m_ppData = NULL;
			vSrc.m_bDeleteBuffer = false;
			vSrc.FreeMemory();
		}

		virtual void Zero(const CType &zero)
		{
			if(NULL == m_ppData)
				return;

			for(S_UINT32 j = 0; j < m_nHeight; ++j)
			for(S_UINT32 i = 0; i < m_nWidth; ++i)
				m_ppData[j][i] = zero;
		}

		virtual void FreeMemory()
		{
			DELETE_ARRAY(m_ppData);
			if(m_bDeleteBuffer)
				DELETE_ARRAY(m_pBuffer);
			m_ppData = NULL;
			m_nWidth = m_nHeight = 0;
			m_bDeleteBuffer = false;
		}

		///
		/// Check if the Array owns its data buffer
		///
		bool HasOwnership() const { return m_bDeleteBuffer; }
		void SetOwnership(const bool bOwnsData) { m_bDeleteBuffer = bOwnsData; }

		/// Computes an estimate of how much memory this object takes up in RAM.
		virtual S_UINT32 EstimateCoreFootprint()const
		{
			return sizeof(CType) * m_nWidth * m_nHeight;
		}

		/// The following should be protected outside of the function call
		/// with locks.
		////////////////////////////////
		virtual S_UINT32 GetWidth()const
		{
			return m_nWidth;
		}
		virtual S_UINT32 GetHeight()const
		{
			return m_nHeight;
		}

		virtual void GetSize(S_UINT32 &nW, S_UINT32 &nH)const
		{
			nW	= GetWidth();
			nH	= GetHeight();
		}

		inline const CType* operator[](S_UINT32 nRow)const
		{
			S_ASSERT((nRow >= 0) && (nRow < m_nHeight));
			return m_ppData[nRow];
		}

		inline CType* operator[](S_UINT32 nRow)
		{
			S_ASSERT((nRow < m_nHeight));
			return m_ppData[nRow];
		}

		inline const CType& Get(S_UINT32 i, S_UINT32 j)const
		{
			S_ASSERT((i < m_nWidth) && (j < m_nHeight));
			return m_ppData[j][i];
		}

		inline CType& At(S_UINT32 i, S_UINT32 j)
		{
			S_ASSERT((i < m_nWidth) && (j < m_nHeight));
			return m_ppData[j][i];
		}

		inline void Set(S_UINT32 i, S_UINT32 j, const CType &obj)
		{
			S_ASSERT((i < m_nWidth) && (j < m_nHeight));
			m_ppData[j][i] = obj;
		}

		inline const CType* GetBuffer()const
		{
			return m_pBuffer;
		}

		inline CType* GetBuffer()
		{
			return m_pBuffer;
		}

		////////////////////////////////
		////////////////////////////////

	protected:
		void Init()
		{
			m_pBuffer		= NULL;
			m_ppData		= NULL;
			m_nWidth		= 0;
			m_nHeight		= 0;
			m_bDeleteBuffer = false;
		}

		CType	*m_pBuffer, **m_ppData;
		S_UINT32	m_nWidth, m_nHeight;
		bool	m_bDeleteBuffer;	// If it's an overlay, this is false so we don't delete the memory...
	};

}// namespace SDICOS

#pragma pop_macro("new")


#endif





