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
#ifndef _STRATOVAN_DICOS_SOP_COMMON_MODULE_H_
#define _STRATOVAN_DICOS_SOP_COMMON_MODULE_H_

#include <list>

#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/CodeSequence.h"
#include "SDICOS/PurposeOfReferenceCode.h"

namespace SDICOS
{

///
/// \class SopCommonModule
///
/// The SDICOS::SopCommonModule class implements the SOP Common Module
/// SPECREF V03 Section 14.4, Table 96
///
class SopCommonModule
{
public:
	/// Default Constructor
	SopCommonModule();
	
	/// Copy Constructor
	SopCommonModule(const SopCommonModule &sopcommonmodule);

	/// Destructor
	virtual ~SopCommonModule();

	/// Reset to default values
	void FreeMemory();
	
	/// Assignment operator
	SopCommonModule& operator=(const SopCommonModule &sopcommonmodule);
	
	/// Comparison operator
	bool operator==(const SopCommonModule &sopcommonmodule)const;
	
	/// Comparison operator
	bool operator!=(const SopCommonModule &sopcommonmodule)const;

	/// Initialize the class attributes from the given AttributeManager.
	/// The AttributeManager contains the attributes for a SOP Common Module
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Move the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false is returned if attributes were specified or if some were invalid.
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	///
	/// Enumeration for DICOS Version used to create the IOD
	///
	typedef enum
	{
		enumUnknownDicosVersion, ///< Unknown DICOS Version

		enumVersion2,	///< "V02"
		enumVersion2A,	///< "V02A"
		enumVersion3,	///< "V03"

		enumCurrentVersion = enumVersion3, ///< Default to Version 3

	}DICOS_VERSION;

	///
	/// Enumeration for DICOS SOP Instance Status
	///
	typedef enum
	{
		enumUnknownSopInstanceStatus, ///< Unknown status. Optional attribute is not written to DICOS file

		enumNotSpecified,		///< "NS" Not specified
		enumOriginal,			///< "OR" Original
		enumAuthorizedOriginal,	///< "AO" Authorized Original
		enumAuthorizedCopy,		///< "AC" Authorized Copy

	}SOP_INSTANCE_STATUS;

	///
	/// \class ContributingEquipment
	/// The SDICOS::SopCommonModule::ContributingEquipment class implements
	/// the Contributing Equipment Sequence Attribute : Tag (0018, A001) of the SOP Common Module
	/// DICOS Specification Section 12.4.1.3
	///
	class ContributingEquipment
	{
	public:
		/// Default Constructor
		ContributingEquipment();
		
		/// Copy Constructor
		ContributingEquipment(const ContributingEquipment &contributingequipment);

		/// Destructor
		~ContributingEquipment();
		
		/// Assignment operator
		ContributingEquipment& operator=(const ContributingEquipment &contributingequipment);
		
		/// Comparison operator
		bool operator==(const ContributingEquipment &contributingequipment)const;

		/// Initialize the class attributes from the given AttributeManager.
		/// The AttributeManager contains the attributes for a Contributing Equipment Sequence it does not contain 
		///	the Tag (0018, A001) for the actual sequence attribute.
		///
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not fetched
		///							or if some were invalid.
		bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Move the attributes from the module into the given AttributeManager
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not uploaded.
		bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Attempt to set all required and optional attributes from the given AttributeManager
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false is returned if attributes were specified or if some were invalid.
		bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Determine if all needed attributes (required and conditionally required) are set
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Check that all attributes are in the correct format;
		bool IsValid() const;
		
		///
		/// Set Purpose of Reference Code Sequence (Single Item Sequence) : Tag (0040, A170), VR = SQ [required]
		///	@param csPurposeOfReference Purpose of Reference Code Sequence \n
		///		i) Context ID = 7005 \n
		///		ii) Code Scheme Designator = DCM
		/// @return true/false false if csPurposeOfReference is not valid
		///
		bool SetPurposeOfReference(const PurposeOfReferenceContributingEquipment &csPurposeOfReference);

