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
#ifndef _STRATOVAN_DICOS_COMMON_IMAGE_DESCRIPTION_H_
#define _STRATOVAN_DICOS_COMMON_IMAGE_DESCRIPTION_H_

#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class CommonImageDescription
/// \brief Base class containing attributes shared by Common CT and 3D AIT Image Modules
/// SPECREF V03 Section 7.5.2, Table 29
/// SPECREF V03 Section 9.3.4.2, Table 55
///
class CommonImageDescription
{
public:
	/// Constructor
	CommonImageDescription();
	/// Copy constructor
	CommonImageDescription(const CommonImageDescription &commonimagedescription);
	/// Destructor
	virtual ~CommonImageDescription();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	CommonImageDescription& operator=(const CommonImageDescription &commonimagedescription);
	/// Comparison operator
	bool operator==(const CommonImageDescription &commonimagedescription)const;
	/// Comparison operator
	bool operator!=(const CommonImageDescription &commonimagedescription)const;

	/// Pixel Presentation enumerations
	typedef enum
	{
		enumUnknownPixelPresentation, ///< Unknown enumeration

		enumPP_Color,		///< "COLOR"
		enumPP_Monochrome,	///< "MONOCHROME"
		enumPP_Mixed,		///< "MIXED"

	}PIXEL_PRESENTATION;

	/// Volumetric Properties enumerations
	typedef enum
	{
		enumUnknownVolumetricProperties, ///< Unknown enumeration

		enumVP_Volume,		///< "VOLUME"
		enumVP_Sampled,		///< "SAMPLED"
		enumVP_Distorted,	///< "DISTORTED"
		enumVP_Mixed,		///< "MIXED"

	}VOLUMETRIC_PROPERTIES;

	/// Volume Based Calculation Technique enumerations
	typedef enum
	{
		enumUnknownVolumeBasedCalculationTechnique, ///< Unknown enumeration

		enumVC_MaxIP,			///< "MAX_IP"
		enumVC_MinIP,			///< "MIN_IP"
		enumVC_VolumeRender,	///< "VOLUME_RENDER"
		enumVC_SurfaceRender,	///< "SURFACE_RENDER"
		enumVC_MPR,				///< "MPR"
		enumVC_CurvedMPR,		///< "CURVED_MPR"
		enumVC_None,			///< "NONE"
		enumVC_Mixed,			///< "MIXED"

	}VOLUME_BASED_CALCULATION_TECHNIQUE;
	
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

	/// Set Pixel Presentation : Tag (0008, 9205), VR = CS [required]
	bool SetPixelPresentation(const PIXEL_PRESENTATION nPresentation);
	/// @see SetPixelPresentation
	PIXEL_PRESENTATION GetPixelPresentation()const;
	/// @see SetPixelPresentation
	DcsString GetPixelPresentationAsString()const;

	/// Set Volumetric Properties : Tag (0008, 9206), VR = CS [required]
	bool SetVolumetricProperties(const VOLUMETRIC_PROPERTIES nProperties);
	/// @see SetVolumetricProperties
	VOLUMETRIC_PROPERTIES GetVolumetricProperties()const;
	/// @see SetVolumetricProperties
	DcsString GetVolumetricPropertiesAsString()const;

	/// Set Volume Based Calculation Technique : Tag (0008, 9207), VR = CS [required]
	bool SetVolumeBasedCalculationTechnique(const VOLUME_BASED_CALCULATION_TECHNIQUE nTechnique);
	/// @see SetVolumeBasedCalculationTechnique
	VOLUME_BASED_CALCULATION_TECHNIQUE GetVolumeBasedCalculationTechnique()const;
	/// @see SetVolumeBasedCalculationTechnique
	DcsString GetVolumeBasedCalculationTechniqueAsString()const;

protected:
	class ImplCommonImageDescription;
	ImplCommonImageDescription	*m_pImplCommonImageDescription; ///< Internal implementation
};

}//namespace SDICOS

#endif
