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
// This example creates CT objects for multiple energy levels and a 2D SP image
// and links a TDR to those CT objects.
// DICOS does not support holding multiple energy levels of the same volume 
// in a single object. Each energy level of the same volume must be stored as a 
// separate CT object.
//
#include "SDICOS/DICOS.h" //Header for DICOS
#include <iostream>

//Set device and OOI information
template<typename TYPE>
bool SetGeneralInformation(TYPE &mod);	

//Set dummy image data for high and low energy
void SetImageData(SDICOS::Section &secHigh, SDICOS::Section &secLow, SDICOS::Section &secSP);	

int main()
{
	SDICOS::CT ctHighEnergy;	//CT object for high energy
	SDICOS::CT ctLowEnergy;		//CT object for low energy
	SDICOS::CT ctSP;			//CT object for 2D SP
	SDICOS::TDR tdr;			//TDR
	SDICOS::Section *psection = S_NULL;	//Pointer to CT volume section

	//Set same general information for each CT
	SetGeneralInformation(ctHighEnergy);
	SetGeneralInformation(ctLowEnergy);
	SetGeneralInformation(ctSP);
	SetGeneralInformation(tdr);

	//Generate SOP Instance UID's for each CT
	ctHighEnergy.GenerateSopInstanceUID();		
	ctLowEnergy.GenerateSopInstanceUID();
	ctSP.GenerateSopInstanceUID();

	//Set same frame of reference
	ctLowEnergy.SetFrameOfReferenceUID(ctHighEnergy.GetFrameOfReferenceUID());

	//Date and time of volume acquisition
	ctHighEnergy.SetImageAcquisitionDateAndTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now());
	ctLowEnergy.SetImageAcquisitionDateAndTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now());
	ctSP.SetImageAcquisitionDateAndTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now());

	////Time taken for acquisition
	ctHighEnergy.SetImageAcquisitionDuration(5000);		
	ctLowEnergy.SetImageAcquisitionDuration(5000);
	ctSP.SetImageAcquisitionDuration(5000);

	//Low values in volume data correspond to low intensity values
	ctHighEnergy.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);	
	ctLowEnergy.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);	
	ctSP.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);	

	//Generate series UID's
	ctHighEnergy.GenerateSeriesInstanceUID();
	ctLowEnergy.GenerateSeriesInstanceUID();
	ctSP.GenerateSeriesInstanceUID();

	//Place all CT objects in the same scan instance
	ctHighEnergy.GenerateScanInstanceUID();
	ctLowEnergy.SetScanInstanceUID(ctHighEnergy.GetScanInstanceUID());
	ctSP.SetScanInstanceUID(ctHighEnergy.GetScanInstanceUID());

	//Set same Scan ID and OOI ID
	ctHighEnergy.SetOOIID("OOIID");		//Object of Inspection ID
	ctHighEnergy.SetScanID("ScanID");	//Scan ID
	ctLowEnergy.SetOOIID(ctHighEnergy.GetOOIID());
	ctLowEnergy.SetScanID(ctHighEnergy.GetScanID());
	ctSP.SetOOIID(ctHighEnergy.GetOOIID());
	ctSP.SetScanID(ctHighEnergy.GetScanID());

	//Specify energy level with enumeration
	ctHighEnergy.SetImageType(SDICOS::CTTypes::CTImage::enumHighEnergy);
	ctLowEnergy.SetImageType(SDICOS::CTTypes::CTImage::enumLowEnergy);
	ctSP.SetImageType(SDICOS::CTTypes::CTImage::enumPhotoelectric);

	//Set single section volume for each energy level
	ctHighEnergy.SetNumberOfSections(1);
	ctLowEnergy.SetNumberOfSections(1);
	ctSP.SetNumberOfSections(1);

	//Set the intensity values for the each section's volume
	SetImageData(*ctHighEnergy.GetSectionByIndex(0), *ctLowEnergy.GetSectionByIndex(0), *ctSP.GetSectionByIndex(0));

	psection = ctHighEnergy.GetSectionByIndex(0); //Get the high energy volume
	psection->SetKVP(7000);	//Set peak kilo voltage used for scanning

	psection = ctLowEnergy.GetSectionByIndex(0); //Get the high energy volume
	psection->SetKVP(400);	//Set peak kilo voltage used for scanning

	psection = ctSP.GetSectionByIndex(0); //Get the 2D image
	psection->SetKVP(100);	//Set peak kilo voltage used for scanning

	///////////////////////////////////////////////////////
	//Link the TDR to the CT objects created above

	//Link the TDR to the same object of inspection, scan, and series as the CT
	tdr.SetOOIID(ctHighEnergy.GetOOIID());						//Same Object of Inspection ID as both CT's
	tdr.SetScanInstanceUID(ctHighEnergy.GetScanInstanceUID());	//Same Scan Instance UID as both CT's

	tdr.GenerateSopInstanceUID();		//Generate SOP Instance UID
	tdr.GenerateSeriesInstanceUID();	//Generate Series Instance UID

	//Set same Frame of Reference UID as both CT's
	tdr.SetFrameOfReferenceUID(ctHighEnergy.GetFrameOfReferenceUID());

	//////////////////////////////////////////////////////
	//Add 1 PTO with 2 PTO Representations. The PTO is not an alarm object.
	//One PTO Representation per CT energy level. Each CT can have any number 
	//of PTO's and PTO Representations associated with it, but for this 
	//example, one PTO with two PTO Representations will be used.

	const SDICOS::S_UINT16 nPTOIdentifier(0); //An identifier used for a Potential Threat Object
	const SDICOS::S_UINT16 nNumPTORepresentations(2); //The number of PTO Representations used for the above PTO Identifier

	//These are indices that will be used for two PTO Representations
	const SDICOS::S_UINT16 nLowEnergyRepresentation(0);
	const SDICOS::S_UINT16 nHighEnergyRepresentation(1);

	//Set PTO as a baggage threat with 2 PTO representations. 
	//Each representation can be a unique energy level or a unique view that represents the same PTO
	tdr.AddPotentialThreatObject(nPTOIdentifier, 
								SDICOS::TDR::enumThreatTypeBaggage, 
								nNumPTORepresentations);

	//Link PTO Representations to the corresponding CT by identifying each CT's SOP instance UID and SOP class UID
	tdr.AddReferencedInstance(nPTOIdentifier, ctHighEnergy.GetSopClassUID(), ctHighEnergy.GetSopInstanceUID(), nHighEnergyRepresentation);
	tdr.AddReferencedInstance(nPTOIdentifier, ctLowEnergy.GetSopClassUID(), ctLowEnergy.GetSopInstanceUID(), nLowEnergyRepresentation);

	//Set the PTO as not a threat
	tdr.AddPTOAssessment(nPTOIdentifier, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoThreat);

	//Set the required Processing time metric attributes
	tdr.SetProcessingStartTime(nPTOIdentifier, SDICOS::DcsDateTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()));
	tdr.SetProcessingEndTime(nPTOIdentifier, SDICOS::DcsDateTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()));

	//Set the required Mass and Density attributes
	tdr.SetBaggagePTOMassInGrams(nPTOIdentifier, 1.0f, nHighEnergyRepresentation);
	tdr.SetBaggagePTODensityInGramsPerCC(nPTOIdentifier, 0.05f, nHighEnergyRepresentation);

	tdr.SetBaggagePTODetails(nPTOIdentifier,	//ID for PTO 	
							1000,				//PTO mass in grams
							5000,				//PTO density in grams per CC
							0);                 //Index for which PTO Representation Sequence Item
	tdr.SetBaggagePTOVolumeInCC(nPTOIdentifier, 100.0f, 0);	//PTO volume in CC

	//High Energy Values
	{
		tdr.SetThreatRegionOfInterest(nPTOIdentifier,	//ID for PTO 
				SDICOS::Point3D<float>(0,0,0),			//Voxel offset to PTO
				SDICOS::Point3D<float>(10,10,10),		//Voxel dimensions of PTO
				SDICOS::Bitmap(),						//Entire region marked as threat
				nHighEnergyRepresentation);				//High energy representation index

		tdr.SetBaggagePTOLocationDescription(nPTOIdentifier, "High Energy PTO", nHighEnergyRepresentation);	//PTO description
	}
	//Low Energy Values
	{
		tdr.SetThreatRegionOfInterest(nPTOIdentifier,	//ID for PTO 
				SDICOS::Point3D<float>(20,20,20),		//Voxel offset to PTO
				SDICOS::Point3D<float>(5,20,5),			//Voxel dimensions of PTO
				SDICOS::Bitmap(),						//Entire region marked as threat
				nLowEnergyRepresentation);				//Low energy representation index

		tdr.SetBaggagePTOLocationDescription(nPTOIdentifier, "Low Energy PTO", nLowEnergyRepresentation);	//PTO description
	}
	tdr.SetInstanceNumber(0);	//Instance number
	tdr.SetContentDateAndTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now());	//Date and time of content creation
	tdr.SetTDRType(SDICOS::TDRTypes::ThreatDetectionReport::enumMachine); //TDR generated by ATR machine
	tdr.SetTDRTypeATR("ATR Manufacturer", "ATR Version"); //ATR manufacturer and version

	//Relative scaling between the representative figure and the image stored in the PTO
	tdr.SetImageScaleRepresentation(1);	

	tdr.SetAlarmDecision(SDICOS::TDRTypes::ThreatDetectionReport::enumClear); //Alarm decision
	tdr.SetAlarmDecisionDateTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()); //Date and time of alarm decision
	tdr.SetAbortFlag(SDICOS::TDRTypes::ThreatDetectionReport::enumSuccess); //No abort
	tdr.SetTotalProcessingTimeInMS(2500); //Processing time for TDR

	////////////////////////////
	//Write files to disk

	SDICOS::Folder folder(SDICOS::GetExecutableFolder().GetFullFolder());
	SDICOS::Filename filenameCTHigh(folder, "CT_High.dcs");
	SDICOS::Filename filenameCTLow(folder, "CT_Low.dcs");
	SDICOS::Filename filenameCTSP(folder, "CT_SP.dcs");
	SDICOS::Filename filenameTDR(folder, "TDR.dcs");
	SDICOS::ErrorLog errorlogCT;
	SDICOS::ErrorLog errorlogTDR;

	//Write High Energy CT
	if(!ctHighEnergy.Write(filenameCTHigh, errorlogCT))
	{
		std::cout<<"\nFailed writing CT High Energy"<<std::endl;
		std::cout<<errorlogCT<<std::endl;
		return 1;
	}
	else
		std::cout<<"CT High Energy write completed"<<std::endl;

	//Write Low Energy CT
	errorlogCT.FreeMemory();
	if(!ctLowEnergy.Write(filenameCTLow, errorlogCT))
	{
		std::cout<<"\nFailed writing CT Low Energy"<<std::endl;
		std::cout<<errorlogCT<<std::endl;
		return 2;
	}
	else
		std::cout<<"CT Low Energy write completed"<<std::endl;

	//Write CT SP Image
	errorlogCT.FreeMemory();
	if(!ctSP.Write(filenameCTSP, errorlogCT))
	{
		std::cout<<"\nFailed writing CT SP"<<std::endl;
		std::cout<<errorlogCT<<std::endl;
		return 3;
	}
	else
		std::cout<<"CT SP write completed"<<std::endl;

	//Write TDR
	if(!tdr.Write(filenameTDR, errorlogTDR, SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cout<<"\nFailed writing TDR"<<std::endl;
		std::cout<<errorlogTDR<<std::endl;
		return 4;
	}
	else
		std::cout<<"TDR write completed"<<std::endl;

	return 0;
}

