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
#ifndef _STRATOVAN_DICOS_ITINERARY_MODULE_H_
#define _STRATOVAN_DICOS_ITINERARY_MODULE_H_

#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/ErrorLog.h"

namespace SDICOS
{

///
/// \class ItineraryModule 
/// \brief Implements Itinerary Module
/// SPECREF V03 Section 4.2, Table 14
///
/// The ItineraryModule is an optional module in the Object of Inspection (OOI) Modules.
/// It is present in CT(EDS), DX(AT), AIT2D, AIT3D, QR and TDR IODs.
/// The Itinerary Module specifies attributes that describe and identify the route and segments of an OOI
/// journey. The Itinerary Module contains attributes that are common for all Objects of Inspection (OOI) owners.
///
class ItineraryModule
{
public:
	
	/// Default Constructor
	ItineraryModule();
	
	/// Copy Constructor
	ItineraryModule(const ItineraryModule &itinerarymodule);

	/// Destructor
	virtual ~ItineraryModule();
	
	/// Assignment operator
	ItineraryModule& operator=(const ItineraryModule &itinerarymodule);
	
	/// Comparison operator
	bool operator==(const ItineraryModule &itinerarymodule)const;

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false is returned if attributes were specified or if some were invalid.
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;
	
	/// Delete data structures and reset to default state
	void FreeMemory();
	
	/// Set Itinerary ID : Tag (4010, 1051)
	/// @param strItineraryID Param 1, ID : Tag (4010, 1051), VR = LO [optional]
	/// @return true/false false is given Itinerary ID is invalid.
	bool SetItineraryID(const DcsLongString &strItineraryID);

	/// @see SetItineryID
	DcsLongString GetItineraryID()const;

	/// Set the itinerary ID so that it is not written to the DICOS file
	void DeleteItineraryID();
	
	/// Enumeration for Itinerary Identification Type
	typedef enum
	{
		enumUnknownItineraryIdType,	///< Does not match defined terms

		enumCarrier,	///< "CARRIER"
		enumAgent,		///< "AGENT"

	}ITINERARY_ID_TYPE;

	/// Set Itinerary ID Type : Tag (4010, 1052)
	///	@param nType Itinerary ID Type : Tag (4010, 1052), VR = SH [optional]
	///			i) values: "CARRIER", "AGENT"
	/// @return true/false
	bool SetItineraryIDType(const ITINERARY_ID_TYPE nType);

	/// @see SetItineraryIdType
	ITINERARY_ID_TYPE GetItineraryIDType()const;

	/// @see SetItineraryIdType
	/// @return A DcsString set to "" if no Itinerary ID Type is set
	DcsString GetItineraryIDTypeAsString()const;

	/// Set Itinerary Id Type so that it is not written to the DICOS file
	void DeleteItineraryIDType();
	
	/// Itinerary ID Assigning Authority : Tag (4010, 1053)
	///	@param strItineraryIdAssigningAuthority Assigning Authority : Tag (4010, 1053), VR = LO [optional]
	/// @return true/false
	bool SetItineraryIDAssigningAuthority(const DcsLongString &strItineraryIdAssigningAuthority);

	/// @see SetItineraryIdAssigningAuthority
	DcsLongString GetItineraryIDAssigningAuthority()const;

	/// Set Itinerary ID Assignment Authority
	void DeleteItineraryIDAssigningAuthority();
	
	static DcsString ItineraryIDTypeAsString(const ITINERARY_ID_TYPE idType);
		
	///
	/// \class ItineraryRouteSegment
	/// \brief Item in Route Segment Sequence, Tag (4010, 100A)
	///
	/// The ItineraryRouteSegment is one entry in the Route Segment Sequence
	/// and describes one component of a potentially multi component journey.
	///
	/// Itinerary Route Segment Attributes:
	/// Note that all attributes in the ItineraryRouteSegment are optional per the DICOS spec.
	///
	///	  - Route ID: Unique Route Identifier such as IATA Flight ID or flight designator.
	///	  - Route ID Assigning Authority: Assigning authority of Route ID. Always set to "IATA".
	///	  - Inbound Arrival Type: Owners method of arrival at itinerary segment start point.
	///	  - Route Segment ID: Identifier for itinerary route segment
	///	  - Carrier ID: Unique carrier designator
	///	  - Carrier ID Assigning Authority: Assigning authority if carrier ID. Set to "ICAO".
	///	..- Boarding Pass ID: Unique identifier for boarding pass associated with the OOI.
	class ItineraryRouteSegment
	{
	public:
		/// Default Constructor
		ItineraryRouteSegment();
		
