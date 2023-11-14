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
#ifndef _STRATOVAN_DICOS_OBJECT_OF_INSPECTION_OWNER_MODULE_H_
#define _STRATOVAN_DICOS_OBJECT_OF_INSPECTION_OWNER_MODULE_H_

#include "SDICOS/PersonIdentificationMacro.h"
#include "SDICOS/DicosCodeDefinitions.h"
#include "SDICOS/Utils.h"

namespace SDICOS
{
	/// Identify the Object Of Inspection owner
	class OwnerIdentification
	{
	public:
		OwnerIdentification();
		OwnerIdentification(const OwnerIdentification&);
		virtual ~OwnerIdentification();

		OwnerIdentification& operator=(const OwnerIdentification& rhs);

		bool operator==(const OwnerIdentification& rhs)const;
		bool operator!=(const OwnerIdentification& rhs)const;

		/// Set Owner Identification
		/// @param issuingOrg Identification Issuer
		/// @param idValue Identification Value
		/// @param ownersName Owner's name
		/// @return true/falwse
		bool SetIdentification(const DcsShortString& issuingOrg, const DcsShortString& idValue, const DcsLongString& ownersName);

		/// Set Identification Issuer
		/// @param issuingOrg Identification Issuer
		/// @return true/false
		bool SetIssuingOrg(const DcsShortString& issuingOrg);
		DcsShortString GetIssuingOrg() const;

		/// Set Owner's Id Value
		/// @param idValue Id Value
		/// @return true/false
		bool SetId(const DcsShortString& idValue);
		/// @see SetId
		DcsShortString GetId() const;

		/// Set Owner's Name
		/// @param ownersName Owner's Name 
		/// @return true/false
		bool SetName(const DcsLongString& ownersName);
		/// @see SetName
		DcsShortString GetName() const;

	private:
		class OwnerIdentificationImpl; ///< Internal Implementation
		OwnerIdentificationImpl* m_pOwnerIdentificationImpl; ///< Internal Implementation
	};

///
/// \class OOIOwnerIdentificationMacro
/// 
/// OOIOwnerIdentificationMacro implements an interface to set requirements for the 
/// person identification attributes of the OOI Owner if the owner is a person.
/// See "Composite IOD Modules Overview"
/// SPECREF V03 Section 2.3.3, Table 11
/// and see "Insert Person Identification Macro"
/// SPECREF V03 Section 14.13, Table 110
/// and see "Context Group UID Values"
/// SPECREF V03 Section 17.4, Table 137
///
class OOIOwnerIdentificationMacro : public PersonIdentificationMacro 
{
public:
	OOIOwnerIdentificationMacro();
	OOIOwnerIdentificationMacro(const OOIOwnerIdentificationMacro&);
	virtual ~OOIOwnerIdentificationMacro();
	
	OOIOwnerIdentificationMacro& operator=(const OOIOwnerIdentificationMacro&);
	bool operator==(const OOIOwnerIdentificationMacro&) const;
	
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
	
	typedef enum
	{
		enumUnknownGender = 0,	///< Does not match defined terms

		enumMale,				///< "MALE"
		enumFemale,				///< "FEMALE"
		enumOther,				///< "OTHER"
		enumUnknown				///< "UNKNOWN"

	}PERSON_GENDER;

	///
	/// Set person's identifying information
	/// @param issuingOrg Organization issuing the Id
	/// @param idValue Value of the Id (e.g. DL number, passport, barcode, rfid etc)
	/// @param personsFullName Owners name that is set as the 'Code Meaning' for 'Identification Code Sequence' (0x0040, 0x1101)
	/// @return true/false false if any strings are invalid
	///
	bool SetPrimaryIdentification(const DcsShortString& issuingOrg, const DcsShortString& idValue, const DcsLongString& personsFullName);
	
	/// @see SetPrimaryIdentificatioin
	/// @return a CodeSequence pointer that is meant for immediate usage.
	bool GetPrimaryIdentification(CodeSequence&) const;
	