		///
		/// Get Purpose of Reference Code Sequence
		/// @see SetPurposeOfReference
		/// @return true/false false if csPurposeOfReference is not valid
		///
		bool GetPurposeOfReference(CodeSequence &csPurposeOfReference)const;

		/// @see SetPurposeOfReference
		const CodeSequence& GetPurposeOfReference() const;
		///
		/// Set Manufacturer : Tag (0008, 0070) VR = LO [required]
		/// @param strManufacturer String describing manufacturer
		/// @return true/false false if strManufacturer is not a valid DcsLongString
		///
		bool SetManufacturer(const DcsLongString &strManufacturer);

		/// Get manufacturer string
		/// @see SetManufacturer
		DcsString GetManufacturer()const;

		///
		/// Set Machine Location : Tag (0008, 0080) VR = LO [optional]
		/// @param strMachineLocation Machine location string \n
		///			- Airport code or location ID
		/// @return true/false false if strMachineLocation is not a valid DcsLongString
		///
		bool SetMachineLocation(const DcsLongString &strMachineLocation);

		/// Get Machine Location
		/// @see SetMachineLocation
		DcsString GetMachineLocation()const;
		
		/// 
		/// Set the Machine Location to an empty string to indicate that
		/// the optional attribute is not specified.
		///
		bool DeleteMachineLocation();

		///
		/// Set Machine Address : Tag (0008, 0081), VR = ST [required (type 2), can be NULL]
		/// @param strMachineAddress Machine Address String \n
		///							 - Physical address of location ID
		/// @return true/false false strMachineAddress is not a valid DcsShortText
		///
		bool SetMachineAddress(const DcsShortText &strMachineAddress);

		///
		/// Get the Machine Address string
		/// @see SetMachineAddress(const DcsShortText)
		/// @return Machine Address string
		///
		DcsString GetMachineAddress()const;

		///
		/// Set Machine ID : Tag (0008, 1010), VR = SH [required]
		/// @param strMachineID Machine ID String
		/// @return true/false false if strMachineID is not a valid DcsShortString
		///
		bool SetMachineID(const DcsShortString &strMachineID);

		/// Get Machine ID
		/// @see SetMachineID(const DcsShortString)
		DcsString GetMachineID()const;

		///
		/// Set Machine Sub-Location : Tag (0008, 1040)
		///	@param strMachineSubLocation Machine Sub-Location : Tag (0008, 1040), VR = LO [optional] \n
		///								 -Sub-location ID (ex. Airport terminal ID)
		/// @return true/false false if strMachineSubLocation is not a valid strMachineSubLocation
		///
		bool SetMachineSubLocation(const DcsLongString &strMachineSubLocation);

		/// Get Machine Sub Location
		/// @see SetMachineSubLocation
		DcsString GetMachineSubLocation()const;

		/// 
		/// Set the Machine SubLocation to an empty string to indicate that
		/// the optional attribute is not specified.
		/// 
		bool DeleteMachineSubLocation();
		
		///
		/// Set Manufacturer's Model Name : Tag (0008, 1090)
		/// @param strModelName Manufacturer's Model Name : Tag (0008, 1090), VR = LO [optional]
		/// @return true/false false if strModelName is not a valid DcsLongString
		///
		bool SetManufacturerModelName(const DcsLongString &strModelName);

		/// @see SetManufacturerModelName
		DcsString GetManufacturerModelName()const;

		/// 
		/// Set the Manufacturer Model Name to an empty string to indicate that
		/// the optional attribute is not specified.
		/// 
		bool DeleteManufacturerModelName();
		
		///
		/// Set Device Serial Number : Tag (0018, 1000)
		/// @param strSerialNumber Device Serial Number : Tag (0018, 1000), VR = LO [optional]
		/// @return true/false false if strSerialNumber is not a valid DcsLongString
		///
		bool SetDeviceSerialNumber(const DcsLongString &strSerialNumber);

