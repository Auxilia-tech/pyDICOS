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
#ifndef _STRATOVAN_DICOS_HIERARCHICAL_REFERENCES_H_
#define _STRATOVAN_DICOS_HIERARCHICAL_REFERENCES_H_

#include <ostream>

#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/CodeSequence.h"
#include "SDICOS/SopInstanceReference.h"

namespace SDICOS
{

///
/// \class HierarchicalSeriesReference
/// Implements Hierarchical Series Reference
/// SPECREF V03 Section 14.9, Table 106
///
class HierarchicalSeriesReference 
{
public:

	/// Constructor
	HierarchicalSeriesReference();

	/// Copy Constructor
	HierarchicalSeriesReference(const HierarchicalSeriesReference &HierarchicalSeriesReference);

	/// Destructor
	~HierarchicalSeriesReference();

	/// Assignment operator
	HierarchicalSeriesReference& operator=(const HierarchicalSeriesReference &HierarchicalSeriesReference);

	/// Equality operator
	bool operator==(const HierarchicalSeriesReference &HierarchicalSeriesReference)const;

	/// Inequality operator
	bool operator!=(const HierarchicalSeriesReference &HierarchicalSeriesReference)const;

	/// stream insertion operator
	friend std::ostream& operator<<(std::ostream&, const HierarchicalSeriesReference&);
	
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

	/// Check if all required parameters have valid values
	/// @return true/false
	bool IsValid() const;
	
	/// Set Series Instance UID : Tag (0020, 000E)
	/// @param strID Series Instance UID : Tag (0020, 000E), VR = UI [required]
	///			Unique Identifier of a Series that contains the referenced Composite Object(s)
	/// @return true/false false if the unique identifier is not valid
	bool SetSeriesInstanceUID(const DcsUniqueIdentifier &strID);

	/// @see SetSeriesInstanceUID
	DcsString GetSeriesInstanceUID()const;

	/// Set the Retrieve AE Title : Tag (0008, 0054)
	/// @param arrayNames Application Entity Name : Tag (0008, 0054), VR = AE [optional]
	///					-Name of DICOS application holding the "Composite Objects"
	/// @return true/false false if the AE strings are not valid
	bool SetApplicationNames(const Array1D<DcsApplicationEntity> &arrayNames);

	/// @see SetApplicationNames
	bool GetApplicationNames(Array1D<DcsApplicationEntity> &arrayNames)const;

	/// @see SetApplicationNames
	const Array1D<DcsApplicationEntity>& GetApplicationNames() const;

	/// Delete application names so that the attribute is not written to the DICOS file
	void DeleteApplicationNames();
	
	/// Set Storage Media File-Set ID : Tag (0088, 0130)
	///	@param strID Storage Media File-Set ID : Tag (0088, 0130), VR = SH [optional]
	///			Human readable identifier for the storage media that holds the Composite Object(s)
	/// @return true/false false if the unique identifier is not valid
	bool SetStorageMediaID(const DcsShortString &strID);

	/// SetStorageMediaID
	DcsString GetStorageMediaID()const;

	/// Delete the 'Storage Media File-Set Id' attribute so that it is not written to the DICOS file
	void DeleteStorageMediaID();
	
	/// Set Storage Media File-Set UID : Tag (0088, 0140)
	///	@param strUID Storage Media File-Set UID : Tag (0088, 0140), VR = UI [optional]
	///			Uniquely identifies the Storage Media with the Composite Object(s)
	/// @return true/false false if the unique identifier is not valid
	bool SetStorageMediaUID(const DcsUniqueIdentifier &strUID);

	/// SetStorageMediaUID
	DcsString GetStorageMediaUID()const;

	/// Delete the 'Storage Media File-Set UID' attribute so that it is not written to the DICOS file
	void DeleteStorageMediaUID();
	
	///
	/// \class SopInstanceReferenceSequenceItem
	/// Implements the Referenced SOP Sequence Tag(0008, 1199)
	/// SPECREF V03 Section 14.9, Table 106
	///
	class  SopInstanceReferenceSequenceItem
	{
	public:
		/// Constructor
		SopInstanceReferenceSequenceItem();

		/// Copy Constructor
		SopInstanceReferenceSequenceItem(const SopInstanceReferenceSequenceItem &sopinstancereferencesequenceitem);

		// Destructor
		~SopInstanceReferenceSequenceItem();

		/// Assignment operator
		SopInstanceReferenceSequenceItem& operator=(const SopInstanceReferenceSequenceItem &sopinstancereferencesequenceitem);

		/// Equality operator
		bool operator==(const SopInstanceReferenceSequenceItem &sopinstancereferencesequenceitem)const;

		/// Inequality operator
		bool operator!=(const SopInstanceReferenceSequenceItem &sopinstancereferencesequenceitem)const;

		/// Stream output operator
		friend std::ostream& operator<<(std::ostream&, const SopInstanceReferenceSequenceItem&);
	
		/// Check if all data is valid
		bool IsValid() const;

		/// Set SOP Instance Reference
		/// @param sop SOP Instance Reference Macro[required]
		/// @return true/false false if the SopInstanceReference is not valid
		bool SetSopInstanceReference(const SopInstanceReference &sop);

