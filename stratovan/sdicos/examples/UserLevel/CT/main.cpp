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
#include "SDICOS/DICOS.h"

bool SetObjectOfInspection(SDICOS::CT& ct);
bool SetAcquisitionDeviceInformation(SDICOS::CT& ct);
bool VerifyWrittenDICOSFiles(
	const SDICOS::CT& originalCT, const SDICOS::Folder& ctFolder, const SDICOS::Filename& ctFilename
);

// Fill the CT object with a set of volumetric shapes
void GenerateCTSection(SDICOS::CT& ct);

/**
 * This example uses the User Level API to create a CT file.
 * The CT has a single volume section.
 * @return true/false
 */
bool CreateCTSimple()
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
		std::cout << "UserCTExample CreateCTSimple failed to verify slice count using iterator. " << bRes << std::endl;
		return false;
	}

    // Fill the CT Section data with shapes and set all relevant information
	// including dimensions, spacing etc.  Resets number of sections to 1 and 
	// sets the dimensions of the volume to (256, 256, 256).
    GenerateCTSection(ct);

	SDICOS::S_UINT32 totalSliceCount(ct.GetSectionByIndex(0)->GetDepth()); // set in GenerateCTSection()
		
	SDICOS::Array3DLarge<SDICOS::S_UINT16> vUnsigned16bitData(10, 20, 40, SDICOS::MemoryPolicy::OWNS_SLICES);
	vUnsigned16bitData.Zero(0xbeef);
				
	// Add another section to the CT volume from an existing 3D array
	// and indicate that ownership of the slice data belongs to the original volume not the new Section.
	// the slice data is deleted when 'vUnsigned16bitData' goes out of scope.
	{
		SDICOS::Section* pSection2 = ct.AddSection(vUnsigned16bitData, SDICOS::MemoryPolicy::DOES_NOT_OWN_SLICES);
		bRes = (NULL != pSection2 && bRes);
		totalSliceCount += pSection2->GetDepth();
	}

	// Iterators can be used to visit each section in a CT
	SDICOS::CT::Iterator sectionIt = ct.Begin();
	SDICOS::S_UINT32 sectionCount(0);
	for( sliceCount = 0; sectionIt != ct.End(); ++sectionIt, ++sectionCount)
	{
		SDICOS::Section * pSection = (*sectionIt);

		//SDICOS::Volume::GetPixelDataType() returns an enumeration to identify the stored data type

		if(SDICOS::Volume::enumUnsigned8Bit == (*sectionIt)->GetPixelDataType())
		{
			for(volumeIterator = (*sectionIt)->GetPixelData().Begin() ; (volumeIterator != (*sectionIt)->GetPixelData().End()); ++volumeIterator, ++sliceCount)
			{
				bRes = (NULL != volumeIterator.AsUnsigned8()) && bRes;
			}
		}
		else if (SDICOS::Volume::enumSigned8Bit == (*sectionIt)->GetPixelDataType())
		{
			for(volumeIterator = (*sectionIt)->GetPixelData().Begin() ; (volumeIterator != (*sectionIt)->GetPixelData().End()); ++volumeIterator, ++sliceCount)
			{
				bRes = (NULL != volumeIterator.AsSigned8()) && bRes;
			}
		}
		else if(SDICOS::Volume::enumUnsigned16Bit == (*sectionIt)->GetPixelDataType())
		{
			for(volumeIterator = (*sectionIt)->GetPixelData().Begin() ; (volumeIterator != (*sectionIt)->GetPixelData().End()); ++volumeIterator, ++sliceCount)
			{
				bRes = (NULL != volumeIterator.AsUnsigned16()) && bRes;
			}
		}
		else if (SDICOS::Volume::enumSigned16Bit == (*sectionIt)->GetPixelDataType())
		{
			for(volumeIterator = (*sectionIt)->GetPixelData().Begin() ; (volumeIterator != (*sectionIt)->GetPixelData().End()); ++volumeIterator, ++sliceCount)
			{
				bRes = (NULL != volumeIterator.AsSigned16()) && bRes;
			}
		}
		else if (SDICOS::Volume::enumUnsigned32Bit == (*sectionIt)->GetPixelDataType())
		{
			for(volumeIterator = (*sectionIt)->GetPixelData().Begin() ; (volumeIterator != (*sectionIt)->GetPixelData().End()); ++volumeIterator, ++sliceCount)
			{
				bRes = (NULL != volumeIterator.AsUnsigned32()) && bRes;
			}
		}
		else if (SDICOS::Volume::enumSigned32Bit == (*sectionIt)->GetPixelDataType())
		{
			for(volumeIterator = (*sectionIt)->GetPixelData().Begin() ; (volumeIterator != (*sectionIt)->GetPixelData().End()); ++volumeIterator, ++sliceCount)
			{
				bRes = (NULL != volumeIterator.AsSigned32()) && bRes;
			}
		}
		else if (SDICOS::Volume::enumUnsigned64Bit == (*sectionIt)->GetPixelDataType())
		{
			for(volumeIterator = (*sectionIt)->GetPixelData().Begin() ; (volumeIterator != (*sectionIt)->GetPixelData().End()); ++volumeIterator, ++sliceCount)
			{
				bRes = (NULL != volumeIterator.AsUnsigned64()) && bRes;
			}
		}
		else if (SDICOS::Volume::enumSigned64Bit == (*sectionIt)->GetPixelDataType())
		{
			for(volumeIterator = (*sectionIt)->GetPixelData().Begin() ; (volumeIterator != (*sectionIt)->GetPixelData().End()); ++volumeIterator, ++sliceCount)
			{
				bRes = (NULL != volumeIterator.AsSigned64()) && bRes;
			}
		}
		else if (SDICOS::Volume::enumFloat== (*sectionIt)->GetPixelDataType())
		{
			for(volumeIterator = (*sectionIt)->GetPixelData().Begin() ; (volumeIterator != (*sectionIt)->GetPixelData().End()); ++volumeIterator, ++sliceCount)
			{
				bRes = (NULL != volumeIterator.AsFloat()) && bRes;
			}
		}
	}

	bRes = (0 != sectionCount) && bRes;

	if(sectionCount != 2 || (sliceCount != totalSliceCount))
	{
		std::cout << "UserCTExample CreateCTSimple failed to verify sections and slices using iterator." << sliceCount << " " << totalSliceCount << std::endl;
		return false;
	}

		
	SDICOS::ErrorLog errorlog;
	SDICOS::Folder ctFolder("CTUserAPI/SimpleCT");
	SDICOS::Filename ctFilename(ctFolder,"SimpleCT.dcs");
	
	// Two separate files will be created in the output folder because all sections in the CT do
	// not have equal width and height volume data.
	if(!ct.Write(ctFilename,errorlog,SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "Simple CT Template Example unable to write DICOS File " << ctFilename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else 
	{
		std::cout << "Simple CT Example wrote DICOS file " << ctFilename << std::endl;
		
		//
		// Use DicosFileListing object to get all DICOS files in the folder.
		// for a CT with a single section use this read method:
		// ctRead.Read(ctFilename,errorlog)
		//
		SDICOS::DicosFileListing files;
		SDICOS::Array1D<std::pair<SDICOS::Filename, SDICOS::ErrorLog> > vErrorLogs;
		bRes = files.FindDicosFiles(ctFolder,false,vErrorLogs)&& bRes;

		// Access files by ObjectOfInspection->Scan->Series
		const SDICOS::DicosFileListing::SopInstance& fileInstance = files[0][0][0][0];
	
		SDICOS::CT ctRead;
		if(ctRead.Read(fileInstance,vErrorLogs))
		{
			if(ct != ctRead) 
			{
				std::cerr << "Original CT and read CT are not equal" <<std::endl;
				return false;
			} 
			else
				std::cerr <<"Simple CT Example original CT and read CT are equal. Number of Sections: " << ctRead.GetNumberOfSections() << std::endl;
		}
		else 
		{
			std::cerr << "Failed to read CT Series from " << ctFilename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}
	
	return true;
} /// EndCreateCTTemplateSimple

/// StartCreateCTTemplateComplex
#include "SDICOS/DICOS.h"

// Dimension of the three sections added below
static const SDICOS::S_UINT32 sectionDims[][3] = { {128,128,50}, {128,128,25}, {64,64,100} };

// Example Data. In an application, the user is responsible for getting this information.
// The spacing for Sections 0 and 1 are the same since they are part of the same volume.
// The spacing for Section 2 is different.
//
// Section Spacing is the Physical Distance in the OOI between pixel centers. Measured in MM.
//	The values are ordered as follows:
//		Distance in MM between pixel centers of two adjacent columns
//		Distance in MM between pixel centers of two adjacent rows
//		Distance in MM between pixel centers of two adjacent slices
//	
static const SDICOS::S_UINT32 SectionSpacingColumnIndex(0);
static const SDICOS::S_UINT32 SectionSpacingRowIndex(1);
static const SDICOS::S_UINT32 SectionSpacingSliceIndex(2);

static const float sectionSpacing[][3] = { {5.0f,2.5f,10.0f}, {5.0f,2.5f,10.0f}, {1.0f,1.5f,2.5f} };

// In this example, Section 0 position is the initial scan position (0,0,0)
// as an object moves along through the scanner the position of the new slice is in the negative Z direction.
// The position for Section 1 starts at -500 (50 slices from Section 0 times 10 MM spacing)
// The position for Section 2 starts at -5000 (100 slices from Section 0 times 2.5 MM spacing)
static const float position[][3] = { {0,0,0.0f}, {0, 0, -500.0f}, {23, 34, -5000} };

///
/// This example demonstrates the User Level API to create a CT DICOS file
/// with multiple volume sections that are saved as multiple DICOS files.
///
bool CreateCTComplex()
{
	///
	/// The SDICOS::CT object abstracts away the hierarchy of the DICOS specification
	/// into a single API that contains methods for setting all of the attributes needed
	/// for a DICOS CT object.
	///
	/// The SDICOS::CT object represents a single Series in a Scan
	/// in an Object of Inspection (OOI).
	///
	/// Note that the Scan may contain multiple Series represented by 
	/// different CT instances and that the OOI may contain multiple scans.
	///
	SDICOS::CT ct;

	//
	// Where applicable, class methods in the Stratovan DICOS library return true/false to indicate success failure.
	// In this example the return values of various methods are tested for success/failure but this is not a requirement for usage.
	//
	bool bRes(true);
	
	//
	//	Set CT attributes in the order that they are defined by the DICOS specification
	// for the CT Information Object Definition (IOD)
	//
	
	//
	// Set Object of Inspection (OOI) Attributes)
	// 
	bRes = SetObjectOfInspection(ct) && bRes;
	
	//
	// Set Scan Module attributes. A Scan is a collection of one or more series of 
	// security objects grouped together to identify a theat.
	// Each Scan is associated with one Object of Interest (OOI)
	//
	
	// Set the UID to identity the Scan instance that the Series belongs to.
	// If the Series is one of many in a Scan, this UID should be passed in to the
	// user of the CTSeriesBase class. If not is can be auto-generated by calling
	// the method CTSeroesBase::GenerateScanInstanceUID()
	//
	// A UID is a series of numeric components separated by the period "."
	ct.SetScanInstanceUID("1.2.3.4.5");
	
	// Set the time and date that the Scan started
	bRes = ct.SetScanStartDateAndTime(SDICOS::DcsDate::Today(),SDICOS::DcsTime::Now()) && bRes;
	bRes = ct.SetScanType(SDICOS::GeneralScanModule::enumOperational) && bRes;
	
	// The Scan ID attribute is a human-readable ID for identifying the scan in a local context
	bRes = ct.SetScanID("001") && bRes;
	
	//
	// Set Series Module attributes. The CTSeriesBase object represents a single
	// Series in the Scann.
	// Note: The CT object forces the Series Modality attribute to "CT"
	//
	
	// A UID is a series of numeric components separated by the period "."
	bRes = ct.SetSeriesInstanceUID(SDICOS::DcsUniqueIdentifier::CreateGUID());
	
	// Set the date and time that this series started
	bRes = ct.SetSeriesDateAndTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()) && bRes;
	bRes = ct.SetSeriesAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful) && bRes;
	
	bRes = SetAcquisitionDeviceInformation(ct) && bRes;
	
	// Unique Identifier for this Service Object Pair (SOP) Instance
	// In this example, the UID is set from a user supplied string.
	SDICOS::DcsUniqueIdentifier strInstanceUID("1.2.3.4");
	bRes = ct.SetSopInstanceUID(strInstanceUID) && bRes;

	// The Frame of Reference UID is used to uniquely identify a frame of reference for the images within a series 
	// or across multiple series in the same scan.
	// Images that shared a Frame of Reference UID are spatially related.
	// For this example, a random UID is simply generated. However, if multiple series share a Frame of Reference
	// then this UID needs to match across them.
	ct.GenerateFrameOfReferenceUID();
	
	//
	// Set information about how the image data was gathered by the device.
	//
	// The Date and Time that data acquisition started
	bRes = ct.SetImageAcquisitionDateAndTime(SDICOS::DcsDate(2014,12,3), SDICOS::DcsTime(22,23,4,0)) && bRes;
	
	// Indicates whether or not the image contains sufficient burned in annotation 
	// to identify the OOI and date the image was acquired.
	// This could be "text" included as part of the CT data to identify objects or orientation.
	// This value is set to false by default.
	ct.SetBurnedInAnnotation(false);
	
	// Intended interpretation of pixel data.
	// For CT these are:
	//		enumMonochrome1		"MONOCHROME1", Minimum pixel value is white
	//		enumMonochrome2		"MONOCHROME2", Minimum pixel value is black
	bRes = ct.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome1) && bRes;
	
	// Information about the image and volume data
	bRes = ct.SetImageType(SDICOS::CTTypes::CTImage::enumHighEnergy,SDICOS::CTTypes::CTImage::enumVolume) && bRes;
	
	// Acquisition Duration in Seconds
	bRes = ct.SetImageAcquisitionDuration(1.414) && bRes;
	
	// The time and date the Data Creation was start.
	// Note: this is the time pixel data was created not the time the data was
	// acquired by the scanning device.
	bRes = ct.SetContentDateAndTime(SDICOS::DcsDate::Today(),SDICOS::DcsTime::Now()) && bRes;
	
	// The Instance Number is another means for the user to identify this CT Series
	// The default value is 0.
	ct.SetInstanceNumber(4251);
		
	//
	// The CT object represents a single Series in a Scan that can contain multiple Series.
	// The volume data for a single Series can be contained in multiple,related volumes called Sections.
	// Sections are independently allocated and can be manipulated in parallel.
	// The two types of Sections are called related and independent.
	//
	// Note that in a typical deployed DICOS application, the CT Series will not be written to disk 
	// but will be written to another DICOS device either through a network connection or through
	// shared memory.
	//
	
	//
	// Related Sections:
	//	For CT Data, a larger volume can be broken down into smaller sections along the Z-direction (Depth).
	//	These sections must share the same Width(W), Height(H).
	//	For example a 512x512x512 (WxHxD) volume can be broken down into three Sections
	//	of dimensions 512x512x100, 512x512x200 and 512x512x212.
	//
	//	The data can be set for these Sections independently, but when the CT data is written to a file
	//	the related sections are combined into a single volume and the original Sections are not
	//	restored when they are read back in.
	//
	
	//
	// Independent Sections:
	//	Independent sections cannot be combined to form a larger volume. These are
	//	Sections that have different dimensions, spacing or location.
	//	Independent Sections are saved to separate DICOS files.
	//
	//	For example, for a particular OOI and Scan, a Series could have a normal
	//	resolution CT volume for the whole OOI and a small higher-resolution volume
	//	for a sub-volume that is of particular interest.
	//	These are stored as independent sections.
	//
	SDICOS::Section * pSection = NULL;
	
	// 
	// This example illustrates a CT with two related sections and one independent section with different dimensions and spacing.
	// The two related sections,which shared X,Y dimensions and X,Y,X spacing are 128x128x50 and 128x128x25. Together they form a 
	// 128x128x75 volume in a single file, but remain separate sections due to positioning. The independent section is 64x64x100 
	// and has different spacing and is placed in a separate file.
	//
	ct.SetNumberOfSections(3);
	
	for(SDICOS::S_UINT32 i = 0; i < 3; ++i)
	{
		pSection = ct.GetSectionByIndex(i);
		
		// Set data common to all Sections of the volume
		// See documentation above where sectionSpacing array pSection defined for the meaning of these values.
		pSection->SetSpacingInMM(sectionSpacing[i][SectionSpacingColumnIndex],sectionSpacing[i][SectionSpacingRowIndex],sectionSpacing[i][SectionSpacingSliceIndex]);
		pSection->SetPositionInMM(position[i][0],position[i][1],position[i][2]);

		// Set slicing direction for slices in the volume data
		// true: (Default) slicing direction is in the row X column direction
		// false: slicing direction is in the -(row X column) direction
		pSection->SetSlicingDirection(true);

		// Set image orientation based on the top left of each slice
		// Pixel row along X-Axis (left-to-right)
		// Pixel column along Y-Axis (top-to-bottom)
		const SDICOS::Vector3D<float> vecRow(1, 0, 0);
		const SDICOS::Vector3D<float> vecColumn(0, 1, 0);
		pSection->SetPlaneOrientation(vecRow, vecColumn);

		// Set Data specific to CT Scans
		pSection->SetImagePixelPresentation(SDICOS::CommonImageDescription::enumPP_Monochrome);
		pSection->SetImageVolumeBasedCalculationTechnique(SDICOS::CommonImageDescription::enumVC_None);
		pSection->SetImageVolumetricProperties(SDICOS::CommonImageDescription::enumVP_Volume);
		
		// Set parameters to transform stored pixel data
		pSection->SetRescaleSlope(1.0f);
		pSection->SetRescaleIntercept(0.0f);
		pSection->SetRescaleType("HU");	// Set the units used by pixel data after applying rescaling
		
		// X-Ray absorbing material in the filter
		pSection->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumMixed);
		
		// Type of filter inserted into the XRay beam
		// Wedge, Butterfly, Multiple, Flat, Shaped, None
		pSection->SetFilterType(SDICOS::CTTypes::CTXRayDetails::enumFlat);
		
		// Used nominal size of the focal spot in MM.
		pSection->SetFocalSpotSizeInMM(5);
		
		// Peak kilo voltage output of the x-ray generator
		pSection->SetKVP(100.1f);
	}

	//
	//	Set the Volume data associated with each of the Sections.
	// See Examples/VolumeDataExample for more information about working with volumes.
	//
	SDICOS::Volume& v0 = ct.GetSectionByIndex(0)->GetPixelData();
	v0.Allocate(SDICOS::Volume::enumUnsigned16Bit);

	SDICOS::Array3DLarge<SDICOS::S_UINT16> &v0Data = *v0.GetUnsigned16();
	v0Data.SetSize(sectionDims[0][0],sectionDims[0][1],sectionDims[0][2]);
	
	// Set volume data by setting each XY plane
	// See the example file Examples/VolumeDataExample/VolumeDataExample.cpp
	for(SDICOS::S_UINT32 i = 0; i < v0Data.GetDepth(); ++i) 
	{
		SDICOS::Array2D<SDICOS::S_UINT16>& xyPlane = v0Data[i];
		SDICOS::S_UINT16 * pBuffer = xyPlane.GetBuffer();
		
		// The user can copy their data into pBuffer from another source or place it directly in pBuffer.
		memset(pBuffer, 0, sizeof(SDICOS::S_UINT16)*xyPlane.GetWidth()*xyPlane.GetHeight());
	}
	
	//
	//	Set the Volume data associated with each of the Sections.
	//
	SDICOS::Volume& v1 = ct.GetSectionByIndex(1)->GetPixelData();
	v1.Allocate(SDICOS::Volume::enumUnsigned16Bit, sectionDims[1][0],sectionDims[1][1],sectionDims[1][2]);
	
	SDICOS::Volume& v2 = ct.GetSectionByIndex(2)->GetPixelData();
	v2.Allocate(SDICOS::Volume::enumUnsigned16Bit, sectionDims[2][0],sectionDims[2][1],sectionDims[2][2]);

	//
	// Iterators can be used to loop over the Sections in a SDICOS::CT object
	//
	
	SDICOS::S_UINT32 numSections(0);
	SDICOS::CT::Iterator CTIterator = ct.Begin();
	for(; CTIterator != ct.End(); ++CTIterator, ++numSections)
	{
		SDICOS::Section *pCurSection = (*CTIterator);
				
		// For this example lets check that data is set correctly from the previous loop
		bRes = (pCurSection->GetFilterMaterial() == SDICOS::CTTypes::CTXRayDetails::enumMixed) && bRes;
				
				
		//
		// An iterator can be used to visit each slice of a volume. For more details see the Examples/VolumeDataExample Folder
		//
		SDICOS::Volume::SliceIterator volumeIterator = pCurSection->GetPixelData().Begin();
		SDICOS::S_UINT32 sliceCount(0);
		for(; volumeIterator != pCurSection->GetPixelData().End(); ++volumeIterator, ++sliceCount)
		{
			// Perform an operation on each slice and zero the data.
			volumeIterator.AsUnsigned16()->Zero((numSections + sliceCount));
		}

		if(sectionDims[numSections][2] != sliceCount)
		{
			std::cout << "UserCTExample failed to verify slice count using iterator." << std::endl;
		}
	}
		
	if((3 != numSections) || !bRes)
	{
		std::cout << "UserCTExample iteration over sections failed. Num Sections " << numSections << " Test Result " << bRes << std::endl;
	} 
	else
	{
		std::cout << "UserCTExample iteration over sections succeeded. Num Sections " << numSections << std::endl;
	}
		
		
	//
	// The SDICOS::ErrorLog class stores errors and warnings generated during the 
	// reading and writing of DICOS files.
	//
	// They are organized by DICOS Tag and include the entire DICOS tag path from the 
	// top-level module (e.g. CT IOD) to the attribute itself.
	// 
	SDICOS::ErrorLog errorlog;

	// Create a path to a file system folder 
	SDICOS::Folder ctFolder("CTUserAPI/CTComplex");
	
	// Create a filename in a specific folder
	// The two DICOS files generated (one for each independent section) are:
	//		CTTemplateFiles/CTComplex0000
	//		CTTemplateFiles/CTComplex0001
	SDICOS::Filename ctFilename(ctFolder,"CTComplex.dcs");
	
	std::cout << "Number of Sections: " << ct.GetNumberOfSections() << std::endl << "Number of Files to Create: " << ct.GetNumberOfFilesToCreate() << std::endl;
	
	if(2 != ct.GetNumberOfFilesToCreate()) 
	{
		std::cerr << "Number of files to create does not match. Expected: 2 Got: " << ct.GetNumberOfFilesToCreate() << std::endl;
	}
	
	//
	// Write the CT object to a file using the indicated transfer syntax and
	// log errors and warnings in the given ErrorLog object.
	//
	if(!ct.Write(ctFilename,errorlog,SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "CT Template Example unable to write DICOS File " << ctFilename << std::endl;
		
		// The SDICOS::ErrorLog supports operator<<
		std::cerr << errorlog << std::endl;
		return false;
	}
	else
	{
		bRes = VerifyWrittenDICOSFiles(ct,ctFolder,ctFilename) && bRes;
	}
	return bRes;
} // EndCreateCTTemplateComplex

