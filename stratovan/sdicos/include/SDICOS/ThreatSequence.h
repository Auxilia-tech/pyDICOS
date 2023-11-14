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
#ifndef _STRATOVAN_DICOS_TDR_THREAT_SEQUENCE_H_
#define _STRATOVAN_DICOS_TDR_THREAT_SEQUENCE_H_

#include "SDICOS/ReferencedPotentialThreatObject.h"
#include "SDICOS/PersonSpecificTDR.h"
#include "SDICOS/BaggageSpecificTDR.h"
#include "SDICOS/AssessmentSequence.h"
#include "SDICOS/Array1D.h"

namespace SDICOS
{
namespace TDRTypes
{

/// \class ThreatSequence
/// \brief Threat Sequence Module
/// SPECREF V03 Section 12.5, Table 70
/// The ThreatSequence class implements the Threat Sequence Module, a conditionally required sequence (4010, 1011)
/// in the Threat Detection Report IE in the Threat Detection Report IOD.
class ThreatSequence
{
public:
	/// Default Constructor
	ThreatSequence();
	
	/// Copy Constructor
	ThreatSequence(const ThreatSequence &threatsequence);
	
	/// Destructor
	~ThreatSequence();

	/// Assignment operator
	ThreatSequence& operator=(const ThreatSequence &threatsequence);
	
	/// Equality comparison operator
	bool operator==(const ThreatSequence &threatsequence)const;
	
	/// Inequality comparison operator
	bool operator!=(const ThreatSequence &threatsequence)const;

	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Reset to default values
	void FreeMemory();

	/// \class ThreatItem
	/// \brief Item in Threat Sequence, Tag (4010, 1011)
	/// The ThreatItem contains the data for the "Threat Sequence" attribute
	/// of the Threat Sequence Module Tag (4010, 1011)
	class ThreatItem
	{
	public:
		/// Constructor
		ThreatItem();
		
		/// Copy Constructor
		ThreatItem(const ThreatItem &item);
		
		/// Destructor
		~ThreatItem();

		/// Reset to default state
		void FreeMemory();

		/// Assignment operator
		ThreatItem& operator=(const ThreatItem &item);
		
		/// Equality comparison operator
		bool operator==(const ThreatItem &item)const;
		
		/// Inequality comparison operator]
		bool operator!=(const ThreatItem &item)const;

		bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
		bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;
		bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Originating TDR Type attribute options
		typedef enum
		{
			enumOriginatingTDRUnknown = -1,	///< Invalid Originating TDR Type

			enumOriginatingTDRMachine = 1,	///< "MACHINE"
			enumOriginatingTDROperator,		///< "OPERATOR"
			enumOriginatingTDRGroundTruth,	///< "GROUND TRUTH"
			enumOriginatingTDRUndefined,	///< "UNDEFINED"
			
		} ORIGINATING_TDR_TYPE;

		/// Set Originating TDR Type : Tag (4010, 1027)
		/// VR = CS [required if TDR Type (4010, 1027), outside of Threat Sequence, is MOD_AGGREGATE, otherwise must not be present]
		/// @param nTDRType ORIGINATING_TDR_TYPE
		/// @return true/false false if enum value is not valid
		bool SetOriginatingTDRType(const ORIGINATING_TDR_TYPE nTDRType);

		/// @see SetOriginatingType
		/// @return enumOriginatingTDRUnknown if not set
		ORIGINATING_TDR_TYPE GetOriginatingTDRType() const;

		/// @see SetOriginatingType
		/// @return Empty string if no value is set
		DcsCodeString GetOriginatingTDRTypeAsString() const;

		/// @return true/false if Originating TDR Type is present
		bool HasOriginatingTDRType() const;

		/// Clear originating TDR Type string
		void DeleteOriginatingTDRType();

		/// Potential Threat Object ID : Tag (4010, 1010)
		/// @param nID PTO ID : Tag (4010, 1010), VR = US [required]
		bool SetID(const S_UINT16 nID);

