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
#ifndef _STRATOVAN_DICOS_ARRAY_2D_LARGE_H__
#define _STRATOVAN_DICOS_ARRAY_2D_LARGE_H__

#include "SDICOS/Types.h"
#include "SDICOS/Array1D.h"

namespace SDICOS
{

	/// Use for large arrays i.e., those requiring more than 100MB of memory. Memory is allocated in several smaller chunks to improve the chances of allocation at runtime.
	/// Array items are accessed in reverse coordinate order in order to improve cache access patterns. Thus, you must access the Y direction first, followed by the X direction to access the array element.
	template < class CType >
	class Array2DLarge : public Array1D< Array1D< CType > >
	{
	public:
		typedef Array2DLarge< CType >		CThisClass;
		typedef Array1D< Array1D< CType > >	CParentClass;

		Array2DLarge()
		{
			Init();
		}

		Array2DLarge(const CThisClass &obj)
		{
			Init();
			*this = obj;
		}

		virtual ~Array2DLarge()
		{
			FreeMemory();
		}

		CThisClass& operator=(const CThisClass &obj)
		{
			if(this == &obj)
				return *this;

			SetSize(obj.GetWidth(), obj.GetHeight());

			for(S_UINT32 nH = 0; nH < GetHeight(); ++nH)
				CParentClass::operator[](nH) = obj.CParentClass::operator[](nH);

			return *this;
		}

		bool SetSize(S_UINT32 nWidth, S_UINT32 nHeight)
		{
			if((m_nWidth == nWidth) && (GetHeight() == nHeight))
				return true;

			bool bRes(true);

			nHeight	= SDICOS::Max(S_UINT32(0), nHeight);
			bRes = bRes && CParentClass::SetSize(nHeight);

			m_nWidth	= SDICOS::Max(S_UINT32(0), nWidth);

			for(S_UINT32 nH = 0; nH < GetHeight(); ++nH)
				bRes = bRes && CParentClass::operator[](nH).SetSize(m_nWidth);

			return bRes;
		}

		bool SetOverlay(S_UINT8 pBuf[], S_UINT32 nWidth, S_UINT32 nHeight)
		{
			nHeight		= SDICOS::Max(S_UINT32(0), nHeight);

			bool bRes(true);
			bRes = bRes && CParentClass::SetSize(nHeight);

			m_nWidth	= SDICOS::Max(S_UINT32(0), nWidth);

			const S_UINT32 nLine(m_nWidth*sizeof(CType));
			for(S_UINT32 nH = 0; nH < GetHeight(); ++nH)
				bRes = bRes && CParentClass::operator[](nH).SetOverlay(&(pBuf[nLine*nH]), m_nWidth);

			return true;
		}

		void Zero(const CType &zero)
		{
			for(S_UINT32 nH = 0; nH < GetHeight(); ++nH)
				CParentClass::operator[](nH).Zero(zero);
		}

		virtual void FreeMemory()
		{
			CParentClass::FreeMemory();
			m_nWidth = 0;
		}

		// Computes an estimate of how much memory this object takes up in RAM...
		virtual S_UINT32 EstimateCoreFootprint()const
		{
			return sizeof(CType) * m_nWidth * GetHeight();
		}

		// The following should be protected outside of the function call
		// with locks...
		////////////////////////////////
		inline S_UINT32 GetWidth()const
		{
			return m_nWidth;
		}
		inline S_UINT32 GetHeight()const
		{
			return CParentClass::GetSize();
		}

		inline void GetSize(S_UINT32 &nW, S_UINT32 &nH)const
		{
			nW	= m_nWidth;
			nH	= GetHeight();
		}

		////////////////////////////////
		////////////////////////////////

	protected:
		void Init()
		{
			m_nWidth		= 0;
		}

		S_UINT32	m_nWidth;
	};

}	// namespace SDICOS


#endif