	/// @see SetPrimaryIdentificatioin
	/// @return a CodeSequence pointer that is meant for immediate usage only.
	const CodeSequence* GetPrimaryIdentification() const;
	
	/// @see SetPrimaryidenfication
	bool AddAlias(const DcsShortString& issuingOrg, const DcsShortString& idValue, const DcsLongString& personsFullName);

	/// @see SetPrimaryidenfication
	bool GetAlias(const S_UINT32 aliasIndex, OwnerIdentification& ownerAlias) const;

	/// @see SetPrimaryidenfication
	bool RemoveAlias(const S_UINT32 aliasIndex);

	/// @see SetPrimaryidenfication
	S_UINT32 GetNumAliases() const;

	///
	/// Set the ID Type indicating the type of id set by SetPrimaryIdentifcation.
	/// This adds a Person Identification Code to the Identification Code Sequence(0x0040 0x1101) 
	///		'CodeValue' = integer code for DICOS Code Definition
	///		'CodeMeaning' = string value for DICOS Code Definition
	///		'Scheme Designator' = "DICOS"
	///		'Scheme Version' = "01"
	///
	/// @param codeDefinition Code Definition for Id Type
	/// @return true/false
	///
	bool SetIDType(const CodeDefinitions::DICOS_CODE_DEFINITION codeDefinition);
	
	/// @see SetIDType
	bool GetIDType(CodeSequence&) const;
	
	/// @see SetIDType
	/// @return a CodeSequence pointer that is meant for immediate usage only.
	const CodeSequence* GetIDType() const;
	
	///
	/// Add an item to the Person Identification indicating the country of residence
	///		'Code Value' = country code according to ISO 3166-1-alpha-2
	///		'Code Meaning' = "Country of Residence"
	///		'Scheme Designator = "ISO 3166-1"
	///		'Scheme Version' = "alpha-2"
	/// @param countryCode	2 Letter country code
	/// @param fullCountryName Optional Full name of the country
	/// @return true/false
	///
	bool SetCountryOfResidence(const DcsShortString& countryCode, const DcsString& fullCountryName = Utils::EmptyCharString);
	
	/// @see SetCountryOfResidence
	bool GetCountryOfResidence(CodeSequence&) const;
	
	///
	/// Add an item to the Person Identification indicating the country of citizenship
	///		'Code Value' = country code according to ISO 3166-1-alpha-2
	///		'Code Meaning' = "Country of Citizenship"
	///		'Scheme Designator = "ISO 3166-1"
	///		'Scheme Version' = "alpha-2"
	/// @param countryCode	2 Letter country code
	/// @param fullCountryName Optional Full name of the country
	/// @return true/false
	///
	bool SetCountryOfCitizenship(const DcsShortString& countryCode, const DcsString& fullCountryName = Utils::EmptyCharString);
	
	/// @see SetCountryOfCitizenship
	bool GetCountryOfCitizenship(CodeSequence&) const;
	
	/// Add an item to the Person Identification indicating the person's gender
	///		'Code Value' = M/F/O/U
	///		'Code Meaning' = MALE/FEMALE/OTHER/UNKNOWN
	///		'Scheme Designator' = "DICOS"
	/// @param gender Person's Gender
	/// @return true/false
	///
	bool SetGender(const PERSON_GENDER gender);
	
	/// @see SetGender
	bool GetGender(CodeSequence&) const;

	/// @see SetGender
	PERSON_GENDER GetGender() const;
private:

	/// Hidden so the setting identification data goes through high-level API
	virtual bool SetIdentificationCodeSequence(const Array1D<CodeSequence> &) { return false; }

	/// Hidden so the setting identification data goes through high-level API
	virtual bool AddIdentificationCodeSequence(const CodeSequence& personIdCode);
	
