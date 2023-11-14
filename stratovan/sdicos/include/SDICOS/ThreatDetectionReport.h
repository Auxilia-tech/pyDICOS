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
#ifndef _STRATOVAN_DICOS_TDR_THREAT_DETECTION_REPORT_H_
#define _STRATOVAN_DICOS_TDR_THREAT_DETECTION_REPORT_H_

#include "SDICOS/PersonIdentificationMacro.h"
#include "SDICOS/IdentificationEncodingType.h"

namespace SDICOS
{
namespace TDRTypes
{
	
///
/// \class ThreatDetectionReport
/// \brief Threat Detection Report Module
/// SPECREF V03 Section 12.4, Table 69
/// The ThreatDetectionReport class represents the Threat Detection Report Module
class ThreatDetectionReport
{
public:
	/// Constructor
	ThreatDetectionReport();
	
	/// Copy Constructor
	ThreatDetectionReport(const ThreatDetectionReport &tdr);
	
	/// Destructor
	~ThreatDetectionReport();

	/// Assignment operator
	ThreatDetectionReport& operator=(const ThreatDetectionReport &tdr);
	
	/// Equality Comparison operator
	bool operator==(const ThreatDetectionReport &tdr)const;
	
	/// Inequality comparison operator
	bool operator!=(const ThreatDetectionReport &tdr)const;

	/// Reset to default values
	void FreeMemory();
	
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

	/// Enumeration for Threat Detection Report Type
	/// Identifies the alarm decision type of the TDR
	typedef enum
	{
		enumUnknownTDRType = 0, ///< Does not match defined terms

		enumMachine,		///< "MACHINE"
		enumOperator,		///< "OPERATOR"
		enumGroundTruth,	///< "GROUND TRUTH"
		enumAggregate,		///< "AGGREGATE"
		enumModAggregate,	///< "MOD_AGGREGATE"
		enumUndefined		///< "UNDEFINED"

	}TDR_TYPE;

	/// Enumeration for Alarm Decision
	typedef enum
	{
		enumUnknownAlarmDecision = 0,	///< "UNKNOWN" and all other values

		enumAlarm,					///< "ALARM"
		enumClear					///< "CLEAR"

	}ALARM_DECISION;

	/// Enumeration for Abort decision
	typedef enum
	{
		enumUnknownAbortFlag = 0,	///< Does not match defined terms

		enumAbort,		//"ABORT"
		enumSuccess		//"SUCCESS"

	}ABORT_FLAG;

	/// Enumeration for abort reason
	typedef enum
	{
		enumUnknownAbortReason = 0,	///< Does not match defined terms

		enumOversizeBag,		///< "OVERSIZE_BAG"
		enumClippedBag,			///< "CLIPPED_BAG"
		enumIncompleteScan,		///< "INCOMPLETE_SCAN"
		enumFailedRecon,		///< "FAILED_RECON"
		enumTimeout,			///< "TIMEOUT"
		enumNotReviewed,		///< "NOT_REVIEWED"
		enumUnknownDataType,	///< "UNKNOWN_DATATYPE"
		enumUserInterrupt,		///< "USER_INTERRUPT"
		enumOutOfBounds			///< "OUT_OF_BOUNDS"

	}ABORT_REASON;

	/// \class OperatorIdentification
	/// \brief Operator Identification Sequence, a conditionally required single item sequence (0008, 1072)
	/// SPECREF V03 Section 12.4
	/// The OperatorIdentification class represents the data for the
	/// "Operator Identification Sequence" attribute, Tag (0008,1072), of the Threat Detection Report Module.
	class OperatorIdentification : public PersonIdentificationMacro
	{
	public:
		/// Default Constructor
		OperatorIdentification();
		
		/// Copy Constructor
		OperatorIdentification(const OperatorIdentification &opid);
		
		/// Destructor
		~OperatorIdentification();

		/// Assignment operator
		OperatorIdentification& operator=(const OperatorIdentification &opid);
		
		/// Equality Comparison operator
		bool operator==(const OperatorIdentification &opid)const;
		
		/// Inequality comparison operator
		bool operator!=(const OperatorIdentification &opid)const;

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

		/// Reset to default values
		void FreeMemory();

		///
		/// Set Person Identification Sequence : Tag (0040, 1101), VR = SQ [required] \n
		///	Params 1-3 are placed into a CodeSequence as the first item in the
		/// 'Person Identification Code Sequence' 'nType' is placed in the second item in
		/// the sequence.
		///
		///	@param strOperatorPrimaryID Operator Primary ID : Code Value
		///	@param strIdIssuingOrganization ID Issuing Organization : Scheme Designator
		///	@param strOperatorName Operator's Name : Code Meaning
		///	@param nType Coded Operator ID Type \n
		///		i) Identification Encoding Type is the Second item in sequence
		/// @return true/false false if data could not be set
		bool SetOperatorInformation(const DcsShortString &strOperatorPrimaryID, 
									const DcsShortString &strIdIssuingOrganization, 
									const DcsPersonName &strOperatorName,
									const IdentificationEncodingType::IDENTIFICATION_ENCODING_TYPE nType);

