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
#ifndef _STRATOVAN_DICOS_SCANNER_COMMON_H_
#define _STRATOVAN_DICOS_SCANNER_COMMON_H_

#include "SDICOS/ObjectOfInspectionOwnerModule.h"
#include "SDICOS/ObjectOfInspectionModule.h"
#include "SDICOS/ItineraryModule.h"
#include "SDICOS/GeneralScanModule.h"
#include "SDICOS/SopCommonModule.h"
#include "SDICOS/CommonInstanceReferenceModule.h"
#include "SDICOS/GeneralEquipmentModule.h"

namespace SDICOS
{

///
/// \class ScannerCommon
/// \brief Implements a common set of modules
/// 
class ScannerCommon
{
public:
	/// Constructor
	ScannerCommon();
	/// Copy constructor
	ScannerCommon(const ScannerCommon &scannercommon);
	/// Destructor
	virtual ~ScannerCommon();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	ScannerCommon& operator=(const ScannerCommon &scannercommon);
	/// Comparison operator
	bool operator==(const ScannerCommon &scannercommon)const;
	/// Comparison operator
	bool operator!=(const ScannerCommon &scannercommon)const;

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

	/// Object Of Inspection Owner [optional]
	virtual bool SetObjectOfInspectionOwner(const ObjectOfInspectionOwnerModule &owner);
	/// @see SetObjectOfInspectionOwner
	bool GetObjectOfInspectionOwner(ObjectOfInspectionOwnerModule &owner)const;
	/// Allocate Object Of Inspection Owner
	void AllocateObjectOfInspectionOwner();
	/// Get the Object Of Inspection Owner
	ObjectOfInspectionOwnerModule* GetObjectOfInspectionOwner();
	/// @see SetObjectOfInspectionOwner
	const ObjectOfInspectionOwnerModule* GetObjectOfInspectionOwner()const;
	/// Delete Object Of Inspection Owner Module
	void DeleteObjectOfInspectionOwnerModule();

	/// Object of Inspection [required]
	virtual bool SetObjectOfInspection(const ObjectOfInspectionModule &objectofinspection);
	/// @see SetObjectOfInspection
	bool GetObjectOfInspection(ObjectOfInspectionModule &objectofinspection)const;
	/// @see SetObjectOfInspection
	ObjectOfInspectionModule& GetObjectOfInspection();
	/// @see SetObjectOfInspection
	const ObjectOfInspectionModule& GetObjectOfInspection()const;

	/// Itinerary [optional]
	virtual bool SetItinerary(const ItineraryModule &itinerary);
	/// @see SetItinerary
	bool GetItinerary(ItineraryModule &itinerary)const;
	/// Allocate Itinerary
	void AllocateItinerary();
	/// Get the itinerary
	ItineraryModule* GetItinerary();
	/// @see SetItinerary
	const ItineraryModule* GetItinerary()const;
	/// Delete Itinerary
	void DeleteItinerary();

	/// General Scan [required]
	virtual bool SetGeneralScan(const GeneralScanModule &generalscan);
	/// @see SetGeneralScan
	bool GetGeneralScan(GeneralScanModule &generalscan)const;
	/// @see SetGeneralScan
	GeneralScanModule& GetGeneralScan();
	/// @see SetGeneralScan
	const GeneralScanModule& GetGeneralScan()const;

	/// General Equipment [required]
	virtual bool SetGeneralEquipment(const GeneralEquipmentModule &generalequipment);
	/// @see SetGeneralEquipment
	bool GetGeneralEquipment(GeneralEquipmentModule &generalequipment)const;
	/// @see SetGeneralEquipment
	GeneralEquipmentModule& GetGeneralEquipment();
	/// @see SetGeneralEquipment
	const GeneralEquipmentModule& GetGeneralEquipment()const;

	/// SOP Common [required]
	virtual bool SetSopCommon(const SopCommonModule &sopcommon);
	/// @see SetSopCommon
	bool GetSopCommon(SopCommonModule &sopcommon)const;
	/// @see SetSopCommon
	SopCommonModule& GetSopCommon();
	/// @see SetSopCommon
	const SopCommonModule& GetSopCommon()const;

	/// Common Instance Reference [required if references are used]
	virtual bool SetCommonInstanceReference(const CommonInstanceReferenceModule &commoninstancereference);
	/// @see SetCommonInstanceReference
	bool GetCommonInstanceReference(CommonInstanceReferenceModule &commoninstancereference)const;
	/// @see SetCommonInstanceReference
	CommonInstanceReferenceModule& GetCommonInstanceReference();
	/// @see SetCommonInstanceReference
	const CommonInstanceReferenceModule& GetCommonInstanceReference()const;

protected:
	class ImplScannerCommon;
	ImplScannerCommon	*m_pImplScannerCommon; ///< Internal implementation
};

}//namespace SDICOS

#endif