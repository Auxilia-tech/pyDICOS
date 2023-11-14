//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2018 Stratovan Corporation. All Rights Reserved.
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
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>

#include "SDICOS/DICOS.h"

void InitCT(SDICOS::CTModule &ct);

bool CreateCT()
{   
	SDICOS::CTModule ct; //Module-Level CT

	InitCT(ct); //Fills CT with data
    
	/*
	* Define the type of TIP image
	*
	*	Valid Types:
	*	SDICOS::TipImage::enumFTI Fictitious Threat Image - Image Type is a fictitious threat image to be projected onto a scan of an OOI
	*	SDICOS::TipImage::enumCTI Composite Threat Image  - Image Type is an image to be presented
	*/
    SDICOS::TipImage tip_image; 
    tip_image.SetTipImageType(SDICOS::TipImage::enumCTI); 
    ct.SetTipImage(tip_image);
    
    SDICOS::CTModule ct2 = ct;
    
    const SDICOS::Filename filename("CTvolume.dcs");

    // Alternatively a Filename can be specified with a folder and name
    //SDICOS::Folder folder("C:\\temp");
    //SDICOS::Filename(folder,"CTvolume.dcs");
    
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
        return false;
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
		return false;
    } 
	else 
	{
        std::cout << "Read CT from " << filename << std::endl;

        if(ct == ctRead) 
		{
            std::cout << "Verified written and read CT files are equivalent" << std::endl;
        } 
		else 
		{
            std::cout << "Failed to verify that written and read CT files are equivalent" << std::endl;
			return false;
		}
    }

    return true;
} // EndCreateCT



