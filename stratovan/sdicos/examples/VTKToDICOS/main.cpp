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
#include <cstring>
#include <cfloat>
#include "SDICOS/DICOS.h"

/** 
 * Ssample data files are located in DICOS/Examples/DataFiles/VTK
 */

//
// Constants for different CT parameters are defined here for example purposes.
//
float focalSpotSizeInMM = 0.0f;
float KVP = 0.0f;

bool LoadVTKVolume(
    const SDICOS::Filename &filename, 
    SDICOS::Array3DLarge<unsigned short> &arrayVolume,
	SDICOS::Point3D<float> &ptOrigin,
	SDICOS::Point3D<float> &ptSpacing);

/**
 * Convert a CT VTK File to a DICOS CT File with the User-Level API
 * @return true/false
 */
bool ConvertVTKToDICOSWithUserAPI(const char * filename)
{	
	const SDICOS::Filename filenameVTK(filename);
	
	/*
	 * CT Data is stored as a buffer of unsigned shorts
	 */
	SDICOS::Array3DLarge<unsigned short> vnVolume;
	
	/*
	 * Origin and Spacing are stored in the SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros
	 */
	SDICOS::Point3D<float> ptOrigin;
	SDICOS::Point3D<float> ptSpacing;

	if(!LoadVTKVolume(filenameVTK, vnVolume, ptOrigin, ptSpacing)) {
		std::cout << "Failed to load VTK file " << filename << std::endl;
		return false;
	}

	/*
	 * The SDICOS::CT object is the user-level API object that represent the
	 * Computed Tomography (CT) Information Object Definition (IOD) in the DICOS Specification Section 7.
	 * 
	 * Defined in "SDICOS/ModuleCT.h" 
	 * Here we create a SDICOS::CT object and then initialize required DICOS attributes.
	 */

	/*
		Construct a CT object given information about the Object of Inspection
		All attributes not set below are given valid default values.
	*/
	SDICOS::CT ctUser(
		SDICOS::ObjectOfInspectionModule::enumTypeBaggage,
		SDICOS::CTTypes::CTImage::enumHighEnergy,
		SDICOS::CTTypes::CTImage::enumVolume,
		SDICOS::ImagePixelMacro::enumMonochrome2
	);
		
	/// Acquisition time in seconds. Set to FLT_MAX to indicate unknown time value.
	ctUser.SetImageAcquisitionDuration(FLT_MAX);

	//
	// Create a new SDICOS::Section object to contain the volume data and indicate
	// that the new Section object now owns its slice data.
	//
    SDICOS::Section * pSection = ctUser.AddSection(vnVolume, SDICOS::MemoryPolicy::OWNS_SLICES);
	vnVolume.SetMemoryPolicy(SDICOS::MemoryPolicy::DOES_NOT_OWN_SLICES);
	
	// These parameters are required 
	pSection->SetFocalSpotSizeInMM(focalSpotSizeInMM);
	pSection->SetKVP(KVP);

	/*
	 * Set Pixel spacing in MM for X, Y, Z directions
	 */
	pSection->SetSpacingInMM(ptSpacing.x, ptSpacing.y, ptSpacing.z);

	/*
	 * Set plane origin position.
	 */
	pSection->SetPositionInMM(ptOrigin.x,ptOrigin.y,ptOrigin.z);

	/*
	 * Set plane orientation for the volume's top left position on a slice. 
	 * Slice rows corresponds to X-axis and and slice columns correspond to Y-Axis 
	 */
	const SDICOS::Vector3D<float> vecRow(1, 0, 0);
	const SDICOS::Vector3D<float> vecColumn(0, 1, 0);
	pSection->SetPlaneOrientation(vecRow, vecColumn);

	const SDICOS::Filename outputFilename("CTFromVTKUserAPI.dcs");

	/*
	 * The ErrorLog class stores warning and errors from the validation process
	 */
	SDICOS::ErrorLog errorlog;

	/*
	 * Writing the CT file validates the CT object and reports errors in the supplied errorlog.
	 */
	if(!ctUser.Write(outputFilename, errorlog, SDICOS::DicosFile::enumLittleEndianExplicit)) 
	{
		SDICOS::Filename errorLogFilename("CTFromVTKUserAPI-ErrorLog.txt");
		errorlog.WriteLog(errorLogFilename);
		std::cout << "Failed to write CT File with User API " << outputFilename.GetFullPath() << std::endl;
		std::cout << "ErrorLog written to " << errorLogFilename.GetFullPath() << std:: endl;
		std::cout << errorlog << std::endl;
		return false;
	}

	errorlog.FreeMemory();

	SDICOS::AttributeManager manager;
	if(SDICOS::DicosFile::Read(outputFilename, errorlog, manager)) 
	{
		manager.WriteToFileAsText("CTFromVTKUserAPI-Listings.txt");
	} 
	else 
	{
		std::cout << "Failed to read CT DICOS file " << outputFilename.GetFullPath() << std::endl;
		std::cout << errorlog << std::endl;
		return false;
	}
		
	errorlog.FreeMemory();

	// Read CT using User Level API
	SDICOS::CT ctUserRead;
	
	if(!ctUserRead.Read(outputFilename, errorlog)) 
	{
		std::cout << "Failed to read CT DICOS file " << outputFilename.GetFullPath() << std::endl;
		return false;
	} 
	else 
	{
		if(ctUser == ctUserRead)
		{
			std::cout << "Successfully read and compared converted CT file" << std::endl;
		}
		else
		{
			std::cout << "Failed to read and compare converted CT file" << std::endl;
			std::cout << errorlog << std::endl;
			return false;
		}
	}

	return true;
} // EndConvertVTKToDICOSWithUserAPI


