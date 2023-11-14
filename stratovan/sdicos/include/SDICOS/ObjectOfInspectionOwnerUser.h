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
#ifndef _STRATOVAN_DICOS_OBJECT_OF_INSPECTION_OWNER_USER_H_
#define _STRATOVAN_DICOS_OBJECT_OF_INSPECTION_OWNER_USER_H_

#include "SDICOS/ObjectOfInspectionOwnerModule.h"

namespace SDICOS
{
	///
	/// \class ObjectOfInspectionOwnerUser
	///
	/// Implements Object of Inspection Owner for the User API
	///
	class ObjectOfInspectionOwnerUser
	{
	public:
		///
		/// Default constructor
		///
		ObjectOfInspectionOwnerUser();

		/// Destructor
		~ObjectOfInspectionOwnerUser();

		///
		/// Copy constructor
		///
		ObjectOfInspectionOwnerUser(const ObjectOfInspectionOwnerUser& objectofinspectionownermodule);

		///
		/// Assignment operator
		///
		ObjectOfInspectionOwnerUser& operator=(const ObjectOfInspectionOwnerUser& objectofinspectionownermodule);

		///
		/// Comparison operator
		///
		bool operator==(const ObjectOfInspectionOwnerUser& objectofinspectionownermodule)const;

		/// Read from the give ObjectOfInspectionOwnerModule
		/// @param rhs ObjectOfInspectionOwnerModule
		/// @param el ErrorLog
		/// @return true/false
		bool Read(const ObjectOfInspectionOwnerModule& rhs, ErrorLog& el);

		/// Write to the give ObjectOfInspectionOwnerModule
		/// @param lhs ObjectOfInspectionOwnerModule
		/// @param el ErrorLog
		/// @return true/false
		bool Write(ObjectOfInspectionOwnerModule& lhs, ErrorLog& el) const;

		/// Reset all data structures
		void FreeMemory();

		///
		/// Set the Owner Type
		///	@param nType Owner Type 
		/// @return true/false false if owner type is invalid
		///
		bool SetOwnerType(const ObjectOfInspectionOwnerModule::OWNER_TYPE nType);

		/// @see SetOwnerType
		ObjectOfInspectionOwnerModule::OWNER_TYPE GetOwnerType()const;

		/// @see SetOwnerType
		/// @return Empty string for invalid Owner Type
		DcsString GetOwnerTypeAsString()const;

		/// Set the OOI Owner Risk Score
		/// @param nRiskScore OOI Owner Risk Score : [optional]
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
		/// Set Owner Identification
		/// Set owner's identifying information
		/// @param issuingOrg Organization issuing the Id
		/// @param idValue Value of the Id (e.g. DL number, passport, barcode, rfid etc)
		/// @param personsFullName Owners name 
		/// @return true/false false if any strings are invalid
		///
		bool SetPrimaryIdentification(const DcsShortString& issuingOrg, const DcsShortString& idValue, const DcsLongString& personsFullName);

		/// @see SetPrimaryIdentificatioin
		/// @return a CodeSequence pointer that is meant for immediate usage.
		bool GetPrimaryIdentification(OwnerIdentification&) const;

		/// @see SetPrimaryidenfication
		bool AddAlias(const DcsShortString& issuingOrg, const DcsShortString& idValue, const DcsLongString& personsFullName);
		
		/// Get the indicated alias
		/// @param aliasIndex Alias index
		/// @param ownerAlias Alias information
		/// @return true/false
		bool GetAlias(const S_UINT32 aliasIndex, OwnerIdentification& ownerAlias) const;

		/// Remove indicated alias
		/// @param aliasIndex Alias index
		/// @return true/false
		bool RemoveAlias(const S_UINT32 aliasIndex);

		/// Get number of aliases
		/// @return Number of added indentifications
		S_UINT32 GetNumAliases() const;

		///
		/// Set the ID Type indicating the type of id set by SetPrimaryIdentifcation.
		/// @param idType Code Definition for Id Type
		/// @return true/false
		///
		bool SetIDType(const CodeDefinitions::DICOS_CODE_DEFINITION idType);

		/// @see SetIDType
		CodeDefinitions::DICOS_CODE_DEFINITION GetIDType() const;

		///
		/// Indicate the owner's country of residence
		/// @param countryCode	2 Letter country code
		/// @param fullCountryName Optional Full name of the country
		/// @return true/false
		///
		bool SetCountryOfResidence(const DcsShortString& countryCode, const DcsString& fullCountryName = Utils::EmptyCharString);

		/// @see SetCountryOfResidence
		bool GetCountryOfResidence(DcsShortString& countryCode, DcsString& fullCountryName) const;

		///
		/// Add an item to the Person Identification indicating the country of citizenship
		/// @param countryCode	2 Letter country code
		/// @param fullCountryName Optional Full name of the country
		/// @return true/false
		///
		bool SetCountryOfCitizenship(const DcsShortString& countryCode, const DcsString& fullCountryName = Utils::EmptyCharString);

