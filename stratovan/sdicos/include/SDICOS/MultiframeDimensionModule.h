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
#ifndef _STRATOVAN_DICOS_MULTIFRAME_DIMENSION_MODULE_H_
#define _STRATOVAN_DICOS_MULTIFRAME_DIMENSION_MODULE_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class MultiframeDimensionModule
/// \brief Multiframe Dimension
/// SPECREF V03 Section 14.16, Table 122
///
class MultiframeDimensionModule
{
public:
	/// Constructor
	MultiframeDimensionModule();
	/// Copy constructor
	MultiframeDimensionModule(const MultiframeDimensionModule &mdm);
	/// Destructor
	virtual ~MultiframeDimensionModule();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	MultiframeDimensionModule& operator=(const MultiframeDimensionModule &mdm);
	/// Comparison operator
	bool operator==(const MultiframeDimensionModule &mdm)const;
	/// Comparison operator
	bool operator!=(const MultiframeDimensionModule &mdm)const;

	///
	/// \class DimensionIndexItem
	/// \brief Item in Dimension Index Sequence (0020, 9222) 
	///
	class DimensionIndexItem
	{
	public:
		/// Constructor
		DimensionIndexItem();
		/// Copy constructor
		DimensionIndexItem(const DimensionIndexItem &item);
		/// Destructor
		virtual ~DimensionIndexItem();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		DimensionIndexItem& operator=(const DimensionIndexItem &item);
		/// Comparison operator
		bool operator==(const DimensionIndexItem &item)const;
		/// Comparison operator
		bool operator!=(const DimensionIndexItem &item)const;

		///
		/// Initialize the class attributes from the given AttributeManager
		///
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @param bIsDimensionOrganizationSequenceEmpty Flag if Dimension Organization Sequence (0020, 9221) has no items
		/// @return true/false		false is returned if any required attribute is missing or invalid
		///
		virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog, const bool bIsDimensionOrganizationSequenceEmpty);

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
		/// @param bIsDimensionOrganizationSequenceEmpty Flag if Dimension Organization Sequence (0020, 9221) has no items
		/// @return true/false
		///
		virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog, const bool bIsDimensionOrganizationSequenceEmpty)const;

		/// Dimension Index Pointer : Tag (0020, 9165), VR = AT [required]
		bool SetDimensionIndexPointer(const Tag &tagDimensionIndexPointer);
		// @see SetDimensionIndexPointer
		bool GetDimensionIndexPointer(Tag &tagDimensionIndexPointer)const;
		// @see SetDimensionIndexPointer
		Tag& GetDimensionIndexPointer();
		// @see SetDimensionIndexPointer
		const Tag& GetDimensionIndexPointer()const;

		/// Dimension Index Private Creator : Tag (0020, 9213), VR = LO [required if "Dimension Index Pointer" (0020, 9165) points to a private attribute]
		bool SetDimensionIndexPrivateCreator(const DcsLongString &strDimensionIndexPrivateCreator);
		/// @see SetDimensionIndexPrivateCreator
		DcsString GetDimensionIndexPrivateCreator()const;

		///
		/// Functional Group Pointer : Tag (0020, 9167), VR = AT [required if "Dimension Index Pointer" (0020, 9165) points to an attribute that is part of a functional group sequence]
		/// @param tagFunctionalGroupPointer Refers to a sequence attribute that contains the tag in Dimension Index Pointer (0020, 9165)
		///
		bool SetFunctionalGroupPointer(const Tag &tagFunctionalGroupPointer);
		/// @see SetFunctionalGroupPointer
		bool GetFunctionalGroupPointer(Tag &tagFunctionalGroupPointer)const;
		/// @see SetFunctionalGroupPointer
		Tag& GetFunctionalGroupPointer();
		/// @see SetFunctionalGroupPointer
		const Tag& GetFunctionalGroupPointer()const;

		/// Functional Group Private Creator : Tag (0020, 9238), VR = LO [required if "Functional Group Pointer" (0020, 9167) points to a private attribute]
		bool SetFunctionalGroupPrivateCreator(const DcsLongString &strFunctionalGroupPrivateCreator);
		/// @see SetFunctionalGroupPrivateCreator
		DcsString GetFunctionalGroupPrivateCreator()const;

		/// Dimension Organization UID : Tag (0020, 9164), VR = UI [required if "Dimension Organization Sequence" (0020, 9221) is not empty]
		bool SetDimensionOrganizationUID(const DcsUniqueIdentifier &strID);
		/// @see SetDimensionOrganizationUID
		DcsString GetDimensionOrganizationUID()const;

		/// Dimension Description Label : Tag (0020, 9421), VR = LO [optional]
		bool SetDescription(const DcsLongString &strDescription);
		/// @see SetDescription
		DcsString GetDescription()const;

	protected:
		class ImplDimensionIndexItem;
		ImplDimensionIndexItem	*m_pImplDimensionIndexItem; ///< Internal implementation
	};

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

	/// Dimension Organization Sequence : Tag (0020, 9221), VR = SQ [required (type 2), can be empty]
	///	@param arrayIDs Dimension Organization UIDs: Each array element represents a single UID : Tag (0020, 9164), VR = UI [required]
	bool SetDimensionOrganizationUID(const Array1D<DcsUniqueIdentifier> &arrayIDs);
	/// @see SetDimensionOrganizationUID
	bool GetDimensionOrganizationUID(Array1D<DcsString> &arrayIDs)const;
	/// Remove all items from Dimension Organization Sequence
	void DeleteDimensionOrganizationUID();

	/// Dimension Index Sequence : Tag (0020, 9222), VR = SQ [required (type 2), can be empty]
	bool SetDimensionIndex(const Array1D<DimensionIndexItem> &arrayIndicis);
	/// @see SetDimensionIndex
	bool GetDimensionIndex(Array1D<DimensionIndexItem> &arrayIndicis)const;
	/// @see SetDimensionIndex
	Array1D<DimensionIndexItem>& GetDimensionIndex();
	/// @see SetDimensionIndex
	const Array1D<DimensionIndexItem>& GetDimensionIndex()const;

protected:
	class ImplMultiframeDimensionModule;
	ImplMultiframeDimensionModule	*m_pImplMultiframeDimensionModule; ///< Internal implementation
};

}//namespace SDICOS

#endif
