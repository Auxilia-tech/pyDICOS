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
#ifndef _STRATOVAN_DICOS_GENERAL_EQUIPMENT_MODULE_H_
#define _STRATOVAN_DICOS_GENERAL_EQUIPMENT_MODULE_H_

#include "SDICOS/Types.h"
#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/ErrorLog.h"

namespace SDICOS
{

class AttributeManager;

///
/// \class GeneralEquipmentModule
/// Implements DICOS General Equipment Module
/// SPECREF V03 Section 14.1.1, Table 84
///
class GeneralEquipmentModule
{
public:
	/// Constructor
	GeneralEquipmentModule();

	/// Destructor
	~GeneralEquipmentModule();

	/// Reset to default values
	void FreeMemory();

	/// Copy Constructor
	GeneralEquipmentModule(const GeneralEquipmentModule &generalequipmentmodule);

	/// Assignment Operator
	GeneralEquipmentModule& operator=(const GeneralEquipmentModule &generalequipmentmodule);

	/// Comparison Operator
	bool operator==(const GeneralEquipmentModule &generalequipmentmodule)const;
	/// Comparison Operator
	bool operator!=(const GeneralEquipmentModule &generalequipmentmodule)const;

	/// Enumeration for Equipment Gantry Type
	typedef enum
	{
		enumUnknownGantryType,	///< Does not match defined terms

		enumRotating,	///< "ROTATING"
		enumStationary, ///< "STATIONARY"

	}GANTRY_TYPE;

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if some attributes failed IsValid()
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Set Manufacturer : Tag (0008, 0070)
	/// @param strManufacturer	Manufacturer : Tag (0008, 0070), VR = LO [required]
	/// @return true/false
	bool SetManufacturer(const DcsLongString &strManufacturer);

	/// @see SetManufacturer
	DcsString GetManufacturer()const;

	///
	/// Set Machine Location : Tag (0008, 0080)
	/// @param strMachineLocation Machine Location : Tag (0008, 0080), VR = LO [required]
	///			-Airport code or location ID
	/// @return true/false
	bool SetMachineLocation(const DcsLongString &strMachineLocation);

	/// @see SetMachineLocation
	DcsString GetMachineLocation()const;

	///
	/// Set Machine Address : Tag (0008, 0081)
	/// @param strMachineAddress Machine Address : Tag (0008, 0081), VR = ST [required]
	///			-Physical address or location ID
	/// @return true/false	false if the DcsShortText object is not valid
	bool SetMachineAddress(const DcsShortText &strMachineAddress);

	/// @see SetMachineAddress
	DcsString GetMachineAddress()const;

	///
	/// Set Machine ID : Tag (0008, 1010)
	/// @param strMachineID Machine ID : Tag (0008, 1010), VR = SH [required]
	/// @return true/false	false if strMachineId is not a valid DcsShortString
	bool SetMachineID(const DcsShortString &strMachineID);
	bool SetMachineID(const Array1D<DcsShortString> &vstrMachineIDs);

	/// @see GetMachineID
	DcsString GetMachineID()const;
	bool GetMachineID(Array1D<DcsShortString> &vstrMachineIDs)const;

	/// Set Machine Sub-Location : Tag (0008, 1040)
	/// @param strMachineSubLocation	Machine Sub-Location : Tag (0008, 1040), VR = LO [optional]
	///			-Sub-location ID (ex. Airport terminal ID)
	bool SetMachineSubLocation(const DcsLongString &strMachineSubLocation);

	/// Remove the Machine Sub-Location attribute.
	/// Type = 3 [optional]
	bool DeleteMachineSubLocation();

	/// @see SetMachineSubLocation
	DcsString GetMachineSubLocation()const;

	/// Set Manufacturer's Model Name : Tag (0008, 1090)
	/// @param strModelName Manufacturer's Model Name : Tag (0008, 1090), VR = LO [required]
	bool SetManufacturerModelName(const DcsLongString &strModelName);

	/// @see SetManufacturerModelName
	DcsString GetManufacturerModelName()const;

	/// Set Device Serial Number : Tag (0018, 1000)
	/// @param strSerialNumber Device Serial Number : Tag (0018, 1000), VR = LO [required]
	bool SetDeviceSerialNumber(const DcsLongString &strSerialNumber);

	/// @see SetDeviceSerialNumber
	DcsString GetDeviceSerialNumber()const;

	/// Set Software Versions : Tag (0018, 1020)
	/// @param arraySoftwareVersions Software Version : Tag (0018, 1020), VR = LO [required]
	///			i) Single tag holds all software version strings (Ex. "Version1\Version2")
	bool SetSoftwareVersions(const Array1D<DcsLongString> &arraySoftwareVersions);

	/// @see SetSoftwareVersions
	bool GetSoftwareVersions(Array1D<DcsString> &arraySoftwareVersions)const;

