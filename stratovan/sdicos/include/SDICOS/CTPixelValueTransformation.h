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
#ifndef _STRATOVAN_DICOS_CT_PIXEL_VALUE_TRANSFORMATION_H_
#define _STRATOVAN_DICOS_CT_PIXEL_VALUE_TRANSFORMATION_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

namespace CTTypes
{

///
/// \class CTPixelValueTransformation
/// \brief Implements CT Pixel Value Transformation, a required single item sequence (0028, 9145)
///	Used for adjusting stored pixel data to the specified output units ( [Pixel Data in Output Units] = [Rescale Slope] * [Pixel Data] + [Rescale Intercept] )
/// SPECREF V03 Section 7.4.3.3, Table 24
///
class CTPixelValueTransformation
{
public:
	/// Constructor
	CTPixelValueTransformation();
	/// Copy constructor
	CTPixelValueTransformation(const CTPixelValueTransformation &pvt);
	/// Destructor
	virtual ~CTPixelValueTransformation();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	CTPixelValueTransformation& operator=(const CTPixelValueTransformation &pvt);
	/// Comparison operator
	bool operator==(const CTPixelValueTransformation &pvt)const;
	/// Comparison operator
	bool operator!=(const CTPixelValueTransformation &pvt)const;

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

	/// Rescale Slope : Tag (0028, 1053), VR = DS [required]
	bool SetRescaleSlope(const float fSlope);
	/// @see SetRescaleSlope
	float GetRescaleSlope()const;
	/// @see SetRescaleSlope
	DcsString GetRescaleSlopeAsString()const;

	/// Rescale Intercept : Tag (0028, 1052), VR = DS [required]
	bool SetRescaleIntercept(const float fIntercept);
	/// @see SetRescaleIntercept
	float GetRescaleIntercept()const;
	/// @see SetRescaleIntercept
	DcsString GetRescaleInterceptAsString()const;

	/// Rescale Type (Specifies output units) : Tag (0028, 1054), VR = LO [required]
	bool SetRescaleType(const DcsLongString &strType);
	/// @see SetRescaleType
	DcsString GetRescaleType()const;

protected:
	class ImplCTPixelValueTransformation;
	ImplCTPixelValueTransformation	*m_pImplCTPixelValueTransformation; ///< Internal implementation
};

}//namespace CTTypes

}//namespace SDICOS

#endif