	bool CheckPersonId(const AttributeManager &attribManager, ErrorLog &errorlog) const;
};

///
/// \class ObjectOfInspectionOwnerModule
///
/// Object of Inspection Owner
/// SPECREF V03 Section 3.1, Table 12
/// OOI Owner Module (Single Item Sequence) : Tag (4010, 1047), VR = SQ [required]
///	-The ObjectOfInspectionOwnerModule class is the only item in the sequence
///
class ObjectOfInspectionOwnerModule
{
public:
	///
	/// Default constructor
	///
	ObjectOfInspectionOwnerModule();
	
	/// Destructor
	~ObjectOfInspectionOwnerModule();
	
	///
	/// Copy constructor
	///
	ObjectOfInspectionOwnerModule(const ObjectOfInspectionOwnerModule &objectofinspectionownermodule);

	///
	/// Assignment operator
	///
	ObjectOfInspectionOwnerModule& operator=(const ObjectOfInspectionOwnerModule &objectofinspectionownermodule);
	
	///
	/// Comparison operator
	///
	bool operator==(const ObjectOfInspectionOwnerModule &objectofinspectionownermodule)const;

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
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

	/// Reset all data structures
	void FreeMemory();
	
	///
	/// Object's owner types
	///
	typedef enum
	{
		enumUnknownOwnerType = 0,	///< Does not match defined terms

		enumPerson,					///< "PERSON"
		enumBusiness,				///< "BUSINESS"
		enumEntity,					///< "ENTITY"
		enumOther,					///< "OTHER"
		enumUnknown					///< "UNKNOWN"

	}OWNER_TYPE;

	///
	/// Transport classification types
	///
	typedef enum
	{
		enumUnknownTransportClassificationType = 0, ///< Does not match defined terms

		enumHazmat,		///< "HAZMAT"
		enumWeapons,	///< "WEAPONS"
		enumMedical,	///< "MEDICAL"
		enumCommercial,	///< "COMMERCIAL"
		enumPersonal,	///< "PERSONAL"
		enumGovernment,	///< "GOVERNMENT"

	}TRANSPORT_CLASSIFICATION_TYPE;

	///
	/// Set the Owner Type
	///	@param nType Owner Type : Tag (4010, 1009), VR = CS [Code String] [required]
	///			i) Values: "PERSON", "BUSINESS", "ENTITY", "OTHER", "UNKNOWN"
	/// @return true/false false if owner type is invalid
	///
	bool SetOwnerType(const OWNER_TYPE nType);

	///
	/// @see SetOwnerType
	///
	OWNER_TYPE GetOwnerType()const;
	
	/// @see SetOwnerType
	/// @return "" is Owner Type if not valid
	DcsString GetOwnerTypeAsString()const;

	/// Set the OOI Owner Risk Score : Tag (4010, 1022)
	/// @param nRiskScore OOI Owner Risk Score  : Tag (4010, 1022), VR = SS [Signed Short] [optional]
	void SetOwnerRiskScore(S_INT16 nRiskScore);
	/// Returns the OOI owner risk score
	/// @return If present risk score, otherwise returns 0
	/// @see SetOwnerRiskScore
	/// @see HasOwnerRiskScore
	S_INT16 GetOwnerRiskScore()const;
	/// @return true/false if risk score is present
	/// @see SetOwnerRiskScore
	bool HasOwnerRiskScore()const;
	/// Delete the risk score
	void DeleteOwnerRiskScore();

	///
	/// Set Owner Identification for OWNER_TYPE == PERSON 
	/// requires specific items added to "Person Identification Code Sequence" (0040, 1101) in "PersonIdentificationMacro"
	/// @param piOwnerIdentification Owner Identification information
	/// @return true/false false if piOwnerIdentification is not properly filled out
	///
	bool SetOwnerIdentification(const OOIOwnerIdentificationMacro &piOwnerIdentification);

	/// @see SetOwnerIdentification
	bool GetOwnerIdentification(OOIOwnerIdentificationMacro &piOwnerIdentification)const;
	/// @see SetOwnerIdentification
	OOIOwnerIdentificationMacro& GetOwnerIdentification();
	/// @see SetOwnerIdentification
	const OOIOwnerIdentificationMacro& GetOwnerIdentification() const;