	/// Same as SetSoftwareVersions(), but for a single version
	bool SetSoftwareVersion(const DcsLongString &strSoftwareVersion);
	/// @see SetSoftwareVersion
	DcsString GetSoftwareVersion()const;

	///
	/// Set Gantry ID : Tag (0018, 1008)
	/// @param strGantryID Gantry ID : Tag (0018, 1008), VR = LO [optional]
	///
	bool SetGantryID(const DcsLongString &strGantryID);

	/// Remove the Gantry ID attribute.
	/// Type is 3 [optional]
	bool DeleteGantryID();

	/// @see SetGantryID
	DcsString GetGantryID()const;

	/// Set Gantry Type : Tag (4010, 1008)
	/// @param nGantryType Gantry Type : Tag (4010, 1008), VR = CS [optional]
	///			i) Values: "ROTATING", "STATIONARY"
	/// @return true/false
	bool SetGantryType(const GANTRY_TYPE nGantryType);

	/// Remove the Gantry Type attribute.
	/// Type is 3 [optional]
	bool DeleteGantryType();

	/// @see SetGantryType
	GANTRY_TYPE GetGantryType()const;

	/// @see SetGantryType
	DcsString GetGantryTypeAsString()const;

	/// Set Spatial Resolution : Tag (0018, 1050)
	/// Spatial Resolution must be > 0.
	/// @param fSpatialResolution Spatial Resolution : Tag (0018, 1050), VR = DS [optional]
	/// @return true/false false is spatial resolution is invalid
	bool SetSpatialResolution(const float fSpatialResolution);

	/// Remove spatial resolution attribute
	/// Type is 3 [optional]
	bool DeleteSpatialResolution();

	/// Get the spatial resolution.
	/// @return spatial resolution or 0 if none has been set
	float GetSpatialResolution()const;

	/// @see GetSpatialResolution
	DcsString GetSpatialResolutionAsString()const;

	/// Set Dates and Times of Last Calibrations
	/// @param arrayDate Calibration Date : Tag (0018, 1200), VR = DA [required]
	///			i) Single tag holds all dates version strings (Ex. "Date1\Date2")
	/// @param arrayTime Calibration Time : Tag (0018, 1201), VR = TM [required]
	///			i) Single tag holds all time strings (Ex. "Time1\Time2")
	///			arrayDate and arrayTime must be equal length
	/// @return true, false if arrays are 0 length or not equal length
	bool SetCalibrationDatesAndTimes(const Array1D<DcsDate> &arrayDate, const Array1D<DcsTime> &arrayTime);

	/// @see SetValibrationDatesAndTimes
	bool GetCalibrationDatesAndTimes(Array1D<DcsDate> &arrayDate, Array1D<DcsTime> &arrayTime)const;

	/// Same as SetCalibrationDatesAndTimes(), but for single date and time
	bool SetCalibrationDateAndTime(const DcsDate &strDate, const DcsTime &strTime);

	/// @see SetCalibrationDateAndTime
	bool GetCalibrationDateAndTime(DcsDate &strDate, DcsTime &strTime)const;

	///
	/// Set Pixel Padding : Tag (0028, 0120)
	/// VR set by "Pixel Representation" (0028, 0103), found in "Image Pixel Macro"
	/// @param nPadding Pixel Padding : Tag (0028, 0120), VR = SS [required if Pixel Padding Range Limit is present]
	///			i) The passed in value is the value used within the data to represent a padded pixel.
	///			Ex. Padding value is "12", all pixels with value "12" are considered padding and not part of the actual image
	bool SetPixelPadding(const S_INT16 nPadding);
	/// @see SetPixelPadding(const S_INT16)
	bool SetPixelPadding(const S_UINT16 nPadding);
	/// @see SetPixelPadding(const S_INT16)
	bool SetPixelPadding(const S_INT32 nPadding);
	/// @see SetPixelPadding(const S_INT16)
	bool SetPixelPadding(const S_UINT32 nPadding);
	/// @see SetPixelPadding(const S_INT16)
	bool SetPixelPadding(const S_INT64 nPadding);
	/// @see SetPixelPadding(const S_INT16)
	bool SetPixelPadding(const S_UINT64 nPadding);
	/// @see SetPixelPadding(const S_INT16)
	bool SetPixelPadding(const float fPadding);

	/// Remove Pixel Padding Value
	/// Type is 1C [conditional required]
	bool DeletePixelPadding();