		/// @see SetDeviceSerialNumber
		DcsString GetDeviceSerialNumber()const;
		
		/// 
		/// Set the Device Serial Number to an empty string to indicate that
		/// the optional attribute is not specified.
		/// 
		bool DeleteDeviceSerialNumber();
		
		///
		/// Set Software Versions : Tag (0018, 1020)
		///	@param arraySoftwareVersions Software Version : Tag (0018, 1020), VR = LO [optional] \n
		///			i) Single tag holds all software version strings (Ex. "Version1\Version2")
		/// @return true/false false if arraySoftwareVersions contains invalid DcsLongString objects
		///
		bool SetSoftwareVersions(const Array1D<DcsLongString> &arraySoftwareVersions);

		/// @see SetSoftwareVersions
		bool GetSoftwareVersions(Array1D<DcsString> &arraySoftwareVersions)const;

		/// @see SetSoftwareVersions
		const Array1D<DcsLongString>& GetSoftwareVersions() const;
		
		/// 
		/// Set the Device Serial Number to an empty string to indicate that
		/// the optional attribute is not specified.
		/// 
		bool DeleteSoftwareVersions();
		
		///
		/// Set Spatial Resolution : Tag (0018, 1050)
		///	@param fSpatialResolution Spatial Resolution : Tag (0018, 1050), VR = DS [optional]
		/// @return true/false false if fSpatialResolution is invalid
		///
		bool SetSpatialResolution(const float fSpatialResolution);

		/// @see SetSpatialResolution
		float GetSpatialResolution()const;

		/// @see SetSpatialResolution
		DcsString GetSpatialResolutionAsString()const;

		/// 
		/// Set the Spatial Resolution to 0.0 to indicate 
		/// that the optional attribute is not specified.
		/// 
		bool DeleteSpatialResolution();
		
		///
		/// Set Dates and Times of Last Calibrations. Date and time arrays must be equal length
		///	@param arrayDate Calibration Date : Tag (0018, 1200), VR = DA [optional] \n
		///			i) Single tag holds all dates version strings (Ex. "Date1\Date2")
		///	@param arrayTime Calibration Time : Tag (0018, 1201), VR = TM [optional] \n
		///			i) Single tag holds all time strings (Ex. "Time1\Time2")
		/// @return true/false false if arrayDate or arrayTime contain invalid DcsDate and DcsTime objects respectively
		///						of if different numbers of dates and times are specified
		///
		bool SetCalibrationDatesAndTimes(const Array1D<DcsDate> &arrayDate, const Array1D<DcsTime> &arrayTime);

		/// @see SetCalibrationDatesAndTimes
		bool GetCalibrationDatesAndTimes(Array1D<DcsDate> &arrayDate, Array1D<DcsTime> &arrayTime)const;

		/// @see SetCalibrationDatesAndTimes
		const Array1D<DcsDate>& GetCalibrationDates() const;
		
		/// @see SetCalibrationDatesAndTimes
		const Array1D<DcsTime>& GetCalibrationTimes() const;
		
		/// 
		/// Clear the Dates and Times to indicate 
		/// that the optional attributes are not specified.
		/// 
		bool DeleteCalibrationDatesAndTimes();
		
		///
		/// Set Contribution Date and Time : Tag (0018, A002), VR = DT [optional]
		///	@param strDateTime Contribution Date and Time
		/// @return true/false false if strDateTime is not a valid DcsDateTime
		///
		bool SetContributionDateAndTime(const DcsDateTime &strDateTime);

		/// @see SetContributionDateAndTime
		DcsDateTime GetContributionDateAndTime()const;

		///
		/// Clear the Contribution Date and Time to indicate
		/// that the optional attribute is not specified
		///
		bool DeleteContributionDateAndTime();
		
		///
		/// Set Contribution Description : Tag (0018, A003)
		/// @param strDescription Contribution Description : Tag (0018, A003), VR = ST [optional]
		/// @return true/false false if strDescription is not a valid DcsShortText
		///
		bool SetContributionDescription(const DcsShortText &strDescription);