		/// @see SetSopInstanceReference
		bool GetSopInstanceReference(SopInstanceReference &sopinstancereference)const;

		/// @see SetSopInstanceReference
		SopInstanceReference& GetSopInstanceReference();

		/// @see SetSopInstanceReference
		const SopInstanceReference& GetSopInstanceReference() const;
		
		/// Set Purpose of Reference Code Sequence : Tag (0040, A170), VR = SQ [optional]
		/// @param arrayPurposeOfReference Purpose of Reference objects for Referenced SOP Sequence
		/// @return true/false false of CodeSequence objects are not valid
		bool SetPurposeOfReference(const Array1D<CodeSequence> &arrayPurposeOfReference);

		/// @see SetPurposeOfReference
		bool AddPurposeOfReference(const CodeSequence& arrayPurposeOfReference);

		/// @see SetPurposeOfReference
		bool GetPurposeOfReference(Array1D<CodeSequence> &arrayPurposeOfReference)const;

		/// @see SetPurposeOfReference
		const Array1D<CodeSequence>& GetPurposeOfReference() const;
		
	protected:
		friend class HierarchicalSeriesReference;
		
		class ImplRefSequenceItem;
		mutable ImplRefSequenceItem	*m_pImplRefSequenceItem; ///< Internal implementation

		ImplRefSequenceItem* GetImpl();
		const ImplRefSequenceItem* GetImpl() const;
	};

	/// Set Referenced SOP Sequence : Tag (0008, 1199), VR = SQ [required]
	/// @param arrayReferences  SOP Instance Reference Sequence Item
	/// @return true/false false if sequence item objects are not valid
	bool SetSopInstanceReference(const Array1D<SopInstanceReferenceSequenceItem> &arrayReferences);

	/// @see SetSopInstanceReference
	bool GetSopInstanceReference(Array1D<SopInstanceReferenceSequenceItem> &arrayReferences)const;

	/// @see SetSopInstanceReference
	Array1D<SopInstanceReferenceSequenceItem>& GetSopInstanceReference();

	/// @see SetSopInstanceReference
	const Array1D<SopInstanceReferenceSequenceItem>& GetSopInstanceReference() const;
private:
	class ImplHierarchicalSeriesReference;
	mutable ImplHierarchicalSeriesReference	*m_pImplHierarchicalSeriesReference; ///< Internal implementation

	ImplHierarchicalSeriesReference* GetImpl();
	const ImplHierarchicalSeriesReference* GetImpl() const;
};

///
/// \class HierarchicalSopInstanceReference
/// Implements Hierarchical SOP Instance Reference Macro
/// SPECREF V03 Section 14.9, Table 105
///
/// Contains Hierarchical Series Reference Macro which is implemented above
///
class HierarchicalSopInstanceReference 
{
public:
	/// Default constructor
	HierarchicalSopInstanceReference();

	/// Copy Constructor
	HierarchicalSopInstanceReference(const HierarchicalSopInstanceReference &hierarchicalsopinstancereference);

	/// destructor
	~HierarchicalSopInstanceReference();

	/// Assignment operator
	HierarchicalSopInstanceReference& operator=(const HierarchicalSopInstanceReference &hierarchicalsopinstancereference);

	/// Equality operator
	bool operator==(const HierarchicalSopInstanceReference &hierarchicalsopinstancereference)const;

	/// Inequality operator
	bool operator!=(const HierarchicalSopInstanceReference &hierarchicalsopinstancereference)const;

	/// Stream output operator
	friend std::ostream& operator<<(std::ostream&, const HierarchicalSopInstanceReference&);

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

	/// Check that all mandatory attributes have valid values
	/// @return true/false false if one or more attributes are not valid
	bool IsValid() const;
	
	/// Set Scan Instance UID
	/// @param strID  Scan Instance UID : Tag (0020, 000D), VR = UI [required]
	bool SetScanInstanceUID(const DcsUniqueIdentifier& strID);

	/// @see SetScanInstanceUID
	DcsString GetScanInstanceUID()const;

	///
	/// Set Referenced Series Sequence : Tag (0008, 1115), VR = SQ [required]
	/// @param arrayReferences Array of Hierarchical Series Reference objects [required]/ 
	/// @return true/false false if the HierarchicalSeriesReference objects are not valid
	bool SetReferencedSeries(const Array1D<HierarchicalSeriesReference> &arrayReferences);

	/// @see SetReferencedSeries
	bool GetReferencedSeries(Array1D<HierarchicalSeriesReference> &arrayReferences)const;

	/// @see SetSopInstanceReference
	Array1D<HierarchicalSeriesReference>& GetReferencedSeries();

	/// @see SetSopInstanceReference
	const Array1D<HierarchicalSeriesReference>& GetReferencedSeries() const;
private:
	class ImplHierarchicalSopInstanceReference;
	mutable ImplHierarchicalSopInstanceReference	*m_pImplHierarchicalSopInstanceReference; ///< Internal implementation
	
	ImplHierarchicalSopInstanceReference* GetImpl();
	const ImplHierarchicalSopInstanceReference* GetImpl() const;
};

}//namespace SDICOS

#endif // _STRATOVAN_DICOS_HIERARCHICAL_REFERENCES_H_