	/// @see SetPixelPadding(const S_INT16)
	bool GetPixelPadding(S_INT16 &nPadding)const;
	/// @see SetPixelPadding(const S_INT16)
	bool GetPixelPadding(S_UINT16 &nPadding)const;
	/// @see SetPixelPadding(const S_INT16)
	bool GetPixelPadding(S_INT32 &nPadding)const;
	/// @see SetPixelPadding(const S_INT16)
	bool GetPixelPadding(S_UINT32 &nPadding)const;
	/// @see SetPixelPadding(const S_INT16)
	bool GetPixelPadding(S_INT64 &nPadding)const;
	/// @see SetPixelPadding(const S_INT16)
	bool GetPixelPadding(S_UINT64 &nPadding)const;
	/// @see SetPixelPadding(const S_INT16)
	bool GetPixelPadding(float &fPadding)const;

	/// Feed mode enumerataions
	typedef enum
	{
		enumUnknownFeedMode,	///< Does not match defined terms

		enumFeedMode_Manual,	///< "MANUAL"
		enumFeedMode_Automatic,	///< "AUTOMATIC"
		enumFeedMode_Other,		///< "OTHER"
	}FEED_MODE;

	/// Data collection mode enumerations
	typedef enum
	{
		enumInvalidDataCollectionMode,	///< Does not match defined terms

		enumDataCollectionMode_Yes,		///< "YES"
		enumDataCollectionMode_No,		///< "NO"
		enumDataCollectionMode_Unknown,	///< "UNKNOWN"
	}DATA_COLLECTION_MODE;

	/// Operation mode enumerations
	typedef enum
	{
		enumUnknownOperationMode,	///< Does not match defined terms

		enumOperationMode_Scan,		///< "SCAN"
		enumOperationMode_Other,	///< "OTHER"
	}OPERATION_MODE;

	/// Timeout mode enumerations
	typedef enum
	{
		enumUnknownTimeoutMode,		///< Does not match defined terms

		enumTimeoutMode_Operator,	///< "OPERATOR"
		enumTimeoutMode_Machine,	///< "MACHINE"
		enumTimeoutMode_Other,		///< "OTHER"
	}TIMEOUT_MODE;

	/// Hold Mode enumerations
	typedef enum
	{
		enumUnknownHoldMode,/// Does not match defined terms
		enumHoldMode_Yes,	/// "YES"
		enumHoldMode_No,	/// "NO"
	}HOLD_MODE;

	/// Set Cluster ID: Storage Cluster ID of original physical location of OOI
	/// (0x0060, 0x7012) [optional]
	void SetClusterID(const S_UINT16 nVal);
	/// @see SetClusterID
	S_UINT16 GetClusterID()const;
	/// Returns true if the data is set
	bool HasClusterID()const;
	/// Deletes the data
	void DeleteClusterID();

	/// Bag Raw Path: Defines bag raw data location on storage cluster
	/// (0x0060, 0x7014) [optional]
	void SetBagRawPath(const S_INT16 nVal);
	/// @see SetBagRawPath
	S_INT16 GetBagRawPath()const;
	/// Returns true if the data is set
	bool HasBagRawPath()const;
	/// Deletes the data
	void DeleteBagRawPath();

	/// Bag Image Path: Defines bag image data location on storage cluster 
	/// (0x0060, 0x7016) [optional]
	void SetBagImagePath(const S_INT16 nVal);
	/// @see SetBagImagePath
	S_INT16 GetBagImagePath()const;
	/// Returns true if the data is set
	bool HasBagImagePath()const;
	/// Deletes the data
	void DeleteBagImagePath();

	/// Feed Mode: Defines the feed mode in use
	/// (0x0060, 0x7018) [optional]
	bool SetFeedMode(const FEED_MODE nMode);
	/// @see SetFeedMode
	FEED_MODE GetFeedMode()const;
	/// @see SetFeedMode
	DcsString GetFeedModeAsString()const;
	/// Returns true if the data is set
	bool HasFeedMode()const;
	/// Deletes the data
	void DeleteFeedMode();

	/// Data Collection Mode: Defines whether or not raw data is collected
	/// (0x0060, 0x7020) [optional]
	bool SetDataCollectionMode(const DATA_COLLECTION_MODE nMode);
	/// @see SetDataCollectionMode
	DATA_COLLECTION_MODE GetDataCollectionMode()const;
	/// @see SetDataCollectionMode
	DcsString GetDataCollectionModeAsString()const;
	/// Returns true if the data is set
	bool HasDataCollectionMode()const;
	/// Deletes the data
	void DeleteDataCollectionMode();

	/// Hold Mode: Defines whether the the bag is held inside the scanner for more slices
	/// (0x0060, 0x7022) [optional]
	/// @return true/false. False if nMode is invalid
	bool SetHoldMode(const HOLD_MODE nMode);
	/// @see SetHoldMode
	HOLD_MODE GetHoldMode()const;
	/// @see SetHoldMode
	DcsString GetHoldModeAsString()const;
	/// Returns true if the data is set
	bool HasHoldMode()const;
	/// Deletes the data
	void DeleteHoldMode();

