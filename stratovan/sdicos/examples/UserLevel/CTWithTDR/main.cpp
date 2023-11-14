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
//
// This example creates a CT volume and uses a TDR to identify 2 Potential Threat Objects (PTO's)
// within that CT volume.  The CT only holds the original volume and not threat information.
// The TDR holds all the threat information and must contain information to identify the CT with
// the original volume.
// The CT volume data is manually created for this example.
//
#include "SDICOS/DICOS.h"	//DICOS include header
#include <iostream>

int main()
{
	bool bRes(true);
	SDICOS::CT	ct;		//CT will hold the original volume data
	SDICOS::TDR tdr;	//TDR will define the threats found in the CT volume
	const SDICOS::DcsDate strDate(SDICOS::DcsDate::Today());	//Constant for today's date
	const SDICOS::DcsTime strTime(SDICOS::DcsTime::Now());		//Constant for current time
	SDICOS::Vector3D<float> vecRowOrientation;		//Vector for row orientation
	SDICOS::Vector3D<float> vecColumnOrientation;	//Vector for column orientation
	SDICOS::S_UINT16 nPTOIdentifier1(0), nPTOIdentifier2(1); // Unique IDs for PTOs

	//////////////////
	//Initialize CT

	//The four UID's and ID's set below will be used by the TDR
	bRes = bRes && ct.SetOOIID("10");	//Object of Inspection ID
	ct.GenerateSopInstanceUID();		//Obtain an SOP Instance UID
	ct.GenerateScanInstanceUID();		//Obtain an SOP Scan Instance UID
	ct.GenerateSeriesInstanceUID();		//Obtain an SOP Series Instance UID

	bRes = bRes && ct.SetImageAcquisitionDateAndTime(strDate, strTime);	//Date and time of volume acquisition
	ct.SetBurnedInAnnotation(false);									//No burned-in annotations

	//Low values in volume data correspond to low intensity values
	bRes = bRes && ct.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);	
	
	bRes = bRes && ct.SetImageType(SDICOS::CTTypes::CTImage::enumPhotoelectric); //Photoelectric acquisition
	bRes = bRes && ct.SetImageAcquisitionDuration(5000);		//Time taken for acquisition
	bRes = bRes && ct.SetContentDateAndTime(strDate, strTime);	//Date and time of content acquisition
	bRes = bRes && ct.SetOOIIDAssigningAuthority("OOI ID Assigning Authority");	//Name of OOI ID assigning authority
	bRes = bRes && ct.SetOOIIDType(SDICOS::ObjectOfInspectionModule::IdInfo::enumRFID); //OOI ID corresponds to an RFID
	bRes = bRes && ct.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage); //OOI is baggage
	bRes = bRes && ct.SetScanID("Scan ID"); //Scan ID
	bRes = bRes && ct.SetScanStartDateAndTime(strDate, strTime); //Date and time scan started
	bRes = bRes && ct.SetScanType(SDICOS::GeneralScanModule::enumOperational); //Operational scan
	bRes = bRes && ct.SetSeriesDateAndTime(strDate, strTime);	//Date and time of series creation
	bRes = bRes && ct.SetSeriesAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful); //Acquisition was successfully captured
	bRes = bRes && ct.SetDeviceCalibrationDateAndTime(strDate, strTime); //Date and time of device calibration
	bRes = bRes && ct.SetDeviceSerialNumber("123456987");	//Device serial number
	bRes = bRes && ct.SetMachineAddress("Machine Address"); //Machine address (Physical address)
	bRes = bRes && ct.SetMachineLocation("Machine Location");//Machine location (Location on site)
	bRes = bRes && ct.SetMachineID("Machine ID"); //Machine ID
	bRes = bRes && ct.SetDeviceManufacturer("Device Manufacturer"); //Device manufacturer
	bRes = bRes && ct.SetDeviceManufacturerModelName("Device Manufacturer Model Name");	//Model name
	bRes = bRes && ct.SetDeviceSoftwareVersion("Device Software Version"); //Device's software version
	bRes = bRes && ct.SetSopInstanceCreationDateAndTime(strDate, strTime); //Date and time of SOP instance creation

	ct.SetNumberOfSections(1);	//Create a single section
	SDICOS::Section *psection = ct.GetSectionByIndex(0);	//Get a reference to the section

	psection->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumAluminum); //Aluminum filter
	psection->SetFocalSpotSizeInMM(10); //10mm nominal focal spot size
	psection->SetKVP(7000); // 7000 Peak Kilo Voltage

	vecRowOrientation.Set(1,0,0);//X-Axis points right
	vecColumnOrientation.Set(0,1,0);  //Y-Axis points down

	//Image plane orientation defines the axis from the top left corner of each slice.
	//Row Orientation corresponds to X-Axis (left to right) and column orientation corresponds to Y-axis (top to bottom).
	psection->SetPlaneOrientation(vecRowOrientation, vecColumnOrientation); 

	psection->GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, 500, 500, 500);	//Create a 500x500x500 volume
	psection->GetPixelData().GetUnsigned16()->Zero(0);				//Initialize all values to 0

	//First frame's position: Left (x = -250), Top (y = -250), Front (z = -250)
	//Last frame's position: Left (x = -250), Top (y = -250), Back (z = +250)
	const SDICOS::Point3D<float> ptFirstFrameTopLeft(-250,-250,-250);

	//Define the real world coordinate of the first frame's top left corner
	psection->SetPositionInMM(ptFirstFrameTopLeft); 
	psection->SetSpacingInMM(1.0f,1.0f,1.0f); //Volume data voxel spacing

	const SDICOS::Point3D<SDICOS::S_UINT16> ptCenter(250,250,250); //Volume index for center position

	///////////////////////////////////////
	//Manually create shapes in the volume
	const SDICOS::S_UINT16 nWhite(0xFFFF); //Constant for white
	SDICOS::Array3DLarge<SDICOS::S_UINT16> &vVolume = *psection->GetPixelData().GetUnsigned16(); //Reference to volume data
	SDICOS::Point3D<SDICOS::S_UINT16> ptPos; //Index for volume
		
	//Rectangle on left-top-front(-X,-Y,-Z) corner of volume. Bounding box corners: (-250, -250, -250), (-200, -230, -50)
	
	for(ptPos.z = 0 ; ptPos.z <= 200 ; ++ptPos.z)
	{
		SDICOS::Array2D<SDICOS::S_UINT16>* pSlice = vVolume.GetSlice(ptPos.z);
		for(ptPos.y = 0 ; ptPos.y <= 20 ; ++ptPos.y)
		{
			SDICOS::S_UINT16 *pvoxel = pSlice->GetBuffer() + (ptPos.y * pSlice->GetWidth());
			for(ptPos.x = 0 ; ptPos.x <= 50 ; ++ptPos.x, ++pvoxel)
				*pvoxel = nWhite;
		}
	}

	//Center block. Bounding box corners (-40, -40, -40), (40, 40, 40)
	for(ptPos.z = (ptCenter.z-40) ; ptPos.z <= (ptCenter.z+40) ; ++ptPos.z)
	{
		SDICOS::Array2D<SDICOS::S_UINT16> *pSlice = vVolume.GetSlice(ptPos.z);
		for(ptPos.y = (ptCenter.y-40); ptPos.y <= (ptCenter.y+40) ; ++ptPos.y)
		{
			ptPos.x = (ptCenter.x-40);
			SDICOS::S_UINT16 *pvoxel = pSlice->GetBuffer() + (ptPos.y * pSlice->GetWidth()) + ptPos.x;
			for(; ptPos.x <= (ptCenter.x+40) ; ++ptPos.x, ++pvoxel)
				*pvoxel = nWhite;
		}
	}

	//Small block to the right of the center block. Bounding box corners (40, -5, -5), (50, 5, 5)
	//pSlice = vVolume.GetBuffer();
	for(ptPos.z = (ptCenter.z-5) ; ptPos.z <= (ptCenter.z+5) ; ++ptPos.z)
	{
		SDICOS::Array2D<SDICOS::S_UINT16> *pSlice = vVolume.GetSlice(ptPos.z);
		for(ptPos.y = (ptCenter.y-5); ptPos.y <= (ptCenter.y+5) ; ++ptPos.y)
		{
			ptPos.x = (ptCenter.x+40);
			SDICOS::S_UINT16 *pvoxel = pSlice->GetBuffer() + (ptPos.y * pSlice->GetWidth()) + ptPos.x;
			for(; ptPos.x <= (ptCenter.x+50) ; ++ptPos.x, ++pvoxel)
				*pvoxel = nWhite;
		}
	}

	if (!bRes)
	{
		std::cout << "\nError setting CT values" << std::endl;
		return 10;
	}

	bRes = true;

	///////////////////////////////////////////////////////
	//Initialize the TDR and link to the CT created above

	//Link the TDR to the same object of inspection, scan, and series as the CT
	bRes = bRes && tdr.SetOOIID(ct.GetOOIID());								//Same Object of Inspection ID as CT
	bRes = bRes && tdr.SetScanInstanceUID(ct.GetScanInstanceUID());			//Same Scan Instance UID as CT
	bRes = bRes && tdr.SetSeriesInstanceUID(ct.GetSeriesInstanceUID());		//Same Series Instance UID as CT

	tdr.GenerateSopInstanceUID(); //Generate the SOP Instance UID

	//Set same Frame of Reference UID as CT
	bRes = bRes && tdr.SetFrameOfReferenceUID(ct.GetFrameOfReferenceUID());

	//////////////////
	//Add 2 PTO's
	{
		//Set both as baggage threats since the CT is of baggage
		bRes = bRes && tdr.AddPotentialThreatObject(nPTOIdentifier1, SDICOS::TDR::enumThreatTypeBaggage);
		bRes = bRes && tdr.AddPotentialThreatObject(nPTOIdentifier2, SDICOS::TDR::enumThreatTypeBaggage);

		//Link both PTO's to objects in the CT by identifying the CT's SOP instance UID and SOP class UID.
		//Each PTO in a TDR can reference one or more scans by its SOP instance UID. The PTO will use the exact
		//same information (ie. bounding box, offset, etc.) for each referenced scan.
		bRes = bRes && tdr.AddReferencedInstance(nPTOIdentifier1, ct.GetSopClassUID(), ct.GetSopInstanceUID(), 0);
		bRes = bRes && tdr.AddReferencedInstance(nPTOIdentifier2, ct.GetSopClassUID(), ct.GetSopInstanceUID(), 0);

		//PTO 0
		bRes = bRes && tdr.AddPTOAssessment(
			nPTOIdentifier1,	//Index to first PTO
			SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat,			//Bag contains a threat
			SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumProhibitedItem,	//Threat is a prohibited item
			SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference,	//No interference occurred during threat evaluation
			"Weapon",			//Additional threat description
			float(98.0f / 100.0f)	//98% Assessment Probability
		);

		//PTO 1
		bRes = bRes && tdr.AddPTOAssessment(nPTOIdentifier2, 	//Index to second PTO
			SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoThreat);//Bag does not contain a threat

		SDICOS::Array1D< SDICOS::Point3D<float> > bounds; //Bounds for threat objects in PTO

		bounds.SetSize(2);	//Bounds with only 2 points will define the opposite corners 
		//of the bounding box containing the threat

		//PTO 0 real world coordinate bounds (-250, -250, -250), (-200, -230, -50)
		bounds[0].Set(-250, -250, -250);
		bounds[1].Set(-200, -230, -50);
		bRes = bRes && tdr.SetThreatBoundingPolygon(0, bounds, 0);

		//PTO 1 bounds (-40, -40, -40), (40, 40, 40)
		bounds[0].Set(-40.0f, -40.0f, -40.0f);
		bounds[1].Set(40.0f, 40.0f, 40.0f);
		bRes = bRes && tdr.SetThreatBoundingPolygon(1, bounds, 0);

		//Offset and dimensions for a PTO's region of interest bitmask volume
		SDICOS::Point3D<float> ptBase;
		SDICOS::Point3D<float> ptExtents;

		//PTO 0: Mark the region of interest for the corner object
		//The parameter 'ptBase' specifies the voxel offset into the volume data where the PTO is located
		//The parameter 'ptExtents' specifies the bounding box in voxels from 'ptBase'
		//The bitmask volume is not specified, which is interpreted the same way as a bitmask volume filled with 1's
		//with the same dimensions defined by ptExtents
		ptBase.Set(1, 2, 3);
		ptExtents.Set(50, 20, 200);
		// Passing the default constructed bitmap indicates the entire region is defined as the PTO
		bRes = bRes && tdr.SetThreatRegionOfInterest(nPTOIdentifier1, ptBase, ptExtents, SDICOS::Bitmap(), 0);
		bRes = bRes && tdr.SetBaggagePTODetails(nPTOIdentifier1, 1000, 5000, 0);
		bRes = bRes && tdr.SetBaggagePTOLocationDescription(nPTOIdentifier1, "Corner Object", 0);

		//PTO 1: Mark the region of interest for the center object
		//The parameter 'ptBase' specifies the voxel offset into the volume data where the PTO is located
		//The parameter 'ptExtents' specifies the bounding box in voxels from 'ptBase'
		//The bitmask volume is not specified, which is interpreted the same way as a bitmask volume filled with 1's
		//with the same dimensions defined by ptExtents
		ptBase.Set(210, 210, 210);
		ptExtents.Set(81, 81, 81);
		// Passing the default constructed bitmap indicates the entire region is defined as the PTO
		bRes = bRes && tdr.SetThreatRegionOfInterest(nPTOIdentifier2, ptBase, ptExtents, SDICOS::Bitmap(), 0);
		bRes = bRes && tdr.SetBaggagePTODetails(nPTOIdentifier2, 20, 2, 0);
		bRes = bRes && tdr.SetBaggagePTOLocationDescription(nPTOIdentifier2, "Corner Object", 0);

		//Set required processing time metrics for PTOs
		bRes = bRes && tdr.SetProcessingStartTime(nPTOIdentifier1, SDICOS::DcsDateTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()));
		bRes = bRes && tdr.SetProcessingEndTime(nPTOIdentifier1, SDICOS::DcsDateTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()));
		bRes = bRes && tdr.SetProcessingStartTime(nPTOIdentifier2, SDICOS::DcsDateTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()));
		bRes = bRes && tdr.SetProcessingEndTime(nPTOIdentifier2, SDICOS::DcsDateTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()));
		
	}
	/*
		IMPORTANT: If no PTOs are created for a given scan, add a reference to that scan with:

			tdr.AddReferencedSopInstance(ct.GetSopInstanceUID(), ct.GetSopClassUID());

		Adding this reference is required for TDRs as of DICOS V03.
	*/

	bRes = bRes && tdr.SetInstanceNumber(0);	//Instance number
	bRes = tdr.SetContentDateAndTime(strDate, strTime);	//Date and time of content creation
	bRes = bRes && tdr.SetTDRType(SDICOS::TDRTypes::ThreatDetectionReport::enumMachine); //TDR generated by an ATR machine
	bRes = bRes && tdr.SetTDRTypeATR("ATR Manufacturer", "ATR Version"); //ATR manufacturer and version

	//Relative scaling between the representative figure and the image stored in the PTO
	bRes = bRes && tdr.SetImageScaleRepresentation(1);	

	bRes = bRes && tdr.SetAlarmDecision(SDICOS::TDRTypes::ThreatDetectionReport::enumAlarm); //Alarm decision for the bag
	bRes = bRes && tdr.SetAlarmDecisionDateTime(strDate, strTime); //Date and time of alarm decision
	bRes = bRes && tdr.SetAbortFlag(SDICOS::TDRTypes::ThreatDetectionReport::enumSuccess); //No abort
	bRes = bRes && tdr.SetTotalProcessingTimeInMS(50); //Processing time for TDR
	bRes = bRes && tdr.SetOOIIDAssigningAuthority(ct.GetOOIIDAssigningAuthority()); //Set same OOI ID assigning authority as CT
	bRes = bRes && tdr.SetOOIIDType(ct.GetOOIIDType()); //Set same OOI ID type as CT
	bRes = bRes && tdr.SetOOIType(ct.GetOOIType());//Set same OOI type type as CT
	bRes = bRes && tdr.SetScanID(ct.GetScanID());//Set same scan ID type type as CT
	bRes = bRes && tdr.SetScanStartDateAndTime(ct.GetScanStartDate(), ct.GetScanStartTime()); //Set date and time of scan start
	bRes = bRes && tdr.SetScanType(ct.GetScanType()); //Set same scan type as CT
	bRes = bRes && tdr.SetSeriesDateAndTime(ct.GetSeriesDate(), ct.GetSeriesTime()); //Set same date and time of series creation as CT
	bRes = bRes && tdr.SetSeriesAcquisitionStatus(ct.GetSeriesAcquisitionStatus()); //Set same series acquisition status
	bRes = bRes && tdr.SetDeviceCalibrationDateAndTime(strDate, strTime); //TDR device calibration date and time
	bRes = bRes && tdr.SetDeviceSerialNumber("TDR Serial Number"); //TDR device's serial number
	bRes = bRes && tdr.SetMachineAddress("TDR machine address"); //TDR machine address
	bRes = bRes && tdr.SetMachineLocation("TDR machine location"); //TDR machine location
	bRes = bRes && tdr.SetMachineID("TDR machine ID"); //TDR machine ID
	bRes = bRes && tdr.SetDeviceManufacturer("TDR device manufacturer"); //TDR device manufacturer
	bRes = bRes && tdr.SetDeviceManufacturerModelName("TDR model name"); //TDR model name
	bRes = bRes && tdr.SetDeviceSoftwareVersion("TDR software version"); //TDR software version
	bRes = bRes && tdr.SetSopInstanceCreationDateAndTime(strDate, strTime); //TDR SOP instance UID creation date and time

	if (!bRes)
	{
		std::cout << "\nError setting TDR values" << std::endl;
	}

	////////////////////////////
	//Write files to disk

	SDICOS::Folder folder(SDICOS::GetExecutableFolder().GetFullFolder() + "..\\..\\..\\..\\DataFiles\\CTwithTDR");
	SDICOS::Filename filenameCT(folder, "CT.dcs");
	SDICOS::Filename filenameTDR(folder, "TDR.dcs");
	SDICOS::ErrorLog errorlogCT;
	SDICOS::ErrorLog errorlogTDR;

	//Write CT
	if(!ct.Write(filenameCT, errorlogCT))
	{
		std::cout<<"\nFailed writing CT (CTwithTDR)"<<std::endl;
		std::cout<<errorlogCT<<std::endl;
		return 1;
	}
	else
		std::cout<<"CT write completed (CTwithTDR)"<<std::endl;

	//Write TDR
	if(!tdr.Write(filenameTDR, errorlogTDR, SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cout<<"\nFailed writing TDR (CTwithTDR)"<<std::endl;
		std::cout<<errorlogTDR<<std::endl;
		return 2;
	}
	else
		std::cout<<"TDR write completed (CTwithTDR)"<<std::endl;

	return (bRes ? 0 : 3);
}
///Endmain
