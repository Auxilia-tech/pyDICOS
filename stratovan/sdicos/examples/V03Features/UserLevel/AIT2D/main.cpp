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
#include "SDICOS/DICOS.h"

void ParentChanges()
{
	SDICOS::AIT2D ait;

	/*
	* Features for the ScanCommon parent class
	*/
	{
		SDICOS::ScanCommon& scanCommon = ait;

		/*
		* TIP Features
		*/
		{
			/*
			* TIP Library Name - a new optional tag to set the TIP library name
			*/
			{
				//Set the library name
				ait.SetTipLibraryName("EXAMLE LIBRARY NAME");
				
				//Check if the library name is set, if it is get it
				if(ait.HasTipLibraryName())
				{
					SDICOS::DcsShortText strLibraryName;
					strLibraryName = ait.GetTipLibraryName();
				}

				//Delete the library name
				ait.DeleteTipLibraryName();
			}

			/*
			* TIP Image Identifier - a new optional tag to set the TIP image identifier
			*/
			{
				//Set the image identifier
				ait.SetTipImageIdentifier("EXAMPLE IMAGE IDENTIFIER");

				//Check if the image identifier is set, if it is get it
				if(ait.HasTipImageIdentifier())
				{
					SDICOS::DcsShortText strImageIdentifier;
					strImageIdentifier = ait.GetTipImageIdentifier();
				}

				//Delete the image identifier
				ait.DeleteTipImageIdentifier();
			}

			/*
			* TIP Library Date - a new optional tag to set the TIP library date
			*/
			{
				//Set the library date
				SDICOS::DcsDateTime dtLibraryDate;
				dtLibraryDate.SetNow();
				ait.SetTipLibraryDate(dtLibraryDate);

				//Check if the library date is set, if it is get it
				if(ait.HasTipLibraryDate())
				{
					dtLibraryDate = ait.GetTipLibraryDate();
				}

				//Delete the library date
				ait.DeleteTipLibraryDate();
			}
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
		// by SDICOS::AIT2D::Write(...).
		ait.EnableObjectOfInspectionOwner();

		ait.IsObjectOfInspectionOwnerEnabled();

		// Reset Object of Inspection Owner Module attributes to defaults
		// IsObjectOfInspectionOwnerEnabled() returns false after calling.
		ait.DisableObjectOfInspectionOwner();

		// Get the Object Of Inspection Owner
		SDICOS::ObjectOfInspectionOwnerUser& owner = ait;

		// Set OOI Owner Module attributes
		owner.SetOwnerType(SDICOS::ObjectOfInspectionOwnerModule::enumBusiness);

		// Set Owner Risk Score
		SDICOS::S_INT16 nRiskScore = 5;
		owner.SetOwnerRiskScore(nRiskScore);

		// [REQUIRED] Set Owner Identification information
		owner.SetPrimaryIdentification("IdIssuingOrg", "IdValue", "OwnersName");
		owner.SetIDType(SDICOS::CodeDefinitions::enumPIV);

		owner.SetCountryOfResidence("USA", "United States");

		owner.SetCountryOfCitizenship("JPN", "Japan");

		// IMPORTANT: Do not confuse with ait.SetGender() 
		// which is the gender associated with the Object Of Inspection when it is a person.
		owner.SetOwnerGender(SDICOS::OOIOwnerIdentificationMacro::enumFemale);

		owner.SetAddress("owner address");

		SDICOS::Array1D<SDICOS::DcsLongString> vPhoneNumbers;
		vPhoneNumbers.Add(SDICOS::DcsLongString("1-415-345-5667"));
		owner.SetPhoneNumbers(vPhoneNumbers);

		// Owner's Organization Name
		owner.SetOrganizationName("org name");

		// Set Owner's Organization Address
		owner.SetOrganizationAddress("Owner Org Address");

		SDICOS::DcsDateTime dt;
		dt.SetNow();
		owner.SetCreationTime(dt);

		// Has the Owner Identity been removed
		owner.SetIdentityRemoved(true);

		SDICOS::Array1D<SDICOS::DcsLongString> deIdentificationMethods;
		deIdentificationMethods.Add(SDICOS::DcsLongString("De Identification Method"));
		owner.SetDeIdentificationMethod(deIdentificationMethods);

		// [REQUIRED] Describes the class of materials the owner is allowed to transport
		owner.SetTransportClassificationType(SDICOS::ObjectOfInspectionOwnerModule::enumMedical);
	}

	//
	// IODCommon derives from SDICOS::ItineraryUser to add support for the Itineray Module attributes
	//
	{
		// Itinerary attributes are disabled by default and must be enabled
		ait.EnableItinerary();

		// To disable the Itinerary attributes
		ait.DisableItinerary();

		// Get the ItineraryUser
		SDICOS::ItineraryUser& itinerary = ait;

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
		SDICOS::FrameOfReferenceUser &frameOfReference = ait;

		// Enable Frame of Reference attributes to be written during Write()
		// FrameOfReferenceUser attributes are disabled by default
		// void SDICOS::AIT2D::EnableFrameOfReference();
		ait.EnableFrameOfReference();

		// Frame Of Reference attributes will not be written during Write()
		// void SDICOS::AIT2D::DisableFrameOfReference();
		ait.DisableFrameOfReference();

		// Determine if Frame of Reference attributes are enabled and will be written during Write() invocations
		// bool SDICOS::AIT2D::IsFrameOfReferenceEnabled();
		ait.IsFrameOfReferenceEnabled();

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
		SDICOS::AcquisitionContextUser &acquisitionContext = ait;

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

void ImageChanges()
{
	SDICOS::AIT2D ait;

	/*
	* Image Type value 2 can be set using the new second parameter in SDICOS::AIT2D::SetImageType()
	*/
	{
		//Image Type Value 2 can be:
		// - enumContentAmplitude
		// - enumContentComplexAmplitude 
		// - enumNoImageCharacteristic
		//By default, value 2 is set to enumNoImageCharacteristic
		SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS nImageChar(SDICOS::AITImageType::enumContentAmplitude);

		//Value 2 can be set as the second parameter in SDICOS::AIT2D::SetImageType()
		ait.SetImageType(SDICOS::ImageType::enumOriginal, nImageChar);

		//Value 2 'get' function
		ait.GetImageCharacteristic();
	}

	/*
	* AIT Device Type has two new defined terms:
	* - enumHDActiveMMW for HD Active Millimeter Wave
	* - enumWTActiveMMW for Walk-Through Active Millimeter Wave
	*/
	{
		ait.SetAitDeviceType(SDICOS::AIT2DTypes::AIT2DImage::enumHDActiveMMW);
		ait.SetAitDeviceType(SDICOS::AIT2DTypes::AIT2DImage::enumWTActiveMMW);
	}

	/* Image Origin - a new required tag to set the image's origin
	*
	* Specifies the origin of the image valid values are:
	*	- enumMachine
	*	- enumAugmented
	*	- enumSynthetic
	*/
	{
		//'Set' function
		ait.SetImageOrigin(SDICOS::ImageCommon::enumMachine);
		ait.SetImageOrigin(SDICOS::ImageCommon::enumAugmented);
		ait.SetImageOrigin(SDICOS::ImageCommon::enumSynthetic);

		//'Get' function
		ait.GetImageOrigin();
	}

	/* Coordinate System - a new required tag to set the image's coordinate system
	*
	* Specifies the coordinate system of the image
	* valid values:
	*	- enumLHS
	*	- enumRHS
	*/
	{
		//'Set' function
		ait.SetCoordinateSystem(SDICOS::ImageCommon::enumLHS);
		ait.SetCoordinateSystem(SDICOS::ImageCommon::enumRHS);

		//'Get' function
		ait.GetCoordinateSystem();
	}
}

int main()
{
	ParentChanges(); //Updates common to multiple modalities
	ImageChanges(); //Updates related to the image

	return 0;
}