		/// Copy Constructor
		ItineraryRouteSegment(const ItineraryRouteSegment &itineraryroutesegment);

		/// Destructor
		virtual ~ItineraryRouteSegment();
		
		/// Assignment operator
		ItineraryRouteSegment& operator=(const ItineraryRouteSegment &itineraryroutesegment);
		
		/// Comparison operator
		bool operator==(const ItineraryRouteSegment &itineraryroutesegment)const;

		/// Initialize the class attributes from the given AttributeManager
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not fetched
		///							or if some were invalid.
		virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Copy the attributes from the module into the given AttributeManager
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not uploaded.
		virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Attempt to set all required and optional attributes from the given AttributeManager
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false is returned if attributes were specified or if some were invalid.
		virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Determine if all needed attributes (required and conditionally required) are set
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

		bool IsValid() const;
		
		/// Delete data structures and reset to default state
		void FreeMemory();
		
		/// Enumeration for assigning authority of Route ID
		typedef enum
		{
			enumUnknownRouteIdAssigningAuthority,	///< Does not match defined Code Values

			enumIATAAssigningAuthority,	///< "IATA"
		}ROUTE_ID_ASSIGNING_AUTHORITY;
		
		/// Enumeration for owners method of arrival at itinerary segment start point
		typedef enum
		{
			enumUnknownInboundArrivalType,	///< Does not match defined Code Values

			enumRoad,		///< "ROAD"
			enumAir,		///< "AIR"
			enumRailMetro,	///< "RAIL_METRO"
		}INBOUND_ARRIVAL_TYPE;

		/// Enumeration for assigning authority of the CarrierID
		typedef enum
		{
			enumUnknownCarrierIdAssigningAuthority,	///< Does not match defined Code Values

			enumICAOAssigningAuthority,	///< "ICAO"
		}CARRIER_ID_ASSIGNING_AUTHORITY;

		// Enumeration for Route Segment Location Id Type
		typedef enum
		{
			enumUnknownRouteSegmentLocationIdType,	///< Does not match defined Code Values

			enumIATARouteSegmentLocation,	///< "IATA"
			enumICAORouteSegmentLocation,	///< "ICAO"
		}ROUTE_SEGMENT_LOCATION_ID_TYPE;

		/// Enumeration for assigning authority of the Route Segment Location ID
		typedef enum
		{
			enumUnknownInternationalRouteSegment,	///< Does not match defined Code Values

			enumYes,	///< "YES"
			enumNo,		///< "NO"

		}INTERNATIONAL_ROUTE_SEGMENT;

		/// Set Route ID that uniquely identifies the route this segment belongs to: Tag (4010, 1054)
		/// @param strRouteID Route ID : Tag (4010, 1054), VR = SH [optional]
		/// @return true/false false if strRouteID is not a valid DcsShortString
		bool SetRouteID(const DcsShortString &strRouteID);

		/// @see SetRouteID
		DcsShortString GetRouteID()const;

		/// Set attribute so that it is not written to the DICOS file
		void DeleteRouteID();
		
		/// Get Route ID Assigning Authority : Tag (4010, 1055), VR = SH [required if "Route ID" is set]
		///	-Value must be "IATA".
		/// @return Always return DcsString with value "IATA" regardless if RouteID is specified.
		DcsString GetRouteIdAssigningAuthority()const;

		/// Set Inbound Arrival Type indicating how the OOI arrived to this segment: Tag (4010, 1056)
		/// @param nInboundArrivalType Inbound Arrival Type : Tag (4010, 1056), VR = CS [optional]
		///		i) Values: "ROAD", "AIR", "RAIL_METRO"
		/// @return true/false
		bool SetInboundArrivalType(const INBOUND_ARRIVAL_TYPE nInboundArrivalType);

