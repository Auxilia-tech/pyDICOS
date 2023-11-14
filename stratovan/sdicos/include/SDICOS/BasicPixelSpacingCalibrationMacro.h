//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2015 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_BASIC_PIXEL_SPACING_CALIBRATION_MACRO_H_
#define _STRATOVAN_DICOS_BASIC_PIXEL_SPACING_CALIBRATION_MACRO_H_

#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class BasicPixelSpacingCalibrationMacro
/// \brief Implements Basic Pixel Spacing Calibration Macro
/// SPECREF V03 Section 14.10, Table 107
///
class BasicPixelSpacingCalibrationMacro
{
public:
	/// Default constructor
	BasicPixelSpacingCalibrationMacro();
	/// Copy constructor
	BasicPixelSpacingCalibrationMacro(const BasicPixelSpacingCalibrationMacro &macro);
	/// Destructor
	virtual ~BasicPixelSpacingCalibrationMacro();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	BasicPixelSpacingCalibrationMacro& operator=(const BasicPixelSpacingCalibrationMacro &macro);
	/// Comparison operator
	bool operator==(const BasicPixelSpacingCalibrationMacro &macro)const;
	/// Comparison operator
	bool operator!=(const BasicPixelSpacingCalibrationMacro &macro)const;

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

	/// Pixel Spacing Calibration Type : Tag (0028, 0A02), VR = CS [optional]
	/// If set, Pixel Spacing (0028, 0030) can be used for measurements of objects at the same depth near the central ray
	void SetPixelSpacingCalibrationType();
	/// Return true if Pixel Spacing Calibration Type is set
	bool HasPixelSpacingCalibrationType()const;
	/// Return value of Pixel Spacing Calibration Type as a string
	DcsString GetPixelSpacingCalibrationTypeAsString()const;
	/// Delete Pixel Spacing Calibration Type
	/// @see SetPixelSpacingCalibrationType
	void DeletePixelSpacingCalibrationType();

	/// Pixel Spacing : Tag (0028, 0030), VR = DS, VM = 2 [required if Pixel Spacing Calibration Type (0028, 0A02) is set]
	/// Physical distance between pixels in the image data
	/// @param fRow Row spacing
	/// @param fColumn Column spacing
	void SetPixelSpacing(const float fRow, const float fColumn);
	/// Returns false if pixel spacing is not present
	/// @see SetPixelSpacing
	bool GetPixelSpacing(float &fRow, float &fColumn)const;
	/// Returns true if Pixel Spacing (0028, 0030) is set
	bool HasPixelSpacing()const;
	/// @see SetPixelSpacing
	float GetPixelSpacingRow()const;
	/// @see SetPixelSpacing
	float GetPixelSpacingColumn()const;
	/// Delete Pixel Spacing
	/// @see SetPixelSpacing
	void DeletePixelSpacing();

	///	Pixel Spacing Calibration Description: Tag (0028, 0A04), VR = LO [required if Pixel Spacing (0028, 0030) is present]
	/// @param dsDescription Description for the pixel spacing calibration
	bool SetPixelSpacingCalibrationDescription(const DcsLongString &dsDescription);
	/// @see SetPixelSpacingCalibrationDescription
	DcsLongString GetPixelSpacingCalibrationDescription()const;
	/// Delete Pixel Spacing Calibration Description
	/// @see SetPixelSpacingCalibrationDescription
	void DeletePixelSpacingCalibrationDescription();

protected:
	class BasicPixelSpacingImpl;
	BasicPixelSpacingImpl *m_pImplBasicPixelSpacing;
};

}//namespace SDICOS

#endif
