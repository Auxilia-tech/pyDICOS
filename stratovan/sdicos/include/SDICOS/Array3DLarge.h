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
#ifndef _STRATOVAN_DICOS_ARRAY_3D_LARGE_H__
#define _STRATOVAN_DICOS_ARRAY_3D_LARGE_H__

#include <iterator>
#include <iostream>

#include "SDICOS/Types.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/Array2D.h"
#include "SDICOS/Array2DLarge.h"
#include "SDICOS/MemoryPolicy.h"
#include "SDICOS/IMemoryManager.h"

#pragma push_macro("new")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace SDICOS
{
/// \enum ITERATION_DIRECTION
typedef enum {
	ITERATION_DIRECTION_FORWARD = 0,	///< iterate from first slice to last slice. 0 to (n-1)
	ITERATION_DIRECTION_BACKWARD = 1,	///< iterate from last slice to first slice (n-1) to 0;
	ITERATION_END = 2					///< Indicate the end of iteration
} ITERATION_DIRECTION;

/// \class Array3DLargeBase
/// \brief Hold enumerations and static data for Array3DLarge template
class Array3DLargeBase
{
	public:

	/// \enum ADD_SLICE_FAILURE_POLICY
	typedef enum {
		EARLY_OUT = 0,			///< Stop adding slices and return an error
		SKIP_AND_CONTINUE,		///< Skip the bad slice and continue adding
		ADD_DEBUG_SLICE		///< Add a Debug slice with sentinel value
	} ADD_SLICE_FAILURE_POLICY;
};

/// Use for large arrays i.e., those requiring more than 100MB of memory. Memory is allocated in several smaller chunks to improve the chances of allocation at runtime.
/// Array items are accessed in reverse coordinate order in order to improve cache access patterns. Thus, you must access the Z direction first, followed by the Y direction, and finally the X direction to access the array element.
template < class CType >
class Array3DLarge : public Array1D< Array2D< CType >* >, public Array3DLargeBase
{
public:

	typedef Array3DLarge< CType >		CThisClass;
	typedef Array2D<CType>				CSliceClass;
	typedef CSliceClass*				CSliceClassPtr;
	typedef Array1D< Array2D<CType>* >	CParentClass;

	Array3DLarge()
	: CParentClass(), m_nWidth(0), m_nHeight(0), m_MemoryPolicy(MemoryPolicy::OWNS_SLICES)
	{
	}

	///
	/// Construct an Array3DLarge object with (W, H, D) dimensions and indicate if it is responsible for deleting slice data.
	/// If the memory policy is DOES_NOT_OWN_SLICES then the depth dimension is only used to preallocate slots for future slices.
	/// To create an empty volume with memory policy OWNS_SLICES, set depth to 0.
	///
	/// @param nWidth	Slice Width. All added slices must have this width.
	/// @param nHeight	Slice Height. All added slices must have this height.
	/// @param nDepth	Number of slices to allocate or number of slots for future slices to preallocate.
	/// @param memoryPolicy if true the Array3DLarge owns its slices and deletes them, if false it does not
	///
	Array3DLarge(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth, const MemoryPolicy::VOLUME_MEMORY_POLICY memoryPolicy)
	: CParentClass(), m_nWidth(0), m_nHeight(0), m_MemoryPolicy(memoryPolicy)
	{
		SetSize(nWidth, nHeight, nDepth);
	}

	///
	/// Copy Constructor. Data is copied and owned by the copy.
	///
	Array3DLarge(const CThisClass &obj) : CParentClass(), m_MemoryPolicy(MemoryPolicy::OWNS_SLICES)
	{
		Init();
		*this = obj;
	}

	/// Destructor
	virtual ~Array3DLarge()
	{
		FreeMemory();
	}

	///
	/// Assignment operator. Data is copied and owned by the copy.
	///
	CThisClass& operator=(const CThisClass &obj);

	///
	/// Comparison operator
	///
	bool operator==(const CThisClass& obj) const;

	/// Comparison operator
	bool operator!=(const CThisClass& obj) const
	{
		return !operator==(obj);
	}

	/// Array subscript operator
	inline const CSliceClass& operator[](S_UINT32 n)const
	{
		S_ASSERT((n < GetDepth()));
		return (*CParentClass::operator [](n)); // dereference Array2D<CType>*
	}

	/// Array subscript operator
	inline CSliceClass& operator[](S_UINT32 n)
	{
		S_ASSERT((n < GetDepth()));
		return (*CParentClass::operator [](n)); // dereference Array2D<CType>*
	}

	///
	/// Indicate whether or not the Array3DLarge is responsible for deleting its slices.
	/// @param nMemPolicy Memory deletion policy for volume data.
	///
	void SetMemoryPolicy(const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy)
	{
		m_MemoryPolicy = nMemPolicy;
		CSliceClass **pArray2D = CParentClass::GetBuffer();
		for (S_UINT32 n(0); n < CParentClass::GetSize(); ++n, ++pArray2D)
			(*pArray2D)->SetOwnership(MemoryPolicy::OWNS_SLICES == nMemPolicy);
	}

	/// Ask if the array owns its slices
	bool OwnsSlices() const { return (m_MemoryPolicy == MemoryPolicy::OWNS_SLICES); }

	/// Get a Pointer to the indicated slice
	CSliceClass* GetSlice(const S_UINT32 nD) 
	{
		return CParentClass::operator [](nD);
	}

	/// Get a const pointer to the indicated slice
	const CSliceClass* GetSlice(const S_UINT32 nD) const
	{
		return CParentClass::operator [](nD);
	}

	///
	/// Add a slice to the volume and return a pointer to it. If the current volumes
	/// width and height are (0,0) the given dimensions are used, otherwise they are ignored.
	///
	/// @param width Width for the new slice if width and height have not been set. Ignored otherwise.
	/// @param height Height for the new slice if width and height have not been set. Ignored otherwise.
	/// @return a pointer to the allocated slice
	///
	CSliceClass* AddSlice(const SDICOS::S_UINT32 width, const SDICOS::S_UINT32 height);

	///
	/// Add a slice to the volume and return a pointer to it. If the current volumes
	/// width and height are (0,0) the given dimensions are used otherwise they are ignored.
	///
	/// @param pSlice Slice data to add
	/// @param width Width for the new slice if width and height have not been set. Ignored otherwise.
	/// @param height Height for the new slice if width and height have not been set. Ignored otherwise.
	/// @return a pointer to the allocated slice
	///
	CSliceClass* AddSlice(CType *pSlice, const SDICOS::S_UINT32 width, const SDICOS::S_UINT32 height);

	///
	/// Add a slice allocated by the user to the volume.
	/// Ensure that the volume's memory ownership policy is set as intended.
	/// If set to OWNS_SLICES and pNewSlice owns the data, ownership will transfer to this object.
	/// If set to OWNS_SLICES and pNewSlice does not own the data, this function will return false.
	/// If set to DOES_NOT_OWN_SLICES, this object will not take ownership of the data.
	/// The ADD_SLICE_FAILURE_POLICY::ADD_DEBUG_SLICE is supported. All others do nothing.
	///
	/// @param pNewSlice Pointer to the slice (Array2D) to be added
	/// @param nFailurePolicy Action to take if adding a slice fails. (e.g. bad dimensions)
	/// @param pfFillValue Value to fill in debug slice with if ADD_DEBUG_SLICE is specified.
	/// @return true/false false if the slice could not be added. e.g. it is NULL, width and height do not match etc.
	///					   false is returned even if a debug slice was added as dictated by the failure policy
	///
	bool AddSlice(CSliceClass* pNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = EARLY_OUT, const CType* pfFillValue = S_NULL);

	///
	/// Add multiple slices stored as an array of pointers
	/// 
	bool AddSlices(CSliceClass **pNewSlices, const SDICOS::S_UINT32 numSlices);

	///
	/// Add slices that are stored in range covered by two stl-like iterators.
	/// If a slice cannot be added, the failure policy determine what action is taken.
	///	IMPORTANT: If the failure policy is ADD_DEBUG_SLICE the added slice is governed by the Array3DLarge object's Memory Policy
	///			   so the user is responsible for deleting the debug slices if the memory policy is DOES_NOT_OWN_SLICES
	///
	/// @param itStart Start Iterator
	/// @param itEnd End Iterator
	/// @param nFailurePolicy Action to take if adding a slice fails.
	/// @param pfFillValue Value to fill 
	/// @return true/false false if one or more slices could not be added
	template<typename _InputIterator>
	bool AddSlices(const _InputIterator& itStart, const _InputIterator& itEnd, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = EARLY_OUT, const CType* pfFillValue = S_NULL);

	/// Move slice ownership to this class. Memory policy must be set to OWNS_SLICES
	Array2D<CType>* MoveSlice(CType *pNewSlice, const S_UINT32 nWidth, const S_UINT32 nHeight, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = EARLY_OUT, const CType* pfFillValue = S_NULL);
	/// Move slice ownership to this class. Memory policy must be set to OWNS_SLICES
	Array2D<CType>* MoveSlice(Array2D<CType> &vNewSlice, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = EARLY_OUT, const CType* pfFillValue = S_NULL);

	/// Move slice ownership to this class. Memory policy must be set to OWNS_SLICES
	template<typename _InputIterator>
	bool MoveSlices(const _InputIterator& itStart, const _InputIterator& itEnd, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = EARLY_OUT, const CType* pfFillValue = S_NULL);
	
	/// Move slice ownership to this class. Memory policy must be set to OWNS_SLICES
	bool MoveSlices(Array3DLarge<CType> &vSrc);

	///
	/// Set the dimensions of the volume.
	/// The Memory Policy dictates how depth is used:
	///		OWNS_SLICES: nDepth number of slices are preallocated
	///		DOES_NOT_OWN_SLICES: the initial slice capacity of the volume is nDepth
	/// The depth can be initialized to 0 if slices are added incrementally.
	///
	/// @param nWidth Slice width
	/// @param nHeight Slice height
	/// @param nDepth Slice depth
	/// @return true/false
	bool SetSize(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth);

	///
	/// Fill in all elements of each slice with the zero value.
	///
	void Zero(const CType &zero)
	{
		for(S_UINT32 nD = 0; nD < GetDepth(); ++nD)
		{
			CParentClass::operator[](nD)->Zero(zero);
		}
	}

	///
	/// Free allocated memory for all slices if the slices are owned by the volume
	/// 
	virtual void FreeMemory()
	{
		{
			// Delete all slices
			CSliceClass **pArray2D = CParentClass::GetBuffer();
			for(S_UINT32 z = 0; z < GetDepth(); ++z, ++pArray2D)
			{
				DELETE_POINTER(*pArray2D);
			}
		}

		// Delete debug slices
		m_vDebugSlices.FreeMemory();

		// Delete pointers to the slices
		CParentClass::FreeMemory();
		m_nWidth= m_nHeight = 0;
	}

	void FreeMemory(IMemoryManager *pMemMgr)
	{
		MemoryBuffer mb;
		CSliceClass **pArray2D = CParentClass::GetBuffer();
		for (S_UINT32 n(0); n < CParentClass::GetSize(); ++n, ++pArray2D)
		{
			if (!(*pArray2D)->HasOwnership())
			{
				mb.SetMemoryPolicy(MemoryBuffer::enumPolicy_DoesNotOwnData);
				mb.SetBuffer((unsigned char*)((*pArray2D)->GetBuffer()), (*pArray2D)->EstimateCoreFootprint());
				pMemMgr->Deallocate(mb);
			}
			else
				mb.SetMemoryPolicy(MemoryBuffer::enumPolicy_OwnsData);

			DELETE_POINTER(*pArray2D);
		}

		// Delete debug slices
		m_vDebugSlices.FreeMemory();

		// Delete pointers to the slices
		CParentClass::FreeMemory();
		m_nWidth = m_nHeight = 0;
	}

	///
	/// Clear the number of slices in the volume to 0 and delete slice memory if it's owned by the volume.
	/// This intended use case for this method is when a user manages the slice memory and manually adds
	/// slices to a volume before saving DICOS files to disk or sending them over a network.
	///
	void Clear()
	{
		{
			// Delete all slices
			CSliceClass **pArray2D = CParentClass::GetBuffer();
			for (S_UINT32 z = 0; z < GetDepth(); ++z, ++pArray2D)
			{
				DELETE_POINTER(*pArray2D);
			}
		}

		// Delete debug slices
		m_vDebugSlices.FreeMemory();
				
		// Reset the size of the array of slices to 0 but keep the capacity the same.
		// The depth is now 0 but width and height and still the same.
		CParentClass::Clear();
	}

	// Computes an estimate of how much memory this object takes up in RAM...
	virtual S_UINT32 EstimateCoreFootprint()const
	{
		return sizeof(CType) * m_nWidth * m_nHeight * GetDepth();
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
		return m_nHeight;
	}
	inline S_UINT32 GetDepth()const
	{
		return CParentClass::GetSize();
	}

	/// Get the number of elements in a slice for this volume
	inline S_UINT32 GetElementsPerSlice() const
	{
		return GetWidth()*GetHeight();
	}

	inline void GetSize(S_UINT32 &nW, S_UINT32 &nH, S_UINT32 &nD)const
	{
		nW	= m_nWidth;
		nH	= m_nHeight;
		nD	= GetDepth();
	}

	////////////////////////////////
	////////////////////////////////

	/**
	 * \class SDICOS.Array3DLarge.Iterator
	 * \brief Iterate over the slices in an Array3DLarge object.
	 *
	 * Iterator over the individual slices of the 3D volume from
	 * front to back or back to front.
	 */
	class Iterator
	{
		friend class Array3DLarge< CType >;

		public:
			/// Construct empty Iterator that indicates iteration has ended
			Iterator() : m_nCurrentSlice(ITERATION_END_VALUE), m_parray3D(S_NULL), m_psliceCurrent(S_NULL), m_Direction(ITERATION_DIRECTION_FORWARD) {}

			///
			/// Construct an Iterator that is ready for iteration over the given volume.
			/// @param obj The Array3DLarge volume to iterate over
			/// @param dir The direction that iteration should occur. 
			///
			Iterator(const CThisClass& obj, const ITERATION_DIRECTION dir = ITERATION_DIRECTION_FORWARD)
			: m_nCurrentSlice(ITERATION_END_VALUE), m_parray3D(&obj), m_psliceCurrent(NULL), m_Direction(dir)
			{
				if(0 != obj.GetDepth())
				{	
					if (ITERATION_DIRECTION_FORWARD == m_Direction)
					{
						m_nCurrentSlice = 0;
						m_psliceCurrent = m_parray3D->CParentClass::GetBuffer() + m_nCurrentSlice;;
					}
					else if (ITERATION_DIRECTION_BACKWARD == m_Direction)
					{
						m_nCurrentSlice = obj.GetDepth() - 1;
						m_psliceCurrent = m_parray3D->CParentClass::GetBuffer() + m_nCurrentSlice;;
					}
					else if (ITERATION_END == m_Direction)
					{
						m_nCurrentSlice = ITERATION_END_VALUE;
						m_psliceCurrent = S_NULL;
					}
				}
			}

			/// Copy constructor
			Iterator(const Iterator& it)
			: m_nCurrentSlice(it.m_nCurrentSlice), m_parray3D(it.m_parray3D), m_psliceCurrent(it.m_psliceCurrent), m_Direction(it.m_Direction)
			{
			}

			virtual ~Iterator()	{}

			/// Assignment operator
			Iterator& operator=(const Iterator& it)
			{
				if(this != &it)
				{
					m_nCurrentSlice =it.m_nCurrentSlice;
					m_parray3D = it.m_parray3D;
					m_psliceCurrent = it.m_psliceCurrent;
					m_Direction = it.m_Direction;
				}
				return (*this);
			}

			/// Comparison operator
			bool operator==(const Iterator& it) const
			{
				return(m_nCurrentSlice == it.m_nCurrentSlice);
			}

			/// Comparison operator
			bool operator!=(const Iterator& it) const { return !operator==(it); }

			/// The prefix operator++ increments the Iterator one step in the iteration direction.
			///	ITERATION_DIRECTION_FORWARD: move to a slice with greater depth
			/// ITERATION_DIRECTION_BACKWARD: move to a slice with lesser depth
			///
			/// If the Iterator is at the iteration itEnd value operator++ does nothing.
			///
			/// Dereferencing the Iterator return a pointer to the current slice or NULL.
			/// @return a reference to the Iterator is returned
			Iterator& operator++()
			{
				// early out if current slice for iteration is not valid
				if(!m_parray3D || (m_nCurrentSlice < 0))
					return (*this);

				if(ITERATION_DIRECTION_FORWARD == m_Direction)
				{
					++m_nCurrentSlice;
					// Volumes with > 2^31 slices are not supported
					if (m_nCurrentSlice >= SDICOS::S_INT32(m_parray3D->GetDepth()))
					{
						m_nCurrentSlice = ITERATION_END_VALUE;
						m_psliceCurrent = S_NULL;
					}
					else
						++m_psliceCurrent;
				}
				else
				{
					--m_nCurrentSlice;
					if (ITERATION_END_VALUE < m_nCurrentSlice)
						--m_psliceCurrent;
					else
						m_psliceCurrent = S_NULL;
				}
				return (*this);
			}

			/// The prefix operator--() decrements the Iterator one step in the iteration direction.
			///	ITERATION_DIRECTION_FORWARD: move to a slice with lesser depth
			/// ITERATION_DIRECTION_BACKWARD: move to a slice with greater depth
			///
			/// If the Iterator is at the iteration itEnd value operator-- does nothing.
			/// @return a reference to the Iterator is returned
			Iterator& operator--()
			{
				// early out if current slice for iteration is not valid
				if(!m_parray3D || (m_nCurrentSlice < 0))
					return (*this);

				if(ITERATION_DIRECTION_FORWARD == m_Direction)
				{
					--m_nCurrentSlice;
					if (ITERATION_END_VALUE < m_nCurrentSlice)
						--m_psliceCurrent;
					else
						m_psliceCurrent = S_NULL;
				}
				else
				{	
					// for a reverse direction iterator operator-- advances one slice in depth
					++m_nCurrentSlice;
					if (m_nCurrentSlice >= SDICOS::S_INT32(m_parray3D->GetDepth()))
					{
						m_nCurrentSlice = ITERATION_END_VALUE;
						m_psliceCurrent = S_NULL;
					}
					else
						++m_psliceCurrent;
				}
				return (*this);
			}

			/// The postfix operator++ increments the Iterator one step in the iteration direction.
			/// @see operator++()
			Iterator operator++(S_INT32)
			{
				Iterator it(*this);
				operator++();
				return it;
			}

			/// The postfix operator-- increments the Iterator one step in the iteration direction.
			/// @see operator--()
			Iterator operator--(S_INT32)
			{
				Iterator it(*this);
				operator--();
				return it;
			}

			/// The operator+=() increments the Iterator n steps in the iteration direction.
			///	ITERATION_DIRECTION_FORWARD: move to a slice with greater depth
			/// ITERATION_DIRECTION_BACKWARD: move to a slice with lesser depth
			///
			/// If the Iterator is at the iteration itEnd value operator+ does nothing.
			/// @return a reference to the incremented Iterator is returned
			Iterator& operator+=(const S_INT32 nInc)
			{
				// early out if current slice for iteration is not valid
				if(!m_parray3D || (m_nCurrentSlice < 0))
					return (*this);

				if(ITERATION_DIRECTION_FORWARD == m_Direction)
				{
					m_nCurrentSlice += nInc;
				}
				else
				{
					m_nCurrentSlice -= nInc;
				}

				if (0 > m_nCurrentSlice || SDICOS::S_INT32(m_parray3D->GetDepth()) <= m_nCurrentSlice)
				{
					m_nCurrentSlice = ITERATION_END_VALUE;
					m_psliceCurrent = S_NULL;
				}
				else if(ITERATION_DIRECTION_FORWARD == m_Direction)
					m_psliceCurrent += nInc;
				else
					m_psliceCurrent -= nInc;

				return *this;
			}

			/// The operator-=() decrements the Iterator n steps in the iteration direction.
			///	ITERATION_DIRECTION_FORWARD: move to a slice with lesser depth
			/// ITERATION_DIRECTION_BACKWARD: move to a slice with greater depth
			///
			/// If the returned Iterator is at the iteration itEnd value operator- does nothing.
			/// @return a reference to the decremented Iterator is returned
			Iterator operator-=(const S_INT32 nInc)
			{
				return operator+=(-nInc);
			}

			/// The operator+ increments the Iterator n steps in the iteration direction.
			/// @see operator+=(S_INT32)
			Iterator operator+(const S_INT32 n)
			{
				Iterator it(*this);
				it += n;
				return it;
			}

			/// The operator- increments the Iterator n steps in the iteration direction.
			/// @see operator-=(S_INT32)
			Iterator operator-(const S_INT32 n)
			{
				Iterator it(*this);
				it -= n;
				return it;
			}

			///
			/// Dereferencing the Iterator returns a pointer to the slice or NULL if iteration has ended.
			/// @return pointer to the slice or NULL
			///
			CSliceClass* operator*()
			{
				if(S_NULL == m_parray3D || 
					m_nCurrentSlice < 0 || 
					m_nCurrentSlice >= SDICOS::S_INT32(m_parray3D->GetDepth()))
					return S_NULL;

				return const_cast<CSliceClass*>(*m_psliceCurrent);
			}

			const CSliceClass* operator*() const
			{
				if(S_NULL == m_parray3D || 
					m_nCurrentSlice < 0 || 
					m_nCurrentSlice >= S_INT32(m_parray3D->GetDepth()))
					return S_NULL;

				return *m_psliceCurrent;
			}

			/// Initialize with a new object and iteration direction
			void Init(const CThisClass& obj, const ITERATION_DIRECTION dir = ITERATION_DIRECTION_FORWARD)
			{
				m_parray3D = &obj;
				m_Direction = dir;
				m_nCurrentSlice = (ITERATION_DIRECTION_FORWARD == m_Direction) ? 0 : (m_parray3D->GetDepth()-1);
				m_psliceCurrent = m_parray3D->CParentClass::GetBuffer() + m_nCurrentSlice;
			}

			/// Reset the Iterator to the itStart or itEnd of the array based on the iteration direction
			bool Reset() 
			{ 
				if(!m_parray3D)
				{
					m_nCurrentSlice = ITERATION_END_VALUE;
					return false;
				}

				m_nCurrentSlice = (ITERATION_DIRECTION_FORWARD == m_Direction) ? 0 : (m_parray3D->GetDepth()-1);
				m_psliceCurrent = m_parray3D->CParentClass::GetBuffer() + m_nCurrentSlice;
				return true;
			}

			void SetIterationDirection(const ITERATION_DIRECTION dir)
			{
				m_Direction = dir;
			}

			ITERATION_DIRECTION GetIterationDirection() const { return m_Direction; }

			/// Set the iterator to point to the first slice in the volume
			bool SetFirst() 
			{
				if(!m_parray3D)
					return false;
				m_nCurrentSlice = 0; 
				m_psliceCurrent = m_parray3D->CParentClass::GetBuffer();
				return true;
			}

			/// Set the iterator to point to the last slice in the volume
			bool SetLast() 
			{
				if(!m_parray3D)
					return false;
				m_nCurrentSlice = m_parray3D->GetDepth()-1; 
				m_psliceCurrent = m_parray3D->CParentClass::GetBuffer() + m_nCurrentSlice;
				return true;
			}

			/// Get the depth in the volume for the slice referenced by the iterator
			/// @return Slice index or a negative number if the iterator is invalid
			SDICOS::S_INT32 GetCurrentSlice() const { return m_nCurrentSlice; }

		private:
			mutable SDICOS::S_INT32 m_nCurrentSlice; ///< Negative number indicates itEnd of iteration
			const CThisClass* m_parray3D;			///< Volume to iterate over
			CSliceClass * const*m_psliceCurrent;	///< Pointer to current slice
			ITERATION_DIRECTION m_Direction;		///< Direction of iteration

			/// Sentinel marker for the itEnd of the iteration
			static const SDICOS::S_INT32 ITERATION_END_VALUE = -1;

			/// Force the iterator to act as if iteration has ended.
			void SetEnd() { m_nCurrentSlice = ITERATION_END_VALUE; }
	};

	///
	/// Get an Iterator ready for forward Iterator
	///
	Iterator Begin() const
	{
		return Iterator(*this);
	}

	///
	/// Iterator that references the itEnd of forward iteration
	///
	Iterator End() const
	{
		return Iterator(*this, SDICOS::ITERATION_END);
	}

	///
	/// Get an Iterator ready for reverse iteration
	///
	Iterator RBegin() const
	{
		return Iterator(*this, SDICOS::ITERATION_DIRECTION_BACKWARD);
	}

	///
	/// Iterator that references the itEnd of backward iteration
	///
	Iterator REnd() const
	{
		return Iterator(*this, ITERATION_END);
	}

protected:
	void Init()
	{
		m_nWidth		= 0;
		m_nHeight		= 0;
	}

private:

	bool IsDebugSlice(const CSliceClassPtr pSlice )const
	{
		for(SDICOS::S_UINT32 i(0); i < m_vDebugSlices.GetSize(); ++i)
		{
			if(m_vDebugSlices[i] == pSlice)
				return true;
		}
		return false;
	}

	S_UINT32		m_nWidth, m_nHeight;

	/// Indicates whether or not the Array3DLarge object owns its slices
	/// and deletes the data buffers.
	MemoryPolicy::VOLUME_MEMORY_POLICY m_MemoryPolicy;

	/// If debug slices are added they are always owned by the Array3DLarge object
	/// The size of this array is expected to be small.
	Array1D<CSliceClassPtr> m_vDebugSlices;
};

template<typename CType>
Array3DLarge<CType>& Array3DLarge<CType>::operator=(const CThisClass &obj)
{
	if(this == &obj)
		return *this;

	// Assignment copies data and is now owned
	m_MemoryPolicy = MemoryPolicy::OWNS_SLICES;

	if(GetDepth() == obj.GetDepth() && GetHeight() == obj.GetHeight() && GetWidth() == obj.GetWidth())
	{
		// Copy and exit

		Iterator itThis(*this);
		Iterator itObj(obj);
		for(; itThis != End(); ++itThis, ++itObj)
		{
			**itThis = **itObj;
		}

		return *this;
	}

	FreeMemory();

	// Allocate a pointer for each slice
	CParentClass::SetSize(obj.GetDepth());

	for(S_UINT32 nD = 0; nD < obj.GetDepth(); ++nD)
	{
		const CSliceClass * pSlice = obj.GetSlice(nD);
		CParentClass::operator[](nD) = new CSliceClass(*pSlice);
	}

	m_nWidth = obj.GetWidth();
	m_nHeight = obj.GetHeight();

	return *this;
}

template<typename CType>
bool Array3DLarge<CType>::operator==(const CThisClass& obj) const
{
	if( GetDepth() != obj.GetDepth() ||
		GetWidth() != obj.GetWidth() ||
		GetHeight() != obj.GetHeight())
	{
		return false;
	}

	// Compare actual slice data
	for(S_UINT32 z = 0; z < GetDepth(); ++z)
	{
		if((*obj.GetSlice(z)) != (*GetSlice(z)))
			return false;
	}
	return true;
}

template<typename CType>
bool Array3DLarge<CType>::SetSize(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth)
{
	if((m_nWidth == nWidth) && (m_nHeight == nHeight) && (GetDepth() == nDepth))
		return true;

	bool bRes(true);

	if(MemoryPolicy::OWNS_SLICES == m_MemoryPolicy)
	{
		bRes = bRes && CParentClass::SetSize(nDepth);

		// Width and Height are set after depth because CParentClass::SetSize() calls the virtual function FreeMemory() which sets width/height to 0.
		m_nWidth = nWidth;
		m_nHeight = nHeight;

		CSliceClass *pSlice(S_NULL);

		for(S_UINT32 nD = 0; nD < GetDepth(); ++nD)
		{
			pSlice = new CSliceClass(m_nWidth, m_nHeight);
			CParentClass::operator [](nD) = pSlice;
			bRes = bRes && (S_NULL != pSlice) ;
		}
	}
	else if(MemoryPolicy::DOES_NOT_OWN_SLICES == m_MemoryPolicy)
	{
		bRes = CParentClass::Reserve(nDepth) && bRes;

		// Width and Height are set after depth because CParentClass::Reserve() calls the virtual function FreeMemory() which sets width/height to 0.
		m_nWidth	= nWidth;
		m_nHeight	= nHeight;

		// Don't allocate any slices as this memory policy assumes the user will add slices accordingly
	}
	else
		return false;
	return bRes;
}

template<typename CType>
Array2D<CType>* Array3DLarge<CType>::AddSlice(CType *pSlice, const SDICOS::S_UINT32 width, const SDICOS::S_UINT32 height)
{
	if(0 == width || 0 == height)
		return S_NULL;

	if(0 == m_nWidth && 0 == m_nWidth)
	{
		m_nWidth = width;
		m_nHeight = height;
	}

	CSliceClass * pNewSlice(S_NULL);

	try
	{
		pNewSlice = new CSliceClass();
	}
	catch (...)
	{
		pNewSlice = S_NULL;
		return S_NULL;
	}

	pNewSlice->MoveData(pSlice, m_nWidth, m_nHeight);
	pNewSlice->SetOwnership(MemoryPolicy::OWNS_SLICES == m_MemoryPolicy);

	if(CParentClass::Add(pNewSlice))
		return pNewSlice;

	DELETE_POINTER(pNewSlice);
	return S_NULL;
}

template<typename CType>
Array2D<CType>* Array3DLarge<CType>::AddSlice(const SDICOS::S_UINT32 width, const SDICOS::S_UINT32 height)
{
	if (0 == width || 0 == height)
		return S_NULL;

	if (0 == m_nWidth && 0 == m_nWidth)
	{
		m_nWidth = width;
		m_nHeight = height;
	}

	CSliceClass * pNewSlice(S_NULL);

	try
	{
		pNewSlice = new CSliceClass(m_nWidth, m_nHeight);
	}
	catch (...)
	{
		pNewSlice = S_NULL;
		return S_NULL;
	}

	pNewSlice->SetOwnership(MemoryPolicy::OWNS_SLICES);

	// Caller owns pointer to data
	if (MemoryPolicy::OWNS_SLICES != m_MemoryPolicy)
	{
		AddSlice(pNewSlice);
		return pNewSlice;
	}

	if(CParentClass::Add(pNewSlice))
		return pNewSlice;

	return S_NULL;
}

template<typename CType>
bool Array3DLarge<CType>::AddSlice(
	CSliceClass* pNewSlice,
	const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY failurePolicy,
	const CType* fillValue)
{
	if (S_NULL == pNewSlice ||
		0 == pNewSlice->GetWidth() ||
		0 == pNewSlice->GetHeight())
		return false;

	// Check if input slice does not own data and this object is set to own data
	if (!pNewSlice->HasOwnership() && MemoryPolicy::OWNS_SLICES == m_MemoryPolicy)
	{
		return false;
	}

	// If existing width and height are both 0 initialize the size of slices
	// with the dimensions of the slice being added and attempt to add the slice.
	if(0 == m_nWidth && 0 == m_nHeight)
	{
		m_nWidth = pNewSlice->GetWidth();
		m_nHeight = pNewSlice->GetHeight();
	}
	
	if(	(pNewSlice->GetWidth() == m_nWidth) &&
		(pNewSlice->GetHeight() == m_nHeight))
	{
		CSliceClass * pSlice(S_NULL);

		try 
		{ 
			pSlice = new CSliceClass();
		}
		catch (...) 
		{ 
			pSlice = S_NULL; 
			return false;
		}

		pSlice->MoveData(pNewSlice->GetBuffer(), m_nWidth, m_nHeight);

		// Transfer ownership
		if (pNewSlice->HasOwnership() && MemoryPolicy::OWNS_SLICES == m_MemoryPolicy)
		{
			pSlice->SetOwnership(true);
			pNewSlice->SetOwnership(false);
		}
		else
		{
			// Set to not own data
			pSlice->SetOwnership(false);
		}

		if(CParentClass::Add(pSlice))
			return true;
	}

	// Process failure if dimensions are bad or adding fails

	if(failurePolicy == Array3DLargeBase::ADD_DEBUG_SLICE)
	{
		CSliceClass * pNewDebugSlice(S_NULL);

		try			{ pNewDebugSlice = new CSliceClass(GetWidth(), GetHeight()); }
		catch(...)	{ pNewDebugSlice = S_NULL; }

		if(pNewDebugSlice) 
		{
			if(fillValue)
				pNewDebugSlice->Zero((*fillValue));

			if(!CParentClass::Add(pNewDebugSlice))
			{
				DELETE_POINTER( pNewDebugSlice );
			} 
			else 
			{
				// Array3DLarge owns all debug slices
				m_vDebugSlices.Add(pNewDebugSlice);
			}
		} 
	}

	return false; // return false even when debug slice added
}

template<typename CType>
bool Array3DLarge<CType>::AddSlices(CSliceClass **pNewSlices, const SDICOS::S_UINT32 numSlices)
{
	bool bRes(true);
	for(SDICOS::S_UINT32 i = 0; i < numSlices; ++i)
	{
		bRes = AddSlice(pNewSlices[i]) && bRes;
	}
	return bRes;
}
		
template<typename CType>
template<typename _InputIterator>
bool Array3DLarge<CType>::AddSlices(const _InputIterator& start, const _InputIterator& end, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY failurePolicy, const CType* fillValue)
{
	bool bRes(true);
	for(_InputIterator it(start); (it != end); ++it)
	{
		// AddSlice() handles adding debug slice
		bool AddSliceResult = AddSlice((*it), failurePolicy, fillValue);
		if(!AddSliceResult && (Array3DLargeBase::ADD_DEBUG_SLICE != failurePolicy))
		{
			switch(failurePolicy)
			{
				case Array3DLargeBase::EARLY_OUT:
					return false;
				case Array3DLargeBase::SKIP_AND_CONTINUE:
					bRes = false;
					break;
				default:
					return false; /// Early out if supplied policy is bad
			}
		}
		bRes = bRes && AddSliceResult;
	}
	return bRes;
}

template<typename CType>
Array2D<CType>* Array3DLarge<CType>::MoveSlice(
	CType *pNewSlice, 
	const S_UINT32 nWidth, const S_UINT32 nHeight,
	const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY failurePolicy,
	const CType* fillValue)
{
	if(!pNewSlice || MemoryPolicy::OWNS_SLICES != m_MemoryPolicy)
		return S_NULL;

	Array2D<CType> *pslice = S_NULL;

	// If existing width and height are both 0 initialize the size of slices
	// with the dimensions of the slice being added and attempt to add the slice.
	if(0 == m_nWidth && 0 == m_nHeight)
	{
		m_nWidth = nWidth;
		m_nHeight = nHeight;
	}
	
	if(	nWidth == m_nWidth &&
		nHeight == m_nHeight)
	{
		try
		{
			pslice = new Array2D<CType>;
		}
		catch(...)
		{
			return S_NULL;
		}
		pslice->MoveData(pNewSlice, nWidth, nHeight);

		if(CParentClass::Add(pslice))
			return pslice;
	}

	// Process failure if dimensions are bad or adding fails

	if(failurePolicy == Array3DLargeBase::ADD_DEBUG_SLICE)
	{
		CSliceClass * pNewSlice(S_NULL);
		try			{ pNewSlice = new CSliceClass(m_nWidth, m_nHeight); }
		catch(...)	{ pNewSlice = S_NULL; }

		if(pNewSlice) 
		{
			if(fillValue)
				pNewSlice->Zero((*fillValue));

			if(!CParentClass::Add(pNewSlice))
			{
				DELETE_POINTER( pNewSlice );
			} 
			else 
			{
				// Array3DLarge owns all debug slices
				m_vDebugSlices.Add(pNewSlice);
			}
		} 
	}

	return S_NULL; // return NULL even when debug slice added
}

template<typename CType>
Array2D<CType>* Array3DLarge<CType>::MoveSlice(
	Array2D<CType> &vNewSlice,
	const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy,
	const CType* pfFillValue)
{
	if (MemoryPolicy::OWNS_SLICES != m_MemoryPolicy)
		return S_NULL;

	Array2D<CType> *pslice(S_NULL);

	// If existing width and height are both 0 initialize the size of slices
	// with the dimensions of the slice being added and attempt to add the slice.
	if (0 == m_nWidth && 0 == m_nHeight)
	{
		m_nWidth = vNewSlice.GetWidth();
		m_nHeight = vNewSlice.GetHeight();
	}

	if (vNewSlice.GetWidth() == m_nWidth &&
		vNewSlice.GetHeight() == m_nHeight)
	{
		try
		{
			pslice = new Array2D<CType>;
		}
		catch (...)
		{
			return S_NULL;
		}
		pslice->MoveData(vNewSlice);

		if (CParentClass::Add(pslice))
			return pslice;
	}

	// Process failure if dimensions are bad or adding fails

	if (nFailurePolicy == Array3DLargeBase::ADD_DEBUG_SLICE)
	{
		CSliceClass * pNewSlice(S_NULL);
		try { pNewSlice = new CSliceClass(GetWidth(), GetHeight()); }
		catch (...) { pNewSlice = S_NULL; }

		if (pNewSlice)
		{
			if (pfFillValue)
				pNewSlice->Zero((*pfFillValue));

			if (!CParentClass::Add(pNewSlice))
			{
				DELETE_POINTER(pNewSlice);
			}
			else 
			{
				// Array3DLarge owns all debug slices
				m_vDebugSlices.Add(pNewSlice);
			}
		}
	}

	return S_NULL; // return NULL even when debug slice added
}
		
template<typename CType>
template<typename _InputIterator>
bool Array3DLarge<CType>::MoveSlices(const _InputIterator& itStart, const _InputIterator& itEnd, 
									const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy, const CType* pfFillValue)
{
	if (MemoryPolicy::OWNS_SLICES != m_MemoryPolicy)
		return false;

	bool bRes(true);
	for(_InputIterator it(itStart); (it != itEnd); ++it)
	{
		// AddSlice() handles adding debug slice
		bRes = MoveSlice(**it, nFailurePolicy, pfFillValue) && bRes;
		if(!bRes && (Array3DLargeBase::ADD_DEBUG_SLICE != nFailurePolicy))
		{
			switch(nFailurePolicy)
			{
				case Array3DLargeBase::EARLY_OUT:
					return false;
				case Array3DLargeBase::SKIP_AND_CONTINUE:
					bRes = false;
					break;
				default:
					return false; /// Early out if supplied policy is bad
			}
		}
	}
	return bRes;
}
		
template<typename CType>
bool Array3DLarge<CType>::MoveSlices(Array3DLarge<CType> &vSrc)
{
	FreeMemory();

	CParentClass::m_bDeleteBuffer	= true;
	m_MemoryPolicy					= MemoryPolicy::OWNS_SLICES;
	CParentClass::m_nCapacity		= vSrc.m_nCapacity;
	CParentClass::m_nSize			= vSrc.m_nSize;
	m_nWidth						= vSrc.m_nWidth;
	m_nHeight						= vSrc.m_nHeight;
	CParentClass::m_pData			= vSrc.m_pData;
	Array1D< Array2D<CType>* >::Move(vSrc.m_vDebugSlices, m_vDebugSlices);

	vSrc.m_MemoryPolicy		= MemoryPolicy::DOES_NOT_OWN_SLICES;
	vSrc.m_pData			= NULL;
	vSrc.m_bDeleteBuffer	= false;
	vSrc.FreeMemory();

	return true;
}

}	// namespace SDICOS

#pragma pop_macro("new")

#endif
