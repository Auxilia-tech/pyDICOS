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
#ifndef _STRATOVAN_DICOS_PIXEL_INTENSITY_RELATIONSHIP_LUT_H_
#define _STRATOVAN_DICOS_PIXEL_INTENSITY_RELATIONSHIP_LUT_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class PixelIntensityRelationshipLutSequence
/// \brief Implements Pixel Intensity Relationship LUT Sequence
/// SPECREF V03 Section 14.14.10, Table 120
///
class PixelIntensityRelationshipLutSequence
{
public:
	/// Constructor
	PixelIntensityRelationshipLutSequence();
	/// Copy constructor
	PixelIntensityRelationshipLutSequence(const PixelIntensityRelationshipLutSequence &pir);
	/// Destructor
	virtual ~PixelIntensityRelationshipLutSequence();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	PixelIntensityRelationshipLutSequence& operator=(const PixelIntensityRelationshipLutSequence &pir);
	/// Comparison operator
	bool operator==(const PixelIntensityRelationshipLutSequence &pir)const;
	/// Comparison operator
	bool operator!=(const PixelIntensityRelationshipLutSequence &pir)const;

	///
	/// \class PixelIntensityRelationshipLUT
	/// \brief An item in Pixel Intensity Relationship LUT Sequence
	///
	class PixelIntensityRelationshipLUT
	{
	public:
		/// Constructor
		PixelIntensityRelationshipLUT();
		/// Copy constructor
		PixelIntensityRelationshipLUT(const PixelIntensityRelationshipLUT &pir);
		/// Destructor
		~PixelIntensityRelationshipLUT();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		PixelIntensityRelationshipLUT& operator=(const PixelIntensityRelationshipLUT &pir);
		/// Comparison operator
		bool operator==(const PixelIntensityRelationshipLUT &pir)const;
		/// Comparison operator
		bool operator!=(const PixelIntensityRelationshipLUT &pir)const;

		/// LUT function enumeration
		typedef enum
		{
			enumUnknownLutFunction, ///< Unknown enumeration

			enumToLog,		///< "TO_LOG"
			enumToLinear,	///< "TO_LINEAR"

		}LUT_FUNCTION;

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

		/////////////////////////////////////////////////////
		// LUT Descriptor : Tag (0028, 3002), VM = 3, VR = US/SS  [required]
		//	-Value 1: Number of entries in LUT Data. Set in SetData()
		//	-Value 2: First value mapped in LUT Data. Set in SetFirstValueMapped()
		//	-Value 3: Bits per entry.  Set in SetData()
		/////////////////////////////////////////////////////

		/// Return true if LUT data is unsigned
		bool IsLutDataUnsigned()const;
		/// Return true if LUT data is signed
		bool IsLutDataSigned()const;

		/// Return true if first value mapped is unsigned
		bool IsFirstValueMappedUnsigned()const;
		/// Return true if first value mapped is signed
		bool IsFirstValueMappedSigned()const;

		///
		/// First value mapped [value 2 of LUT Descriptor (0028, 3002)].  
		/// Used as base index LUTData[nValue - FirstValueMapped]
		///
		bool SetFirstValueMapped(const S_UINT16 nFirstValueMapped);
		///
		/// First value mapped [value 2 of LUT Descriptor (0028, 3002)].  
		/// Used as base index LUTData[nValue - FirstValueMapped]
		///
		bool SetFirstValueMapped(const S_INT16 nFirstValueMapped);
		/// @see SetFirstValueMapped
		bool GetFirstValueMapped(S_UINT16 &nFirstValueMapped)const;
		/// @see SetFirstValueMapped
		bool GetFirstValueMapped(S_INT16 &nFirstValueMapped)const;

		/// LUT Data : Tag (0028, 3006), VR = US [required]
		bool SetData(const Array1D<S_UINT16> &arrayData);
		/// LUT Data : Tag (0028, 3006), VR = SS [required]
		bool SetData(const Array1D<S_INT16> &arrayData);
		/// Get unsigned LUT data.  Deletes signed data.
		Array1D<S_UINT16>& GetUnsignedData();
		/// Get unsigned LUT data.  Deletes unsigned data.
		Array1D<S_INT16>& GetSignedData();
		/// @see SetData
		const Array1D<S_UINT16>& GetUnsignedData()const;
		/// @see SetData
		const Array1D<S_INT16>& GetSignedData()const;

		/// LUT Function : Tag (0028, 9474), VR = CS [required]
		bool SetLutFunction(const LUT_FUNCTION nFunction);
		/// @see SetLutFunction
		LUT_FUNCTION GetLutFunction()const;
		/// @see SetLutFunction
		DcsString GetLutFunctionAsString()const;

	protected:
		class ImplPixelIntensityRelationshipLUT;
		ImplPixelIntensityRelationshipLUT	*m_pImplPIRLUT; ///< Internal implementation
	};

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false is returned if attributes were specified or if some were invalid.
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	///
	/// Pixel Intensity Relationship LUT Sequence : Tag (0028, 9422), VR = SQ [required]
	/// Only a single item can have LUT_FUNCTION set to enumToLinear.  Multiple items may have LUT_FUNCTION set to enumToLog.
	///
	bool SetPixelIntensityRelationshipLUT(const Array1D<PixelIntensityRelationshipLUT> &arrayPixelIntensityRelationshipLUT);
	/// @see SetPixelIntensityRelationshipLUT
	bool GetPixelIntensityRelationshipLUT(Array1D<PixelIntensityRelationshipLUT> &arrayPixelIntensityRelationshipLUT)const;
	/// @see SetPixelIntensityRelationshipLUT
	Array1D<PixelIntensityRelationshipLUT>& GetPixelIntensityRelationshipLUT();
	/// @see SetPixelIntensityRelationshipLUT
	const Array1D<PixelIntensityRelationshipLUT>& GetPixelIntensityRelationshipLUT()const;

protected:
	class ImplPixelIntensityRelationshipLutSequence;
	ImplPixelIntensityRelationshipLutSequence	*m_pImplPIRS; ///< Internal implementation
};

}//namespace SDICOS

#endif
