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
#ifndef _STRATOVAN_DICOS_ITINERARY_MODULE_USER_H_
#define _STRATOVAN_DICOS_ITINERARY_MODULE_USER_H_

#include "SDICOS/ItineraryModule.h"
#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/ErrorLog.h"

namespace SDICOS
{

	///
	/// \class ItineraryUser 
	/// \brief Implements Itinerary Module User Level API
	///
	/// The Itinerary Module is an optional module in the Object of Inspection (OOI) Modules:
	/// It is present in CT(EDS), DX(AT), AIT2D, AIT3D, QR and TDR IODs.
	/// 
	/// The Itinerary specifies attributes that describe and identify the route and segments of an OOI
	/// journey. The Itinerary contains attributes that are common for all Objects of Inspection (OOI) owners.
	///
	class ItineraryUser
	{
	public:

		/// Default Constructor
		ItineraryUser();

		/// Copy Constructor
		ItineraryUser(const ItineraryUser& itinerarymodule);

		/// Destructor
		virtual ~ItineraryUser();

		/// Assignment operator
		ItineraryUser& operator=(const ItineraryUser& itinerarymodule);

		/// Comparison operator
		bool operator==(const ItineraryUser& itinerarymodule)const;

		/// Comparison operator
		bool operator!=(const ItineraryUser& itinerarymodule)const;

		/// Read from an ItineraryModule
		/// @param rhs ItineraryModule
		/// @param el ErrorLog
		/// @return trie/false
		bool Read(const ItineraryModule& rhs, ErrorLog& el);

		/// Write to an ItineraryModule
		/// @param lhs ItineraryModule
		/// @param el ErrorLog
		/// @return true/false
		bool Write(ItineraryModule& lhs, ErrorLog& el) const;

		/// Delete data structures and reset to default state
		void FreeMemory();

		/// Set Itinerary ID
		/// @param strItineraryID Itinerary Id
		/// @return true/false false is given Itinerary ID is invalid.
		bool SetItineraryID(const DcsLongString& strItineraryID);

		/// @see SetItineryID
		DcsLongString GetItineraryID()const;

		/// Set the itinerary ID so that it is not written to the DICOS file
		void DeleteItineraryID();

		/// Set Itinerary ID Type : Tag (4010, 1052)
		///	@param nType Itinerary ID Type : Tag (4010, 1052), VR = SH [optional]
		///			i) values: "CARRIER", "AGENT"
		/// @return true/false
		bool SetItineraryIDType(const ItineraryModule::ITINERARY_ID_TYPE nType);

		/// @see SetItineraryIdType
		ItineraryModule::ITINERARY_ID_TYPE GetItineraryIDType()const;

		/// @see SetItineraryIdType
		/// @return A DcsString set to "" if no Itinerary ID Type is set
		DcsString GetItineraryIDTypeAsString()const;

		/// Set Itinerary Id Type so that it is not written to the DICOS file
		void DeleteItineraryIDType();

		/// [OPTIONAL] Itinerary ID Assigning Authority
		///	@param strItineraryIdAssigningAuthority Assigning Authority
		/// @return true/false
		bool SetItineraryIDAssigningAuthority(const DcsLongString& strItineraryIdAssigningAuthority);

		/// @see SetItineraryIdAssigningAuthority
		DcsLongString GetItineraryIDAssigningAuthority()const;

		/// Set Itinerary ID Assignment Authority
		void DeleteItineraryIDAssigningAuthority();

		///
		/// \class ItineraryRouteSegment
		/// \brief Item in Route Segment 
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
		///	  - Boarding Pass ID: Unique identifier for boarding pass associated with the OOI.
		/// 
		class ItineraryRouteSegment
		{
		public:
			friend class ItineraryUser;

			/// Default Constructor
			ItineraryRouteSegment();

			/// Copy Constructor
			ItineraryRouteSegment(const ItineraryRouteSegment& itineraryroutesegment);

			/// Destructor
			virtual ~ItineraryRouteSegment();

			/// Assignment operator
			ItineraryRouteSegment& operator=(const ItineraryRouteSegment& itineraryroutesegment);

			/// Comparison operator
			bool operator==(const ItineraryRouteSegment& itineraryroutesegment)const;

			/// Comparison Operator
			bool operator!=(const ItineraryRouteSegment& itineraryroutesegment)const;

