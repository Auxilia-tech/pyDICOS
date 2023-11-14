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
#ifndef _STRATOVAN_DICOS_DICOS_CODE_DEFINITIONS_H_
#define	_STRATOVAN_DICOS_DICOS_CODE_DEFINITIONS_H_

#include "SDICOS/String.h"

namespace SDICOS { namespace CodeDefinitions {
	
	///
	/// DICOS Code Definitions
	/// SPECREF V03 Section 17.5, Table 138
	/// Coding Scheme Designator = 'DICOS'
	/// Coding Scheme Version = '01'
	/// Enum integer value is the 'Code Value'
	///
	typedef enum
	{
		enumUnknownCodeDefinition = 0,	///< Does not match defined terms

		enumText,		///< 100001, "TEXT"
		enumRFID,		///< 100002, "RFID"
		enumBarcode,	///< 100003, "BARCODE"
		enumMRP,		///< 100004, "MRP"
		enumPIV,		///< 100005, "PIV"
	}DICOS_CODE_DEFINITION;
	
	/// Get the code definition from the code value ('100001' ... )
	DICOS_CODE_DEFINITION CodeDefinitionFromCodeValue(const S_UINT32 codeValue);
	
	/// Get the code definition from the code value ("100001" ... )
	DICOS_CODE_DEFINITION CodeDefinitionFromCodeValue(const DcsString& s);
	
	/// Code Definition from code meaning string ("TEXT", ...)
	DICOS_CODE_DEFINITION CodeDefinitionFromString(const DcsString& s);
	
	/// Get numerical code for the gicen definition as a string
	DcsString GetCodeValue(const DICOS_CODE_DEFINITION d);
	
	/// Get the human readable code meaning for a definition
	DcsString GetCodeMeaning(const DICOS_CODE_DEFINITION d); 

	/// Is the given enum value valid
	bool IsValidCodeDefinition(const DICOS_CODE_DEFINITION d);

} // namespace CodeDefinitions	
} // namespace SDICOS

#endif	/* _STRATOVAN_DICOS_DICOS_CODE_DEFINITIONS_H_ */

