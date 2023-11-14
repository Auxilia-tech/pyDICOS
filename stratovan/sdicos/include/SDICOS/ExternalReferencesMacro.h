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
#ifndef _STRATOVAN_DICOS_EXTERNAL_REFERENCES_MACROS_H_
#define _STRATOVAN_DICOS_EXTERNAL_REFERENCES_MACROS_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class ExternalReferencesMacro
/// Implementation of External References Macro in the V03 specification
/// SPECREF V03 Section 14.20, Table 126
///
class ExternalReferencesMacro
{
public:
	/// Constructor
	ExternalReferencesMacro();

	/// Copy Constructor
	/// @param rhs Parameter to copy
	ExternalReferencesMacro(const ExternalReferencesMacro& rhs);

	/// Destructor
	virtual ~ExternalReferencesMacro();

	/// Delete allocated resources
	void FreeMemory();

	/// Assignment operator
	/// @param rhs Parameter to copy
	/// @return Reference to this object
	ExternalReferencesMacro& operator=(const ExternalReferencesMacro& rhs);

	/// Equality comparison operator. Compared array elements must be in same order to be considered equal.
	/// @param rhs Parameter to compare
	/// @return true/false
	bool operator==(const ExternalReferencesMacro& rhs)const;

	/// Inequality comparison operator
	/// @param rhs Parameter to compare
	/// @return true/false
	bool operator!=(const ExternalReferencesMacro& rhs)const;

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	bool SetAttributes(const AttributeManager& attribManager, ErrorLog& errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	bool GetAttributes(AttributeManager& attribManager, ErrorLog& errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false is returned if attributes were specified or if some were invalid.
	bool UpdateAttributes(const AttributeManager& attribManager, ErrorLog& errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	bool IsValid(const AttributeManager& attribManager, ErrorLog& errorlog) const;

	/// Set external references: Tag (4010, 2000), VR = ST, VM = 1...n [optional]
	/// @param vstrRefs External references to set
	/// @return true/false
	/// @see AddExternalReference
	/// @see GetExternalReferences
	bool SetExternalReferences(const Array1D<DcsShortText>& vstrRefs);
	/// Get external references
	/// @param vstrRefs External references
	/// @return true if references are present, false otherwise
	/// @see AddExternalReference
	/// @see SetExternalReferences
	bool GetExternalReferences(Array1D<DcsShortText>& vstrRefs)const;
	/// Append one external reference
	/// @see SetExternalReferences
	/// @see GetExternalReferences
	bool AddExternalReference(const DcsShortText&strRef);
	/// Returns tue if External References is preset, false otherwise
	/// @return Returns tue if External References is preset, false otherwise
	bool HasExternalReferences()const;
	/// Delete the optional attribute External References
	void DeleteExternalReferences();

protected:
	class Impl;
	Impl* m_pImpl; ///< Internal implementation
	Impl* GetImpl();
	const Impl* GetImpl() const;
};

}

#endif