		/// @see SetOperatorInformation
		bool GetOperatorInformation(DcsString &strOperatorPrimaryID, 
									DcsString &strIdIssuingOrganization, 
									DcsString &strOperatorName,
									IdentificationEncodingType::IDENTIFICATION_ENCODING_TYPE &nType)const;

		/// @see SetOperatorInformation
		bool GetOperatorInformation(CodeSequence &csOperatorPrimaryID,
									CodeSequence &csEncodingType)const;

	protected:
		class ImplOperatorIdentification;
		ImplOperatorIdentification	*m_pImplOperatorIdentification; ///< Internal implementation
		
		ImplOperatorIdentification* GetImpl();
		const ImplOperatorIdentification* GetImpl() const;

		/// Operator information should only be set through the public interface methods
		/// @return false
		bool SetIdentificationCodeSequence(const Array1D<CodeSequence> &);
		
		bool FetchAttributes(const AttributeManager& attribManager, ErrorLog& el, const bool required);
	};

	/// Set TDR Type : Tag (4010, 1027)
	/// @param nType TDR_TYPE : Tag (4010, 1027), VR = CS [required] \n
	///			i) Values: "MACHINE", "OPERATOR", "GROUND TRUTH", "AGGREGATE", "MOD_AGGREGATE", "UNDEFINED"
	/// @return true/false
	bool SetTdrType(const TDR_TYPE nType);

	TDR_TYPE GetTdrType()const; ///< @see SetTdrType
	DcsString GetTdrTypeAsString()const; ///< @see SetTdrType

	/// Operator Identification Sequence (Single Item Sequence) : Tag (0008, 1072), VR = SQ [required if "TDR Type", tag (4010, 1027), is "OPERATOR"]
	/// @param opid OperatorIdentification object
	bool SetOperatorInformation(const OperatorIdentification &opid);

	/// @see OperatorIdentification.SetOperatorInformation
	bool SetOperatorInformation(const DcsShortString &strOperatorPrimaryID, 
									const DcsShortString &strIdIssuingOrganization, 
									const DcsPersonName &strOperatorName,
									const IdentificationEncodingType::IDENTIFICATION_ENCODING_TYPE nType);

	/// @see SetOperatorInformation
	bool GetOperatorInformation(OperatorIdentification &opid)const; 

	/// @see SetOperatorInformation
	const OperatorIdentification* GetOperatorIdentification() const;
	
	/// @see SetOperatorInformation
	OperatorIdentification* GetOperatorIdentification();
		
	/// SetImage Scale Representation : Tag (4010, 1075)
	/// Ratio of image data units to real world units (Ex. 1 unit in the image data represents 5 units in real world units)
	/// The default value is 0.0f and indicates that no valid value has been set and that the 
	/// scale representation attribute is not needed.
	///
	/// @param fScaleRepresentation Image Scale Representation : Tag (4010, 1075), 
	///		VR = FD [required if "OOI Type", tag (4010, 1042) is "PERSON" and "TDR Type", 
	///		tag (4010, 1027), is "MACHINE" or "GROUND TRUTH"]
	/// @return true/false
	bool SetImageScaleRepresentation(const double fScaleRepresentation);
	
	/// @see SetImageScaleRepresentation
	/// @return Image Scale Representation value or 0.0f is none is set.
	double GetImageScaleRepresentation()const;
	
	/// Set Alarm Decision Date and Time : Tag (4010, 102B)
	/// @param strDateTime Acquisition Date and Time : Tag (4010, 102B), VR = DT [required]
	/// @return true/false
	bool SetAlarmDecisionDateAndTime(const DcsDateTime &strDateTime);

	/// @see SetAlarmDecisionDateAndTime
	bool SetAlarmDecisionDateAndTime(const DcsDate &strDate, const DcsTime &strTime, const S_INT16 nOffsetFromUTC = 0);
	
	/// @see SetAlarmDecisionDateAndTime
	DcsDateTime GetAlarmDecisionDateAndTime()const;

	/// @see SetAlarmDecisionDateAndTime
	bool GetAlarmDecisionDateAndTime(DcsDateTime &strDateTime) const;
	
	/// @see SetAlarmDecisionDateAndTime
	bool GetAlarmDecisionDateAndTime(DcsDate &strDate, DcsTime &strTime, S_INT16 &offsetFromUTC)const;

