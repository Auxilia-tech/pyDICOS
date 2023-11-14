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
#ifndef _STRATOVAN_DICOS_IDENTIFICATION_ENCODING_TYPE_H_
#define _STRATOVAN_DICOS_IDENTIFICATION_ENCODING_TYPE_H_

#include "SDICOS/CodeSequence.h"

namespace SDICOS
{

///
/// \class IdentificationEncodingType
/// Implementation for Identification Encoding Type
/// SPECREF V03 Section 14.11.8, Table 108
///
/// Context ID = "DCS4"
/// Code Scheme Designator = "DCS"
/// Code Scheme Version of the form yyyymmdd
class IdentificationEncodingType : public CodeSequence
{
public:

	/// Default Constructor
	IdentificationEncodingType();
	
	/// Copy Constructor
	IdentificationEncodingType(const IdentificationEncodingType &identificationencodingtype);

	/// Assignment operator
	IdentificationEncodingType& operator=(const IdentificationEncodingType &identificationencodingtype);
	
	/// Comparison operator
	bool operator==(const IdentificationEncodingType &identificationencodingtype)const;

	typedef enum
	{
		enumUnknownIdentificationEncodingType,	///< Does not match defined Code Values

		enumTextEncoding,	///< Code Meaning = "Text Encoding", Code Value = "100001"
		enumRFID,			///< Code Meaning = "RFID",			 Code Value = "100002"
		enumBarcode,		///< Code Meaning = "Barcode",		 Code Value = "100003"
		enumMRP,			///< Code Meaning = "MRP", 			 Code Value = "100004", Machine Readable Passport
		enumPIV,			///< Code Meaning = "PIV", 			 Code Value = "100005", Personal Identity Verification

	}IDENTIFICATION_ENCODING_TYPE;

	/// Constructor from identification encoding type
	IdentificationEncodingType(const IDENTIFICATION_ENCODING_TYPE nType);
	
	/// Set Encoding type using enumeration
	///	@param nType Param 1, Encoding Type
	/// @return true/false
	bool SetEncodingType(const IDENTIFICATION_ENCODING_TYPE nType);

	/// @see SetEncodingType
	IDENTIFICATION_ENCODING_TYPE GetEncodingType()const;
	
	/// @see SetEncodingType
	DcsString GetEncodingTypeAsString()const;
	
	/// Utility method to initialize a CodeSequence object with the correct data
	/// for a CID DCS4 Identification Encoding Type
	static bool SetEncodingType(CodeSequence& cs, const IDENTIFICATION_ENCODING_TYPE nType);

	/// Static IsValid method to validate a CodeSequence object against the requirements
	/// for a CID DCS4 Identification Encoding Type
	static bool IsValid(const CodeSequence& cs, const IDENTIFICATION_ENCODING_TYPE nType, const AttributeManager& attribManager, ErrorLog& errorlog);

	/// Static SetAttributes method to set attributes on a CodeSequence object and extract the Identification Encoding Type if possible
	/// @param cs Fill this CodeSequence with parameters from the attribute manager
	/// @param nType Extract Identification Encoding Type using CodeValue and Code meaning attributes
	/// @param attribManager Attribute Manager to find attribute data in
	/// @param errorlog ErrorLog to log errors in
	/// @return true/false false if Identification Encoding Type cannot be deduced
	static bool SetAttributes(CodeSequence& cs, IDENTIFICATION_ENCODING_TYPE& nType, const AttributeManager& attribManager, ErrorLog& errorlog);

	/// Attempt to extract the identification encoding type from the given code sequence
	static IDENTIFICATION_ENCODING_TYPE GetIdEncodingType(const CodeSequence& cs);
private:
	/// Identification Encoding Type
	/// Declared here instead of implementation class for simplicity
	IDENTIFICATION_ENCODING_TYPE m_IdentificationEncodingType;

	/// Set Code Scheme Designator : Tag (0008, 0102)
	///	@param strSchemeDesignator Code Scheme Designator : Tag (0008, 0102), VR = SH [required]
	///		i) Internally set Code Scheme Designator = DCS
	/// @return true/false
	virtual bool SetSchemeDesignator(const DcsShortString &strSchemeDesignator);

	/// Set Context Identifier : Tag (0008, 010F)
	///	@param strContextID Context Identifier : Tag (0008, 010F), VR = CS [optional]
	///		i) Internally set Context ID = DCS4
	/// @return true/false
	virtual bool SetContextID(const DcsCodeString &strContextID);

	/// Set Code Value : Tag (0008, 0100)
	///	-Set with call to SetEncodingType(IDENTIFICATION_ENCODING_TYPE)
	///	@param strCodeValue Code Value : Tag (0008, 0100), VR = SH [required]
	virtual bool SetCodeValue(const DcsShortString &strCodeValue);

	/// Set Code Meaning : Tag (0008, 0104)
	///	-Set with call to SetEncodingType(IDENTIFICATION_ENCODING_TYPE)
	///	@param strCodeMeaning Code Meaning : Tag (0008, 0104), VR = LO [required]
	virtual bool SetCodeMeaning(const DcsLongString &strCodeMeaning);

};

}//namespace SDICOS

#endif