//Set general information such as equipment and OOI
template<typename TYPE>
bool SetGeneralInformation(TYPE &mod)
{
	bool bRes(true);
	const SDICOS::DcsDate strDate(SDICOS::DcsDate::Today());	//Constant for today's date
	const SDICOS::DcsTime strTime(SDICOS::DcsTime::Now());		//Constant for current time

	bRes = bRes && mod.SetContentDateAndTime(strDate, strTime);	//Date and time of content acquisition
	bRes = bRes && mod.SetOOIIDAssigningAuthority("OOI ID Assigning Authority");	//Name of OOI ID assigning authority
	bRes = bRes && mod.SetOOIIDType(SDICOS::ObjectOfInspectionModule::IdInfo::enumRFID); //OOI ID corresponds to an RFID
	bRes = bRes && mod.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage); //OOI is baggage
	bRes = bRes && mod.SetScanStartDateAndTime(strDate, strTime); //Date and time scan started
	bRes = bRes && mod.SetScanType(SDICOS::GeneralScanModule::enumOperational); //Operational scan
	bRes = bRes && mod.SetSeriesDateAndTime(strDate, strTime);	//Date and time of series creation
	bRes = bRes && mod.SetSeriesAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful); //Acquisition was successfully captured
	bRes = bRes && mod.SetDeviceCalibrationDateAndTime(strDate, strTime); //Date and time of device calibration
	bRes = bRes && mod.SetDeviceSerialNumber("123456987");	//Device serial number
	bRes = bRes && mod.SetMachineAddress("Machine Address"); //Machine address (Physical address)
	bRes = bRes && mod.SetMachineLocation("Machine Location");//Machine location (Location on site)
	bRes = bRes && mod.SetMachineID("Machine ID"); //Machine ID
	bRes = bRes && mod.SetDeviceManufacturer("Device Manufacturer"); //Device manufacturer
	bRes = bRes && mod.SetDeviceManufacturerModelName("Device Manufacturer Model Name");	//Model name
	bRes = bRes && mod.SetDeviceSoftwareVersion("Device Software Version"); //Device's software version
	bRes = bRes && mod.SetSopInstanceCreationDateAndTime(strDate, strTime); //Date and time of SOP instance creation

	return bRes;
}

//Set image data for low and high energy
void SetImageData(SDICOS::Section &secHigh, SDICOS::Section &secLow, SDICOS::Section &secSP)
{
	//Allocate volume data for each energy level
	secHigh.GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, 100,100,100);
	secLow.GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, 100,100,100);
	secSP.GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, 100,100,1);

	//Initialize to uniform value
	secHigh.GetPixelData().GetUnsigned16()->Zero(1000);
	secLow.GetPixelData().GetUnsigned16()->Zero(500);
	secSP.GetPixelData().GetUnsigned16()->Zero(700);

	//Set volume spacing
	secHigh.SetSpacingInMM(1.0f,1.0f,1.0f);
	secLow.SetSpacingInMM(1.0f,1.0f,1.0f);
	secSP.SetSpacingInMM(1.0f,1.0f,0.0f);

	//Define the real world coordinate of the first frame's top left corner
	secHigh.SetPositionInMM(0,0,0); 
	secLow.SetPositionInMM(0,0,0); 
	secSP.SetPositionInMM(0,0,0); 
}
