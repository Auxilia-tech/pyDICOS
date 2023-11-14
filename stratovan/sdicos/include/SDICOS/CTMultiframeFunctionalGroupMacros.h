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
#ifndef _STRATOVAN_DICOS_CT_MULTIFRAME_FUNCTIONAL_GROUP_MACROS_H_
#define _STRATOVAN_DICOS_CT_MULTIFRAME_FUNCTIONAL_GROUP_MACROS_H_

#include "SDICOS/Attribute.h"
#include "SDICOS/PlanePosition.h"
#include "SDICOS/PlaneOrientation.h"
#include "SDICOS/FrameContentMacro.h"
#include "SDICOS/PixelMeasurement.h"
#include "SDICOS/DerivationImageMacro.h"
#include "SDICOS/ReferencedImageMacro.h"
#include "SDICOS/RealWorldValueMapping.h"
#include "SDICOS/CTXRayDetails.h"
#include "SDICOS/CTImageFrameType.h"
#include "SDICOS/CTPixelValueTransformation.h"
#include "SDICOS/FrameVoiLut.h"

namespace SDICOS
{

namespace CTTypes
{

///
/// \class CTMultiframeFunctionalGroupMacros
/// \brief Implements CT Multiframe Functional Group Macros
/// SPECREF V03 Section 7.3.1, Table 18
///
class CTMultiframeFunctionalGroupMacros
{
public:
	/// Constructor
	CTMultiframeFunctionalGroupMacros();
	/// Copy constructor
	CTMultiframeFunctionalGroupMacros(const CTMultiframeFunctionalGroupMacros &mfg);
	/// Destructor
	virtual ~CTMultiframeFunctionalGroupMacros();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	CTMultiframeFunctionalGroupMacros& operator=(const CTMultiframeFunctionalGroupMacros &mfg);
	/// Comparison operator
	bool operator==(const CTMultiframeFunctionalGroupMacros &mfg)const;
	/// Comparison operator
	bool operator!=(const CTMultiframeFunctionalGroupMacros &mfg)const;

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

	/// Returns true if the parameter 'mfg' and this object have at least 1 equal item (Ex. Returns true if pixel measurement is equal for both, but none of the other items are equal)
	bool HasEqualItem(const CTMultiframeFunctionalGroupMacros &mfg)const;

