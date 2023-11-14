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
#ifndef _STRATOVAN_DICOS_OBJECT_OF_INSPECTION_MODULE_H_
#define _STRATOVAN_DICOS_OBJECT_OF_INSPECTION_MODULE_H_

#include "SDICOS/Types.h"
#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/CodeSequence.h"

namespace SDICOS
{

///
/// \class ObjectOfInspectionModule
/// \brief Implements Object Of Inspection Module (OOI)
/// SPECREF V03 Section 4.1, Table 13
///
class ObjectOfInspectionModule
{
public:
	/// Constructor
	ObjectOfInspectionModule();
	/// Copy constructor
	ObjectOfInspectionModule(const ObjectOfInspectionModule &objectofinspectionmodule);
	/// Destructor
	virtual ~ObjectOfInspectionModule();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	ObjectOfInspectionModule& operator=(const ObjectOfInspectionModule &objectofinspectionmodule);
	/// Comparison operator
	bool operator==(const ObjectOfInspectionModule &objectofinspectionmodule)const;
	/// Comparison operator
	bool operator!=(const ObjectOfInspectionModule &objectofinspectionmodule)const;

	/// Object of inspection gender enumrations
	typedef enum
	{
		enumUnknownObjectOfInspectionGender,

		enumGenderMale,		///< "M"
		enumGenderFemale,	///< "F"
		enumGenderOther,	///< "O"
		enumGenderUnknown,	///< "U"

	}OBJECT_OF_INSPECTION_GENDER;

	/// Object of inspection type enumerations
	typedef enum
	{
		enumUnknownObjectOfInspectionType,

		enumTypeBioSample,		///< "BIO_SAMPLE"
		enumTypeCargo,			///< "CARGO"
		enumTypeBaggage,		///< "BAGGAGE"
		enumTypeAnimal,			///< "ANIMAL"
		enumTypeOther,			///< "OTHER"
		enumTypePerson,			///< "PERSON"

	}OBJECT_OF_INSPECTION_TYPE;
	
	///
	/// \class IdInfo
	/// \brief Implements a sub class for handling ID oriented attributes
	///
	class IdInfo
	{
	public:
		/// Constructor
		IdInfo();
		/// Copy constructor
		IdInfo(const IdInfo &idinfo);
		/// Destructor
		~IdInfo();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		IdInfo& operator=(const IdInfo &idinfo);
		/// Comparison operator
		bool operator==(const IdInfo &idinfo)const;
		/// Comparison operator
		bool operator!=(const IdInfo &idinfo)const;

		/// OOI Type enumerations
		typedef enum
		{
			enumUnknownObjectOfInspectionIdType, ///< Unknown enumeration

			enumText,		///< "TEXT"
			enumRFID,		///< "RFID"
			enumBarcode,	///< "BARCODE"
			enumMRP,		///< "MRP"

		}OBJECT_OF_INSPECTION_ID_TYPE;

		///
		/// Initialize the class attributes from the given AttributeManager
		///
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if any required attribute is missing or invalid
		///
		bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		///
		/// Copy the attributes from the module into the given AttributeManager
		///
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if any required attribute is not present.
		///
		bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

		///
		/// Set all required and optional attributes from the given AttributeManager
		///
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false if IsValid() returned false
		///
		bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		///
		/// Determine if all needed attributes (required and conditionally required) are set.
		///
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		///
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

		/// Set OOI ID : Tag (0010, 0020), VR = LO [required]
		bool SetID(const DcsLongString &strID);
		/// @see SetID
		DcsString GetID()const;

		/// Set OOI ID Assigning Authority : Tag (0010, 0021), VR = LO [required]
		bool SetIdAssigningAuthority(const DcsLongString &strAssigningAuthority);
		/// @see SetIdAssigningAuthority
		DcsString GetIdAssigningAuthority()const;

		/// Set OOI ID Type : Tag (0010, 0022), VR = CS [required]
		bool SetIdType(const OBJECT_OF_INSPECTION_ID_TYPE nIdType);
		/// @see SetIdType
		OBJECT_OF_INSPECTION_ID_TYPE GetIdType()const;
		/// Return the ID Type as a string
		DcsString GetIdTypeAsString()const;

	protected:
		class ImplIdInfo;
		ImplIdInfo	*m_pImplIdInfo; ///< Internal implementation
	};

