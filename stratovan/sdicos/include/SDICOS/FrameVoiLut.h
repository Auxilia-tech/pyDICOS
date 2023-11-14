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
#ifndef _STRATOVAN_DICOS_FRAME_VOI_LUT_H_
#define _STRATOVAN_DICOS_FRAME_VOI_LUT_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class FrameVoiLut
/// \brief Implements Frame VOI LUT, a required single item sequence (0028, 9132)
/// SPECREF V03 Section 14.14.8, Table 118
///
class FrameVoiLut
{
public:
	/// Constructor
	FrameVoiLut();
	/// Copy constructor
	FrameVoiLut(const FrameVoiLut &framevoilut);
	/// Destructor
	virtual ~FrameVoiLut();

	/// VOI LUT Function enumerations
	typedef enum
	{
		enumUnknownVoiLutFunction,	///< Unknown enumeration

		enumLinear,		///< "LINEAR"
		enumSigmoid,	///< "SIGMOID"

		enumDefault = enumLinear, ///< Default enumeration

	}VOI_LUT_FUNCTION;

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	FrameVoiLut& operator=(const FrameVoiLut &framevoilut);
	/// Comparison operator
	bool operator==(const FrameVoiLut &framevoilut)const;
	/// Comparison operator
	bool operator!=(const FrameVoiLut &framevoilut)const;

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

	/// Window Center And Width [required]
	/// @param fCenter Window Center : Tag (0028, 1050), VR = DS [required]
	/// @param fWidth Window Width : Tag (0028, 1051), VR = DS [required]
	bool SetWindowCenterAndWidth(const float fCenter, const float fWidth);
	/// Window Center And Width [required]
	/// @param arrayCenter Window Center : Tag (0028, 1050), VR = DS [required]
	/// @param arrayWidth Window Width : Tag (0028, 1051), VR = DS [required]
	bool SetWindowCenterAndWidth(const Array1D<float> &arrayCenter, const Array1D<float> &arrayWidth);
	/// @see SetWindowCenterAndWidth
	bool GetWindowCenterAndWidth(Array1D<float> &arrayCenter, Array1D<float> &arrayWidth)const;
	/// @see SetWindowCenterAndWidth
	Array1D<float>& GetWindowCenter();
	/// @see SetWindowCenterAndWidth
	const Array1D<float>& GetWindowCenter()const;
	/// @see SetWindowCenterAndWidth
	Array1D<float>& GetWindowWidth();
	/// @see SetWindowCenterAndWidth
	const Array1D<float>& GetWindowWidth()const;

	/// Window Center And Width Explanation : Tag (0028, 1055), VR = LO [optional]
	bool SetWindowCenterAndWidthExplanation(const Array1D<DcsLongString> &arrayExplanation);
	/// @see SetWindowCenterAndWidthExplanation
	bool GetWindowCenterAndWidthExplanation(Array1D<DcsString> &arrayExplanation)const;
	/// @see SetWindowCenterAndWidthExplanation
	Array1D<DcsLongString>& GetWindowCenterAndWidthExplanation();
	/// @see SetWindowCenterAndWidthExplanation
	const Array1D<DcsLongString>& GetWindowCenterAndWidthExplanation()const;
	/// Delete Window Center And Width Explanation
	void DeleteWindowCenterAndWidthExplanation();

	/// VOI LUT Function : Tag (0028, 1056), VR = CS [optional]
	bool SetVoiLutFunction(const VOI_LUT_FUNCTION nFunction);
	/// @see SetVoiLutFunction
	VOI_LUT_FUNCTION GetVoiLutFunction()const;
	/// @see SetVoiLutFunction
	DcsString GetVoiLutFunctionAsString()const;
	/// Delete VOI LUT Function
	void DeleteVoiLutFunction();

protected:
	class ImplFrameVoiLut;
	ImplFrameVoiLut	*m_pImplFrameVoiLut; ///< Internal implementation
};

}//namespace SDICOS

#endif
