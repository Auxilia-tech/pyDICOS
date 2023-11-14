//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2022 Stratovan Corporation. All Rights Reserved.
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


// Fill the CT object with a set of volumetric shapes
void GenerateCTSection(SDICOS::CT& ct);
// Set the required CT attributes aside from SDI/CDI Data Type
bool CommonExampleCT(SDICOS::CT& ct);

/**
 * This example uses the User Level API to create a CT file.
 * The CT has a single volume section.
 * The SDI/CDI Data type is set to SDI - Sensor Data Interface
 * @return true/false
 */
bool CreateCTSimpleSDI()
{
	/// Create a CT Series for a baggage Object of Inspection (OOI)
	/// The SDICOS::CT object represents a single Series in a Scan in an OOI.
	/// All required Date and Time attributes are set to SDICOS::DcsDate::Today() and SDICOS::DcsTime::Now()
	/// CT Image Type Pixel Data Characteristics value is set to ORIGINAL
	SDICOS::CT ct(
		SDICOS::ObjectOfInspectionModule::enumTypeBaggage,
		SDICOS::CTTypes::CTImage::enumHighEnergy,	// Data is from a high-energy scan. See Examples/Multiple_Energy_CT for how to combine High and Low energy.
		SDICOS::CTTypes::CTImage::enumVolume,
		SDICOS::ImagePixelMacro::enumMonochrome2	// Minimum pixel value is black
	);

	/// Set the SDI/CDI Data type to SDI - Sensor Data Interface
	ct.SetSDI();

	/// Set the rest of the required attributes
	if(!CommonExampleCT(ct))
		return false;

	/// Verify Read/Write
	SDICOS::ErrorLog errorlog;
	SDICOS::Folder ctFolder("CTUserAPI/SimpleCTSDI");
	SDICOS::Filename ctFilename(ctFolder,"SimpleCTSDI.dcs");
	
	// Two separate files will be created in the output folder because all sections in the CT do
	// not have equal width and height volume data.
	if(!ct.Write(ctFilename,errorlog,SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "CT_CDI_SDI_Example CreateCTSimpleSDI Example unable to write DICOS File " << ctFilename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else 
	{
		std::cout << "CT_CDI_SDI_Example CreateCTSimpleSDI wrote DICOS file " << ctFilename << std::endl;
		
		//
		// Use DicosFileListing object to get all DICOS files in the folder.
		// for a CT with a single section use this read method:
		// ctRead.Read(ctFilename,errorlog)
		//
		SDICOS::DicosFileListing files;
		SDICOS::Array1D<std::pair<SDICOS::Filename, SDICOS::ErrorLog> > vErrorLogs;
		if(!files.FindDicosFiles(ctFolder,false,vErrorLogs))
			return false;

		// Access files by ObjectOfInspection->Scan->Series
		const SDICOS::DicosFileListing::SopInstance& fileInstance = files[0][0][0][0];
	
		SDICOS::CT ctRead;
		if(ctRead.Read(fileInstance,vErrorLogs))
		{
			if(ct != ctRead) 
			{
				std::cerr << "Original CT SDI and read CT are not equal" <<std::endl;
				return false;
			} 
			else
				std::cerr <<"Simple CT SDI Example original CT and read CT are equal." << std::endl;
		}
		else 
		{
			std::cerr << "Failed to read CT Series from " << ctFilename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}
	
	return true;
}

/**
 * This example uses the User Level API to create a CT file.
 * The CT has a single volume section.
 * The SDI/CDI Data type is set to CDI - Constructed/Corrected Data Interface
 * @return true/false
 */
bool CreateCTSimpleCDI()
{
	/// Create a CT Series for a baggage Object of Inspection (OOI)
	/// The SDICOS::CT object represents a single Series in a Scan in an OOI.
	/// All required Date and Time attributes are set to SDICOS::DcsDate::Today() and SDICOS::DcsTime::Now()
	/// CT Image Type Pixel Data Characteristics value is set to ORIGINAL
	SDICOS::CT ct(
		SDICOS::ObjectOfInspectionModule::enumTypeBaggage,
		SDICOS::CTTypes::CTImage::enumHighEnergy,	// Data is from a high-energy scan. See Examples/Multiple_Energy_CT for how to combine High and Low energy.
		SDICOS::CTTypes::CTImage::enumVolume,
		SDICOS::ImagePixelMacro::enumMonochrome2	// Minimum pixel value is black
	);

	/// Set the SDI/CDI Data type to CDI - Constructed/Corrected Data Interface
	ct.SetCDI();
	
	/// Set the rest of the required attributes
	if(!CommonExampleCT(ct))
		return false;

	/// Verify Read/Write 
	SDICOS::ErrorLog errorlog;
	SDICOS::Folder ctFolder("CTUserAPI/SimpleCTCDI");
	SDICOS::Filename ctFilename(ctFolder,"SimpleCTCDI.dcs");
	
	// Two separate files will be created in the output folder because all sections in the CT do
	// not have equal width and height volume data.
	if(!ct.Write(ctFilename,errorlog,SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "CT_CDI_SDI_Example CreateCTSimpleCDI Example unable to write DICOS File " << ctFilename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else 
	{
		std::cout << "CT_CDI_SDI_Example CreateCTSimpleCDI wrote DICOS file " << ctFilename << std::endl;
		
		//
		// Use DicosFileListing object to get all DICOS files in the folder.
		// for a CT with a single section use this read method:
		// ctRead.Read(ctFilename,errorlog)
		//
		SDICOS::DicosFileListing files;
		SDICOS::Array1D<std::pair<SDICOS::Filename, SDICOS::ErrorLog> > vErrorLogs;
		if(!files.FindDicosFiles(ctFolder,false,vErrorLogs))
			return false;

		// Access files by ObjectOfInspection->Scan->Series
		const SDICOS::DicosFileListing::SopInstance& fileInstance = files[0][0][0][0];
	
		SDICOS::CT ctRead;
		if(ctRead.Read(fileInstance,vErrorLogs))
		{
			if(ct != ctRead) 
			{
				std::cerr << "Original CT CDI and read CT are not equal" <<std::endl;
				return false;
			} 
			else
				std::cerr <<"Simple CT CDI Example original CT and read CT are equal." << std::endl;
		}
		else 
		{
			std::cerr << "Failed to read CT Series from " << ctFilename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}
	
	return true;
}

int main()
{
    bool b;
    b = CreateCTSimpleSDI();
    b = CreateCTSimpleCDI() && b;
	return (b ? 0 : 1);
}

void GenerateCTSection(SDICOS::CT& ct)
{
	SDICOS::Section *psection = S_NULL;

	ct.SetNumberOfSections(1);
	psection = ct.GetSectionByIndex(0);

	psection->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumAluminum);
	psection->SetFocalSpotSizeInMM(10);
	psection->SetKVP(7000);

    SDICOS::Vector3D<float> vecRowOrientation;
    SDICOS::Vector3D<float> vecColumnOrientation;

	vecRowOrientation.Set(1,0,0);		// X-Axis points right
	vecColumnOrientation.Set(0,1,0);	// Y-Axis points down
										// Z-Axis points into screen
	psection->SetPlaneOrientation(vecRowOrientation, vecColumnOrientation);

	psection->SetPositionInMM(-125,-125,125);
		
	/// Physical Distance in the OOI between pixel centers. Measured in MM.
	const float fColumnSpacing = 1.0f;		// Distance in MM between pixel centers of two adjacent columns
	const float fRowSpacing = 1.0f;		// Distance in MM between pixel centers of two adjacent rows
	const float fSliceSpacing = 1.0f;	//Distance in MM between pixel centers of to adjacent slices
	const float fSliceThickness = 1.0f;	//Thickness of each slice in MM
		
	psection->SetSpacingInMM(fColumnSpacing, fRowSpacing, fSliceSpacing);
	psection->SetSliceThickness(fSliceThickness);
	psection->GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, 256, 256, 256);
	psection->GetPixelData().GetUnsigned16()->Zero(0);

	const SDICOS::Point3D<SDICOS::S_UINT16> ptCenter(125,125,125);

	// Make shapes
	const SDICOS::S_UINT16 nWhite(0xFFFF), nGray256(0x0100), nGray2048(0x1000);
	SDICOS::Array3DLarge<SDICOS::S_UINT16> &vVolume = *psection->GetPixelData().GetUnsigned16();
	SDICOS::Point3D<SDICOS::S_UINT16> ptPos;

	// Rectangle on left-top-back(-X,-Y,+Z) corner of volume .
	// Longest on Z axis, then Y-axis, then X-axis
	SDICOS::S_UINT32 curSlice(0);
		
	for(ptPos.z = 0 ; ptPos.z < 200 ; ++ptPos.z, ++curSlice)
	{
		SDICOS::Array2D<SDICOS::S_UINT16>* pSlice = vVolume.GetSlice(curSlice);
		for(ptPos.y = 0 ; ptPos.y < 20 ; ++ptPos.y)
		{
			SDICOS::S_UINT16 *pvoxel = pSlice->GetBuffer() + (ptPos.y * pSlice->GetWidth());
			for(ptPos.x = 0 ; ptPos.x < 50 ; ++ptPos.x, ++pvoxel)
				*pvoxel = nWhite;
		}
	}

	// Center block
	for(curSlice = 0, ptPos.z = (ptCenter.z-40) ; ptPos.z < (ptCenter.z+40) ; ++ptPos.z, ++curSlice)
	{
		SDICOS::Array2D<SDICOS::S_UINT16>* pSlice = vVolume.GetSlice(curSlice);
		for(ptPos.y = (ptCenter.y-40); ptPos.y < (ptCenter.y+40) ; ++ptPos.y)
		{
			ptPos.x = (ptCenter.x-40);
			SDICOS::S_UINT16 *pvoxel = pSlice->GetBuffer() + (ptPos.y * pSlice->GetWidth()) + ptPos.x;
			for(; ptPos.x < (ptCenter.x+40) ; ++ptPos.x, ++pvoxel)
				*pvoxel = nGray256;
		}
	}

	// Small block to the right (+X) of the center block
	for(curSlice = 0, ptPos.z = (ptCenter.z-5) ; ptPos.z < (ptCenter.z+5) ; ++ptPos.z, ++curSlice)
	{
		SDICOS::Array2D<SDICOS::S_UINT16>* pSlice = vVolume.GetSlice(curSlice);
		for(ptPos.y = (ptCenter.y-5); ptPos.y < (ptCenter.y+5) ; ++ptPos.y)
		{
			ptPos.x = (ptCenter.x+40);
			SDICOS::S_UINT16 *pvoxel = pSlice->GetBuffer() + (ptPos.y * pSlice->GetWidth()) + ptPos.x;
			for(; ptPos.x < (ptCenter.x+51) ; ++ptPos.x, ++pvoxel)
				*pvoxel = nGray2048;
		}
	}
}

bool CommonExampleCT(SDICOS::CT& ct)
{
	/// Set the rest of required 
	
	/// Acquisition time in seconds
	ct.SetImageAcquisitionDuration(5.2);
	
	/// Set Scan Description.
	ct.SetScanDescription("HIGH ENERGY SCAN");


	/// Add one section of volume data to the CT Series
	///		Section position at (0,0,0)
	///		XYZ voxel spacing (1,1,1)
	///		Row and Column orientation vectors are (1,0,0) and (0,1,0) by default
	///		CT Frame Type Pixel Data Characteristics value is set to ORIGINAL
	///		CT Filter Type is set to NONE. CT Filter Material is not used.
	ct.SetNumberOfSections(1);
	
	SDICOS::Section * pSection = ct.GetSectionByIndex(0);

	// Used nominal size of the focal spot in MM.
	pSection->SetFocalSpotSizeInMM(1.414f);

	// Set image orientation based on the top left of each slice
	// Pixel row along X-Axis (left-to-right)
	// Pixel column along Y-Axis (top-to-bottom)
	const SDICOS::Vector3D<float> vecRow(1, 0, 0);
	const SDICOS::Vector3D<float> vecColumn(0, 1, 0);
	pSection->SetPlaneOrientation(vecRow, vecColumn);

	// Set slicing direction for slices in the volume data
	// true: (Default) slicing direction is in the row X column direction
	// false: slicing direction is in the -(row X column) direction
	pSection->SetSlicingDirection(true);

	// Peak kilo voltage output of the x-ray generator
	pSection->SetKVP(3.14f);
		
	// NOTE: currently DICOS does not have an attribute to store the Amperage used to make the scan

	//	Set the Volume data for the CT Series section
	SDICOS::Volume& volume = pSection->GetPixelData();
	volume.Allocate(SDICOS::Volume::enumUnsigned16Bit, 128, 129, 100);
	SDICOS::Array3DLarge<SDICOS::S_UINT16>& sectionData = *volume.GetUnsigned16();
	
	SDICOS::S_UINT16 * userData = new SDICOS::S_UINT16[volume.GetWidth()*volume.GetHeight()];
	for(SDICOS::S_UINT32 i =- 0; i < volume.GetSliceSize(); ++i) 
	{
		userData[i] = i & 0xFFFF;
	}
		
	// Set volume data by setting each XY plane
	for(SDICOS::S_UINT32 i = 0; i < volume.GetDepth(); ++i)
	{
		SDICOS::Array2D<SDICOS::S_UINT16>& xyPlane = sectionData[i];
		SDICOS::S_UINT16 * pBuffer = xyPlane.GetBuffer();
		
		// The user can copy their data into pBuffer from another source or place it directly in pBuffer.
		memcpy(pBuffer, userData, sizeof(SDICOS::S_UINT16)*xyPlane.GetWidth()*xyPlane.GetHeight());
	}
		
	delete [] userData;

	//
	// An iterator can be used to visit each slice of a volume. For more details see the Examples/VolumeDataExample Folder
	//
	bool bRes(true);
	SDICOS::Volume::SliceIterator volumeIterator = volume.Begin();
	SDICOS::S_UINT32 sliceCount(0);
	for(; volumeIterator != volume.End(); ++volumeIterator, ++sliceCount)
	{
		SDICOS::Array2D<SDICOS::S_UINT16> *pCurSlice = volumeIterator.AsUnsigned16();

		// Perform an operation on each slice and zero the data.
		pCurSlice->Zero(sliceCount);

		bRes = (pCurSlice->GetWidth() == 128) && (pCurSlice->GetHeight() == 129) && bRes;
	}

	if(100 != sliceCount || !bRes)
	{
		std::cout << "CT_CDI_SDI_Example CreateCTSimpleSDI failed to verify slice count using iterator. " << bRes << std::endl;
		return false;
	}

    // Fill the CT Section data with shapes and set all relevant information
	// including dimensions, spacing etc.  Resets number of sections to 1 and 
	// sets the dimensions of the volume to (256, 256, 256).
    GenerateCTSection(ct);

	SDICOS::S_UINT32 totalSliceCount(ct.GetSectionByIndex(0)->GetDepth()); // set in GenerateCTSection()
		
	SDICOS::Array3DLarge<SDICOS::S_UINT16> vUnsigned16bitData(10, 20, 40, SDICOS::MemoryPolicy::OWNS_SLICES);
	vUnsigned16bitData.Zero(0xbeef);

	return true;
}