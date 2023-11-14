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
#include <iostream>
#include "SDICOS/DICOS.h"

// StartAccessingArray3DLargeData

bool AccessingArray3DLargeData();

int main()
{
	if(AccessingArray3DLargeData())
	{
		std::cout << "Successfully stored and retrieved data using the Array3DLarge class" << std::endl;
		return 0;
	} 
	else 
	{
		std::cout << "Failed to store and retrieve data using the Array3DLarge class" << std::endl;
		return 1;
	}
}

//
// Sample code for setting and accessing data stored in 3-D arrays.
//
/// \section Array3DLarge_ex1 Using the Array3DLarge class to set and get volume data using 2D slices.
/// Accessing 3D data in the Array3DLarge class.
///
bool AccessingArray3DLargeData()
{
	bool bRes(true);
	
	//
	// <b>The SDICOS::Array3DLarge</b> class stores 3D Data for CT, DX, AIT etc.
	// Internally it is implemented as a 1-D array of 2-D arrays so (X,Y) slices are contiguous blocks of memory.
	//
	SDICOS::Array3DLarge<SDICOS::S_UINT16> vnVolume;
	SDICOS::S_UINT32 width(128),height(128),depth(100);
	vnVolume.SetSize(width,height,depth);
	
	//
	// The 3D array of CT data can be set in multiple ways
	//
	// Method 1: Accessing the array using 3-D indices.
	//
	SDICOS::S_UINT32 z;
	for(z = 0; z < depth; ++z)
	for(SDICOS::S_UINT32 h = 0; h < height; ++h)
	for(SDICOS::S_UINT32 w = 0; w < width; ++w)
		vnVolume[z][h][w] = (z+h+w);

	//
	// Method 2: Accessing the data one plane at a time
	// Note that the 3D memory is not a contiguous block. Slices are contiguous blocks.
	//
	for(z = 0; z < depth; ++z)
	{
		SDICOS::Array2D<SDICOS::S_UINT16> &zPlane = vnVolume[z];
		for(SDICOS::S_UINT32 h = 0; h < height; ++h)
		for(SDICOS::S_UINT32 w = 0; w < width; ++w) {
			if((z+h+w) != zPlane[h][w]) {
				bRes = false;
				std::cout << "Error writing/reading volume data " << zPlane[h][w] << " " << (z+h+w) << std::endl;
			}
			zPlane[h][w] = (z+h+w); // If needed convert raw data to SDICOS::S_UINT16 cConvertData<type>(val);
		}
	}
	
	//
	// Method 3: Access data explicitly as 2D planes
	//
	// The 3D volume is implemented as an array of 2D slices
	// GetSlice() returns a pointer to an Array2D that stores a contiguous block 
	//
	for(z = 0; z < depth; ++z)
	{
		SDICOS::Array2D<SDICOS::S_UINT16> * volSlice = vnVolume.GetSlice(z);

		// one-dimensional array that holds a plane of width*height dimensions
		SDICOS::S_UINT16 * currentSlice = volSlice->GetBuffer();

		// Set data for a single slice as if it is a 1-D array.
		for(SDICOS::S_UINT32 i = 0; i < (width*height); ++i) {
			SDICOS::S_UINT16 value = z + (i/width) + (i%width);
			
			if(currentSlice[i] != value) {
				std::cout << "Error writing/reading volume data " << currentSlice[i] << " " << value << std::endl;
				bRes = false;
			}

			currentSlice[i] = z+i;
		}
	}
	
	//
	// Method 4: Copy data directly into the raw buffers of the array.
	// Requires caller to setup data buffers in the correct format
	//
	
	// Pointer to user data for a XY slice.
	// This is for example purposes only.
	SDICOS::S_UINT16 * userDataForSlice = new SDICOS::S_UINT16[width*height];
	for(SDICOS::S_UINT32 i = 0; i < (width*height); ++i) 
		userDataForSlice[i] = SDICOS::S_UINT16(i);
	
	for(z = 0; z < depth; ++z)
	{
		// point to data buffer for Array2D object
		SDICOS::S_UINT16 * destSlice = vnVolume[z].GetBuffer();
		
		// Copy user data into the volume slice.
		// Alternatively, the user can 
		memcpy(destSlice, userDataForSlice, width*height*sizeof(SDICOS::S_UINT16));
	}

	delete [] userDataForSlice;
	
	// Verify data 
	for(z = 0; z < depth; ++z)
	for(SDICOS::S_UINT32 h = 0; h < height; ++h)
	for(SDICOS::S_UINT32 w = 0; w < width; ++w)
	{
		if(vnVolume[z][h][w] != SDICOS::S_UINT16(h*width+w))
			bRes = false;
	}

	return bRes;
} // EndAccessingArray3DLargeData