int main(int argc, char** argv) 
{
    
    if (CreateCT()) 
	{
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}

// Utility function to initialize data for example
void InitCT(SDICOS::CTModule &ct)
{
	SDICOS::DcsDateTime dateTime;
	SDICOS::DcsDate date;
	SDICOS::DcsTime time;
	SDICOS::Point3D<float> ptOrigin(1.0f, 2.0f, 3.0f);
	SDICOS::Point3D<float> ptSpacing(0.1f, 0.1f, 0.5f);
	SDICOS::Array3DLarge<float> vnVolume;

	const SDICOS::S_UINT32 width(5), height(5), depth(5);
	vnVolume.SetSize(width, height, depth);
	vnVolume.Zero(0);

	date.SetToday();
	time.SetNow();
	dateTime.Set(date, time);

	SDICOS::CTTypes::CTImage &image = ct.GetCTImage();

	SDICOS::CTTypes::CTSeries &series = ct.GetSeries();
	series.SetAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful);
	series.SetDateAndTime(date, time);

	//
	// Set the Unique ID of the Scan for the CTSeries.
	//
	SDICOS::DcsUniqueIdentifier instanceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370732.880");
	series.SetInstanceUID(instanceUID);

	image.SetPixelData(vnVolume);
	image.SetAcquisitionDateAndTime(dateTime);
	image.SetBurnedInAnnotation(false);

	image.SetCoordinateSystem(SDICOS::ImageCommon::enumLHS);
	image.SetImageOrigin(SDICOS::ImageCommon::enumMachine);

	/*
	* See the documentation for SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION
	*/
	image.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);

	/*
	* The CT Image Type attribute contains 4 values.
	*/
	image.SetImageTypeCT(SDICOS::CTTypes::CTImage::enumOriginal,
		SDICOS::CTTypes::CTImage::enumPhotoelectric,
		SDICOS::CTTypes::CTImage::enumVolume,
		SDICOS::CTTypes::CTImage::enumNone);
	image.SetAcquisitionDuration(30);

	SDICOS::CommonImageDescription * commonImageDescription = image.GetCommonImageDescription();
	commonImageDescription->SetPixelPresentation(SDICOS::CommonImageDescription::enumPP_Monochrome);
	commonImageDescription->SetVolumeBasedCalculationTechnique(SDICOS::CommonImageDescription::enumVC_None);
	commonImageDescription->SetVolumetricProperties(SDICOS::CommonImageDescription::enumVP_Volume);

	/*
	* The CTTypes::CTMultiframeFunctionalGroups class is the CT Specific implementation of the MultiframeFunctionalGroups (Table 109) module
	* with the CT Specific Multiframe Functional Groups in Table 15
	*/
	SDICOS::CTTypes::CTMultiframeFunctionalGroups& multiframeFunctionalGroups = ct.GetMultiframeFunctionalGroups();
	multiframeFunctionalGroups.SetNumberOfFrames(vnVolume.GetDepth());
	multiframeFunctionalGroups.SetContentDateAndTime(date, time);
	multiframeFunctionalGroups.SetInstanceNumber(1001);

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
	pixelMeasurement->SetPixelSpacingInMM(ptSpacing.x, ptSpacing.y);

	/*
	* Set slice thickness in MM (Z direction)
	*/
	pixelMeasurement->SetSliceThicknessInMM(1.0f);

	/*
	* Set plane orientation using cosines to define frame vectors.
	*/
	SDICOS::PlaneOrientation * planeOrientation = pmfg->GetPlaneOrientation();
	planeOrientation->SetImageOrientation(1, 0, 0, 0, 1, 0);

	/*
	* Set plane per frame positions along the z-axis.
	*/
	SDICOS::Array1D<SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros> &vPerFrame = ct.GetMultiframeFunctionalGroups().GetPerFrameFunctionalGroups();

	vPerFrame.SetSize(vnVolume.GetDepth());

	for (SDICOS::S_UINT32 nFrame(0); nFrame < vPerFrame.GetSize(); ++nFrame)
	{
		SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros &mfgm = vPerFrame[nFrame];
		mfgm.AllocatePlanePosition();
		mfgm.GetPlanePosition()->SetPositionInMM(ptOrigin.x, ptOrigin.y, ptOrigin.z + ptSpacing.z * float(nFrame));
	}

	/*
	* The PixelValueTransformation specifies a linear transform applied to the
	* stored values to produce values in the output units.
	*/
	SDICOS::CTTypes::CTPixelValueTransformation * pixelValueTransform = pmfg->GetPixelValueTransformation();
	pixelValueTransform && pixelValueTransform->SetRescaleIntercept(-1000);
	pixelValueTransform && pixelValueTransform->SetRescaleSlope(1);

	/*
	* String value indicating what the output units are after applying pixel transformation
	*/
	pixelValueTransform && pixelValueTransform->SetRescaleType("HU");

	/*
	* Same as as call to ct.GetCTImage().SetImageTypeCT()
	*/
	SDICOS::CTTypes::CTImageFrameType * imageFrameType = pmfg->GetImageFrameType();
	imageFrameType && imageFrameType->SetFrameType(SDICOS::CTTypes::CTImage::enumOriginal,
		SDICOS::CTTypes::CTImage::enumPhotoelectric,
		SDICOS::CTTypes::CTImage::enumVolume,
		SDICOS::CTTypes::CTImage::enumNone);

	/*
	* The CommonImageDescription data is shared between the CTImage and CTMultiframeFunctionalGroupMacros
	*/
	if (imageFrameType)
	{
		SDICOS::CommonImageDescription& description = imageFrameType->GetCommonImageDescription();
		description = *(ct.GetCTImage().GetCommonImageDescription());
	}

	/*
	* The CTXRayDetails module is required if the first value in the CT Image Type attribute is ORIGINAL or MIXED.
	* See CTImage::SetImageTypeCT which is set above by calling SetImageTypeCT
	*/
	SDICOS::CTTypes::CTXRayDetails * xRayDetails = pmfg->GetXRayDetails();
	xRayDetails->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumLead);
	xRayDetails->SetFilterType(SDICOS::CTTypes::CTXRayDetails::enumNone);
	xRayDetails->SetFocalSpotSizeInMM(0);
	xRayDetails->SetKVP(0);

	/*
	* The SDICOS::FrameOfReference class represents the Frame of Reference (Table 107)
	* The Frame of Reference UID uniquely identifies a frame of reference for a series and
	* is a grouping to indicate that multiple series in a scan have the same frame of reference.
	*/
	SDICOS::DcsUniqueIdentifier frameOfReferenceUID;

	// Generate a randomized unique identifier
	frameOfReferenceUID.SetGUID();

	SDICOS::FrameOfReference& frame = ct.GetFrameOfReference();
	frame.SetFrameOfReferenceUID(frameOfReferenceUID);

	/*
	* The ObjectOfInspectionModule class represents Object Of Inspection Module (OOI) (Section 4.1, Table 10)
	*/
	SDICOS::ObjectOfInspectionModule& ooi = ct.GetObjectOfInspection();
	SDICOS::ObjectOfInspectionModule::IdInfo& idInfo = ooi.GetID();
	idInfo.SetID("TSS4.000314");
	idInfo.SetIdAssigningAuthority("Issuer-001");
	idInfo.SetIdType(SDICOS::ObjectOfInspectionModule::IdInfo::enumText);
	ooi.SetType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);

	/*
	* The GeneralScanModule class represents the General Scan Module (Section 5 Table 12)
	*/
	SDICOS::GeneralScanModule& generalScan = ct.GetGeneralScan();
	generalScan.SetScanID("TSS4.314");

	// Create unique identifier using static class method
	generalScan.SetScanInstanceUID(SDICOS::DcsUniqueIdentifier::CreateGUID());
	generalScan.SetStartDateAndTime(date, time);
	generalScan.SetType(SDICOS::GeneralScanModule::enumOperational);
	generalScan.SetDescription("MY SCAN DESCRIPTION");

	/*
	* The GeneralEquipmentModule class represent the General Equipment Module (Table 70)
	* Required information about the machine the scan was captured on.
	*/
	SDICOS::GeneralEquipmentModule& generalEquipment = ct.GetGeneralEquipment();
	generalEquipment.SetCalibrationDateAndTime(date, time);
	generalEquipment.SetDeviceSerialNumber("001");
	generalEquipment.SetMachineAddress("Ave");
	generalEquipment.SetMachineID("007");
	generalEquipment.SetMachineLocation("Check Point 1");
	generalEquipment.SetManufacturer("Stratovan");
	generalEquipment.SetManufacturerModelName("HAL");
	generalEquipment.SetSoftwareVersion("3.14");

	/*
	* The SOPCommonModule class represents the SOP Common Module (Table 82)
	* which defines attributes for identifying associated Service Object Pair (SOP) instances
	*/
	SDICOS::SopCommonModule& sopCommon = ct.GetSopCommon();
	sopCommon.SetSopInstanceCreationDateAndTime(date, time);

	SDICOS::DcsUniqueIdentifier sopInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.881");
	sopCommon.SetSopInstanceUID(sopInstanceUID);
}
