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
#ifndef _STRATOVAN_DICOS_CT_MULTIFRAME_FUNCTIONAL_GROUP_H_
#define _STRATOVAN_DICOS_CT_MULTIFRAME_FUNCTIONAL_GROUP_H_

#include "SDICOS/CTMultiframeFunctionalGroupMacros.h"
#include "SDICOS/MultiframeFunctionalGroupsBase.h"

namespace SDICOS
{

namespace CTTypes
{

///
/// \class CTMultiframeFunctionalGroups
/// \brief Implements CT Multiframe Functional Groups, which is a CT specific usage of multiframe functional groups
/// SPECREF V03 Section 14.17, Table 123
///	
class CTMultiframeFunctionalGroups : public MultiframeFunctionalGroupsBase
{
public:
	/// Constructor
	CTMultiframeFunctionalGroups();
	/// Copy constructor
	CTMultiframeFunctionalGroups(const CTMultiframeFunctionalGroups &mfg);
	/// Destructor
	virtual ~CTMultiframeFunctionalGroups();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	CTMultiframeFunctionalGroups& operator=(const CTMultiframeFunctionalGroups &mfg);
	/// Comparison operator
	bool operator==(const CTMultiframeFunctionalGroups &mfg)const;
	/// Comparison operator
	bool operator!=(const CTMultiframeFunctionalGroups &mfg)const;

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

	/// Shared Functional Groups Sequence (Single item sequence). These are values common to all frames. : Tag (5200, 9229), VR = SQ [required (Type 2), can be empty]
	bool SetSharedFunctionalGroups(const CTMultiframeFunctionalGroupMacros &mfgm);
	/// @see SetSharedFunctionalGroups
	bool GetSharedFunctionalGroups(CTMultiframeFunctionalGroupMacros &mfgm)const;
	/// Allocate Shared Functional Groups
	void AllocateSharedFunctionalGroups();
	/// Get the Shared Functional Groups
	CTMultiframeFunctionalGroupMacros* GetSharedFunctionalGroups();
	/// @see SetSharedFunctionalGroups
	const CTMultiframeFunctionalGroupMacros* GetSharedFunctionalGroups()const;
	/// Delete the Shared Functional Groups
	void DeleteSharedFunctionalGroups();

	/// Per-Frame Functional Groups Sequence. These are values unique to the frame, where each item in this array represents a single frame (First item corresponds to the first frame). : Tag (5200, 9230), VR = SQ [required]
	bool SetPerFrameFunctionalGroups(const Array1D<CTMultiframeFunctionalGroupMacros> &arrayPerFrame);
	/// @see SetPerFrameFunctionalGroups
	bool GetPerFrameFunctionalGroups(Array1D<CTMultiframeFunctionalGroupMacros> &arrayPerFrame)const;
	/// @see SetPerFrameFunctionalGroups
	Array1D<CTMultiframeFunctionalGroupMacros>& GetPerFrameFunctionalGroups();
	/// @see SetPerFrameFunctionalGroups
	const Array1D<CTMultiframeFunctionalGroupMacros>& GetPerFrameFunctionalGroups()const;
	/// Delete Per-Frame Functional Groups
	void DeletePerFrameFunctionalGroups();

protected:
	class ImplCTMultiframeFunctionalGroups;
	ImplCTMultiframeFunctionalGroups	*m_pImplCTMultiframeFunctionalGroups; ///< Internal implementation
};

}//namespace CTTypes

}//namespace SDICOS

#endif