		/// @see SetContributionDescription
		DcsShortText GetContributionDescription()const;

		///
		/// Clear the Contribution Description to indicate
		/// that the optional attribute is not specified
		///
		bool DeleteContributionDescription();
		
	private:
		class ImplContributingEquipment;
		ImplContributingEquipment	*m_pImplContributingEquipment; ///< Internal implementation
		
		ImplContributingEquipment* GetImpl();
		const ImplContributingEquipment* GetImpl() const;
	};

	///
	/// \class OriginalAttribute
	/// The SDICOS::SopCommonModule::OriginalAttribute class implements an Attribute
	/// for the "Original Attributes Sequence" Attribute : Tag (0400, 0561) of the SOP Common Module
	///
	class OriginalAttribute
	{
	public:
		/// Default Constructor
		OriginalAttribute();
		
		/// Copy Constructor
		OriginalAttribute(const OriginalAttribute &originalattribute);

		/// Destructor
		~OriginalAttribute();
		
		/// Assignment operator
		OriginalAttribute& operator=(const OriginalAttribute &originalattribute);
		
		/// Comparison operator
		bool operator==(const OriginalAttribute &originalattribute)const;

		///
		/// Initialize the class attributes from the given AttributeManager.
		/// The AttributeManager contains the attributes for an Original Attributes Sequence it does not contain 
		///	the Tag (0400, 0561) for the actual sequence attribute.
		///
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not fetched
		///							or if some were invalid.
		bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Move the attributes from the module into the given AttributeManager
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not uploaded.
		bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Attempt to set all required and optional attributes from the given AttributeManager
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false is returned if attributes were specified or if some were invalid.
		bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Determine if all needed attributes (required and conditionally required) are set
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Determine if all set attributes have valid values.
		bool IsValid() const;
		///
		/// Enumeration for "Reason For the Attribute Modification" Attribute
		///
		typedef enum
		{
			enumUnknownAttributeModificationReason, ///< Unknown Modification Reason

			enumCoerce,		///< "COERCE" - Replace values
			enumCorrect,	///< "CORRECT"	- Replace incorrect values

		}ATTRIBUTE_MODIFICATION_REASON;

		///
		/// \typedef std::list<Tag> TagPath
		///
		typedef std::list<Tag> TagPath;
		
		///
		/// \struct ModifiedAttributeData
		///
		typedef struct
		{
			TagPath m_TagPath;	///< Sequence of Tags from root to Attribute
			
			/// Pointer to the original attribute information. 
			/// This must be allocated on the heap and ownership will be handled 
			/// by the OriginalAttribute module.
			const AttributeCommon * m_OriginalAttribute; 
			
		} ModifiedAttributeData;
		
		///
		/// \typedef std::list<ModifiedAttributeData> ModifiedAttributeList
		///
		typedef std::list<ModifiedAttributeData> ModifiedAttributeList;
		
		///
		/// Set the Source of Previous Values : Tag (0400, 0564)
		/// @param strPreviousValuesSource Source of Previous Values : Tag (0400, 0564), VR = CS [required (type 2), can be NULL]
		/// @return true/false false if strPreviousValuesSource is not a valid DcsCodeString
		///
		bool SetPreviousValuesSource(const DcsCodeString &strPreviousValuesSource);		

		/// @see SetPreviousValuesSource
		DcsString GetPreviousValuesSource()const;

		///
		/// Set Attribute Modification Date & Time : Tag (0400, 0562), VR = DT [required]
		/// @param strDateTime Attribute Modification Date and Time
		/// @return true/false false if strDateTime is not a valid DcsDateTime
		///
		bool SetAttributeModificationDateAndTime(const DcsDateTime &strDateTime);	

		/// @see SetAttributeModificationDateAndTime
		/// @return Date and Time as a string
		DcsDateTime GetAttributeModificationDateAndTime()const;	

