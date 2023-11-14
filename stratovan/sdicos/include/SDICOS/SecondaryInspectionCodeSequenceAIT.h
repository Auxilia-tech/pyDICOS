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
#ifndef _STRATOVAN_DICOS_AIT_SECONDARY_INSPECTION_CODE_SEQUENCE_H_
#define _STRATOVAN_DICOS_AIT_SECONDARY_INSPECTION_CODE_SEQUENCE_H_

#include "SDICOS/CodeSequence.h"

namespace SDICOS
{

///
/// \class AitSecondaryInspectionCodeSequence
/// Implements a CodeSequence with the restrictions described in 
/// CID DCS3 Ait Secondary Inspection Methods Context
///
///		Context ID = "DCS3"
///		Code Scheme Designator = "TSA"
///
/// SPECREF V03 Section 14.11.8, Table 108
///
class AitSecondaryInspectionCodeSequence : public CodeSequence
{
public:

	/// Constructor
	AitSecondaryInspectionCodeSequence();

	/// Copy constructor
	AitSecondaryInspectionCodeSequence(const AitSecondaryInspectionCodeSequence &aitsecondaryinspectioncodesequence);

	/// Destructor
	~AitSecondaryInspectionCodeSequence();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	AitSecondaryInspectionCodeSequence& operator=(const AitSecondaryInspectionCodeSequence &aitsecondaryinspectioncodesequence);
	/// Comparison operator
	bool operator==(const AitSecondaryInspectionCodeSequence &aitsecondaryinspectioncodesequence)const;
	/// Comparison operator
	bool operator!=(const AitSecondaryInspectionCodeSequence &aitsecondaryinspectioncodesequence)const;
	
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
	
private:

	/// Method to verify CodeSequence restrictions for Baseline CID = DCS3
	bool CheckDCS3Attributes(ErrorLog &);

	/// Set Code Scheme Designator : Tag (0008, 0102)
	///		i) Internally set Code Scheme Designator to "TSA"
	virtual bool SetSchemeDesignator(const DcsShortString &);

	/// Set Context Identifier : Tag (0008, 010F)
	///		i) Internally set Context Identifier to "DCS3"
	virtual bool SetContextID(const DcsCodeString &);
};
}//namespace SDICOS

#endif