		/// @see SetInboundArrivalType
		INBOUND_ARRIVAL_TYPE GetInboundArrivalType()const;

		/// @see SetInboundArrivalType
		DcsCodeString GetInboundArrivalTypeAsString()const;

		/// Set Inbound Arrival Type so that is it not written to the DICOS File
		void DeleteInboundArrivalType();
		
		/// Set Route Segment ID that uniquely identifies this segment in the route : Tag (4010, 1007)
		/// @param strRouteSegmentID Route Segment ID : Tag (4010, 1007), VR = SH [optional]
		bool SetRouteSegmentID(const DcsShortString &strRouteSegmentID);

		/// @see SetRouteSegmentID
		DcsShortString GetRouteSegmentID()const;

		/// Delete Route Segment ID so that it is not written to the DICOS file
		void DeleteRouteSegmentID();
		
		/// Set Carrier ID that the uniquely identifies the carrier operating the route segment
		/// @param strCarrierID Carrier ID : Tag (4010, 1058), VR = SH [optional]
		/// @return true/false false if strCarrierID is not a valid DcsShortString
		bool SetCarrierID(const DcsShortString &strCarrierID);

		/// @see SetCarrierID
		DcsShortString GetCarrierID()const;

		/// Set carrier ID so that it is not written to the DICOS file
		void DeleteCarrierID();
		
		/// Get Carrier ID Assigning Authority : Tag (4010, 1059), VR = CS [required if "Carrier ID" is set]
		/// Value must be "ICAO"
		CARRIER_ID_ASSIGNING_AUTHORITY GetCarrierIdAssigningAuthority()const;

		/// @return Always return DcsString with value "ICAO"
		DcsString GetCarrierIdAssigningAuthorityAsString()const;

		/// Set Boarding Pass ID : Tag (4010, 101A)
		///	@param strBoardingPassID Boarding Pass ID : Tag (4010, 101A), VR = SH [optional]
		/// @return true/false
		bool SetBoardingPassID(const DcsShortString &strBoardingPassID);

		/// @see SetBoardingPassID
		DcsShortString GetBoardingPassID()const;

		/// Set boarding pass ID so that it is not written to the DICOS file
		void DeleteBoardingPassID();
		
		/// Set Route Segment Start Location ID : Tag (4010, 101E)
		/// @param strRouteSegmentStartLocationID Route Segment Start Location ID : Tag (4010, 101E), VR = SH [optional]
		/// @return true/false
		bool SetRouteSegmentStartLocationID(const DcsShortString &strRouteSegmentStartLocationID);

		/// @see SetRouteSegmentStartLocationID
		DcsShortString GetRouteSegmentStartLocationID()const;

		/// Set Route Segment Start Location ID so that it is not written to the DICOS File
		void DeleteRouteSegmentStartLocationID();
		
		/// Set Route Segment End Location ID : Tag (4010, 101F)
		/// @param strRouteSegmentEndLocationID Route Segment End Location ID : Tag (4010, 101F), VR = SH [optional]
		/// @return true/false
		bool SetRouteSegmentEndLocationID(const DcsShortString &strRouteSegmentEndLocationID);

		/// @see SetRouteSegmentEndLocationID
		DcsShortString GetRouteSegmentEndLocationID()const;

		/// Set Route Segment End Location ID so that it is not written to the DICOS File
		void DeleteRouteSegmentEndLocationID();
		
		/// Set Route Segment Location ID Type : Tag (4010, 1020)
		///	@param nType Route Segment Location ID Type : Tag (4010, 1020), VR = CS [required if "Route Segment Start Location ID" or "Route Segment End Location ID" are set]
		///		i) Values: "IATA", "ICAO"
		/// @return true/false
		bool SetRouteSegmentLocationIdType(const ROUTE_SEGMENT_LOCATION_ID_TYPE nType);

		/// @see SetRouteSegmentLocationIdType
		ROUTE_SEGMENT_LOCATION_ID_TYPE GetRouteSegmentLocationIdType()const;
		
