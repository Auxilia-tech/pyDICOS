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

/*
 * The XRay Equipment object is the module-level API object that represent the
 * XRay Equipment in the DICOS Specification.
 *
 * #include "SDICOS/XRayEquipmentModule.h"
 */
bool CreateXRayEquipment(SDICOS::XRayEquipmentModule& xr)
{
	/*
	 *	High and low-level API methods generally return true/false to indicate
	 *	success and failure.
	 */
	bool bRes(true);

	/*
	 * XRay Equipment has one required Floating Point Single attribute.
	 */
	float energy = 0;
	bRes = bRes && xr.SetEffectiveEnergy(energy);

	/*
	 * XRay Equipment has one optional Short Text attribute.
	 */
	SDICOS::DcsShortText st = "Short Text Test.";
	bRes = bRes && xr.SetMaskCharacteristics(st);

	/*
	 * XRay Equipment has five optional Code String attributes.
	 * These attributes are represented by enums.
	 */

	// Type of G0
	//bRes = bRes && xr.SetTypeG0(SDICOS::XRayEquipmentModule::enumXrayAnodeG0);
	bRes = bRes && xr.SetTypeG0(SDICOS::XRayEquipmentModule::enumGratingG0);
	bRes = bRes && xr.SetTypeG0(SDICOS::XRayEquipmentModule::enumMaskG0);

	// Type of G1
	bRes = bRes && xr.SetTypeG1(SDICOS::XRayEquipmentModule::enumGratingG1);
	bRes = bRes && xr.SetTypeG1(SDICOS::XRayEquipmentModule::enumOtherG1);

	// Type of G2
	bRes = bRes && xr.SetTypeG2(SDICOS::XRayEquipmentModule::enumGratingG2);
	bRes = bRes && xr.SetTypeG2(SDICOS::XRayEquipmentModule::enumOtherG2);

	// Reconstruction Algorithm for Phase Image
	bRes = bRes && xr.SetReconAlgorithmPhaseImage(SDICOS::XRayEquipmentModule::enumFFT);
	bRes = bRes && xr.SetReconAlgorithmPhaseImage(SDICOS::XRayEquipmentModule::enumModifiedFFT);
	bRes = bRes && xr.SetReconAlgorithmPhaseImage(SDICOS::XRayEquipmentModule::enumOtherImage);

	// Reconstruction Algorithm for Dark Image
	bRes = bRes && xr.SetReconAlgorithmDarkImage(SDICOS::XRayEquipmentModule::enumFFT);
	bRes = bRes && xr.SetReconAlgorithmDarkImage(SDICOS::XRayEquipmentModule::enumModifiedFFT);
	bRes = bRes && xr.SetReconAlgorithmDarkImage(SDICOS::XRayEquipmentModule::enumOtherImage);

	/*
	 * XRay Equipment has thirteen optional Floating Point Single attributes.
	 */
	bRes = bRes && xr.SetDistanceFromG0ToSourceInCentimeters(0.0f);
	bRes = bRes && xr.SetDistanceFromG1ToSourceInCentimeters(1.0f);
	//bRes = bRes && xr.SetDistanceFromG2ToSourceInCentimeters(2.0f);
	bRes = bRes && xr.SetG0AbsorptionPeriod(3.0f);
	bRes = bRes && xr.SetG1PhasePeriod(4.0f);
	bRes = bRes && xr.SetG2AnalyzerPeriod(5.0f);
	bRes = bRes && xr.SetVisibility(6.0f);
	bRes = bRes && xr.SetAbsorptionXRDetectorSize(7.0f, 9.0f);
	bRes = bRes && xr.SetAbsorptionReconstructionVoxelSize(9.0f, 10.0f);
	bRes = bRes && xr.SetPhaseXRDetectorSize(11.0f, 12.0f);
	bRes = bRes && xr.SetPhaseReconstructionVoxelSize(13.0f, 14.0f, 15.0f);
	bRes = bRes && xr.SetDarkXRDetectorSize(16.0f, 17.0f);
	bRes = bRes && xr.SetDarkReconstructionVoxelSize(18.0f, 19.0f, 20.0f);

	return bRes;
}

/**
 * Create example CT file using the CTModule class.
 * @return true/false
 */
