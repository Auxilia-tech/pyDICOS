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
#ifndef _STRATOVAN_DICOS_SOPREFERENCE_H_
#define _STRATOVAN_DICOS_SOPREFERENCE_H_

#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class SopInstanceReference
///
/// The SDICOS::SopInstanceReference class implements the SOP Instance Reference Macro
/// SPECREF V03 Section 14.8, Table 104
/// - Attributes
///   - Referenced SOP Class UID : Tag (0008, 1150)
///   - Referenced SOP Instance UID : Tag (0008, 1155)
///
class SopInstanceReference
{
public:
	///
	/// Initialize with default values
	///
	SopInstanceReference();
	///
	/// Copy constructor
	///
	SopInstanceReference(const SopInstanceReference &sopinstancereference);

	///
	/// Destructor
	///
	~SopInstanceReference();

	///
	/// Reset to default values
	///
	virtual void FreeMemory();

	///
	/// Copy operator
	///
	SopInstanceReference& operator=(const SopInstanceReference &sopinstancereference);
	///
	/// Comparison operator
	///
	bool operator==(const SopInstanceReference &sopinstancereference)const;
	///
	/// Comparison operator
	///
	bool operator!=(const SopInstanceReference &sopinstancereference)const;

	///
	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set the Referenced SOP Class UID : Tag (0008, 1150), VR = UI [required]
	///
	/// @param strClassUID A string of characters that uniquely identifies the referenced SOP Class
	/// @return true/false
	///
	bool SetClassUID(const DcsUniqueIdentifier &strClassUID);		

	///
	/// Get the unique class id.
	///
	/// @see SetClassUID(const DcsUniqueIdentifier)
	///
	DcsString GetClassUID()const;

	///
	/// Set Referenced SOP Instance UID : Tag (0008, 1155), VR = UI [required]
	///
	/// @param strInstanceUID A string of characters that uniquely identifies the referenced SOP Instance
	/// @return true/false
	///
	bool SetInstanceUID(const DcsUniqueIdentifier &strInstanceUID);	

	///
	/// Get the unique instance UID
	///
	/// @see SetInstanceUID(const DcsUniqueIdentifier)
	///
	DcsString GetInstanceUID()const;	

protected:
	class ImplSopInstanceReference;
	ImplSopInstanceReference *m_pImplSopInstanceReference; ///< Internal implementation
};

}//namespace SDICOS

#endif
