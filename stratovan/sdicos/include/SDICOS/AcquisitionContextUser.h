//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2022 Stratovan Corporation. All Rights Reserved.
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

#ifndef _STRATOVAN_DICOS_USER_ACQUISITION_CONTEXT_H_
#define _STRATOVAN_DICOS_USER_ACQUISITION_CONTEXT_H_

#include "SDICOS/AcquisitionContextModule.h"

namespace SDICOS
{

class AcquisitionContextValue
{
public:
    /// Default Constructor
    AcquisitionContextValue();
    
    /// Destructor
    ~AcquisitionContextValue();

    /// Copy Constructor
    AcquisitionContextValue(const AcquisitionContextValue &av);

    /// Reset to default values
    void FreeMemory();

    /// Assignment operator
    AcquisitionContextValue& operator=(const AcquisitionContextValue &av);

    /// Comparison operator
    bool operator==(const AcquisitionContextValue &av)const;
    /// Comparison operator
    bool operator!=(const AcquisitionContextValue &av)const;

    /// Read values from parameter
    virtual bool Read(const AcquisitionContextSequence::AcquisitionContextModule &ac, ErrorLog &errorlog);
    /// Write values to parameter
    virtual bool Write(AcquisitionContextSequence::AcquisitionContextModule &ac, ErrorLog &errorlog)const;

    /// @brief Set the Value Type (0040, A040), VR = CS [optional]
    /// @param nType Value type to be sets
    /// @return true if Value type was valid and successfully set, false otherwise
    bool SetType(AcquisitionContextSequence::AcquisitionContextModule::ACQUISITION_VALUE_TYPE nType);

    /// @brief Check if the Acquisition Context Value Type is "TEXT"
    /// @return true if Value Type is "TEXT", false otherwise
    bool IsText()const;
    /// @brief Check if the Acquisition Context Value Type is "NUMERIC"
    /// @return true if Value Type is "NUMERIC", false otherwise
    bool IsNumeric()const;
    /// @brief Check if the Acquisition Context Value Type is "CODE"
    /// @return true if Value Type is "CODE", false otherwise
    bool IsCode()const;
    /// @brief Check if the Acquisition Context Value Type is "DATE"
    /// @return true if Value Type is "DATE", false otherwise
    bool IsDate()const;
    /// @brief Check if the Acquisition Context Value Type is "TIME"
    /// @return true if Value Type is "TIME", false otherwise
    bool IsTime()const;
    /// @brief Check if the Acquisition Context Value Type is "PNAME"
    /// @return true if Value Type is "PNAME", false otherwise
    bool IsPersonName()const;
    /// @brief Check if the Value Type has been set
    bool HasType()const;

    /// @brief delete the Value Type if it has been set
    /// Also deletes the Associated data, e.g. if Value Type = DATE delete the date
    void DeleteType();

    /// @brief Concept Name Code Tag (0040, A043), VR = SQ [required]
    /// @param strName  Code Value for Concept Name
    /// @param strNameMeaning Human readable Code Meaning for Concept Name
    /// @param strNameDesignator Code Designator for Concept Name
    /// @return true/false False if the Concent Name Code is not set
    bool SetConceptNameCode(const DcsShortString &strName, const DcsLongString &strNameMeaning, const DcsShortString &strNameDesignator);
    /// @see SetConceptNameCode
    bool GetConceptNameCode(DcsShortString &strName, DcsLongString &strNameMeaning, DcsShortString &strNameDesignator)const;

	/// Set Referenced Frame Numbers : Tag (0040, A136) [required if the Acquisition Context only applies to specific frames]
    /// @param arrayFrameNumbers Array of Referenced Frame Numbers
    /// @return true/false False if arrayFrameNumbers is empty
    bool SetReferencedFrameNumbers(const Array1D<S_UINT16> &arrayFrameNumbers);
    /// @see SetReferenceFrameNumbers 
    bool GetReferencedFrameNumbers(Array1D<S_UINT16> &arrayFrameNumbers)const;
    /// Check if the Referenced Frame Numbers have been set
    /// @return True if Referenced Frame Numbers is set, false otherwise
    bool HasReferencedFrameNumbers()const;
    /// Delete the Referenced Frame Numbers
    void DeleteReferencedFrameNumbers();

