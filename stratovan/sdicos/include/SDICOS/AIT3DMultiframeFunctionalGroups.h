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
#ifndef _STRATOVAN_DICOS_AIT_3D_MULTIFRAME_FUNCTIONAL_GROUPS_H_
#define _STRATOVAN_DICOS_AIT_3D_MULTIFRAME_FUNCTIONAL_GROUPS_H_

#include "SDICOS/AIT3DMultiframeFunctionalGroupMacros.h"
#include "SDICOS/MultiframeFunctionalGroupsBase.h"

namespace SDICOS
{
namespace AIT3DTypes
{

///
/// \class AIT3DMultiframeFunctionalGroups
/// \brief Implements AIT3D Multiframe Functional Groups, which is an AIT3D specific usage of multiframe functional groups
/// SPECREF V03 Section 14.17, Table 123
///	
class AIT3DMultiframeFunctionalGroups : public MultiframeFunctionalGroupsBase
{
public:
	/// Constructor
	AIT3DMultiframeFunctionalGroups();
	/// Copy constructor
	AIT3DMultiframeFunctionalGroups(const AIT3DMultiframeFunctionalGroups &mfg);
	/// Destructor
	virtual ~AIT3DMultiframeFunctionalGroups();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	AIT3DMultiframeFunctionalGroups& operator=(const AIT3DMultiframeFunctionalGroups &mfg);
	/// Comparison operator
	bool operator==(const AIT3DMultiframeFunctionalGroups &mfg)const;
	/// Comparison operator
	bool operator!=(const AIT3DMultiframeFunctionalGroups &mfg)const;

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
	/// Shared Functional Groups Sequence (Single item sequence) : Tag (5200, 9229), VR = SQ [required (Type 2), can be empty]
	/// These are values common to all frames.
	///
	bool SetSharedFunctionalGroups(const AIT3DMultiframeFunctionalGroupMacros &mfgShared);
	/// @see SetSharedFunctionalGroups
	bool GetSharedFunctionalGroups(AIT3DMultiframeFunctionalGroupMacros &mfgShared)const;
	/// Allocate Shared Functional Groups
	void AllocateSharedFunctionalGroups();
	/// Get the Shared Functional Groups
	AIT3DMultiframeFunctionalGroupMacros* GetSharedFunctionalGroups();
	/// @see SetSharedFunctionalGroups
	const AIT3DMultiframeFunctionalGroupMacros* GetSharedFunctionalGroups()const;
	/// Delete the Shared Functional Groups
	void DeleteSharedFunctionalGroups();

	///
	/// Per-Frame Functional Groups Sequence : Tag (5200, 9230), VR = SQ [required]
	/// These are values unique to the frame, where each item in this array represents a single frame (First item corresponds to the first frame)
	///
	bool SetPerFrameFunctionalGroups(const Array1D<AIT3DMultiframeFunctionalGroupMacros> &arrayPerFrame);
	/// @see SetPerFrameFunctionalGroups
	bool GetPerFrameFunctionalGroups(Array1D<AIT3DMultiframeFunctionalGroupMacros> &arrayPerFrame)const;
	/// @see SetPerFrameFunctionalGroups
	Array1D<AIT3DMultiframeFunctionalGroupMacros>& GetPerFrameFunctionalGroups();
	/// @see SetPerFrameFunctionalGroups
	const Array1D<AIT3DMultiframeFunctionalGroupMacros>& GetPerFrameFunctionalGroups()const;
	/// Delete Per-Frame Functional Groups
	void DeletePerFrameFunctionalGroups();

protected:
	class ImplAIT3DMultiframeFunctionalGroups;
	ImplAIT3DMultiframeFunctionalGroups	*m_pImplAIT3DMFG; ///< Internal implementation
};

}//namespace AIT3DTypes
}//namespace SDICOS

#endif
