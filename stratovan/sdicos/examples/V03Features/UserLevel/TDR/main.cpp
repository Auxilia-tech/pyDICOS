//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2022 Stratovan Corporation. All Rights Reserved.
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

void BaggageFeatures()
{
	SDICOS::TDR tdr;
    
	tdr.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);
	tdr.SetTDRType(SDICOS::TDRTypes::ThreatDetectionReport::enumMachine);

	SDICOS::S_UINT16 nBaggagePTOIdentifier(6357);
	SDICOS::S_UINT16 nRepresentation(0);
	SDICOS::S_UINT16 nNumPTORepresentations(1);

    tdr.AddPotentialThreatObject(nBaggagePTOIdentifier, SDICOS::TDR::enumThreatTypeBaggage, nNumPTORepresentations);

    /*
     *  Additions to TDR
     */

    /* Center of Mass [optional]
     *
     * Specifies the 3-dimensional coordinate for the PTO's Center of Mass
	 *     i) Values stored sequentially as XYZ
	 *     ii) Values in image space (i.e. Z indicates frame number)
	 *     iii) 2D images: Z = 0
     * Stored within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem
     * 
	 * PTOIdentifier   Numeric Identifier for the PTO
	 * ptCenter        Point representing the location of the PTO's center of mass
	 * nRepresentation The PTO representation item index
     *
     * See within SDICOS::TDR:
	 *      - bool SetBaggagePTOCenterOfMass(const S_UINT16 PTOIdentifier, const Point3D<float>& ptCenter, const S_UINT16 nRepresentation);
	 *      - Point3D<float> GetBaggagePTOCenterOfMass(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	 *      - bool HasBaggagePTOCenterOfMass(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	 *      - bool DeleteBaggagePTOCenterOfMass(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
     *
     */
    tdr.SetBaggagePTOCenterOfMass(nBaggagePTOIdentifier, SDICOS::Point3D<float>(1.0f, 1.0f, 0.0f), nRepresentation);

	/*
	* Bounding Box Resolution for a PTO [Optional]
	* Enumeration describing possible bounding box resolution methods to avoid multiple bounding boxes on the same PTO
	*/
	{
		//Set to summation of bounding boxes
		tdr.SetBaggageBoundingBoxResolution(nBaggagePTOIdentifier,
											SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumBBR_Summation,
											nRepresentation);
		//Set to largest of the bounding boxes
		tdr.SetBaggageBoundingBoxResolution(nBaggagePTOIdentifier,
											SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumBBR_LargestBoundingBox,
											nRepresentation);
		//Set to the bounding box with the highest assessement probability
		tdr.SetBaggageBoundingBoxResolution(nBaggagePTOIdentifier,
											SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumBBR_HighestAssessmentProbability,
											nRepresentation);
		//Set to a bounding box not described by the other enumerations
		tdr.SetBaggageBoundingBoxResolution(nBaggagePTOIdentifier,
											SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumBBR_Other,
											nRepresentation);

		//Get the Bounding Box Resolution
		SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::BOUNDING_BOX_RESOLUTION nResolution;
		nResolution = tdr.GetBaggageBoundingBoxResolution(nBaggagePTOIdentifier, nRepresentation);

		//Check if a Bounding Box Resolution is present
		bool bHasValue = tdr.HasBaggageBoundingBoxResolution(nBaggagePTOIdentifier, nRepresentation);

		//Delete the Bounding Box Resolution
		tdr.DeleteBaggageBoundingBoxResolution(nBaggagePTOIdentifier, nRepresentation);
	}

	/*
	* Aggregated Method For Bounding Box
	* [Required if the Bounding Box Resolution is set to OTHER (ie. SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumBBR_Other)]
	* Text description on how the bounding box resolution was performed from the TDRs
	*/
	{
		//Set the description
		tdr.SetBaggageAggregatedMethodForBoundingBox(nBaggagePTOIdentifier, "Description", nRepresentation);

		//Get the description
		SDICOS::DcsLongText str = tdr.GetBaggageAggregatedMethodForBoundingBox(nBaggagePTOIdentifier, nRepresentation);

		//Check if the description is present
		bool bHasValue = tdr.HasBaggageAggregatedMethodForBoundingBox(nBaggagePTOIdentifier, nRepresentation);

		//Delete the description
		tdr.DeleteBaggageAggregatedMethodForBoundingBox(nBaggagePTOIdentifier, nRepresentation);
	}

	/*
	* ROI (Region of Interest) Resolution [Optional]
	* [Required if Bounding Box Resolution is present]
	* Enumeration describing possible ROI resolution methods to avoid multiple ROIs on the same PTO
	*/
	{
		//Set to summation of ROIs
		tdr.SetBaggageROIResolution(nBaggagePTOIdentifier,
									SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumROI_Summation,
									nRepresentation);
		//Set to largest of the ROIs
		tdr.SetBaggageROIResolution(nBaggagePTOIdentifier,
									SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumROI_LargestBoundingBox,
									nRepresentation);
		//Set to the ROI with the highest assessement probability
		tdr.SetBaggageROIResolution(nBaggagePTOIdentifier,
									SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumROI_HighestAssessmentProbability,
									nRepresentation);
		//Set to a ROI not described by the other enumerations
		tdr.SetBaggageROIResolution(nBaggagePTOIdentifier,
									SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumROI_Other,
									nRepresentation);

		//Get the ROI Resolution
		SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::ROI_RESOLUTION nResolution;
		nResolution = tdr.GetBaggageROIResolution(nBaggagePTOIdentifier, nRepresentation);

		//Check if the ROI Resolution is present
		bool bHasValue = tdr.HasBaggageROIResolution(nBaggagePTOIdentifier, nRepresentation);

		//Delete the ROI Resolution
		tdr.DeleteBaggageROIResolution(nBaggagePTOIdentifier, nRepresentation);
	}

	/*
	* Aggregated Method of ROI (Region of Interest) Resolution
	* [Required if ROI Resolution is set to OTHER (ie. SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumROI_Other)]
	* Text description on how the ROI resolution was performed from the TDRs
	*/
	{
		//Set the description
		tdr.SetBaggageAggregatedMethodOfROIResolution(nBaggagePTOIdentifier, "Description", nRepresentation);

		//Get the description
		SDICOS::DcsLongText str = tdr.GetBaggageAggregatedMethodOfROIResolution(nBaggagePTOIdentifier, nRepresentation);

		//Check if the description is present
		bool bHasValue = tdr.HasBaggageAggregatedMethodOfROIResolution(nBaggagePTOIdentifier, nRepresentation);

		//Delete the description
		tdr.DeleteBaggageAggregatedMethodOfROIResolution(nBaggagePTOIdentifier, nRepresentation);
	}
}

