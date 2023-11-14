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
#ifndef _STRATOVAN_DICOS_PIXEL_MEASUREMENTS_H_
#define _STRATOVAN_DICOS_PIXEL_MEASUREMENTS_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class PixelMeasurement
/// \brief Implements Pixel Measurement, a required single item sequence (0028, 9110)
/// SPECREF V03 Section 14.14.1, Table 111
///
class PixelMeasurement
{
public:
	/// Constructor
	PixelMeasurement();
	/// Copy constructor
	PixelMeasurement(const PixelMeasurement &pixelmeasurement);
	/// Destructor
	virtual ~PixelMeasurement();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	PixelMeasurement& operator=(const PixelMeasurement &pixelmeasurement);
	/// Comparison operator
	bool operator==(const PixelMeasurement &pixelmeasurement)const;
	/// Comparison operator
	bool operator!=(const PixelMeasurement &pixelmeasurement)const;

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

	/// Set Pixel Spacing in millimeters (Distance between pixel centers) : Tag (0028, 0030), VR = DS [required if Volumetric Properties, tag (0008, 9206), is not "DISTORTED" or "SAMPLED"]
	/// @param fSpacingRow Row spacing in millimeters
	/// @param fSpacingColumn Column spacing in millimeters
	bool SetPixelSpacingInMM(const float fSpacingRow, const float fSpacingColumn);
	//		a) Param 1, Distance between pixel center of rows in mm
	//		b) Param 2, Distance between pixel center of columns in mm
	//		c) Param 1-2 : Tag (0028, 0030)
	//			i) Stored in single tag : "RowSpacing\ColumnSpacing"

	/// @see SetPixelSpacingInMM
	float GetRowSpacing()const;
	/// @see SetPixelSpacingInMM
	DcsString GetRowSpacingAsString()const;
	/// @see SetPixelSpacingInMM
	float GetColumnSpacing()const;
	/// @see SetPixelSpacingInMM
	DcsString GetColumnSpacingAsString()const;

	/// Set Slice Thickness in millimeters : Tag (0018, 0050), VR = DS [required if Volumetric Properties, tag (0008, 9206), is "VOLUME" or "SAMPLED"]
	bool SetSliceThicknessInMM(const float fSliceThickness);
	/// @see SetSliceThicknessInMM
	float GetSliceThickness()const;
	/// @see SetSliceThicknessInMM
	DcsString GetSliceThicknessAsString()const;

protected:
	class ImplPixelMeasurement;
	ImplPixelMeasurement	*m_pImplPixelMeasurement; ///< Internal implementation
};

}//namespace SDICOS

#endif
