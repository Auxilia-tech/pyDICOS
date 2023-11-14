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
#ifndef _STRATOVAN_DICOS_ACQUISITION_CONTEXT_MODULE_
#define _STRATOVAN_DICOS_ACQUISITION_CONTEXT_MODULE_

#include <ostream>

#include "SDICOS/Types.h"
#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/CodeSequence.h"

namespace SDICOS
{

///
/// \class AcquisitionContextSequence
/// Implements Acquisition Context Module
/// SPECREF V03 Section 14.2.7, Table 93
///
class AcquisitionContextSequence
{
public:
	/// Default Constructor
	AcquisitionContextSequence();

	/// Destructor
	~AcquisitionContextSequence();

	/// Copy Constructor
	AcquisitionContextSequence(const AcquisitionContextSequence &acquisitioncontextsequence);

	/// Reset to default values
	void FreeMemory();

	/// Assignment operator
	AcquisitionContextSequence& operator=(const AcquisitionContextSequence &acquisitioncontextsequence);

	/// Comparison operator
	bool operator==(const AcquisitionContextSequence &acquisitioncontextsequence)const;

	/// Comparison operator
	bool operator!=(const AcquisitionContextSequence &acquisitioncontextsequence)const;

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
	/// @return true/false		false is returned if any specified attributes were invalid.
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	///
	/// \class AcquisitionContextModule
	/// Item in Acquisition Context Sequence : Tag (0040, 0555), VR = SQ
	/// For multi-frame data this sequence can have multiple items.
	///
	class AcquisitionContextModule
	{
		friend class AcquisitionContextSequence;

	public:
		/// Constructor
		AcquisitionContextModule();

		/// Destructor
		~AcquisitionContextModule();

		/// Copy Constructor
		AcquisitionContextModule(const AcquisitionContextModule &acquisitioncontextmodule);

		/// Assignment operator
		AcquisitionContextModule& operator=(const AcquisitionContextModule &acquisitioncontextmodule);

		/// Reset to default values
		void FreeMemory();

		/// Comparison operator
		bool operator==(const AcquisitionContextModule &acquisitioncontextmodule) const;

		/// Output operator for human readable output
		friend std::ostream& operator<<(std::ostream &os, const AcquisitionContextModule &acquisitioncontextmodule);

		/// enumeration for the type of data described by this context module
		typedef enum
		{
			enumUnknownAcquisitionValueType, ///< Does not match defined terms

			enumText,		///< "TEXT"
			enumNumeric,	///< "NUMERIC"
			enumCode,		///< "CODE"
			enumDate,		///< "DATE"
			enumTime,		///< "TIME"
			enumPName,		///< "PNAME"

		} ACQUISITION_VALUE_TYPE;
		
		/// Value Type : Tag (0040, A040). Default value is enumUnknownAcquisitionValueType.
		///	@param nType Value Type : Tag (0040, A040) [optional] VR = CS
		bool SetValueType(const ACQUISITION_VALUE_TYPE nType);

		/// @see SetValueType
		ACQUISITION_VALUE_TYPE GetValueType()const;

		/// @see SetValueType
		/// @return DcsString described in definition of ACQUISITION_VALUE_TYPE.
		DcsString GetValueTypeAsString()const;

		/// @see SetValueType
		bool HasValueType()const;

		/// @see SetValueType
		/// Also deletes data associated with the Value Type
		/// e.g. if ValueType = Date, Also delete the date
		void DeleteValueType();

		/// Concept Name Code (Single Item Sequence) : Tag (0040, A043), VR = SQ [required]
		///	@param codesequence Concept Name Code Sequence
		///		i) Context ID not defined
		/// @return true/false false if the CodeSequence object is not valid
		bool SetConceptNameCode(const CodeSequence &codesequence);

		/// @see SetContextNameCode
		bool GetConceptNameCode(CodeSequence &codesequence)const;

		/// Set Referenced Frame Numbers : Tag (0040, A136)
		/// Since Type=1C (Conditional Required) use DeleteReferencedFrameNumbers() to unset.
		/// @param arrayFrameNumbers Array of Referenced Frame Numbers : Tag (0040, A136), VR = US [required if the "Acquisition Context Module" only applies to specific frames]
		///		i) Adds values to same tag (Ex. "Value1\Value2")
		///		ii) VM = nSize
		/// @return true/false  false if arrayFrameNumbers is empty
		bool SetReferencedFrameNumbers(const Array1D<S_UINT16> &arrayFrameNumbers);

		/// @see SetReferencedFrameNumbers
		bool GetReferencedFrameNumbers(Array1D<S_UINT16> &arrayFrameNumbers)const;

		/// @see SetReferenedFrameNumbers
		bool HasReferencedFrameNumbers()const;

		/// @see DeleteReferencedFrameNumbers
		void DeleteReferencedFrameNumbers();

