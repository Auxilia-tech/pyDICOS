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
#ifndef _STRATOVAN_DICOS_CODESEQUENCE_H_
#define _STRATOVAN_DICOS_CODESEQUENCE_H_

#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/ErrorLog.h"

namespace SDICOS
{

///
/// \class CodeSequenceCommon
///
/// Common tags between the Code Sequence and Extended Code Sequence Macros.
/// The Code Value/Extended Code Value and Code Meaning/Extended Code Meaning attributes
/// are implemented in derived classes.
///
/// SPECREF V03 Section 14.11.8, Table 108
/// SPECREF V03 Section 14.12, Table 109
///
class CodeSequenceCommon
{
public:
	/// Default Constructor
	CodeSequenceCommon();

	/// Destructor
	virtual ~CodeSequenceCommon();

	/// Copy Constructor
	CodeSequenceCommon(const CodeSequenceCommon &codesequencecommon);

	/// Assignment operator
	CodeSequenceCommon& operator=(const CodeSequenceCommon &codesequencecommon);

	/// Comparison operator
	bool operator==(const CodeSequenceCommon &codesequencecommon)const;
	/// Comparison operator
	bool operator!=(const CodeSequenceCommon &codesequencecommon)const;

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

	/// Determine if all attributes are properly set
	/// @return true/false
	virtual bool IsValid() const;

	/// Free the memory allocated for CodeSequenceCommon
	virtual void FreeMemory();
	
	/// Determine if all required fields in the CodeSequence are empty strings
	/// @return true/false true if all required strings are empty
	virtual bool Empty() const;
	
	/// Enumeration for Context Group Extension Flag
	typedef enum
	{
		enumUnknownContextGroupExtensionFlag,	///< Does not match defined terms

		enumNo,		///< "N"
		enumYes,	///< "Y"
	}CONTEXT_GROUP_EXTENSION_FLAG;

	/// Set Code Scheme Designator : Tag (0008, 0102)
	/// @param strSchemeDesignator	Tag (0008, 0102), VR = SH [required]
	/// @return true/false	false if strSchemeDesignator is not a valid DcsShortString
	virtual bool SetSchemeDesignator(const DcsShortString &strSchemeDesignator);

	/// @see SetSchemeDesignator
	DcsString GetSchemeDesignator()const;

	/// Code Version : Tag(0008, 0103)
	/// @param strCodeVersion Code Version Tag(0008, 0103), VR = SH [optional]
	/// @return true/false	false if strCodeVersion is not a valid DcsShortString
	bool SetCodeVersion(const DcsShortString &strCodeVersion);

	/// @see SetCodeVersion
	DcsString GetCodeVersion()const;

	/// Context Identifier : Tag (0008, 010F)
	/// @param strContextID Context ID Tag(0008, 010F), VR = CS [optional]
	/// @return true/false false if strContextID is not a valid DcsCodeString
	virtual bool SetContextID(const DcsCodeString &strContextID);

	/// @see SetContextID
	DcsString GetContextID()const;

	/// Clear the Context ID Attribute
	bool DeleteContextID();

	/// Mapping Resource : Tag (0008, 0105), VR = CS
	///	@param strMappingResource Tag (0008, 0105), VR = CS [required if "Context Identifier" is set]
	///		i) Defined values: "DCMR"
	bool SetMappingResource(const DcsCodeString &strMappingResource);

	/// @see SetMappingResource
	DcsString GetMappingResource()const;

	/// Context Group Version : Tag (0008, 0106), VR = DT
	///	@param strContextGroupVersion	Tag (0008, 0106), VR = DT [required if "Context Identifier" is set]
	///		i) The parameter is a version number in DateTime format and not a date and time
	bool SetContextGroupVersion(const DcsDateTime &strContextGroupVersion);

	/// @see SetContextGroupVersion
	DcsDateTime GetContextGroupVersion()const;						

