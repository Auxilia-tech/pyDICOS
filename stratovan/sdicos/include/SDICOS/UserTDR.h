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
	/// @return Returns number of clients that successfully sent DICOS data
#ifndef _STRATOVAN_DICOS_SDCS_TEMPLATE_TDR_H_
#define	_STRATOVAN_DICOS_SDCS_TEMPLATE_TDR_H_

#include "SDICOS/DicosFile.h"
#include "SDICOS/SopClassUID.h"
#include "SDICOS/TemplateBase.h"
#include "SDICOS/ModuleTDR.h"
#include "SDICOS/FrameOfReferenceUser.h"

namespace SDICOS 
{

///
/// \class TDR
/// \brief TDR represents a Thread Detection Report (TDR) for an Object of Inspection (OOI)
/// 
/// The TDR class is not thread safe.
///
/// This class abstracts away the hierarchy of the DICOS specification 
/// and provides an API that contains methods for setting the attributes needed for a DICOS TDR object.
/// The TDR contains information for one or more Potential Threat Objects (PTOs).
///
/// Valid default values are provided for many attributes required by the DICOS specification.
/// If no PTOs are added to the TDR, make sure to add referenced scans using SDICOS::IODCommon::AddReferencedSopInstance().
/// Default values for attributes that can be set through the TDR API are as follows:
///
///		- Frame Of Reference UID:	Randomized DcsUniqueIdentifier UID string
///		- Instance Number:		0 
///		- Content Date:			result of DcsDate::Today() when object is created
///		- Content Time:			result of DcsTime::Now() when object is created
///		- TDR Type:				SDICOS::TDRTypes::ThreatDetectionReport::enumUnknownTDRType
///		- ATR Manufacturer:		Defaults to 'UNKNOWN'. Must be set by user if TDR Type is ATR.
///		- ATR Version:			Defaults to 'UNKNOWN'
///		- ATR Params:				Defaults to an empty set.
///		- Image Scale Rep:		No default value is set. Must be set by user if requirement conditions are met.
///		- Alarm Decision Time:	Result of DcsDate:Today() and DcsTime::Now() when object is created
///		- Alarm Decision:			No default value is set. Must be set by user.
///		- Abort Flag:				Set to SUCCESS. Abort reason is not set.
///		- Number of PTOs:				Defaults to 0.
///		- Number of Alarm objects:	Defaults to 0.
///		- Additional Screening Performed:		Defaults to 'NO'.
///
///		- PTO Assessment Information:
///			- Assessment Flag : Defaults to UNKNOWN
///			- Threat Category : Defaults to Anomaly
///			- Assessment Ability : Defaults to No Interference
///			- Threat Category Description : Optional attribute. Defaults to empty string.
///			- Assessment Probability : Optional attribute. Defaults to -1.0f indicating no value is written to the file.
///		- PTO Mass and Density:	Defaults to 0 if required and not specified.
///
///		- Threat Bounding Polygon: Optional attribute not used by default.
///		- Region of Interest Information:
///			- PTO Base : Required, no default value.
///			- PTO Extents : Required, no default value.
///			- PTO Bitmap: Not required.
///		- Referenced Instances: Required value must be set by user.
///			- If no instance is available, a user message is written to the ErrorLog and writing will fail.
///		- Baggage Specific Details:
///			- Mass : Defaults to 0. 
///			- Density : Defaults to 0.
///			- Location Description : Defaults to empty string
///		- Person Specific Details:
///			- Location Description : Defaults to empty string
///			- PTO Center : Not used by default.
class TDR : public IODCommon,
			public FrameOfReferenceUser // See FrameOfReferenceUser.h Adds FrameOfReference Module Attributes to the SDICOS::TDR User Level API.
{
public:
	/// Default constructor
	TDR();
	
	/// Construct with Object of Inspection Type, TDR Type and Identifying Instance Number
	TDR(
		const SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE OOIType,
		const TDRTypes::ThreatDetectionReport::TDR_TYPE tdrType,
		const S_INT32 instanceNumber
	);
	
	/// Construct a TDR with Object of Inspection (OOI) Type, TDR Type and creation information.
	/// @param OOIType Object Of Inspection Type (Bio, Cargo, Animal, Person, Baggage etc)
	/// @param tdrType Indicates how the TDR was produced.
	/// @param instanceNumber Numeric identifier for the PTO
	/// @param contentCreationDate Date that the TDR data or the activity resulting in the TDR creation was started.
	/// @param contentCreationTime Time that the TDR data of the activity resulting in the TDR creation was started.
	TDR(
		const SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE OOIType,
		const TDRTypes::ThreatDetectionReport::TDR_TYPE tdrType,
		const S_INT32 instanceNumber,
		const DcsDate& contentCreationDate,
		const DcsTime& contentCreationTime
	);
	
	/// Construct a TDR with person gender, TDR Type and creation information.
	/// OOI type is automatically set to Person.
	/// Image Scale Representation is set to 1.0. Call SetImageScaleRepresentation() to override.
	/// Call SetPersonPTODetails() and AddAnomalyIndicator() as needed to set person-specific attributes.
	/// @param gender The OOI's gender
	/// @param tdrType Indicates how the TDR was produced.
	/// @param instanceNumber Numeric identifier for the PTO
	/// @param contentCreationDate Date that the TDR data or the activity resulting in the TDR creation was started.
	/// @param contentCreationTime Time that the TDR data of the activity resulting in the TDR creation was started.
	TDR(
		const SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER gender,
		const TDRTypes::ThreatDetectionReport::TDR_TYPE tdrType,
		const S_INT32 instanceNumber,
		const DcsDate& contentCreationDate,
		const DcsTime& contentCreationTime
	);
	
	/// Construct a TDR with Object of Inspection (OOI) parameters.
	/// @param OOIIdentifier Primary airport identification number or code for the OOI
	/// @param IdType The type of OOIIdentifier (enumText, enumRFID, enumBarcode, enumMRP)
	/// @param OOIIdentifierIssuer Authority that assigned the Id the OOI.
	/// @param OOIType Object of Inspection Type assigned by scanning device or another source
	///			(enumBioSample, enumCargo, enumBaggage, enumAnimal, enumOther, enumPerson)
	/// @param tdrType Indicates how the TDR was produced.
	/// @param instanceNumber Numeric identifier for the PTO.
	TDR(
		const DcsLongString& OOIIdentifier,
		const SDICOS::ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE& IdType,
		const DcsLongString& OOIIdentifierIssuer,
		const SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE OOIType,
		const TDRTypes::ThreatDetectionReport::TDR_TYPE tdrType,
		const S_INT32 instanceNumber
	);

	/// Copy Constructor
	TDR(const TDR &tdr);

	~TDR();

	/// Copy Operator
	TDR& operator=(const TDR &tdr);

	/// Comparison operator
	bool operator==(const TDR&) const;
	
	/// Comparison operator
	bool operator!=(const TDR&) const;
	
	/// \enum ThreatType
	/// Threats represented by TDRs must be classified as either person or baggage (non-person).
	enum ThreatType 
	{
		enumThreatTypeUnknown,	///< Threat type is unknown
		enumThreatTypePerson,	///< Threat type is a person
		enumThreatTypeBaggage,	///< Threat type is baggage
	};

	/// Initialize with a TDR object
	/// @param tdr		  TDR to initialize from
	/// @param errorlog	  Error Log
	/// @param bMoveData  true = Move data (such as pixel data), instead of copying, from vSeries
	bool Initialize(const TDRModule &tdr, ErrorLog &errorlog, const bool bMoveData = false);
	
	/// Initialize with a set of required values
	bool Initialize(
		const DcsLongString& OOIIdentifier,
		const SDICOS::ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE& IdType,
		const DcsLongString& OOIIdentifierIssuer,
		const SDICOS::ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE OOIType,
		const TDRTypes::ThreatDetectionReport::TDR_TYPE tdrType,
		const S_INT32 instanceNumber
		);

	/// Free allocated resources
	virtual void FreeMemory();

	/// Write to file
	virtual bool Write(const Filename &filename, ErrorLog &errorlog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG)const;

	/// Write to a contiguous memory buffer
	/// @param memorybuffer MemoryBuffer object to store the DICOS data.
	/// @param errorlog Error encountered during DICOS conversion or writing to the memory buffer.
	/// @param nTransferSyntax DICOS Transfer syntax
	/// @return true/false If false, check error log.
	virtual bool Write(MemoryBuffer &memorybuffer, ErrorLog &errorlog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG) const;

	/// Write to a contiguous memory buffer
	/// @param memfile MemoryFile object to store the DICOS data.
	/// @param errorlog Error encountered during DICOS conversion or writing to the memory buffer.
	/// @param nTransferSyntax DICOS Transfer syntax
	/// @return true/false If false, check error log.
	virtual bool Write(MemoryFile &memfile, ErrorLog &errorlog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG) const;

	/// Convenience method to read a series that contains a single file
	/// @param filename Filename for the file to be read
	/// @param errorLog Errorlog to store read errors
	/// @param pMemMgr Currently not used in TDR
	virtual bool Read(const Filename &filename, ErrorLog& errorLog, IMemoryManager *pMemMgr = S_NULL);
	/// Read from a contiguous memory buffer
	/// @param memfile MemoryFile object to read the DICOS data.
	/// @param errorLog Errors encountered while reading the DICOS data.
	/// @param pMemMgr Currently not used in TDR
	virtual bool Read(MemoryFile &memfile, ErrorLog& errorLog, IMemoryManager *pMemMgr = S_NULL);

	/// Send data over TCP/IP connection. Handles opening and closing a socket connection and starting 
	/// and ending a DICOS session.
	/// @param nPort Host port
	/// @param dsIP Host IP address
	/// @param aeSrcAppName Name of source application (i.e. Name of application calling this function)
	/// @param aeDstAppName Name of destination application
	/// @param errorlog Error log
	/// @param dsUserID User ID. Leave empty if not used.
	/// @param dsPasscode Passcode. If used, user ID must be set.
	virtual bool SendOverNetwork(const S_INT32 nPort, const DcsString &dsIP, const DcsApplicationEntity &aeSrcAppName, 
							const DcsApplicationEntity &aeDstAppName, ErrorLog &errorlog, 
							const DcsString &dsUserID = "", const DcsString dsPasscode = "");

	/// Send data over TCP/IP connection. The passed in client must already be connected to a host.
	/// Handles Starting and ending a DICOS session if a session is not already in progress.
	/// @param dclient Client already connected to host.
	/// @param errorlog Error log
	virtual bool SendOverNetwork(SDICOS::Network::DcsClient &dclient, ErrorLog &errorlog);
	/// Send data over TCP/IP connection to multiple clients.
	/// Handles Starting and ending a DICOS sessions if not already in progress.
	/// @param clientManager Clients already connected to host.
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Returns number of clients that successfully sent DICOS data
	virtual S_UINT32 SendOverNetwork(SDICOS::Network::DcsClientManager &clientManager, ErrorLog &errorlog, std::vector< Network::DcsClientManager::ClientMetrics > &vSendTimes);
	
	/// Check the attributes in the TDR object against the DICOS specification
	virtual bool Validate(ErrorLog& errorlog) const;

	/// Returns enumTDR
	virtual MODALITY GetModality()const;
	
	// General Report
	
	/// Set the Instance Number that identifies this TDR
	/// @param nInstanceNumber Instance number that uniquely identifies the TDR. Must be >= 0
	/// @return true/false false if instance number is invalid
	bool SetInstanceNumber(const S_INT32 nInstanceNumber);

	/// @see SetInstanceNumber
	/// @return the instance number or TDR::INVALID_INSTANCE_NUMBER
	S_INT32 GetInstanceNumber()const;

	///
	/// Set Content Date and Time
	/// @param contentCreationDate Date that the TDR data or the activity resulting in the TDR creation was started.
	/// @param contentCreationTime Time that the TDR data of the activity resulting in the TDR creation was started.
	/// @return true/false false if creation date or time are not valid DcsDate or DcsTime objects.
	///
	bool SetContentDateAndTime(const DcsDate &contentCreationDate, const DcsTime &contentCreationTime);

	/// @see SetContentDateAndTime
	/// @return Empty DcsDate object if no date was set
	DcsDate GetContentDate()const;

	/// @see SetContentDateAndTime
	/// @return Empty DcsTime object if no time was set
	DcsTime GetContentTime()const;
	
	// Threat Detection Report
	
	/// Set the Threat Detection Report(TDR) Type
	/// @param tdrType Threat Detection Report Type
	///			Options: enumMachine:	TDR from ATR Machine
	///					 enumOperator:	TDR from Device of viewing station operator
	///					 enumGroundTruth:	Provide by person with domain specific knowledge
	///					 enumAggregate: TDR aggregated from multiple TDRs with the same modality
	///					 enumModAggregate: TDR aggregated from multiple TDRs with different modalities				
	///					 enumUndefined:	Threat type is undefined
	/// @return true/false
	bool SetTDRType(const SDICOS::TDRTypes::ThreatDetectionReport::TDR_TYPE tdrType);

	/// @see SetTDRType
	/// @return enumUnknownTDRType if no TDR Type was set
	TDRTypes::ThreatDetectionReport::TDR_TYPE GetTDRType() const;

	/// Set the ATR algorithm used.
	/// Required only is TDR Type is set to enumMachine. Optional otherwise.
	///
	/// @param atrManufacturer	Manufacturer of ATR Algorithm
	/// @param atrVersion		Version of ATR Algorithm. Uniquely identifies algorithm used for this TDR.
	/// @param atrParameters	Any additional 
	/// @return true/false		false if atrManufacturer, atrAlgorithm or atrVersion are not valid DcsLongString objects
	bool SetTDRTypeATR(
		const DcsLongString& atrManufacturer,
		const DcsLongString& atrVersion,
		const Array1D<DcsLongString>& atrParameters = Array1D<DcsLongString>()
	);
	
	/// @see SetTDRTypeATR
	bool GetATRInfo(DcsLongString& atrManufacturer, DcsLongString& atrVersion, Array1D<DcsLongString>& atrParameters) const;
	
	/// Set the Identification of the Operator
	/// Required only if TDR Type has been set to enumOperator. Optional otherwise.
	///
	/// @param operatorId Identification string for the operator
	/// @param IdIssuer Organization that issued the Id
	/// @param operatorFullName Full legal name of the operator
	/// @param IdType Type of Identification string. 
	///					enumTextEncoding	Text Encoding
	///					enumRFID			RFID
	///					enumBarcode			Barcode
	///					enumMRP				Machine Readable Passport
	///					enumPIV				Personal Identity Verification
	/// @return true/false false if given values are not valid
	bool SetOperatorTDR(
		const DcsLongString& operatorId,
		const DcsLongString& IdIssuer,
		const DcsPersonName& operatorFullName,
		const IdentificationEncodingType::IDENTIFICATION_ENCODING_TYPE IdType
	);
	
	/// @see SetOperatorTDR
	bool GetOperatorTDR(
		DcsLongString& operatorId,
		DcsLongString& IdIssuer,
		DcsPersonName& operatorFullName,
		IdentificationEncodingType::IDENTIFICATION_ENCODING_TYPE& IdType
	) const;
	
	/// Set the relative scaling factor between the representative human figure
	/// and the image and related Potential Threat Objects (PTOs)
	/// Required if Object of Inspection (OOI) Type is a person
	/// Required if TDR Type is MACHINE or GROUND TRUTH.
	/// Optional otherwise.
	///
	/// @param imageScale	Scaling factor between person and image.
	/// @return true/false	false if imageScale < 0.0
	bool SetImageScaleRepresentation(const double imageScale);
	
	/// @see SetImageScaleRepresentation
	double GetImageScaleRepresentation() const;
	
		/// Set the alarm decision for the Object of Inspection (OOI)
	/// @param alarmDecision Type of alarm decision
	///							enumAlarm		Threat or suspect detected
	///							enumClear		No threat detected
	///							enumUnknown		Unable to make a decision.
	/// @return true/false
	bool SetAlarmDecision(const TDRTypes::ThreatDetectionReport::ALARM_DECISION alarmDecision);
	
	/// @see SetAlarmDecision
	TDRTypes::ThreatDetectionReport::ALARM_DECISION GetAlarmDecision() const;
	
	/// Date and timestamp at which the Machine or Operator rendered the alarm decision
	/// @param alarmDecisionDate Data alarm decision was made. Defaults to result of DcsDate::Today()
	/// @param alarmDecisionTime Time alarm decision was made. Defaults to result of DcsTime::Now()
	/// @return true/false false if alarmDecisonDate or alarmDecisionTime are not valid DcsDate and DcsTime objects
	bool SetAlarmDecisionDateTime(const DcsDate& alarmDecisionDate, const DcsTime& alarmDecisionTime);
	
	/// @see SetAlarmDecisionDateTime
	bool GetAlarmDecisionDateTime(DcsDate& alarmDecisionDate, DcsTime& alarmDecisionTime) const;
	
	/// Indicate whether the alarm decision process was successful or aborted.
	/// @param abortFlag Abort flag value
	///						enumAbort	Alarm decision process was aborted.
	///						enumSuccess	Alarm decision process succeeded.
	/// @param abortReason	Required if abortFlag is set to enumAbort
	/// @return true/false false if alarm decision is abort and a valid reason is not given.
	bool SetAbortFlag(const TDRTypes::ThreatDetectionReport::ABORT_FLAG abortFlag, const TDRTypes::ThreatDetectionReport::ABORT_REASON abortReason = TDRTypes::ThreatDetectionReport::enumUnknownAbortReason);
	
	/// @see SetAbortFlag
	bool GetAbortFlag(TDRTypes::ThreatDetectionReport::ABORT_FLAG& abortFlag, TDRTypes::ThreatDetectionReport::ABORT_REASON& abortReason) const;
	
	/// @see GetAbortFlag
	TDRTypes::ThreatDetectionReport::ABORT_FLAG GetAbortFlag() const;
	
	/// @see GetAbortFlag
	TDRTypes::ThreatDetectionReport::ABORT_REASON GetAbortReason() const;
	
	/// Get the number of Potential Threat Objects (PTOs) and the number of Alarm Objects
	/// @param numPotentialThreatObjects	Number of OOIs evaluated and reported as PTOs
	/// @param numAlarmObjects				Number of PTOs that actually alarmed.
	/// @return true/false
	bool GetNumberOfObjects(S_UINT16& numPotentialThreatObjects, S_UINT16& numAlarmObjects) const;
	
	/// @see SetNumberOfObjects
	S_UINT16 GetNumPTOs() const;
	
	/// @see SetNumberOfObjects
	S_UINT16 GetNumAlarmObjects() const;
	
	/// Set the total processing time in milliseconds.
	/// This parameter is not required but is included for tracking purposes
	/// @param processingTime	Processing time in milliseconds. A value <= 0 is not written to the DICOS file.
	/// @return true/false
	bool SetTotalProcessingTimeInMS(const float processingTime);
	
	/// @see SetTotalProcessingTimeInMS
	float GetTotalProcessingTimeInMS() const;

	/////////////////////////////////////////
	// Additional Inspection Criteria

	/// \class AdditionalInspectionData
	/// Stores Method and Method Description for the Additional Inspection
	class AdditionalInspectionData
	{
	public:
		/// Default constructor
		AdditionalInspectionData();
		/// Copy constructor
		///@param rhs Copy this object
		AdditionalInspectionData(const AdditionalInspectionData& rhs);

		/// Copy operator
		/// @param rhs Copy this object
		/// @return Reference to this object
		AdditionalInspectionData& operator=(const AdditionalInspectionData& rhs);
		/// Comparison operator
		/// @param rhs Compare to this object
		/// @return true/false
		bool operator==(const AdditionalInspectionData& rhs)const;
		/// Comparison operator
		/// @param rhs Compare to this object
		/// @return true/false
		bool operator!=(const AdditionalInspectionData& rhs)const;

		DcsShortString	m_strMethod; ///< Additional Inspection Method
		DcsLongString	m_strMethodDescription; ///< Additional Inspection Method Description
	};
	
	/// Indicate if additional screening was performed and what kind of inspection it was.
	/// This attributes defaults to 'NO'. It's primary use is intended for follow on
	/// systems, ATR or other, that determine if extra screening is needed.
	///
	/// @param additionalInspectionPerformed true/false
	/// @param selectionCriteria Defines the criteria used to select the Object of Inspection (OOI) for secondary inspection.
	///								Values are enumRandom, enumBehavioral, and enumAll.
	/// @param additionalInspectionMethod	TSA defined code for inspection selection criteria
	/// @param inspectionMethodDescription	Longer form description of inspection selection criteria
	/// @return true/false false if any parameters are in valid.
	bool SetAdditionalInspectionCriteria(
		const bool additionalInspectionPerformed = false,
		const TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA selectionCriteria = TDRTypes::AdditionalInspectionSelectionCriteria::enumUnknownAdditionalInspectionSelectionCriteria,
		const DcsShortString& additionalInspectionMethod = "",
		const DcsLongString& inspectionMethodDescription = ""
	);

	/// Indicate if additional screening was performed and what kind of inspection it was.
	/// This attributes defaults to 'NO'. It's primary use is intended for follow on
	/// systems, ATR or other, that determine if extra screening is needed.
	///
	/// @param additionalInspectionPerformed true/false
	/// @param selectionCriteria Defines the criteria used to select the Object of Inspection (OOI) for secondary inspection.
	///								Values are enumRandom, enumBehavioral, and enumAll.
	/// @param vAdditionalInspectionMethods Array of TSA defined code for inspection selection criteria with description
	/// @return true/false false if any parameters are in valid.
	bool SetAdditionalInspectionCriteria(
		const bool additionalInspectionPerformed,
		const TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA selectionCriteria,
		const Array1D<AdditionalInspectionData> &vAdditionalInspectionMethods
	);
	
	/// Get Additional Inspection information. If multiple methods and descriptions are present, returns the first method and description.
	/// @return true/false true if additional inspection was performed. false otherwise.
	bool GetAdditionalInspectionCriteria(
		TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA& selectionCriteria,
		DcsShortString& additionalInspectionMethod,
		DcsLongString& inspectionMethodDescription
	) const;
	
	/// Get Additional Inspection information
	/// @return true/false true if additional inspection was performed. false otherwise.
	bool GetAdditionalInspectionCriteria(
		TDRTypes::AdditionalInspectionSelectionCriteria::ADDITIONAL_INSPECTION_SELECTION_CRITERIA& selectionCriteria,
		Array1D<AdditionalInspectionData>& vAdditionalInspectionMethods
	) const;
	
	// Threat Sequence
	
	/// Add a PTO with the indicated identifier.
	/// Required only if the Alarm Decision is set to enumAlarm
	/// The PTO identifier is used to indicate the PTO when setting other attributes.
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param threatType The threat can be Person or Baggage (non-person) see TDR::ThreatType.
	///			If the Object of Inspection Type (OOI Type) is PERSON, at least one PTO of type enumPerson must be added.
	///			If the OOI Type is BAGGAGE, at least one PTO of type enumBaggage must be added.
	///			For all other OOI Types uses Baggage as the threat type.
	/// @param nNumPTORepresentations Number of representations for the given PTO. For example, a dual view system has 2 representations and a dual view dual energy system has 4 representations
	/// @return true/false	false if PTO could not be created with the indicated identifier
	bool AddPotentialThreatObject(const S_UINT16 PTOIdentifier, const ThreatType threatType, const S_UINT16 nNumPTORepresentations = 1);

	/// Returns the threat type of the indicated PTO
	/// @param PTOIdentifier Numeric identifier for the PTO
	ThreatType GetThreatType(const S_UINT16 PTOIdentifier)const;
	
	/// Delete a PTO with the indicated identifier
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @return true/false false if a PTO with the indicated identifier did not exist.
	bool DeletePotentialThreatObject(const S_UINT16 PTOIdentifier);

	/// Deletes all potential threat objects
	void DeleteAllPotentialThreatObjects();

	/// Check if a PTO with the indicated identifier exists.
	bool HasPotentialThreatObject(const S_UINT16 PTOIdentifier) const;

	/// Returns the numbrer of PTO Representations
	/// @see AddPotentialThreatObject
	S_UINT16 GetNumberOfPTORepresentations(const S_UINT16 PTOIdentifier)const;
	
	/// Get an array of PTO identifiers
	bool GetPTOIds(Array1D<S_UINT16>& ids) const;

	/// Set Originating TDR Type. The TDR Type from which the PTO originated.
	/// Required if TDR Type is MOD_AGGREGATE. Must not present otherwise.
	/// @param PTOIdentifier PTO in this TDR
	/// @param nTDRType ORIGINATING_TDR_TYPE
	/// @return true/false false if enum value is not valid
	bool SetOriginatingTDRType(const S_UINT16 PTOIdentifier, const TDRTypes::ThreatSequence::ThreatItem::ORIGINATING_TDR_TYPE nTDRType);
	/// Check if Originating TDR Type is present
	/// @param PTOIdentifier PTO in this TDR
	/// @return true/false false if PTO is not found or value is not present
	bool HasOriginatingTDRType(const S_UINT16 PTOIdentifier) const;
	/// @see SetOriginatingTDRType
	/// @param PTOIdentifier PTO in this TDR
	/// @return enumOriginatingTDRUnknown if not is set or PTO is not found
	TDRTypes::ThreatSequence::ThreatItem::ORIGINATING_TDR_TYPE GetOriginatingTDRType(const S_UINT16 PTOIdentifier) const;
	/// Clear originating TDR Type string
	/// @param PTOIdentifier PTO in this TDR to add the processing time metrics to
	bool DeleteOriginatingTDRType(const S_UINT16 PTOIdentifier);

	/// \class ReferencedPTO
	/// Stores references to a PTO in another TDR
	class ReferencedPTO
	{
	public:
		/// Default constructor
		ReferencedPTO();
		/// Copy constructor
		/// @param rhs Object to copy
		ReferencedPTO(const ReferencedPTO &rhs);

		/// Copy operator
		/// @param rhs Object to copy
		/// @return Reference to this object
		ReferencedPTO& operator=(const ReferencedPTO& rhs);
		/// Comparison operator
		/// @param rhs Object to compare
		/// @return true/false
		bool operator==(const ReferencedPTO& rhs)const;
		/// Comparison operator
		/// @param rhs Object to compare
		/// @return true/false
		bool operator!=(const ReferencedPTO& rhs)const;

		S_UINT16	m_nPTOID; ///< PTO ID of referenced PTO in referenced TDR
		DcsUniqueIdentifier	m_strSopInstanceUID; ///< SOP Instance UID of the referenced TDR with the referenced PTO
	};

	/// Set referenced PTOs in other TDRs
	/// @param PTOIdentifier PTO in this TDR
	/// @param vRefs Referenced PTOs
	/// @return true/false if PTO is found for the given PTOIdentifier
	bool SetReferencedPotentialThreatObject(const S_UINT16 PTOIdentifier, const Array1D<ReferencedPTO> &vRefs);
	/// Get referenced PTOs in other TDRs
	/// @param PTOIdentifier PTO in this TDR
	/// @param vRefs Referenced PTOs
	/// @return true/false if PTO is found for the given PTOIdentifier
	bool GetReferencedPotentialThreatObject(const S_UINT16 PTOIdentifier, Array1D<ReferencedPTO>& vRefs) const;
	/// Check if referenced PTOs are present
	/// @param PTOIdentifier PTO in this TDR
	/// @return true/false reference is present or false if PTO is not found for the given PTOIdentifier
	bool HasReferencedPotentialThreatObject(const S_UINT16 PTOIdentifier)const;
	/// Delete referenced PTOs
	/// @param PTOIdentifier PTO in this TDR
	/// @return true/false if PTO is found for the given PTOIdentifier
	bool DeleteReferencedPotentialThreatObject(const S_UINT16 PTOIdentifier);

	/// Signal Generation Software Versions
	/// Defines version(s) of software that converts original sensor data and transforms data for presentation or analysis
	/// @param PTOIdentifier PTO in this TDR
	/// @param vVersions Signal Generation Software Versions
	/// @return true/false if PTO is found for the given PTOIdentifier
	bool SetSignalGenerationSoftwareVersion(const S_UINT16 PTOIdentifier, Array1D<DcsLongString>& vVersions);
	/// @param PTOIdentifier PTO in this TDR
	/// @param vVersions Signal Generation Software Versions
	/// @return true/false if PTO is found for the given PTOIdentifier
	bool GetSignalGenerationSoftwareVersion(const S_UINT16 PTOIdentifier, Array1D<DcsLongString>& vVersions)const;
	/// Check if Signal Generation Software Versions is present
	/// @return true/false if present or false if PTO is not found for the given PTOIdentifier
	bool HasSignalGenerationSoftwareVersion(const S_UINT16 PTOIdentifier)const;
	/// Delete Signal Generation Software Versions for a PTO
	/// @param PTOIdentifier PTO in this TDR
	/// @return true/false if PTO is found for the given PTOIdentifier
	bool DeleteSignalGenerationSoftwareVersion(const S_UINT16 PTOIdentifier);

	/// Set the Dynamic Screening Flag
	/// @param PTOIdentifier PTO in this TDR
	/// @param nFlag enum value to set the dynamic screening flag to, Unknown enumerations map to enumNone.
	/// @return true if the flag is successfully set, false otherwise
	bool SetDynamicScreeningFlag(const S_UINT16 PTOIdentifier, const TDRTypes::ThreatSequence::ThreatItem::DYNAMIC_SCREENING_FLAG nFlag);
	/// Get the Dynamic Screening Flag
	/// @param PTOIdentifier PTO in this TDR
	/// @see SetDynamicScreeningFlag
	/// @return Dynamic Screening Flag or enumUnknownDynamicScreeningFlag if PTO is not found
	TDRTypes::ThreatSequence::ThreatItem::DYNAMIC_SCREENING_FLAG GetDynamicScreeningFlagEnum(const S_UINT16 PTOIdentifier)const;
	/// Returns true if the data is set
	/// @param PTOIdentifier PTO in this TDR
	bool HasDynamicScreeningFlag(const S_UINT16 PTOIdentifier)const;
	/// Delete the data
	/// @param PTOIdentifier PTO in this TDR
	bool DeleteDynamicScreeningFlag(const S_UINT16 PTOIdentifier);

	/// Start date and time for analyzing PTO.
	/// @param PTOIdentifier PTO in this TDR
	/// @param startTime Processing start time
	/// @return true/false
	bool SetProcessingStartTime(const S_UINT16 PTOIdentifier, const DcsDateTime& startTime);

	/// @see SetProcessingStartTime
	/// @param PTOIdentifier PTO in this TDR
	/// @param startTime Store processing start time here
	/// @return true/false
	bool GetProcessingStartTime(const S_UINT16 PTOIdentifier, DcsDateTime& startTime) const;

	/// End date and time for analyzing PTO.
	/// @param PTOIdentifier PTO in this TDR
	/// @param endTime Processing start time
	/// @return true/false
	bool SetProcessingEndTime(const S_UINT16 PTOIdentifier, const DcsDateTime& endTime);

	/// etProcessingEndTime
	/// @param PTOIdentifier PTO in this TDR
	/// @param endTime Store processing end time here
	/// @return true/false
	bool GetProcessingEndTime(const S_UINT16 PTOIdentifier, DcsDateTime& endTime) const;

	/// Set the processing time metrics for a PTO that exists in a referenced TDR.
	/// @param PTOIdentifier PTO in this TDR to add the processing time metrics to
	/// @param dtStart Start Date and Time for the processing of the object
	/// @param dtEnd   End Date and Time for the processing of the object
	/// @param fTotalTimeMS Total processing time in milliseconds for the object
	/// @return true if each of the processing time parameters are successfully set, false otherwise
	bool SetPTOProcessingTime(
		const S_UINT16 PTOIdentifier,
		const SDICOS::DcsDateTime &dtStart,
		const SDICOS::DcsDateTime &dtEnd,
		const float fTotalTimeMS
	);

	/// Get the processing time metrics for a PTO that exists in a referenced TDR.
	/// @param PTOIdentifier PTO in this TDR to add the processing time metrics to
	/// @param dtStart Start Date and Time for the processing of the object
	/// @param dtEnd   End Date and Time for the processing of the object
	/// @param fTotalTimeMS Total processing time in milliseconds for the object
	/// @see SetPTOProcessingTime
	/// @return true if each of the processing time parameters are successfully retrieved, false otherwise
	bool GetPTOProcessingTime(
		const S_UINT16 PTOIdentifier,
		SDICOS::DcsDateTime &dtStart,
		SDICOS::DcsDateTime &dtEnd,
		float &fTotalTimeMS
	) const;
	
	/// Add Threat Assessment information for the indicate PTO.
	/// More than one Threat Assessment may be added for a PTO.
	/// Values for enumerated types are defined in the class SDICOS::TDRTypes::AssessmentSequence::AssessmentItem
	///
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param assessmentFlag Final assessment of the Potential Threat Object (PTO)
	///						  Values: enumHighThreat, enumThreat, enumNoThreat, enumUnknown
	/// @param threatCategory The type of threat reported by the Automatic Threat Recognition (ATR) system.
	///						  Values enumHME, enumPrecursor, enumProhibitedItem, enumContraband, enumAnomaly
	/// @param ability	Indicates if the Machine or Operator was able to assess the PTO without interference
	///					Values are enumNoInterference and enumShield.
	/// @param threatDescription Human readable description of the threat. An empty string will exclude the threat description from the PTO.
	/// @param assessmentProbability Operator or Machine defined probability of the threat assessment in percentage of certainty between 0.0 and 1.0.
	///								 Values less than 0.0 will exclude the assessment probability from the PTO.
	///								 Values greater than 1.0 will cause an error.
	/// @return true/false false indicates one or more supplied values are invalid.
	bool AddPTOAssessment(
		const S_UINT16 PTOIdentifier,
		const TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG assessmentFlag = TDRTypes::AssessmentSequence::AssessmentItem::enumUnknown,
		const TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY threatCategory = TDRTypes::AssessmentSequence::AssessmentItem::enumAnomaly,
		const TDRTypes::AssessmentSequence::AssessmentItem::ABILITY_ASSESSMENT ability = TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference,
		const DcsLongText& threatDescription = "",
		const float assessmentProbability = -1.0f 
	);
	
	/// Convenience type definition 
	typedef SDICOS::TDRTypes::AssessmentSequence::AssessmentItem AssessmentItem;
	typedef SDICOS::Array1D<TDR::AssessmentItem> AssessmentArray;
	
	/// Get a list of assessments that have been assigned to a PTO
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param assessments Assessment information is stored here
	/// @return true/false false indicates the data in assessments is no valid
	bool GetPTOAssessments(const S_UINT16 PTOIdentifier, AssessmentArray& assessments) const;

	/// Delete all assessments associated with a PTO
	void DeleteAssessments(const S_UINT16 PTOIdentifier);

	/// Set a single PTO assessment.  Replaces previous assessments.
	/// @param PTOIdentifier PTO ID
	/// @param assessmentFlag Final assessment of the Potential Threat Object (PTO)
	///						  Values: enumHighThreat, enumThreat, enumNoThreat, enumUnknown
	/// @param threatCategory The type of threat reported by the Automatic Threat Recognition (ATR) system.
	///						  Values eenumHME, enumPrecursor, enumProhibitedItem, enumContraband, enumAnomaly
	/// @param ability	Indicates if the Machine or Operator was able to assess the PTO without interference
	///					Values are enumNoInterference and enumShield.
	/// @param assessmentProbability Operator or Machine defined probability of the threat assessment in percentage of certainty between 0.0 and 1.0.
	///								 Values less than 0.0 will exclude the assessment probability from the PTO.
	///								 Values greater than 1.0 will cause an error.
	/// @param threatDescription Human readable description of the threat. An empty string will exclude the threat description from the PTO.
	/// @return true/false false indicates one or more supplied values are invalid.
	bool SetPTOAssessment(const S_UINT16 PTOIdentifier, 
		const TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG assessmentFlag = TDRTypes::AssessmentSequence::AssessmentItem::enumUnknown,
		const TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY threatCategory = TDRTypes::AssessmentSequence::AssessmentItem::enumAnomaly,
		const TDRTypes::AssessmentSequence::AssessmentItem::ABILITY_ASSESSMENT ability = TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference,
		const DcsLongText& threatDescription = "",
		const float assessmentProbability = -1.0f );

	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nAssessment Index for assessment
	/// @see SetPTOAssessment
	TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG GetPTOAssessmentFlag(const S_UINT16 PTOIdentifier, const S_UINT16 nAssessment = 0)const;
	/// Returns the assessment flag of the first assessment in the first PTO
	/// @see SetPTOAssessment
	TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG GetPTOAssessmentFlag()const;
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nAssessment Index for assessment
	/// @see SetPTOAssessment
	TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY GetPTOAssessmentThreatCategory(const S_UINT16 PTOIdentifier, const S_UINT16 nAssessment = 0)const;
	/// Returns the assessment threat category of the first assessment in the first PTO
	/// @see SetPTOAssessment
	TDRTypes::AssessmentSequence::AssessmentItem::THREAT_CATEGORY GetPTOAssessmentThreatCategory()const;
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nAssessment Index for assessment
	/// @see SetPTOAssessment
	TDRTypes::AssessmentSequence::AssessmentItem::ABILITY_ASSESSMENT GetPTOAssessmentAbility(const S_UINT16 PTOIdentifier, const S_UINT16 nAssessment = 0)const;
	/// Returns the assessment ability of the first assessment in the first PTO
	/// @see SetPTOAssessment
	TDRTypes::AssessmentSequence::AssessmentItem::ABILITY_ASSESSMENT GetPTOAssessmentAbility()const;
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nAssessment Index for assessment
	/// @see SetPTOAssessment
	DcsLongText GetPTOAssessmentDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nAssessment = 0)const;
	/// Returns the assessment description of the first assessment in the first PTO
	/// @see SetPTOAssessment
	DcsLongText GetPTOAssessmentDescription()const;
	/// Returns the assessment probability for the given Assessment in the given PTO. 
	/// Valid values for the Assessment Probability are in the range [0,1].
	/// Values < 0.0f indicate that no Assessment Probability has been determined.
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nAssessment Index for assessment
	/// @see SetPTOAssessment
	float GetPTOAssessmentProbability(const S_UINT16 PTOIdentifier, const S_UINT16 nAssessment = 0)const;
	/// Returns the assessment probability of the first assessment in the first PTO
	/// @see SetPTOAssessment
	float GetPTOAssessmentProbability()const;