	///
	/// Set Owner Creation Time : Tag (4010, 1041)
	///	@param strDateTime Creation Date and Time : Tag (4010, 1041), VR = DT [optional]
	/// @return true/false
	///
	bool SetCreationTime(const DcsDateTime &strDateTime);

	/// @see SetCreationTime
	DcsDateTime GetCreationTime()const;

	/// Remove creation time so that it is not written to the DICOS file
	bool DeleteCreationTime();
	
	/// Valid creation time has been set
	/// @return true/false
	bool HasCreationTime() const;

	///
	/// Set Owner Identity Removed : Tag (0012, 0062)
	///	@param bIdentityRemoved Identity removal flag : Tag (0012, 0062), VR = CS [required]
	///			i) Values: "YES" = true, "NO" = false.
	/// @return true/false false if identity removed flag could not be set
	///
	bool SetIdentityRemoved(const bool bIdentityRemoved);

	/// @see SetIdentityRemoved
	bool IsIdentityRemoved()const;
	
	/// @see SetIdentityRemoved
	DcsString IsIdentityRemovedAsString()const;

	///
	/// Set Owner De-identification Method
	///	@param arrayMethods De-identification method : Tag (0012, 0063), VR = LO [required if "Owner Identity Removed" is "YES" and "De-identification Method Code Sequence" is not set]
	///			i) Values stored in same tag (Ex. "method1\method2\method3")
	/// @return true/false false if De-identification strings are not formatted correctly
	///
	bool SetDeIdentificationMethod(const Array1D<DcsLongString> &arrayMethods);
	
	/// @see SetDeIdentificationMethods
	bool GetDeIdentificationMethod(Array1D<DcsString> &arrayMethods)const;

	/// Remove de-identification methods so they are not included in DICOS file
	bool DeleteDeIdentificationMethod();
	
	/// @see SetDeIdentificationMethods
	const Array1D<DcsLongString>& GetDeIdentificationMethod() const;
	
	///
	/// Set De-identification Method Code Sequence : Tag (0012, 0064), VR = SQ [required if "Owner Identity Removed" is "YES" and "Owner De-identification Method" is not present]
	///	@param arrayDeIdentificationMethods De-identification Methods
	///			i) Context ID not defined
	/// @return true/false false if De-identification method CodeSequences are not formatted correctly
	///
	bool SetDeIdentificationMethod(const Array1D<CodeSequence> &arrayDeIdentificationMethods);

	/// @see SetDeIdentificationMethod
	bool GetDeIdentificationMethod(Array1D<CodeSequence> &arrayDeIdentificationMethods)const;

	/// Remove de-identification methods so they are not included in DICOS file
	bool DeleteDeIdentificationMethodCodeSequence();
	
	///
	/// Set Transport Classification : Tag (4010, 1067)
	///	@param nType Transport Classification Type : Tag (4010, 1067), VR = CS [required]
	///			i) Values: "HAZMAT", "WEAPONS", "MEDICAL", "COMMERCIAL", "PERSONAL", "GOVERNMENT"
	/// @return true/false false if Transport Classification Type could not be set
	///
	bool SetTransportClassificationType(const TRANSPORT_CLASSIFICATION_TYPE nType);

	/// @see SetTransportClassificationType
	TRANSPORT_CLASSIFICATION_TYPE GetTransportClassificationType()const;
	
	/// @see SetTransportClassificationType
	DcsString GetTransportClassificationTypeAsString()const;

protected:

	class ImplObjectOfInspectionOwner;
	mutable ImplObjectOfInspectionOwner	*m_pImplObjectOfInspectionOwner; ///< Internal implementation
	
	ImplObjectOfInspectionOwner* GetImpl();
	const ImplObjectOfInspectionOwner* GetImpl() const;
};

}//namespace SDICOS

#endif