	/// Set the ContextID, Mapping Resource and Context Group Version
	/// Convenience method to set optional Context ID and conditionally required Mapping Resource and Context Group Version
	/// The parameters are set only if all are valid strings of the given type.
	/// @param strContextID	 		Tag (0008, 010F), VR = CS
	/// @param strMappingResource	Tag (0008, 0105), VR = CS
	/// @param strVersion			Tag (0008, 0106), VR = DT
	/// @return true/false false if any of parameters are invalid
	bool SetContextInfo(const DcsCodeString &strContextID, const DcsCodeString &strMappingResource, const DcsDateTime &strVersion);

	/// Context Group Extension Flag : Tag (0008, 010B), VR = CS
	///	@param nContextGroupExtensionFlag	Tag (0008, 010B), VR = CS [optional]
	///		i) Values : "Y", "N"
	/// @return true/false	false if invalid enum value is passed
	bool SetContextGroupExtensionFlag(const CONTEXT_GROUP_EXTENSION_FLAG nContextGroupExtensionFlag);

	/// @see SetContextGroupExtensionFlag
	CONTEXT_GROUP_EXTENSION_FLAG GetContextGroupExtensionFlag()const;	

	/// Get the extension flag as a DcsString.
	/// @return "Y", "N" or "" if the extension flag is enumUnknownContextGroupExtensionFlag
	DcsString GetContextGroupExtensionFlagAsString()const;	

	/// Context Group Local Version : Tag (0008, 0107)
	///	@param strContextGroupLocalVersion	Tag (0008, 0107), VR = DT [required if "Context Group Extension Flag" is "Y"]
	///		i) The parameter is a version number and not a date and time
	/// @return	true/false	false if strContextGroupLocalVersion is not a valid DcsDateTime string
	bool SetContextGroupLocalVersion(const DcsDateTime strContextGroupLocalVersion);

	/// @see SetContextGroupLocalVersion
	DcsDateTime GetContextGroupLocalVersion()const;				

	/// Context Group Extension Creator UID : Tag (0008, 010D)
	///	@param strContextGroupExtensionCreatorUID	Tag (0008, 010D), VR = UI [required if "Context Group Extension Flag" is "Y"]
	/// return true/false	false if strContextGroupExtensionCreatorUID is not a valid DcsUniqueIdentifier
	bool SetContextGroupExtensionCreatorUID(const DcsUniqueIdentifier strContextGroupExtensionCreatorUID);

	/// @see SetContextGroupExtensionCreatorUID
	DcsString GetContextGroupExtensionCreatorUID()const;

private:

	class ImplCodeSequenceCommon;
	ImplCodeSequenceCommon *m_pImplCodeSequenceCommon; ///< Internal implementation

	ImplCodeSequenceCommon* GetImpl();
	const ImplCodeSequenceCommon* GetImpl() const;
};

///
/// \class CodeSequence
/// The CodeSequence class implements the Code Sequence Macro
/// It adds methods to set the Code Value and Code Meaning
///
/// SPECREF V03 Section 14.11.8, Table 108
///
class CodeSequence : public CodeSequenceCommon
{
public:
	/// Constructor
	CodeSequence();

	/// Destructor
	virtual ~CodeSequence();

	/// Copy Constructor
	CodeSequence(const CodeSequence &codesequence);

	/// Assignment operator
	CodeSequence& operator=(const CodeSequence &codesequence);

	/// Comparison operator
	bool operator==(const CodeSequence &codesequence)const;
	/// Comparison operator
	bool operator!=(const CodeSequence &codesequence)const;

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

	/// Determine if all attributes are properly set
	/// @return true/false
	bool IsValid() const;

	/// Free the memory allocated by the CodeSequence
	virtual void FreeMemory();
	
	/// Determine if all required fields in the CodeSequence are empty strings
	/// @return true/false true if all required strings are empty
	virtual bool Empty() const;

	/// Code Value : Tag (0008, 0100)
	///	@param strCodeValue Tag (0008, 0100), VR = SH [required]
	/// @return true/false	false if strCodeValue is not a valid DcsShortString
	bool SetCodeValue(const DcsShortString &strCodeValue);