		/// @see SetRouteSegmentLocationIdType
		/// @return If the Location ID Type is unknown return a DcsString set to ""
		DcsString GetRouteSegmentLocationIdTypeAsString()const;

		/// Set Route Segment Start Time : Tag (4010, 1025)
		///	@param strDateTime Route Segment Start Date and Time : Tag (4010, 1025), VR = DT [optional]
		/// @return true/false
		bool SetRouteSegmentStartTime(const DcsDateTime &strDateTime);

		/// @see SetRouteSegmentStartTime
		DcsDateTime GetRouteSegmentStartTime()const;

		/// Delete Route Segment Start Time so that it is not written to the DICOS file
		void DeleteRouteSegmentStartTime();
		
		/// Set Route Segment Start End : Tag (4010, 1026)
		///	@param strDateTime Route Segment End Date and Time : Tag (4010, 1026), VR = DT [optional]
		/// @return true/false
		bool SetRouteSegmentEndTime(const DcsDateTime &strDateTime);

		/// @see SetRouteSegmentEndTime
		DcsDateTime GetRouteSegmentEndTime()const;

		/// Delete Route Segment End Time so that it is not written to the DICOS file
		void DeleteRouteSegmentEndTime();
		
		/// Set Assigned Location : Tag (4010, 102A)
		///	@param strAssignedLocation Assigned Location : Tag (4010, 102A), VR = SH [optional]
		/// @return true/false
		bool SetAssignedLocation(const DcsShortString &strAssignedLocation);

		/// @see SetAssignedLocation
		DcsShortString GetAssignedLocation()const;

		/// Set assigned location so that it is not written to the DICOS file
		void DeleteAssignedLocation();
		
		/// Set International Route Segment : Tag (4010, 1028)
		///	@param nInternationalRouteSegment International Route Segment : Tag (4010, 1028), VR = SH [required if "Route Segment Start Location ID" are set]
		///		i) Values: "YES", "NO"
		/// @return true/false
		bool SetInternationalRouteSegment(const INTERNATIONAL_ROUTE_SEGMENT nInternationalRouteSegment);

		/// @see SetInternationalRouteSegment
		INTERNATIONAL_ROUTE_SEGMENT GetInternationalRouteSegment()const;

		/// @see SetInternationalRouteSegment
		/// @return DcsCodeString("") if no segment is set
		DcsCodeString GetInternationalRouteSegmentAsString()const;

	private:
		class ImplItineraryRouteSegment;
		ImplItineraryRouteSegment	*m_pImplItineraryRouteSegment; ///< Internal implementation
		
		ImplItineraryRouteSegment* GetImpl();
		const ImplItineraryRouteSegment* GetImpl() const;
	};

	///
	/// \typedef 	typedef Array1D<ItineraryRouteSegment> ItineraryRouteArray
	///
	typedef Array1D<ItineraryRouteSegment> ItineraryRouteArray;
	
	/// Set Route Segment Sequence : Tag (4010, 100A), VR = SQ [optional]
	/// @param arrayRouteSegments Array of route segments
	/// @return true/false
	bool SetItineraryRouteSegments(const ItineraryRouteArray &arrayRouteSegments);

	/// @see SetItineraryRouteSegments
	bool GetItineraryRouteSegments(ItineraryRouteArray &arrayRouteSegments)const;

	/// @see SetItineraryRouteSegments
	const ItineraryRouteArray& GetItineraryRouteSegments() const;
	
	/// @see SetItineraryRouteSegments
	const ItineraryRouteArray* GetItineraryRouteSegmentsPtr() const;
		
	/// @see SetItineraryRouteSegments
	ItineraryRouteArray* GetItineraryRouteSegmentsPtr();
		
	/// Remove route segments so that they are not written to the DICOS file
	void DeleteItineraryRouteSegments();
private:
	class ImplItineraryModule;
	mutable ImplItineraryModule	*m_pImplItineraryModule; ///< Internal implementation
	
	ImplItineraryModule* GetImpl();
	const ImplItineraryModule* GetImpl() const;
};

}//namespace SDICOS

#endif