/**
 * Convert a CT VTK File to a DICOS CT File with the Module-Level API
 * This example explicitly sets all required DICOS attributes
 * using the Module-Level API interface.
 * 
 * In the User-Level API example above, the SDICOS::CT User-Level API object
 * initializes required attributes to valid default values.
 * 
 * @return true/false
 */
bool ConvertVTKToDICOSWithModuleAPI(const char * filename)
{	
	/*
	 * The CT object is the high-level API object that represent the
	 * Computed Tomography (CT) Information Object Definition (IOD) in the DICOS Specification Section 7.
	 * 
	 * #include "SDICOS/ModuleCT.h"
	 *
	 * All objects in the Stratovan DICOS Toolkit are declared in the SDICOS namespace.
	 */
	SDICOS::CTModule ct;
	
	const SDICOS::Filename filenameVTK(filename);
	
	/*
	 * CT Data is stored as a buffer of unsigned shorts
	 */
	SDICOS::Array3DLarge<unsigned short> vnVolume;
	
	/*
	 * Origin and Spacing are stored in the SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros
	 */
	SDICOS::Point3D<float> ptOrigin;
	SDICOS::Point3D<float> ptSpacing;

	if(!LoadVTKVolume(filenameVTK, vnVolume, ptOrigin, ptSpacing))
		return false;

	/*
	 *	API methods generally return true/false to indicate
	 *	success and failure.
	 */
	bool bRes(true);
	
	/*
	 *	The following code sets up all required attributes in the CT Image IOD (Section &, Table 14) 
	 *	This shows the minimum set of required attributes needed for a DICOS file to conform
	 *	to the DICOS Specification.
	 */
	
	/*
	 * Set CT Series attributes represented by the CT Series Module (Table 
	 */

	bRes = bRes && ct.GetSeries().SetAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful);
	bRes = bRes && ct.GetSeries().SetDateAndTime("20140114", "074417");
	bRes = bRes && ct.GetSeries().SetInstanceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370732.880");

	/*
	 * The CT Image class represents the CT Image Module (Table 17)
	 * 
	 * See "SDICOS/CTImage.h"
	 */
	bRes = bRes && ct.GetCTImage().SetPixelData(vnVolume);
	
	/*
	 * DcsdDateTime object takes data as "YYYYMMDD" and time as "HHMMSS"
	 */
	SDICOS::DcsDateTime strDT;
	strDT.Set("20140114", "074417");
	bRes = bRes && ct.GetCTImage().SetAcquisitionDateAndTime(strDT);
	bRes = bRes && ct.GetCTImage().SetBurnedInAnnotation(false);
	
	/*
	 * See the documentation for SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION
	 */
	bRes = bRes && ct.GetCTImage().SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);
	
	/*
	 * The CT Image Type attribute contains 4 values.
	 */
	bRes = bRes && ct.GetCTImage().SetImageTypeCT(	SDICOS::CTTypes::CTImage::enumOriginal, 
													SDICOS::CTTypes::CTImage::enumPhotoelectric,
													SDICOS::CTTypes::CTImage::enumVolume,
													SDICOS::CTTypes::CTImage::enumNone);
	bRes = bRes && ct.GetCTImage().SetAcquisitionDuration(30);
	bRes = bRes && S_NULL != ct.GetCTImage().GetCommonImageDescription();
	bRes = bRes && ct.GetCTImage().GetCommonImageDescription()->SetPixelPresentation(SDICOS::CommonImageDescription::enumPP_Monochrome);
	bRes = bRes && ct.GetCTImage().GetCommonImageDescription()->SetVolumeBasedCalculationTechnique(SDICOS::CommonImageDescription::enumVC_None);
	bRes = bRes && ct.GetCTImage().GetCommonImageDescription()->SetVolumetricProperties(SDICOS::CommonImageDescription::enumVP_Volume);

	/*
	 * The CTTypes::CTMultiframeFunctionalGroups class is the CT Specific implementation of the MultiframeFunctionalGroups (Table 109) module
	 * with the CT Specific Multiframe Functional Groups in Table 15 
	 */
	bRes = bRes && ct.GetMultiframeFunctionalGroups().SetNumberOfFrames(vnVolume.GetDepth());
	bRes = bRes && ct.GetMultiframeFunctionalGroups().SetContentDateAndTime("20140114", "074417");
	bRes = bRes && ct.GetMultiframeFunctionalGroups().SetInstanceNumber(1001);

	/*
	 * Passing true to the GetSharedFunctionalGroups(), GetPixelMeasurement(), GetPlaneOrientation(), GetPlanePosition()
	 * GetPixelValueTransformation(), GetImageFrameType() and GetXRayDetails() 
	 * methods ensures that space is allocated for the PixelMeasurement object.
	 */
	ct.GetMultiframeFunctionalGroups().AllocateSharedFunctionalGroups();
	SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros *pmfg = ct.GetMultiframeFunctionalGroups().GetSharedFunctionalGroups();
	pmfg->AllocatePixelMeasurement();
	bRes = bRes && pmfg->GetPixelMeasurement();
	
	/*
	 * Set Pixel spacing in MM for X and Y directions
	 */
	bRes = bRes && pmfg->GetPixelMeasurement()->SetPixelSpacingInMM(ptSpacing.x, ptSpacing.y);
	
	/*
	 * Set slice thickness in MM (Z direction)
	 */
	bRes = bRes && pmfg->GetPixelMeasurement()->SetSliceThicknessInMM(1.0f);
	
	/*
	 * Set plane orientation using cosines to define frame vectors.
	 */
	pmfg->AllocatePlaneOrientation();
	bRes = bRes && pmfg->GetPlaneOrientation()->SetImageOrientation(1,0,0, 0,1,0);
	
	/*
	 * Set plane per frame positions along the z-axis.
	 */
	SDICOS::Array1D<SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros> &vPerFrame = ct.GetMultiframeFunctionalGroups().GetPerFrameFunctionalGroups();

	for (SDICOS::S_UINT32 nFrame(0); nFrame < vPerFrame.GetSize(); ++nFrame)
	{
		SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros &mfgm = vPerFrame[nFrame];
		mfgm.AllocatePlanePosition();
		bRes = bRes && mfgm.GetPlanePosition()->SetPositionInMM(ptOrigin.x, ptOrigin.y, ptOrigin.z + ptSpacing.z * float(nFrame));
	}
	
	/*
	 * The PixelValueTransformation specifies a linear transform applied to the
	 * stored values to produce values in the output units.
	 */
	pmfg->AllocatePixelValueTransformation();
	bRes = bRes && pmfg->GetPixelValueTransformation()->SetRescaleIntercept(-1000);
	bRes = bRes && pmfg->GetPixelValueTransformation()->SetRescaleSlope(1);
	
	/*
	 * String value indicating what the output units are after applying pixel transformation
	 */
	bRes = bRes && pmfg->GetPixelValueTransformation()->SetRescaleType("HU");
	
	/*
	 * Same as as call to ct.GetCTImage().SetImageTypeCT()
	 */
	pmfg->AllocateImageFrameType();
	bRes = bRes && pmfg->GetImageFrameType()->SetFrameType(	SDICOS::CTTypes::CTImage::enumOriginal,		
															SDICOS::CTTypes::CTImage::enumPhotoelectric,
															SDICOS::CTTypes::CTImage::enumVolume,
															SDICOS::CTTypes::CTImage::enumNone);
	
	/*
	 * The CommonImageDescription data is shared between the CTImage and CTMultiframeFunctionalGroupMacros
	 */
	pmfg->GetImageFrameType()->GetCommonImageDescription() = *(ct.GetCTImage().GetCommonImageDescription());
	
	/*
	 * The CTXRayDetails module is required if the first value in the CT Image Type attribute is ORIGINAL or MIXED.
	 * See CTImage::SetImageTypeCT which is set above by calling SetImageTypeCT
     */
	pmfg->AllocateXRayDetails();
	bRes = bRes && pmfg->GetXRayDetails()->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumLead);
	bRes = bRes && pmfg->GetXRayDetails()->SetFilterType(SDICOS::CTTypes::CTXRayDetails::enumNone);
	bRes = bRes && pmfg->GetXRayDetails()->SetFocalSpotSizeInMM(0);
	bRes = bRes && pmfg->GetXRayDetails()->SetKVP(0);

	/*
	 * The SDICOS::FrameOfReference class represents the Frame of Reference (Table 107)
	 * The Frame of Reference UID uniquely identifies a frame of reference for a series and 
	 * is a grouping to indicate that multiple series in a scan have the same frame of reference.
	 */
	bRes = bRes && ct.GetFrameOfReference().SetFrameOfReferenceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370740.886");

	/*
	 * The ObjectOfInspectionModule class represents Object Of Inspection Module (OOI) (Section 4.1, Table 10)
	 */
	bRes = bRes && ct.GetObjectOfInspection().GetID().SetID("TSS4.000314");
	bRes = bRes && ct.GetObjectOfInspection().GetID().SetIdAssigningAuthority("Issurer-001");
	bRes = bRes && ct.GetObjectOfInspection().GetID().SetIdType(SDICOS::ObjectOfInspectionModule::IdInfo::enumText);
	bRes = bRes && ct.GetObjectOfInspection().SetType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);

	/*
	 * The GeneralScanModule class represents the General Scan Module (Section 5 Table 12)
	 */
	bRes = bRes && ct.GetGeneralScan().SetScanID("TSS4.314");
	bRes = bRes && ct.GetGeneralScan().SetScanInstanceUID("1.2.276.0.7230010.3.1.2.4126100761.8984.1407370732.879");
	bRes = bRes && ct.GetGeneralScan().SetStartDateAndTime("20140114", "074417");
	bRes = bRes && ct.GetGeneralScan().SetType(SDICOS::GeneralScanModule::enumOperational);

	/*
	 * The GeneralEquipmentModule class represent the General Equipment Module (Table 70)
	 * Required information about the machine the scan was captured on.
	 */
	bRes = bRes && ct.GetGeneralEquipment().SetCalibrationDateAndTime("20140225", "130532.435");
	bRes = bRes && ct.GetGeneralEquipment().SetDeviceSerialNumber("DSN-001");
	bRes = bRes && ct.GetGeneralEquipment().SetMachineAddress("Southfield, Michigan");
	bRes = bRes && ct.GetGeneralEquipment().SetMachineID("Gremlin");
	bRes = bRes && ct.GetGeneralEquipment().SetMachineLocation("1 Rust Bucket Way");
	bRes = bRes && ct.GetGeneralEquipment().SetManufacturer("American Motors");
	bRes = bRes && ct.GetGeneralEquipment().SetManufacturerModelName("GremlinX");
	bRes = bRes && ct.GetGeneralEquipment().SetSoftwareVersion("1972");

	/*
	 * The SOPCommonModule class represents the SOP Common Module (Table 82)
	 * which defines attributes for identifying associated Service Object Pair (SOP) instances
	 */
	bRes = bRes && ct.GetSopCommon().SetSopInstanceCreationDateAndTime("20140225", "150423.546");
	bRes = bRes && ct.GetSopCommon().SetSopInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.881");

	/*
	 * The CommonInstanceReferenceModule class represents the Common Instance Reference Module (Table 87)
	 * which describes the relationships between SOP Instances referenced between modules in the same instance.
	 * In this example, we have one scan with one series.
	 */
	ct.GetCommonInstanceReference().AllocateReferencedSeries();
	bRes = bRes && ct.GetCommonInstanceReference().GetReferencedSeries()->GetReferencedSeries().SetSize(1);
	
	/*
	 * Note that this series instance UID matches the one set above on the CT object
	 * with the call to ct.GetSeries().SetInstanceUID(...)
	 */
	bRes = bRes && ct.GetCommonInstanceReference().GetReferencedSeries()->GetReferencedSeries()[0].SetSeriesInstanceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370732.880");
	bRes = bRes && ct.GetCommonInstanceReference().GetReferencedSeries()->GetReferencedSeries()[0].GetReferencedInstances().SetSize(1);
	bRes = bRes && ct.GetCommonInstanceReference().GetReferencedSeries()->GetReferencedSeries()[0].GetReferencedInstances()[0].SetClassUID(SDICOS::SOPClassUID::GetCT());
	bRes = bRes && ct.GetCommonInstanceReference().GetReferencedSeries()->GetReferencedSeries()[0].GetReferencedInstances()[0].SetInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.885");

	const SDICOS::Filename outputFilename("CTFromVTKModuleAPI.dcs");

	/*
	 * The ErrorLog class stores warning and errors from the validation process
	 */
	SDICOS::ErrorLog errorlog;
	
	/*
	 * Writing the CT file validates the CT object and reports errors in the
	 * supplied errorlog. If this call 
	 */
	if(!ct.Write(outputFilename, SDICOS::DicosFile::enumLittleEndianExplicit, errorlog)) 
	{
		errorlog.WriteLog("CTFromVTKModuleAPI-ErrorLog.txt");
		std::cout << "Failed to write CT File " << outputFilename.GetFullPath() << std::endl;
		std::cout << errorlog << std::endl;
	}

	errorlog.FreeMemory();
	SDICOS::AttributeManager manager;
	if(SDICOS::DicosFile::Read(outputFilename, errorlog, manager)) 
	{
		manager.WriteToFileAsText("CTFromVTKModuleAPI-Listings.txt");
	} 
	else 
	{
		std::cout << "Failed to read CT DICOS file " << outputFilename.GetFullPath() << std::endl;
		std::cout << errorlog << std::endl;
		bRes = false;
	}

	SDICOS::CTModule ctRead;
	SDICOS::ErrorLog errorlogRead;
	if(!ctRead.Read(outputFilename, errorlogRead)) 
	{
		std::cout << "Failed to read CT DICOS file " << outputFilename.GetFullPath() << std::endl;
		bRes = false;
	} 
	else 
	{
		bRes = bRes && ct == ctRead;
	}

	return bRes;
} // EndConvertVTKToDICOSWithModuleAPI

