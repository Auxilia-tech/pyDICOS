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
#ifndef _STRATOVAN_DICOS_REAL_WORLD_VALUE_MAPPING_H_
#define _STRATOVAN_DICOS_REAL_WORLD_VALUE_MAPPING_H_

#include "SDICOS/MeasurementUnitsCodeSequence.h"

namespace SDICOS
{

///
/// \class RealWorldValueMappingSequence
/// \brief World Value Mapping 
/// SPECREF V03 Section 14.14.9, Table 119
///
class RealWorldValueMappingSequence
{
public:
	/// Constructor
	RealWorldValueMappingSequence();
	/// Copy constructor
	RealWorldValueMappingSequence(const RealWorldValueMappingSequence &rwvm);
	/// Destructor
	virtual ~RealWorldValueMappingSequence();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	RealWorldValueMappingSequence& operator=(const RealWorldValueMappingSequence &rwvm);
	/// Comparison operator
	bool operator==(const RealWorldValueMappingSequence &rwvm)const;
	/// Comparison operator
	bool operator!=(const RealWorldValueMappingSequence &rwvm)const;
		
	///
	/// \class RealWorldValueItem
	/// \brief Item used in sequence (0040, 9096)
	///
	class RealWorldValueItem
	{
	public:
		/// Constructor
		RealWorldValueItem();
		/// Copy constructor
		RealWorldValueItem(const RealWorldValueItem &rwvi);
		/// Destructor
		~RealWorldValueItem();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		RealWorldValueItem& operator=(const RealWorldValueItem &rwvi);
		/// Comparison operator
		bool operator==(const RealWorldValueItem &rwvi)const;
		/// Comparison operator
		bool operator!=(const RealWorldValueItem &rwvi)const;

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

		/// Mapped Value Representation (0x0060, 0x7006), VR = US [Required]
		/// Value set internally after calling SetFirstAndLastValueMapped
		/// @see SetFirstAndLastValueMapped
		S_UINT16 GetMappedValueRepresentation()const;
		/// Returns true if value is set
		/// @see SetFirstAndLastValueMapped
		bool HasMappedValueRepresentation()const;

		/// Real World First and Last Value Mapped (VR based on Mapped Value Representation (0x0060, 0x7006))
		/// Values are used to indicate the first index and last index used with the LUT (i.e. arrayMappedValues[nFirst]) or
		/// first and last value used with slope and intercept (i.e. [Real Value] = [Slope] * [first value] + [Intercept])
		/// Internally sets Mapped Value Representation (0x0060, 0x7006) to 0 (Unsigned)
		/// @param nFirst Real World First Value Mapped : Tag (0040, 9216), VR = US [required]
		/// @param nLast Real World Last Value Mapped : Tag (0040, 9211), VR = US [required]
		bool SetFirstAndLastValueMapped(const S_UINT16 nFirst, const S_UINT16 nLast);
		/// Real World First and Last Value Mapped (VR based on Mapped Value Representation (0x0060, 0x7006))
		/// Values are used to indicate the first index and last index used with the LUT or
		/// first and last value used with slope and intercept (i.e. [Real Value] = [Slope] * [first value] + [Intercept])
		/// Internally sets Mapped Value Representation (0x0060, 0x7006) to 1 (Signed)
		/// @param nFirst Real World First Value Mapped : Tag (0040, 9216), VR = SS [required]
		/// @param nLast Real World Last Value Mapped : Tag (0040, 9211), VR = SS [required]
		bool SetFirstAndLastValueMapped(const S_INT16 nFirst, const S_INT16 nLast);

		/// @see SetFirstAndLastValueMapped
		bool GetFirstAndLastValueMapped(S_UINT16 &nFirst, S_UINT16 &nLast)const;
		/// @see SetFirstAndLastValueMapped
		bool GetFirstAndLastValueMapped(S_INT16 &nFirst, S_INT16 &nLast)const;

		/// Returns true if first and last value mapped are unsigned
		bool IsUnsignedValue()const;
		/// Returns true if first and last value mapped are signed
		bool IsSignedValue()const;

		/// Real World Value Slope and Intercept
		///	@param fSlope Real World Value Slope : Tag (0040, 9225), VR = FD [required if Real World Value LUT Data (0040, 9212) is not set]
		///	@param fIntercept Real World Value Intercept : Tag (0040, 9224), VR = FD [required if Real World Value LUT Data (0040, 9212) is not set]
		bool SetSlopeAndIntercept(const double fSlope, const double fIntercept);

		/// @see SetSlopeAndIntercept
		bool GetSlopeAndIntercept(double &fSlope, double &fIntercept)const;
		/// @see SetSlopeAndIntercept
		double GetSlope()const;
		/// @see SetSlopeAndIntercept
		double GetIntercept()const;

		/// Real World Value LUT Data : Tag (0040, 9212), VR = FD 
		/// [required if Real World Value Intercept (0040, 9224) and Real World Value Slope are (0040, 9925) not set]
		bool SetData(const Array1D<double> &arrayData);
		/// @see SetData
		bool GetData(Array1D<double> &arrayData)const;
		/// @see SetData
		Array1D<double>& GetData();
		/// @see SetData
		const Array1D<double>& GetData()const;

		/// LUT Explanation : Tag (0028, 3003), VR = LO [required]
		bool SetLutExplanation(const DcsLongString &strExplanation);
		/// @see SetLutExplanation
		DcsString GetLutExplanation()const;

		/// LUT Label (Identifies transform) : Tag (0040, 9210), VR = SH [required]
		bool SetLutLabel(const DcsShortString &strLabel);
		/// @see SetLutLabel
		DcsString GetLutLabel()const;

		/// Measurement Units Code Sequence (Single Item Sequence) : Tag (0040, 08EA), VR = SQ [required]
		bool SetMeasurementUnits(const MeasurementUnitsCodeSequence &csUnits);
		/// @see SetMeasurementUnits
		MeasurementUnitsCodeSequence& GetMeasurementUnits();
		/// @see SetMeasurementUnits
		const MeasurementUnitsCodeSequence& GetMeasurementUnits()const;

	protected:
		class ImplRealWorldValueItem;
		ImplRealWorldValueItem	*m_pImplRealWorldValueItem; ///< Internal implementation
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

	/// Real World Value Mapping Sequence : Tag (0040, 9096), VR = SQ [optional]
	bool SetRealWorldValueMapping(const Array1D<RealWorldValueItem> &arrayRealWorldValues);
	/// @see SetRealWorldValueMapping
	bool GetRealWorldValueMapping(Array1D<RealWorldValueItem> &arrayRealWorldValues)const;
	/// @see SetRealWorldValueMapping
	Array1D<RealWorldValueItem>& GetRealWorldValueMapping();
	/// @see SetRealWorldValueMapping
	const Array1D<RealWorldValueItem>& GetRealWorldValueMapping()const;

protected:
	class ImplRealWorldValueMappingSequence;
	ImplRealWorldValueMappingSequence	*m_pImplRealWorldValueMappingSequence; ///< Internal implementation
};

}//namespace SDICOS

#endif