bool CreateCT()
{	
	/*
	 * The CTModule object is the module-level API object that represent the
	 * Computed Tomography (CT) Information Object Definition (IOD) in the DICOS Specification.
	 * 
	 * #include "SDICOS/ModuleCT.h"
	 *
	 * All objects in the Stratovan DICOS Toolkit are declared in the SDICOS namespace.
	 * SDICOS::CTModule is not a thread-safe object.
	 * The SDICOS::CTTypes namespace contains classes that implement DICOS modules specific the CT IOD.
	 */
	SDICOS::CTModule ct;
	
	// Objects and data for CT Modules are in the SDICOS::CTTypes namespace
	SDICOS::CTTypes::CTImage &image = ct.GetCTImage();
	
	/*
	 * CT Data is stored as a buffer of unsigned shorts
	 * Internally this is implemented as a 1-D array of 2-D arrays so (X,Y) slices and contiguous blocks of memory.
	 */
	SDICOS::Array3DLarge<SDICOS::S_UINT16> vnVolume;// = image.GetPixelData();
	
	SDICOS::S_UINT32 width(128),height(128),depth(100);
	vnVolume.SetSize(width,height,depth);

	SDICOS::S_UINT16 val = 123;
	
	//
	// The 3D array of CT data can be set in multiple ways
	//
	// Method 1: Accessing the array using 3-D indices.
	//
	SDICOS::S_UINT32 x,y,z;
	for(z = 0; z < depth; ++z)
	for(y = 0; y < height; ++y)
	for(x = 0; x < width; ++x)
		vnVolume[z][y][x] = val;	// Implicitly converts data to SDICOS::S_UINT16.

	//
	// Method 2: Accessing the data one plane at a time
	// note that the 3D memory is not a contiguous block. Slices are contiguous blocks.
	//
	for(z = 0; z < depth; ++z)
	{
		SDICOS::Array2D<SDICOS::S_UINT16> &zPlane = vnVolume[z];
		for(y = 0; y < height; ++y)
		for(x = 0; x < width; ++x)
			zPlane[y][x] = val; // If needed convert raw data to SDICOS::S_UINT16 cConvertData<type>(val);
	}
	
	//
	// Method 3: Copy data directly into the raw buffers of the array.
	// Requires caller to setup data buffers in the correct format
	//
	SDICOS::S_UINT16 * slice = new SDICOS::S_UINT16[width*height];
	
	for(z = 0; z < depth; ++z)
	{
		memcpy(vnVolume[z].GetBuffer(), slice, width*height*sizeof(SDICOS::S_UINT16));
	}

	delete [] slice;
	
	//
	// Method 4: Access data explicitly as 2D planes
	//
	// 3D volume is an array of 2D slices
	// GetBuffer() returns a pointer to an array of slices
	//
	
	for(SDICOS::S_UINT32 z = 0; z < depth; ++z)
	{
		// one-dimensional array that holds XY plane of width*height dimensions
		SDICOS::S_UINT16 * xyPlane = vnVolume[z].GetBuffer();
		
		/*
		 * Set data for a single slice as if it is a 1-D array.
		 */
		for(SDICOS::S_UINT32 i = 0; i < (width*height); ++i)
			xyPlane[i] = z;
	}

	/*
	 * Origin and Spacing are stored in the SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros
	 */
	SDICOS::Point3D<float> ptOrigin(1.0f,2.0f,3.0f);
	SDICOS::Point3D<float> ptSpacing(0.1f,0.1f,0.5f);

	/*
	 *	High and low-level API methods generally return true/false to indicate
	 *	success and failure.
	 */
	bool bRes(true);
	
	/*
	 *	The following code sets up all required attributes in the CT Image IOD
	 *	This shows the minimum set of required attributes needed for a DICOS file to conform
	 *	to the DICOS Specification.
	 */
	
	/* 
	 * DcsdDateTime object takes data as "YYYYMMDD" and time as "HHMMSS"
	 */
	SDICOS::DcsDateTime dateTime;
	SDICOS::DcsDate date;
	SDICOS::DcsTime time;
	date.SetToday();
	time.SetNow();
	dateTime.Set(date,time);
	
	/*
	 * The CT Series class represents the CT Series Module
	 * 
	 * #include "SDICOS/CTSeries.h"
	 */
	SDICOS::CTTypes::CTSeries &series = ct.GetSeries();
	bRes = bRes && series.SetAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful);
	bRes = bRes && series.SetDateAndTime(date,time);
	
	//
	// Set the Unique ID of the Scan for the CTSeries.
	//
	SDICOS::DcsUniqueIdentifier instanceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370732.880");
	bRes = bRes && series.SetInstanceUID(instanceUID);

	/*
	 * The CT Image class represents the CT Image Module
	 * 
	 * See "SDICOS/CTImage.h"
	 * 
	 * Currently the data is copied from the given array into the
	 * CTImage module.
	 */

	bRes = bRes && image.SetPixelData(vnVolume);
	bRes = bRes && image.SetAcquisitionDateAndTime(dateTime);
	bRes = bRes && image.SetBurnedInAnnotation(false);
	
	/*
	 * See the documentation for SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION
	 */
	bRes = bRes && image.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);
	
	/*
	 * The CT Image Type attribute contains 4 values.
	 */
	bRes = bRes && image.SetImageTypeCT(	SDICOS::CTTypes::CTImage::enumOriginal, 
											SDICOS::CTTypes::CTImage::enumPhotoelectric,
											SDICOS::CTTypes::CTImage::enumVolume,
											SDICOS::CTTypes::CTImage::enumNone);
	bRes = bRes && image.SetAcquisitionDuration(30);

	bRes = bRes && image.SetImageOrigin(SDICOS::ImageCommon::enumMachine);
	bRes = bRes && image.SetCoordinateSystem(SDICOS::ImageCommon::enumLHS);
	
	SDICOS::CommonImageDescription * commonImageDescription = image.GetCommonImageDescription();
	bRes = bRes && (S_NULL != commonImageDescription);
	bRes = bRes && commonImageDescription->SetPixelPresentation(SDICOS::CommonImageDescription::enumPP_Monochrome);
	bRes = bRes && commonImageDescription->SetVolumeBasedCalculationTechnique(SDICOS::CommonImageDescription::enumVC_None);
	bRes = bRes && commonImageDescription->SetVolumetricProperties(SDICOS::CommonImageDescription::enumVP_Volume);

	/*
	 * The CTTypes::CTMultiframeFunctionalGroups class is the CT Specific implementation of the MultiframeFunctionalGroups module
	 * with the CT Specific Multiframe Functional Groups
	 */
	SDICOS::CTTypes::CTMultiframeFunctionalGroups& multiframeFunctionalGroups = ct.GetMultiframeFunctionalGroups();
	bRes = bRes && multiframeFunctionalGroups.SetNumberOfFrames(vnVolume.GetDepth());
	bRes = bRes && multiframeFunctionalGroups.SetContentDateAndTime(date,time);
	bRes = bRes && multiframeFunctionalGroups.SetInstanceNumber(1001);

	/*
	 * Shared Functional Groups are values that are identical between all frames
	 */
	multiframeFunctionalGroups.AllocateSharedFunctionalGroups();
	SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros *pmfg = multiframeFunctionalGroups.GetSharedFunctionalGroups();

	//
	// Modules that are marked as 'U' or User optional need to be explicitly allocated
	// by the user to indicate that their attributes are being used.
	//
	pmfg->AllocatePixelMeasurement();
	pmfg->AllocatePlaneOrientation();
	pmfg->AllocatePixelValueTransformation();
	pmfg->AllocateImageFrameType();
	pmfg->AllocateXRayDetails();
	pmfg->AllocatePixelMeasurement();

	/*
	 * Set Pixel spacing in MM for X and Y directions.
	 * Pixel spacing in the distance in MM between pixel centers.
	 */
	SDICOS::PixelMeasurement *pixelMeasurement = pmfg->GetPixelMeasurement();
	bRes = bRes && pixelMeasurement && pixelMeasurement->SetPixelSpacingInMM(	ptSpacing.y, //Row spacing
																				ptSpacing.x);//Column spacing
	
	/*
	 * Set slice thickness in MM
	 */
	bRes = bRes && pixelMeasurement && pixelMeasurement->SetSliceThicknessInMM(1.0f);
	
	/*
	 * Set plane orientation using cosines to define frame vectors.
	 */
	SDICOS::PlaneOrientation * planeOrientation = pmfg->GetPlaneOrientation();
	bRes = bRes && planeOrientation && planeOrientation->SetImageOrientation(	1,0,0, //Row Vector
																				0,1,0);//Column Vector

	/*
	* Set per-frame plane positions along the z-axis.
	*/
	SDICOS::Array1D<SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros> &vPerFrame = ct.GetMultiframeFunctionalGroups().GetPerFrameFunctionalGroups();

	vPerFrame.SetSize(vnVolume.GetDepth()); //Set the number of frames

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
	SDICOS::CTTypes::CTPixelValueTransformation * pixelValueTransform = pmfg->GetPixelValueTransformation();
	bRes = bRes && pixelValueTransform && pixelValueTransform->SetRescaleIntercept(-1000);
	bRes = bRes && pixelValueTransform && pixelValueTransform->SetRescaleSlope(1);
	
	/*
	 * String value indicating what the output units are after applying pixel transformation
	 */
	bRes = bRes && pixelValueTransform && pixelValueTransform->SetRescaleType("HU");
	
	/*
	 * Same as as call to ct.GetCTImage().SetImageTypeCT()
	 */
	SDICOS::CTTypes::CTImageFrameType * imageFrameType = pmfg->GetImageFrameType();
	bRes = bRes && imageFrameType && imageFrameType->SetFrameType(	SDICOS::CTTypes::CTImage::enumOriginal,
																	SDICOS::CTTypes::CTImage::enumPhotoelectric,
																	SDICOS::CTTypes::CTImage::enumVolume,
																	SDICOS::CTTypes::CTImage::enumNone);
	
	/*
	 * The CommonImageDescription data is shared between the CTImage and CTMultiframeFunctionalGroupMacros
	 */
	if(imageFrameType)
	{
		SDICOS::CommonImageDescription& description = imageFrameType->GetCommonImageDescription();
		description = *(ct.GetCTImage().GetCommonImageDescription());
	}
	
	/*
	 * The CTXRayDetails module is required if the first value in the CT Image Type attribute is ORIGINAL or MIXED.
	 * See CTImage::SetImageTypeCT which is set above by calling SetImageTypeCT
     */
	SDICOS::CTTypes::CTXRayDetails * xRayDetails = pmfg->GetXRayDetails();
	bRes = bRes && xRayDetails->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumLead);
	bRes = bRes && xRayDetails->SetFilterType(SDICOS::CTTypes::CTXRayDetails::enumNone);
	bRes = bRes && xRayDetails->SetFocalSpotSizeInMM(0);
	bRes = bRes && xRayDetails->SetKVP(0);

	/*
	 * The SDICOS::FrameOfReference class represents the Frame of Reference
	 * The Frame of Reference UID uniquely identifies a frame of reference for a series and 
	 * is a grouping to indicate that multiple series in a scan have the same frame of reference.
	 */
	SDICOS::DcsUniqueIdentifier frameOfReferenceUID;
	
	// Generate a randomized unique identifier
	frameOfReferenceUID.SetGUID();
	
	SDICOS::FrameOfReference& frame = ct.GetFrameOfReference();
	bRes = bRes && frame.SetFrameOfReferenceUID(frameOfReferenceUID);

	/*
	 * The ObjectOfInspectionModule class represents Object Of Inspection Module (OOI)
	 */
	SDICOS::ObjectOfInspectionModule& ooi = ct.GetObjectOfInspection();
	SDICOS::ObjectOfInspectionModule::IdInfo& idInfo = ooi.GetID();
	bRes = bRes && idInfo.SetID("TSS4.000314");
	bRes = bRes && idInfo.SetIdAssigningAuthority("Issuer-001");
	bRes = bRes && idInfo.SetIdType(SDICOS::ObjectOfInspectionModule::IdInfo::enumText);
	bRes = bRes && ooi.SetType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);

	/*
	 * The GeneralScanModule class represents the General Scan Module
	 */
	SDICOS::GeneralScanModule& generalScan = ct.GetGeneralScan();
	bRes = bRes && generalScan.SetScanID("TSS4.314");
	
	// Create unique identifier using static class method
	bRes = bRes && generalScan.SetScanInstanceUID(SDICOS::DcsUniqueIdentifier::CreateGUID());
	bRes = bRes && generalScan.SetStartDateAndTime(date,time);
	bRes = bRes && generalScan.SetType(SDICOS::GeneralScanModule::enumOperational);
	bRes = bRes && generalScan.SetDescription("MY SCAN DESCRIPTION");
	/*
	 * The GeneralEquipmentModule class represent the General Equipment Module
	 * Required information about the machine the scan was captured on.
	 */
	SDICOS::GeneralEquipmentModule& generalEquipment = ct.GetGeneralEquipment();
	bRes = bRes && generalEquipment.SetCalibrationDateAndTime(date,time);
	bRes = bRes && generalEquipment.SetDeviceSerialNumber("FooBar-001");
	bRes = bRes && generalEquipment.SetMachineAddress("1600 Pennsylvania Ave");
	bRes = bRes && generalEquipment.SetMachineID("007");
	bRes = bRes && generalEquipment.SetMachineLocation("Check Point 1");
	bRes = bRes && generalEquipment.SetManufacturer("Stratovan");
	bRes = bRes && generalEquipment.SetManufacturerModelName("HAL");
	bRes = bRes && generalEquipment.SetSoftwareVersion("3.14");

	/*
		XRayEquipmentModule represents the X-Ray Equipment Module
		Attribute related to the device's grating and detectors using X-Ray Image acquisition.
	*/
	SDICOS::XRayEquipmentModule& XRayEquipment = ct.GetXRayEquipment();
	bRes = bRes && CreateXRayEquipment(XRayEquipment);

	/*
	 * The SOPCommonModule class represents the SOP Common Module
	 * which defines attributes for identifying associated Service Object Pair (SOP) instances
	 */
	SDICOS::SopCommonModule& sopCommon = ct.GetSopCommon();
	bRes = bRes && sopCommon.SetSopInstanceCreationDateAndTime(date,time);
	
	SDICOS::DcsUniqueIdentifier sopInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.881");
	bRes = bRes && sopCommon.SetSopInstanceUID(sopInstanceUID);

	/*
	 * The CommonInstanceReferenceModule class represents the Common Instance Reference Module
	 * which describes the relationships between SOP Instances referenced between modules in the same instance.
	 * In this example, we have one scan with one series.
	 */
	SDICOS::CommonInstanceReferenceModule& commonInstanceRef = ct.GetCommonInstanceReference();
	commonInstanceRef.AllocateReferencedSeries();
	
	SDICOS::ReferencedSeriesSequence * refSeries = commonInstanceRef.GetReferencedSeries();
	bRes = bRes && (S_NULL != refSeries);
	
	if(refSeries)
	{
		SDICOS::Array1D<SDICOS::ReferencedSeriesSequence::ReferencedSeries> & referencedSeries = refSeries->GetReferencedSeries();
		bRes = bRes && referencedSeries.SetSize(1);

		//
		// This Series Instance UID matches the one for the original CTSeries
		// indicating that the CTSeries is referenced here
		//
		bRes = bRes && referencedSeries[0].SetSeriesInstanceUID(instanceUID);

		SDICOS::Array1D<SDICOS::SopInstanceReference>& referencedInstances = referencedSeries[0].GetReferencedInstances();
		bRes = bRes && referencedInstances.SetSize(1);
		bRes = bRes && referencedInstances[0].SetClassUID(SDICOS::SOPClassUID::GetCT());
		
		// Specify UID with a user defined string
		bRes = bRes && referencedInstances[0].SetInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.885");
	}
	
	const SDICOS::Filename filename("CTvolume.dcs");

	// Alternatively a Filename can be specified with a folder and name
