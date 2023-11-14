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
// This example utilizes the user-level API to create a QR DICOS file
//
#include "SDICOS/DICOS.h"

int main()
{
	SDICOS::QR		qr;	//User-Level API for QR modality
	SDICOS::DcsDate dsDate(SDICOS::DcsDate::Today());	//Current Date
	SDICOS::DcsTime dsTime(SDICOS::DcsTime::Now());		//Current Time
	bool bRes(true);	//Results variable

	qr.GenerateSopInstanceUID();	//Generate an SOP Instance UID
	qr.GenerateSeriesInstanceUID();	//Generate a Series Instance UID
	qr.GenerateScanInstanceUID();	//Generate a Scan Instance UID

	qr.SetMeasurementsDateAndTime(dsDate, dsTime);	//Date and time measurement was taken
	qr.SetScanStartDateAndTime(dsDate, dsTime);		//Date and time scan was created
	qr.SetSeriesDateAndTime(dsDate, dsTime);		//Date and time series was created
	qr.SetSopInstanceCreationDateAndTime(dsDate, dsTime);	//Date and time SOP instance was created

	bRes = bRes && qr.SetDeviceCalibrationDateAndTime(dsDate, dsTime); //Date and time device was calibrated
	bRes = bRes && qr.SetDeviceManufacturer("manufacturer");	//Device manufacturer
	bRes = bRes && qr.SetDeviceManufacturerModelName("model");	//Device model name
	bRes = bRes && qr.SetDeviceSerialNumber("serial number");	//Device serial number
	bRes = bRes && qr.SetDeviceSoftwareVersion("s.version");	//Device software version

	qr.SetInspectionBehavioral();	//Set inspection criteria to behavioral

	qr.SetItineraryID("itinerary ID");							//Itinerary ID
	qr.SetItineraryIDAssigningAuthority("Itinerary assigner");	//Authority that assigned the itinerary ID
	qr.SetItineraryIDType(SDICOS::ItineraryModule::enumAgent);	//Itinerary ID Type set to agent

	qr.SetOOIID("OOIID");							//Object of Inspection ID
	qr.SetOOIIDAssigningAuthority("OOID Assigner"); //Authority that assigned the OOI ID
	qr.SetOOIMassInGrams(100);						//OOI mass in grams
	qr.SetOOISizeInMeters(1000, 1000, 1000);		//OOI dimensions in meters
	qr.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);	//OOI type set to baggage
	qr.SetOOITypeDescriptor("description");			//OOI type description

	SDICOS::QR::QRMeasurement measurement;	//QR measurement data

	measurement.m_dsTargetMaterialInChICompound = "InChI=1S/C6H6/c1-2-4-6-5-3-1/h1-6H";	//InChI compound
	measurement.m_dsTargetMaterialInChIKey = "UHOVQNZJYSORNB-UHFFFAOYSA-N";				//InChI key
	measurement.m_fSignalToNoiseRatio = 33.0f;	//Signal-to-Noise (SNR) ratio
	measurement.m_fSNRThreshold = 12;			//SNR threshold

	//Bounding polygon in real world coordinates
	//Providing two points defines the opposite corners of the bounding box
	measurement.m_vBoundingPolygon.SetSize(2);
	measurement.m_vBoundingPolygon[0].Set(0,0,0);
	measurement.m_vBoundingPolygon[1].Set(10,20,30);

	qr.AddMeasurement(measurement);	//Add the measurement

	SDICOS::Filename filename("QR.dcs");	//Output file name
	SDICOS::ErrorLog errorlog;			//Error log

	//Write QR to a DICOS file using little endian explicit transfer syntax
    bRes = qr.Write(filename, errorlog, SDICOS::DicosFile::enumLittleEndianExplicit);
	if(bRes)
		std::cout<<"QR saved to file"<<std::endl;
	else
		std::cout<<"Failed to save QR\n"<<errorlog<<std::endl;

    return (bRes ? 0 : 1);
}
///Endmain