	/// @see SetCodeValue
	DcsString GetCodeValue()const;

	/// Code Meaning : Tag (0008, 0104)
	/// @param strCodeMeaning Tag (0008, 0104), VR = LO [required]
	/// @return true/false	false if strCodeMeaning is an invalid DcsLongString
	bool SetCodeMeaning(const DcsLongString &strCodeMeaning);

	/// @see SetCodeMeaning
	DcsString GetCodeMeaning()const;

	/// Add the CodeSequence's attributes to the given AttributeSequence as a SequenceItem.
	/// @param attributeSequence	An empty AttributeSequence used solely for this CodeSequence
	/// @param errorlog				Report conversion errors here
	/// @return true/false
	bool AsAttributeSequence(AttributeSequence &attributeSequence, ErrorLog &errorlog) const;

private:
	class ImplCodeSequence;
	ImplCodeSequence *m_pImplCodeSequence; ///< Internal implementation

	ImplCodeSequence* GetImpl();
	const ImplCodeSequence* GetImpl() const;
};

///
/// \class ExtendedCodeSequence
/// The ExtendedCodeSequence class implements the Extended Code Sequence Macro
/// It adds methods to set the Extended Code Value and Extended Code Meaning
///
/// SPECREF V03 Section 14.12, Table 109
///
class ExtendedCodeSequence : public CodeSequenceCommon
{
public:
	/// Constructor
	ExtendedCodeSequence();

	/// Destructor
	virtual ~ExtendedCodeSequence();

	/// Copy Constructor
	ExtendedCodeSequence(const ExtendedCodeSequence &extendedcodesequence);

	/// Assignment Operator
	ExtendedCodeSequence& operator=(const ExtendedCodeSequence &extendedcodesequence);

	/// Comparison Operator
	bool operator==(const ExtendedCodeSequence &extendedcodesequence)const;
	/// Comparison Operator
	bool operator!=(const ExtendedCodeSequence &extendedcodesequence)const;

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

	/// Determine if all attributes are properly set
	/// @return true/false
	bool IsValid() const;

	/// Free the memory allocated by the ExtendedCodeSequence
	virtual void FreeMemory();
	
	/// Determine if all required fields in the CodeSequence are empty strings
	/// @return true/false true if all required strings are empty
	virtual bool Empty() const;
	
	/// Extended Code Value : Tag (0008, 0101)
	///	@param strExtendedCodeValue Tag (0008, 0101), VR = LO [required]
	/// @return true/false false if strExtendedCodeValue is not a valid DcsLongString
	bool SetExtendedCodeValue(const DcsLongString &strExtendedCodeValue);

	/// @see SetExtendedCodeValue
	DcsString GetExtendedCodeValue()const;

	/// Extended Code Meaning : Tag (0008, 0104)
	///	@param strExtendedCodeMeaning Tag (0008, 0104), VR = LT [required]
	/// @return true/false false if strExtendedCodeMeaning is an invalid DcsLongText
	bool SetExtendedCodeMeaning(const DcsLongText &strExtendedCodeMeaning);

	/// @see SetExtendedCodeMeaning
	DcsString GetExtendedCodeMeaning()const;

	/// Add the CodeSequence attributes to the AttributeSequence as a SequenceItem
	/// @param attributeSequence	An empty AttributeSequence used solely for this ExtendedCodeSequence
	/// @param errorlog				Report conversion errors here
	/// @return true/false
	bool AsAttributeSequence(AttributeSequence &attributeSequence, ErrorLog &errorlog) const;
private:
	class ImplExtendedCodeSequence;
	ImplExtendedCodeSequence *m_pImplExtendedCodeSequence; ///< Internal implementation

	ImplExtendedCodeSequence* GetImpl();
	const ImplExtendedCodeSequence* GetImpl() const;
};

} //namespace SDICOS

#endif
