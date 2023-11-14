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
/* 
 * File:   TemplateBase.h
 * Author: bgregorski
 *
 * Created on December 18, 2014, 9:41 AM
 */

#ifndef _STRATOVAN_DICOS_TEMPLATE_CLASSES_BASE_H_
#define	_STRATOVAN_DICOS_TEMPLATE_CLASSES_BASE_H_

#include "SDICOS/ScannerCommon.h"
#include "SDICOS/GeneralSeriesModule.h"
#include "SDICOS/GeneralEquipmentModule.h"
#include "SDICOS/DicosFile.h"
#include "SDICOS/ClientManager.h"
#include "SDICOS/ObjectOfInspectionOwnerUser.h"
#include "SDICOS/ItineraryUser.h"

namespace SDICOS 
{

///
/// \class IODCommon
/// \brief Base class for Information Object Definition (IOD) Template classes containing shared, required attributes.
///
/// Notes:
///		1) The IODCommon class contains attributes that are common to all IODs.
///		2) In general, only required attributes are supported as part of the API.
///		3) Template classes for specific IODs derive from IODCommon and implement IOD specific attributes.
///		4) Default values for most string attributes are set to 'UNKNOWN'.
///		5) Default values for date and time attributes are set to DcsDate::Today() and DcsTime::Now().
///		6) Bad or non-conformant values encountered during the reading/loading of a DICOS file are ignored and replaced with the default value.
///
/// Notes:
///		Only required attributes in the SOP Common Module are supported in the API.
///		No API is provided for the Acquisition Context Module because all attributes are under a type 2C (Mandatory but NULL permissible) Sequence. Module handled by deriving class.
///		Limited API is provided for the Common Instance Reference. Other module functionality handled by deriving class.
///
///		Provides API for:
///			- OOI Owner
///			- Itinerary Module
///			- Object of Inspection (OOI)
///			- General Scan Module
///			- General Series Module
///			- General Equipment
///			- SOP Common Module
///			- Common Instance Reference Module (Getter functions only)
///
///		No API provided for:
///			- Acquisition Context Module
///			- Common Instance Reference (other than Getters)
///
class IODCommon : 
	public ObjectOfInspectionOwnerUser,	// Methods for accessing OOI Owner Module. See EnableObjectOfInspectionOwner() and DisableObjectOfInspectionOwner()
	public ItineraryUser				// Interface to Itinerary Module. See EnableItinerary() and DisableItineray()	

{
public:
	/// Default constructor
	IODCommon();
	
	/// Copy Constructor
	IODCommon(const IODCommon& iod);
	
	/// Destructor
	virtual ~IODCommon();
	
	/// Free allocated resources
	virtual void FreeMemory();
	
	/// Assignment operator
	IODCommon& operator=(const IODCommon&);
	
	/// Comparison operator
	bool operator==(const IODCommon&) const;
	
	/// Comparison operator
	bool operator!=(const IODCommon&) const;

	typedef enum
	{
		enumAIT2D,
		enumAIT3D,
		enumCT,
		enumXRAY,	///< X-Ray / DX
		enumQR,
		enumTDR,
		enumHDAIT,
		enumWAIT,
		enumETD,	///< Explosive Trace Detection
		enumDPC,
		enumXRD,
		enumUnknownModality
	}MODALITY;
	
	/// Read a series
	/// @param sopinstance	A listing of all file names associated with a SOP Instance UID. Contains data for an IOD series. 
	/// @param vErrorlogs	An array of (filename, error log) pairs for each file read
	/// @param pMemMgr		Memory manager for custom pixel data allocation
	/// @return true/false	false if files could not be read or if they contain errors
	virtual bool Read(const DicosFileListing::SopInstance &sopinstance, Array1D< std::pair<Filename, ErrorLog> > &vErrorlogs, IMemoryManager *pMemMgr = S_NULL);
		
	/// Read from a file
	virtual bool Read(const Filename &filename, ErrorLog& errorLog, IMemoryManager *pMemMgr = S_NULL) = 0;
	/// Read from a memory file
	/// @param memfile		Memory buffer to read from
	/// @param errorLog		Errors logged during read operation
	/// @param pMemMgr		Memory manager for custom pixel data allocation
	virtual bool Read(MemoryFile &memfile, ErrorLog &errorLog, IMemoryManager *pMemMgr = S_NULL) = 0;

	/// Write the DICOS file. Pure virtual method implemented by derived class.
	/// @param filename				Destination file
	/// @param errorlog				Log errors with the DICOS file here
	/// @param nTransferSyntax		DICOS transfer syntax defaults to Little-endian explicit using lossless JPEG compression.
	/// @return true/false			false if file could not be opened or if it contains errors
	virtual bool Write(const Filename &filename, ErrorLog &errorlog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG) const = 0;
		
	/// Write function used for a series that requires more than one file
	/// @see GetNumberOfFilesToCreate
	/// @param filenameBase		The base file name, which defines the folder and base name. Ex. filenameBase = "C:\MyFolder\dcsfile", files will have the name pattern "dcsfile0000", "dcsfile0001", etc.
	/// @param vErrorlogs		An array of (filename, error log) pairs for each file located
	/// @param nTransferSyntax	Transfer syntax use when creating DICOS file(s)
	/// @return true/false		false if files could not be read or contained errors.
	virtual bool Write(const Filename &filenameBase, Array1D< std::pair<Filename, ErrorLog> > &vErrorlogs, 
						const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG)const;

	/// Write to a memory file
	/// @param memfile			Output memory buffer
	/// @param errorlog			Errors logged during write operation
	/// @param nTransferSyntax	Transfer syntax use when writing DICOS data
	virtual bool Write(MemoryFile &memfile, ErrorLog &errorlog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG) const = 0;

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

	/// Check the attributes in the IODCommon object against the DICOS specification.
	virtual bool Validate(ErrorLog& errorlog) const;

	virtual MODALITY GetModality()const = 0;

	virtual DcsUniqueIdentifier GetSopClassUID()const = 0;


	/////////////////////////////////////////////////////
	//  Object of Inspectiion Owner

	/// Enable Object of Inspection Owner Module's attributes to be writted during Write()
	void EnableObjectOfInspectionOwner();

	/// Disable Object of Inspection Owner Module from being written to DICOS file
	/// IsObjectOfInspectionOwnerEnabled() returns false after calling.
	void DisableObjectOfInspectionOwner();

	/// @see EnableObjectOfInspectionOwner()
	/// @return true/false
	bool IsObjectOfInspectionOwnerEnabled() const;


	/////////////////////////////////////////////////////
	//  Itinerary

	/// Enable Itinerary attributes to be written during Write()
	/// ItineraryUser attributes are disabled by default
	void EnableItinerary();

	/// Itinerary attributes will not be written during Write()
	void DisableItinerary();

	/// @see EnableItinerary
	/// @return true/false
	bool IsItineraryEnabled() const;


	///////////////////////////////////////
	/// Object of Inspection (OOI))

	/// OOI (Object of Inspection) ID
	/// @param strID Primary airport identification number or code for the object
	///				 Example: Bag number from a baggage handling system.
	/// @return true/false false if strID is not a valid DcsLongString
	bool SetOOIID(const DcsLongString &strID);
	/// @see SetOOIID
	const DcsLongString& GetOOIID()const;

	/// OOI (Object of Inspection) ID Assigning Authority
	/// @param strAssigningAuthority	ID of authority that issued the OOI ID.
	/// @return true/false false if strAssigningAuthority is not a valid DcsLongString
	bool SetOOIIDAssigningAuthority(const DcsLongString &strAssigningAuthority);
	/// @see SetOOIIDAssigningAuthority
	const DcsLongString& GetOOIIDAssigningAuthority()const;

	/// OOI (Object of Inspection) ID Type
	/// @param nType (enumText, enuRFID, enumBarCode, enumMRP)
	/// @return true/false false if nType is not valid
	bool SetOOIIDType(const ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE nType);
	/// @see SetOOIIDType
	ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE GetOOIIDType()const;

	/// Set the mass of the OOI. [optional]
	/// @param massInGrams	Mass of OOI. Mass <= 0.0 will not be written to the DICOS file
	/// @return true/false 
	bool SetOOIMassInGrams(const float massInGrams);
	/// @see SetOOIMassInGrams
	float GetOOIMassInGrams() const;
	/// Has the mass in grams been set
	/// @return true/false
	bool HasOOIMass() const;
	/// Set Mass so that it is not written to the DICOS file
	void DeleteOOIMass();

	/// Set the gender if the OOI type is person. Default is 'U'=unknown.
	/// Required only if OOI type is enumTypePerson.
	/// @param nGender	Options are 'M', 'F', 'O', 'U'.
	/// @return true/false
	bool SetGender(const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER nGender);

	/// @see SetGender
	ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER GetGender() const;

	/// Add alternative identification information for the Object of Inspection (OOI). [optional]
	/// @param OOIId Object of Inspection ID
	/// @param OOIIdIssuer Object of Inspection ID Assigning Authority
	/// @param OOIIdType Object of Inspection Type
	/// @return true/false
	bool AddAlternativeOOIId(
		const DcsLongString& OOIId, const DcsLongString& OOIIdIssuer, const ObjectOfInspectionModule::IdInfo::OBJECT_OF_INSPECTION_ID_TYPE OOIIdType
	);
		
	/// Get all of the Alternative OOI Id information entered with AddAlternativeOOIIds
	bool GetAlternativeOOIIds(std::vector<SDICOS::ObjectOfInspectionModule::IdInfo>& ids) const;
	
	/// Get an alternative OOI Id by index
	bool GetAlternativeOOIId(const S_UINT32 index, SDICOS::ObjectOfInspectionModule::IdInfo& idInfo) const;
		
	/// Remove the indicate Object of Inspection Id
	void DeleteAlternativeOOIId(const DcsLongString& OOIId);
		
	/// Remove all alternative Object of Inspection IDs so that they are not written to the DICOS file
	void DeleteAllAlternativeOOIIds();
		
	S_UINT32 GetNumAlternativeOOIIds() const;
		
	typedef struct
	{
		DcsShortString algorithmCode;			///< Unique identification code for the threat detection algorithm to be used.
		DcsShortString algorithmCodingScheme;	///< Name of the coding scheme that algorithmCode belongs to.
		DcsLongString algorithmDescription;		///< Human readable text describing the Code, Coding Scheme combination.
	} AlgorithmRoutingCode;
			
	/// Set the algorithm routing code that identifies the threat detection algorithm to be used. [optional]
	/// The code is passed from an external system such as the Baggage Handling System.
	/// @param algorithmCode			Unique identification code for the threat detection algorithm to be used.
	/// @param algorithmCodingScheme	Name of the coding scheme that algorithmCode belongs to.
	/// @param algorithmDescription		Human readable text describing the Code, Coding Scheme combination.
	/// @return true/false
	bool SetAlgorithmRoutingCode(const DcsShortString& algorithmCode, const DcsShortString& algorithmCodingScheme, const DcsLongString& algorithmDescription);
		
	/// @see SetAlgorithmRoutingCode
	/// @return true/false returns false if Routing Code information could not be fetched
	bool GetAlgorithmRoutingCode(AlgorithmRoutingCode& algorithmRoutingCode);
		
	/// Remove Algorithm routing code 
	void DeleteAlgorithmRoutingCode();

	/// OOI (Object of Inspection) Type
	bool SetOOIType(const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE nType);
	/// @see SetOOIType
	ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE GetOOIType()const;

	/// Set additional text that describes the Object of Inspection Type. [optional]
	/// @param OOITypeDescriptor Additional text describing the Object of Inspection Type
	/// @return true/false
	bool SetOOITypeDescriptor(const SDICOS::DcsLongText& OOITypeDescriptor);
		
	/// @see SetOOITypeDescriptor
	bool GetOOITypeDescriptor(DcsLongText& OOITypeDescriptor) const;
		
	/// @see SetOOITypeDescriptor
	DcsLongText GetOOITypeDescriptor() const;
		
	/// Remove OOI Type Descriptor so that it is not written to the DICOS file
	void DeleteOOITypeDescriptor();
		
	/// Set Object of Inspection Size in Meters [optional]
	/// @return true/false false if any value is <= 0.0
	bool SetOOISizeInMeters(const float height, const float length, const float width);
		
	/// @see SetOOISizeInMeters
	bool GetOOISizeInMeters(float& height, float& length, float& width) const;
		
	/// Remove OOI size so that it is not written to the DICOS file
	void DeleteOOISize();

	/// Set baggage description
	bool SetBagDescription(const DcsLongString &ds);
	/// @see SetBagDescription
	DcsString GetBagDescription()const;
	/// Returns true if data is set
	bool HasBagDescription()const;
	/// Delete data
	void DeleteBagDescription();
		
	///////////////////////////////
	/// General Scan Module

	/// Scan ID
	/// @param strID Human readable Scan ID
	/// @return true/false false if strID is not a valid DcsShortString
	bool SetScanID(const DcsShortString &strID);
	/// @see SetScanID
	const DcsShortString& GetScanID()const;

	/// Scan Description is an optional text description of the scan
	bool SetScanDescription(const DcsLongString &strDescription);
	/// @see SetScanDescription
	const DcsLongString& GetScanDescription()const;

	/// Scan Instance UID
	/// @param strScanUID Unique ID of Scan. Randomly generated by default constructor
	/// @return true/false false if strScanUID is not a valid DcsUniqueIdentifier
	bool SetScanInstanceUID(const DcsUniqueIdentifier &strScanUID);
	/// Auto generate Scan Instance UID
	void GenerateScanInstanceUID();
	/// @see SetScanInstanceUID
	const DcsUniqueIdentifier& GetScanInstanceUID()const;

	/// Scan start date and time
	/// @param strDate	Date of scan start. (Day, Month, Year)
	/// @param strTime	Time of scan start. (Hour.minute, second, second fraction)
	/// @return true/false false if strDate or strTime are not valid
	bool SetScanStartDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetScanStartDateAndTime
	const DcsDate& GetScanStartDate()const;
	/// @see SetScanStartDateAndTime
	const DcsTime& GetScanStartTime()const;
	
	/// Scan Type
	/// @param nType must be enumOperational or enumNonOperational
	/// @return true/false false if nType is not valid/
	bool SetScanType(const GeneralScanModule::SCAN_TYPE nType);
	/// @see SetScanType
	GeneralScanModule::SCAN_TYPE GetScanType()const;

	/// Total number of views for this scan
	void SetNumberOfViews(const S_UINT16 nNum);
	/// @see SetNumberOfViews
	S_UINT16 GetNumberOfViews()const;
	/// Returns true if value is set
	bool HasNumberOfViews()const;
	/// Delete data
	void DeleteNumberOfViews();

	/// Total number of energies for this scan
	void SetNumberOfEnergies(const S_UINT16 nNum);
	/// @see SetNumberOfEnergies
	S_UINT16 GetNumberOfEnergies()const;
	/// Returns true if value is set
	bool HasNumberOfEnergies()const;
	/// Delete data
	void DeleteNumberOfEnergies();

	/**
	 * \struct ReferencedSopInstance
	 * Represents a reference to another scan defined by the scan's identifiers
	 * SOP Instance UID and SOP Class UID
	 */
	struct ReferencedSopInstance
	{
		DcsUniqueIdentifier	m_strSopInstanceUID; ///< Referenced scan's SOP Instance UID
		DcsUniqueIdentifier	m_strSopClassUID; ///< Referenced scan's SOP Class UID (i.e. identifier for its modality)

		/// Convert m_strSOPClassUID to MODALITY enum
		SDICOS::IODCommon::MODALITY GetModality() const;
	};

	/// Add a reference to another scan by adding a referenced SOP instance
	bool AddReferencedSopInstance(const DcsUniqueIdentifier& strSopInstanceUID,
		const DcsUniqueIdentifier& strSopClassUID);

	/// Returns SOP instance UIDs from all references
	void GetReferencedSopInstances(Array1D<DcsUniqueIdentifier>& arrayReferences)const;

	/// Returns SOP instance UIDs and Class UIDs from all references
	void GetReferencedSopInstances(Array1D<ReferencedSopInstance>& arrayReferences)const;

	/// The IOD Contains one or more references
	bool HasReferencedInstances() const;

	/// Delete all referenced instances
	void ClearReferencedInstances();

	/////////////////////////////////
	/// General Series Module

	/// Series Instance UID
	/// @param strUID	Unique identifier for the series. Default value is randomly generated.
	/// @return true/false false if strUID is not a valid DcsUniqueIdentifier
	bool SetSeriesInstanceUID(const DcsUniqueIdentifier &strUID);
	/// Auto generate Series Instance UID
	void GenerateSeriesInstanceUID();
	/// @see SetSeriesInstanceUID
	const DcsUniqueIdentifier& GetSeriesInstanceUID()const;

	/// A number that identifies this series and is unique within a scan
	void SetSeriesNumber(const DcsInteger nNumber);
	/// @see SetSeriesNumber
	DcsInteger GetSeriesNumber()const;
	/// Returns true if value is set
	bool HasSeriesNumber()const;
	/// Delete data
	void DeleteSeriesNumber();

	/// View identifier for this series when using multi-view image data
	void SetSeriesView(const S_UINT16 nView);
	/// @see SetSeriesView
	S_UINT16 GetSeriesView()const;
	/// Returns true if value is set
	bool HasSeriesView()const;
	/// Delete data
	void DeleteSeriesView();

	/// Series View Description
	bool SetSeriesViewDescription(const DcsLongString& strDescription);
	/// @see SetSeriesViewDescription
	DcsString GetSeriesViewDescription()const;
	/// Returns true of value is set
	bool HasSeriesViewDescription()const;
	/// Delete data
	void DeleteSeriesViewDescription();

	/// Energy identifier for this series when using multi-energy image data
	void SetSeriesEnergy(const S_UINT16 nEnergy);
	/// @see SetSeriesEnergy
	S_UINT16 GetSeriesEnergy()const;
	/// Returns true if value is set
	bool HasSeriesEnergy()const;
	/// Delete data
	void DeleteSeriesEnergy();

	/// Series Energy Description
	bool SetSeriesEnergyDescription(const DcsLongString& strDescription);
	/// @see SetSeriesEnergyDescription
	DcsString GetSeriesEnergyDescription()const;
	/// Returns true of value is set
	bool HasSeriesEnergyDescription()const;
	/// Delete data
	void DeleteSeriesEnergyDescription();

	/// Series Date and Time
	/// @param strDate	Date of series creation. Default value is DcsDate::Today()
	/// @param strTime	Time of series creation. Default value is DcsTime::Now()
	/// @return true/false false if strDate or strTime is not a valid DcsDate or DcsTime object
	bool SetSeriesDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetSeriesDateAndTime
	const DcsDate& GetSeriesDate()const;
	/// @see SetSeriesDateAndTime
	const DcsTime& GetSeriesTime()const;

	/// Series Acquisition Status
	bool SetSeriesAcquisitionStatus(const GeneralSeriesModule::ACQUISITION_STATUS nStatus);
	/// @see SetSeriesAcquisitionStatus
	GeneralSeriesModule::ACQUISITION_STATUS GetSeriesAcquisitionStatus()const;

	////////////////////////////
	/// General Equipment

	/// Device Calibration Date and Time
	/// @param strDate	Date device was calibrated. Default value is DcsDate::Today()
	/// @param strTime	Time device was calibrated. Default value is DcsTime::Now()
	/// @return true/false false if strDate or strTime is not a valid DcsDate or DcsTime object
	bool SetDeviceCalibrationDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetDeviceCalibrationDateAndTime
	const DcsDate& GetDeviceCalibrationDate()const;
	/// @see SetDeviceCalibrationDateAndTime
	const DcsTime& GetDeviceCalibrationTime()const;

	/// Device Serial Number
	/// @param strSerialNumber	String representing device serial number
	/// @return true/false false if strSerialNumber is not a valid DcsLongString
	bool SetDeviceSerialNumber(const DcsLongString &strSerialNumber);
	/// @see SetDeviceSerialNumber
	const DcsLongString& GetDeviceSerialNumber()const;

	/// Machine Address (Physical Address)
	/// @param strMachineAddress Physical Address of machine (e.g. 1 infinite loop)
	/// @return true/false false if strMachineAddress is not a valid DcsShortText
	bool SetMachineAddress(const DcsShortText &strMachineAddress);
	/// @see SetMachineAddress
	const DcsShortText& GetMachineAddress()const;

	/// Machine Location (Location within Machine Address)
	/// @param strMachineLocation	Location at Machine Address
	/// @return true/false false if strMachineLocation is not a valid DcsLongString
	bool SetMachineLocation(const DcsLongString &strMachineLocation);
	/// @see SetMachineLocation
	const DcsLongString& GetMachineLocation()const;

	/// Machine ID
	/// @param strMachineID	String identifier for the machine
	/// @return true/false false if strMachineID is not a valid DcsShortString
	bool SetMachineID(const DcsShortString &strMachineID);
	/// @see SetMachineID
	const DcsShortString& GetMachineID()const;

	/// Machine Sub Location (User-defined location within Machine Location domain. e.g. terminal or security checkpoint)
	/// @param strMachineSubLocation	Location within Machine Location
	/// @return true/false false if strMachineSubLocation is not a valid DcsLongString
	bool SetMachineSubLocation(const DcsLongString &strMachineSubLocation);
	/// @see SetMachineLocation
	const DcsLongString& GetMachineSubLocation()const;

	/// Device Manufacturer
	/// @param strManufacturer	Device Manufacturer
	/// @return true/false false if strManufacturer is not a valid DcsLongStri g
	bool SetDeviceManufacturer(const DcsLongString &strManufacturer);
	/// @see SetDeviceManufacturer
	const DcsLongString& GetDeviceManufacturer()const;

	/// Device Manufacturer Model Name
	/// @param strModelName	Device Model Name
	/// @return true/false false if strModelName is not a valid DcsLongString
	bool SetDeviceManufacturerModelName(const DcsLongString &strModelName);
	/// @see SetDeviceManufacturerModelName
	const DcsLongString& GetDeviceManufacturerModelName()const;

	/// Device Software Version
	/// @param strSoftwareVersion	Device Software Version
	/// @return true/false false if strSoftwareVersion is not a valid DcsLongString
	bool SetDeviceSoftwareVersion(const DcsLongString &strSoftwareVersion);
	/// @see SetDeviceSoftwareVersion
	const DcsLongString& GetDeviceSoftwareVersion()const;

	/// Set Cluster ID: Storage Cluster ID of original physical location of OOI
	void SetClusterID(const S_UINT16 nVal);
	/// @see SetClusterID
	S_UINT16 GetClusterID()const;
	/// Returns true if the data is set
	bool HasClusterID()const;
	/// Deletes the data
	void DeleteClusterID();

	/// Bag Raw Path: Defines bag raw data location on storage cluster
	void SetBagRawPath(const S_INT16 nVal);
	/// @see SetBagRawPath
	S_INT16 GetBagRawPath()const;
	/// Returns true if the data is set
	bool HasBagRawPath()const;
	/// Deletes the data
	void DeleteBagRawPath();

	/// Bag Image Path: Defines bag image data location on storage cluster 
	void SetBagImagePath(const S_INT16 nVal);
	/// @see SetBagImagePath
	S_INT16 GetBagImagePath()const;
	/// Returns true if the data is set
	bool HasBagImagePath()const;
	/// Deletes the data
	void DeleteBagImagePath();

	/// Feed Mode: Defines the feed mode in use
	bool SetFeedMode(const GeneralEquipmentModule::FEED_MODE nMode);
	/// @see SetFeedMode
	GeneralEquipmentModule::FEED_MODE GetFeedMode()const;
	/// Returns true if the data is set
	bool HasFeedMode()const;
	/// Deletes the data
	void DeleteFeedMode();

	/// Data Collection Mode: Defines whether or not raw data is collected
	bool SetDataCollectionMode(const GeneralEquipmentModule::DATA_COLLECTION_MODE nMode);
	/// @see SetDataCollectionMode
	GeneralEquipmentModule::DATA_COLLECTION_MODE GetDataCollectionMode()const;
	/// Returns true if the data is set
	bool HasDataCollectionMode()const;
	/// Deletes the data
	void DeleteDataCollectionMode();

	/// Hold Mode: Defines whether the the bag is held inside the scanner for more slices
	bool SetHoldMode(const GeneralEquipmentModule::HOLD_MODE nMode);
	/// @see SetHoldMode
	GeneralEquipmentModule::HOLD_MODE GetHoldMode()const;
	/// Returns true if the data is set
	bool HasHoldMode()const;
	/// Deletes the data
	void DeleteHoldMode();

	/// Operation Mode: Define the operation mode of the bag
	bool SetOperationMode(const GeneralEquipmentModule::OPERATION_MODE nMode);
	/// @see SetOperationMode
	GeneralEquipmentModule::OPERATION_MODE GetOperationMode()const;
	/// Returns true if the data is set
	bool HasOperationMode()const;
	/// Deletes the data
	void DeleteOperationMode();

	/// Show Mode: Identifies the mode controlling on-screen display
	bool SetShowMode(const DcsShortString &dsMode);
	/// @see SetShowMode
	DcsString GetShowMode()const;
	/// Returns true if the data is set
	bool HasShowMode()const;
	/// Deletes the data
	void DeleteShowMode();

	/// TimeoutMode: Defines the conditions for a timeout
	bool SetTimeoutMode(const GeneralEquipmentModule::TIMEOUT_MODE nMode);
	/// @see SetTimeoutMode
	GeneralEquipmentModule::TIMEOUT_MODE GetTimeoutMode()const;
	/// Returns true if the data is set
	bool HasTimeoutMode()const;
	/// Deletes the data
	void DeleteTimeoutMode();

	/// Operator Timeout [seconds]: Defines minimum viewing timeout for operator in seconds
	bool SetOperatorTimeout(const S_UINT16 nSeconds);
	/// @see SetOperatorTimeout
	S_UINT16 GetOperatorTimeout()const;
	/// @see SetOperatorTimeout
	bool HasOperatorTimeout()const;
	/// Deletes the data
	void DeleteOperatorTimeout();

	/// Machine Timeout [seconds]: Defines timeout for machine after bag exit in seconds
	bool SetMachineTimeout(const float nSeconds);
	/// @see SetMachineTimeout
	float GetMachineTimeout()const;
	/// Returns true if the data is set
	bool HasMachineTimeout()const;
	/// Deletes the data
	void DeleteMachineTimeout();

	/// Printer Name
	Array1D<DcsLongString>& GetPrinterNames();
	/// Printer Name
	const Array1D<DcsLongString>& GetPrinterNames()const;
	/// Add a printer name
	bool AddPrinterName(const DcsLongString &strName);
	/// Returns true if the data is set
	bool HasPrinterNames()const;
	/// Deletes the data
	void DeletePrinterNames();

	/// Bar Code Type: Defines type of bar code and reader in use
	bool SetBarCodeType(const DcsShortString &strCode);
	/// @see SetBarCodeType
	DcsString GetBarCodeType()const;
	/// Returns true if the data is set
	bool HasBarCodeType()const;
	/// Deletes the data
	void DeleteBarCodeType();

	/// Scanner IP and Port
	bool SetScannerIPAndPort(const DcsLongString &strIP, const DcsLongString &strPort);
	/// @see SetScannerIPAndPort
	bool AddScannerIPAndPort(const DcsLongString &strIP, const DcsLongString &strPort);
	/// Set Scanner IP and Port pairs. Array formatted as [0]=IP, [1]=Port, [2]=IP, [3]=Port, ...
	bool SetScannerIPAndPort(const Array1D<DcsLongString> &vScanners);
	/// @see SetScannerIPAndPort
	DcsString GetScannerIP()const;
	/// @see SetScannerIPAndPort
	DcsString GetScannerPort()const;
	/// @see SetScannerIPAndPort
	const Array1D<DcsLongString>& GetScannerIPAndPorts()const;
	/// Returns true if the data is set
	bool HasScannerIPAndPort()const;
	/// Deletes the data
	void DeleteScannerIPAndPort();

	/////////////////////////////
	/// SOP Common Module

	/// SOP Instance Creation Date and Time
	/// @param strDate Instance creation date. Default value is DcsDate::Today()
	/// @param strTime Instance creation time. Default value is DcsTime::Now()
	/// @return true/false false if strDate or strTime is not a valid DcsDate or DcsTime
	bool SetSopInstanceCreationDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetSopInstanceCreationDateAndTime
	const DcsDate& GetSopInstanceCreationDate()const;
	/// @see SetSopInstanceCreationDateAndTime
	const DcsTime& GetSopInstanceCreationTime()const;

	/// SOP Instance UID
	/// @param strInstanceUID Unique identifier for the instance. Default value is randomly generated
	/// @return true/false false is strInstanceUID is not a valid DcsUniqueIdentifier
	bool SetSopInstanceUID(const DcsUniqueIdentifier &strInstanceUID);
	/// Auto generate SOP Instance UID
	void GenerateSopInstanceUID();
	/// @see SetSopInstanceUID
	const DcsUniqueIdentifier& GetSopInstanceUID()const;

	/// Location to store the file the DICOS Data was loaded from.
	void SetFilename(const std::string& strFilename);

	/// @return Empty string if data was not loaded from a file
	std::string GetFilename() const;

	////////////////////////////////////////////
	/// Common Instance Reference Module

	/**
	 *  \struct ReferencedSeriesAndInstances
	 *  Represents references to scans from a specific series, identified by the included Series Instance UID
	 *  Each scan scan reference is their SOP Instance UID and SOP Class UID within ReferencedSopInstance
	 */
	struct ReferencedSeriesAndInstances
	{
		DcsUniqueIdentifier	m_strSeriesInstanceUID; ///< Referenced Series Instance UID
		Array1D<ReferencedSopInstance> m_vReferencedInstances; ///< References to scans defined by their SOP Instance UID and SOP Class UID
	};

	/**
	 *  \struct OtherScansReferencedInstances
	 *  Represents references to scans which are related to the scan whose UID is provided
	 *  These related scans themselves contain references to instances referenced within this scan instance
	 *  The references to each of the other scans can be identified by their SOP Instance UID and SOP Class UID within
	 */
	struct OtherScansReferencedInstances
	{
		DcsUniqueIdentifier	m_strScanInstanceUID; ///< Referenced Scan Instance UID
		Array1D<ReferencedSeriesAndInstances> m_vReferencedSeries; ///< References to other scans which contain instances referenced elsewhere in this instance
	};

	/// Get references to other scans using the same Scan Instance UID as this scan
	/// @param vReferencedSeries Vector which will be filled with references to other scans
	void GetReferencedSeries(Array1D<ReferencedSeriesAndInstances>& vReferencedSeries)const;

	/// Get references to other related scans
	/// @param vOtherReferencedScans Vector which will be filled with references to related scans
	void GetOtherReferences(Array1D<OtherScansReferencedInstances>& vOtherReferencedScans)const;


protected:
	class ImplIODCommon;
	
	ImplIODCommon* GetImpl();
	const ImplIODCommon* GetImpl() const;
	
	/// Reset to default values
	void Initialize(const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE nOOIType = ObjectOfInspectionModule::enumUnknownObjectOfInspectionType);
	
	/// Set shared attributes
	bool Read(const ScannerCommon& sc, const GeneralSeriesModule& series, ErrorLog& errorlog);
	
	/// Write shared attribute values
	bool Write(ScannerCommon& sc, GeneralSeriesModule& series, ErrorLog& errorlog) const;
	
private:
	ImplIODCommon * m_pImplIODCommon; ///< Internal implementation
};

/// \class ScanCommon
/// \brief This class contains data that is common to all modalities except TDR
/// 
/// Notes:
///		Provides API for:
///			- General Series Module
///			- TIP
class ScanCommon
{
public:
	/// Constructor
	ScanCommon();
	/// Copy constructor
	ScanCommon(const ScanCommon &sc);
	/// Destructor
	virtual ~ScanCommon();