    /// Set Numeric Value : Tag (0040, A30A) [required if Value Type is NUMERIC]
    ///	@param arrayValues Array of Numeric Values
    /// @return true/false
    bool SetNumericValues(const Array1D<float> &arrayValues);
    /// @see SetNumericValues
    bool GetNumericValues(Array1D<float> &arrayValues)const;

    /// Set Measurement Units Code : Tag (0040, 08EA), VR = SQ [required if Value Type is NUMERIC]
    ///	@param strUnits Code Value for the units of measurement
    /// @param strUnitsMeaning Human readable Code Meaning for the units of measurements
    /// @param strUnitsMappingResource Mapping Resource for the units of measurements
    /// @param strContextGroupVersion Version used for the Context Group for the measurements
    /// @return true/false False if Measurements Unit is not set
    bool SetMeasurementUnits(const DcsShortString &strUnits, const DcsLongString &strUnitsMeaning, const DcsCodeString &strUnitsMappingResource, const DcsDateTime &strContextGroupVersion);
    /// @see SetMeasurementUnits
    bool GetMeasurementUnits(DcsShortString &strUnits, DcsLongString &strUnitsMeaning, DcsCodeString &strUnitsMappingResource, DcsDateTime &strContextGroupVersion)const;


    /// Set Date : Tag (0040, A121), VR = DA [required if Value Type is DATE]
    ///	@param strDate Date for the Acquisition Context
    /// @return true/false False if strDate is not valid
    bool SetDate(const DcsDate &strDate);
    /// @see SetDate
    bool GetDate(DcsDate &strDate)const;

    /// Set Time : Tag (0040, A122), VR = TM [required if Value Type is TIME]
    ///	@param strTime Time for the Acquisition Context
    /// @return true/false False if strTime is not valid
    bool SetTime(const DcsTime &strTime);
    /// @see SetTime
    bool GetTime(DcsTime &strTime)const;

    ///Person's Name : Tag (0040, A123), VR = PN [required if Value Type is PNAME]
    ///	@param strPersonName Person's Name for the Acquisition Context
    /// @return true/false False if strPersonName is not valid
    bool SetPersonName(const DcsPersonName &strPersonName);
    /// @see SetPersonName
    bool GetPersonName(DcsPersonName &strPersonName)const;

    /// Set Text Value : Tag (0040, A160), VR = UT [required if Value Type is TEXT]
    ///	@param strText Text Value for the Acquisition Contextf
    /// @return true/false False if strText is not valid
    bool SetTextValue(const DcsUnlimitedText &strText);
    /// @see SetTextValue
    bool GetTextValue(DcsUnlimitedText &strText)const;

    /// Set Concept Code Sequence : Tag (0040, A168), VR = SQ [required if Value Type is not set]
    ///	@param strCodeValue Code Value for the Concept Code Sequence
    /// @param strCodeMeaning Human readable Code Meaning for the Concept Code Sequence
    /// @param strCodeDesignator Code Designator for the Concept Code Sequence
    /// @return true/false False if Concept Code Sequence is not set
    bool SetConceptCodeSequence(const DcsShortString &strCodeValue, const DcsLongString &strCodeMeaning, const DcsShortString &strCodeDesignator);
    /// @see SetConceptCodeSequence
    bool GetConceptCodeSequence(DcsShortString &strCodeValue, DcsLongString &strCodeMeaning, DcsShortString &strCodeDesignator)const;

    /// @brief Check if the AcquisitionContextValue object contains all of the required values
    /// @return true/false True if the AcquisitionContextValue is valid, false otherwise
    bool IsValid()const;

protected:
    class ImplAcquisitionContextValue;
    ImplAcquisitionContextValue *m_pImplAcquisitionContextValue;
}; //class AcquisitionContextValue

class AcquisitionContextUser
{
public:

    /// Default Constructor
    AcquisitionContextUser();
    
    /// Destructor
    ~AcquisitionContextUser();

    /// Copy Constructor
    AcquisitionContextUser(const AcquisitionContextUser &ac);

    /// Reset to default values
    void FreeMemory();

    /// Assignment operator
    AcquisitionContextUser& operator=(const AcquisitionContextUser &ac);

    /// Comparison operator
    bool operator==(const AcquisitionContextUser &ac)const;
    /// Comparison operator
    bool operator!=(const AcquisitionContextUser &ac)const;