void AdditionInspectionCriteriaFeatures()
{
	SDICOS::TDR tdr;

	/*
	* Added access functions to set/get multiple additional inspection methods and their descriptions
	*/
	{
		SDICOS::Array1D<SDICOS::TDR::AdditionalInspectionData> vMethods; //Array to store inspection methods and their descriptions
		vMethods.SetSize(2);
		vMethods[0].m_strMethod = "Method 1";
		vMethods[0].m_strMethodDescription = "Method 1 Description";
		vMethods[1].m_strMethod = "Method 2";
		vMethods[1].m_strMethodDescription = "Method 2 Description";

		//Set the methods
		tdr.SetAdditionalInspectionCriteria(true, //true/false if additional inspection was performed
									SDICOS::TDRTypes::AdditionalInspectionSelectionCriteria::enumRandom, //Criteria for additional inspection
									vMethods); // Method(s) used for additional inspection

		//Get the methods
		vMethods.FreeMemory();
		SDICOS::TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA nCriteria;
		tdr.GetAdditionalInspectionCriteria(nCriteria, vMethods);
	}
}

void PTOFeatures()
{
	SDICOS::TDR tdr;
	SDICOS::S_UINT16 nPTOIdentifier(6357);
	SDICOS::S_UINT16 nNumPTORepresentations(1);

	tdr.SetTDRType(SDICOS::TDRTypes::ThreatDetectionReport::enumModAggregate);
	tdr.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);

	tdr.AddPotentialThreatObject(nPTOIdentifier, SDICOS::TDR::enumThreatTypeBaggage, nNumPTORepresentations);

	/*
	* Originating TDR Type
	* [Required if TDR Type is MOD_AGGREGATE (ie. SDICOS::TDRTypes::ThreatDetectionReport::enumModAggregate). Must not present otherwise.]
	* The TDR Type from which the PTO originated.
	*/
	{
		//Set to Machine
		tdr.SetOriginatingTDRType(nPTOIdentifier, SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumOriginatingTDRMachine);
		//Set to Operator
		tdr.SetOriginatingTDRType(nPTOIdentifier, SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumOriginatingTDROperator);
		//Set to Ground Truth
		tdr.SetOriginatingTDRType(nPTOIdentifier, SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumOriginatingTDRGroundTruth);
		//Set to Undefined
		tdr.SetOriginatingTDRType(nPTOIdentifier, SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumOriginatingTDRUndefined);

		//Get the type
		SDICOS::TDRTypes::ThreatSequence::ThreatItem::ORIGINATING_TDR_TYPE nType;
		nType = tdr.GetOriginatingTDRType(nPTOIdentifier);

		//Check if Originating TDR Type is present
		bool bHasValue = tdr.HasOriginatingTDRType(nPTOIdentifier);

		//Delete Originating TDR Type
		tdr.DeleteOriginatingTDRType(nPTOIdentifier);
	}

	/*
	* PTO References [Optional]
	* Set referenced PTOs in other TDRs.
	*/
	{
		SDICOS::Array1D<SDICOS::TDR::ReferencedPTO> vRefs;

		vRefs.SetSize(1); //Set number of references
		
		vRefs[0].m_strSopInstanceUID = "1.1.1.1"; //SOP Instance UID of the referenced TDR containing the referenced PTO
		vRefs[0].m_nPTOID = 1; //PTO ID from referenced TDR

		//Set the references
		tdr.SetReferencedPotentialThreatObject(nPTOIdentifier, vRefs);

		//Get the references
		vRefs.FreeMemory();
		tdr.GetReferencedPotentialThreatObject(nPTOIdentifier, vRefs);

		//Check if PTO References are present
		bool bHasValue = tdr.HasReferencedPotentialThreatObject(nPTOIdentifier);

		//Delete the references
		tdr.DeleteReferencedPotentialThreatObject(nPTOIdentifier);
	}

	/*
	* Signal Generation Software Version [Optional]
	* Defines version(s) of software that converts original sensor data and transforms data for presentation or analysis
	*/
	{
		SDICOS::Array1D<SDICOS::DcsLongString> vVersions;

		vVersions.SetSize(1); //Set number of versions
		vVersions[0] = "Version 1"; //Set version

		//Set Signal Generation Software Versions
		tdr.SetSignalGenerationSoftwareVersion(nPTOIdentifier, vVersions);

		//Set Signal Generation Software Versions
		vVersions.FreeMemory();
		tdr.GetSignalGenerationSoftwareVersion(nPTOIdentifier, vVersions);

		//Check if Signal Generation Software Versions are present
		bool bHasValue = tdr.HasSignalGenerationSoftwareVersion(nPTOIdentifier);

		//Delete all Signal Generation Software Versions
		tdr.DeleteSignalGenerationSoftwareVersion(nPTOIdentifier);
	}

	/*
	* Dynamic Screening Flag [Optional]
	*/
	{
		//Set flag to BHS
		tdr.SetDynamicScreeningFlag(nPTOIdentifier, SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumBHS);
		//Set flag to STIP
		tdr.SetDynamicScreeningFlag(nPTOIdentifier, SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumSTIP);
		//Set flag to Other
		tdr.SetDynamicScreeningFlag(nPTOIdentifier, SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumOther);
		//Set flag to None
		tdr.SetDynamicScreeningFlag(nPTOIdentifier, SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumNone);

		//Get the flag
		SDICOS::TDRTypes::ThreatSequence::ThreatItem::DYNAMIC_SCREENING_FLAG nFlag;
		nFlag = tdr.GetDynamicScreeningFlagEnum(nPTOIdentifier);

		//Check if the flag is present
		bool bHasValue = tdr.HasDynamicScreeningFlag(nPTOIdentifier);

		//Delete the flag
		tdr.DeleteDynamicScreeningFlag(nPTOIdentifier);
	}
}