int main()
{
	bool b = CreateCTComplex();
	b = CreateCTSimple() && b;
	return (b ? 0 : 1);
}

bool SetObjectOfInspection(SDICOS::CT& ct)
{
	// The Object of Inspection (OOI) ID is the 
	// primary airport identification number or code for identifying an OOI.
	// It can be generated by the scanning device.
	bool bRes = ct.SetOOIID("123456789");
	
	// Identifier of the Assigning Authority that issues the above ID
	bRes = ct.SetOOIIDAssigningAuthority("SFO") && bRes;
	
	// What type of identifier is the ID? Text, RFID, Barcode etc.
	bRes = ct.SetOOIIDType(SDICOS::ObjectOfInspectionModule::IdInfo::enumText) && bRes;
	
	// What type of object is this?
	bRes = ct.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage) && bRes;
	return bRes;
}

bool SetAcquisitionDeviceInformation(SDICOS::CT& ct)
{
	//
	// Set information about the acquisition device
	//
	SDICOS::DcsDate calibrationDate(2013,1,31);
	SDICOS::DcsTime calibrationTime(19,23,2,12344);
	bool bRes = ct.SetDeviceCalibrationDateAndTime(calibrationDate,calibrationTime);
	
	bRes = ct.SetDeviceSerialNumber(SDICOS::DcsLongString("3.14")) && bRes;
	bRes = ct.SetMachineAddress("202 Cousteau Way Suite 108") && bRes;	// Physical Address
	bRes = ct.SetMachineLocation(SDICOS::DcsLongString("Secure Room")) && bRes;
	bRes = ct.SetMachineID("Stratovan 1") && bRes;
	bRes = ct.SetDeviceManufacturer("French Bulldog") && bRes;
	bRes = ct.SetDeviceManufacturerModelName("Daisy-Jones-1") && bRes;
	bRes = ct.SetDeviceSoftwareVersion("1.1.0") && bRes;
	bRes = ct.SetSopInstanceCreationDateAndTime(SDICOS::DcsDate::Today(),SDICOS::DcsTime::Now()) && bRes;
	return bRes;
}