	/// Copy operator
	ScanCommon& operator=(const ScanCommon &sc);
	/// Comparison operator
	bool operator==(const ScanCommon &sc)const;
	/// Comparison operator
	bool operator!=(const ScanCommon &sc)const;

	/// Reset to default values
	virtual void FreeMemory();

	/// Read values from parameters
	virtual bool Read(const TipImage *ptip, const GeneralSeriesModule &gsm, ErrorLog& errorlog);
	/// Write values to parameters
	virtual bool Write(TipImage *ptip, GeneralSeriesModule &gsm, ErrorLog& errorlog)const;

	////////////////////////////////
	// General Series Module

	/// Test Article Type [optional]
	/// @param nTestArticleType Test Article Type
	/// @return true/false
	bool SetTestArticleType(const GeneralSeriesModule::TEST_ARTICLE_TYPE nTestArticleType);
	/// Get Test Article Type
	/// @return GeneralSeriesModule::TEST_ARTICLE_TYPE
	GeneralSeriesModule::TEST_ARTICLE_TYPE GetTestArticleType() const;
	/// @see SetTestArticleType
	/// @return true/false
	bool HasTestArticleType() const;
	/// Delete data
	void DeleteTestArticleType();
	
	//////////////
	// TIP

	/// Initialize TIP image from module API
	/// @param ptip TIP to initialize from. If NULL, function internally calls DeleteTipImage
	/// @see DeleteTipImage
	void SetTip(const TipImage *ptip);
	/// Get Module API for TIP
	/// @see SetTip
	void GetTip(TipImage &tip)const;