		///
		/// Set the Modifying System : Tag (0400, 0563)
		///	@param strModifyingSystem Modifying System : Tag (0400, 0563), VR = LO [required]
		/// @return true/false false if strModifyingSystem is not a valid DcsLongString
		///
		bool SetModifyingSystem(const DcsLongString &strModifyingSystem);			

		/// @see SetModifyingSystem
		DcsString GetModifyingSystem()const;

		///
		/// Set Attribute Modification Reason : Tag (0400, 0565)
		///	@param nReason Attribute Modification Reason : Tag (0400, 0565), VR = CS. Values: "COERCE", "CORRECT" [required]
		/// @return true/false
		///
		bool SetAttributeModificationReason(const ATTRIBUTE_MODIFICATION_REASON nReason);

		/// @see SetAttributeModificationReason
		ATTRIBUTE_MODIFICATION_REASON GetAttributeModificationReason()const;

		/// @see SetAttributeModificationReason
		DcsString GetAttributeModificationReasonAsString()const;
		
		///
		/// Set Modified Attributes Sequence : Tag (0400, 0550), VR = SQ [required]
		/// Memory allocated for the ModifiedAttributeData is controlled by the
		/// OriginalAttribute module. The caller should not reuse this memory.
		///
		///	@param modifiedAttributes Data for original attributes that were modified
		/// @return true/false
		///
		bool SetModifiedAttributes(const ModifiedAttributeList& modifiedAttributes);

		///
		/// Add a single modified attribute
		/// Memory allocated for the ModifiedAttributeData is controlled by the
		/// OriginalAttribute module. The caller should not reuse this memory.
		///
		/// @param modifiedAttribute	Data for the modified attribute
		/// @return true/false
		///
		bool AddModifiedAttribute(const ModifiedAttributeData& modifiedAttribute);
		
		/// @see AddModifiedAttribute(const ModifiedAttributeData& modifiedAttribute)
		bool AddModifiedAttribute(const TagPath &tagHierarchy, const AttributeCommon* attribute);

		/// @see SetModifiedAttributes
		/// @return true/false false if there are no modified attributes
		bool GetModifiedAttributes(ModifiedAttributeList& modifiedAttributes)const;
		
		/// Remove modified attributes so that they are not written to the file.
		bool DeleteModifiedAttributes();
	private:
		class ImplOriginalAttribute;
		ImplOriginalAttribute	*m_pImplOriginalAttribute; ///< Internal implementation
		
		ImplOriginalAttribute* GetImpl();
		const ImplOriginalAttribute* GetImpl() const;
	};
	
	///
	/// Set SOP Class UID : Tag (0008, 0016)
	///	@param strClassUID SOP Class UID : Tag (0008, 0016), VR = UI [required]
	/// @return true/false false if strClassUID is not a valid DcsUniqueIdentifier
	///
	virtual bool SetSopClassUID(const DcsUniqueIdentifier &strClassUID);

	/// @see SetSopClassUID
	DcsString GetSopClassUID()const;

	///
	/// Set SOP Instance UID : Tag (0008, 0018)
	///	@param strInstanceUID SOP Instance UID : Tag (0008, 0018), VR = UI [required]
	/// @return true/false false if strInstanceUID is not a valid DcsUniqueIdentifier
	///
	bool SetSopInstanceUID(const DcsUniqueIdentifier &strInstanceUID);

	/// @see SetSopInstanceUID
	DcsString GetSopInstanceUID()const;

