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
// This example shows how to utilize the User-Level API in order to send a 
// CT object over the network.
//
#include "SDICOS/DICOS.h" // DICOS include header
#include <iostream>

//Initialize CT data
void InitCT(SDICOS::CT &ct);

int main()
{
	SDICOS::CT ct;		// User-Level API CT object
	SDICOS::ErrorLog errorlog;	// Error log

	// Initialize the CT object
	InitCT(ct);

	// Send the CT object over the network to a server
	// Sends uncompressed data.
	// SendOverNetwork() is a blocking call.
	if(!ct.SendOverNetwork(	1000,		// Port
							"1.1.1.1",	// IP Address
							"SrcApp",	// Source Application Name. Name of application using calling this function.
							"DstApp",	// Destination Application Name. Name of application accepting the client's connection.
							errorlog))	// Error log
	{
		//Print error log if the transmission fails
		std::cout<<"Failed to send data across network:"<<std::endl;
		std::cout<<errorlog<<std::endl;
		return 1;
	}

	return 0;
}

// Initialize a CT object with User-Level API
void InitCT(SDICOS::CT &ct)
{
	const SDICOS::DcsDate strDate(SDICOS::DcsDate::Today()); 
	const SDICOS::DcsTime strTime(SDICOS::DcsTime::Now());
	SDICOS::Vector3D<float> vecRowOrientation;
	SDICOS::Vector3D<float> vecColumnOrientation;

	ct.FreeMemory();

	vecRowOrientation.Set(1,0,0);
	vecColumnOrientation.Set(0,1,0);

	ct.SetFrameOfReferenceUID("4.4.6.6.0.0.8.8.7");
	ct.SetImageAcquisitionDateAndTime(strDate, strTime);
	ct.SetBurnedInAnnotation(false);
	ct.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);
	ct.SetImageType(SDICOS::CTTypes::CTImage::enumPhotoelectric);
	ct.SetImageAcquisitionDuration(5000);
	ct.SetContentDateAndTime(strDate, strTime);
	ct.SetOOIID("10");
	ct.SetOOIIDAssigningAuthority("OOI ID Assigning Authority");
	ct.SetOOIIDType(SDICOS::ObjectOfInspectionModule::IdInfo::enumRFID);
	ct.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);
	ct.SetScanID("Scan ID");
	ct.GenerateScanInstanceUID();
	ct.SetScanStartDateAndTime(strDate, strTime);
	ct.SetScanType(SDICOS::GeneralScanModule::enumOperational);
	ct.GenerateSeriesInstanceUID();
	ct.SetSeriesDateAndTime(strDate, strTime);
	ct.SetSeriesAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful);
	ct.SetDeviceCalibrationDateAndTime(strDate, strTime);
	ct.SetDeviceSerialNumber("123456987");
	ct.SetMachineAddress("Machine Address");
	ct.SetMachineLocation("Machine Location");
	ct.SetMachineID("Machine ID");
	ct.SetDeviceManufacturer("Device Manufacturer");
	ct.SetDeviceManufacturerModelName("Device Manufacturer Model Name");
	ct.SetDeviceSoftwareVersion("Device Software Version");
	ct.SetSopInstanceCreationDateAndTime(strDate, strTime);
	ct.GenerateSopInstanceUID();

	SDICOS::Section *psection = S_NULL;

	ct.SetNumberOfSections(1);
	psection = ct.GetSectionByIndex(0);

	psection->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumAluminum);
	psection->SetFocalSpotSizeInMM(10);
	psection->SetKVP(7000);
	psection->SetPlaneOrientation(vecRowOrientation, vecColumnOrientation);
	psection->SetPositionInMM(0,0,2000);
	psection->SetSpacingInMM(1,1,1);
	psection->GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, 500, 500, 500);
	psection->GetPixelData().GetUnsigned16()->Zero(20);
}
