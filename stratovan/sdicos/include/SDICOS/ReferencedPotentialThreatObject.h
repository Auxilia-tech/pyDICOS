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
#ifndef _STRATOVAN_DICOS_REFERENCED_POTENTIAL_THREAT_OBJECT_TDR_H_
#define _STRATOVAN_DICOS_REFERENCED_POTENTIAL_THREAT_OBJECT_TDR_H_

#include "SDICOS/SopInstanceReference.h"

namespace SDICOS
{
namespace TDRTypes
{

///
/// \class ReferencedPotentialThreatObject
/// Referenced Potential Threat Object Sequence : Tag (4010, 1076), 
/// VR = SQ [required if using a PTO from a referenced TDR]
///
/// SPECREF V03 Section 12.5, Table 70
///
/// As a separate object that represents a sequence attribute, 
/// the ReferencedPotentialThreatObject class knows to push/pop its Tag
/// when reporting errors in the AttributeManager methods.
///
class ReferencedPotentialThreatObject
{
public:
	/// Default Constructor
	ReferencedPotentialThreatObject();
	
	/// Copy Constructor
	ReferencedPotentialThreatObject(const ReferencedPotentialThreatObject &pto);
	
	/// Destructor
	~ReferencedPotentialThreatObject();

	/// Reset to default state
	void FreeMemory();

	/// Assignment operator
	ReferencedPotentialThreatObject& operator=(const ReferencedPotentialThreatObject &pto);
	
	/// Equality Comparison operator
	bool operator==(const ReferencedPotentialThreatObject &pto)const;
	
	/// Inequality Comparison operator
	bool operator!=(const ReferencedPotentialThreatObject &pto)const;

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

	///
	/// \class PTOItem 
	/// Item in Referenced Potential Threat Object Sequence, Tag (4010, 1076)
	///
	class PTOItem
	{
	public:
		
		/// Constructor
		PTOItem();
		
		/// Copy Constructor
		PTOItem(const PTOItem &item);
		
		/// Destructor
		~PTOItem();

		/// Reset to default values
		void FreeMemory();

		/// Assignment operator
		PTOItem& operator=(const PTOItem &item);

		/// Equality Comparison Operator
		bool operator==(const PTOItem &item)const;

		/// Inequality Comparison Operator
		bool operator!=(const PTOItem &item)const;

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

		/// Set Referenced PTO ID : Tag (4010, 1010), VR = US [required]
		/// @param nID Identification of the referenced PTO
		/// @return true/false
		bool SetObjectID(const S_UINT16 nID);

		/// @see SetObjectID
		S_UINT16 GetObjectID()const;

		/// Set Referenced TDR Instance Sequence (Single Item Sequence) : Tag (4010, 1077), VR = SQ [required]
		/// @param sopinstancereference The SOP Instance of the TDR being assessed
		bool SetSopInstanceReference(const SopInstanceReference &sopinstancereference);	

		/// @see SetSopInstanceReference
		bool GetSopInstanceReference(SopInstanceReference &sopinstancereference)const;	

		/// @see SetSopInstanceReference
		SopInstanceReference& GetSopInstanceReference();

		/// @see SetSopInstanceReference
		const SopInstanceReference& GetSopInstanceReference()const;

	protected:
		class ImplPTOItem;
		ImplPTOItem *m_pImplPTOItem; ///< Internal implementation
		
		ImplPTOItem* GetImpl();
		const ImplPTOItem* GetImpl() const;
	};

	typedef Array1D<PTOItem> PTOItemList;
	
	/// Set Referenced Potential Threat Object Sequence : Tag (4010, 1076), VR = SQ [required if using a referenced PTO]
	/// @param ptoItems	Potential Threat Object Items
	/// @return true/false
	bool SetReferencedPotentialThreatObject(const PTOItemList &ptoItems);

	/// @see SetReferencedPotentialThreatObject
	bool GetReferencedPotentialThreatObject(PTOItemList &arrayRef)const;

	/// @see SetReferencedPotentialThreatObject
	PTOItemList& GetReferencedPotentialThreatObject();

	/// @see SetReferencedPotentialThreatObject
	const PTOItemList& GetReferencedPotentialThreatObject()const;

protected:
	class ImplReferencedPTO;
	ImplReferencedPTO	*m_pImplReferencedPTO; ///< Internal implementation
	
	ImplReferencedPTO* GetImpl();
	const ImplReferencedPTO* GetImpl() const;
};

}//namespace TDRTypes
}//namespace SDICOS

#endif