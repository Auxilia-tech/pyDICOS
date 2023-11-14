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

///
/// Create a Threat Detection Report for a person.
///
bool CreatePersonTDR()
{
	//
	// The TDRModule object is the modile-level API object that represent the
	// Threat Detection Report (TDR) Information Object Definition (IOD) in the DICOS Specification Section 7.
	//
	// #include "SDICOS/ModuleTDR.h"
	//
	// All objects in the Stratovan DICOS Toolkit are declared in the SDICOS namespace.
	// SDICOS::TDR is not a thread-safe object.
	// The SDICOS::TDRTypes namespace contains modules used to implement the SDICOS::TDR object.
	//
	SDICOS::TDRModule tdr;

	/*
	 *	High and low-level API methods generally return true/false to indicate
	 *	success and failure.
	 */
	bool bRes(true);
	
	//
	// SOP Common
	// The DICOS SOP Class UID for all IODs is described in Section 14.
	//
	bRes = bRes && tdr.GetSopCommon().GetSopClassUID() == SDICOS::SOPClassUID::GetTDR();
	
	// Utility method for setting the current date
	SDICOS::DcsDate date;
	date.SetToday();
	
	// Utility method for setting the current time
	SDICOS::DcsTime time;
	time.SetNow();
	
	// The DateTime object is a specific DICOS Value Representation (VR) that contains date and time
	SDICOS::DcsDateTime dateTime;
	dateTime.Set(date,time);
	
	bRes = bRes && tdr.GetSopCommon().SetSopInstanceCreationDateAndTime(date,time);
	
	//
	// Create a unique identifier for the TDR from a user defined string.
	//
	SDICOS::DcsUniqueIdentifier sopInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.883");
	bRes = bRes && tdr.GetSopCommon().SetSopInstanceUID(sopInstanceUID);

	//
	// The GeneralScanModule class represents the General Scan Module (Section 5 Table 12)
	//
	SDICOS::GeneralScanModule &generalScan = tdr.GetGeneralScan();
	bRes = bRes && generalScan.SetScanID("TSS4.314");
	bRes = bRes && generalScan.SetStartDateAndTime(date,time);
	
	//
	// This demonstrates how to create a unique identifier using 
	// the static class method 'CreateGUID()' in the DcsUniqueIdentifier class.
 	//
	SDICOS::DcsUniqueIdentifier scanInstanceUID = SDICOS::DcsUniqueIdentifier::CreateGUID();
	bRes = bRes && generalScan.SetScanInstanceUID(scanInstanceUID);
	bRes = bRes && generalScan.SetType(SDICOS::GeneralScanModule::enumOperational);

	//
	// The TDRSeries class represents the TDR Series Module Table 58
	// 
	// #include "SDICOS/TDRSeries.h"
	//
	SDICOS::TDRTypes::TDRSeries& series = tdr.GetSeries();
	bRes = bRes && series.SetDateAndTime(date,time);
	bRes = bRes && series.GetModality() == SDICOS::GeneralSeriesModule::enumTDR;
	
	//
	// A unique identifier for the TDR Series
	//
	SDICOS::DcsUniqueIdentifier seriesInstanceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370732.882");
	bRes = bRes && series.SetInstanceUID(seriesInstanceUID);
	bRes = bRes && series.SetAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful);

	//
	// The GeneralEquipmentModule class represent the General Equipment Module (Table 70)
	// Required information about the machine the scan was captured on.
	//
	SDICOS::GeneralEquipmentModule& generalEquipment = tdr.GetGeneralEquipment();
	bRes = bRes && generalEquipment.SetManufacturer("Stratovan");
	bRes = bRes && generalEquipment.SetMachineLocation("Security Checkpoint 1");
	bRes = bRes && generalEquipment.SetMachineAddress("Davis, CA");
	bRes = bRes && generalEquipment.SetMachineID("007");
	bRes = bRes && generalEquipment.SetManufacturerModelName("HAL");
	bRes = bRes && generalEquipment.SetDeviceSerialNumber("DSN-001");
	bRes = bRes && generalEquipment.SetSoftwareVersion("3.14");
	bRes = bRes && generalEquipment.SetCalibrationDateAndTime(date,time);

	//
	// The Common Instance Reference Module (Table 87) is a mandatory module in the TDR
	// The Referenced Series Sequence is type 1C (Conditionally Required) and is explicitly allocated when used.
	//
	SDICOS::CommonInstanceReferenceModule& commonInstance = tdr.GetCommonInstanceReference();
	commonInstance.AllocateReferencedSeries();
	SDICOS::ReferencedSeriesSequence *prss = tdr.GetCommonInstanceReference().GetReferencedSeries();
	bRes = bRes && prss != S_NULL;
	if(S_NULL != prss)
	{
		// The sequence contains one or more ReferencedSeries objects
		SDICOS::Array1D<SDICOS::ReferencedSeriesSequence::ReferencedSeries> & referencedSeries = prss->GetReferencedSeries();
		referencedSeries.SetSize(1);
		bRes = bRes && referencedSeries[0].SetSeriesInstanceUID(seriesInstanceUID);
		referencedSeries[0].GetReferencedInstances().SetSize(1);
		
		// This reference points to another TDR, so the SOP Class UID for the TDR is used.
		// The SOP Class UIDs for the other IOD types (CT, DX etc) should be used as appropriate
		bRes = bRes && referencedSeries[0].GetReferencedInstances()[0].SetClassUID(SDICOS::SOPClassUID::GetTDR());
		bRes = bRes && referencedSeries[0].GetReferencedInstances()[0].SetInstanceUID(sopInstanceUID);
	}

	//
	// The ObjectOfInspectionModule class represents Object Of Inspection Module (OOI) (Section 4.1, Table 10)
	//
	SDICOS::ObjectOfInspectionModule& ooi = tdr.GetObjectOfInspection();
	bRes = bRes && ooi.GetID().SetID("TSS4.000314");
	bRes = bRes && ooi.GetID().SetIdAssigningAuthority("Issuer-001");
	bRes = bRes && ooi.GetID().SetIdType(SDICOS::ObjectOfInspectionModule::IdInfo::enumText);
	bRes = bRes && ooi.SetType(SDICOS::ObjectOfInspectionModule::enumTypePerson);
	bRes = bRes && ooi.SetGender(SDICOS::ObjectOfInspectionModule::enumGenderFemale);

	// OOI Type Description and OOI Size are optional attributes
	bRes = bRes && ooi.SetTypeDescription(SDICOS::DcsLongText("Person is traveling from Liberia"));
	bRes = bRes && ooi.SetSizeInMeters(1.7f,0.1f,0.1f);

	//
	// The General Report class represents the General Report module (Table 60)
	//
	SDICOS::TDRTypes::GeneralReport& generalReport = tdr.GetGeneralReport();
	bRes = bRes && generalReport.SetContentDateAndTime(SDICOS::DcsDate("20140130"), SDICOS::DcsTime("130532.435"));
	bRes = bRes && generalReport.SetInstanceNumber(1001);

	//
	// The SDICOS::FrameOfReference class represents the Frame of Reference (Table 107)
	// The Frame of Reference UID identifies a shared frame of reference for all objects associated with the TDR
	// It is a grouping to indicate that multiple series in scan have the same frame of reference.
	//
	SDICOS::DcsUniqueIdentifier frameOfReferenceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370740.887");
	bRes = bRes && tdr.GetFrameOfReference().SetFrameOfReferenceUID(frameOfReferenceUID);

	//
	// The Threat Detection Report class represents the Threat Detection Report Module (Table 61)
	//
	SDICOS::TDRTypes::ThreatDetectionReport& threadDetectionReport = tdr.GetThreatDetectionReport();
	bRes = bRes && threadDetectionReport.SetAbortFlag(SDICOS::TDRTypes::ThreatDetectionReport::enumSuccess);
	
	// Set the alarm decision type (MACHINE, OPERATOR, AGGREGATE, MOD_AGGREGATE, or GROUND TRUTH)
	bRes = bRes && threadDetectionReport.SetTdrType(SDICOS::TDRTypes::ThreatDetectionReport::enumMachine);
	
	// A set of ATR algorithm control parameters
	SDICOS::Array1D<SDICOS::DcsLongString> threadDetectionControlParameters;
	
	// Manufacturer, Algorithm Version, control parameters
	bRes = bRes && threadDetectionReport.SetThreatDetectionAlgorithmAndVersion("Stratovan", "3.16", threadDetectionControlParameters);
	bRes = bRes && threadDetectionReport.SetAlarmDecision(SDICOS::TDRTypes::ThreatDetectionReport::enumAlarm);
	
	bRes = bRes && threadDetectionReport.SetAlarmDecisionDateAndTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now());
	bRes = bRes && threadDetectionReport.SetNumberOfAlarmObjects(3);
	bRes = bRes && threadDetectionReport.SetNumberOfTotalObjects(3);
	bRes = bRes && threadDetectionReport.SetImageScaleRepresentation(1.0);

	// The AdditionalInspectionSelectionCriteria object is used to specify other types of screening that were used
	// to determine if the object is a threat.
	SDICOS::TDRTypes::AdditionalInspectionSelectionCriteria& additionalCriteria = tdr.GetAdditionalInspectionSelectionCriteria();
	bRes = bRes && additionalCriteria.SetAdditionalScreeningPerformed(false);

	//
	// unique identifier for the CT instance referenced by threat items
	//
	SDICOS::DcsUniqueIdentifier ctInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.881");
	//
	// The Threat Sequence class represents the Threat Sequence Module (Table 62)
	//
	SDICOS::TDRTypes::ThreatSequence &ts = tdr.GetThreatSequence();
	
	//
	// The ThreatSequence contains information about Potential Threat Objects (PTOs).
	// The ThreatSequence::ThreatItem class stores the information for a specific PTO.
	// The ThreatSequence contains one or more ThreatItems.
	//
	SDICOS::Array1D<SDICOS::TDRTypes::ThreatSequence::ThreatItem>& threatObject = ts.GetPotentialThreatObject();
	
	// for this example there are 2 threats
	threatObject.SetSize(2);

	// Indicate that Item 0 is a piece of baggage
	threatObject[0].EnablePersonTDR(true);
	bRes = bRes && threatObject[0].SetID(0);
	
	//
	// The AssessmentSequence class contains one or more threat assessments for this threat object
	// The Assessment Sequence is implemented as an array of AssessmentItem objects
	// In this example, two threat assessments are provided for a contraband prohibited item
	//
	SDICOS::TDRTypes::AssessmentSequence& objectAssessmentSequence = threatObject[0].GetAssessment();
	bRes = bRes && objectAssessmentSequence.GetAssessment().SetSize(2);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumProhibitedItem);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetAbilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumShield);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetAssessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetAssessmentProbability(0.75f);
	
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumContraband);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetAbilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumShield);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetAssessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetAssessmentProbability(1.0f);
	
	// Set person specific attributes
	{
		// The PersonSpecificTDR object stores information specific to baggage threats
		SDICOS::TDRTypes::PersonSpecificTDR & personTDR = threatObject[0].GetPersonTDR();

		// One representation for the PTO (Single-Energy CT). 
		// Each representation can signify information for another view or energy level.
		personTDR.GetPTORepresentationSequenceItems().SetSize(1);

		// Indicate the original scan or scans associated with this TDR.
		SDICOS::Array1D<SDICOS::SopInstanceReference> & referencedInstanceSequence = personTDR.GetPTORepresentationSequenceItems()[0].GetReferencedInstance();
		bRes = bRes && referencedInstanceSequence.SetSize(1);
		bRes = bRes && referencedInstanceSequence[0].SetClassUID(SDICOS::SOPClassUID::GetCT());
		bRes = bRes && referencedInstanceSequence[0].SetInstanceUID(ctInstanceUID);

		// Region of interest can also be set as a bounding polygon
		SDICOS::Array1D<SDICOS::Point3D<float> > boundingPolygon(4);
		for(SDICOS::S_UINT32 i = 0; i < boundingPolygon.GetSize(); ++i) 
		{
			boundingPolygon[i].x = 1.0f;
			boundingPolygon[i].y = 2.0f;
			boundingPolygon[i].z = 3.0f;
		}
		
		personTDR.GetPTORepresentationSequenceItems()[0].SetBoundingPolygon(boundingPolygon);
		
		// Indicate the geometry of the threat Region Of Interest
		SDICOS::TDRTypes::CommonSpecificTDR::ThreatROI& threatRegionOfInterest = personTDR.GetPTORepresentationSequenceItems()[0].GetThreatROI();
		bRes = bRes && threatRegionOfInterest.SetThreatRoiBase(101.0f, 141.0f, 57.0f);
		bRes = bRes && threatRegionOfInterest.SetThreatRoiExtents(54.0f, 63.0f, 104.0f);
		bRes = bRes && threatRegionOfInterest.GetThreatRoiBitmap().SetDims(54, 63, 104);

		// Short description of Potential Threat Object(PTO) location
		personTDR.GetPTORepresentationSequenceItems()[0].SetLocationDescription(SDICOS::DcsShortText("Outside of right leg"));
		
		// The Anomaly Locator Indicators are the (x,y,z) image coordinates of the center of each anomaly intended for on-screen presentation.
		SDICOS::Array1D<SDICOS::TDRTypes::PersonSpecificTDR::AnomalyLocatorIndicator>& anomalyIndicators = personTDR.GetPTORepresentationSequenceItems()[0].GetAnomalyLocatorIndicator();
		anomalyIndicators.SetSize(1);
		anomalyIndicators[0].SetCenter(10.1f,13.3f,5.0f);
	}

	// Set the Processing time for Item 0
	// Total Processing time is in milliseconds
	bRes = bRes && threatObject[0].SetProcessingStartTime(dateTime);
	bRes = bRes && threatObject[0].SetProcessingEndTime(dateTime);
	bRes = bRes && threatObject[0].SetTotalProcessingTime(0.0f);


	threatObject[1].EnablePersonTDR(true);
	threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems().SetSize(1);
	bRes = bRes && threatObject[1].SetID(2);
	bRes = bRes && threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems()[0].GetReferencedInstance().SetSize(1);
	bRes = bRes && threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems()[0].GetReferencedInstance()[0].SetClassUID(SDICOS::SOPClassUID::GetCT());
	bRes = bRes && threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems()[0].GetReferencedInstance()[0].SetInstanceUID(ctInstanceUID);
	bRes = bRes && threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems()[0].GetThreatROI().SetThreatRoiBase(73.0f, 68.0f, 92.0f);
	bRes = bRes && threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems()[0].GetThreatROI().SetThreatRoiExtents(61.0f, 94.0f, 72.0f);
	bRes = bRes && threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems()[0].GetThreatROI().GetThreatRoiBitmap().SetDims(61, 94, 72);
	bRes = bRes && threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems()[0].SetLocationDescription(SDICOS::DcsShortText("Lower back"));
	bRes = bRes && threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems()[0].GetAnomalyLocatorIndicator().SetSize(1);
	bRes = bRes && threatObject[1].GetPersonTDR().GetPTORepresentationSequenceItems()[0].GetAnomalyLocatorIndicator()[0].SetCenter(1.0,2.0,4.0);

	SDICOS::Array1D<SDICOS::SopInstanceReference> vReferencedScans;
	SDICOS::SopInstanceReference reference;
	reference.SetClassUID(SDICOS::SOPClassUID::GetCT());
	reference.SetInstanceUID(ctInstanceUID);
	vReferencedScans.Add(reference);

	bRes = bRes && tdr.GetGeneralScan().SetReferencedScans(vReferencedScans);
	
	bRes = bRes && threatObject[1].GetAssessment().GetAssessment().SetSize(1);
	bRes = bRes && threatObject[1].GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumExplosive);
	bRes = bRes && threatObject[1].GetAssessment().GetAssessment()[0].SetAbilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference);
	bRes = bRes && threatObject[1].GetAssessment().GetAssessment()[0].SetAssessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat);
	bRes = bRes && threatObject[1].SetProcessingStartTime(dateTime);
	bRes = bRes && threatObject[1].SetProcessingEndTime(dateTime);
	// Total Processing time is in milliseconds
	bRes = bRes && threatObject[1].SetTotalProcessingTime(0.0f);
	
	////////////////////////////////////////////////

	const SDICOS::Filename filename("TDRPerson.dcs");
	
	SDICOS::ErrorLog errorlog;
	
	if(!tdr.IsValid(errorlog))
	{
		std::cout << "Failed to validate Person Specific TDR" << std::endl;
		std::cout << errorlog << std::endl;
		return false;
	}
	
	// The FreeMemory call empties the ErrorLog of existing warnings and error messages.
	errorlog.FreeMemory();
	
	bRes = bRes && tdr.Write(filename, SDICOS::DicosFile::enumLittleEndianExplicit, errorlog);

	if(errorlog.HasErrors() || errorlog.HasWarnings())
	{
		errorlog.WriteLog(SDICOS::Filename("TDRPersonErrors.txt"));
		std::cout << "Failed to write Person-Specific TDR DICOS File " << filename << " Writing Errors to TDRPersonErrors.txt" << std::endl;
		std::cout << errorlog << std::endl;
	} 
	else 
	{
		std::cout << "Wrote Person-Specific TDR DICOS File " << filename << std::endl;
	}

	errorlog.FreeMemory();
	
	//
	// Read the DICOS file from disk using the AttributeManager object
	//
	SDICOS::AttributeManager manager;
	if(SDICOS::DicosFile::Read(filename, errorlog, manager)) 
	{
		bRes = bRes && manager.WriteToFileAsText("TDRPersonListings.txt");
		std::cout << "Write Attribute Listing to TDRPersonListings.txt" << std::endl;
	} 
	else 
	{
		std::cout << "Failed to read as DICOS file " << filename << std::endl;
		std::cout << errorlog << std::endl;
		return false;
	}
	errorlog.FreeMemory();
	
	SDICOS::TDRModule tdr2;
	
	//
	// Read again and compare to existing TDR object
	//
	if(!tdr2.Read(filename, errorlog))
	{
		std::cout << "Failed to read as Person-Specific TDR Object " << filename << std::endl;
		std::cout << errorlog << std::endl;
		errorlog.WriteLog(SDICOS::Filename("TDRPersonFileReadErrorLog.txt"));
		return false;
	}
	else 
	{
		std::cout << "Read TDR From " << filename << std::endl;
		bRes = bRes && (tdr == tdr2);
		
		if(bRes) 
		{
			std::cout << "Verified written and read Person-Specific TDR files are equivalent" << std::endl;
		} 
		else
		{
			std::cout << "Failed to verify that written and read Person-Specific TDR files are equivalent" << std::endl;
		}
		if(!tdr2.IsValid(errorlog))
		{
			std::cout << "Failed to validate Person-Specific TDR read from disk" << std::endl;
			std::cout << errorlog << std::endl;
			return false;
		}
	}

	return bRes;
} // EndCreatePersonTDR

