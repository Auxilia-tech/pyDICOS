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
#ifndef _STRATOVAN_DICOS_PERSON_IDENTIFICATION_MACRO_H_
#define _STRATOVAN_DICOS_PERSON_IDENTIFICATION_MACRO_H_

#include <ostream>
#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/CodeSequence.h"

namespace SDICOS
{

///
/// \class PersonIdentificationMacro
/// Person Identification Macro
/// SPECREF V03 Section 14.13, Table 110
///
class PersonIdentificationMacro
{
public:
	/// Default constructor
	PersonIdentificationMacro();
	
	/// Copy Constructor
	PersonIdentificationMacro(const PersonIdentificationMacro &personidentificationmacro);

	/// Destructor
	virtual ~PersonIdentificationMacro();
	
	/// Assignment Operator
	PersonIdentificationMacro& operator=(const PersonIdentificationMacro &personidentificationmacro);

	/// Comparison Operator
	bool operator==(const PersonIdentificationMacro &personidentificationmacro)const;
	
	/// Comparison Operator
	bool operator!=(const PersonIdentificationMacro &personidentificationmacro)const;

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
	
	/// Reset data structures to default values
	virtual void FreeMemory();
	
	///
	/// Set the Person identification codes. This erases all existing codes
	/// @param arrayPersonIdCodes Person Identification Code Sequence : Tag (0040, 1101), VR = SQ [required]	-Context ID not defined
	/// @return true/false false if one or more CodeSequence objects is invalid
	///
	virtual bool SetIdentificationCodeSequence(const Array1D<CodeSequence> &arrayPersonIdCodes);
	
	/// 
	/// Add a person identification code
	/// @param personIdCode Person Identification Code Sequence
	/// @return true/false false if the CodeSequence is invalid
	///
	virtual bool AddIdentificationCodeSequence(const CodeSequence& personIdCode);
	
	/// @see SetIdentificationCodeSequence
	virtual bool GetIdentificationCodeSequence(Array1D<CodeSequence> &arrayPersonIdCodes)const;
	
	/// @see SetIdentificationCodeSequence
	bool RemoveIdentification(const S_UINT32 identificationIndex);

	/// @see SetIdentificationCodeSequence
	S_UINT32 GetNumberOfIdentifications() const;

	///
	/// Set the Person's Address : Tag (0040, 1102)
	/// @param strAddress Person's Address : Tag (0040, 1102), VR = ST [optional]
	///						i) Physical or email address
	/// @return true/false false if the address is not a valid DcsShortText
	///
	bool SetPersonAddress(const DcsShortText& strAddress);

	/// @see SetPersonAddress
	DcsString GetPersonAddress()const;
	
	///
	/// Set the Person's Telephone Numbers : Tag (0040, 1103)
	/// Invalid phone numbers will not be set
	/// @param arrayPhoneNumbers  Person's Telephone Numbers : Tag (0040, 1103), VR = LO [optional]
	/// @return true/false false if one or more phone numbers was invalid
	///
	bool SetPersonPhoneNumbers(const Array1D<DcsLongString> &arrayPhoneNumbers);
	
	/// @see SetPersonPhoneNumbers
	bool GetPersonPhoneNumbers(Array1D<DcsString> &arrayPhoneNumbers)const;

	/// @see SetPersonPhoneNumbers
	const Array1D<DcsLongString>& GetPersonPhoneNumbers() const;
	
	///
	/// Set Organization Name for Person : Tag (0008, 0080)
	/// @param strOrganizationName Organization Name : Tag (0008, 0080), VR = LO 
	///								[required if "Organization Code Sequence" (0008, 0082) is not set], found in Person Identification Macro]
	/// @return true/false false if the organization name string is invalid
	///
	bool SetOrganizationName(const DcsLongString& strOrganizationName);
	
	/// @see SetOrganizationName
	DcsString GetOrganizationName()const;
	
	///
	/// Set Organization's Address : Tag (0008, 0081)
	/// -Organization accountable for person
	/// @param strOrganizationAddress Organization's Address : Tag (0008, 0081), VR = ST [optional]
	/// @return true/false false if the mailing address is not a valid short text string
	///
	bool SetOrganizationAddress(const DcsShortText& strOrganizationAddress);
	
	/// @see SetOrganizationAddress
	DcsString GetOrganizationAddress()const;

	///
	/// Set the Organization Code Sequence (Single Item Sequence) : Tag (0008, 0082), VR = SQ [required if "Organization Name" (0008, 0080) is not set]
	///	-Organization accountable for person
	///	-Context ID not defined
	/// @param csOrganization CodeSequence with organization information
	/// @return true/false false if organization code sequence is invalid
	/// 
	bool SetOrganization(const CodeSequence &csOrganization);
	
	/// @see SetOrganization
	bool GetOrganization(CodeSequence &csOrganization)const;

	/// @see SetOrganization
	const CodeSequence& GetOrganization() const;
	
protected:
	/// Preallocate space for a specific number of ids in the 'Person Identification Code Sequence'
	PersonIdentificationMacro(const unsigned int numIds);
	
	/// Add an identification Code Sequence to a specific position in the Attribute Sequence
	bool SetIdentificationCodeSequence(const unsigned int index, const CodeSequence& s);

	/// Get a pointer to a code sequence or NULL
	CodeSequence* GetIdentificationCodeSequence(const unsigned int index);
	
	/// Get a pointer to a code sequence or NULL
	const CodeSequence* GetIdentificationCodeSequence(const unsigned int index) const;
	
	typedef std::vector<CodeSequence> PersonIdList;
	
	const PersonIdList& GetIdentifications() const;
	PersonIdList& GetIdentifications();
	
	class ImplPersonIdentificationMacro;
	ImplPersonIdentificationMacro	*m_pImplPersonIdentificationMacro; ///< Internal implementation
	
	ImplPersonIdentificationMacro* GetImpl();
	const ImplPersonIdentificationMacro* GetImpl() const;
};

}//namespace SDICOS

#endif