    /// Read values from parameters
    virtual bool Read(const AcquisitionContextSequence &acs, ErrorLog &errorlog);
    /// Write values to parameters
    virtual bool Write(AcquisitionContextSequence &acs, ErrorLog &errorlog)const;

    /// Add an AcquisitionContext object with values set by the AcquisitionContextValue
    /// @param av AcquisitionContextValue object to be added
    /// @returns Index of the added object if it was successfully added, else -1
    int AddAcquisitionContextValue(const AcquisitionContextValue &av);

    /// Add an AcquisitionContext object of type "NUMERIC"
    /// @param strName Code Name for the Concept Name
    /// @param strNameMeaning Human readable Code Meaning for the Concept Name
    /// @param strNameDesignator Code Designator for the Concept Name
    /// @param arrayValues Array of numeric values for the Acquisition Context
    /// @param strUnits Code Name for the Measurement Units
    /// @param strUnitsMeaning Human readable Code Meaning for the Measurement Units
    /// @param strUnitsMappingResource Mapping Resource for the Measurement Units
    /// @param strContextGroupVersion Version for the Context Group for the Measurement Units
    /// @return Index of the added object if it was successfully added, else -1
    int AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, const DcsShortString &strNameDesignator, const Array1D<float> &arrayValues, const DcsShortString &strUnits, const DcsLongString &strUnitsMeaning, const DcsCodeString &strUnitsMappingResource, const DcsDateTime& strContextGroupVersion);

