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
#ifndef _STRATOVAN_DICOS_TDR_ADDITIONAL_INSPECTION_SELECTION_CRITERIA_H_
#define _STRATOVAN_DICOS_TDR_ADDITIONAL_INSPECTION_SELECTION_CRITERIA_H_

#include "SDICOS/IdentificationEncodingType.h"
#include "SDICOS/SecondaryInspectionCodeSequenceAIT.h"
#include "SDICOS/Array1D.h"

namespace SDICOS
{
namespace TDRTypes
{

/// 
/// \class AdditionalInspectionSelectionCriteria
/// Additional Inspection Selection Criteria Module
/// SPECREF V03 Section 12.2, Table 67
///
class AdditionalInspectionSelectionCriteria
{
public:
	/// Constructor
	AdditionalInspectionSelectionCriteria();
	
	/// Copy Constructor
	AdditionalInspectionSelectionCriteria(const AdditionalInspectionSelectionCriteria &aisc);
	
	/// Destructor
	~AdditionalInspectionSelectionCriteria();

	/// Reset internal data to a default state
	void FreeMemory();

	/// Assignment operator
	AdditionalInspectionSelectionCriteria& operator=(const AdditionalInspectionSelectionCriteria &aisc);
	
	/// Comparison operator
	bool operator==(const AdditionalInspectionSelectionCriteria &aisc)const;
	
	/// Comparison operator
	bool operator!=(const AdditionalInspectionSelectionCriteria &aisc)const;

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
	/// Enumeration for additional inspection selection criteria
	///
	typedef enum
	{
		enumUnknownAdditionalInspectionSelectionCriteria, ///< Does not match defined terms

		enumRandom,			///< "RANDOM"
		enumBehavioral,		///< "BEHAVIORAL"
		enumAll,			///< "ALL"
		enumOwnerRisk,		///< "OWNER_RISK"
		enumFlightRisk,		///< "FLIGHT_RISK"
		enumThreatLevel,	///< "THREAT_LEVEL"

	}ADDITIONAL_INSPECTION_SELECTION_CRITERIA;

	///
	/// Set Additional Screening Performed : Tag (4010, 106D)
	///	@param bAdditionalScreening Additional Screening Performed : Tag (4010, 106D), VR = CS [required]
	///			i) true = "YES", false = "NO"
	/// @return true/false
	bool SetAdditionalScreeningPerformed(const bool bAdditionalScreening);

	/// @see SetAdditionalScreeningPerformed
	bool GetAdditionalScreeningPerformed()const;

	/// @see SetAdditionalScreeningPerformed
	/// @return "YES" or "NO"
	DcsString GetAdditionalScreeningPerformedAsString()const;

	///
	/// Set Additional Inspection Selection Criteria : Tag (4010, 106E)
	/// @param nCriteria Additional Selection Criteria : Tag (4010, 106E), VR = CS [required if "Additional Screening Performed" is "YES"]
	///			i) Values: "RANDOM", "BEHAVIORAL", "ALL", "OWNER_RISK", "FLIGHT_RISK", "THREAT_LEVEL"
	/// @return true/false
	bool SetAdditionalInspectionSelectionCriteria(const ADDITIONAL_INSPECTION_SELECTION_CRITERIA nCriteria);

	/// @see SetAdditionalInspectionSelectionCriteria
	ADDITIONAL_INSPECTION_SELECTION_CRITERIA GetAdditionalInspectionSelectionCriteria()const;

	/// @see SetAdditionalInspectionSelectionCriteria
	DcsString GetAdditionalInspectionSelectionCriteriaAsString()const;

	/// Clear so that data is not written to the DICOS file
	void DeleteAdditionalInspectionSelectionCriteria();
	
	///
	/// Set Additional Inspection Method Sequence : Tag (4010, 106F), VR = SQ [required if "Additional Inspection Selection Criteria" (4010, 106E) is "RANDOM" and "TDR Type" (4010, 1027) is "MACHINE"] 
	///	@param arrayInspectionMethods Inspection Methods
	///			i) Baseline Context ID = "DCS3"
	/// @return true/false
	///
	bool SetInspectionMethods(const Array1D<AitSecondaryInspectionCodeSequence> &arrayInspectionMethods);

	/// @see SetInspectionMethods
	bool GetInspectionMethods(Array1D<AitSecondaryInspectionCodeSequence> &arrayInspectionMethods)const;

	/// Delete inspection methods so that they are not written to the DICOS file
	void DeleteInspectionMethods();
	
protected:
	class ImplAdditionalInspectionSelectionCriteria;
	ImplAdditionalInspectionSelectionCriteria	*m_pImplAdditionalInspectionSelectionCriteria; ///< Internal implementation
	
	ImplAdditionalInspectionSelectionCriteria* GetImpl();
	const ImplAdditionalInspectionSelectionCriteria* GetImpl() const;
};

}//namespace TDRTypes
}//namespace SDICOS

#endif