bool CreateBaggageTDR()
{
	//
	// The TDRModule object is the high-level API object that represent the
	// Threat Detection Report (TDR) Information Object Definition (IOD) in the DICOS Specification Section 7.
	//
	// #include "SDICOS/ModuleTDR.h"
	//
	// All objects in the Stratovan DICOS Toolkit are declared in the SDICOS namespace.
	// SDICOS::TDR is not a thread-safe object.
	//
	SDICOS::TDRModule tdr;

	//
	//	High and low-level API methods generally return true/false to indicate
	//	success and failure.
	//
	bool bRes(true);
	
	//
	// SOP Common
	// The DICOS SOP Class UID for all IODs is described in Section 14.
	//
	bRes = bRes && tdr.GetSopCommon().GetSopClassUID() == SDICOS::SOPClassUID::GetTDR();
	
	// Utility method for setting the current date
	SDICOS::DcsDate date;
	date.SetToday();
	
	// Utility method for setting the current time
	SDICOS::DcsTime time;
	time.SetNow();
	
	// The DateTime object is a specific DICOS Value Representation (VR) that contains date and time
	SDICOS::DcsDateTime dateTime;
	dateTime.Set(date,time);
	
	bRes = bRes && tdr.GetSopCommon().SetSopInstanceCreationDateAndTime(date,time);
	
	//
	// Create a unique identifier for the TDR from a user defined string.
	//
	SDICOS::DcsUniqueIdentifier sopInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.883");
	bRes = bRes && tdr.GetSopCommon().SetSopInstanceUID(sopInstanceUID);

	//
	// The GeneralScanModule class represents the General Scan Module (Section 5 Table 12)
	//
	SDICOS::GeneralScanModule &generalScan = tdr.GetGeneralScan();
	bRes = bRes && generalScan.SetScanID("TSS4.314");
	bRes = bRes && generalScan.SetStartDateAndTime(date,time);
	
	//
	// This demonstrates how to create a unique identifier using 
	// the static class method 'CreateGUID()' in the DcsUniqueIdentifier class.
 	//
	SDICOS::DcsUniqueIdentifier scanInstanceUID = SDICOS::DcsUniqueIdentifier::CreateGUID();
	bRes = bRes && generalScan.SetScanInstanceUID(scanInstanceUID);
	bRes = bRes && generalScan.SetType(SDICOS::GeneralScanModule::enumOperational);

	//
	// The TDRSeries class represents the TDR Series Module Table 58
	// 
	// #include "SDICOS/TDRSeries.h"
	//
	SDICOS::TDRTypes::TDRSeries& series = tdr.GetSeries();
	bRes = bRes && series.SetDateAndTime(date,time);
	bRes = bRes && series.GetModality() == SDICOS::GeneralSeriesModule::enumTDR;
	
	//
	// A unique identifier for the TDR Series
	//
	SDICOS::DcsUniqueIdentifier seriesInstanceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370732.882");
	bRes = bRes && series.SetInstanceUID(seriesInstanceUID);
	bRes = bRes && series.SetAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful);

	//
	// The GeneralEquipmentModule class represent the General Equipment Module (Table 70)
	// Required information about the machine the scan was captured on.
	//
	SDICOS::GeneralEquipmentModule& generalEquipment = tdr.GetGeneralEquipment();
	bRes = bRes && generalEquipment.SetManufacturer("Stratovan");
	bRes = bRes && generalEquipment.SetMachineLocation("Security Checkpoint 1");
	bRes = bRes && generalEquipment.SetMachineAddress("Davis, CA");
	bRes = bRes && generalEquipment.SetMachineID("007");
	bRes = bRes && generalEquipment.SetManufacturerModelName("HAL");
	bRes = bRes && generalEquipment.SetDeviceSerialNumber("DSN-001");
	bRes = bRes && generalEquipment.SetSoftwareVersion("3.14");
	bRes = bRes && generalEquipment.SetCalibrationDateAndTime(date,time);

	//
	// The Common Instance Reference Module (Table 87) is a mandatory module in the TDR
	// The Referenced Series Sequence is type 1C (Conditionally Required) and is explicitly allocated when used.
	//
	SDICOS::CommonInstanceReferenceModule& commonInstance = tdr.GetCommonInstanceReference();
	commonInstance.AllocateReferencedSeries();
	SDICOS::ReferencedSeriesSequence *prss = tdr.GetCommonInstanceReference().GetReferencedSeries();
	bRes = bRes && prss != S_NULL;
	if(S_NULL != prss)
	{
		// The sequence contains one or more ReferencedSeries objects
		SDICOS::Array1D<SDICOS::ReferencedSeriesSequence::ReferencedSeries> & referencedSeries = prss->GetReferencedSeries();
		referencedSeries.SetSize(1);
		bRes = bRes && referencedSeries[0].SetSeriesInstanceUID(seriesInstanceUID);
		referencedSeries[0].GetReferencedInstances().SetSize(1);
		
		// This reference points to another TDR, so the SOP Class UID for the TDR is used.
		// The SOP Class UIDs for the other IOD types (CT, DX etc) should be used as appropriate
		bRes = bRes && referencedSeries[0].GetReferencedInstances()[0].SetClassUID(SDICOS::SOPClassUID::GetTDR());
		bRes = bRes && referencedSeries[0].GetReferencedInstances()[0].SetInstanceUID(sopInstanceUID);
	}

	//
	// The ObjectOfInspectionModule class represents Object Of Inspection Module (OOI) (Section 4.1, Table 10)
	//
	SDICOS::ObjectOfInspectionModule& ooi = tdr.GetObjectOfInspection();
	bRes = bRes && ooi.GetID().SetID("TSS4.000314");
	bRes = bRes && ooi.GetID().SetIdAssigningAuthority("Issuer-001");
	bRes = bRes && ooi.GetID().SetIdType(SDICOS::ObjectOfInspectionModule::IdInfo::enumText);
	bRes = bRes && ooi.SetType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);

	//
	// The General Report class represents the General Report module (Table 60)
	//
	SDICOS::TDRTypes::GeneralReport& generalReport = tdr.GetGeneralReport();
	bRes = bRes && generalReport.SetContentDateAndTime(SDICOS::DcsDate("20140130"), SDICOS::DcsTime("130532.435"));
	bRes = bRes && generalReport.SetInstanceNumber(1001);

	//
	// The SDICOS::FrameOfReference class represents the Frame of Reference (Table 107)
	// The Frame of Reference UID identifies a shared frame of reference for all objects associated with the TDR
	// It is a grouping to indicate that multiple series in scan have the same frame of reference.
	//
	SDICOS::DcsUniqueIdentifier frameOfReferenceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370740.887");
	bRes = bRes && tdr.GetFrameOfReference().SetFrameOfReferenceUID(frameOfReferenceUID);

	//
	// The Threat Detection Report class represents the Thread Detection Report Module (Table 61)
	//
	SDICOS::TDRTypes::ThreatDetectionReport& threadDetectionReport = tdr.GetThreatDetectionReport();
	bRes = bRes && threadDetectionReport.SetAbortFlag(SDICOS::TDRTypes::ThreatDetectionReport::enumSuccess);
	
	// Set the alarm decision type (MACHINE, OPERATOR or TRUTH)
	bRes = bRes && threadDetectionReport.SetTdrType(SDICOS::TDRTypes::ThreatDetectionReport::enumMachine);
	
	// A set of ATR algorithm control parameters
	SDICOS::Array1D<SDICOS::DcsLongString> threadDetectionControlParameters;
	
	// Manufacturer, Algorithm Version, control parameters
	bRes = bRes && threadDetectionReport.SetThreatDetectionAlgorithmAndVersion("Stratovan", "3.16", threadDetectionControlParameters);
	bRes = bRes && threadDetectionReport.SetAlarmDecision(SDICOS::TDRTypes::ThreatDetectionReport::enumAlarm);
	
	bRes = bRes && threadDetectionReport.SetAlarmDecisionDateAndTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now());
	bRes = bRes && threadDetectionReport.SetNumberOfAlarmObjects(3);
	bRes = bRes && threadDetectionReport.SetNumberOfTotalObjects(3);
	bRes = bRes && threadDetectionReport.SetImageScaleRepresentation(1.0);

	// The AdditionalInspectionSelectionCriteria object is used to specify other types of screening that were used
	// to determine if the object is a threat.
	SDICOS::TDRTypes::AdditionalInspectionSelectionCriteria& additionalCriteria = tdr.GetAdditionalInspectionSelectionCriteria();
	bRes = bRes && additionalCriteria.SetAdditionalScreeningPerformed(false);

	//
	// unique identifier for the CT instance referenced by threat items
	//
	SDICOS::DcsUniqueIdentifier ctInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.881");
	//
	// The Threat Sequence class represents the Threat Sequence Module (Table 62)
	//
	SDICOS::TDRTypes::ThreatSequence &ts = tdr.GetThreatSequence();
	
	//
	// The ThreatSequence contains information about Potential Threat Objects (PTOs).
	// The ThreatSequence::ThreatItem class stores the information for a specific PTO.
	// The ThreatSequence contains one or more ThreatItems.
	//
	SDICOS::Array1D<SDICOS::TDRTypes::ThreatSequence::ThreatItem>& threatObject = ts.GetPotentialThreatObject();
	
	// for this example there are 3 threats
	threatObject.SetSize(3);

	// Indicate that Item 0 is a piece of baggage
	threatObject[0].EnableBaggageTDR(true);
	bRes = bRes && threatObject[0].SetID(0);
	
	//
	// The AssessmentSequence class contains one or more threat assessments for this threat object
	// The Assessment Sequence is implemented as an array of AssessmentItem objects
	// In this example, two threat assessments are provided for a explosive precursor
	//
	SDICOS::TDRTypes::AssessmentSequence& objectAssessmentSequence = threatObject[0].GetAssessment();
	bRes = bRes && objectAssessmentSequence.GetAssessment().SetSize(2);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumExplosive);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetAbilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetAssessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumOther);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetAbilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetAssessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat);

	// Set baggage specific attributes
	{
		// The BaggageSpecificTDR object stores information specific to baggage threats
		SDICOS::TDRTypes::BaggageSpecificTDR& baggageTDR = threatObject[0].GetBaggageTDR();
		// One representation for the PTO (Single-Energy CT). 
		// Each representation can signify information for another view or energy level.
		baggageTDR.GetPTORepresentationSequenceItems().SetSize(1);
		SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem& seqItem = baggageTDR.GetPTORepresentationSequenceItems()[0];

		bRes = bRes && seqItem.SetMass(1321.2283935546875f);
		bRes = bRes && seqItem.SetDensity(1.0f);

		// Indicate the original scan or scans associated with this TDR.
		SDICOS::Array1D<SDICOS::SopInstanceReference> & referencedInstanceSequence = baggageTDR.GetPTORepresentationSequenceItems()[0].GetReferencedInstance();
		bRes = bRes && referencedInstanceSequence.SetSize(1);
		bRes = bRes && referencedInstanceSequence[0].SetClassUID(SDICOS::SOPClassUID::GetCT());
		bRes = bRes && referencedInstanceSequence[0].SetInstanceUID(ctInstanceUID);

		// Indicate the geometry of the threat Region Of Interest
		SDICOS::TDRTypes::CommonSpecificTDR::ThreatROI& threatRegionOfInterest = baggageTDR.GetPTORepresentationSequenceItems()[0].GetThreatROI();
		bRes = bRes && threatRegionOfInterest.SetThreatRoiBase(101.0f, 141.0f, 57.0f);
		bRes = bRes && threatRegionOfInterest.SetThreatRoiExtents(54.0f, 63.0f, 104.0f);
		bRes = bRes && threatRegionOfInterest.GetThreatRoiBitmap().SetDims(54, 63, 104);
	}

	// Set the Processing time for Item 0
	bRes = bRes && threatObject[0].SetProcessingStartTime(dateTime);
	bRes = bRes && threatObject[0].SetProcessingEndTime(dateTime);
	// Total Processing time is in milliseconds
	bRes = bRes && threatObject[0].SetTotalProcessingTime(0.0f);

	SDICOS::Array1D<SDICOS::SopInstanceReference> vReferencedScans;
	SDICOS::SopInstanceReference reference;
	reference.SetClassUID(SDICOS::SOPClassUID::GetCT());
	reference.SetInstanceUID(ctInstanceUID);
	vReferencedScans.Add(reference);

	bRes = bRes && tdr.GetGeneralScan().SetReferencedScans(vReferencedScans);

	//
	// For Items 1 & 2 the syntax is compacted to show how the TDR ThreatItem information
	// can be set in a less verbose way the the previous example which illustrated the hierarchy
	// of types in the TDR class.
	//

	//Item 1
	threatObject[1].EnableBaggageTDR(true);
	bRes = bRes && threatObject[1].SetID(1);
	bRes = bRes && threatObject[1].GetBaggageTDR().GetPTORepresentationSequenceItems().SetSize(1);
	bRes = bRes && threatObject[1].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetReferencedInstance().SetSize(1);
	bRes = bRes && threatObject[1].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetReferencedInstance()[0].SetClassUID(SDICOS::SOPClassUID::GetCT());
	bRes = bRes && threatObject[1].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetReferencedInstance()[0].SetInstanceUID(ctInstanceUID);
	bRes = bRes && threatObject[1].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetThreatROI().SetThreatRoiBase(112.0f, 48.0f, 122.0f);
	bRes = bRes && threatObject[1].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetThreatROI().SetThreatRoiExtents(12.0f, 6.0f, 12.0f);
	bRes = bRes && threatObject[1].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetThreatROI().GetThreatRoiBitmap().SetDims(12, 6, 12);
	bRes = bRes && threatObject[1].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].SetMass(1321.2283935546875f);
	bRes = bRes && threatObject[1].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].SetDensity(1.0f);
	bRes = bRes && threatObject[1].GetAssessment().GetAssessment().SetSize(1);
	bRes = bRes && threatObject[1].GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumExplosive);
	bRes = bRes && threatObject[1].GetAssessment().GetAssessment()[0].SetAbilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference);
	bRes = bRes && threatObject[1].GetAssessment().GetAssessment()[0].SetAssessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat);
	bRes = bRes && threatObject[1].SetProcessingStartTime(dateTime);
	bRes = bRes && threatObject[1].SetProcessingEndTime(dateTime);
	// Total Processing time is in milliseconds
	bRes = bRes && threatObject[1].SetTotalProcessingTime(0.0f);

	//Item 2
	threatObject[2].EnableBaggageTDR(true);
	bRes = bRes && threatObject[2].SetID(2);
	bRes = bRes && threatObject[2].GetBaggageTDR().GetPTORepresentationSequenceItems().SetSize(1);
	bRes = bRes && threatObject[2].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetReferencedInstance().SetSize(1);
	bRes = bRes && threatObject[2].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetReferencedInstance()[0].SetClassUID(SDICOS::SOPClassUID::GetCT());
	bRes = bRes && threatObject[2].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetReferencedInstance()[0].SetInstanceUID(ctInstanceUID);
	bRes = bRes && threatObject[2].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetThreatROI().SetThreatRoiBase(73.0f, 68.0f, 92.0f);
	bRes = bRes && threatObject[2].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetThreatROI().SetThreatRoiExtents(61.0f, 94.0f, 72.0f);
	bRes = bRes && threatObject[2].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].GetThreatROI().GetThreatRoiBitmap().SetDims(61, 94, 72);
	bRes = bRes && threatObject[2].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].SetMass(1321.2283935546875f);
	bRes = bRes && threatObject[2].GetBaggageTDR().GetPTORepresentationSequenceItems()[0].SetDensity(1.0f);
	bRes = bRes && threatObject[2].GetAssessment().GetAssessment().SetSize(1);
	bRes = bRes && threatObject[2].GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumExplosive);
	bRes = bRes && threatObject[2].GetAssessment().GetAssessment()[0].SetAbilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference);
	bRes = bRes && threatObject[2].GetAssessment().GetAssessment()[0].SetAssessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat);
	bRes = bRes && threatObject[2].SetProcessingStartTime(dateTime);
	bRes = bRes && threatObject[2].SetProcessingEndTime(dateTime);
	// Total Processing time is in milliseconds
	bRes = bRes && threatObject[2].SetTotalProcessingTime(0.0f);
	
	////////////////////////////////////////////////

	const SDICOS::Filename filename("TDRBaggage.dcs");
	
	SDICOS::ErrorLog errorlog;
	
	if(!tdr.IsValid(errorlog))
	{
		std::cout << "Failed to validate Baggage TDR" << std::endl;
		std::cout << errorlog << std::endl;
		return false;
	}
	
	// The FreeMemory call empties the ErrorLog of existing warnings and error messages.
	errorlog.FreeMemory();
	
	bRes = bRes && tdr.Write(filename, SDICOS::DicosFile::enumLittleEndianExplicit, errorlog);

	if(errorlog.HasErrors() || errorlog.HasWarnings())
	{
		errorlog.WriteLog(SDICOS::Filename("TDRBaggageErrors.txt"));
		std::cout << "Failed to write Baggage TDR DICOS File " << filename << " Writing Errors to TDRBaggageErrors.txt" << std::endl;
		std::cout << errorlog << std::endl;
	} 
	else 
	{
		std::cout << "Wrote TDR DICOS File " << filename << std::endl;
	}

	errorlog.FreeMemory();
	
	//
	// Read the DICOS file from disk using the AttributeManager object
	//
	SDICOS::AttributeManager manager;
	if(SDICOS::DicosFile::Read(filename, errorlog, manager)) 
	{
		bRes = bRes && manager.WriteToFileAsText("TDRBaggageListings.txt");
		std::cout << "Write Attribute Listing to TDRBaggageListings.txt" << std::endl;
	} 
	else
	{
		std::cout << "Failed to read as DICOS file " << filename << std::endl;
		std::cout << errorlog << std::endl;
		return false;
	}
	errorlog.FreeMemory();
	
	SDICOS::TDRModule tdr2;
	
	//
	// Read again and compare to existing TDR object
	//
	if(!tdr2.Read(filename, errorlog))
	{
		std::cout << "Failed to read as TDR Object " << filename << std::endl;
		std::cout << errorlog << std::endl;
		errorlog.WriteLog(SDICOS::Filename("TDRBaggageFileReadErrorLog.txt"));
		return false;
	}
	else 
	{
		std::cout << "Read TDR From " << filename << std::endl;
		bRes = bRes && (tdr == tdr2);
		
		if(bRes) 
		{
			std::cout << "Verified written and read Baggage TDR files are equivalent" << std::endl;
		} 
		else 
		{
			std::cout << "Failed to verify that written and read Baggage TDR files are equivalent" << std::endl;
		}
		
		if(!tdr2.IsValid(errorlog))
		{
			std::cout << "Failed to validate Baggage TDR read from disk" << std::endl;
			std::cout << errorlog << std::endl;
			return false;
		}
	}

	return bRes;
} // EndCreateBaggageTDR

int main()
{
	bool bRes = CreatePersonTDR();
	bRes = CreateBaggageTDR() && bRes;
	return (bRes ? 0 : 1);
}