		/// @see SetID
		S_UINT16 GetID()const;

		/// Potential Threat Object Start Time of Processing
		/// @param dtStartTime Start Time of Processing : Tag (4010, 1080), VR = DT [required]
		/// @return true if the processing start time is successfully set, false otherwise
		bool SetProcessingStartTime(const DcsDateTime dtStartTime);

		/// @see SetProcessingStartTime
		DcsDateTime GetProcessingStartTime()const;
		
		/// Potential Threat Object End Time of Processing
		/// @param dtEndTime End Time of Processing : Tag (4010, 1081), VR = DT [required]
		/// @return true if the processing end time is successfully set, false otherwise
		bool SetProcessingEndTime(const DcsDateTime dtEndTime);

		/// @see SetProcessingEndTime
		DcsDateTime GetProcessingEndTime()const;

		/// Potential Threat Object Total Time for Processing
		/// @param fTotalProcessingTimeMS Total Time for Processing in Milliseconds : Tag (4010, 1082), VR = FL [required]
		/// @return true if the total processing time is successfully set, false otherwise
		bool SetTotalProcessingTime(const float fTotalProcessingTimeMS);

		/// @see SetTotalProcessingTime
		float GetTotalProcessingTime()const;

		/// Set Referenced Potential Threat Object [required if using a PTO from a referenced TDR]
		bool SetReferencedPotentialThreatObject(const ReferencedPotentialThreatObject &ref);
	
		/// @see SetReferencedPotentialThreatObject
		bool GetReferencedPotentialThreatObject(ReferencedPotentialThreatObject &ref)const;
	
		/// @see SetReferencedPotentialThreatObject
		const ReferencedPotentialThreatObject& GetReferencedPotentialThreatObject() const;

		/// Set Assessment Sequence [required]
		bool SetAssessment(const AssessmentSequence &assessment);
		
		/// @see SetAssessment
		bool GetAssessment(AssessmentSequence &assessment)const;
		
		/// @see SetAssessment
		const AssessmentSequence& GetAssessment() const;
		
		AssessmentSequence& GetAssessment();
		
		/// Signal Generation Software Versions : Tag (0060, 7008) VM = 1 or more, VR = LO [optional]
		/// Defines version of software that converts original sensor data and transforms data for presentation or analysis.
		/// For 3D imaging devices this is the reconstruction software version used to generate the display 
		/// image from the raw detector dataand for 2D screening devices it is the transformation software/algorithm.
		/// version from detector data to display image.
		Array1D<DcsLongString>& GetSignalGenerationSoftwareVersion();
		const Array1D<DcsLongString>& GetSignalGenerationSoftwareVersion()const;
		/// Add a version
		void AddSignalGenerationSoftwareVersion(const DcsLongString& ds);
		/// Returns true if the data is set
		bool HasSignalGenerationSoftwareVersion()const;
		/// Delete the data
		void DeleteSignalGenerationSoftwareVersions();

		/// Enumeration for Dynamic Screening Flag
		typedef enum
		{
			enumUnknownDynamicScreeningFlag, ///< Invalid Dynamic Screening Flag
			enumBHS,	///< "BHS"
			enumSTIP,	///< "STIP"
			enumOther,	///< "OTHER"
			enumNone	///< "NONE"
		}DYNAMIC_SCREENING_FLAG;

		/// Dynamic Screening Flag : Tag (0060, 7010) VR = CS [optional]
		/// Defines the inspection mode. 
		/// Dynamic screening is an adaptive Risk Based Screening (RBS) security screening capability
		/// that provides personalized screening by adjusting screening parameters based on what is known about
		/// each passenger on the day of travel.It enables dynamic switching of automated detection algorithms for
		/// the screening of passengersand their belongings(including accessible property and checked baggage)
		/// based on passenger risk designations in a real-time fashion.
		/// @param nFlag	enum value to set the dynamic screening flag to, Unknown enumerations map to enumNone.
		/// @return true if the flag is successfully set, false otherwise
		bool SetDynamicScreeningFlag(const DYNAMIC_SCREENING_FLAG nFlag);
		/// @see SetDynamicScreeningFlag
		DYNAMIC_SCREENING_FLAG GetDynamicScreeningFlagEnum()const;
		/// @see SetDynamicScreeningFlag
		DcsString GetDynamicScreeningFlagString()const;
		/// Returns true if the data is set
		bool HasDynamicScreeningFlag()const;
		/// Delete the data
		void DeleteDynamicScreeningFlag();

