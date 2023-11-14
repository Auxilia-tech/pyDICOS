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


void BaseClassFeatures()
{
	SDICOS::DX dx;

	/*
	* Detector Type has one new enumeration and new access functions
	*/
	{
		//New enum 'enumOther'
		dx.SetDetectorType(SDICOS::DXTypes::DXDetector::enumOther); // "OTHER"

		//Check if Detector Type is present and valid
		bool bRet = dx.HasDetectorType();

		//Delete Detector Type. This saves the value as NULL when written to file.
		dx.DeleteDetectorType();
	}

	/*
	* Added Detector Configuration access functions
	*/
	{
		//Set Detector Configuration to any of the below enumerations
		dx.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumUnknown);		// "UNKNOWN"
		dx.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumSandwich);		// "SANDWICH"
		dx.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumSideBySide);	// "SIDE BY SIDE"
		dx.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumCheckerboard);	// "CHECKERBOARD"
		dx.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumMonoEnergetic);// "MONOENERGETIC"

		//Get the Detector Configuration
		SDICOS::DXTypes::DXDetector::DETECTOR_CONFIGURATION nConfig = dx.GetDetectorConfiguration();

		//Check if Detector Configuration is present
		bool bRet = dx.HasDetectorConfiguration();

		//Delete Detector Configuration is present
		dx.DeleteDetectorConfiguration();
	}
}

