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

// Utility method to verify an AIT3D Series that multiple volume files in a single folder.
bool VerifyWrittenDICOSFiles(
	const SDICOS::AIT3D& original, 
	const SDICOS::Folder& aitFolder, 
	const SDICOS::Filename& aitFilename
);

/// StartCreateAIT3DSimple

/**
 * Create an AIT3D DICOS file with one volume section.
 * @return 
 */
bool CreateAIT3DSimple()
{
	/// Create an AIT3D DICOS file for a person
	/// The Object of Inspection Type (OOI) is automatically set to person
	/// The AIT Device Type is Active Millimeter Wave.
	/// The pixel photometric interpretation is Monochrome2 indicating that lower values map to lower intensities.
	/// The Image description attributes default to a monochrome volume with original data.
	///
	/// The Object of Inspection Type (OOI) is one of:
	///		enumTypeBioSample
	///		enumTypeCargo
	///		enumTypeBaggage
	///		enumTypeAnimal
	///		enumTypeOther
	///		enumTypePerson
	///
	/// The AIT Device Type is one of:
	///		enumPassiveMillimeterWave
	///		enumActiveMillimeterWave
	///		enumTerahertzImaging
	///
	/// The Photometric Interpretation is one of:
	///		enumMonochrome1
	///		enumMonochrome2
	///		enumPaletteColor
	SDICOS::AIT3D ait(
		SDICOS::ObjectOfInspectionModule::enumGenderFemale,
		SDICOS::AIT3DTypes::AIT3DImage::enumActiveMillimeterWave,
		SDICOS::ImagePixelMacro::enumMonochrome2
	);
	
	
	// Set the time that the pixel data was created.
	ait.SetPixelDataCreationDateAndTime(SDICOS::DcsDate::Today(),SDICOS::DcsTime::Now());
		
	// Indicate when the data was originally acquired
	SDICOS::DcsDate acquisitionDate(1941,12,7);
	SDICOS::DcsTime acquisitionTime(7,48,0,0);
	ait.SetAcquisitionDateTime(acquisitionDate,acquisitionTime);

	// Add one 3D Volume Section.
	// Image Type and Image description are the same as the AIT3DSeriesBase
	SDICOS::SectionAIT *pSection = ait.AddSection();
	pSection->GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, 128,100,400); // 3D Array of data allocated by 2D slices
	
	// Set slice spacing
	pSection->SetSpacingInMM(10.0f,15.0f,20.0f);
		
	// Set Slice Position
	pSection->SetPositionInMM(100,150,200);

	// Set plane orientation for each slice
	// X-Axis goes from person's right hand to left hand
	// Y-Axis goes from person's posterior to anterior
	// Z-Axis goes from person's foot to head
	const SDICOS::Vector3D<float> vecRow(1, 0, 0);
	const SDICOS::Vector3D<float> vecColumn(0, 1, 0);
	pSection->SetPlaneOrientation(vecRow, vecColumn);
		
	// Get reference to the Volume Data 
	SDICOS::Array3DLarge<SDICOS::S_UINT16>& sectionData = *pSection->GetPixelData().GetUnsigned16();

	// This buffer is allocated for example purposes only
	SDICOS::S_UINT16 * userData = new SDICOS::S_UINT16[pSection->GetSliceSize()];

	//Initialize with dummy data
	memset(userData, 0, pSection->GetSliceSize() * sizeof(SDICOS::S_UINT16));

	// Set volume data by setting each XY plane
	for(SDICOS::S_UINT32 i = 0; i < pSection->GetDepth(); ++i) 
	{
		SDICOS::Array2D<SDICOS::S_UINT16>& xyPlane = sectionData[i];
		SDICOS::S_UINT16 * pBuffer = xyPlane.GetBuffer();
		
		// The use can copy their data into pBuffer from another source or place it directly in pBuffer.
		memcpy(pBuffer, userData, sizeof(SDICOS::S_UINT16)*pSection->GetSliceSize());
	}

	// Delete buffer
	SDICOS::DELETE_ARRAY(userData);
	
	SDICOS::ErrorLog errorlog;
	SDICOS::Folder folder("AIT3DFiles/SimpleAIT3D/");
	SDICOS::Filename filename(folder,"SimpleAIT3D.dcs");
	
	if(!ait.Write(filename,errorlog,SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "Simple AIT3D Template Example unable to write DICOS File " << filename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else 
	{
		std::cout << "Simple AIT3D Example wrote DICOS file " << filename << std::endl;
		SDICOS::AIT3D AitRead;
		if(AitRead.Read(filename,errorlog))
		{
			if(ait != AitRead) 
			{
				std::cerr << "Original AIT3D and read AIT3D are not equal" <<std::endl;
				return false;
			} 
			else 
			{
				std::cerr << "Original AIT3D and read AIT3D are equal" <<std::endl;
			}
		}
		else 
		{
			std::cerr << "Failed to read AIT3D Series from " << filename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}

	return true;
} // EndCreateAIT3DSimple

/// StartCreateAIT3DMultiVolume

// Dimensions, voxel spacing and position of two section added below
static const SDICOS::S_UINT32 sectionDims[][3] = { {50,50,400}, {64,32,100} };

static const float sectionSpacing[][3] = { {5.0f,2.5f,1.0f}, {5.0f,2.5f,1.0f} };

static const float position[][3] = { {0,0,0}, {0,0,700} };

/**
 * Create an AIT3D DICOS object with multiple volumes that are written to separate DICOS.
 * files in the same folder. The volumes are differentiated by (Width, Height, sign and bit depth)
 * In this example the two volumes have different width and height but the same sign and bit depth.
 * @return true/false
 */
bool CreateAIT3DMultiVolume()
{
	/// Create an AIT3D DICOS file for a piece of baggage.
	/// The pixel photometric interpretation is Monochrome2 indicating that lower values map to lower intensities.
	/// The Image description attributes default to a monochrome volume with original data.
	///
	/// The Object of Inspection Type (OOI) is one of:
	///		enumTypeBioSample
	///		enumTypeCargo
	///		enumTypeBaggage
	///		enumTypeAnimal
	///		enumTypeOther
	///		enumTypePerson
	///
	/// The AIT Device Type is one of:
	///		enumPassiveMillimeterWave
	///		enumActiveMillimeterWave
	///		enumTerahertzImaging
	///
	/// The Photometric Interpretation is one of:
	///		enumMonochrome1
	///		enumMonochrome2
	///		enumPaletteColor
	SDICOS::AIT3D ait(
		SDICOS::ObjectOfInspectionModule::enumTypeBaggage,
		SDICOS::AIT3DTypes::AIT3DImage::enumTerahertzImaging,
		SDICOS::ImagePixelMacro::enumMonochrome2
	);
	
	//
	// Where applicable, class methods in the Stratovan DICOS library return true/false to indicate success failure.
	// In this example the return values of various methods are tested for success/failure but this is not a requirement for usage.
	//
	bool bRes(true);
	
	// The Frame of Referenced UID defaults to a randomly generated UID
	// but can be explicitly set to identify the frame of reference for a series
	// and to indicate that multiple series share the same frame of reference.
	SDICOS::DcsUniqueIdentifier frameUID("1941.12.7.7.48.0.0");
	bRes = ait.SetFrameOfReferenceUID(frameUID) && bRes;
		
	// Set the time that the pixel data was created.
	bRes = ait.SetPixelDataCreationDateAndTime(SDICOS::DcsDate::Today(),SDICOS::DcsTime::Now()) && bRes;
		
	// Indicate when the data was originally acquired
	SDICOS::DcsDate acquisitionDate(1941,12,7);
	SDICOS::DcsTime acquisitionTime(7,48,0,0);
	bRes = ait.SetAcquisitionDateTime(acquisitionDate,acquisitionTime) && bRes;

	// Optional Number that uniquely identifies the acquisition period over which the data was acquired
	SDICOS::S_INT32 acquisitionNumber(7001);
	ait.SetAcquisitionNumber(acquisitionNumber);
	
	{
		// Add one 3D Volume Section.
		// Image Type and Image description are the same as the AIT3DSeriesBase
		SDICOS::SectionAIT * pSection = ait.AddSection();
		pSection->GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, sectionDims[0][0],sectionDims[0][1],sectionDims[0][2]); // 3D Array of data allocated by 2D slices

		// Set slice spacing
		pSection->SetSpacingInMM(sectionSpacing[0][0],sectionSpacing[0][1],sectionSpacing[0][2]);

		// Set Slice Position
		pSection->SetPositionInMM(position[0][0],position[0][1],position[0][2]);

		// Set plane orientation for each slice
		// X-Axis goes from person's right hand to left hand
		// Y-Axis goes from person's posterior to anterior
		// Z-Axis goes from person's foot to head
		const SDICOS::Vector3D<float> vecRow(1, 0, 0);
		const SDICOS::Vector3D<float> vecColumn(0, 1, 0);
		pSection->SetPlaneOrientation(vecRow, vecColumn);

		// Set Volume Data
		SDICOS::Array3DLarge<SDICOS::S_UINT16>& sectionData = *pSection->GetPixelData().GetUnsigned16();

		SDICOS::S_UINT16 * userData = new SDICOS::S_UINT16[pSection->GetSliceSize()];

		//Initialize with dummy values
		memset(userData, 0, pSection->GetSliceSize() * sizeof(SDICOS::S_UINT16));

		// Set volume data by setting each XY plane
		for(SDICOS::S_UINT32 i = 0; i < pSection->GetDepth(); ++i) 
		{
			SDICOS::Array2D<SDICOS::S_UINT16>& xyPlane = sectionData[i];
			SDICOS::S_UINT16 * pBuffer = xyPlane.GetBuffer();

			// The use can copy their data into pBuffer from another source or place it directly in pBuffer.
			memcpy(pBuffer, userData, sizeof(SDICOS::S_UINT16)*pSection->GetSliceSize());
		}

		delete [] userData;
	}
	
	{
		// Create a second volume independent from the first
		// that will ultimately be save to a different DICOS file
		const SDICOS::S_UINT32 sectionId = (12345);

		// Add a section with dimensions and indicate that unsigned 16 bit data should be allocated.
		SDICOS::SectionAIT * pSection = ait.AddSection(sectionId,sectionDims[1][0],sectionDims[1][1],sectionDims[1][2], SDICOS::Volume::enumUnsigned16Bit);

		// Set slice spacing
		pSection->SetSpacingInMM(sectionSpacing[1][0],sectionSpacing[1][1],sectionSpacing[1][2]);

		// Set Slice Position such that it is not aligned with the first volume
		pSection->SetPositionInMM(position[1][0],position[1][1],position[1][2]);

		// Set plane orientation for each slice
		// X-Axis goes from person's right hand to left hand
		// Y-Axis goes from person's posterior to anterior
		// Z-Axis goes from person's foot to head
		const SDICOS::Vector3D<float> vecRow(1, 0, 0);
		const SDICOS::Vector3D<float> vecColumn(0, 1, 0);
		pSection->SetPlaneOrientation(vecRow, vecColumn);

		// Set Volume Data
		SDICOS::Array3DLarge<SDICOS::S_UINT16>& sectionData = *pSection->GetPixelData().GetUnsigned16();
		SDICOS::S_UINT16 * userData = new SDICOS::S_UINT16[pSection->GetSliceSize()];

		//Initialize with dummy values
		memset(userData, 0, pSection->GetSliceSize() * sizeof(SDICOS::S_UINT16));

		// Set volume data by setting each XY plane
		for(SDICOS::S_UINT32 i = 0; i < pSection->GetDepth(); ++i) 
		{
			SDICOS::Array2D<SDICOS::S_UINT16>& xyPlane = sectionData[i];
			SDICOS::S_UINT16 * pBuffer = xyPlane.GetBuffer();

			// The use can copy their data into pBuffer from another source or place it directly in pBuffer.
			memcpy(pBuffer, userData, sizeof(SDICOS::S_UINT16)*pSection->GetSliceSize());
		}

		delete [] userData;
	}
	
	SDICOS::ErrorLog errorlog;
	SDICOS::Folder folder("AIT3DFiles/MultiVolumeAIT3D/");
	SDICOS::Filename filename(folder,"MultiVolumeAIT3D.dcs");

	std::cout << "Number of Sections: " << ait.GetNumberOfSections() << " Number of Files to Create: " << ait.GetNumberOfFilesToCreate() << std::endl;
	
	if(2 != ait.GetNumberOfFilesToCreate()) 
	{
		std::cerr << "Number of files to create does not match. Expected: 2 Got: " << ait.GetNumberOfFilesToCreate() << std::endl;
		return false;
	}
	
	if(!ait.Write(filename,errorlog,SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "Multivolume AIT3D Template Example unable to write DICOS File " << filename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else 
	{
		// The Verify
		bRes = VerifyWrittenDICOSFiles(ait,folder,filename) && bRes;
	}

	return bRes;
} // EndCreateAIT3DMultiVolume


/**
 * Verify that the DICOS files written by CreateAIT3DMultiVolume() can be read and compared.
 * @param original The original AIT object 
 * @param folder Folder that contains the DICOS files for each section. No other files should be in this folder
 * @param baseFilename Files for each separate DICOS files are written as baseFilename0000, baseFilename0001 etc
 * @return true/false
 */
bool VerifyWrittenDICOSFiles(
	const SDICOS::AIT3D& original, 
	const SDICOS::Folder& folder, 
	const SDICOS::Filename& baseFilename
)
{
	bool bRes(true);
	
	std::cout << "Write AIT3D DICOS file from template " << baseFilename << " " << original.GetNumberOfFilesToCreate() << std::endl;

	//
	// The SDICOS::DicosFileListing class searches and collects all DICOS files
	// in a file system folder and hierarchy.  Any files DICOS files excluded from
	// the listing due to errors will populate the 'vErrorLog' parameter.
	//
	SDICOS::DicosFileListing files;
	SDICOS::Array1D<std::pair<SDICOS::Filename, SDICOS::ErrorLog> > vErrorLog;
	files.FindDicosFiles(folder,false,vErrorLog);

	if(	0 == files.GetNumberOfObjectOfInspections() ||
		0 == files[0].GetNumberOfScans() ||
		0 == files[0][0].GetNumberOfSeries())
	{
		std::cerr << "Unable to find DICOS files for AIT3D Template" << std::endl;
		return false;
	}

	//
	// In this example, the SDICOS::DicosFileListing object is used to find the 
	// files generated for each independent AIT3D Section added to the AIT3D Series.
	// There are two files generated in this example and they exist in the same folder
	//
	SDICOS::Array1D<SDICOS::DicosFileListing::FileInfo> filenames;
	files.GetFileInfo(filenames);

	for(SDICOS::S_UINT32 i = 0; i < filenames.GetSize(); ++i) 
	{
		std::cout << filenames[i].m_filename << std::endl;
	}

	// One error log is created for each Section in the Series
	SDICOS::Array1D< std::pair<SDICOS::Filename, SDICOS::ErrorLog> > vErrorlogs;
	SDICOS::AIT3D aitRead;

	// Access files by ObjectOfInspection->Scan->Series
	const SDICOS::DicosFileListing::SopInstance& fileSopInstance = files[0][0][0][0];

	// Read the CT Data for the Series
	if(!aitRead.Read(fileSopInstance, vErrorlogs))
	{
		std::cerr << "Unable to read AIT3D DICOS files" << std::endl;
		for(SDICOS::S_UINT32 i = 0; i < vErrorlogs.GetSize(); ++i) 
		{
			std::cerr << vErrorlogs[i].first << std::endl << vErrorlogs[i].second << std::endl;
		}
		return false;
	} 
	else
	{
		std::cout << "Loaded AIT3D DICOS Files. Number of Sections: " << aitRead.GetNumberOfSections() << std::endl;
		bRes = (2 == aitRead.GetNumberOfSections()) && bRes;
		SDICOS::SectionAIT * sections[2];
		
		// When a AIT3D object is loaded, the Section numbering starts at 0.
		sections[0] = aitRead.GetSectionByIndex(0);
		sections[1] = aitRead.GetSectionByIndex(1);

		bRes = (sections[0] && sections[1]) && bRes;

		// Check that volumes have the expected dimensions and spacing
		for(SDICOS::S_UINT32 i = 0; i < 2; ++i)
		{
			bool bSectionSpacingFound(false);
			for(SDICOS::S_UINT32 j = 0; j < 2; ++j)
			{
				if(sections[i]->GetColumnSpacing() == sectionSpacing[j][0] && 
				   sections[i]->GetRowSpacing() == sectionSpacing[j][1] &&
				   sections[i]->GetSliceSpacing() == sectionSpacing[j][2]) 
				{
					bSectionSpacingFound = true;
					break;
				}
			}
			bRes = bSectionSpacingFound && bRes;
			bool bSectionDimsFound(false);
			for(SDICOS::S_UINT32 j = 0; j < 2; ++j)
			{
				if(sections[i]->GetWidth() == sectionDims[j][0] && 
				   sections[i]->GetHeight() == sectionDims[j][1] && 
				   sections[i]->GetDepth() == sectionDims[j][2]) 
				{
					bSectionDimsFound = true;
				}
			}

			bRes = bSectionDimsFound && bRes;
		}
		std::cout << "Comparison of original and loaded AIT files " << bRes << std::endl;

	}
	return bRes;
}


int main()
{
	if (false == CreateAIT3DSimple())
		return 1;

	if (false == CreateAIT3DMultiVolume())
		return 2;

	return 0;
}
