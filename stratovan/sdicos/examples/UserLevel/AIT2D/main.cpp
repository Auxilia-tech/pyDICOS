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
// StartCreateAIT2DForProcessingSimple

#include "SDICOS/DICOS.h"

bool CreateAIT2DForProcessingSimple()
{
	//
	// Instantiate and initialize the AIT2D object.
	// Attributes not set in the constructor call are set to valid defaults.
	// See API documentation in SdcsTemplateAIT2D.h for default values.
	//		Object of Inspection Type (OOI Type) : Person
	//		AIT Device Type : Passive Millimeter Wave
	//		Presentation Intent Type : For Processing. Indicates data will undergo additional processing.
	//		Photometric Interpretation of Pixel Data : Monochrome2 (low pixel values map to low intensity)
	//
	SDICOS::AIT2D ait(
		SDICOS::ObjectOfInspectionModule::enumTypePerson,
		SDICOS::AIT2DTypes::AIT2DImage::enumPassiveMillimeterWave,
		SDICOS::AIT2DTypes::AIT2DSeries::enumProcessing,
		SDICOS::ImagePixelMacro::enumMonochrome2
	);

	// OOI Type Person required gender
	ait.SetGender(SDICOS::ObjectOfInspectionModule::enumGenderFemale);

	// AIT2D only supports unsigned 8-64 bit and float image data
	SDICOS::S_UINT32 width(256), height(128);
	SDICOS::Image2D& aitData = ait.GetData();

	// Allocate a contiguous block of memory for the AIT data.
	// Data is stored as unsigned shorts (16-bit).
	if(!aitData.Allocate(SDICOS::Image2D::enumUnsigned16Bit, width,height))
	{
        std::cerr << "Failed to allocate AIT data buffer" << std::endl;
        return false;
    }

    // Get reference to allocated unsigned data buffer.
	SDICOS::Array2D<SDICOS::S_UINT16> &rawData = *aitData.GetUnsigned16();

	// Example for setting AIT data by accessing each element individually
	SDICOS::S_UINT16 count(0);
	for(SDICOS::S_UINT32 row(0); row < aitData.GetHeight(); ++row) 
	{
		for(SDICOS::S_UINT32 col(0); col < aitData.GetWidth(); ++col) 
		{
			rawData[row][col] = count++;
		}
	}

	// Buffer that holds user generated data.
	// For example purposes only
	SDICOS::S_UINT16 * userGeneratedData = new unsigned short[width*height];

	//Initialize with dummy data
	memset(userGeneratedData, 0, width*height * sizeof(SDICOS::S_UINT16));

	// Set AIT data by getting a pointer to the raw data buffer
	// allocated by the call to AllocateUnsigned.
	// Data can be copied into this buffer or the buffer can be used directly
	SDICOS::S_UINT16 * rawBuffer = rawData.GetBuffer();
	
	// Copy user generated into allocated buffer for image data.
	memcpy(rawBuffer,userGeneratedData,width*height*sizeof(SDICOS::S_UINT16));

	// Delete buffer
	SDICOS::DELETE_ARRAY(userGeneratedData);

	// Example for how to set the orientation of the person OOI with respect to AIT2D's Coordinate System.
	// This attribute is not required.
	SDICOS::Vector3D<float> personXAxis(-1,0,0), personYAxis(0,-1,0);
	ait.SetPersonOrientation(personXAxis,personYAxis);
	
	SDICOS::ErrorLog errorlog;
	SDICOS::Folder folder("AIT2DFiles");
	SDICOS::Filename filename(folder,"SimpleProcessingAIT2D.dcs");

	if(!ait.Write(filename,errorlog,SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "Simple AIT2D Template Example unable to write DICOS File " << filename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else
	{
		std::cout << "Wrote file to " << filename << std::endl;
		SDICOS::AIT2D aitRead;

		SDICOS::ErrorLog errorlog;
		if(aitRead.Read(filename,errorlog)) {
			if(aitRead == ait) {
				std::cout << "Successfully read and compared AIT2D files" << std::endl;
				return true;
			} else {
				std::cout << "AIT2D file loaded from " << filename << " does not match original." << std::endl;
				return false;
			}
		} 
		else {
			std::cerr << "Unable to read AIT2D file " << filename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}
	return true;
} // EndCreateAIT2DForProcessingSimple


  ///
  ///	Create a AIT2D file using a color palette that is intended for additional processing using the user-level API Object SDICOS::DX.
  ///
bool CreateAIT2DWithColorPaletteForProcessingSimple()
{
	//
	// Instantiate and initialize the AIT2D object.
	// Attributes not set in the constructor call are set to valid defaults.
	// See API documentation in SdcsTemplateAIT2D.h for default values.
	//		Object of Inspection Type (OOI Type) : Person
	//		AIT Device Type : Passive Millimeter Wave
	//		Presentation Intent Type : For Processing. Indicates data will undergo additional processing.
	//		Photometric Interpretation of Pixel Data : enumPaletteColor (Indicates that the a color palette is used.)
	SDICOS::AIT2D ait(
		SDICOS::ObjectOfInspectionModule::enumTypePerson,
		SDICOS::AIT2DTypes::AIT2DImage::enumPassiveMillimeterWave,
		SDICOS::AIT2DTypes::AIT2DSeries::enumProcessing,
		SDICOS::ImagePixelMacro::enumPaletteColor);

	// Identity: Low to high values represent dark to light
	// Inverse: Low to high values represent light to dark
	if (!ait.SetPresentationLUTShape(SDICOS::GeneralImageModule::enumIdentity))
	{
		std::cout << "Invalid Presentation LUT Shape" << std::endl;
		return false;
	}

	//Dimensions of image
	const SDICOS::S_UINT32 nWidth(256), nHeight(128);

	//Set up Red, Green, and Blue color palette
	//These values are indexed into by the Pixel Data values
	SDICOS::Array1D<SDICOS::S_UINT8> &vRed = ait.GetRedLUT();
	SDICOS::Array1D<SDICOS::S_UINT8> &vGreen = ait.GetGreenLUT();
	SDICOS::Array1D<SDICOS::S_UINT8> &vBlue = ait.GetBlueLUT();

	//Set all to same size. This example will use a single color for each row.
	vRed.SetSize(nHeight);
	vGreen.SetSize(nHeight);
	vBlue.SetSize(nHeight);

	SDICOS::S_UINT8 *pnRed = vRed.GetBuffer();
	SDICOS::S_UINT8 *pnGreen = vGreen.GetBuffer();
	SDICOS::S_UINT8 *pnBlue = vBlue.GetBuffer();
	SDICOS::S_UINT8 nColor(0);
	for (SDICOS::S_UINT16 nIndex(0); nIndex < nHeight; ++nIndex, ++pnRed, ++pnGreen, ++pnBlue)
	{
		//Setting RGB to (nColor, nColor/2, nColor)
		*pnRed = nColor;
		*pnGreen = nColor / 2;
		*pnBlue = nColor;

		++nColor;
	}

	SDICOS::Image2D& imgPixelData = ait.GetData();
	imgPixelData.Allocate(SDICOS::Image2D::enumUnsigned16Bit, nWidth, nHeight);

	// Pixel Data is set of indices into the Red, Green, and Blue LUT's
	SDICOS::Array2D<SDICOS::S_UINT16> &vIndexData = *imgPixelData.GetUnsigned16();

	for (SDICOS::S_UINT32 row(0); row < imgPixelData.GetHeight(); ++row)
	{
		for (SDICOS::S_UINT32 col(0); col < imgPixelData.GetWidth(); ++col)
		{
			vIndexData[row][col] = row; //Sets each column in a row to the same color
		}
	}

	SDICOS::ErrorLog errorlog;
	SDICOS::Folder aitFolder("AIT2DFiles");
	SDICOS::Filename aitFilename(aitFolder, "SimpleColorPaletteAIT2D.dcs");

	if (!ait.Write(aitFilename, errorlog, SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "Color Palette AIT2D Example unable to write DICOS File " << aitFilename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else
	{
		std::cout << "Wrote file to " << aitFilename << std::endl;
		SDICOS::AIT2D aitRead;

		SDICOS::ErrorLog errorlog;
		if (aitRead.Read(aitFilename, errorlog))
		{
			if (aitRead == ait)
			{
				std::cout << "Successfully read and compared AIT2D files" << std::endl;
				return true;
			}
			else
			{
				std::cout << "AIT2D file loaded from " << aitFilename << " does not match original." << std::endl;
				return false;
			}
		}
		else
		{
			std::cerr << "Unable to read DX file " << aitFilename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}
} /// CreateAIT2DWithColorPaletteForProcessingSimple

int main()
{
	bool bRes(true);
	bRes = CreateAIT2DForProcessingSimple() && bRes;
	bRes = CreateAIT2DWithColorPaletteForProcessingSimple() && bRes;
	return (bRes ? 0 : 1);
}