void ParentChanges()
{
	SDICOS::DX dx;

	/*
	* Features for the ScanCommon parent class
	*/
	{
		SDICOS::ScanCommon& scanCommon = dx;

		/*
		* TIP Features
		*/
		{
			/*
			* TIP Library Name - a new optional tag to set the TIP library name
			*/
			{
				//Set the library name
				dx.SetTipLibraryName("EXAMLE LIBRARY NAME");
				
				//Check if the library name is set, if it is get it
				if(dx.HasTipLibraryName())
				{
					SDICOS::DcsShortText strLibraryName;
					strLibraryName = dx.GetTipLibraryName();
				}

				//Delete the library name
				dx.DeleteTipLibraryName();
			}

			/*
			* TIP Image Identifier - a new optional tag to set the TIP image identifier
			*/
			{
				//Set the image identifier
				dx.SetTipImageIdentifier("EXAMPLE IMAGE IDENTIFIER");

				//Check if the image identifier is set, if it is get it
				if(dx.HasTipImageIdentifier())
				{
					SDICOS::DcsShortText strImageIdentifier;
					strImageIdentifier = dx.GetTipImageIdentifier();
				}

				//Delete the image identifier
				dx.DeleteTipImageIdentifier();
			}

			/*
			* TIP Library Date - a new optional tag to set the TIP library date
			*/
			{
				//Set the library date
				SDICOS::DcsDateTime dtLibraryDate;
				dtLibraryDate.SetNow();
				dx.SetTipLibraryDate(dtLibraryDate);

				//Check if the library date is set, if it is get it
				if(dx.HasTipLibraryDate())
				{
					dtLibraryDate = dx.GetTipLibraryDate();
				}

				//Delete the library date
				dx.DeleteTipLibraryDate();
			}
		}

		// XRayEquipmentUser Features
		{
			/*  X-Ray Equipment User Level API 
			 *
			 *  Describes the attributes related to the device's grating and detectors during the acquisition of an X-Ray image
			 *
			 *  See within SDICOS::DXModule:
			 *      - bool SetXRayEquipment(const XRayEquipmentModule &xRayEquipment);
			 *      - bool GetXRayEquipment(XRayEquipmentModule &xRayEquipment)const;
			 *      - XRayEquipmentModule& GetXRayEquipment();
			 *      - const XRayEquipmentModule& GetXRayEquipment()const;
			 */
			SDICOS::XRayEquipmentUser& xRayEquipment = dx;


			// Members of X-Ray Equipment Module:


			/*  Mask Characteristics : Tag (4300, 0906), VR = ST [optional]
			 *
			 *  Describes how the CAI mask was designed
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetMaskCharacteristics(const DcsShortText &nMaskCharacteristics);
			 *      - DcsShortText GetMaskCharacteristics()const;
			 *      - bool HasMaskCharacteristics()const;
			 *      - void DeleteMaskCharacteristics();
			 */
			xRayEquipment.GetMaskCharacteristics();

			/*  Type of G0 : Tag (4300, 0904), VR = CS [optional]
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetTypeG0(const TYPE_G nTypeG0);
			 *      - TYPE_G GetTypeG0()const;
			 *      - DcsString GetTypeG0AsString()const;
			 *      - bool HasTypeG0()const;
			 *      - void DeleteTypeG0();
			 */
			xRayEquipment.GetTypeG0();
			// Valid Values:
			SDICOS::XRayEquipmentModule::enumGratingG0;
			SDICOS::XRayEquipmentModule::enumMaskG0;

			/*  Type of G1 : Tag (4300, 0910), VR = CS [optional]
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetTypeG1(const TYPE_G nTypeG1);
			 *      - TYPE_G GetTypeG1()const;
			 *      - DcsString GetTypeG1AsString()const;
			 *      - bool HasTypeG1()const;
			 *      - void DeleteTypeG1();
			 */
			xRayEquipment.GetTypeG1();
			// Valid Values:
			SDICOS::XRayEquipmentModule::enumGratingG1;
			SDICOS::XRayEquipmentModule::enumOtherG1;

			/*  Type of G2 : Tag (4300, 0914), VR = CS [optional]
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetTypeG2(const TYPE_G nTypeG2);
			 *      - TYPE_G GetTypeG2()const;
			 *      - DcsString GetTypeG2AsString()const;
			 *      - bool HasTypeG2()const;
			 *      - void DeleteTypeG2();
			 */
			xRayEquipment.GetTypeG2();
			// Valid Values:
			SDICOS::XRayEquipmentModule::enumGratingG2;
			SDICOS::XRayEquipmentModule::enumOtherG2;

			/*  Reconstruction Algorithm for Phase Image : Tag (4300, 0938), VR = CS [optional]
			 *
			 *  Type of algorithm used for reconstruction of the phase image
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetReconAlgorithmPhaseImage(const RECON_IMAGE nPhaseImage);
			 *      - RECON_IMAGE GetReconAlgorithmPhaseImage()const;
			 *      - DcsString GetReconAlgorithmPhaseImageAsString()const;
			 *      - bool HasReconAlgorithmPhaseImage()const;
			 *      - void DeleteReconAlgorithmPhaseImage();
			 */
			xRayEquipment.GetReconAlgorithmPhaseImage();
			// Valid Values:
			SDICOS::XRayEquipmentModule::enumFFT;
			SDICOS::XRayEquipmentModule::enumModifiedFFT;
			SDICOS::XRayEquipmentModule::enumOtherImage;

			/*  Reconstruction Algorithm for Dark Image : Tag (4300, 0940), VR = CS [optional]
			 *
			 *  Type of algorithm used for reconstruction of the dark image
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetReconAlgorithmDarkImage(const RECON_IMAGE nDarkImage);
			 *      - RECON_IMAGE GetReconAlgorithmDarkImage()const;
			 *      - DcsString GetReconAlgorithmDarkImageAsString()const;
			 *      - bool HasReconAlgorithmDarkImage()const;
			 *      - void DeleteReconAlgorithmDarkImage();
			 */
			xRayEquipment.GetReconAlgorithmDarkImage();
			// Valid Values:
			SDICOS::XRayEquipmentModule::enumFFT;
			SDICOS::XRayEquipmentModule::enumModifiedFFT;
			SDICOS::XRayEquipmentModule::enumOtherImage;

			/*  Effective Energy : Tag (4300, 0902), VR = FL [required]
			 *
			 *  The energy for which the gratings were designed for
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetEffectiveEnergy(const float nEffectiveEnergy);
			 *      - float GetEffectiveEnergy()const;
			 */
			xRayEquipment.GetEffectiveEnergy();

			/*  Distance G0 from X-Ray Source : Tag (4300, 0908), VR = FL [optional]
			 *
			 *  Distance from the output of the X-Ray source to the G0 grating (in cm)
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetDistanceFromG0ToSourceInCentimeters(const float nDistanceG0XR);
			 *      - float GetDistanceFromG0ToSourceInCentimeters()const;
			 *      - bool HasDistanceFromG0ToSourceInCentimeters()const;
			 *      - void DeleteDistanceFromG0ToSourceInCentimeters();
			 */
			xRayEquipment.GetDistanceFromG0ToSourceInCentimeters();

			/*  Distance G1 from X-Ray Source : Tag (4300, 0912), VR = FL [optional]
			 *
			 *  Distance from the output of the X-Ray source to the G1 grating (in cm)
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetDistanceFromG1ToSourceInCentimeters(const float nDistanceG1XR);
			 *      - float GetDistanceFromG1ToSourceInCentimeters()const;
			 *      - bool HasDistanceFromG1ToSourceInCentimeters()const;
			 *      - void DeleteDistanceFromG1ToSourceInCentimeters();
			 */
			xRayEquipment.GetDistanceFromG1ToSourceInCentimeters();

			/*  G0 Absorption Period : Tag (4300, 0918), VR = FL [optional]
			 *
			 *  The pitch or period of the G0 grating
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetG0AbsorptionPeriod(const float nG0Absorption);
			 *      - float GetG0AbsorptionPeriod()const;
			 *      - bool HasG0AbsorptionPeriod()const;
			 *      - void DeleteG0AbsorptionPeriod();
			 */
			xRayEquipment.GetG0AbsorptionPeriod();

			/*  G1 Phase Period : Tag (4300, 0920), VR = FL [optional]
			 *
			 *  The period of the G1 grating
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetG1PhasePeriod(const float nG1Phase);
			 *      - float GetG1PhasePeriod()const;
			 *      - bool HasG1PhasePeriod()const;
			 *      - void DeleteG1PhasePeriod();
			 */
			xRayEquipment.GetG1PhasePeriod();

			/*  G2 Analyzer Period : Tag (4300, 0922), VR = FL [optional]
			 *
			 *  The period of the G1 grating
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetG2AnalyzerPeriod(const float nG2Analyzer);
			 *      - float GetG2AnalyzerPeriod()const;
			 *      - bool HasG2AnalyzerPeriod()const;
			 *      - void DeleteG2AnalyzerPeriod();
			 */
			xRayEquipment.GetG2AnalyzerPeriod();

			/*  Visibility : Tag (4300, 0924), VR = FL [optional]
			 *
			 *  The resulting visibility of the phase and dark image
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetVisibility(const float nVisibility);
			 *      - float GetVisibility()const;
			 *      - bool HasVisibility()const;
			 *      - void DeleteVisibility();
			 */
			xRayEquipment.GetVisibility();

			/*  Absorption X-Ray Detector Size : Tag (4300, 0926), VR = FL [optional]
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetAbsorptionXRDetectorSize(const float nSizeX, const float nSizeY);
			 *      - float GetAbsorptionXRDetectorSizeX()const;
			 *      - float GetAbsorptionXRDetectorSizeY()const;
			 *      - bool HasAbsorptionXRDetectorSize()const;
			 *      - void DeleteAbsorptionXRDetectorSize();
			 */
			xRayEquipment.GetAbsorptionXRDetectorSizeX();
			xRayEquipment.GetAbsorptionXRDetectorSizeY();

			/*  Absorption Reconstruction Voxel Size : Tag (4300, 0928), VR = FL [optional]
			 *
			 *  The resulting size of the X-Ray detectors which are combined to provide the absorption pixel/voxel size (x, y)
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetAbsorptionReconstructionVoxelSize(const float nSizeX, const float nSizeY);
			 *      - float GetAbsorptionReconstructionVoxelSizeX()const;
			 *      - float GetAbsorptionReconstructionVoxelSizeY()const;
			 *      - bool HasAbsorptionReconstructionVoxelSize()const;
			 *      - void DeleteAbsorptionReconstructionVoxelSize();
			 */
			xRayEquipment.GetAbsorptionReconstructionVoxelSizeX();
			xRayEquipment.GetAbsorptionReconstructionVoxelSizeY();

			/*  Phase X-Ray Detector Size : Tag (4300, 0930), VR = FL [optional]
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetPhaseXRDetectorSize(const float nSizeX, const float nSizeY);
			 *      - float GetPhaseXRDetectorSizeX()const;
			 *      - float GetPhaseXRDetectorSizeY()const;
			 *      - bool HasPhaseXRDetectorSize()const;
			 *      - void DeletePhaseXRDetectorSize();
			 */
			xRayEquipment.GetPhaseXRDetectorSizeX();
			xRayEquipment.GetPhaseXRDetectorSizeY();

			/*  Phase Reconstruction Voxel Size : Tag (4300, 0932), VR = FL [optional]
			 *
			 *  The resulting size of the X-Ray detectors which are combined to provide the phase pixel/voxel size (x, y)
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetPhaseReconstructionVoxelSize(const float nSizeX, const float nSizeY, const float nSizeZ);
			 *      - float GetPhaseReconstructionVoxelSizeX()const;
			 *      - float GetPhaseReconstructionVoxelSizeY()const;
			 *      - float GetPhaseReconstructionVoxelSizeZ()const;
			 *      - bool HasPhaseReconstructionVoxelSize()const;
			 *      - void DeletePhaseReconstructionVoxelSize();
			 */
			xRayEquipment.GetPhaseReconstructionVoxelSizeX();
			xRayEquipment.GetPhaseReconstructionVoxelSizeY();
			xRayEquipment.GetPhaseReconstructionVoxelSizeZ();

			/*  Dark XR Detector Size : Tag (4300, 0934), VR = FL [optional]
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetDarkXRDetectorSize(const float nSizeX, const float nSizeY);
			 *      - float GetDarkXRDetectorSizeX()const;
			 *      - float GetDarkXRDetectorSizeY()const;
			 *      - bool HasDarkXRDetectorSize()const;
			 *      - void DeleteDarkXRDetectorSize();
			 */
			xRayEquipment.GetDarkXRDetectorSizeX();
			xRayEquipment.GetDarkXRDetectorSizeY();

			/*  Dark Reconstruction Voxel Size : Tag (4300, 0936), VR = FL [optional]
			 *
			 *  The resulting size of the X-Ray detectors which are combined to provide the dark image voxel size, (x, y, z)
			 *
			 *  See within SDICOS::XRayEquipmentModule:
			 *      - bool SetDarkReconstructionVoxelSize(const float nSizeX, const float nSizeY, const float nSizeZ);
			 *      - float GetDarkReconstructionVoxelSizeX()const;
			 *      - float GetDarkReconstructionVoxelSizeY()const;
			 *      - float GetDarkReconstructionVoxelSizeZ()const;
			 *      - bool HasDarkReconstructionVoxelSize()const;
			 *      - void DeleteDarkReconstructionVoxelSize();
			 */
			xRayEquipment.GetDarkReconstructionVoxelSizeX();
			xRayEquipment.GetDarkReconstructionVoxelSizeY();
			xRayEquipment.GetDarkReconstructionVoxelSizeZ();
		}

		/*
		 * SDICOS::DX derives from the DX Modality Modules to support the APIs for:
		 *		X-Ray Detector
		 *		X-Ray Positioning
		 *		X-Ray Generation
		 *		X-Ray Filtration
		 * 
		 * See the respective classes for complete listing
		 */
		{
			// Example for X-Ray Detector
			dx.SetDetectorType(SDICOS::DXTypes::DXDetector::enumScintillator);

			// Example for X-Ray Positioning
			const float fBeltSpeed = 123.4f;
			dx.SetBeltSpeed(fBeltSpeed);

			// Example for X-Ray Generation
			const float fPeakKiloVoltage = 123.4f;
			dx.SetKVP(fPeakKiloVoltage);

			// Example for X-Ray Filtration
			dx.SetFilterType(SDICOS::DXTypes::XRayFiltration::enumButterfly);
		}
	}

	/*
		Object of Inspection Owner Attributes
		See ObjectOfInspectionOwnerUser.h

		Object of Inspection Owner Module is optional.
		By default OOI Owner attributes are not written unless all required attributes are correct.
	*/
	{
		// Explicitly indicate that OOI Owner attributes should be written
		// by SDICOS::DX::Write(...).
		dx.EnableObjectOfInspectionOwner();

		dx.IsObjectOfInspectionOwnerEnabled();

		// Reset Object of Inspection Owner Module attributes to defaults
		// IsObjectOfInspectionOwnerEnabled() returns false after calling.
		dx.DisableObjectOfInspectionOwner();

		// Get Object of Inspection Owner
		SDICOS::ObjectOfInspectionOwnerUser& OOIOwner = dx;

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

		// IMPORTANT: Do not confuse with dx.SetGender() 
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


	//
	// IODCommon derives from SDICOS::ItineraryUser to add support for the Itineray Module attributes
	//
	{
		// Itinerary attributes are disabled by default and must be enabled
		dx.EnableItinerary();

		// To disable the Itinerary attributes
		dx.DisableItinerary();

		// Get the ItineraryUser
		SDICOS::ItineraryUser& itinerary = dx;

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

	//
	// Frame of Reference
	// Provides an optional set of attributes
	//
	{
		SDICOS::FrameOfReferenceUser &frameOfReference = dx;

		// Enable Frame of Reference attributes to be written during Write()
		// FrameOfReferenceUser attributes are disabled by default
		// void SDICOS::DX::EnableFrameOfReference();
		dx.EnableFrameOfReference();

		// Frame Of Reference attributes will not be written during Write()
		// void SDICOS::DX::DisableFrameOfReference();
		dx.DisableFrameOfReference();

		// Determine if Frame of Reference attributes are enabled and will be written during Write() invocations
		// bool SDICOS::DX::IsFrameOfReferenceEnabled();
		dx.IsFrameOfReferenceEnabled();

		// Set Frame Of Reference UID
		// bool SDICOS::FrameOfReferenceUser::SetFrameOfReferenceUID(const DcsUniqueIdentifier& strFrameOfReferenceUID);
		frameOfReference.SetFrameOfReferenceUID("125");

		// Generate a new Frame of Reference UID
		// bool SDICOS::FrameOfReferenceUser::GenerateFrameOfReferenceUID();
		frameOfReference.GenerateFrameOfReferenceUID();

		// Retrieve Frame of Reference UID or an empty string if their is none
		// DcsUniqueIdentifier SDICOS::FrameOfReferenceUser::GetFrameOfReferenceUID() const;
		frameOfReference.GetFrameOfReferenceUID();

		// Set Position Reference Indicator
		// bool SDICOS::FrameOfReferenceUser::SetPositionReferenceIndicator(const DcsLongString& strPositionReferenceIndicator);
		frameOfReference.SetPositionReferenceIndicator("indicator");

		// Retrieve Position Reference Indicator or an empty string if their is none
		// DcsString SDICOS::FrameOfReferenceUser::GetPositionReferenceIndicator() const;
		frameOfReference.GetPositionReferenceIndicator();
	}

	//
	// Acquistion Context
	// Provides a required set of attributes
	//
	{
		SDICOS::AcquisitionContextUser &acquisitionContext = dx;

		// Add an AcquisitionContextValue to the User Level API object
		// AddAcquisitionContextValue returns the index to the AcquisitionContextValue item if it was successfully added
		// If the item was not successfully added, returns -1
		//
		// Has multiple function signatures, can pass all values required for a Value Type to automatically create and add an AcquisitionContextValue
		// See:
		// AddAcquisitionContextValue(const AcquisitionContestValue &av);
    	// AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, DcsShortString &strNameDesignator, const Array1D<float> &arrayValues, const DcsShortString &strUnits, const DcsLongString &strUnitsMeaning, const DcsCodeString &strUnitsMappingResource, const DcsDateTime& strContextGroupVersion);
		// AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, DcsShortString &strNameDesignator, const DcsDate &strDate);
    	// AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, DcsShortString &strNameDesignator, const DcsTime &strTime);
    	// AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, DcsShortString &strNameDesignator, const DcsPersonName &strPersonName);
		// AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, DcsShortString &strNameDesignator, const DcsUnlimitedText &strText);
		// AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, DcsShortString &strNameDesignator, const DcsShortString &strConcept, const DcsLongString &strConceptMeaning, DcsShortString &strConceptDesignator);
		
		// Add an Acquisition Context Item with Value Type = Numeric
		SDICOS::Array1D<float> numerics;
		int index = acquisitionContext.AddAcquisitionContextValue("CODE VALUE", "Numerics pertaining to the Acquisition", "DESIGNATOR", numerics, "UNIT VALUE", "Meaning of the units of measurement", "DESIGNATOR", SDICOS::DcsDateTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()));
		// If the AcquisitionContextValue object at the given index is Numeric, get the Numeric values
		acquisitionContext.GetNumericValues(index, numerics);

		// Check if the AcquisitionContextValue object at the given index is Numeric
		acquisitionContext.IsNumeric(index);

		// If the AcquisitionContextValue object at the given index is Numeric, get the Measurement Units
		SDICOS::DcsShortString strUnitsValue;
		SDICOS::DcsLongString strUnitsMeaning;
		SDICOS::DcsCodeString strUnitsMapping;
		SDICOS::DcsDateTime strUnitsVersion;
		acquisitionContext.GetMeasurementUnits(index, strUnitsValue, strUnitsMeaning, strUnitsMapping, strUnitsVersion);

		// Add an Acquisition Context Item with Value Type = Date
		{
			index = acquisitionContext.AddAcquisitionContextValue("CODE VALUE", "Date of the Acquisition", "DESIGNATOR", SDICOS::DcsDate::Today());
			
			// Check if the AcquisitionContextValue object at the given index is a Date
			acquisitionContext.IsDate(index);

			// If the AcquisitionContextValue object at the given index is a Date, get the Date
			SDICOS::DcsDate strDate;
			acquisitionContext.GetDate(index, strDate);
		}

		// Add an Acquisition Context Item with Value Type = Time
		{
			index = acquisitionContext.AddAcquisitionContextValue("CODE VALUE", "Time of the Acquisition", "DESIGNATOR", SDICOS::DcsTime::Now());

			// Check if the AcquisitionContextValue object at the given index is a Time
			acquisitionContext.IsTime(index);

			// If the AcquisitionContextValue object at the given index is a Time, get the Time
			SDICOS::DcsTime strTime;
			acquisitionContext.GetTime(index, strTime);
		}

		// Add an Acquisition Context Item with Value Type = PName
		{
			index = acquisitionContext.AddAcquisitionContextValue("CODE VALUE", "Person name for the Acquisition", "DESIGNATOR", SDICOS::DcsPersonName("Firstname Lastname"));

			// Check if the AcquisitionContextValue object at the given index is a Person Name
			acquisitionContext.IsPersonName(index);

			// If the AcquisitionContextValue object at the given index is a Person Name, get the name
			SDICOS::DcsPersonName strPersonName;
			acquisitionContext.GetPersonName(index, strPersonName);
		}

		// Add an Acquisition Context Item with Value Type = Text
		{
			index = acquisitionContext.AddAcquisitionContextValue("CODE VALUE", "Text Details for the Acquisition", "DESIGNATOR", SDICOS::DcsUnlimitedText("The value of the text for the acquisition context"));

			// Check if the AcquisitionContextValue object at the given index is Text
			acquisitionContext.IsText(index);

			// If the AcquisitionContextValue object at the given index is Text, get the text
			SDICOS::DcsUnlimitedText strText;
			acquisitionContext.GetText(index, strText);
		}

		// Add an Acquisition Context Item with Value Type not set
		{
			index = acquisitionContext.AddAcquisitionContextValue("CODE VALUE", "Concept Code for the Acquisition", "DESIGNATOR", "CONCEPT VALUE", "Meaning for the Concept Value", "DESIGNATOR");
			
			// If the AcquisitionContextValue object at the given index has a Concept Code Sequence, get it
			SDICOS::DcsShortString strConceptValue, strConceptDesignator;
			SDICOS::DcsLongString strConceptMeaning;
			acquisitionContext.GetConceptCode(index, strConceptValue, strConceptMeaning, strConceptDesignator);
		}

		// Add Referenced Frame Numbers to the AcquisitionContextValue at the given index
		SDICOS::Array1D<SDICOS::S_UINT16> arrayFrames;
		arrayFrames.Add(1);
		arrayFrames.Add(2);
		acquisitionContext.AddReferencedFrameNumbers(index, arrayFrames);

		// If the AcquisitionContextValue at the given index has Referenced Frame Numbers, get them
		SDICOS::Array1D<SDICOS::S_UINT16> arrayFramesGet;
		acquisitionContext.GetReferencedFrameNumbers(index, arrayFramesGet);
		// Referenced Frame Numbers are optional
		// Can check if the AcquisitionContextValue at a given index has Referenced Frame Numbers and delete them
		acquisitionContext.HasReferencedFrameNumbers(index);
		acquisitionContext.DeleteReferenecedFrameNumbers(index);

		// Acquisition Context Value provides an interface for each Acquisition Context Item
		// An AcquisitionContextValue object represents one of many values that can be added to the Acquisition Context
		SDICOS::AcquisitionContextValue acquisitionContextValue;

		// Get the Acquisition Context object at the given index
		// If no object exists at that index return false
		acquisitionContext.GetAcquisitionContext(index, acquisitionContextValue);

		// Set the Value Type for the Acquisition Context
		// Different value types have different required attributes
		acquisitionContextValue.SetType(SDICOS::AcquisitionContextSequence::AcquisitionContextModule::enumText);

		// Value Type is an optional attribute
		// Can check if the Type is set and can delete the Type
		acquisitionContextValue.HasType();
		acquisitionContextValue.DeleteType();

		// Set the Concept Name Code, required for all Value types
		// The Code value and Code designators are both short strings, and can be 16 characters max, cannot contain backslash
		// The Concept Name Code describes the attribute based on the Value Type that is set
		// e.g. If Value Type = DATE, then the Concept Name describes the date
		SDICOS::DcsShortString strValue, strDesignator;
		SDICOS::DcsLongString strMeaning;
		acquisitionContextValue.SetConceptNameCode("CODE VALUE", "Human readable code meaning", "DESIGNATOR");

		// Get the Concept Name Code
		acquisitionContextValue.GetConceptNameCode(strValue, strMeaning, strDesignator);

		// Setting Acquisition Context Values for Type = NUMERIC
		{
			acquisitionContextValue.SetType(SDICOS::AcquisitionContextSequence::AcquisitionContextModule::enumNumeric);

			// Required values for Measurement Units
			SDICOS::DcsShortString strUnits;  // Code Value for units, may only be 16 characters max, cannot contain backslash
			SDICOS::DcsLongString strUnitsMeaning; // Human readable meaning for units
			SDICOS::DcsCodeString strUnitsMapping; // Mapping resource for units, may only contain capital letters, numbers, spaces, and underscores. 16 characters max.
			SDICOS::DcsDateTime strContextGroupVersion; // DateTime for the Context Group Version for the units

			// Set the Measurement Units, required if Type = NUMERIC
			acquisitionContextValue.SetMeasurementUnits("UNIT VALUE", "Human readable expalanation of units", "MAPPING", SDICOS::DcsDateTime(SDICOS::DcsDate::Today(), SDICOS::DcsTime::Now()));

			// Get the Measurement Units
			acquisitionContextValue.GetMeasurementUnits(strUnits, strUnitsMeaning, strUnitsMapping, strContextGroupVersion);

			// Numeric Values
			SDICOS::Array1D<float> arrayValues;
			arrayValues.Add(123341.0321f);
			arrayValues.Add(8982.23f);

			// Set the Numeric Values
			acquisitionContextValue.SetNumericValues(arrayValues);

			// Get the Numeric Values
			SDICOS::Array1D<float> arrayValuesGet;
			acquisitionContextValue.GetNumericValues(arrayValuesGet);

			// Add the AcquisitionContextValue to the AcquisitionContext
			acquisitionContext.AddAcquisitionContextValue(acquisitionContextValue);
		}

		// Setting Acquisition Context Values for Type = DATE
		{
			acquisitionContextValue.SetType(SDICOS::AcquisitionContextSequence::AcquisitionContextModule::enumDate);

			// Set the Date
			acquisitionContextValue.SetDate(SDICOS::DcsDate::Today());

			// Get the Date
			SDICOS::DcsDate strDate;
			acquisitionContextValue.GetDate(strDate);

			// Add the AcquisitionContextValue to the AcquisitionContext
			acquisitionContext.AddAcquisitionContextValue(acquisitionContextValue);
		}

		// Setting Acqusition Context Values for Type = TIME
		{
			acquisitionContextValue.SetType(SDICOS::AcquisitionContextSequence::AcquisitionContextModule::enumTime);

			// Set the Time
			acquisitionContextValue.SetTime(SDICOS::DcsTime::Now());

			// Get the Time
			SDICOS::DcsTime strTime;
			acquisitionContextValue.GetTime(strTime);

			// Add the AcquisitionContextValue to the AcquisitionContext
			acquisitionContext.AddAcquisitionContextValue(acquisitionContextValue);
		}

		// Setting Acquisition Context Values for Type = PNAME
		{
			acquisitionContextValue.SetType(SDICOS::AcquisitionContextSequence::AcquisitionContextModule::enumPName);

			// Set the Person Name
			acquisitionContextValue.SetPersonName("Firstname Lastname");

			// Get the Person Name
			SDICOS::DcsPersonName strPersonName;
			acquisitionContextValue.GetPersonName(strPersonName);

			// Add the AcquisitionContextValue to the AcquisitionContext
			acquisitionContext.AddAcquisitionContextValue(acquisitionContextValue);
		}

		// Setting Acquisition Context Values for Type = TEXT
		{
			acquisitionContextValue.SetType(SDICOS::AcquisitionContextSequence::AcquisitionContextModule::enumText);

			// Set the text
			acquisitionContextValue.SetTextValue("Long text value for the acquisition context information");

			// Get the text
			SDICOS::DcsUnlimitedText strText;
			acquisitionContextValue.GetTextValue(strText);

			// Add the AcquisitionContextValue to the AcquisitionContext
			acquisitionContext.AddAcquisitionContextValue(acquisitionContextValue);
		}

		// Setting Acquisition Context Values for Type not Set
		{
			// Set the Concept Code Sequence
			// If type is not set to one of the above values, must set concept code sequence
			// Concept Value may only be 16 characters long and cannot include a backslash
			// DESIGNATOR may only be 16 characters long. Can only contain capital lettrs, numbers, spaces, and underscores
			acquisitionContextValue.SetConceptCodeSequence("Concept Value", "Human readable explanation for concept value", "DESIGNATOR");

			// Get the Concept Code Sequence
			SDICOS::DcsShortString strCodeValue, strCodeDesignator;
			SDICOS::DcsLongString strCodeMeaning;
			acquisitionContextValue.GetConceptCodeSequence(strCodeValue, strCodeMeaning, strCodeDesignator);

			// Add the AcquisitionContextValue to the AcquisitionContext
			acquisitionContext.AddAcquisitionContextValue(acquisitionContextValue);
		}

		// Any Value Type can have referenced frames
		// Required if the Acquisition Context only applies to specific frames
		{
			// Required values for the referenced frames
			SDICOS::Array1D<SDICOS::S_UINT16> arrayFrames;
			arrayFrames.Add(1);
			arrayFrames.Add(2);

			// Set the Referenced Frames
			acquisitionContextValue.SetReferencedFrameNumbers(arrayFrames);

			// Get the Referenced Frames
			SDICOS::Array1D<SDICOS::S_UINT16> arrayFramesGet;
			acquisitionContextValue.GetReferencedFrameNumbers(arrayFramesGet);

			// Referenced Frame Numbers are optional
			// Can check if the Referenced Frame Numbers are set and Delete them
			acquisitionContextValue.HasReferencedFrameNumbers();
			acquisitionContextValue.DeleteReferencedFrameNumbers();

			// Add the AcquisitionContextValue to the AcquisitionContext
			acquisitionContext.AddAcquisitionContextValue(acquisitionContextValue);
		}
	}
}

int main()
{
	// New functionality common to multiple modalities
	ParentChanges();
	// New functionality within User DX
	BaseClassFeatures();
    return 0;
}