		/// @see SetCountryOfCitizenship
		bool GetCountryOfCitizenship(DcsShortString& countryCode, DcsString& fullCountryName) const;

		///
		/// Indicate owner's gender for Owner Type "PERSON".
		/// @param gender Person's Gender
		/// @return true/false
		///
		bool SetOwnerGender(const OOIOwnerIdentificationMacro::PERSON_GENDER gender);

		/// @see SetOwnerGender
		OOIOwnerIdentificationMacro::PERSON_GENDER GetOwnerGender() const;

		///
		/// Set the Owners's Address
		/// @param strAddress Owners's Address Physical or email address
		/// @return true/false false if the address is not a valid DcsShortText
		///
		bool SetAddress(const DcsShortText& strAddress);

		/// @see SetPersonAddress
		DcsString GetAddress()const;

		///
		/// Set the Person's Telephone Numbers
		/// Invalid phone numbers will not be set
		/// @param arrayPhoneNumbers  Person's Telephone Numbers : [optional]
		/// @return true/false false if one or more phone numbers was invalid
		///
		bool SetPhoneNumbers(const Array1D<DcsLongString>& arrayPhoneNumbers);

		/// @see SetPersonPhoneNumbers
		bool GetPhoneNumbers(Array1D<DcsString>& arrayPhoneNumbers)const;

		///
		/// Set Organization Name for Owner
		/// @param strOrganizationName Organization Name
		/// @return true/false false if the organization name string is invalid
		///
		bool SetOrganizationName(const DcsLongString& strOrganizationName);

		/// @see SetOrganizationName
		DcsString GetOrganizationName()const;

		///
		/// Set Organization's Address 
		/// @param strOrganizationAddress Organization's Address : [optional]
		/// @return true/false false if the mailing address is not a valid short text string
		///
		bool SetOrganizationAddress(const DcsShortText& strOrganizationAddress);

		/// @see SetOrganizationAddress
		DcsString GetOrganizationAddress()const;

		///
		/// Set Owner Creation Time 
		///	@param strDateTime Creation Date and Time : [optional]
		/// @return true/false
		///
		bool SetCreationTime(const DcsDateTime& strDateTime);

		/// @see SetCreationTime
		DcsDateTime GetCreationTime()const;

		/// Remove creation time so that it is not written to the DICOS file
		bool DeleteCreationTime();

		/// Creation time has been set
		/// @return true/false
		bool HasCreationTime() const;

		///
		/// Set Owner Identity Removed 
		///	@param bIdentityRemoved Identity removal flag : [required]
		/// @return true/false false if identity removed flag could not be set
		///
		bool SetIdentityRemoved(const bool bIdentityRemoved);

		/// @see SetIdentityRemoved
		bool IsIdentityRemoved()const;

		///
		/// Set Owner De-identification Method
		/// 
		///	@param arrayMethods	De-identification methods : [required if "Owner Identity Removed" is "YES" (@see SetIdentityRemoved())
		/// and "De-identification Method Code Sequence" is not set (@see SetDeIdentificationMethod())]
		///			i) Values stored in same tag (Ex. "method1\method2\method3")
		/// 
		/// @return true/false false if De-identification strings are not formatted correctly
		///
		bool SetDeIdentificationMethod(const Array1D<DcsLongString>& arrayMethods);

		/// @see SetDeIdentificationMethods
		bool GetDeIdentificationMethod(Array1D<DcsString>& arrayMethods)const;

		/// Remove de-identification methods so they are not included in DICOS file
		bool DeleteDeIdentificationMethod();

		/// @see SetDeIdentificationMethods
		const Array1D<DcsLongString>& GetDeIdentificationMethod() const;

		///
		/// Set Transport Classification 
		///	@param nType Transport Classification Type
		///			i) Values: "HAZMAT", "WEAPONS", "MEDICAL", "COMMERCIAL", "PERSONAL", "GOVERNMENT"
		/// @return true/false false if Transport Classification Type could not be set
		///
		bool SetTransportClassificationType(const ObjectOfInspectionOwnerModule::TRANSPORT_CLASSIFICATION_TYPE nType);

		/// @see SetTransportClassificationType
		ObjectOfInspectionOwnerModule::TRANSPORT_CLASSIFICATION_TYPE GetTransportClassificationType()const;

		/// @see SetTransportClassificationType
		DcsString GetTransportClassificationTypeAsString()const;

	private:

		class ImplObjectOfInspectionOwner;
		mutable ImplObjectOfInspectionOwner* m_pImplObjectOfInspectionOwner; ///< Internal implementation

		ImplObjectOfInspectionOwner* GetImpl();
		const ImplObjectOfInspectionOwner* GetImpl() const;
	};

}//namespace SDICOS

#endif