			/// @brief Read from ItineraryModule::ItineraryRouteSegment
			/// @param rhs ItineraryRouteSegment
			/// @param el ErrorLog
			/// @return true/false
			bool Read(const ItineraryModule::ItineraryRouteSegment& rhs, ErrorLog& el);
			
			/// @brief Write to ItineraryModule::ItineraryRouteSegment
			/// @param lhs ItineraryRouteSegment
			/// @param el ErrorLog
			/// @return true/false
			bool Write(ItineraryModule::ItineraryRouteSegment& lhs, ErrorLog& el) const;

			/// Delete data structures and reset to default state
			void FreeMemory();

			/// Set Route ID that uniquely identifies the route this segment belongs to.
			/// @param strRouteID Route ID 
			/// @return true/false false if strRouteID is not a valid DcsShortString
			bool SetRouteID(const DcsShortString& strRouteID);

			/// @see SetRouteID
			DcsShortString GetRouteID()const;

			/// Set attribute so that it is not written to the DICOS file
			void DeleteRouteID();

			/// Get Route ID Assigning Authority
			///	-Value must be "IATA".
			/// @return Always return DcsString with value "IATA" regardless if RouteID is specified.
			DcsString GetRouteIdAssigningAuthority()const;

			/// Set Inbound Arrival Type indicating how the OOI arrived to this segment.
			/// @param nInboundArrivalType Inbound Arrival Type. Values: "ROAD", "AIR", "RAIL_METRO"
			/// @return true/false
			bool SetInboundArrivalType(const ItineraryModule::ItineraryRouteSegment::INBOUND_ARRIVAL_TYPE nInboundArrivalType);

			/// @see SetInboundArrivalType
			ItineraryModule::ItineraryRouteSegment::INBOUND_ARRIVAL_TYPE GetInboundArrivalType()const;

			/// @see SetInboundArrivalType
			DcsString GetInboundArrivalTypeAsString()const;

			/// Set Inbound Arrival Type so that is it not written to the DICOS File
			void DeleteInboundArrivalType();

			/// Set Route Segment ID that uniquely identifies this segment in the route,
			/// @param strRouteSegmentID Route Segment ID
			bool SetRouteSegmentID(const DcsShortString& strRouteSegmentID);

			/// @see SetRouteSegmentID
			DcsShortString GetRouteSegmentID()const;

			/// Delete Route Segment ID so that it is not written to the DICOS file
			void DeleteRouteSegmentID();

			/// Set Carrier ID that the uniquely identifies the carrier operating the route segment
			/// @param strCarrierID Carrier ID
			/// @return true/false false if strCarrierID is not a valid DcsShortString
			bool SetCarrierID(const DcsShortString& strCarrierID);

			/// @see SetCarrierID
			DcsShortString GetCarrierID()const;

			/// Set carrier ID so that it is not written to the DICOS file
			void DeleteCarrierID();

			/// Get Carrier ID Assigning Authority
			/// Value must be "ICAO"
			ItineraryModule::ItineraryRouteSegment::CARRIER_ID_ASSIGNING_AUTHORITY GetCarrierIdAssigningAuthority()const;

			/// @return Always return DcsString with value "ICAO"
			DcsString GetCarrierIdAssigningAuthorityAsString()const;

			/// Set Boarding Pass ID
			///	@param strBoardingPassID Boarding Pass ID
			/// @return true/false
			bool SetBoardingPassID(const DcsShortString& strBoardingPassID);

			/// @see SetBoardingPassID
			DcsShortString GetBoardingPassID()const;

			/// Set boarding pass ID so that it is not written to the DICOS file
			void DeleteBoardingPassID();

			/// Set Route Segment Start Location ID
			/// @param strRouteSegmentStartLocationID Route Segment Start Location ID
			/// @return true/false
			bool SetRouteSegmentStartLocationID(const DcsShortString& strRouteSegmentStartLocationID);

			/// @see SetRouteSegmentStartLocationID
			DcsShortString GetRouteSegmentStartLocationID()const;

			/// Set Route Segment Start Location ID so that it is not written to the DICOS File
			void DeleteRouteSegmentStartLocationID();

			/// Set Route Segment End Location ID
			/// @param strRouteSegmentEndLocationID Route Segment End Location ID
			/// @return true/false
			bool SetRouteSegmentEndLocationID(const DcsShortString& strRouteSegmentEndLocationID);