	/// Flag image data as a TIP (Threat Image Projection) FTI image.
	/// FTI: Fictitious Threat Image to be projected onto a scan of an OOI
	void SetTipImageFTI();
	/// Returns true if data is TIP and is an FTI image
	/// @see SetTipImageFTI
	bool IsTipImageFTI()const;
	/// Flag image data as a TIP (Threat Image Projection) CTI image
	/// CTI: Composite Threat Image to be presented
	void SetTipImageCTI();
	/// Returns true if image data is TIP and is a CTI image
	bool IsTipImageCTI()const;

	/// Set TIP Image Library Name
	/// @param strLibraryName - TIP Library Name to be set
	void SetTipLibraryName(DcsShortText strLibraryName);
	/// @see SetTipLibraryName()
	DcsShortText GetTipLibraryName()const;
	/// @see HasTipLibraryName()
	bool HasTipLibraryName()const;
	/// @see hasTipLibraryName()
	void DeleteTipLibraryName();

	/// Set TIP Library Date
	/// @param dtLibraryDate - TIP Library Date to be set
	void SetTipLibraryDate(DcsDateTime dtLibraryDate);
	/// @see SetTipLibraryDate
	DcsDateTime GetTipLibraryDate()const;
	/// @see SetTipLibraryDate
	bool HasTipLibraryDate()const;
	/// @see SetTipLibraryDate
	void DeleteTipLibraryDate();

	/// Set TIP Image Identifier
	/// @param strIdentifier - TIP Image Identifier to be set
	void SetTipImageIdentifier(DcsShortText strIdentifier);
	/// @see SetTipImageIdentifier
	DcsShortText GetTipImageIdentifier()const;
	/// @see SetTipImageIdentifier
	bool HasTipImageIdentifier()const;
	/// @see SetTipimageIdentifier
	void DeleteTipImageIdentifier();

	/// Returns true if image is TIP (FTI or cTI)
	bool IsTipImage()const;
	/// Delete TIP flag
	void DeleteTipImage();
private:
	class ScanCommonImpl;
	ScanCommonImpl	*m_pScanCommonImpl;
};

} // SDICOS

#endif	/* _STRATOVAN_DICOS_TEMPLATE_CLASSES_BASE_H_ */