	/// Set Alarm Decision : Tag (4010, 1031)
	///	@param nAlarmDecision Alarm Decision : Tag (4010, 1031), VR = CS [required]
	///			i) Values: "ALARM", "CLEAR", "UNKNOWN"
	///			ii) Attribute note states some alternatively used enumerations, but since they are not included within the defined enumeration list, they will not be supported (i.e. will be set to "UNKNOWN")
	/// @return true/false
	bool SetAlarmDecision(const ALARM_DECISION nAlarmDecision);
	
	/// @see SetAlarmDecision
	ALARM_DECISION GetAlarmDecision()const;
	
	/// @see SetAlarmDecision
	DcsString GetAlarmDecisionAsString()const;
	
	/// Set Abort Flag : Tag (4010, 1024)
	///	@param nFlag Abort Flag : Tag (4010, 1024), VR = CS [required]
	///			i) Values: "ABORT", "SUCCESS"
	/// @return true/false
	bool SetAbortFlag(const ABORT_FLAG nFlag);

	/// @see SetAbortFlag
	/// @return return enumUnknownAbortFlag if no flag has been set
	ABORT_FLAG GetAbortFlag() const;

	/// Set Abort Reason : Tag (4010, 1021)
	/// @param nAbortReason Abort Reason : Tag (4010, 1021), VR = CS [required IF "Abort Flag" is "ABORT"]
	///			i) Values: "OVERSIZE_BAG", "CLIPPED_BAG", "INCOMPLETE_SCAN", "FAILED_RECON", "TIMEOUT", "NOT_REVIEWED", "UNKNOWN_DATATYPE", "USER_INTERRUPT", "OUT_OF_BOUNDS"
	/// @return true/false
	bool SetAbortReason(const ABORT_REASON nAbortReason);
	
	/// @see SetAbortReason
	/// @return return enumUnknownAbortReason if flag has not been set
	ABORT_REASON GetAbortReason()const;
	
	/// @see SetAbortReason
	/// @return return "" if abort reason has not been set
	DcsString GetAbortReasonAsString()const;
	
	/// Set Threat Detection Algorithm and Version : Tag (4010, 1029)
	///		a) Tag (4010, 1029), VR = LO [required if "TDR Type", tag (4010, 1027), is "MACHINE"]
	///		b) Values stored in single tag "Manufacturer\VersionNumber\ControlParameters[0]\...\ControlParameters[n]"
	///	@param strManufacturer Manufacturer
	///	@param strVersionNumber Version Number
	///	@param arrayControlParameters Control Parameters
	/// @return true/false
	bool SetThreatDetectionAlgorithmAndVersion(	const DcsLongString &strManufacturer, 
												const DcsLongString &strVersionNumber, 
												const Array1D<DcsLongString>& arrayControlParameters);
	
	/// @see SetThreatDetectionAlgorithmAndVersion
	bool GetThreatDetectionAlgorithmAndVersion(	DcsString &strManufacturer, 
												DcsString &strVersionNumber, 
												Array1D<DcsString> &arrayControlParameters)const;

	void DeleteThreatDetectionAlgorithmAndVersion();
	
	/// Set Number of Total Objects : Tag (4010, 1033)
	/// @param nNumTotal Number of Total Objects : Tag (4010, 1033), VR = US [required]
	bool SetNumberOfTotalObjects(const S_UINT16 nNumTotal);

	S_UINT16 GetNumberOfTotalObjects()const; ///< @see SetNumberOfTotalObjects

	/// Set Number of Alarm Objects : Tag (4010, 1034), 
	/// VR = US [required if "Alarm Decision", tag (4010, 1031), is "ALARM"]
	/// @param nNumAlarm Number of alarm objects
	/// @return true/false
	bool SetNumberOfAlarmObjects(const S_UINT16 nNumAlarm);

	/// @see SetNumberOfAlarmObjects
	S_UINT16 GetNumberOfAlarmObjects()const;

	/// Set Total Processing Time : Tag (4010, 1069), VR = FL [required]
	/// @param fProcessingTime Total processing time must be > 0.0f
	bool SetTotalProcessingTime(const float fProcessingTime);

	/// @see SetTotalProcessingTime
	float GetTotalProcessingTime()const;

	/// @see SetTotalProcessingTime
	void DeleteTotalProcessingTime();

protected:
	class ImplThreatDetectionReport;
	ImplThreatDetectionReport	*m_pImplThreatDetectionReport; ///< Internal implementation
	
	ImplThreatDetectionReport* GetImpl();
	const ImplThreatDetectionReport* GetImpl() const;
};

}//namespace TDRTypes
}//namespace SDICOS

#endif