			/// @see SetRouteSegmentEndLocationID
			DcsShortString GetRouteSegmentEndLocationID()const;

			/// Set Route Segment End Location ID so that it is not written to the DICOS File
			void DeleteRouteSegmentEndLocationID();

			/// Set Route Segment Location ID Type
			///	@param nType Route Segment Location ID Type. Values: "IATA", "ICAO"
			/// @return true/false
			bool SetRouteSegmentLocationIdType(const ItineraryModule::ItineraryRouteSegment::ROUTE_SEGMENT_LOCATION_ID_TYPE nType);

			/// @see SetRouteSegmentLocationIdType
			ItineraryModule::ItineraryRouteSegment::ROUTE_SEGMENT_LOCATION_ID_TYPE GetRouteSegmentLocationIdType()const;

			/// @see SetRouteSegmentLocationIdType
			/// @return If the Location ID Type is unknown return a DcsString set to ""
			DcsString GetRouteSegmentLocationIdTypeAsString()const;

			/// Set Route Segment Start Time
			///	@param strDateTime Route Segment Start Date and Time
			/// @return true/false
			bool SetRouteSegmentStartTime(const DcsDateTime& strDateTime);

			/// @see SetRouteSegmentStartTime
			DcsDateTime GetRouteSegmentStartTime()const;

			/// Delete Route Segment Start Time so that it is not written to the DICOS file
			void DeleteRouteSegmentStartTime();

			/// Set Route Segment Start End
			///	@param strDateTime Route Segment End Date and Time
			/// @return true/false
			bool SetRouteSegmentEndTime(const DcsDateTime& strDateTime);

			/// @see SetRouteSegmentEndTime
			DcsDateTime GetRouteSegmentEndTime()const;

			/// Delete Route Segment End Time so that it is not written to the DICOS file
			void DeleteRouteSegmentEndTime();

			/// Set Assigned Location
			///	@param strAssignedLocation Assigned Location
			/// @return true/false
			bool SetAssignedLocation(const DcsShortString& strAssignedLocation);

			/// @see SetAssignedLocation
			DcsShortString GetAssignedLocation()const;

			/// Set assigned location so that it is not written to the DICOS file
			void DeleteAssignedLocation();

			/// Set International Route Segment
			///	@param nInternationalRouteSegment International Route Segment. Values: "YES", "NO"
			/// @return true/false
			bool SetInternationalRouteSegment(const ItineraryModule::ItineraryRouteSegment::INTERNATIONAL_ROUTE_SEGMENT nInternationalRouteSegment);

			/// @see SetInternationalRouteSegment
			ItineraryModule::ItineraryRouteSegment::INTERNATIONAL_ROUTE_SEGMENT GetInternationalRouteSegment()const;

			/// @see SetInternationalRouteSegment
			/// @return DcsCodeString("") if no segment is set
			DcsCodeString GetInternationalRouteSegmentAsString()const;

		private:
			class ImplItineraryRouteSegment;
			ImplItineraryRouteSegment* m_pImplItineraryRouteSegment; ///< Internal implementation

			ImplItineraryRouteSegment* GetImpl();
			const ImplItineraryRouteSegment* GetImpl() const;

			const ItineraryModule::ItineraryRouteSegment& GetModuleItineraryRouteSegment() const; 
		};

		/// Set Route Segments
		/// @param arrayRouteSegments Array of route segments
		/// @return true/false
		bool SetItineraryRouteSegments(const Array1D<ItineraryUser::ItineraryRouteSegment>& arrayRouteSegments);

		/// @see SetItineraryRouteSegments
		bool GetItineraryRouteSegments(Array1D<ItineraryUser::ItineraryRouteSegment>& arrayRouteSegments)const;

		/// Remove route segments so that they are not written to the DICOS file
		void DeleteItineraryRouteSegments();

		/// @see SetItineraryRouteSegments
		S_UINT32 GetNumItinerarySegments() const;

	private:
		class ItineraryUserImpl;
		mutable ItineraryUserImpl* m_pItineraryUserImpl;

		ItineraryUserImpl* GetImpl();
		const ItineraryUserImpl* GetImpl() const;
	};

}//namespace SDICOS

#endif