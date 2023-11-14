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
/// StartVolumeExample

#include "SDICOS/DICOS.h"	//DICOS include header

bool VolumeExample();

int main()
{
	bool bRes = VolumeExample();
	if(bRes)
		std::cout << "VolumeExample finished successfully" << std::endl;
	else
		std::cout << "VolumeExample failed" << std::endl;
	return (bRes ? 0 : 1);
}

//
/// Example showing how to use the SDICOS::Volume class used to store signed or unsigned 16-bit
/// volume data in an SDICOS::CT object using SDICOS:Section or an SDICOS::AIT3D object using SDICOS::SectionAIT.
//
/// \section Volume Use the SDICOS::Volume class to store signed or unsigned 8,16,32,64 bit and float data in SDICOS::Section or SDICOS::SectionAIT.
///
bool VolumeExample()
{
	bool bRes(true);
		
	///
	/// The Volume object stores either signed or unsigned 8,16,32,64 bit and float data using the SDICOS::Array3DLarge class.
	/// It is designed to only store one kind of data at a time.
	/// The interface for Volume contains utility methods for interfacing with the 
	SDICOS::Volume vol;
	
	// Explicitly allocate a float volume of the given size and delete any unsigned data
	SDICOS::S_UINT32 width(123),height(234), depth(12);
	vol.Allocate(SDICOS::Volume::enumFloat, width, height, depth);
	
	SDICOS::S_UINT32 sliceCount(0);

	// Use an iterator to access the slices in the volume and manipulate them
	SDICOS::Volume::SliceIterator itSliceFloat = vol.Begin();
	for(; itSliceFloat != vol.End(); ++ itSliceFloat, ++sliceCount)
	{
		// pSlice is a Array2D
		SDICOS::Array2D<float> *pSlice = itSliceFloat.AsFloat();
		
		// Get a raw buffer to the slice's data
		// For further examples for accessing volume data see the Example VolumeDataExample/VolumeDataExample.cpp
		float *pSliceBuffer = pSlice->GetBuffer();

		memset(pSliceBuffer, 0xB0, vol.GetSliceSizeInBytes());
	}
	
	bRes = (sliceCount == depth) && bRes;

	// Slices can be added individually
	SDICOS::Array2D<float> *pSlice = vol.AddSliceFloat();
	bRes = (vol.GetDepth() == (sliceCount+1)) && bRes;	
	depth = vol.GetDepth();

	// Slices can be added using an iterator that supports operator++() and operator*()
	SDICOS::S_UINT32 numNewSlices(5);
	SDICOS::Array2D<float> **ppSlices = new SDICOS::Array2D<float>*[numNewSlices+1];
	for (SDICOS::S_UINT32 i(0); i < numNewSlices; ++i)
	{
		ppSlices[i] = new SDICOS::Array2D<float>(width, height);
		ppSlices[i]->Zero(float(i));
	}
	ppSlices[numNewSlices] = NULL; //Add NULL to mark end of slices
		
	//The volume object, by default, is set to own all the slices and is responsible for deleting them.
	//Adding slices in this way transfers the data from the array of slices to the Volume object
	vol.AddSlices(ppSlices, &ppSlices[numNewSlices]);
	bRes = (vol.GetDepth() == (numNewSlices + depth)) && bRes;

	//Delete slices. They no longer own the data and act as references to the data.
	for (SDICOS::S_UINT32 i(0); i < numNewSlices; ++i)
		DELETE_POINTER(ppSlices[i]);

	delete [] ppSlices; //Delete array of pointers to slices
		
	// The raw Array3DLarge object can be accessed
	SDICOS::Array3DLarge<float> &volRef = *vol.GetFloat();
	bRes = (volRef.GetDepth() == (numNewSlices+depth)) && bRes;

	// Slices can be added from an existing 3D array
	{
		SDICOS::S_UINT32 oldDepth(vol.GetDepth());
		const SDICOS::S_UINT32 w(1), h(2), d(3);
		SDICOS::Array3DLarge<float> newData;

		bRes = newData.SetSize(w,h,d) && bRes;
		newData.Zero(-30789.0f);

		// Fails because slice dimensions do not match
		bRes = !vol.AddSlices(newData) && bRes;

		SDICOS::S_UINT32 newDepth(123);

		// Call SetSize() first to allocate memory by 2D slices.
		bRes = newData.SetSize(vol.GetWidth(),vol.GetHeight(), newDepth) && bRes;
		newData.Zero(-31062.0f);

		// Setting the Array3DLarge (source) and Volume (destination) objects to OWNS_SLICES results in moving
		// ownership of the slices when calling AddSlices().
		//
		// Setting the destination object to DOES_NOT_OWN_SLICES copies references to the slices.
		// This means the slice data is shared between both objects and the source handles deleting
		// the data.
		newData.SetMemoryPolicy(SDICOS::MemoryPolicy::OWNS_SLICES);	//Default memory policy
		vol.SetMemoryPolicy(SDICOS::MemoryPolicy::OWNS_SLICES);	//Default memory policy

		bRes = vol.AddSlices(newData) && bRes;
		bRes = !newData.OwnsSlices(); //No longer owns data as ownership was moved to Volume object
		bRes = SDICOS::MemoryPolicy::OWNS_SLICES == vol.GetMemoryPolicy(); //Volume has data ownership
		bRes = (vol.GetDepth() == (oldDepth + newDepth)) && bRes;
	}

	// Same as above with Unsigned data. The memory allocation policy is set so that the Array3DLarge<float> object owns the data
	// instead of the SDICOS::Volume object.
	{
		// Volume that holds float data, but does not own the data
		SDICOS::Volume vol32bit(SDICOS::Volume::enumUnsigned32Bit, SDICOS::MemoryPolicy::DOES_NOT_OWN_SLICES);

		// Create an Array3DLarge of unsigned slices and add those slices to the Volume object.
		const SDICOS::S_UINT32 w(10), h(20), d(30);
		SDICOS::Array3DLarge<SDICOS::S_UINT32> data(w,h,d, SDICOS::MemoryPolicy::OWNS_SLICES);
		data.Zero(0xFEDC);

		bRes = vol32bit.AddSlices(data) && bRes;
		bRes = (d == vol32bit.GetDepth()) && bRes;
	}

	return bRes;
}
/// EndVolumeExample