    /// Add an AcquisitionContext object of Type "DATE"
    /// @param strName Code Name for the Concept Name
    /// @param strNameMeaning Human readable Code Meaning for the Concept Name
    /// @param strNameDesignator Code Designator for the Concept Name
    /// @param strDate Date for the Acquisition Context
    /// @return Index of the added object if it was successfully added, else -1
    int AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, const DcsShortString &strNameDesignator, const DcsDate &strDate);

    /// Add an AcquisitionContext object of Type "TIME"
    /// @param strName Code Name for the Concept Name
    /// @param strNameMeaning Human readable Code Meaning for the Concept Name
    /// @param strNameDesignator Code Designator for the Concept Name 
    /// @param strTime Time for the Acquisition Context
    /// @return Index of the added object if it was successfully added, else -1
    int AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, const DcsShortString &strNameDesignator, const DcsTime &strTime);

    /// Add an AcquisitionContext object of Type "PNAME"
    /// @param strName Code Name for the Concept Name
    /// @param strNameMeaning Human readable Code Meaning for the Concept Name
    /// @param strNameDesignator Code Designator for the Concept Name 
    /// @param strPersonName Person Name for the Acquisition Context
    /// @return Index of the added object if it was successfully added, else -1
    int AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, const DcsShortString &strNameDesignator, const DcsPersonName &strPersonName);
    
    /// Add an AcquisitionContext object of Type "TEXT"
    /// @param strName Code Name for the Concept Name
    /// @param strNameMeaning Human readable Code Meaning for the Concept Name
    /// @param strNameDesignator Code Designator for the Concept Name 
    /// @param strText Text value for the Acquisition Context
    /// @return Index of the added object if it was successfully added, else -1
    int AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, const DcsShortString &strNameDesignator, const DcsUnlimitedText &strText);

    /// Add an AcquisitionContext object with no Value Type
    /// @param strName Code Name for the Concept Name
    /// @param strNameMeaning Human readable Code Meaning for the Concept Name
    /// @param strNameDesignator Code Designator for the Concept Name 
    /// @param strConcept Code Name for the Concept Code
    /// @param strConceptMeaning Human readable Code Meaning for the Concept Code
    /// @param strConceptDesignator Code Designator for the Concept Code
    /// @return Index of the added object if it was successfully added, else -1
    int AddAcquisitionContextValue(const DcsShortString &strName, const DcsLongString &strNameMeaning, const DcsShortString &strNameDesignator, const DcsShortString &strConcept, const DcsLongString &strConceptMeaning, const DcsShortString &strConceptDesignator);

    /// Get the Concept Name Code for the AcquisitionContextValue object at the given index value
    /// @param index Index of the AcquisitionContextValue object to get the Concept Name Code from
    /// @param strName String to store the Concept Name Code Value to
    /// @param strNameMeaning String to store the Concept Name Code Meaning to
    /// @param strNameDesignator String to store the Concept Name Designator to
    /// @return True if the Concept Name Code values are successfully saved to the parameters, false otherwise
    bool GetConceptName(SDICOS::S_UINT32 index, DcsShortString &strName, DcsLongString &strNameMeaning, DcsShortString &strNameDesignator)const;

    /// Get the Numeric Values for the AcquisitionContextValue object at the given index if it is Numeric
    /// @param index Index of the AcquisitionContextValue object to get the numeric values from
    /// @param arrayValues Array to store the numeric values to
    /// @return True if the AcquisitionContextValue at the given index is numeric and the values are saved to the parameter, false otherwise
    bool GetNumericValues(SDICOS::S_UINT32 index, Array1D<float> &arrayValues)const;

    /// Get the Measurement Unit values for the AcquisitionContextValue object at the given index if it is Numeric
    /// @param index Index of the AcquisitionContextValue object to get the Measurement Unit values from
    /// @param strUnits String to store the Measurement Units Code Value to
    /// @param strUnitsMeaning String to store the Measurement Units Meaning to
    /// @param strUnitsMappingResource String to store the Measurement Units Mapping Resource to
    /// @param strContextGroupVersion String to store the Context Group Version to
    /// @return True if the AcquisitionContextValue at the given index is numeric and the values are saved to the parameters, false otherwise
    bool GetMeasurementUnits(SDICOS::S_UINT32 index, DcsShortString &strUnits, DcsLongString &strUnitsMeaning, DcsCodeString &strUnitsMappingResource, DcsDateTime &strContextGroupVersion)const;

    /// Get the Date value for the AcquisitionContextValue object at the given index if it is a Date
    /// @param index Index of the AcquisitionContextValue object to get the Date from
    /// @param strDate String to store the date to
    /// @return True if the AcquisitionContextValue at the given index is a date and the values are saved to the parameter, false otherwise
    bool GetDate(SDICOS::S_UINT32 index, DcsDate &strDate)const;

    /// Get the Time value for the AcquisitionContextValue object at the given index if it is a Time
    /// @param index Index of the AcquisitionContextValue object to get the Time from
    /// @param strTime String to store the time to
    /// @return True if the AcquisitionContextValue at the given index is a time and the values are saved to the parameter, false otherwise
    bool GetTime(SDICOS::S_UINT32 index, DcsTime &strTime)const;

    /// Get the Person Name for the AcquisitionContextValue object at the given index if it is a Person Name
    /// @param index Index of the AcquisitionContextValue object to get the Person Name from
    /// @param strPersonName String to store the Person Name to
    /// @return True if the AcquisitionContextValue at the given index is a Person Name and the values are saved to the parameter, false otherwise
    bool GetPersonName(SDICOS::S_UINT32 index, DcsPersonName &strPersonName)const;

    /// Get the Text value for the AcquisitionContextValue object at the given index if it is Text
    /// @param index Index of the AcquisitionContextValue object to get the Text from
    /// @param strText String to store the Text to
    /// @return True if the AcquisitionContextValue at the given index is Text and the values are saved to the parameter, false otherwise
    bool GetText(SDICOS::S_UINT32 index, DcsUnlimitedText &strText)const;

    /// Get the Concept Code for the AcquisitionContextValue object at the given index if it has one
    /// @param index Index of the AcquisitionContextValue object to get the Concept Code from
    /// @param strConceptValue String to store the Concept Code Value to
    /// @param strConceptMeaning String to store the Concept Code Meaning to
    /// @param strConceptDesignator String to store the Concept Code Designator to
    /// @return True if the AcquisitionContextValue at the given index has a Concept Code and the values are saved to the parameter, false otherwise
    bool GetConceptCode(SDICOS::S_UINT32 index, DcsShortString &strConceptValue, DcsLongString &strConceptMeaning, DcsShortString &strConceptDesignator)const;

    /// Add ReferencedFrameNumbers to the AcquisitionContext at the given index
    /// @param index index for the AcquisitionContextValue object to add the referenced frame numbers to
    /// @param arrayFrameNumbers Referenced Frame Numbers to add to the Acquisition Context
    /// @return true/false True if there is an Acquisition Context with the given index and the frame numbers were set, false otherwise
    bool AddReferencedFrameNumbers(SDICOS::S_UINT32 index, const Array1D<S_UINT16> &arrayFrameNumbers);

    /// Get the Referenced Frame Numbers for the AcquisitionContextValue object at the given index if it has them
    /// @param index Index of the AcquisitionContextValue object to get the Referenced Frame Numbers from
    /// @param arrayFrameNumbers Array to store the Referenced Frame Numbers to
    /// @return True if the AcquisitionContextValue at the given index has Referenced Frame Numbers and they are saved to the parameter, false otherwise
    bool GetReferencedFrameNumbers(SDICOS::S_UINT32 index, Array1D<S_UINT16> &arrayFrameNumbers)const;

    /// Check if the AcquisitionContextValue object at the given index has Referenced Frame Numbers set
    /// @param index Index of the AcquisitionContextValue object to check
    /// @return True if the AcquisitionContextValue object at the given index has Referenced Frame Numbers
    bool HasReferencedFrameNumbers(SDICOS::S_UINT32 index)const;

    /// Delete the Referenced Frame Numbers from the AcquisitionContextValue object at the given index
    /// @param index Index of the AcquisitionContextValue object to delete the Referenced Frame Numbers
    void DeleteReferenecedFrameNumbers(SDICOS::S_UINT32 index);

    /// Get the AcquisitionContextValue object at this index in the series
    /// @param index index for the AcquisitionContextValue to be gotten
    /// @param av AcquisitionContextValue object to save the values to
    /// @return true/false True if there is an Acquisition Context with the given index, false otherwise
    bool GetAcquisitionContext(SDICOS::S_UINT32 index, AcquisitionContextValue &av)const;

    /// Check if the AcquisitionContextValue object at the given index is Numeric
    /// @param index Index of the AcquisitionConextValue object to check
    /// @return True if the object is Numeric, false otherwise
    bool IsNumeric(SDICOS::S_UINT32 index)const;

    /// Check if the AcquisitionContextValue object at the given index is a Date
    /// @param index Index of the AcquisitionConextValue object to check
    /// @return True if the object is Date, false otherwise
    bool IsDate(SDICOS::S_UINT32 index)const;

    /// Check if the AcquisitionContextValue object at the given index is a Time
    /// @param index Index of the AcquisitionConextValue object to check
    /// @return True if the object is Time, false otherwise
    bool IsTime(SDICOS::S_UINT32 index)const;

    /// Check if the AcquisitionContextValue object at the given index is a Person Name
    /// @param index Index of the AcquisitionConextValue object to check
    /// @return True if the object is a Person Name, false otherwise
    bool IsPersonName(SDICOS::S_UINT32 index)const;

    /// Check if the AcquisitionContextValue object at the given index is Text
    /// @param index Index of the AcquisitionConextValue object to check
    /// @return True if the object is Text, false otherwise
    bool IsText(SDICOS::S_UINT32 index)const;

    /// Check if the AcquisitionContextValue object at the given index is Code
    /// @param index Index of the AcquisitionConextValue object to check
    /// @return True if the object is Code, false otherwise
    bool IsCode(SDICOS::S_UINT32 index)const;

    /// Check if the AcquisitionContextValue object at the given index has Value Type set
    /// @param index Index of the AcquisitionContextValue object to check
    /// @returns True if the object has Value Type set, false otherwise
    bool HasType(SDICOS::S_UINT32 index)const;

    /// Delete the Value Type for the AcquisitionContextValue object at the given index
    /// Also deletes the associated data if it is set e.g. if Value Type = DATE the date will also be deleted
    /// @param index Index of the AcquisitionContextValue object to delete the Value Type of
    void DeleteType(SDICOS::S_UINT32 index);

	/// Acquisition Context Description : Tag (0040, 0556), VR = ST [optional]
	///	@param strDescription Description to be set
	/// @return true/false True if the description is valid and successfully set, false otherwise
	bool SetAcquisitionContextDescription(const DcsShortText &strDescription);
	/// @see SetAcquisitionContextDescription
	DcsString GetAcquisitionContextDescription()const;
protected:
    class ImplAcquisitionContextUser;
    ImplAcquisitionContextUser *m_pImplAcquisitionContextUser;
}; //class AcquisitionContextUser

} //namespace SDICOS

#endif // _STRATOVAN_DICOS_USER_ACQUISITION_CONTEXT_H_
