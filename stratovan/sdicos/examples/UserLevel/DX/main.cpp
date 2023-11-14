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
/// StartCreateUserDXExamples
#include "SDICOS/DICOS.h"

///
///	Create a DX file that is intended for additional processing using the user-level API Object SDICOS::DX.
///
bool CreateDXForProcessingSimple()
{
	// Create a DX DICOS file for a Cargo Object of Inspection
	//	enumTypeCargo:		OOI Type
	//	enumProcessing:		The DICOS file is intended for further processing by ATR etc.
	//	enumOriginal:		The DX Data is original data from the acquisition source
	//	enumMonochrome2:	Indicates that low pixel values map to black.
	SDICOS::DX dx(
		SDICOS::ObjectOfInspectionModule::enumTypeCargo,
		SDICOS::DXTypes::DXSeries::enumProcessing,
		SDICOS::DXTypes::DXImage::enumOriginal,
		SDICOS::ImagePixelMacro::enumMonochrome2
	);

	SDICOS::S_UINT32 width(256), height(128);
	SDICOS::Image2D& dxData = dx.GetXRayData();
	dxData.Allocate(SDICOS::Image2D::enumUnsigned16Bit, width,height);

	// Data is in a 2D Array
	SDICOS::Array2D<SDICOS::S_UINT16> &rawData = *dxData.GetUnsigned16();

	SDICOS::S_UINT16 count(0);
	for(SDICOS::S_UINT32 row(0); row < dxData.GetHeight(); ++row) 
	{
		for(SDICOS::S_UINT32 col(0); col < dxData.GetWidth(); ++col) 
		{
			rawData[row][col] = count++;
		}
	}

	// Set other required attributes
	dx.SetKVP(1.0f);
	dx.SetImageOrientation(SDICOS::Vector3D<float>(1,0,0), SDICOS::Vector3D<float>(0,1,0));
	dx.SetImagePosition(SDICOS::Point3D<float>(0,0,1));
	dx.SetXRayTubeCurrent(2.5f);

	SDICOS::ErrorLog errorlog;
	SDICOS::Folder dxFolder("DXFiles");
	SDICOS::Filename dxFilename(dxFolder,"SimpleProcessingDX.dcs");

	if(!dx.Write(dxFilename,errorlog,SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "Simple DX Template Example unable to write DICOS File " << dxFilename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else
	{
		std::cout << "Wrote file to " << dxFilename << std::endl;
		SDICOS::DX dxRead;
				
		SDICOS::ErrorLog errorlog;
		if(dxRead.Read(dxFilename,errorlog)) 
		{
			if(dxRead == dx) 
			{
				std::cout << "Successfully read and compared DX files" << std::endl;
				return true;
			} 
			else 
			{
				std::cout << "DX file loaded from " << dxFilename << " does not match original." << std::endl;
				return false;
			}
		} 
		else 
		{
			std::cerr << "Unable to read DX file " << dxFilename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}
} /// EndCreateDXForProcessingSimple

///
/// Create a DX file intended for viewing.
/// DX Files for viewing require LUT information.
///
bool CreateDXForPresentationSimple()
{
	// Create a DX DICOS file for a Cargo Object of Inspection
	//	enumTypeBioSample:	OOI Type
	//	enumPresentation:	The DICOS file is intended for presentation at a viewing station
	//	enumOriginal:		The DX Data is original data from the acquisition source
	//	enumMonochrome2:	Indicates that low pixel values map to black.
	SDICOS::DX dx(
		SDICOS::ObjectOfInspectionModule::enumTypeBioSample,
		SDICOS::DXTypes::DXSeries::enumPresentation,
		SDICOS::DXTypes::DXImage::enumOriginal,
		SDICOS::ImagePixelMacro::enumMonochrome2
	);

	SDICOS::S_UINT32 width(256), height(128);
	SDICOS::Image2D& dxData = dx.GetXRayData();
	dxData.Allocate(SDICOS::Image2D::enumUnsigned16Bit,width,height);

	// Data is in a 2D Array
	SDICOS::Array2D<SDICOS::S_UINT16> &rawData = *dxData.GetUnsigned16();

	SDICOS::S_UINT16 count(0);
	for(SDICOS::S_UINT32 row(0); row < dxData.GetHeight(); ++row) 
	{
		for(SDICOS::S_UINT32 col(0); col < dxData.GetWidth(); ++col) 
		{
			rawData[row][col] = count++;
		}
	}
		
	// DX Files for presentation require a LUT.
	// The example code demonstrates two ways to specify the LUT but only one is required.

	// LUT setup using Window Center and Width to define a linear transformation.
	// The input range [734,1734] 
	dx.SetWindowCenterAndWidth(1234, 500);
		
	float windowCenter,windowWidth;
	dx.GetWindowCenterAndWidth(windowCenter,windowWidth);
	std::cout << "Center and Width " << windowCenter << " " << windowWidth << std::endl;
		
	// The explanation is optional
	dx.SetWindowCenterAndWidthExplanation("Window Center and Width for test screen");
		
	// LUT Setup using an array of values
	SDICOS::VoiLut::UnsignedLUT lut;
	SDICOS::S_UINT32 lutSize = 512;
	SDICOS::S_UINT16 lutMinValue = 1000;
	lut.SetSize(lutSize);
	for(unsigned int i(0); i < lutSize; ++i) 
	{
		// made up LUT function for example purposes.
		lut[i] = lutMinValue + (unsigned int)(sqrt(float(i)));
	}
	
	// The LUT maps values in the input range [firstValueMapped, firstValueMaped+lutSize]
	// to output range starting a lutMinValue.
	// Values below firstValueMapped map to lutMinValue.
	// Values above (firstValueMapped+lutSize) map to the last value in the lut.
	SDICOS::S_UINT16 firstValueMapped = 2000;
	dx.SetLUTData(lut,firstValueMapped);

	// Set other required attributes
	dx.SetKVP(1.0f);
	dx.SetImageOrientation(SDICOS::Vector3D<float>(1,0,0), SDICOS::Vector3D<float>(0,1,0));
	dx.SetImagePosition(SDICOS::Point3D<float>(0,0,1));
	dx.SetXRayTubeCurrent(2.5f);

	SDICOS::ErrorLog errorlog;
	SDICOS::Folder dxFolder("DXFiles");
	SDICOS::Filename dxFilename(dxFolder,"SimplePresentationDX.dcs");

	if(!dx.Write(dxFilename,errorlog))
	{
		std::cerr << "Simple DX Template Example unable to write DICOS File " << dxFilename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else
	{
		std::cout << "Wrote file to " << dxFilename << std::endl;
		SDICOS::DX dxRead;
				
		SDICOS::ErrorLog errorlog;
		if(dxRead.Read(dxFilename,errorlog)) 
		{
			if(dxRead == dx) 
			{
				std::cout << "Successfully read and compared DX files" << std::endl;
				return true;
			} 
			else 
			{
				std::cout << "DX file loaded from " << dxFilename << " does not match original." << std::endl;
				return false;
			}
		} 
		else 
		{
			std::cerr << "Unable to read DX file " << dxFilename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}
	return true;
} /// EndCreateDXForPresentationSimple


  ///
  ///	Create a DX file using a color palette that is intended for additional processing using the user-level API Object SDICOS::DX.
  ///
bool CreateDXWithColorPaletteForProcessingSimple()
{
	// Create a DX DICOS file for a Cargo Object of Inspection
	//	enumTypeCargo:		OOI Type
	//	enumProcessing:		The DICOS file is intended for further processing by ATR etc.
	//	enumOriginal:		The DX Data is original data from the acquisition source
	//	enumPaletteColor:	Indicates that the a color palette is used.
	SDICOS::DX dx(
		SDICOS::ObjectOfInspectionModule::enumTypeCargo,
		SDICOS::DXTypes::DXSeries::enumProcessing,
		SDICOS::DXTypes::DXImage::enumOriginal,
		SDICOS::ImagePixelMacro::enumPaletteColor);

	// Identity: Low to high values represent dark to light
	// Inverse: Low to high values represent light to dark
	if (!dx.SetPresentationLUTShape(SDICOS::GeneralImageModule::enumIdentity))
	{
		std::cout << "Invalid Presentation LUT Shape" << std::endl;
		return false;
	}

	//Dimensions of image
	const SDICOS::S_UINT32 nWidth(256), nHeight(128);

	//Set up Red, Green, and Blue color palette
	//These values are indexed into by the Pixel Data values
	SDICOS::Array1D<SDICOS::S_UINT8> &vRed = dx.GetRedLUT();
	SDICOS::Array1D<SDICOS::S_UINT8> &vGreen = dx.GetGreenLUT();
	SDICOS::Array1D<SDICOS::S_UINT8> &vBlue = dx.GetBlueLUT();

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
		*pnGreen = nColor/2;
		*pnBlue = nColor;

		++nColor;
	}

	SDICOS::Image2D& imgPixelData = dx.GetXRayData();
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

	// Set other required attributes
	dx.SetKVP(1.0f);
	dx.SetImageOrientation(SDICOS::Vector3D<float>(1,0,0), SDICOS::Vector3D<float>(0,1,0));
	dx.SetImagePosition(SDICOS::Point3D<float>(0,0,1));
	dx.SetXRayTubeCurrent(2.5f);

	SDICOS::ErrorLog errorlog;
	SDICOS::Folder dxFolder("DXFiles");
	SDICOS::Filename dxFilename(dxFolder, "SimpleColorPaletteDX.dcs");

	if (!dx.Write(dxFilename, errorlog, SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "Color Palette DX Example unable to write DICOS File " << dxFilename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else
	{
		std::cout << "Wrote file to " << dxFilename << std::endl;
		SDICOS::DX dxRead;

		SDICOS::ErrorLog errorlog;
		if (dxRead.Read(dxFilename, errorlog))
		{
			if (dxRead == dx)
			{
				std::cout << "Successfully read and compared DX files" << std::endl;
				return true;
			}
			else
			{
				std::cout << "DX file loaded from " << dxFilename << " does not match original." << std::endl;
				return false;
			}
		}
		else
		{
			std::cerr << "Unable to read DX file " << dxFilename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}
} /// EndCreateDXWithColorPaletteForProcessingSimple

#include "SDICOS/DICOS.h"

int main()
{
    bool b = CreateDXForProcessingSimple();
	b = CreateDXForPresentationSimple() && b;
	b = CreateDXWithColorPaletteForProcessingSimple() && b;
    return (b ? 0 : 1);
}

/// EndCreateUserDXExamples
