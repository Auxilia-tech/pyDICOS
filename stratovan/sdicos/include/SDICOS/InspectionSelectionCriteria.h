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
#ifndef _STRATOVAN_DICOS_INSPECTION_SELECTION_CRITERIA_H_
#define _STRATOVAN_DICOS_INSPECTION_SELECTION_CRITERIA_H_

#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/SecondaryInspectionCodeSequenceAIT.h"

namespace SDICOS
{

///
/// \class InspectionSelectionCriteria
/// Inspection Selection Criteria
/// SPECREF V03 Section 14.6, Table 102
///
class InspectionSelectionCriteria
{
public:
	/// Constructor
	InspectionSelectionCriteria();
	
	/// Copy Constructor
	InspectionSelectionCriteria(const InspectionSelectionCriteria &inspectionselectioncriteria);

	/// Destructor
	~InspectionSelectionCriteria();
	
	/// Assignment operator
	InspectionSelectionCriteria& operator=(const InspectionSelectionCriteria &inspectionselectioncriteria);

	/// Comparison operator
	bool operator==(const InspectionSelectionCriteria &inspectionselectioncriteria)const;

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

	/// Determine if all attributes are properly set
	/// @return true/false
	bool IsValid() const;
	
	/// Reset all data members to default values
	virtual void FreeMemory();
	
	///
	/// Enumeration for Inspection Selection Criteria
	///
	typedef enum
	{
		enumUnknownInspectionSelectionCriteria,	///< Does not match defined Code Values

		enumRandom,		///< "RANDOM"
		enumBehavioral,	///< "BEHAVIORAL"
		enumAll,		///< "ALL"

	}INSPECTION_SELECTION_CRITERIA;

	///
	/// Set Inspection Selection Criteria
	/// @param nInspectionSelectionCriteria Inspection Selection Criteria : Tag (4010, 107C), VR = CS [required]
	///			i) Values: "RANDOM", "BEHAVIORAL", "ALL"
	/// @return true/false
	///
	bool SetInspectionSelectionCriteria(const INSPECTION_SELECTION_CRITERIA nInspectionSelectionCriteria);

	/// @see SetInspectionSelectionCriteria
	INSPECTION_SELECTION_CRITERIA GetInspectionSelectionCriteria()const;

	/// @see SetInspectionSelectionCriteria
	/// @return Is inspection selection criteria
	DcsString GetInspectionSelectionCriteriaAsString()const;
	
	///
	/// Set Secondary Inspection Method : Tag (4010, 107D), VR = SQ [required if "Inspection Selection Criteria" is "RANDOM" and "TDR Type" (4010, 1027) is "MACHINE"]
	/// @param arraySecondaryInspectionMethods Code Sequence struct
	///			i) Context ID = DCS3
	/// @return true/false
	///
	bool SetSecondaryInspectionMethod(const Array1D<AitSecondaryInspectionCodeSequence> &arraySecondaryInspectionMethods);

	/// @see SecondaryInspectionMethod
	bool GetSecondaryInspectionMethod(Array1D<AitSecondaryInspectionCodeSequence> &arraySecondaryInspectionMethods)const;

	/// @see SecondaryInspectionMethod
	Array1D<AitSecondaryInspectionCodeSequence>& GetSecondaryInspectionMethod();
	/// @see SecondaryInspectionMethod
	const Array1D<AitSecondaryInspectionCodeSequence>& GetSecondaryInspectionMethod()const;

	/// Clear the data so that it is not written to the DICOS file.
	void DeleteSecondaryInspectionMethod();
	
private:
	class ImplInspectionSelectionCriteria;
	ImplInspectionSelectionCriteria	*m_pImplInspectionSelectionCriteria; ///< Internal implementation
	
	ImplInspectionSelectionCriteria* GetImpl();
	const ImplInspectionSelectionCriteria* GetImpl() const;
};

}//namespace SDICOS

#endif