	typedef Point3D<float> ControlPoint;
	typedef Array1D<ControlPoint> BoundingPolygon;
	
	/// Indicate the (x,y,z) vertices bounding the PTO for on screen presentation.
	/// If two points are specified, they indicate the major diagonal of a volume.
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param controlPoints Two or more (x,y,z) points must be given
	/// @param nRepresentation PTO representation index that controlPoints refers to
	/// @return true/false false if not enough points are given
	bool SetThreatBoundingPolygon(const S_UINT16 PTOIdentifier, const BoundingPolygon& controlPoints, const S_UINT16 nRepresentation);
	/// @see SetThreatBoundingPolygon
	bool GetThreatBoundingPolygon(const S_UINT16 PTOIdentifier, BoundingPolygon& controlPoints, const S_UINT16 nRepresentation)const;
	
	/// Add Voxel description of a Region Of Interest (ROI) for the PTO.
	/// There is one Threat Region of Interest (ROI) per PTO.
	///
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param ptoBase (x,y,z) location of the starting corner point in voxel/pixel space 
	///			for a bounding box surrounding the PTO.
	/// @param ptoExtents (x,y,z) dimensions of the pixels/voxels in image space
	///			for a bounding box starting at ptoBase that surrounds the PTO.
	/// @param ptoMask A mask indicating which pixels/voxels described by the Base and Extents are in the PTO. 
	///					1 indicates inside the PTO. An empty bitmap indicates the whole region is in the PTO.
	/// @param nRepresentation The PTO representation index that the region of interest refers to
	/// @return true/false false
	bool SetThreatRegionOfInterest(
		const S_UINT16 PTOIdentifier,
		const Point3D<float>& ptoBase,
		const Point3D<float>& ptoExtents,
		const Bitmap& ptoMask,			// By default an empty Bitmap indicates the whole region is in the PTO.
		const S_UINT16 nRepresentation
	);