bool VerifyWrittenDICOSFiles(
	const SDICOS::CT& originalCT, 
	const SDICOS::Folder& ctFolder, 
	const SDICOS::Filename& ctFilename
)
{
	bool bRes(true);
	
	std::cout << "Write CT DICOS file from template " << ctFilename << " " << originalCT.GetNumberOfFilesToCreate() << std::endl;

	//
	// The SDICOS::DicosFileListing class searches and collects all DICOS files
	// in a file system folder and hierarchy.  Any files DICOS files excluded from
	// the listing due to errors will populate the 'vErrorLog' parameter.
	//
	SDICOS::DicosFileListing files;
	SDICOS::Array1D<std::pair<SDICOS::Filename, SDICOS::ErrorLog> > vErrorLog;
	files.FindDicosFiles(ctFolder,false,vErrorLog);

	if(	0 == files.GetNumberOfObjectOfInspections() ||
		0 == files[0].GetNumberOfScans() ||
		0 == files[0][0].GetNumberOfSeries())
	{
		std::cerr << "Unable to find DICOS files for CT Template" << std::endl;
		return false;
	}

	//
	// In this example, the SDICOS::DicosFileListing object is used to find the 
	// files generated for each independent CT Section added to the CT Series.
	// There are two files generated in this example.
	//
	SDICOS::Array1D<SDICOS::DicosFileListing::FileInfo> filenames;
	files.GetFileInfo(filenames);

	for(SDICOS::S_UINT32 i = 0; i < filenames.GetSize(); ++i) 
	{
		std::cout << filenames[i].m_filename << std::endl;
	}

	// One error log is created for each Section in the Series
	SDICOS::Array1D< std::pair<SDICOS::Filename, SDICOS::ErrorLog> > vErrorlogs;
	SDICOS::CT ctRead;

	// Access files by ObjectOfInspection->Scan->Series
	const SDICOS::DicosFileListing::SopInstance& fileInstance = files[0][0][0][0];

	// Read the CT Data for the Series
	if(!ctRead.Read(fileInstance, vErrorlogs))
	{
		std::cerr << "Unable to read CT DICOS files" << std::endl;
		for(SDICOS::S_UINT32 i = 0; i < vErrorlogs.GetSize(); ++i) 
		{
			std::cerr << vErrorlogs[i].first << std::endl << vErrorlogs[i].second << std::endl;
		}

		return false;
	} 

	const SDICOS::S_UINT32 nNumSections(3);
	std::cout << "Loaded CT DICOS Files. Number of Sections: " << ctRead.GetNumberOfSections() << std::endl;
	bRes = (nNumSections == ctRead.GetNumberOfSections()) && bRes;
	SDICOS::Section * sections[nNumSections];

	for (SDICOS::S_UINT32 n(0); n < nNumSections; ++n)
	{
		sections[n] = ctRead.GetSectionByIndex(n);
		bRes = bRes && S_NULL != sections[n];
	}

	// Check that volumes have the expected dimensions and spacing
	for(SDICOS::S_UINT32 i = 0; i < nNumSections; ++i)
	{
		bool bSectionSpacingFound(false);
		for(SDICOS::S_UINT32 j = 0; j < nNumSections; ++j)
		{
			if( SDICOS::IsEqual(sections[i]->GetColumnSpacing(),sectionSpacing[j][0]) && 
				SDICOS::IsEqual(sections[i]->GetRowSpacing(),   sectionSpacing[j][1]) &&
				SDICOS::IsEqual(sections[i]->GetSliceSpacing(), sectionSpacing[j][2])
				) 
			{
				bSectionSpacingFound = true;
				break;
			}
		}
		bRes = bSectionSpacingFound && bRes;
		bool bSectionDimsFound(false);
		for(SDICOS::S_UINT32 j = 0; j < nNumSections; ++j)
		{
			if(sections[i]->GetWidth() == sectionDims[j][0] && 
				sections[i]->GetHeight() == sectionDims[j][1] &&
				sections[i]->GetDepth() == sectionDims[j][2])
			{
				bSectionDimsFound = true;
				break;
			}
		}

		bRes = bSectionDimsFound && bRes;
	}
	std::cout << "Comparison of original and loaded CT files " << bRes << std::endl;

	return bRes;
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
