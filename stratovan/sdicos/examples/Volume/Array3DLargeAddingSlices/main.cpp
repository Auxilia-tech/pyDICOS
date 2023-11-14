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
#include <list>

#include "SDICOS/DICOS.h"

/// StartArray3DLargeAddingSlices

bool Array3DLargeAddingSlicesExample();

int main()
{
	bool bRes = Array3DLargeAddingSlicesExample();

	if(bRes)
		std::cout << "Array3DLargeAddingSlicesExample finished successfully" << std::endl;
	else
		std::cout << "Array3DLargeAddingSlicesExample failed" << std::endl;

	return (bRes ? 0 : 1);
}

///
/// Sample code for incrementally adding slices to a volume
///
/// \section Array3DLargeAddingSlicesExample Creating a 3D volume by incrementally adding slices
///
/// Incrementally add slices to a volume. The slices can be owned by the Array3DLarge object
/// or by the user.
///
bool Array3DLargeAddingSlicesExample()
{
	bool bRes(true);
	const SDICOS::S_UINT32 nWidth(197), nHeight(237), nDepth(50);

	//
	// Construct the Array3DLarge object and indicate that it does not own the data
	//
	const SDICOS::MemoryPolicy::VOLUME_MEMORY_POLICY nMemoryPolicy = SDICOS::MemoryPolicy::DOES_NOT_OWN_SLICES;
		
	// A nDepth of 0 indicates that no slices are allocated at construction
	SDICOS::Array3DLarge<SDICOS::S_INT32> volData(nWidth, nHeight, 0, nMemoryPolicy);
	
	const SDICOS::S_INT32 nInitValue(0XFADEC01B);
	SDICOS::S_UINT32 nSliceCount(0);
		
	// Each slice is an SDICOS::Array2D object
	SDICOS::Array2D<SDICOS::S_INT32> *pNewSlice = new SDICOS::Array2D<SDICOS::S_INT32>(nWidth, nHeight);

	pNewSlice->Zero(nInitValue); //Initialize each volume element with the same nValue
	
	// Add the slice to the volume. AddSlice returns true/false.
	bRes = volData.AddSlice(pNewSlice) && bRes;
		
	// A slice with bad dimensions is rejected.
	// The action taken when a bad slice is encountered is one of
	//	SDICOS::Array3DLargeBase::EARLY_OUT
	//	SDICOS::Array3DLargeBase::SKIP_AND_CONTINUE (applies only when adding multiple slices)
	//	SDICOS::Array3DLargeBase::ADD_DEBUG_SLICE 
	// The default action is EARLY_OUT
	SDICOS::Array2D<SDICOS::S_INT32> vSliceDifferentDims(nWidth-1, nHeight-1);
	vSliceDifferentDims.Zero(nInitValue);
		
	bool bAddResult = volData.AddSlice(&vSliceDifferentDims); // this call fails
	bRes = (!bAddResult) && bRes;
	bRes = (1 == volData.GetDepth()) && bRes;
		
	//
	// Add a debug slice filled with a specific nValue.
	// The debug slice is always owned by the Array3DLarge object
	//
	const SDICOS::Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nAddSliceFailurePolicy = SDICOS::Array3DLargeBase::ADD_DEBUG_SLICE;
	const SDICOS::S_INT32 nDebugFillValue(0xABCDEF);

	bAddResult = volData.AddSlice(&vSliceDifferentDims, nAddSliceFailurePolicy, &nDebugFillValue);
		
	// Failure to properly add the slice still returns false even if the debug slice is added
	bRes = (!bAddResult) && bRes;
	bRes = (2 == volData.GetDepth()) && bRes;

	//Check the first value of both slices
	//volData[Slice][Row][Column]
	bRes = volData[0][0][0] == nInitValue && bRes;
	bRes = volData[1][0][0] == nDebugFillValue && bRes;

	if(!bRes) 
	{
		std::cout << "Array3DLargeAddingSlicesExample failed to add slice with wrong dimensions" << std::endl;
		std::cout << "added debug slice using failure policy ADD_DEBUG_SLICE." << std::endl;
	}

	volData.FreeMemory(); //Delete references to slices
	SDICOS::DELETE_POINTER(pNewSlice); //Delete slice

	//Reinitialize the volume to accept slices of nWidth x nHeight
	volData.SetSize(nWidth, nHeight, 0);

	//Add the slice with incorrect dimensions, which results in adding a debug slice again
	bAddResult = volData.AddSlice(&vSliceDifferentDims, nAddSliceFailurePolicy, &nDebugFillValue);

	//
	// Allocated multiple slices to add to the volume
	//
	std::list< SDICOS::Array2D<SDICOS::S_INT32>* > listSlices;
	for(SDICOS::S_UINT32 i(0); i < nDepth; ++i)
	{
		pNewSlice = new SDICOS::Array2D<SDICOS::S_INT32>(nWidth, nHeight);
		pNewSlice->Zero(nInitValue + i);
		listSlices.push_back(pNewSlice);
	}

	const SDICOS::S_UINT32 nNewSliceCount = SDICOS::S_UINT32(volData.GetDepth() + listSlices.size());

	// Add a bad slice that will be ignored because the error policy is SKIP_AND_CONTINUE. 
	// All good slices will be added.
	pNewSlice = new SDICOS::Array2D<SDICOS::S_INT32>(12,13);
	listSlices.insert((++listSlices.begin()), pNewSlice);

	// Add slices to the volume using iterator bounds and ignore bad slices.
	// Note that if bad slices are encountered AddSlices() will return false regardless of what
	// the bad slice policy is set to
	const bool bResAddSlicesWithBadSlice = volData.AddSlices(listSlices.begin(), listSlices.end(), SDICOS::Array3DLargeBase::SKIP_AND_CONTINUE);
	bRes = !bResAddSlicesWithBadSlice && bRes;

	// Check that all slices have been added
	bRes = (volData.GetDepth() == nNewSliceCount) && bRes;
		
	if(bRes)
		std::cout << "Array3DLargeAddingSlicesExample successfully added " << (listSlices.size()-1) << " listSlices from a list using iteration." << std::endl;
				
	// Use an iterator to traverse the slices and test that slice data is correct.
	SDICOS::S_UINT32 nDebugSliceCount(0);
	SDICOS::S_INT32 nValidSliceCount(0);
	SDICOS::Array3DLarge<SDICOS::S_INT32>::Iterator it = volData.Begin();

	for(nSliceCount = 0; it != volData.End(); ++it, ++nSliceCount)
	{
		const SDICOS::S_INT32 nValue = (**it)[0][0]; //Access first value of slice

		if(nValue == nDebugFillValue)
			++nDebugSliceCount;
		else if(nValue == (nValidSliceCount + nInitValue))
			++nValidSliceCount;
		else
		{
			bRes = false;
			std::cout << "Array3DLargeAddingSlicesExample encountered bad nValue for slice " << nSliceCount << std::endl;
		}
	}

	bRes = (nValidSliceCount == SDICOS::S_INT32(nNewSliceCount - nDebugSliceCount));
	bRes = (1 == nDebugSliceCount) && bRes;
	bRes = (nSliceCount == nNewSliceCount) && bRes;

	std::list< SDICOS::Array2D<SDICOS::S_INT32>* >::iterator itSlice;

	//Delete slices
	for (itSlice = listSlices.begin(); itSlice != listSlices.end(); ++itSlice)
		SDICOS::DELETE_POINTER(*itSlice);

	listSlices.clear();
	
	return bRes;
} // EndArray3DLargeAddingSlices