	/// @see SetThreatRegionOfInterest
	bool GetThreatRegionOfInterest(const S_UINT16 PTOIdentifier, Point3D<float>& PTOBase, Point3D<float>& PTOExtents, Bitmap& bitmap, const S_UINT16 nRepresentation) const;

	/// Add a reference in the PTO to another DICOS object containing information for this TDR. 
	/// Internally, also adds the reference with SDICOS::IODCommon::AddReferencedSopInstance().
	/// The DICOS object can be a CT, DX, AIT etc. scan or another Threat Detection Report (TDR).
	/// The instance UID should reference the scan UID in the DICOS object.
	///
	/// @param PTOIdentifier Numeric Identifier for the PTO
	/// @param referencedSopClassUID		IOD specific SOP Class UID. See SOPClassUID in SdcsSopClassUID.h
	/// @param referencedSopInstanceUID		Unique identifier for the DICOS object. This is SOP Instance UID.
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true/false false if either parameter is not a valid DcsUniqueIdentifier
	/// @see SDICOS::IODCommon::AddReferencedSopInstance
	bool AddReferencedInstance(
		const S_UINT16 PTOIdentifier,
		const DcsUniqueIdentifier& referencedSopClassUID,
		const DcsUniqueIdentifier& referencedSopInstanceUID, 
		const S_UINT16 nRepresentation
	);
	