/*
	SDICOS::Folder folder("C:\temp");
	SDICOS::Filename(folder,"CTvolume.dcs");
*/
	
	/*
	 * The ErrorLog class stores warning and errors from the validation process
	 */
	SDICOS::ErrorLog errorlog;
	
	/*
	 * Writing the CT file validates the CT object and reports errors in the
	 * supplied ErrorLog
	 */
	if(!ct.Write(filename, SDICOS::DicosFile::enumLittleEndianExplicit, errorlog)) 
	{
		errorlog.WriteLog("CTErrorLog.txt");
		std::cout << "Failed to write CT DICOS File " << filename << " Writing Errors to CTErrorLog.txt" << std::endl;
		std::cout << errorlog << std::endl;
	} 
	else 
	{
		std::cout << "Wrote CT DICOS File " << filename << std::endl;
	}

	errorlog.FreeMemory();
	
	//
	// Read the DICOS file from disk using the AttributeManager object
	//
	SDICOS::AttributeManager manager;
	if(SDICOS::DicosFile::Read(filename, errorlog, manager)) 
	{
		manager.WriteToFileAsText("CTListings.txt");
		std::cout << "Write Attribute Listing to CTListings.txt" << std::endl;
	} 
	else 
	{
		std::cout << "Failed to read as DICOS file " << filename << std::endl;
		std::cout << errorlog << std::endl;
		bRes = false;
	}

	//
	// Reading the CT object from disk validates it and reports errors
	// in the supplied ErrorLog.
	//
	SDICOS::CTModule ctRead;
	SDICOS::ErrorLog errorlogRead;
	if(!ctRead.Read(filename, errorlogRead))
	{
		std::cout << "Failed to read as CT object " << filename << std::endl;
		std::cout << errorlogRead << std::endl;
		bRes = false;
	} 
	else 
	{
		std::cout << "Read CT from " << filename << std::endl;
		bRes = bRes && ct == ctRead;
		if(bRes) 
		{
			std::cout << "Verified written and read CT files are equivalent" << std::endl;
		} 
		else 
		{
			std::cout << "Failed to verify that written and read CT files are equivalent" << std::endl;
		}
	}

	return bRes;
} // EndCreateCT

int main()
{
	bool bResult = CreateCT();
	return (bResult ? 0 : 1);
}