void ObjectOfInspectionOwnerFeatures()
{
	SDICOS::TDR tdr;

	/*
		Object of Inspection Owner Attributes
		See ObjectOfInspectionOwnerUser.h

		Object of Inspection Owner Module is optional.
		By default OOI Owner attributes are not written unless all required attributes are correct.
	*/

	// Explicitly indicate that OOI Owner attributes should be written
	// by SDICOS::AIT2D::Write(...).
	tdr.EnableObjectOfInspectionOwner();

	tdr.IsObjectOfInspectionOwnerEnabled();

	// Reset Object of Inspection Owner Module attributes to defaults
	// IsObjectOfInspectionOwnerEnabled() returns false after calling.
	tdr.DisableObjectOfInspectionOwner();

	// Get the ItineraryUser
	SDICOS::ObjectOfInspectionOwnerUser& OOIOwner = tdr;

	// Set OOI Owner Module attributes
	OOIOwner.SetOwnerType(SDICOS::ObjectOfInspectionOwnerModule::enumBusiness);

	// Set Owner Risk Score
	SDICOS::S_INT16 nRiskScore = 5;
	OOIOwner.SetOwnerRiskScore(nRiskScore);

	// [REQUIRED] Set Owner Identification information
	OOIOwner.SetPrimaryIdentification("IdIssuingOrg", "IdValue", "OwnersName");
	OOIOwner.SetIDType(SDICOS::CodeDefinitions::enumPIV);

	OOIOwner.SetCountryOfResidence("USA", "United States");

	OOIOwner.SetCountryOfCitizenship("JPN", "Japan");

	// IMPORTANT: Do not confuse with tdr.SetGender() 
	// which is the gender associated with the Object Of Inspection when it is a person.
	OOIOwner.SetOwnerGender(SDICOS::OOIOwnerIdentificationMacro::enumFemale);

	OOIOwner.SetAddress("owner address");

	SDICOS::Array1D<SDICOS::DcsLongString> vPhoneNumbers;
	vPhoneNumbers.Add(SDICOS::DcsLongString("1-415-345-5667"));
	OOIOwner.SetPhoneNumbers(vPhoneNumbers);

	// Owner's Organization Name
	OOIOwner.SetOrganizationName("org name");

	// Set Owner's Organization Address
	OOIOwner.SetOrganizationAddress("Owner Org Address");

	SDICOS::DcsDateTime dt;
	dt.SetNow();
	OOIOwner.SetCreationTime(dt);

	// Has the Owner Identity been removed
	OOIOwner.SetIdentityRemoved(true);

	SDICOS::Array1D<SDICOS::DcsLongString> deIdentificationMethods;
	deIdentificationMethods.Add(SDICOS::DcsLongString("De Identification Method"));
	OOIOwner.SetDeIdentificationMethod(deIdentificationMethods);

	// [REQUIRED] Describes the class of materials the owner is allowed to transport
	OOIOwner.SetTransportClassificationType(SDICOS::ObjectOfInspectionOwnerModule::enumMedical);
}