	/// @see AddReferencedInstance
	bool GetReferencedInstances(const S_UINT16 PTOIdentifier, Array1D<SDICOS::SopInstanceReference>& referencedInstances, const S_UINT16 nRepresentation) const;
	
	/// Clears current references and sets the referenced scans in SDICOS::IODCommon to match those in each PTO.
	/// Referenced Scan Sequence is required for TDR
	/// @see SDICOS::IODCommon::AddReferencedSopInstance
	void MatchReferencedScanSequenceToPTOs();

	/// The PTO's Geometric Centroid given in image space.
	///		i) Values in image space (i.e. Z indicates frame number and starts at Z=1 for 3D images)
	///		ii) 2D images: Z = 0
	/// 
	/// @param PTOIdentifier Numeric Identifier for the PTO
	///	@param ptCenter Point representing the location of the PTO's center
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	bool SetBaggagePTOCenter(const S_UINT16 PTOIdentifier, const Point3D<float>& ptCenter, const S_UINT16 nRepresentation);
	/// @see SetBaggagePTOCenterOfMass
	Point3D<float> GetBaggagePTOCenter(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// Returns true if data is present
	bool HasBaggagePTOCenter(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// Deletes data
	bool DeleteBaggagePTOCenter(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// The PTO's Center of Mass given in image space.
	///		i) Values in image space(i.e.Z indicates frame number and starts at Z = 1 for 3D images)
	///		ii) 2D images: Z = 0
	///
	/// @param PTOIdentifier Numeric Identifier for the PTO
	///	@param ptCenter Point representing the location of the PTO's center of mass
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	bool SetBaggagePTOCenterOfMass(const S_UINT16 PTOIdentifier, const Point3D<float>& ptCenter, const S_UINT16 nRepresentation);
	/// @see SetBaggagePTOCenterOfMass
	Point3D<float> GetBaggagePTOCenterOfMass(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// Returns true if data is present
	bool HasBaggagePTOCenterOfMass(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// Deletes data
	bool DeleteBaggagePTOCenterOfMass(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// Set details specific to a Baggage Threat Detection Report
	/// The Object Of Inspection (OOI) Type must be set to enumBaggage and the PTO ThreatType set to enumThreatTypeBaggage.
	/// See SDICOS::IODCommon::SetOOIType() in SdcsTemplateBase.h.
	/// @param PTOIdentifier Numeric identifier for the PTO.
	/// @param PTOMassInGrams			The PTO's mass is required if the scan is a CT and the TDR Type is Machine.
	/// @param PTODensityInGramsPerCC	The PTO's density is required if the scan is a CT and the TDR Type is Machine.
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true/false false if the TDR Type is not set to enumBaggage or PTOIdentifier is not valid.
	bool SetBaggagePTODetails(
		const S_UINT16 PTOIdentifier,
		const float PTOMassInGrams,
		const float PTODensityInGramsPerCC,
		const S_UINT16 nRepresentation
	);

	/// @see SetBaggagePTODetails
	bool GetBaggagePTODetails(const S_UINT16 PTOIdentifier, float& PTOMass, float& PTODensity, const S_UINT16 nRepresentation) const;

	/// The PTO's Mass in grams
	/// @param PTOIdentifier   Numeric identifier for the PTO
	/// @param fMassInGrams  The PTO's mass is required if the scan is a CT and the TDR Type is Machine.
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	bool SetBaggagePTOMassInGrams(const S_UINT16 PTOIdentifier, const float fMassInGrams, const S_UINT16 nRepresentation);
	/// @see SetBaggagePTOMassInGrams
	float GetBaggagePTOMassInGrams(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Returns true if data is present
	bool HasBaggagePTOMassInGrams(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Deletes data
	bool DeleteBaggagePTOMassInGrams(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// The PTO's Density in grams CC
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param fDensityInGramsPerCC The PTO's density is required if the scan is a CT and the TDR Type is Machine.
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	bool SetBaggagePTODensityInGramsPerCC(const S_UINT16 PTOIdentifier, const float fDensityInGramsPerCC, const S_UINT16 nRepresentation);
	/// @see SetBaggagePTODensityInGramsPerCC
	float GetBaggagePTODensityInGramsPerCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Returns true if data is present
	bool HasBaggagePTODensityInGramsPerCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Deletes data
	bool DeleteBaggagePTODensityInGramsPerCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
	
	/// A description for the PTO's location
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param dsDescription Short text describing the PTO's location
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	bool SetBaggagePTOLocationDescription(const S_UINT16 PTOIdentifier, const DcsShortText &dsDescription, const S_UINT16 nRepresentation);
	/// @see SetBaggagePTOLocationDescription
	DcsString GetBaggagePTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Returns true if the value is set
	bool HasBaggagePTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Deletes data
	bool DeleteBaggagePTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
	
	/// The PTO's volume in CC's
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param fVolumeInCC The PTO's volume in CC's
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	bool SetBaggagePTOVolumeInCC(const S_UINT16 PTOIdentifier, const float fVolumeInCC, const S_UINT16 nRepresentation);
	/// @see SetBaggagePTOVolumeInCC
	float GetBaggagePTOVolumeInCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Returns true if the value is set
	bool HasBaggagePTOVolumeInCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Deletes data
	bool DeleteBaggagePTOVolumeInCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// Set the Z-effective value for a baggage PTO
	/// @param PTOIdentifier Numeric identifier for the PTO.
	/// @param fZeffective Z-effective value for PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	bool SetBaggageZeffective(const S_UINT16 PTOIdentifier, const float fZeffective, const S_UINT16 nRepresentation);
	/// @return Returns false if the PTO does not have a Z-effective value
	/// @see SetBaggageZeffective
	bool GetBaggageZeffective(const S_UINT16 PTOIdentifier, float &fZeffective, const S_UINT16 nRepresentation)const;
	/// Returns true if data is present
	bool HasBaggageZeffective(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Delete the Z-effective value from the specified PTO
	bool DeleteBaggageZeffective(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// An alternative to Z Effective, Zeff is based on the calculated x-ray 
	/// properties of a compound. Zeff is designed to closely match the actual 
	/// x-ray absorption of each material over the spectral region of interest. 
	/// Zeff removes the arbitrariness and lack of optimization entailed in using Z Effective
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param fVal Zeff alternative value for PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true/false
	bool SetBaggageZeffAlternative(const S_UINT16 PTOIdentifier, const float fVal, const S_UINT16 nRepresentation);
	/// @see SetBaggageZeffAlternative
	float GetBaggageZeffAlternative(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Returns true if data is present
	bool HasBaggageZeffAlternative(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Deletes data
	bool DeleteBaggageZeffAlternative(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// The electron density per unit volume [Mole of electrons per cm^3]
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param fVal value containing the electron density per unit volume PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	bool SetBaggageRho(const S_UINT16 PTOIdentifier, const float fVal, const S_UINT16 nRepresentation);
	/// @see SetRho
	float GetBaggageRho(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Returns true if data is present
	bool HasBaggageRho(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Deletes data
	bool DeleteBaggageRho(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// Bounding Box Resolution [Optional]
	/// Enumeration describing possible bounding box resolution methods to avoid multiple bounding boxes on the same PTO
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nBoundingBox Specifies which bounding box resolution method was used
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true/false false if unable to set a valid value
	bool SetBaggageBoundingBoxResolution(const S_UINT16 PTOIdentifier,
										const TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::BOUNDING_BOX_RESOLUTION nBoundingBox,
										const S_UINT16 nRepresentation);
	/// @see SetBaggageBoundingBoxResolution
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return returns enumUnknownBoundingBoxResolution if not set
	TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::BOUNDING_BOX_RESOLUTION GetBaggageBoundingBoxResolution(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true if data is present
	bool HasBaggageBoundingBoxResolution(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// Delete bounding box enum so that it is not written to the DICOS file
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	void DeleteBaggageBoundingBoxResolution(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// Aggregated Method For Bounding Box
	/// Required if the Bounding Box Resolution is set to OTHER.
	/// Text description on how the bounding box resolution was performed from the TDRs
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param strDescription Describes the bounding box resolution method performed from the different TDRs
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true/false false if given empty string as input
	bool SetBaggageAggregatedMethodForBoundingBox(const S_UINT16 PTOIdentifier, const DcsLongText& strDescription, const S_UINT16 nRepresentation);
	/// @see SetBaggageAggregatedMethodForBoundingBox
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return returns empty string if not accessible
	DcsLongText GetBaggageAggregatedMethodForBoundingBox(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true if data is present
	bool HasBaggageAggregatedMethodForBoundingBox(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// Delete description so that it is not written to the DICOS file
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	void DeleteBaggageAggregatedMethodForBoundingBox(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// ROI Resolution [Optional]
	/// Required if Bounding Box Resolution is present
	/// Enumeration describing possible ROI resolution methods to avoid multiple ROIs on the same PTO
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nROIResolution Specifies which ROI resolution method was used
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true/false false if unable to set a valid value
	bool SetBaggageROIResolution(const S_UINT16 PTOIdentifier,
								const TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::ROI_RESOLUTION nROIResolution,
								const S_UINT16 nRepresentation);
	/// @see SetBaggageROIResolution
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return returns enumUnknownROIResolution if not set
	TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::ROI_RESOLUTION GetBaggageROIResolution(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true if data is present
	bool HasBaggageROIResolution(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// Delete mass so that it is not written to the DICOS file
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	void DeleteBaggageROIResolution(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// Aggregated Method of ROI Resolution
	/// Required if ROI Resolution is set to OTHER
	/// Text description on how the ROI resolution was performed from the TDRs
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param strDescription Describes the bounding box resolution method performed from the different TDRs
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true/false false if input is the empty string
	/// @see SetBaggageROIResolution
	bool SetBaggageAggregatedMethodOfROIResolution(const S_UINT16 PTOIdentifier, const DcsLongText& strDescription, const S_UINT16 nRepresentation);
	/// @see SetBaggageAggregatedMethodOfROIResolution
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return returns the empty string if not set
	DcsLongText GetBaggageAggregatedMethodOfROIResolution(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	/// @return true if data is present
	bool HasBaggageAggregatedMethodOfROIResolution(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// Delete description
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param nRepresentation The PTO representation index that the referenced instance refers to
	void DeleteBaggageAggregatedMethodOfROIResolution(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// Set an optional text description of the PTOs location.
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param PTOLocation Optional text description of the PTO's location.
	/// @param nRepresentation PTO representation index that PTOLocation refers to
	/// @return true/false
	bool SetPersonPTOLocationDescription(const S_UINT16 PTOIdentifier, const DcsShortText& PTOLocation, const S_UINT16 nRepresentation);
	/// @see SetPersonPTOLocationDescription
	bool GetPersonPTOLocationDescription(const S_UINT16 PTOIdentifier, DcsShortText& PTOLocation, const S_UINT16 nRepresentation) const;
	/// @see SetPersonPTOLocationDescription
	DcsString GetPersonPTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	/// Returns true if data is present
	bool HasPersonPTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Deletes data
	bool DeletePersonPTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// Set optional location of PTO's physical center
	bool SetPersonPTOCenter(const S_UINT16 PTOIdentifier, const Point3D<float>& ptCenter, const S_UINT16 nRepresentation);
	/// @see SetPersonPTOCenter
	Point3D<float> GetPersonPTOCenter(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Returns true if data is present
	bool HasPersonPTOCenter(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Delete data
	bool DeletePersonPTOCenter(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
	
	/// Set details specific to a Person Threat Detection Report
	/// The Object of Inspection (OOI) type must be set to enumPerson and the PTO ThreatType set to enumThreatTypePerson.
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param PTOLocation Optional text description of the PTO's location.
	/// @param PTOCenter Optional location of PTO's physical center
	/// @param nRepresentation PTO representation index that PTOCenter and PTOLocation refer to
	/// @return true/false false if TDR Type is not set to enumPerson or PTOIdentifier is not valid.
	bool SetPersonPTODetails(
		const S_UINT16 PTOIdentifier,
		const DcsShortText& PTOLocation,
		const Point3D<float>& PTOCenter, 
		const S_UINT16 nRepresentation
	);
	
	/// @see SetPersonPTODetails
	bool GetPersonPTODetails(const S_UINT16 PTOIdentifier, DcsShortText& PTOLocation, Point3D<float>& PTOCenter, const S_UINT16 nRepresentation) const;

	/// Add the center location of an anomalous region in the PTO intended for on-screen presentation.
	/// More than one position can be added for a PTO
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param anomalyLocations Point3D representing center point location.
	/// @param nRepresentation PTO representation index that anomalyLocations refers to
	/// @return true/false 
	bool AddPersonAnomalyIndicator(const S_UINT16 PTOIdentifier, const Point3D<float>& anomalyLocations, const S_UINT16 nRepresentation);

	///
	/// \typedef SDICOS::Array1D< SDICOS::Point3D<float> > Point3DArray
	///
	typedef SDICOS::Array1D< SDICOS::Point3D<float> > Point3DArray;
	
	/// Add the center locations of an anomalous region in the PTO intended for on-screen presentation.
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param anomalyLocations Point3D representing center point location.
	/// @param nRepresentation PTO representation index that anomalyLocations refers to
	/// @return true/false 
	bool AddPersonAnomalyIndicator(const S_UINT16 PTOIdentifier, const Point3DArray& anomalyLocations, const S_UINT16 nRepresentation);
	
	/// @see AddPersonAnomalyIndicator
	/// @return true/false false if no indicators could be found
	bool GetPersonAnomalyIndicators(const S_UINT16 PTOIdentifier, Point3DArray& anomalyLocations, const S_UINT16 nRepresentation) const;
	/// Returns true if data is present
	bool HasPersonAnomalyIndicators(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Delete data
	bool DeletePersonAnomalyIndicators(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// Set the AIT Body zones for the PTO
	/// @param PTOIdentifier Numeric identifier for the PTO
	/// @param vAitBodyZones The body zones for the PTO
	/// @param nRepresentation PTO representation index that vAitBodyZones refers to
	bool SetPersonPTORegionSequence(const S_UINT16 PTOIdentifier, const Array1D<AitBodyZones> &vAitBodyZones, const S_UINT16 nRepresentation);
	/// @see SetPersonPTORegionSequence
	bool GetPersonPTORegionSequence(const S_UINT16 PTOIdentifier, Array1D<AitBodyZones> &vAitBodyZones, const S_UINT16 nRepresentation) const;
	/// Returns true if data is present
	bool HasPersonPTORegionSequence(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	/// Delete data
	bool DeletePersonPTORegionSequence(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);

	/// Returns SOP Class UID
	virtual DcsUniqueIdentifier GetSopClassUID()const;
	
	// Common Instance Reference/ Scanner Common in IOD Common

	/// Constant for indicating that no Instance Number has been set
	static const S_INT32 INVALID_INSTANCE_NUMBER;
	
protected:

	/// Override to allocate a derived module-level API object.
	/// By default allocates TDRModule.  This module is internally
	/// used for reading, writing, and networking.
	/// @return Dynamically allocated module-level API object
	virtual TDRModule* AllocateModule()const;

	/// Override this function to set attributes in the SDICOS::TDR object that are not set with TDR
	/// WriteDerived_internal is called by the TDR::Write() methods before attributes in the TDR class are written.
	/// If the derived class wishes to further restrict values 
	/// @param tdr TDR object to set new values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors writing data
	virtual bool WriteDerived_internal(SDICOS::TDRModule  &tdr, ErrorLog &errorlog)const;
	
	/// Override this function to retrieve attributes from the SDICOS::TDR object that are not retrieved by TDR
	/// ReadDerived_internal is called by TDR::Read() methods before attributes in the TDR class are read.
	/// @param tdr TDR object to retrieve read values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors reading data
	virtual bool ReadDerived_internal(const SDICOS::TDRModule &tdr, ErrorLog &errorlog);
	
	class ImplTDR;
	
	ImplTDR* GetImpl();
	const ImplTDR* GetImpl()const;

private:
	ImplTDR * m_pImplTDR; ///< Internal implementation
	
	/// Do not allow reading multiple TDRs at once
	virtual bool Read(const DicosFileListing::SopInstance&, Array1D< std::pair<Filename, ErrorLog> > &, IMemoryManager *pMemMgr = S_NULL);
	
	/// Do not allow writing multiple TDRs at once.
	virtual bool Write(const Filename &, Array1D< std::pair<Filename, ErrorLog> > &, const DicosFile::TRANSFER_SYNTAX)const;
};

} // SDICOS

#endif	/* _STRATOVAN_DICOS_SDCS_TEMPLATE_TDR_H_ */