int main(int argc, char *argv[])
{
    if(1 == argc) 
    {
        std::cout << "Usage: VTKToDICOS filename" << std::endl;
        return 0;
    }
	
	bool b = ConvertVTKToDICOSWithUserAPI(argv[1]);
	std::cout << "Conversion result with User API " << b << std::endl;
		
	b = ConvertVTKToDICOSWithModuleAPI(argv[1]) && b;
	std::cout << "Conversion result with Module API " << b << std::endl;
    return (b ? 0 : 1);
}

bool IsEqualNoCase(const std::string &strA, const std::string &strB)
{
#ifdef WIN32
#define strcasecmp _stricmp 
	return (0 == strcasecmp(strA.c_str(),strB.c_str()));
#undef strcasecmp
#else
	return (0 == strcasecmp(strA.c_str(),strB.c_str()));
#endif
}

typedef enum
{
	enumVTK_Unknown,
	enumVTK_Scalar,
	enumVTK_ColorScalar_1,
	enumVTK_ColorScalar_2,
	enumVTK_ColorScalar_3,
	enumVTK_ColorScalar_4,
}VTK_SCALAR_TYPE;

//
// Simple VTK loader.
//
bool LoadVTKVolume(
    const SDICOS::Filename &filename, 
    SDICOS::Array3DLarge<unsigned short> &arrayVolume,
	SDICOS::Point3D<float> &ptOrigin,
	SDICOS::Point3D<float> &ptSpacing)
{
	bool bRes(true);

	SDICOS::File file;

	if(!file.OpenReading(filename))
		return false;

	int nW(1), nH(1), nD(1) /*nNumDims(0), nDataType(0)*/;
	VTK_SCALAR_TYPE		nScalarType(enumVTK_Unknown);

	std::string str;
	{
		bRes = bRes && file.ReadWord(str);
		if(!IsEqualNoCase(str, "#"))
			return false;
		bRes = bRes && file.ReadWord(str);
		if(!IsEqualNoCase(str, "vtk"))
			return false;
		bRes = bRes && file.ReadWord(str);
		if(!IsEqualNoCase(str, "DataFile"))
			return false;
		bRes = bRes && file.ReadWord(str);
		if(!IsEqualNoCase(str, "Version"))
			return false;
		bRes = bRes && file.ReadLine(str);
		if(!IsEqualNoCase(str, "3.0"))
			return false;
	}

	{
		bRes = bRes && file.ReadLine(str);
		if(!IsEqualNoCase(str, "vtk output"))
			return false;
	}

	{
		bRes = bRes && file.ReadLine(str);
		if(!IsEqualNoCase(str, "BINARY"))
			return false;
	}

	{
		bRes = bRes && file.ReadLine(str);
		if(!IsEqualNoCase(str, "DATASET STRUCTURED_POINTS"))
			return false;
	}

	{
		bRes = bRes && file.ReadWord(str);
		if(!IsEqualNoCase(str, "DIMENSIONS"))
			return false;
		bRes = bRes && file.ReadWord(str);
		nW = atoi(str.c_str());
		bRes = bRes && file.ReadWord(str);
		nH = atoi(str.c_str());
		bRes = bRes && file.ReadLine(str);
		nD = atoi(str.c_str());
	}

	{
		bRes = bRes && file.ReadWord(str);
		if(!IsEqualNoCase(str, "SPACING"))
			return false;
		bRes = bRes && file.ReadWord(str);
		ptSpacing.x = (float)atof(str.c_str());
		bRes = bRes && file.ReadWord(str);
		ptSpacing.y = (float)atof(str.c_str());
		bRes = bRes && file.ReadLine(str);
		ptSpacing.z = (float)atof(str.c_str());
	}

	{
		bRes = bRes && file.ReadWord(str);
		if(!IsEqualNoCase(str, "ORIGIN"))
			return false;
		bRes = bRes && file.ReadWord(str);
		ptOrigin.x = (float)atof(str.c_str());
		bRes = bRes && file.ReadWord(str);
		ptOrigin.y = (float)atof(str.c_str());
		bRes = bRes && file.ReadLine(str);
		ptOrigin.z = (float)atof(str.c_str());
	}

	{
		bool bDone(false);
		while(!bDone || !bRes)
		{
			bRes = bRes && file.ReadWord(str);	// POINT_DATA XXXXX
			if(IsEqualNoCase(str, "CELL_DATA"))
			{
				bRes = bRes && file.ReadLine(str);	// POINT_DATA XXXXX
				//S_ASSERT((nW-1)*(nH-1)*(nD-1) == atoi(str.c_str()));
			}
			else
			if(IsEqualNoCase(str, "POINT_DATA"))
			{
				bRes = bRes && file.ReadLine(str);	// POINT_DATA XXXXX
				S_ASSERT(nW*nH*nD == atoi(str.c_str()));
			}
			else
				bDone = true;
		}

		if(IsEqualNoCase(str, "SCALARS"))
		{
			nScalarType = enumVTK_Scalar;
			bRes = bRes && file.ReadLine(str);
			if(!IsEqualNoCase(str, "scalars unsigned_short"))
				return false;
			bRes = bRes && file.ReadLine(str);
			if(!IsEqualNoCase(str, "LOOKUP_TABLE default"))
				return false;
		}
		else
		if(IsEqualNoCase(str, "COLOR_SCALARS"))
		{
			nScalarType = enumVTK_ColorScalar_1;
			bRes = bRes && file.ReadLine(str);
			//if(Tools::IsEqualNoCase(str, "scalars 4"))
			//	nScalarType = enumVTK_ColorScalar_4;
			//else
			//if(Tools::IsEqualNoCase(str, "scalars 3"))
			//	nScalarType = enumVTK_ColorScalar_3;
			//else
			//if(Tools::IsEqualNoCase(str, "scalars 2"))
			//	nScalarType = enumVTK_ColorScalar_2;
			//else
			if(!IsEqualNoCase(str, "scalars 1"))
				return false;
		}
		else
			return false;
	}

	/*int nAt = (int)*/file.Tell();

	file.SetFileEndian(SDICOS::IFile::enumBigEndian);

	std::cout << "Load VTK file with dimensions (" << nW << "," << nH << "," << nD << ")" << std::endl;
	std::cout << "Origin (" << ptOrigin.x << "," << ptOrigin.y << "," << ptOrigin.z << ")" << std::endl;
	std::cout << "Spacing (" << ptSpacing.x << "," << ptSpacing.y << "," << ptSpacing.z << ")" << std::endl;
		
	// We should be at the short data by now...
	SDICOS::Array2D<unsigned short>	temp;
	SDICOS::Array2D<unsigned char>	tempUChar;
	arrayVolume.SetSize(nW, nH, nD);

	if(enumVTK_Scalar == nScalarType)
	{
		temp.SetSize(nW, nH);
		for(int k = 0; k < nD; ++k)
		{
			bRes = bRes && file.Read( temp.GetBuffer(), nW*nH );
			SDICOS::Array2D<unsigned short> &slice = arrayVolume[k];
			for(int j = 0; j < nH; ++j)
			for(int i = 0; i < nW; ++i)
				slice[j][i] = temp[j][i];
				//slice[j][i] = (short)Clamp<int>(temp[j][i], 0, 32767);
		}
	}
	else
	if(enumVTK_ColorScalar_1 == nScalarType)
	{
		tempUChar.SetSize(nW, nH);
		for(int k = 0; k < nD; ++k)
		{
			bRes = bRes && file.Read( tempUChar.GetBuffer(), nW*nH );
			SDICOS::Array2D<unsigned short> &slice = arrayVolume[k];
			for(int j = 0; j < nH; ++j)
			for(int i = 0; i < nW; ++i)
				slice[j][i] = (unsigned short)SDICOS::Clamp<int>(int(tempUChar[j][i])*4096, 0, 65535);
				//slice[j][i] = (short)Clamp<int>(int(tempUChar[j][i])*4096, 0, 32767);
		}
	}

	return bRes;
} // EndLoadVTKVolume