	/// Returns true if the parameter 'mfg' and this object meet validation requirements when items are combined.  Items cannot be shared between 'mfg' and this object.  Mainly used to compare shared and per-frame group macros.
	bool IsValidCombined(const CTMultiframeFunctionalGroupMacros &mfg, const AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// Pixel Measurement : Tag (0028, 9110), VR = SQ [required]
	bool SetPixelMeasurement(const PixelMeasurement &pixelmeasurement);
	/// @see SetPixelMeasurement
	bool GetPixelMeasurement(PixelMeasurement &pixelmeasurement)const;
	/// Allocate Pixel Measurement
	void AllocatePixelMeasurement();
	/// Get the pixel measurement
	PixelMeasurement* GetPixelMeasurement();
	/// @see SetPixelMeasurement
	const PixelMeasurement* GetPixelMeasurement()const;
	/// Delete Pixel Measurement
	void DeletePixelMeasurement();
	
	/// Frame Content Macro : Tag (0020, 9111), VR = SQ [optional]
	bool SetFrameContent(const FrameContentMacro &framecontentmacro);
	/// @see SetFrameContent
	bool GetFrameContent(FrameContentMacro &framecontentmacro)const;
	/// Allocate Frame Content
	void AllocateFrameContent();
	/// Get the frame content macro
	FrameContentMacro* GetFrameContent();
	/// @see SetFrameContent
	const FrameContentMacro* GetFrameContent()const;
	/// Delete Frame Content Macro
	void DeleteFrameContentMacro();

	/// Plane Position : Tag (0020, 9113), VR = SQ [required]
	bool SetPlanePosition(const PlanePosition &planeposition);
	/// @see SetPlanePosition
	bool GetPlanePosition(PlanePosition &planeposition)const;
	/// Allocate Plane Position
	void AllocatePlanePosition();
	/// Get the plane position
	PlanePosition* GetPlanePosition();
	/// @see SetPlanePosition
	const PlanePosition* GetPlanePosition()const;
	/// Delete Plane Position
	void DeletePlanePosition();

	/// Plane Orientation [required]
	bool SetPlaneOrientation(const PlaneOrientation &planeorientation);
	/// @see SetPlaneOrientation
	bool GetPlaneOrientation(PlaneOrientation &planeorientation)const;
	/// Allocate Plane Orientation
	void AllocatePlaneOrientation();
	/// Get the plane orientation
	PlaneOrientation* GetPlaneOrientation();
	/// @see SetPlaneOrientation
	const PlaneOrientation* GetPlaneOrientation()const;
	/// Delete Plane Orientation
	void DeletePlaneOrientation();

	/// Referenced Image Sequence : Tag (0008, 1140), VR = SQ [optional]
	bool SetReferencedImages(const ReferencedImageSequence &referencedimagesequence);
	/// @see SetReferencedImages
	bool GetReferencedImages(ReferencedImageSequence &referencedimagesequence)const;
	/// Allocate Referenced Image
	void AllocateReferencedImages();
	/// Get the Referenced Image Sequence
	ReferencedImageSequence* GetReferencedImages();
	/// @see SetReferencedImages
	const ReferencedImageSequence* GetReferencedImages()const;
	/// Delete Referenced Image Sequence
	void DeleteReferencedImageSequence();

	/// Derivation Image Sequence : Tag (0008, 9124), VR = SQ [optional]
	bool SetDerivationImageSequence(const DerivationImageSequence &derivationimagesequence);
	/// @see SetDerivationImageSequence
	bool GetDerivationImageSequence(DerivationImageSequence &derivationimagesequence)const;
	/// Allocate Derivation Image Sequence
	void AllocateDerivationImageSequence();
	/// Get the derivation image sequence
	DerivationImageSequence* GetDerivationImageSequence();
	/// @see SetDerivationImageSequence
	const DerivationImageSequence* GetDerivationImageSequence()const;
	/// Delete Derivation Image Sequence
	void DeleteDerivationImageSequence();

	/// Frame VOI LUT Sequence : Tag (0028, 9132), VR = SQ [optional]
	bool SetFrameVoiLut(const FrameVoiLut &framevoilut);
	/// @see SetFrameVoiLut
	bool GetFrameVoiLut(FrameVoiLut &framevoilut)const;
	/// Allocate Frame VOI LUT
	void AllocateFrameVoiLut();
	/// Get the VOI LUT Sequence
	FrameVoiLut* GetFrameVoiLut();
	/// @see SetFrameVoiLut
	const FrameVoiLut* GetFrameVoiLut()const;
	/// Delete VOI LUT Sequence
	void DeleteFrameVoiLut();

	/// Real World Value Mapping Sequence : Tag (0040, 9096), VR = SQ [optional]
	bool SetRealWorldValueMapping(const RealWorldValueMappingSequence &realworldvaluemappingsequence);
	/// @see SetRealWorldValueMapping
	bool GetRealWorldValueMapping(RealWorldValueMappingSequence &realworldvaluemappingsequence)const;
	/// Allocate Real World Value Mapping
	void AllocateRealWorldValueMapping();
	/// Get the Real World Value Mapping Sequence
	RealWorldValueMappingSequence* GetRealWorldValueMapping();
	/// @see SetRealWorldValueMapping
	const RealWorldValueMappingSequence* GetRealWorldValueMapping()const;
	/// Delete Real World Value Mapping Sequence
	void DeleteRealWorldValueMappingSequence();

	/// CT Image Frame Type [required]
	bool SetImageFrameType(const CTImageFrameType &imageframetype);
	/// @see SetImageFrameType
	bool GetImageFrameType(CTImageFrameType &imageframetype)const;
	/// Allocate Image Frame Type
	void AllocateImageFrameType();
	/// Get the CT image frame type
	CTImageFrameType* GetImageFrameType();
	/// @see SetImageFrameType
	const CTImageFrameType* GetImageFrameType()const;
	/// Delete CT Image Frame Type
	void DeleteCTImageFrameType();

	/// CT X-Ray Details : Tag (0018, 9325), VR = SQ [conditionally required]
	bool SetXRayDetails(const CTXRayDetails &xraydetails);
	/// @see GetXRayDetails
	bool GetXRayDetails(CTXRayDetails &xraydetails)const;
	/// Allocate X-Ray Details
	void AllocateXRayDetails();
	/// Get the CT X-Ray Details
	CTXRayDetails* GetXRayDetails();
	/// @see GetXRayDetails
	const CTXRayDetails* GetXRayDetails()const;
	/// Delete CT X-Ray Details
	void DeleteCTXRayDetails();

	/// CT Pixel Value Transformation [Required]
	bool SetPixelValueTransformation(const CTPixelValueTransformation &pixelvaluetransformation);
	/// @see SetPixelValueTransformation
	bool GetPixelValueTransformation(CTPixelValueTransformation &pixelvaluetransformation)const;
	/// Allocate Pixel Value Transformation
	void AllocatePixelValueTransformation();
	/// Get the CT pixel value transformation
	CTPixelValueTransformation* GetPixelValueTransformation();
	/// @see SetPixelValueTransformation
	const CTPixelValueTransformation* GetPixelValueTransformation()const;
	/// Delete CT Pixel Value Transformation
	void DeleteCTPixelValueTransformation();

protected:
	class ImplCTMultiframeFunctionalGroupMacros;
	ImplCTMultiframeFunctionalGroupMacros	*m_pImplCTMultiframeFunctionalGroupMacros; ///< Internal implementation
};

}//namespace CTTypes

}//namespace SDICOS

#endif
