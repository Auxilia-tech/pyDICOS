//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2015 Stratovan Corporation. All Rights Reserved.
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
#include "SDICOS/DICOS.h"

/// StartArray3DLargeIteratorExample
bool Array3DLargeIteratorExample();

int main()
{
	if(	Array3DLargeIteratorExample())
	{
		std::cout << "Array3DLargeIteratorExample finished successfully" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Array3DLargeIteratorExample failed" << std::endl;
		return 1;
	}
}

//
// Sample code for setting and accessing data stored in 3-D arrays using iterator object
//
/// \section Array3DLargeIteratpr Using the Array3DLarge class to set and get volume data using 2D slices.
/// Accessing slices in the Array3DLarge class using iterator classes.
///
bool Array3DLargeIteratorExample()
{
	typedef SDICOS::Array3DLarge<SDICOS::S_INT32> ArrayType;
	bool bRes(true);
	SDICOS::S_UINT32 width(197),height(237),depth(50);

	//
	// Construct the Array3DLarge object to own its slices and preallocate memory for them.
	//
	SDICOS::MemoryPolicy::VOLUME_MEMORY_POLICY memoryPolicy = SDICOS::MemoryPolicy::OWNS_SLICES;
	ArrayType data(width,height,depth,memoryPolicy);
	
	SDICOS::S_INT32 zeroOffset(0xfadec01b);
	SDICOS::S_UINT32 sliceCount(0);
		
	// Use an iterator to traverse the slices
	// in the indicated direction and set their data
	// Forward iteration goes from depth value 0 to the last slice in the volume
	ArrayType::Iterator it(data, SDICOS::ITERATION_DIRECTION_FORWARD);
	for(; it != data.End(); ++it, ++sliceCount)
	{
		// Each slice is an SDICOS::Array2D object
		ArrayType::CSliceClassPtr pSlice = (*it);
		pSlice->Zero(it.GetCurrentSlice() + zeroOffset);
	}
	
	// Sanity checking
	bRes = (sliceCount == depth) && bRes;

	//
	// Iteration can also proceed backward from the last slice to the first slice
	// Note that SDICOS::Array3DLarge::Iterator::operator++ 'increments' the iteration direction
	//
	for(sliceCount = 0, it = data.RBegin(); it != data.REnd(); ++it, ++sliceCount)
	{
		ArrayType::CSliceClass* pSlice = (*it);
		const SDICOS::S_INT32 value = (it.GetCurrentSlice() + zeroOffset);
		SDICOS::S_INT32 *pSliceData = pSlice->GetBuffer();

		// Simple loop over slice contents
		for(SDICOS::S_UINT32 i(0); i < data.GetElementsPerSlice(); ++i)
			bRes = (pSliceData[i] == value) && bRes;
	}
	bRes = (sliceCount == depth) && bRes;
		
	//
	// Iteration can also be done using operator-- to iterate in the opposite order indicated by the iteration direction.
	// e.g. move toward the first slice with a forward iterator and move toward last slice for a backward iteratoe

	// it is currently set to iterate in SDICOS::ITERATION_DIRECTION_BACKWARD
	// iterating with operator-- moves from the first slice to the last slice
	//
	it.SetFirst(); 
	for(sliceCount = 0; it != data.End(); --it, ++sliceCount)
	{
		ArrayType::CSliceClass* pSlice = (*it);
		const SDICOS::S_INT32 value = (it.GetCurrentSlice() + zeroOffset);
		SDICOS::S_INT32 *pSliceData = pSlice->GetBuffer();

		//
		// Simple loop over slice contents
		//
		for(SDICOS::S_UINT32 i(0); i < data.GetElementsPerSlice(); ++i)
			bRes = (pSliceData[i] == value) && bRes;
	}
	bRes = (sliceCount == depth) && bRes;

	//
	// Reset the iterator so that it is a forward iterator at the last element
	//
	it.SetIterationDirection(SDICOS::ITERATION_DIRECTION_FORWARD);
	it.SetLast();

	//
	// Iterate from last slice to first slice using operator--() on a forward iterator.
	//
	for(sliceCount = 0; it != data.REnd(); --it, ++sliceCount)
	{
		ArrayType::CSliceClass* pSlice = (*it);
		const SDICOS::S_INT32 value = (it.GetCurrentSlice() + zeroOffset);
		SDICOS::S_INT32 *pSliceData = pSlice->GetBuffer();

		//
		// Simple loop over slice contents
		//
		for(SDICOS::S_UINT32 i(0); i < data.GetElementsPerSlice(); ++i)
			bRes = (pSliceData[i] == value) && bRes;
	}
	bRes = (sliceCount == depth) && bRes;

	return bRes;
} // EndArray3DLargeIteratorExample