	typedef enum
	{
		enumUnknownCharacterSets = 0,

		// Single byte sets without code extensions
		enumNone,				///<"" Default Repetoire (ISO-IR 6). Not written to DICOS File
		
		enumISO_IR_100,			///< "ISO_IR 100"	Latin alphabet 1
		enumISO_IR_101,			///< "ISO_IR 101"	Latin alphabet 2
		enumISO_IR_109,			///< "ISO_IR 109"	Latin alphabet 3
		enumISO_IR_110,			///< "ISO_IR 110"	Latin alphabet 4
		enumISO_IR_148,			///< "ISO_IR 148"	Latin alphabet 5
		enumISO_IR_144,			///< "ISO_IR 144"	Cyrillic
		enumISO_IR_127,			///< "ISO_IR 127"	Arabic
		enumISO_IR_126,			///< "ISO_IR 126"	Greek
		enumISO_IR_138,			///< "ISO_IR 138"	Hebrew
		enumISO_IR_13,			///< "ISO_IR 13"	Japanese
		enumISO_IR_166,			///< "ISO_IR 166"	Thai

		// Single byte sets with code extensions
		enumISO_2022_IR_6,		///< "ISO 2022 IR 6"	Default Repetoire	[Escape Sequence (ISO 646):							"ESC 02/08 04/02"]
		enumISO_2022_IR_100,	///< "ISO 2022 IR 100"	Latin alphabet 1 	[Escape Sequence (Supplementary set of ISO 8859): 	"ESC 02/13 04/01", Escape Sequence (ISO 646): "ESC 02/08 04/02"]
		enumISO_2022_IR_101,	///< "ISO 2022 IR 101"	Latin alphabet 2 	[Escape Sequence (Supplementary set of ISO 8859): 	"ESC 02/13 04/02", Escape Sequence (ISO 646): "ESC 02/08 04/02"]
		enumISO_2022_IR_109,	///< "ISO 2022 IR 109"	Latin alphabet 3 	[Escape Sequence (Supplementary set of ISO 8859): 	"ESC 02/13 04/03", Escape Sequence (ISO 646): "ESC 02/08 04/02"]
		enumISO_2022_IR_110,	///< "ISO 2022 IR 110"	Latin alphabet 4 	[Escape Sequence (Supplementary set of ISO 8859): 	"ESC 02/13 04/04", Escape Sequence (ISO 646): "ESC 02/08 04/02"]
		enumISO_2022_IR_148,	///< "ISO 2022 IR 148"	Latin alphabet 5 	[Escape Sequence (Supplementary set of ISO 8859): 	"ESC 02/13 04/13", Escape Sequence (ISO 646): "ESC 02/08 04/02"]
		enumISO_2022_IR_144,	///< "ISO 2022 IR 144"	Cyrillic			[Escape Sequence (Supplementary set of ISO 8859): 	"ESC 02/13 04/12", Escape Sequence (ISO 646): "ESC 02/08 04/02"]
		enumISO_2022_IR_127,	///< "ISO 2022 IR 127"	Arabic				[Escape Sequence (Supplementary set of ISO 8859): 	"ESC 02/13 04/07", Escape Sequence (ISO 646): "ESC 02/08 04/02"]
		enumISO_2022_IR_126,	///< "ISO 2022 IR 126"	Greek				[Escape Sequence (Supplementary set of ISO 8859): 	"ESC 02/13 04/06", Escape Sequence (ISO 646): "ESC 02/08 04/02"]
		enumISO_2022_IR_138,	///< "ISO 2022 IR 138"	Hebrew				[Escape Sequence (Supplementary set of ISO 8859): 	"ESC 02/13 04/08", Escape Sequence (ISO 646): "ESC 02/08 04/02"]
		enumISO_2022_IR_13,		///< "ISO 2022 IR 13"	Japanese			[Escape Sequence (JIS X 0201: Katakana):			"ESC 02/09 04/10", Escape Sequence (JIS X 0201: Romaji): "ESC 02/08 04/10"]
		enumISO_2022_IR_166,	///< "ISO 2022 IR 166"	Thai				[Escape Sequence (TIS 620-2533 (1990)):				"ESC 02/13 05/04", Escape Sequence (ISO 646): "ESC 02/08 04/02"]

		// Multi-byte sets with code extensions
		enumISO_2022_IR_87,		///< "ISO 2022 IR 87"	Japanese	[Escape Sequence (JIS X 0208: Kanji):					"ESC 02/04 04/02"]
		enumISO_2022_IR_159,	///< "ISO 2022 IR 159"	Japanese	[Escape Sequence (JIS X 0212: Supplementary Kanji Set): "ESC 02/04 02/08 04/04"]
		enumISO_2022_IR_149,	///< "ISO 2022 IR 166"	Korean		[Escape Sequence (KS X: Hangul and Hanja):				"ESC 02/04 02/09 04/03"]

		enumNumCharacterSets		///< Constant 
	}CHARACTER_SETS;

