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
#ifndef _STRATOVAN_DICOS_GENERAL_SCAN_MODULE_H_
#define _STRATOVAN_DICOS_GENERAL_SCAN_MODULE_H_

#include "SDICOS/String.h"
#include "SDICOS/SopInstanceReference.h"
#include "SDICOS/ExternalReferencesMacro.h"

namespace SDICOS
{

///
/// \class GeneralScanModule
/// \brief Implements General Scan Module
/// SPECREF V03 Section 5.1, Table 15
/// 
class GeneralScanModule
{
public:
	/// Constructor
	GeneralScanModule();
	/// Copy constructor
	GeneralScanModule(const GeneralScanModule &generalscanmodule);
	/// Destructor
	virtual ~GeneralScanModule();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	GeneralScanModule& operator=(const GeneralScanModule &generalscanmodule);
	/// Comparison operator
	bool operator==(const GeneralScanModule &generalscanmodule)const;
	/// Comparison operator
	bool operator!=(const GeneralScanModule &generalscanmodule)const;

	/// Scan type enumerations
	typedef enum
	{
		enumUnknownScanType, ///< Unknown enumeration

		enumOperational,	///< "OPERATIONAL"
		enumNonOperational,	///< "NON_OPERATIONAL"

	}SCAN_TYPE;

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

	/// Set Scan Instance UID : Tag (0020, 000D), VR = UI [required]
	bool SetScanInstanceUID(const DcsUniqueIdentifier &strScanUID);
	/// @see SetScanInstanceUID
	DcsString GetScanInstanceUID()const;

	/// Set Start Date and Time
	/// @param strDate Date : Tag (0008, 0020), VR = DA [required]
	/// @param strTime Time : Tag (0008, 0030), VR = TM [required]
	bool SetStartDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetStartDateAndTime
	DcsDate GetStartDate()const;
	/// @see SetStartDateAndTime
	DcsTime GetStartTime()const;

	/// Set Type : Tag (4010, 1048), VR = CS [required]
	bool SetType(const SCAN_TYPE nScanType);
	/// @see SetType
	SCAN_TYPE GetType()const;
	/// @see SetType
	DcsString GetTypeAsString()const;

	/// Set Description : Tag (0008, 1030), VR = LO [optional]
	bool SetDescription(const DcsLongString &strScanDescription);
	/// @see SetDescription
	DcsString GetDescription()const;
	/// Delete Description
	void DeleteDescription();

	/// Set Referenced Scan Sequence : Tag (0008, 1110), VR = SQ [required if Modality (0008, 0060) is TDR]
	bool SetReferencedScans(const Array1D<SopInstanceReference> &arrayReferenceScans);
	/// @see SetReferencedScans
	bool GetReferencedScans(Array1D<SopInstanceReference> &arrayReferenceScans)const;
	/// Returns referenced scans. If HasReferencedScans() returned false before calling this function, it will return true afterwards
	/// even if no elements are added.
	/// @see SetReferencedScans
	/// @see HasReferencedScans
	Array1D<SopInstanceReference>& GetReferencedScans();
	/// @see SetReferencedScans
	const Array1D<SopInstanceReference>& GetReferencedScans()const;
	/// @return true/false if Referenced scans is present
	bool HasReferencedScans()const;
	/// Delete Referenced Scan Sequence
	/// @see HasReferencedScans
	void DeleteReferencedScans();

	/// Scan ID : Tag (0020, 0010), VR = SH [required]
	bool SetScanID(const DcsShortString &strID);
	/// @see SetScanID
	DcsString GetScanID()const;

	/// Total number of views for this scan : Tag (6100, 0028), VR = US [optional]
	bool SetNumberOfViews(const S_UINT16& nNum);
	/// @see SetNumberOfViews
	S_UINT16 GetNumberOfViews()const;
	/// Returns true if value is set
	bool HasNumberOfViews()const;
	/// Delete data
	void DeleteNumberOfViews();

	/// Total number of energies for this scan : Tag (6100, 0032), VR = US [optional]
	bool SetNumberOfEnergies(const S_UINT16& nNum);
	/// @see SetNumberOfEnergies
	S_UINT16 GetNumberOfEnergies()const;
	/// Returns true if value is set
	bool HasNumberOfEnergies()const;
	/// Delete data
	void DeleteNumberOfEnergies();

protected:
	class ImplGeneralScan;
	ImplGeneralScan	*m_pImplGeneralScan; ///< Internal implementation
	ImplGeneralScan* GetImpl();
	const ImplGeneralScan* GetImpl()const;
};

}//namespace SDICOS

#endif