		/// Set the Baggage TDR so that it is written to the DICOS file
		/// Enabling the Baggage TDR disables the PersonTDR
		/// @param bEnable true/false enable or disable the baggage TDR
		bool EnableBaggageTDR(const bool bEnable);
		
		/// Set Baggage Specific TDR [required if "OOI Type", tag (4010, 1042), is "BAGGAGE", found in ObjectOfInspectionModule]
		/// Setting the Baggage TDR removes an existing Person TDR.
		bool SetBaggageTDR(const BaggageSpecificTDR &baggagetdr);
	
		/// @see SetBaggageTDR
		bool GetBaggageTDR(BaggageSpecificTDR &baggagetdr)const;
		
		/// @see SetBaggageTDR
		BaggageSpecificTDR& GetBaggageTDR();
		
		/// @see SetBaggageTDR
		const BaggageSpecificTDR& GetBaggageTDR()const;
	
		/// Delete Baggage TDR so that it is not written to the DICOS file
		void DeleteBaggageTDR();
		
		/// Determine if a baggage tdr has been set.
		bool HasBaggageTDR() const;
		
		/// Set the Person TDR so that it is written to the DICOS file
		/// Enabling the Person TDR disables the Baggage TDR
		/// @param bEnable true/false enable or disable the baggage TDR
		bool EnablePersonTDR(const bool bEnable);
		
		/// Set Person Specific TDR [required if 'OOI Type' (4010, 1042) is 'PERSON', found in ObjectOfInspectionModule]
		/// Setting the Person TDR removes an existing Baggage TDR
		bool SetPersonTDR(const PersonSpecificTDR &persontdr);
	
		/// @see SetPersonTDR
		bool GetPersonTDR(PersonSpecificTDR &persontdr)const;
		
		/// @see SetPersonTDR
		PersonSpecificTDR& GetPersonTDR();
		
		/// @see SetPersonTDR
		const PersonSpecificTDR& GetPersonTDR()const;
		
		/// Delete person TDR so that it is not written to the DICOS file
		void DeletePersonTDR();

		/// Determine if a person TDR has been set
		bool HasPersonTDR() const;

	protected:
		class ImplThreatItem;
		ImplThreatItem	*m_pImplThreatItem; ///< Internal implementation
		
		ImplThreatItem* GetImpl();
		const ImplThreatItem* GetImpl() const;
	};

	/// Set Threat Sequence : Tag (4010, 1011), 
	/// VR = SQ [required if "Alarm Decision" (4010, 1031) is "ALARM"]
	bool SetPotentialThreatObject(const Array1D<ThreatItem> &arrayPotentialThreatObject);

	/// @see SetPotentialThreatObject
	bool GetPotentialThreatObject(Array1D<ThreatItem> &arrayPotentialThreatObject)const;

	/// @see SetPotentialThreatObject
	Array1D<ThreatItem>& GetPotentialThreatObject();
	/// @see SetPotentialThreatObject
	const Array1D<ThreatItem>& GetPotentialThreatObject()const;
	/// @see SetPotentialThreatObject
	bool AddPotentialThreatObject(const ThreatItem& threatItem);
	/// @see SetPotentialThreatObject
	S_UINT32 NumPTOs() const;
	
protected:
	class ImplThreatSequence;
	ImplThreatSequence	*m_pImplThreatSequence; ///< Internal implementation
	
	ImplThreatSequence* GetImpl();
	const ImplThreatSequence* GetImpl() const;
};

}//namespace TDRTypes
}//namespace SDICOS

#endif