	///
	/// Specific Character Set : Tag (0008, 0005)
	/// @param charSets Specific Character Set : Tag (0008, 0005), VR = CS [required if used]
	/// @return true/false
	///
	bool SetSopSpecificCharacterSet(const Array1D<CHARACTER_SETS> &charSets);
	
	/// @see SetSopSpecificCharacterSet
	bool GetSopSpecificCharacterSet(Array1D<CHARACTER_SETS> &charSets) const;

	/// Get the character sets as DcsCodeString objects
	bool GetSopSpecificCharacterSet(Array1D<DcsCodeString> &charSets) const;
	
	/// @see SetSopSpecificCharacterSet
	const Array1D<DcsCodeString>& GetSopSpecificCharacterSet() const;
	
	/// 
	/// Delete mandatory conditional so that it is not written to the DICOS file
	///
	bool DeleteSopSpecificCharacterSet();
	
	///
	/// Set SOP Instance Creation Date and Time
	///	@param strDate Instance Creation Date : Tag (0008, 0012), VR = DA [required]
	/// @param strTime Instance Creation Time : Tag (0008, 0013), VR = TM [required]
	/// @return true/false false if strDate or strTime is not a valid DcsDate or DcsTime
	///
	bool SetSopInstanceCreationDateAndTime(const DcsDate &strDate, const DcsTime &strTime);

	/// @see SetSopInstanceCreationDateAndTime
	DcsDate GetSopInstanceCreationDate()const;

	/// @see SetSopInstanceCreationDateAndTime
	DcsTime GetSopInstanceCreationTime()const;

	///
	/// Set SOP Instance Creator ID : Tag (0008, 0014)
	/// @param strInstanceCreatorID Instance Creator UID : Tag (0008, 0014), VR = UI [optional]
	/// @return true/false false if strInstanceCreatorID is not a valid DcsUniqueIdentifier
	///
	bool SetSopInstanceCreatorID(const DcsUniqueIdentifier &strInstanceCreatorID);

	/// @see SetSopInstanceCreatorID
	DcsString GetSopInstanceCreatorID()const;

	/// Delete optional attribute Instance Creator ID
	bool DeleteSopInstanceCreatorID();
	
	///
	/// Set Related General SOP Class UID
	///	@param strRelatedSopClassUID Related General SOP Class UID : Tag (0008, 001A), VR = UI [optional]
	/// @return true/false false if strRelatedSopClassUID is not a valid DcsUniqueIdentifier
	///
	bool SetRelatedSopClassUID(const DcsUniqueIdentifier &strRelatedSopClassUID);

	/// @see SetRelatedSopClassUID
	DcsString GetRelatedSopClassUID()const;

	/// Delete optional attribute Relate General SOP Class UID
	bool DeleteRelatedSopClassUID();
	
	///
	/// Set Original Specialized SOP Class UID : Tag (0008, 001B)
	///	@param strClassUID Original Specialized SOP Class UID : Tag (0008, 001B), VR = UI [optional]
	/// @return true/false false if strClassUID is not a valid DcsUniqueIdentifier
	///
	bool SetOriginalSpecializedSopClassUID(const DcsUniqueIdentifier &strClassUID);

	/// @see SetOriginalSpecializedSopClassUID
	DcsString GetOriginalSpecializedSopClassUID()const;

	/// Delete optional attribute Original Specialized SOP Class UID
	bool DeleteOriginalSpecializedSopClassUID();
	
