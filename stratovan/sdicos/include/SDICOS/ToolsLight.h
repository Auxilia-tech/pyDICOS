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
#ifndef _STRATOVAN_DICOS_TOOLS_LIGHT_H_
#define _STRATOVAN_DICOS_TOOLS_LIGHT_H_

#include <string>
#include <vector>
#include <cstdarg>
#include <math.h>

#include "SDICOS/Types.h"
#include "SDICOS/String.h"
#include "SDICOS/Memory.h"

#pragma push_macro("new")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace SDICOS
{
	/// Automate casting for sqrt to the input type.
	template < typename CType>	inline CType		Sqrt(const CType &fVal)
	{
		return (CType) sqrt( (double)fVal );
	}
	template < >				inline float		Sqrt<float>(const float &fVal)						{ return (float)sqrt( fVal ); }
	template < >				inline double		Sqrt<double>(const double &fVal)					{ return sqrt( fVal ); }
	template < >				inline long double	Sqrt<long double>(const long double &fVal)			{ return (long double)sqrt( (double)fVal ); }

	/// Absolute value of two numbers.
	template <class CType>
	inline CType Abs(const CType &a)
	{
		return (a > (CType)0 ? a : -a);
	}
	
	/// Minimum of two values.
	template< class CType >
	inline CType Min(const CType &a, const CType &b)
	{
		return (a < b) ? a : b;
	}
	
	/// Maximum of two values.
	template< class CType >
	inline CType Max(const CType &a, const CType &b)
	{
		return (a < b) ? b : a;
	}
	
	/// Minimum of three values.
	template< class CType >
	inline CType Min(const CType &a, const CType &b, const CType &c)
	{
		return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
	}
	
	/// Maximum of three values.
	template< class CType >
	inline CType Max(const CType &a, const CType &b, const CType &c)
	{
		return (a < b) ? ((b < c) ? c : b) : ((a < c) ? c : a);
	}

	/// Returns +1 or -1 depending upon the sign of the passed value 
	template< class CType >
	inline CType Sign(const CType &val)
	{
		if(val < 0)
			return CType(-1);
		return CType(1);
	}

	/// Clamp a value to the given range.
	template< class CType >
	inline CType Clamp(const CType &val, const CType &minVal, const CType &maxVal)
	{
		if(val < minVal)	return minVal;
		if(val > maxVal)	return maxVal;
		return val;
	}

	/// Swap two values.
	template <class CType>
	inline void Swap(CType &a, CType &b)
	{
		CType t(a);
		a = b;
		b = t;
	}

	//@{
	/// Working range for zero and equality testing methods. These ranges describe the maximum "size" of the numbers to be considered when determining if values are either equal or zero
	#define         FLOAT_DEFAULT_WORKING_RANGE                             (float)1e5
	#define         DOUBLE_DEFAULT_WORKING_RANGE                    1e8
	#define         LONG_DOUBLE_DEFAULT_WORKING_RANGE               1e8
	template< typename T >  inline T                        GetDefaultWorkingRange()                                {return (T)1e5;}
	template<  >                    inline float            GetDefaultWorkingRange<float>()                 {return FLOAT_DEFAULT_WORKING_RANGE;}
	template<  >                    inline double           GetDefaultWorkingRange<double>()                {return DOUBLE_DEFAULT_WORKING_RANGE;}
	template<  >                    inline long double      GetDefaultWorkingRange<long double>()   {return LONG_DOUBLE_DEFAULT_WORKING_RANGE;}
	//@}

	//@{
	/// Used to control the number of significant digits to compare to when determine zero or equality tests
	#define     FLOAT_SIGNIFICANT_DIGITS                (float)1e-10	///< Ten significant digits to compare to
	#define     DOUBLE_SIGNIFICANT_DIGITS               1e-16			///< Sixteen significant digits to compare to
	#define     LONG_DOUBLE_SIGNIFICANT_DIGITS          1e-16			///< Sixteen significant digits to compare to
	template< typename T >	inline T			GetDefaultSignificantDigits()				{return (T)(1e-10);}
	template<  >			inline float		GetDefaultSignificantDigits<float>()		{return FLOAT_SIGNIFICANT_DIGITS;}
	template<  >			inline double		GetDefaultSignificantDigits<double>()		{return DOUBLE_SIGNIFICANT_DIGITS;}
	template<  >			inline long double	GetDefaultSignificantDigits<long double>()	{return LONG_DOUBLE_SIGNIFICANT_DIGITS;}
	//@}

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	/// Comparison of unsigned ints.
	inline bool IsZero(const S_UINT32 &a, const S_UINT32 & S_UNUSED(nUnused) = 0)
	{
		return (0 == a);
	}
	/// Comparison of unsigned 64 bit ints.
	inline bool IsZero(const S_UINT64 &a, const S_UINT64 & S_UNUSED(nUnused) = 0)
	{
		return (0 == a);
	}
	/// Comparison of 64 bit ints.
	inline bool IsZero(const S_INT64 &a, const S_INT64 & S_UNUSED(nUnused) = 0)
	{
		return (0 == a);
	}
	/// Comparison of ints.
	inline bool IsZero(const S_INT32 &a, const S_INT32 & S_UNUSED(nUnused) = 0)
	{
		return (0 == a);
	}

	/// Reliable comparison of floats. If you're working with numbers in the range of 100 to 1000, working range would be 1000, for numbers 1e-6 to 1e-7, working range would be 1e-6, for 1e6 to 1e8, working range would be 1e8
	inline bool IsZero(const float &a, const float &fWorkingRange = GetDefaultWorkingRange<float>())
	{
		return (Abs(a) <= (fWorkingRange * FLOAT_SIGNIFICANT_DIGITS));
	}
	/// Reliable comparison of doubles.
	inline bool IsZero(const double &a, const double &fWorkingRange = GetDefaultWorkingRange<double>())
	{
		return (Abs(a) <= (fWorkingRange * DOUBLE_SIGNIFICANT_DIGITS));
	}

	/// Reliable comparison of doubles.
	inline bool IsZero(const long double &a, const long double &fWorkingRange = GetDefaultWorkingRange<long double>())
	{
		return (Abs(a) <= (fWorkingRange * LONG_DOUBLE_SIGNIFICANT_DIGITS));
	}

	/// Reliable comparison of unsigned int.
	inline bool IsNotZero(const S_UINT32 &a, const S_UINT32 & S_UNUSED(nUnused) = 0)
	{
		return (0 != a);
	}
	/// Reliable comparison of ints.
	inline bool IsNotZero(const S_INT32 &a, const S_INT32 & S_UNUSED(nUnused) = 0)
	{
		return (0 != a);
	}
	/// Reliable comparison of floats.
	inline bool IsNotZero(const float &a, const float &fWorkingRange = GetDefaultWorkingRange<float>())
	{
		return (Abs(a) > (fWorkingRange * FLOAT_SIGNIFICANT_DIGITS));
	}
	/// Reliable comparison of doubles.
	inline bool IsNotZero(const double &a, const double &fWorkingRange = GetDefaultWorkingRange<double>())
	{
		return (Abs(a) > (fWorkingRange * DOUBLE_SIGNIFICANT_DIGITS));
	}

	/// Reliable comparison of doubles.
	inline bool IsNotZero(const long double &a, const long double &fWorkingRange = GetDefaultWorkingRange<long double>())
	{
		return (Abs(a) > (fWorkingRange * LONG_DOUBLE_SIGNIFICANT_DIGITS));
	}

	/// Comparison of unsigned ints.
	inline bool IsEqual(const S_UINT16 &a, const S_UINT16 &b, const S_UINT16 & S_UNUSED(nUnused) = 0)
	{
		return (a == b);
	}
	/// Comparison of ints.
	inline bool IsEqual(const S_INT16 &a, const S_INT16 &b, const S_INT16 & S_UNUSED(nUnused) = 0)
	{
		return (a == b);
	}
	/// Comparison of unsigned ints.
	inline bool IsEqual(const S_UINT32 &a, const S_UINT32 &b, const S_UINT32 & S_UNUSED(nUnused) = 0)
	{
		return (a == b);
	}
	/// Comparison of ints.
	inline bool IsEqual(const S_INT32 &a, const S_INT32 &b, const S_INT32 & S_UNUSED(nUnused) = 0)
	{
		return (a == b);
	}
	/// Comparison of unsigned ints.
	inline bool IsEqual(const S_UINT64 &a, const S_UINT64 &b, const S_UINT64 & S_UNUSED(nUnused) = 0)
	{
		return (a == b);
	}
	/// Comparison of ints.
	inline bool IsEqual(const S_INT64 &a, const S_INT64 &b, const S_INT64 & S_UNUSED(nUnused) = 0)
	{
		return (a == b);
	}
	/// Reliable comparison of floats.
	inline bool IsEqual(const float &a, const float &b, const float &fWorkingRange = GetDefaultWorkingRange<float>())
	{
		return IsZero(a - b, fWorkingRange);
	}
	/// Reliable comparison of doubles.
	inline bool IsEqual(const double &a, const double &b, const double &fWorkingRange = GetDefaultWorkingRange<double>())
	{
		return IsZero(a - b, fWorkingRange);
	}

	/// Reliable comparison of doubles.
	inline bool IsEqual(const long double &a, const long double &b, const long double &fWorkingRange = GetDefaultWorkingRange<long double>())
	{
		return IsZero(a - b, fWorkingRange);
	}

	template<typename TYPE>
	bool IsEqual(const TYPE *pA, const TYPE *pB)
	{
		if(S_NULL == pA && S_NULL == pB)
			return true;

		if(S_NULL == pA && S_NULL != pB)
			return false;

		if(S_NULL != pA && S_NULL == pB)
			return false;

		return *pA == *pB;
	}

	/// Is equal for array
	template<typename TYPE>
	bool IsEqual(const TYPE *pA, const TYPE *pB, const S_UINT32 nSize)
	{
		if(S_NULL == pA && S_NULL == pB)
			return true;

		if(S_NULL == pA && S_NULL != pB)
			return false;

		if(S_NULL != pA && S_NULL == pB)
			return false;

		for (S_UINT32 n(0); n < nSize; ++n, ++pA, ++pB)
		{
			if (*pA != *pB)
				return false;
		}

		return true;
	}
	template<typename ARRAY>
	bool IsEqualArray1D(const ARRAY &vA, const ARRAY &vB)
	{
		if (vA.GetSize() != vB.GetSize())
			return false;

		for (S_UINT32 n(0); n < vA.GetSize(); ++n)
		{
			if (!IsEqual(vA[n], vB[n]))
				return false;
		}

		return true;
	}

	/// For Array1D of Point3D
	template<typename ARRAY>
	bool IsEqualPointArray1D(const ARRAY &vA, const ARRAY &vB)
	{
		if (vA.GetSize() != vB.GetSize())
			return false;

		for (S_UINT32 n(0); n < vA.GetSize(); ++n)
		{
			if (vA[n] != vB[n])
				return false;
		}

		return true;
	}

	/// Comparison of unsigned ints.
	inline bool IsNotEqual(const S_UINT32 &a, const S_UINT32 &b, const S_UINT32 & S_UNUSED(nUnused) = 0)
	{
		return (a != b);
	}
	/// Comparison of ints.
	inline bool IsNotEqual(const S_INT32 &a, const S_INT32 &b, const S_INT32 & S_UNUSED(nUnused) = 0)
	{
		return (a != b);
	}
	/// Reliable comparison of floats.
	inline bool IsNotEqual(const float &a, const float &b, const float &fWorkingRange = GetDefaultWorkingRange<float>())
	{
		return IsNotZero(a - b, fWorkingRange);
	}
	/// Reliable comparison of doubles.
	inline bool IsNotEqual(const double &a, const double &b, const double &fWorkingRange = GetDefaultWorkingRange<double>())
	{
		return IsNotZero(a - b, fWorkingRange);
	}

	/// Reliable comparison of doubles.
	inline bool IsNotEqual(const long double &a, const long double &b, const long double &fWorkingRange = GetDefaultWorkingRange<long double>())
	{
		return IsNotZero(a - b, fWorkingRange);
	}

	template<typename TYPE>
	bool IsNotEqual(const TYPE *pA, const TYPE *pB)
	{
		return !IsEqual(pA, pB);
	}

	/// Format a std::string in a similar manner as sprintf
	int Format(DcsString &strResult, const char *strFormat, ... );

	/// Format a std::string in a similar manner as sprintf
	int Format(std::string &strResult, const char *strFormat, ... );

	/// Format a std::string in a similar manner as sprintf
	std::string Format(const char *strFormat, ... );

	/// Format a std::string in a similar manner as sprintf
	std::string FormatArgs(const char *strFormat, va_list args );

	/// Format a std::string in a similar manner as sprintf
	int FormatArgs(DcsString &strResult, const char *strFormat, va_list args );

	/// Format a std::string in a similar manner as sprintf
	int FormatArgs(std::string &strResult, const char *strFormat, va_list args );
	
	/// Case-sensitive string comparison
	bool IsEqual(const DcsString &strA, const DcsString &strB);
	bool IsNotEqual(const DcsString &strA, const DcsString &strB);

	/// Given a string, such as "hello, world , text", SplitString() turns it into a vector 'hello', 'world', 'text'. Pass 0 to the strip spaces parameters to prevent character stripping.
	void		SplitString(const DcsString &strIn, std::vector< DcsString > &vSplit, int nAtChar = ',', int nStripLeadingSpaces = ' ', int nStripTrailingSpaces = ' ');

	///	Sleep for a certain number of milliseconds.
	/// This blocks the calling application for the specified amount of time.
	void			SleepTime(unsigned int nMilliSecs);
	/// Returns the number of milliseconds elapsed since the start of the program.
	unsigned int	MilliSecondsSinceProgramStart();


	template <typename TYPE>
	class LinkedList
	{
	public:
		LinkedList()
		{
			m_nNumItems = 0;
			m_pFirst = S_NULL;
			m_pLast = S_NULL;
		}

		~LinkedList()
		{
			FreeMemory();
		}

		struct iterator;
		struct const_iterator;

	protected:
		struct Node;

	public:
		LinkedList<TYPE>& operator=(const LinkedList<TYPE> &list)
		{
			FreeMemory();

			if(0 == list.Length())
				return *this;

			Node *pCurrentSource = S_NULL;

			pCurrentSource = list.m_pFirst;
			m_pFirst = new Node(pCurrentSource->m_data);
			S_ASSERT(S_NULL != m_pFirst);

			m_pLast = m_pFirst;
			pCurrentSource = pCurrentSource->m_pNext;

			for(; pCurrentSource != S_NULL ; pCurrentSource = pCurrentSource->m_pNext)
			{
				m_pLast->m_pNext = new Node(pCurrentSource->m_data);
				S_ASSERT(S_NULL != m_pLast->m_pNext);
				m_pLast->m_pNext->m_pPrev = m_pLast;
				m_pLast = m_pLast->m_pNext;
			}

			m_nNumItems = list.m_nNumItems;
			return *this;
		}

		bool operator==(const LinkedList<TYPE> &list)const
		{
			if(Length() != list.Length())
				return false;

			const_iterator itThis = Begin();
			const_iterator itCompare = list.Begin();
			for(S_UINT64 n(0) ; n < Length() ; ++n, ++itThis, ++itCompare)
			{
				if(*itThis != *itCompare)
					return false;
			}

			return true;
		}

		bool operator!=(const LinkedList<TYPE> &list)const
		{
			return !operator==(list);
		}

		TYPE& operator[](const S_UINT64 nIndex)
		{
			S_ASSERT(m_nNumItems > nIndex);
			iterator it(m_pFirst);
			for(S_UINT64 n(0) ; n < nIndex ;++n)
				++it;

			return *it;
		}

		const TYPE& operator[](const S_UINT64 nIndex)const
		{
			S_ASSERT(m_nNumItems > nIndex);
			const_iterator it(m_pFirst);
			for(S_UINT64 n(0) ; n < nIndex ;++n)
				++it;

			return *it;
		}

		///
		/// Delete all nodes
		///
		void FreeMemory()
		{
			if(S_NULL == m_pFirst)
				return;

			Node *pNext = S_NULL;

			for(S_UINT64 n(0) ; n < m_nNumItems && m_pFirst != m_pLast ; ++n)
			{
				pNext = m_pFirst->m_pNext;
				if(pNext) {
					pNext->m_pPrev = S_NULL;
				}
				m_pFirst->m_pNext = S_NULL;
				DELETE_POINTER(m_pFirst);

				m_pFirst = pNext;
			}

			if(m_pFirst == m_pLast)
			{
				DELETE_POINTER(m_pFirst);
				m_pLast = S_NULL;
			}

			m_nNumItems = 0;
		}

		///
		/// Deletes items at the end of the list when reducing size. Appends items when increasing size.
		///
		void SetSize(const S_UINT64 nNewSize)
		{
			// Same size
			if(nNewSize == m_nNumItems)
				return;

			// Delete all items
			if(0 == nNewSize)
			{
				FreeMemory();
				return;
			}

			// Append items
			if(nNewSize > m_nNumItems)
			{
				const S_UINT64 nNumItemsToAdd(nNewSize-m_nNumItems);

				for(S_UINT64 n(0) ; n < nNumItemsToAdd ; ++n)
					Append(TYPE());

				return;
			}

			// Delete items
			const S_UINT64 nNumItemsToRemove(m_nNumItems-nNewSize);

			for(S_UINT64 n(0) ; n < nNumItemsToRemove ; ++n)
			{
				m_pLast = m_pLast->m_pPrev;
				m_pLast->m_pNext->m_pPrev = S_NULL;
				DELETE_POINTER(m_pLast->m_pNext);
				--m_nNumItems;
			}
		}

		///
		/// Append node
		///
		bool Append(const TYPE &type)
		{
			Node *pnode;

			pnode = new Node(type);

			if(S_NULL == pnode)
			{
				S_ASSERT(0);
				return false;
			}

			++m_nNumItems;

			// First node
			if(S_NULL == m_pFirst)
			{
				m_pFirst = pnode;
				m_pLast = pnode;
				return true;
			}

			// Append node
			m_pLast->m_pNext = pnode;
			pnode->m_pPrev  = m_pLast;
			m_pLast = pnode;
			return true;
		}

		///
		/// Append List
		///
		bool Append(const LinkedList<TYPE> &list)
		{
			const_iterator it(list.Begin());

			for(S_UINT64 n(0) ; n < list.Length() ; ++n, ++it)
				Append(*it);

			return true;
		}

		///
		/// Delete node
		///
		bool Delete(iterator &it)
		{
			Node *pCurrent = m_pFirst;

			for(S_UINT64 n(0) ; n < m_nNumItems ; ++n)
			{
				if(it.m_pNode != pCurrent)
				{
					S_ASSERT(S_NULL != pCurrent->m_pNext);
					pCurrent = pCurrent->m_pNext;
					continue;
				}

				// Update the pointer to the first element if needed
				if(m_pFirst == pCurrent) {
					m_pFirst = pCurrent->m_pNext;
				}

				if(S_NULL != pCurrent->m_pNext)
					pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;

				if(S_NULL != pCurrent->m_pPrev)
					pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;

				DELETE_POINTER(pCurrent);
				it = iterator(S_NULL);

				--m_nNumItems;
				return true;
			}

			return false;
		}

		///
		/// Insert node
		///
		bool Insert(const S_UINT64 nIndex, const TYPE &type)
		{
			if(nIndex == 0)
			{
				m_pFirst->m_pPrev = new Node(type);
				S_ASSERT(S_NULL != m_pFirst->m_pPrev);
				m_pFirst->m_pPrev->m_pNext = m_pFirst;
				m_pFirst = m_pFirst->m_pPrev;

				++m_nNumItems;
				return true;
			}

			iterator it = iterator(m_pFirst) + (nIndex-1);
			it.m_pNode->m_pNext = new Node(type);
			S_ASSERT(S_NULL != it.m_pNode->m_pNext);
			it.m_pNode->m_pNext->m_pPrev = it.m_pNode;
			
			++m_nNumItems;
			return true;
		}

		///
		/// Get Length of list
		///
		S_UINT64 Length()const
		{
			return m_nNumItems;
		}
		
		///
		/// First item of list
		///
		iterator Begin()
		{
			return iterator(m_pFirst);
		}

		///
		/// Get null iterator
		///
		iterator End()
		{
			return iterator(S_NULL);
		}
		
		///
		/// First item of list
		///
		const_iterator Begin()const
		{
			return const_iterator(m_pFirst);
		}

		///
		/// Get null iterator
		///
		const_iterator End()const
		{
			return const_iterator(S_NULL);
		}

		///
		/// iterator
		///
		struct iterator
		{
			friend struct const_iterator;
			friend class LinkedList<TYPE>;
		public:
			iterator()
			{
				m_pNode = S_NULL;
			}

			iterator(Node *pnode)
			{
				m_pNode = pnode;
			}

			iterator(const iterator &it)
			{
				m_pNode = it.m_pNode;
			}

			iterator& operator=(const iterator& it)
			{
				if (this != &it)
					m_pNode = it.m_pNode;
				return (*this);
			}

			iterator& operator++()
			{
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pNext;

				return *this;
			}

			iterator& operator--()
			{
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pPrev;

				return *this;
			}

			iterator operator++(int)
			{
				iterator it = *this;
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pNext;

				return it;
			}

			iterator operator--(int)
			{
				iterator it = *this;
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pPrev;

				return it;
			}

			iterator operator+(const S_UINT64 nIndex)
			{
				iterator it = *this;
				for(S_UINT64 n(0) ; n < nIndex ; ++n)
					it++;

				return it;
			}

			iterator operator-(const S_UINT64 nIndex)
			{
				iterator it = *this;
				for(S_UINT64 n(0) ; n < nIndex ; ++n)
					it--;

				return it;
			}

			TYPE& operator*()const
			{
				S_ASSERT(S_NULL != m_pNode);
				return m_pNode->m_data;
			}

			TYPE* operator->()const
			{
				S_ASSERT(S_NULL != m_pNode);
				return &m_pNode->m_data;
			}

			bool operator==(const iterator& it)const
			{
				if(S_NULL == m_pNode || S_NULL == it.m_pNode)
					return m_pNode == it.m_pNode;

				return	m_pNode == it.m_pNode &&
						m_pNode->m_pNext == it.m_pNode->m_pNext &&
						m_pNode->m_pPrev == it.m_pNode->m_pPrev;
			}

			bool operator!=(const iterator& it)const
			{
				return !operator==(it);
			}

		protected:
			Node *m_pNode;
		};

		///
		/// constant iterator
		///
		struct const_iterator
		{
		public:
			const_iterator()
			{
				m_pNode = S_NULL;
			}

			const_iterator(Node *pnode)
			{
				m_pNode = pnode;
			}

			const_iterator(const iterator &it)
			{
				m_pNode = it.m_pNode;
			}

			const_iterator(const const_iterator &it)
			{
				m_pNode = it.m_pNode;
			}

			const_iterator& operator=(const iterator &it)
			{
				m_pNode = it.m_pNode;
				return *this;
			}

			const_iterator& operator=(const const_iterator &it)
			{
				m_pNode = it.m_pNode;
				return *this;
			}

			const_iterator& operator++()
			{
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pNext;

				return *this;
			}

			const_iterator& operator--()
			{
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pPrev;

				return *this;
			}

			const_iterator operator++(int)
			{
				const_iterator it = *this;
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pNext;

				return it;
			}

			const_iterator operator--(int)
			{
				const_iterator it = *this;
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pPrev;

				return it;
			}

			const_iterator operator+(const S_UINT64 nIndex)
			{
				const_iterator it = *this;
				for(S_UINT64 n(0) ; n < nIndex ; ++n)
					it++;

				return it;
			}

			const_iterator operator-(const S_UINT64 nIndex)
			{
				const_iterator it = *this;
				for(S_UINT64 n(0) ; n < nIndex ; ++n)
					it--;

				return it;
			}

			const TYPE& operator*()const
			{
				S_ASSERT(S_NULL != m_pNode);
				return m_pNode->m_data;
			}

			const TYPE* operator->()const
			{
				S_ASSERT(S_NULL != m_pNode);
				return &m_pNode->m_data;
			}

			bool operator==(const const_iterator& it)const
			{
				if(S_NULL == m_pNode || S_NULL == it.m_pNode)
					return m_pNode == it.m_pNode;

				return	m_pNode == it.m_pNode &&
						m_pNode->m_pNext == it.m_pNode->m_pNext &&
						m_pNode->m_pPrev == it.m_pNode->m_pPrev;
			}

			bool operator!=(const const_iterator& it)const
			{
				return !operator==(it);
			}

		protected:
			const Node *m_pNode;
		};

	protected:
		struct Node
		{
			Node()
			{
				m_pNext = m_pPrev = S_NULL;
			}
			Node(const TYPE &type)
				: m_data(type)
			{
				m_pNext = m_pPrev = S_NULL;
			}

			Node& operator=(const Node &node)
			{
				m_data = node.m_data;
				return *this;
			}

			TYPE m_data;

			Node *m_pNext;
			Node *m_pPrev;
		};

		S_UINT64 m_nNumItems;

		Node *m_pFirst;
		Node *m_pLast;
	};
	

	template <typename TYPE>
	class Stack
	{
	public:
		Stack()
		{
			m_nNumItems = 0;
			m_pTop = S_NULL;
			m_pBottom = S_NULL;
		}

		~Stack()
		{
			FreeMemory();
		}

	protected:
		struct Node;

	public:
		Stack<TYPE>& operator=(const Stack<TYPE> &stack)
		{
			FreeMemory();

			if(0 == stack.Length())
				return *this;

			Node *pCurrentSource = S_NULL;

			pCurrentSource = stack.m_pBottom;
			m_pBottom = new Node(pCurrentSource->m_data);
			S_ASSERT(S_NULL != m_pBottom);

			m_pTop = m_pBottom;
			pCurrentSource = pCurrentSource->m_pNext;

			for(; pCurrentSource != S_NULL ; pCurrentSource = pCurrentSource->m_pNext)
			{
				m_pTop->m_pNext = new Node(pCurrentSource->m_data);
				S_ASSERT(S_NULL != m_pTop->m_pNext);
				m_pTop->m_pNext->m_pPrev = m_pTop;
				m_pTop = m_pTop->m_pNext;
			}

			m_nNumItems = stack.m_nNumItems;
			return *this;
		}

		///
		/// Delete all nodes
		///
		void FreeMemory()
		{
			if(S_NULL == m_pBottom)
				return;

			Node *pNext = S_NULL;

			for(S_UINT64 n(0) ; n < m_nNumItems && m_pBottom != m_pTop ; ++n)
			{
				pNext = m_pBottom->m_pNext;
				pNext->m_pPrev = S_NULL;
				m_pBottom->m_pNext = S_NULL;
				DELETE_POINTER(m_pBottom);

				m_pBottom = pNext;
			}

			if(m_pBottom == m_pTop)
			{
				DELETE_POINTER(m_pBottom);
				m_pTop = S_NULL;
			}

			m_nNumItems = 0;
		}

		///
		/// Push item onto the stack
		///
		bool Push(const TYPE &type)
		{
			if(S_NULL == m_pTop)
			{
				m_pTop = new Node(type);

				if(S_NULL == m_pTop)
				{
					S_ASSERT(0);
					return false;
				}

				m_pBottom = m_pTop;

				++m_nNumItems;
				return true;
			}

			m_pTop->m_pNext = new Node(type);

			if(S_NULL == m_pTop->m_pNext)
			{
				S_ASSERT(0);
				return false;
			}

			m_pTop->m_pNext->m_pPrev = m_pTop;
			m_pTop = m_pTop->m_pNext;
			++m_nNumItems;
			return true;
		}

		///
		/// Pop item off the stack
		///
		TYPE Pop()
		{
			if(S_NULL == m_pTop)
				return TYPE();

			TYPE type = m_pTop->m_data;
			Node *pPrev = m_pTop->m_pPrev;

			DELETE_POINTER(m_pTop);
			m_pTop = pPrev;

			--m_nNumItems;

			if(S_NULL == m_pTop)
			{
				m_pBottom = S_NULL;
				return type;
			}

			m_pTop->m_pNext = S_NULL;
			return type;
		}

		S_UINT64 Length()const
		{
			return m_nNumItems;
		}

		struct const_iterator;

		const_iterator Top()const
		{
			return const_iterator(m_pTop);
		}

		const_iterator Bottom()const
		{
			return const_iterator(m_pBottom);
		}

		const_iterator End()const
		{
			return const_iterator(S_NULL);
		}

		///
		/// constant iterator
		///
		struct const_iterator
		{
		public:
			const_iterator()
			{
				m_pNode = S_NULL;
			}

			const_iterator(Node *pnode)
			{
				m_pNode = pnode;
			}

			const_iterator(const const_iterator &it)
			{
				m_pNode = it.m_pNode;
			}

			const_iterator& operator=(const const_iterator &it)
			{
				m_pNode = it.m_pNode;
				return *this;
			}

			///
			/// Moves up the stack
			///
			const_iterator& operator++()
			{
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pNext;

				return *this;
			}

			///
			/// Moves down the stack
			///
			const_iterator& operator--()
			{
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pPrev;

				return *this;
			}

			///
			/// Moves up the stack
			///
			const_iterator operator++(int)
			{
				const_iterator it = *this;
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pNext;

				return it;
			}

			///
			/// Moves down the stack
			///
			const_iterator operator--(int)
			{
				const_iterator it = *this;
				if(S_NULL != m_pNode)
					m_pNode = m_pNode->m_pPrev;

				return it;
			}

			///
			/// Moves up the stack
			///
			const_iterator operator+(const S_UINT64 nIndex)
			{
				const_iterator it = *this;
				for(S_UINT64 n(0) ; n < nIndex ; ++n)
					it++;

				return it;
			}

			///
			/// Moves down the stack
			///
			const_iterator operator-(const S_UINT64 nIndex)
			{
				const_iterator it = *this;
				for(S_UINT64 n(0) ; n < nIndex ; ++n)
					it--;

				return it;
			}

			const TYPE& operator*()const
			{
				S_ASSERT(S_NULL != m_pNode);
				return m_pNode->m_data;
			}

			const TYPE* operator->()const
			{
				S_ASSERT(S_NULL != m_pNode);
				return &m_pNode->m_data;
			}

			bool operator==(const const_iterator& it)const
			{
				return m_pNode == it.m_pNode;
			}

			bool operator!=(const const_iterator& it)const
			{
				return m_pNode != it.m_pNode;
			}

		protected:
			const Node *m_pNode;
		};

	protected:
		struct Node
		{
			Node()
			{
				m_pNext = m_pPrev = S_NULL;
			}
			Node(const TYPE &type)
				: m_data(type)
			{
				m_pNext = m_pPrev = S_NULL;
			}

			TYPE m_data;

			Node *m_pNext;
			Node *m_pPrev;
		};

		S_UINT64 m_nNumItems;

		Node *m_pTop;
		Node *m_pBottom;
	};

	///
	/// Represents a 128-bit GUID (globally unique identifier)
	/// Internal data structures follow Windows GUID as used by CoCreateGuid.
	///
	class DcsGUID
	{
	public:
		DcsGUID();
		bool operator==(const DcsGUID &rhs);

		/// Generates a GUID
		void Generate();

		/// Sets the GUID from a string of the form "00000000.0000.0000.0000.000000000000"
		bool Set(const std::string &str);

		/// Sets the GUID from a string of the form "00000000.0000.0000.0000.000000000000"
		bool Set(const DcsString& str);

		/// Converts the GUID to a string of hex values in the form "00000000.0000.0000.0000.000000000000"
		DcsString AsString()const;

		/// Converts the GUID to a string of decimal numbers in the form "0000000000.00000.00000.000000.000000000000000000"
		DcsString AsDecimalString()const;

		/// Generate GUID and return as string
		static DcsString GenerateAsString();

		/// Converts the GUID to a string of decimal numbers
		static DcsString GenerateAsDecimalString();

	    unsigned int  m_nData1;	///< unsigned int b/c int and long are different sizes on Linux.
	    unsigned short m_nData2;
	    unsigned short m_nData3;
	    unsigned char  m_pchData4[8];
	};

}//namespace SDICOS

#pragma pop_macro("new")

#endif