	///
	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// Set the OOI's ID [required]
	bool SetID(const ObjectOfInspectionModule::IdInfo &idinfo);
	/// @see SetID
	bool GetID(ObjectOfInspectionModule::IdInfo &idinfo)const;
	/// @see SetID
	IdInfo& GetID();
	/// @see SetID
	const IdInfo& GetID()const;

	/// Set Mass in grams : Tag (0010, 1030), VR = DS [optional]
	bool SetMassInGrams(const float fMassInGrams);
	/// @see SetMassInGrams
	float GetMassInGrams()const;
	/// @see SetMassInGrams
	DcsString GetMassInGramsAsString()const;
	/// Delete mass
	void DeleteMass();

	/// Set Gender : Tag (0010, 0040), VR = CS  [required if OOI Type, (4010, 1042), is "PERSON"]
	bool SetGender(const OBJECT_OF_INSPECTION_GENDER nGender);
	/// @see SetGender
	ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER GetGender()const;
	/// @see SetGender
	DcsString GetGenderAsString()const;
	/// Delete gender
	void DeleteGender();

	/// Set Alternate ID's Sequence : Tag (0010, 1002), VR = SQ [optional]
	/// These are alternate ID's for this OOI
	bool SetAlternateIDs(const Array1D<ObjectOfInspectionModule::IdInfo> &arrayAlternateIDs);
	/// @see SetAlternateIDs
	bool GetAlternateIDs(Array1D<ObjectOfInspectionModule::IdInfo> &arrayAlternateIDs)const;
	/// @see SetAlternateIDs
	Array1D<ObjectOfInspectionModule::IdInfo>& GetAlternateIDs();
	/// @see SetAlternateIDs
	const Array1D<ObjectOfInspectionModule::IdInfo>& GetAlternateIDs()const;
	/// Delete Other OOI IDs
	void DeleteObjectOfInspectionAlternateIDs();

	/// Set Algorithm Routing Code (Single Item Sequence) : Tag (4010, 1064), VR = SQ [required (Type 2), can be empty]
	///	Passed to the threat detection system to identify which algorithm to use on this scan.
	bool SetAlgorithmRoutingCode(const CodeSequence &csAlgorithmRoutingCode);
	/// @see SetAlgorithmRoutingCode
	bool GetAlgorithmRoutingCode(CodeSequence &csAlgorithmRoutingCode)const;
	/// Delete Algorithm Routing Code
	void DeleteAlgorithmRoutingCode();

	/// Set OOI Type : Tag (4010, 1042), VR = CS [required]
	bool SetType(const OBJECT_OF_INSPECTION_TYPE nType);
	/// @see SetType
	ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE GetType()const;
	/// @see SetType
	DcsString GetTypeAsString()const;

	/// Type Descriptor : Tag (4010, 1068), VR = LT [optional]
	/// Additional description for the set SDICOS::OBJECT_OF_INSPECTION_TYPE
	/// @see SetType
	bool SetTypeDescription(const DcsLongText &strDescription);
	/// @see SetTypeDescription
	DcsString GetTypeDescription()const;
	/// Delete OOI Type Descriptor
	void DeleteTypeDescription();

	/// Set Size in meters : Tag (4010, 1043), VR = FL, VM = 3 [optional]
	bool SetSizeInMeters(const float fHeight, const float fLength, const float fWidth);
	/// @see SetSizeInMeters
	bool GetSizeInMeters(float &fHeight, float &fLength, float &fWidth)const;
	/// Delete Size
	void DeleteSize();

	/// Bag Description : Tag (0060, 0022), VR = LT [optional]
	/// Additional description for the bag
	bool SetBagDescription(const DcsLongText &strDescription);
	/// @see SetBagDescription
	DcsString GetBagDescription()const;
	/// Delete Bag Description
	void DeleteBagDescription();

	/// Convert string to OBJECT_OF_INSPECTION_TYPE enumeration
	static OBJECT_OF_INSPECTION_TYPE ObjectOfInspectionTypeFromString(const DcsString& s);
protected:
	class ImplObjectOfInspectionModule;
	ImplObjectOfInspectionModule	*m_pImplObjectOfInspectionModule; ///< Internal implementation
};

}//namespace SDICOS

#endif