	///
	/// Explicitly set the DICOS_VERSION
	/// Default value is "V03". Value is forced to V03 during GetAttributes() since this module only supports V03, but 
	/// will not change the value returned by GetDicosVersion() or GetDicosVersionAsString()
	/// @param version Dicos Version : Tag (4010, 103A), VR = CS. Values "V01", "V02", "V02A", "V03" [required]
	/// @return true/false false if an invalid version is specified
	///
	bool SetDicosVersion(const DICOS_VERSION version);
	
	///
	/// GetDicos Version : Tag (4010, 103A)
	///	-Internally set to "V03"
	///
	DICOS_VERSION GetDicosVersion()const;
	
	/// @see GetDicosVersion
	DcsString GetDicosVersionAsString()const;

	///
	/// Set Time Zone Offset From UTC : Tag (0008, 0201)
	///	@param nOffsetSecondsFromUTC Time Zone Offset in Seconds From UTC : Tag (0008, 0201), VR = SH [optional]
	/// @return true/false false if the offset exceeds one day
	///
	bool SetSopTimeZoneOffsetFromUTC(const S_INT32 nOffsetSecondsFromUTC);

	/// @see SetSopTimeZoneOffsetFromUTC
	S_INT32 GetSopTimeZoneOffsetFromUTC()const;

	/// Get offset in seconds as a string.
	/// @return DcsString The format is +/-HHMM
	DcsString GetSopTimeZoneOffsetFromUTCAsString()const;

	/// Delete optional attribute Timezone Offset from UTC
	bool DeleteSopTimeZoneOffset();
	
	///
	/// Set Contributing Equipment Sequence : Tag (0018, A001), VR = SQ [optional]
	/// @param arrayEquipment ContributingEquipment objects
	/// @return true/false false if arrayEquipment contains invalid ContributingEquipment objects
	///
	bool SetContributingEquipment(const Array1D<ContributingEquipment> &arrayEquipment);

	/// @see SetContributingEquipment
	bool GetContributingEquipment(Array1D<ContributingEquipment> &arrayEquipment)const;

	/// @see SetContributingEquipment
	const Array1D<ContributingEquipment>& GetContributingEquipment() const;
	
	/// Delete optional attribute Contributing Equipment Sequence
	bool DeleteContributingEquipment();
	
	///
	/// Set SOP Instance Status : Tag (0100, 0410)
	/// @param nStatus SOP Instance Status : Tag (0100, 0410), VR = CS [optional] \n
	///			i) Values: "NS" = Not Specified, "OR" = Original, "AO" = Authorized Original, "AC" = Authorized Copy
	/// @return true/false false if an invalid status is specified
	///
	bool SetSopInstanceStatus(const SOP_INSTANCE_STATUS nStatus);

	/// @see SetSopInstanceStatus
	SOP_INSTANCE_STATUS GetSopInstanceStatus()const;

	/// @see SetSopInstanceStatus
	DcsString GetSopInstanceStatusAsString()const;

	/// Delete optional attribute instance status so that it is not written to the DICOS file
	bool DeleteSopInstanceStatus();
	
	///
	/// Set Original Attributes Sequence : Tag (0400, 0561), VR = SQ [optional]
	///	@param arrayAttributes -Indicates removed/replaced attribute. \n
	///							An item within a sequence includes all the parent sequences
	/// @return true/false
	///
	bool SetModifiedAttributes(const Array1D<OriginalAttribute> &arrayAttributes);

	/// @see SetModifiedAttributes
	/// @return true/false
	bool GetModifiedAttributes(Array1D<OriginalAttribute> &arrayAttributes) const;
	
	/// @see SetModifiedAttributes
	const Array1D<OriginalAttribute>& GetModifiedAttributes()const;

	/// Delete optional attribute Original Attributes Sequence
	bool DeleteModifiedAttributes();
	
private:
	class ImplSopCommonModule;
	ImplSopCommonModule	*m_pImplSopCommonModule; ///< Internal implementation
	
	ImplSopCommonModule* GetImpl();
	const ImplSopCommonModule* GetImpl() const;
};

}// namespace SDICOS

#endif
