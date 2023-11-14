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
#ifndef _STRATOVAN_DICOS_ASSESSMENT_SEQUENCE_H_
#define _STRATOVAN_DICOS_ASSESSMENT_SEQUENCE_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{
namespace TDRTypes
{

///
/// \class AssessmentSequence
/// \brief Implements Assessment Sequence (4010, 1038), a required sequence
/// SPECREF V03 Section 12.5, Table 70
///
class AssessmentSequence
{
public:
	/// Constructor
	AssessmentSequence();
	/// Copy constructor
	AssessmentSequence(const AssessmentSequence& as);
	/// Destructor
	~AssessmentSequence();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	AssessmentSequence& operator=(const AssessmentSequence& as);
	/// Comparison operator
	bool operator==(const AssessmentSequence& as)const;
	/// Comparison operator
	bool operator!=(const AssessmentSequence& as)const;

	///
	/// \class AssessmentItem
	/// \brief Implements an item in Assessment Sequence
	///
	class AssessmentItem
	{
	public:
		/// Constructor
		AssessmentItem();
		/// Copy constructor
		AssessmentItem(const AssessmentItem &item);
		/// Destructor
		~AssessmentItem();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		AssessmentItem& operator=(const AssessmentItem &item);
		/// Comparison operator
		bool operator==(const AssessmentItem &item)const;
		/// Comparison operator
		bool operator!=(const AssessmentItem &item)const;

		/// Threat category enumeration
		typedef enum
		{
			enumUnknownThreatCategory,	///< Does not match defined terms

			enumExplosive,		 ///< "EXPLOSIVE"
			enumProhibitedItem,	 ///< "PI"
			enumContraband,		 ///< "CONTRABAND"
			enumAnomaly,		 ///< "ANOMALY"
			enumLaptop,			 ///< "LAPTOP"
			enumOther,			 ///< "OTHER"
			enumPharmaceutical,	 ///< "PHARMACEUTICAL"

		}THREAT_CATEGORY;
		
		/// Ability assessment enumeration
		typedef enum
		{
			enumUnknownAbilityAssessment,	///< Does not match defined terms

			enumNoInterference,	///< "NO_INTERFERENCE"
			enumShield,			///< "SHIELD"

		}ABILITY_ASSESSMENT;

		/// Assessment flag enumeration
		typedef enum
		{
			enumUnknownAssessmentFlag,	///< Does not match defined terms

			enumHighThreat,	///< "HIGH_THREAT"
			enumThreat,		///< "THREAT"
			enumNoThreat,	///< "NO_THREAT", 
			enumUnknown,	///< "UNKNOWN"

		}ASSESSMENT_FLAG;

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
		/// @return true/false		false is returned if any specified attributes were invalid
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

		/// Threat Category : Tag (4010, 1012), VR = CS [required if "TDR Type", tag (4010, 1027), is "MACHINE"]
		bool SetThreatCategory(const THREAT_CATEGORY nThreatCategory);		
		/// @see SetThreatCategory
		THREAT_CATEGORY GetThreatCategory()const;		
		/// @see SetThreatCategory
		DcsString GetThreatCategoryAsString()const;		

		/// Threat Category Description : Tag (4010, 1013), VR = LT [optional]
		/// Additional descriptor for threat category
		bool SetThreatCategoryDescription(const DcsLongText &strDescription);		
		/// @see SetThreatCategoryDescription
		DcsString GetThreatCategoryDescription()const;
		/// @see SetThreatCategoryDescription
		void DeleteThreatCategoryDescription();

		/// Ability Assessment : Tag (4010, 1014), VR = CS [required]
		bool SetAbilityAssessment(const ABILITY_ASSESSMENT nAbilityAssessment);	
		/// @see SetAbilityAssessment
		ABILITY_ASSESSMENT GetAbilityAssessment()const;	
		/// @see SetAbilityAssessment
		DcsString GetAbilityAssessmentAsString()const;	

		/// Assessment Flag : Tag (4010, 1015), VR = CS [required]
		bool SetAssessmentFlag(const ASSESSMENT_FLAG nAssessmentFlag);		
		/// @see SetAssessmentFlag
		ASSESSMENT_FLAG GetAssessmentFlag()const;		
		/// @see SetAssessmentFlag
		DcsString GetAssessmentFlagAsString()const;		

		/// Assessment Probability : Tag (4010, 1016), VR = FL [optional]
		/// @param fAssessmentProbability Percentage value between 0.0 and 1.0
		bool SetAssessmentProbability(const float fAssessmentProbability);			
		/// @see SetAssessmentProbability
		float GetAssessmentProbability()const;
		/// @see SetAssessmentProbability
		void DeleteAssessmentProbability();

	protected:
		class ImplAssessmentItem;
		ImplAssessmentItem	*m_pImplAssessmentItem; ///< Internal implementation
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
	/// @return true/false		false is returned if any specified attributes were invalid
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

	/// Assessment Sequence : Tag (4010, 1038), VR = SQ [required]
	bool SetAssessment(const Array1D<AssessmentItem> &arrayAssessment);
	/// @see SetAssessment
	bool GetAssessment(Array1D<AssessmentItem> &arrayAssessment)const;
	/// @see SetAssessment
	Array1D<AssessmentItem>& GetAssessment();
	/// @see SetAssessment
	const Array1D<AssessmentItem>& GetAssessment()const;

	/// @see SetAssessment
	bool AddAssessmentItem(const AssessmentItem& );
	
protected:
	class ImplAssessmentSequence;
	ImplAssessmentSequence	*m_pImplAssessmentSequence; ///< Internal implementation
};

}//namespace TDRTypes
}//namespace SDICOS

#endif