	/// Operation Mode: Define the operation mode of the bag
	/// (0x0060, 0x7024) [optional]
	bool SetOperationMode(const OPERATION_MODE nMode);
	/// @see SetOperationMode
	OPERATION_MODE GetOperationMode()const;
	/// @see SetOperationMode
	DcsString GetOperationModeAsString()const;
	/// Returns true if the data is set
	bool HasOperationMode()const;
	/// Deletes the data
	void DeleteOperationMode();

	/// Show Mode: Identifies the mode controlling on-screen display
	/// (0x0060, 0x7026) [optional]
	bool SetShowMode(const DcsLongString &dsMode);
	/// @see SetShowMode
	DcsLongString GetShowMode()const;
	/// Returns true if the data is set
	bool HasShowMode()const;
	/// Deletes the data
	void DeleteShowMode();

	/// TimeoutMode: Defines the conditions for a timeout
	/// (0x0060, 0x7028) [optional]
	bool SetTimeoutMode(const TIMEOUT_MODE nMode);
	/// @see SetTimeoutMode
	TIMEOUT_MODE GetTimeoutMode()const;
	/// @see SetTimeoutMode
	DcsString GetTimeoutModeAsString()const;
	/// Returns true if the data is set
	bool HasTimeoutMode()const;
	/// Deletes the data
	void DeleteTimeoutMode();

	/// Operator Timeout [seconds]: Defines minimum viewing timeout for operator in seconds
	/// (0x0060, 0x7030) [optional]
	bool SetOperatorTimeout(const S_UINT16 nSeconds);
	/// @see SetOperatorTimeout
	S_UINT16 GetOperatorTimeout()const;
	/// @see SetOperatorTimeout
	bool HasOperatorTimeout()const;
	/// Deletes the data
	void DeleteOperatorTimeout();

	/// Machine Timeout [seconds]: Defines timeout for machine after bag exit in seconds
	/// (0x0060, 0x7032) [optional]
	/// @param fSeconds Machine timeout in seconds. Must be >= 0.0f
	/// @return true/false false if fSeconds < 0.0f
	bool SetMachineTimeout(const float fSeconds);
	/// @see SetMachineTimeout
	float GetMachineTimeout()const;
	/// Returns true if the data is set
	bool HasMachineTimeout()const;
	/// Deletes the data
	void DeleteMachineTimeout();

	/// Printer Name
	/// (0x0060, 0x7034) [optional]
	bool SetPrinterName(const DcsLongString &strName);
	/// @see SetPrinterName
	bool SetPrinterNames(const Array1D<DcsLongString> &vstrNames);
	/// @see SetPrinterName
	bool AddPrinterName(const DcsLongString &strName);
	/// @see SetPrinterName
	DcsString GetPrinterName()const;
	/// @see SetPrinterName
	const Array1D<DcsLongString>& GetPrinterNames()const;
	/// Returns true if the data is set
	bool HasPrinterName()const;
	/// Deletes the data
	void DeletePrinterName();

	/// Bar Code Type: Defines type of bar code and reader in use
	/// (0x0060, 0x7036) [optional]
	bool SetBarCodeType(const DcsLongString &strCode);
	/// @see SetBarCodeType
	DcsLongString GetBarCodeType()const;
	/// Returns true if the data is set
	bool HasBarCodeType()const;
	/// Deletes the data
	void DeleteBarCodeType();

	/// Scanner IP and Port
	/// (0x0060, 0x7038) [optional] IP:Port/IP:Port/...
	bool SetScannerIPAndPort(const DcsLongString &strIP, const DcsLongString &strPort);
	/// @see SetScannerIPAndPort
	bool AddScannerIPAndPort(const DcsLongString &strIP, const DcsLongString &strPort);
	/// Set Scanner IP and Port pairs. Array formatted as [0]=IP:Port, [1]=IP:Poprt, ...
	bool SetScannerIPAndPort(const Array1D<DcsLongString> &vScanners);
	/// @see SetScannerIPAndPort
	DcsString GetScannerIP()const;
	/// @see SetScannerIPAndPort
	DcsString GetScannerPort()const;
	/// @see SetScannerIPAndPort
	/// @return "IP:Port"
	DcsString GetScannerIPAndPort()const;
	/// @see SetScannerIPAndPort
	const Array1D<DcsLongString>& GetScannerIPAndPorts()const;
	/// Returns true if the data is set
	bool HasScannerIPAndPort()const;
	/// Deletes the data
	void DeleteScannerIPAndPort();

protected:
	class	ImplGeneralEquipment;
	ImplGeneralEquipment	*m_pImplGeneralEquipment;

	const ImplGeneralEquipment* GetImpl() const;
	ImplGeneralEquipment* GetImpl();
};

}//namespace SDICOS

#endif