		/// Set Numeric Value : Tag (0040, A30A)
		///	@param arrayValues Numeric Value : Tag (0040, A30A), VR = DS [required if "Concept Name Code" needs it]
		///		i) Adds values to same tag (Ex. "Value1\Value2")
		/// @return true/false
		bool SetNumericValues(const Array1D<float> &arrayValues);

		/// @see SetNumericValues
		bool GetNumericValues(Array1D<float> &arrayValues)const;

		/// @see SetNumericValues
		bool GetNumericValuesAsString(Array1D<DcsString> &arrayValues)const;

		/// Set Measurement Units Code (Single Item Sequence) : Tag (0040, 08EA), VR = SQ [required if "Numeric Value" is set]
		///	@param codesequence Measurement Units Code if Value Type is "NUMERIC"
		///		i) Baseline Context ID = 82
		///		ii) Coding Scheme Designator = UCUM (Unified Codes for Units of Measurement)
		/// @return true/false	false if Context ID and Coding Scheme Designator are not correct
		bool SetMeasurementUnitsCode(const CodeSequence &codesequence);

		/// @see GetMeasurementUnitsCode
		bool GetMeasurementUnitsCode(CodeSequence &codesquence)const;

		/// Set Date : Tag (0040, A121)
		///	@param strDate Date : Tag (0040, A121), VR = DA [required if "Concept Name Code" is a date]
		/// @return true/false	false if strDate is not valid
		bool SetDate(const DcsDate &strDate);

		/// @see SetDate
		DcsDate GetDate()const;

		/// Set Time : Tag (0040, A122)
		///	@param strTime Time : Tag (0040, A122), VR = TM [required if "Concept Name Code" is time]
		/// @return true/false false if strTime is not valid
		bool SetTime(const DcsTime &strTime);

		/// @see SetTime
		/// @return Empty string if value type is not enumTime
		DcsTime GetTime()const;

		/// Person's Name : Tag (0040, A123)
		///	@param strPersonName Person's Name : Tag (0040, A123), VR = PN [required if "Concept Name Code", Tag (0040, A043), is a person's name]
		/// @return true/false false if strPersonName is not valid
		bool SetPersonName(const DcsPersonName &strPersonName);

		/// @see SetPersonName
		DcsString GetPersonName()const;

		/// Set Text Value : Tag (0040, A160)
		///	@param strText Text Value : Tag (0040, A160), VR = UT [required if "Concept Name Code" needs extra text]
		/// @return true/false	false if strText is not valid
		bool SetTextValue(const DcsUnlimitedText &strText);

		/// @see SetTextValue
		DcsString GetTextValue()const;

		/// Set Concept Code Sequence (Single Item Sequence) : Tag (0040, A168), VR = SQ [required if "Numeric Value", "Measurement Units Code", "Date", "Time", "Person's Name", "Text Value" are not set]
		///	@param codesequence Concept Code Sequence
		///			1) Context ID not defined
		/// @return true/false	false if codesequence is not valid
		bool SetConceptCodeSequence(const CodeSequence &codesequence);

		/// @see SetConceptCodeSequence
		bool GetConceptCodeSequence(CodeSequence &codesequence)const;

	private:
		class ImplAcquisitionContext;
		ImplAcquisitionContext	*m_pImplAcquisitionContext; ///< Internal implementation

		ImplAcquisitionContext* GetImpl();
		const ImplAcquisitionContext* GetImpl()const;

		typedef AcquisitionContextSequence::AcquisitionContextModule::ImplAcquisitionContext AcqContModImpl;
	};

	/// Set Acquisition Context Sequence : Tag (0040, 0555), VR = SQ [required (type 2), can be NULL]
	///	@param arrayAcquisitionContext Array of AcquisitionContextModule objects
	/// @return true/false
	bool SetAcquisitionContext(const Array1D<AcquisitionContextModule> &arrayAcquisitionContext);

	/// @see SetAcquisitionContext
	bool GetAcquisitionContext(Array1D<AcquisitionContextModule> &arrayAcquisitionContext);

	/// @see SetAcquisitionContext
	Array1D<AcquisitionContextModule>& GetAcquisitionContext();
	/// @see SetAcquisitionContext
	const Array1D<AcquisitionContextModule>& GetAcquisitionContext()const;

	/// Acquisition Context Description : Tag (0040, 0556)
	///	@param strDescription Acquisition Context Description : Tag (0040, 0556), VR = ST [optional]
	/// @return true/false false if strDescription is not valid
	bool SetAcquisitionContextDescription(const DcsShortText &strDescription);

	/// @see SetAcquisitionContextDescription
	DcsString GetAcquisitionContextDescription()const;
		
private:
	class ImplAcquisitionContextSequence;
	ImplAcquisitionContextSequence	*m_pImplAcquisitionContextSequence; ///< Internal implementation

	ImplAcquisitionContextSequence* GetImpl();
	const ImplAcquisitionContextSequence* GetImpl() const;
};

}//namespace SDICOS

#endif