void SetItinerary()
{
	SDICOS::TDR tdr;

	//
	// SDICOS::TDR derives from SDICOS::ItineraryUser to add support for the Itineray Module attributes
	//
	
	// Itinerary attributes are disabled by default and must be enabled
	tdr.EnableItinerary();

	// To disable the Itinerary attributes
	tdr.DisableItinerary();

	// Get the ItineraryUser
	SDICOS::ItineraryUser& itinerary = tdr;

	//
	//	Create an Itinerary for the Object of Inspection (OOI)
	//	An itinerary contains:
	//		- Identification information for the whole itinerary
	//		- One or more Route Segments with segment-specific information
	//

	// Itinerary ID uniquely identifies the itinerary from a carrier, booking number etc.
	SDICOS::DcsLongString itineraryID("123-345-567");
	itinerary.SetItineraryID(itineraryID);

	// Indicate that the itineraryID came from an agent
	// use enumCarrier to indicate that it came from the carrier handling the OOI
	SDICOS::ItineraryModule::ITINERARY_ID_TYPE itineraryIDType(SDICOS::ItineraryModule::enumAgent);
	itinerary.SetItineraryIDType(itineraryIDType);

	//
	// Human-readable name for the entity assigning the Itinerary ID
	// For example, Agent name or Carrier Name
	//
	SDICOS::DcsLongString itineraryIDAssigningAuthority("Agent Smith");
	itinerary.SetItineraryIDAssigningAuthority(itineraryIDAssigningAuthority);

	//
		// Set up the Itinerary's Route Segments
		// The Itinerary's Route Segments are optional.
		// 
		// Route Segment Attributes:
		//  - Route ID
		//  - Route ID Assigning Authority (IATA)
		//  - Inbound Arrival Type
		//  - Route Segment ID
		//  - Carrier ID
		//  - Carrier ID Assigning Authority (ICAO)
		//  - Boarding Pass ID
		//  - Route Segment Start Location ID
		//  - Route Segment End Location ID
		//  - Route Segment Location ID Type 
		//  - Route Segment Start Time
		//  - Route Segment End Time
		//  - Location Assigned
		//  - International Route Segment (YES/NO)
		//
	SDICOS::Array1D<SDICOS::ItineraryUser::ItineraryRouteSegment> vRouteSegments;

	SDICOS::DcsShortString routeSegmentID0("SFO to LAX");
	SDICOS::ItineraryUser::ItineraryRouteSegment routeSegment0;

	// Unique Identifier for the Route Segment
	routeSegment0.SetRouteSegmentID(routeSegmentID0);

	// Unique Identifier for the entire Route
	routeSegment0.SetRouteID("Wormhole 1");

	// How did the owner get to the Route Segment start location
	routeSegment0.SetInboundArrivalType(SDICOS::ItineraryModule::ItineraryRouteSegment::enumRailMetro);

	// Unique carrier designator
	routeSegment0.SetCarrierID(SDICOS::DcsShortString("The Federation NCC1017A"));

	// Boarding Pass document ID
	routeSegment0.SetBoardingPassID(SDICOS::DcsShortString("Mamma Mia"));

	// Start Location and End Location
	routeSegment0.SetRouteSegmentStartLocationID(SDICOS::DcsShortString("SFO"));
	routeSegment0.SetRouteSegmentEndLocationID(SDICOS::DcsShortString("LAX"));

	// Assigning authority for the Route Segment Start and End Location IDs.
	routeSegment0.SetRouteSegmentLocationIdType(SDICOS::ItineraryModule::ItineraryRouteSegment::enumIATARouteSegmentLocation);

	// Date and Time of segment start
	SDICOS::DcsDateTime segmentStart(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now());
	routeSegment0.SetRouteSegmentStartTime(segmentStart);

	// Date and Time the segment end
	SDICOS::DcsDateTime segmentEnd(SDICOS::DcsDate::Today(), SDICOS::DcsTime(12, 15, 0, 0));
	routeSegment0.SetRouteSegmentEndTime(segmentEnd);

	// Assigned location of Person or OOI. 
	// For example, passenger seat number or cargo locator reference.
	routeSegment0.SetAssignedLocation(SDICOS::DcsShortString("Seat A32"));

	// Is the segment art location an International destination.
	// Required if Route Segment Start Location
	routeSegment0.SetInternationalRouteSegment(SDICOS::ItineraryModule::ItineraryRouteSegment::enumNo);

	vRouteSegments.Add(routeSegment0);

	//
	// Set up a second route segment in the itinerary
	//
	SDICOS::DcsShortString routeSegmentID1 = "LAX to Pudong";
	SDICOS::ItineraryUser::ItineraryRouteSegment routeSegment1;

	routeSegment1.SetRouteID("EVA 1025");
	routeSegment1.SetInboundArrivalType(SDICOS::ItineraryModule::ItineraryRouteSegment::enumAir);

	routeSegment1.SetCarrierID(SDICOS::DcsShortString("NCC1017B"));
	routeSegment1.SetBoardingPassID(SDICOS::DcsShortString("EVA123456"));
	routeSegment1.SetRouteSegmentStartLocationID(SDICOS::DcsShortString("LAX"));
	routeSegment1.SetRouteSegmentEndLocationID(SDICOS::DcsShortString("PUD"));

	// Assigning authority for the Route Segment Start and End Location IDs.
	routeSegment1.SetRouteSegmentLocationIdType(SDICOS::ItineraryModule::ItineraryRouteSegment::enumIATARouteSegmentLocation);
	routeSegment1.SetAssignedLocation(SDICOS::DcsShortString("Seat R10A"));
	routeSegment1.SetInternationalRouteSegment(SDICOS::ItineraryModule::ItineraryRouteSegment::enumYes);

	vRouteSegments.Add(routeSegment1);

	// Add route segments to the IOD
	itinerary.SetItineraryRouteSegments(vRouteSegments);
}

void FrameOfReferenceFeatures()
{
	SDICOS::TDR tdr;
	//
	// Frame of Reference
	// Provides a required set of attributes
	//
	{
		SDICOS::FrameOfReferenceUser &frameOfReference = tdr;

		// Set Position Reference Indicator
		// bool SDICOS::FrameOfReferenceUser::SetPositionReferenceIndicator(const DcsLongString& strPositionReferenceIndicator);
		frameOfReference.SetPositionReferenceIndicator("indicator");

		// Retrieve Position Reference Indicator or an empty string if their is none
		// DcsString SDICOS::FrameOfReferenceUser::GetPositionReferenceIndicator() const;
		frameOfReference.GetPositionReferenceIndicator();
	}
}

int main()
{
	// New functionality within User TDR
	BaggageFeatures();

	// Additional Inspection Criteria Features
	AdditionInspectionCriteriaFeatures();

	// Object of Inspection Owner Features
	ObjectOfInspectionOwnerFeatures();

	// Set Itinerary Information for the TDR's OOI
	SetItinerary();

	// Frame of Reference Features
	FrameOfReferenceFeatures();

	return 0;
}
