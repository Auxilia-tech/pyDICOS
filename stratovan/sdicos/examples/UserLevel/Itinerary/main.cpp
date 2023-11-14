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
#include "SDICOS/DICOS.h"	//DICOS include header

/**
 * CreateCTWithItinerary shows how to use the itinerary API methods in IODCommon
 * to create a CT DICOS file with itinerary information.
 * 
 * In this example all itinerary attributes are set but in general
 * the itinerary attributes are optional and can be left unset as needed.
 */
bool CreateCTWithItinerary()
{
	/// Create a CT Series for a person Object of Inspection (OOI)
	/// For more details on using the User-Level API object SDICOS::CT see 
	/// the CTExample and UserCTExample
	SDICOS::CT ct(
		SDICOS::ObjectOfInspectionModule::enumTypePerson,
		SDICOS::CTTypes::CTImage::enumHighEnergy,
		SDICOS::CTTypes::CTImage::enumVolume,
		SDICOS::ImagePixelMacro::enumMonochrome2	// Minimum pixel value is black
	);
	ct.EnableItinerary();
	ct.SetGender(SDICOS::ObjectOfInspectionModule::enumGenderFemale);

	/// Acquisition time in seconds
	ct.SetImageAcquisitionDuration(5.2);
	
	/// Add one section of volume data to the CT Series
	///		Row and Column orientation vectors are (0,1,0) and (1,0,0)
	///		CT Frame Type Pixel Data Characteristics value is set to ORIGINAL
	///		CT Filter Type is set to NONE. CT Filter Material is not used.
	ct.SetNumberOfSections(1);
	
	SDICOS::Section * s = ct.GetSectionByIndex(0);
	s->SetFocalSpotSizeInMM(1.414f);			/// Used nominal size of the focal spot in MM.
	s->SetKVP(3.14f);							/// Peak kilo voltage output of the x-ray generator
	s->SetPositionInMM(10.0f, 20.0f, 15.0f);	/// Volume data location in MM
	s->SetSpacingInMM(1.0f, 2.0f, 10.0f);		/// Column spacing, row spacing and slice thickness.

	//	Set the Volume data for the CT Series section
	SDICOS::Volume& volume = s->GetPixelData();
	volume.Allocate(SDICOS::Volume::enumUnsigned16Bit,128,128,100);
	SDICOS::Array3DLarge<SDICOS::S_UINT16>& sectionData = *volume.GetUnsigned16();
	
	SDICOS::S_UINT16 * userData = new SDICOS::S_UINT16[volume.GetWidth()*volume.GetHeight()];

	//Initialize with dummy values
	memset(userData, 0, volume.GetWidth()*volume.GetHeight() * sizeof(SDICOS::S_UINT16));
	
	// Set volume data by setting each XY plane
	for(SDICOS::S_UINT32 i = 0; i < volume.GetDepth(); ++i) 
	{
		SDICOS::Array2D<SDICOS::S_UINT16>& xyPlane = sectionData[i];
		SDICOS::S_UINT16 * pBuffer = xyPlane.GetBuffer();
		
		// The use can copy their data into pBuffer from another source or place it directly in pBuffer.
		memcpy(pBuffer, userData, sizeof(SDICOS::S_UINT16)*xyPlane.GetWidth()*xyPlane.GetHeight());
	}

	// Delete buffer
	SDICOS::DELETE_ARRAY(userData);

	//
	//	Create an Itinerary for the Object of Inspection (OOI)
	//	An itinerary contains:
	//		- Identification information for the whole itinerary
	//		- One or more Route Segments with segment-specific information
	//

	// Itinerary ID uniquely identifies the itinerary from a carrier, booking number etc.
	SDICOS::DcsLongString itineraryID("123-345-567"); 
	ct.SetItineraryID(itineraryID);

	// Indicate that the itineraryID came from an agent
	// use enumCarrier to indicate that it came from the carrier handling the OOI
	SDICOS::ItineraryModule::ITINERARY_ID_TYPE itineraryIDType(SDICOS::ItineraryModule::enumAgent);
	ct.SetItineraryIDType(itineraryIDType);
		
	SDICOS::DcsLongString itineraryIDAssigningAuthority("Agent Smith");
	ct.SetItineraryIDAssigningAuthority(itineraryIDAssigningAuthority);
		
	//
	// Set up route segments in the itinerary
	//
	SDICOS::Array1D<SDICOS::ItineraryUser::ItineraryRouteSegment> vRouteSegments;

	SDICOS::DcsShortString routeSegmentID0("SFO to LAX");
	SDICOS::ItineraryUser::ItineraryRouteSegment routeSegment0;

	routeSegment0.SetRouteSegmentID(routeSegmentID0);
	routeSegment0.SetRouteID("Wormhole 1");
	routeSegment0.SetInboundArrivalType(SDICOS::ItineraryModule::ItineraryRouteSegment::enumRailMetro);
			
	routeSegment0.SetCarrierID(SDICOS::DcsShortString("The Federation NCC1017A"));
	routeSegment0.SetBoardingPassID(SDICOS::DcsShortString("Mamma Mia"));
	routeSegment0.SetRouteSegmentStartLocationID(SDICOS::DcsShortString("SFO"));
	routeSegment0.SetRouteSegmentEndLocationID(SDICOS::DcsShortString("LAX"));
		
	// Assigning authority for the Route Segment Start and End Location IDs.
	routeSegment0.SetRouteSegmentLocationIdType(SDICOS::ItineraryModule::ItineraryRouteSegment::enumIATARouteSegmentLocation);
		
	SDICOS::DcsDateTime segmentStart(SDICOS::DcsDate::Today(),SDICOS::DcsTime::Now());
	routeSegment0.SetRouteSegmentStartTime(segmentStart);

	SDICOS::DcsDateTime segmentEnd(SDICOS::DcsDate::Today(),SDICOS::DcsTime(12,15,0,0));
	routeSegment0.SetRouteSegmentEndTime(segmentEnd);
		
	routeSegment0.SetAssignedLocation(SDICOS::DcsShortString("Seat A32"));
	routeSegment0.SetInternationalRouteSegment(SDICOS::ItineraryModule::ItineraryRouteSegment::enumNo);

	vRouteSegments.Add(routeSegment0);

	// Set up a second route segment in the itinerary
	SDICOS::DcsShortString routeSegmentID1 = "LAX to Pudong";
	SDICOS::ItineraryUser::ItineraryRouteSegment routeSegment1;

	routeSegment1.SetRouteSegmentID(routeSegmentID1);
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

	ct.SetItineraryRouteSegments(vRouteSegments);

	SDICOS::ErrorLog errorlog;
	SDICOS::Folder ctFolder("ItineraryExampleFiles");
	SDICOS::Filename ctFilename(ctFolder,"CTWithItinerary.dcs");
	
	if(!ct.Write(ctFilename,errorlog,SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cerr << "Itinerary Example unable to write DICOS File " << ctFilename << std::endl;
		std::cerr << errorlog << std::endl;
		return false;
	}
	else 
	{
		std::cout << "Itinerary Example wrote DICOS file " << ctFilename << std::endl;
		SDICOS::CT ctRead;
		if(ctRead.Read(ctFilename,errorlog))
		{
			if(ct != ctRead) 
			{
				std::cerr << "Original CT and read CT are not equal" <<std::endl;
				return false;
			}

			// Check that itinerary data matches
			bool bRes = (itineraryID == ctRead.GetItineraryID());
			bRes = (itineraryIDAssigningAuthority == ctRead.GetItineraryIDAssigningAuthority()) && bRes;
			bRes = (itineraryIDType == ctRead.GetItineraryIDType()) && bRes;

			SDICOS::Array1D<SDICOS::ItineraryUser::ItineraryRouteSegment> vRouteSegmentsRead;
			bRes = ctRead.GetItineraryRouteSegments(vRouteSegmentsRead) && bRes;
			bRes = (vRouteSegments == vRouteSegmentsRead) && bRes;

			if(!bRes) 
			{
				std::cerr << "Failed to validate itinerary data from " << ctFilename << std::endl;
				return false;
			} 
			else 
			{
				std::cerr << "Validated itinerary data from " << ctFilename << std::endl;
			}
		}
		else 
		{
			std::cerr << "Failed to read CT Series from " << ctFilename << std::endl;
			std::cerr << errorlog << std::endl;
			return false;
		}
	}
	
	return true;
}
///EndCreateCTWithItinerary

int main()
{
	bool bRes = CreateCTWithItinerary();
	return (bRes ? 0 : 1);
}
