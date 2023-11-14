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
#ifndef _STRATOVAN_DICOS_AIT_3D_MULTIFRAME_FUNCTIONAL_GROUP_MACROS_H_
#define _STRATOVAN_DICOS_AIT_3D_MULTIFRAME_FUNCTIONAL_GROUP_MACROS_H_

#include "SDICOS/PixelMeasurement.h"
#include "SDICOS/FrameContentMacro.h"
#include "SDICOS/PlanePosition.h"
#include "SDICOS/PlaneOrientationAIT.h"
#include "SDICOS/ReferencedImageMacro.h"
#include "SDICOS/DerivationImageMacro.h"
#include "SDICOS/FrameVoiLut.h"
#include "SDICOS/RealWorldValueMapping.h"
#include "SDICOS/AIT3DImageFrameType.h"
#include "SDICOS/PixelIntensityRelationshipLUT.h"

namespace SDICOS
{
namespace AIT3DTypes
{

///
/// \class AIT3DMultiframeFunctionalGroupMacros
/// \brief Implements 3D AIT Multiframe Functional Group Macros
/// SPECREF V03 Section 9.3.2.1, Table 46
///
class AIT3DMultiframeFunctionalGroupMacros
{	
public:
	/// Constructor
	AIT3DMultiframeFunctionalGroupMacros();
	/// Copy constructor
	AIT3DMultiframeFunctionalGroupMacros(const AIT3DMultiframeFunctionalGroupMacros &mfg);
	/// Destructor
	virtual ~AIT3DMultiframeFunctionalGroupMacros();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	AIT3DMultiframeFunctionalGroupMacros& operator=(const AIT3DMultiframeFunctionalGroupMacros &mfg);
	/// Comparison operator
	bool operator==(const AIT3DMultiframeFunctionalGroupMacros &mfg)const;
	/// Comparison operator
	bool operator!=(const AIT3DMultiframeFunctionalGroupMacros &mfg)const;

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
	bool HasEqualItem(const AIT3DMultiframeFunctionalGroupMacros &mfg)const;

	/// Returns true if the parameter 'mfg' and this object meet validation requirements when items are combined. Items cannot be shared between 'mfg' and this object. Mainly used to compare shared and per-frame group macros.
	bool IsValidCombined(const AIT3DMultiframeFunctionalGroupMacros &mfg, const AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// Pixel Measurement [required]
	bool SetPixelMeasurement(const PixelMeasurement &pixelmeasurement);
	/// @see SetPixelMeasurement
	bool GetPixelMeasurement(PixelMeasurement &pixelmeasurement)const;
	/// Allocate Pixel Measurement
	void AllocatePixelMeasurement();
	/// @see SetPixelMeasurement
	PixelMeasurement* GetPixelMeasurement();
	/// @see SetPixelMeasurement
	const PixelMeasurement* GetPixelMeasurement()const;
	/// Delete Pixel Measurement
	void DeletePixelMeasurement();
	
	/// Frame Content Macro [optional]
	bool SetFrameContent(const FrameContentMacro &framecontentmacro);
	/// @see SetFrameContent
	bool GetFrameContent(FrameContentMacro &framecontentmacro)const;
	/// Allocate Frame Content
	void AllocateFrameContent();
	/// @see SetFrameContent
	FrameContentMacro* GetFrameContent();
	/// @see SetFrameContent
	const FrameContentMacro* GetFrameContent()const;
	/// Delete Frame Content Macro
	void DeleteFrameContentMacro();

	/// Plane Position [required]
	bool SetPlanePosition(const PlanePosition &planeposition);
	/// @see SetPlanePosition
	bool GetPlanePosition(PlanePosition &planeposition)const;
	/// Allocate Plane Position
	void AllocatePlanePosition();
	/// @see SetPlanePosition
	PlanePosition* GetPlanePosition();
	/// @see SetPlanePosition
	const PlanePosition* GetPlanePosition()const;
	/// Delete Plane Position
	void DeletePlanePosition();

	/// AIT Plane Orientation [required]
	bool SetAitPlaneOrientation(const AitPlaneOrientation &planeorientation);
	/// @see SetAitPlaneOrientation
	bool GetAitPlaneOrientation(AitPlaneOrientation &planeorientation)const;
	/// Allocate AIT Plane Orientation
	void AllocateAitPlaneOrientation();
	/// @see SetAitPlaneOrientation
	AitPlaneOrientation* GetAitPlaneOrientation();
	/// @see SetAitPlaneOrientation
	const AitPlaneOrientation* GetAitPlaneOrientation()const;
	/// Delete AIT Plane Orientation
	void DeleteAitPlaneOrientation();

	/// Referenced Image Sequence [required if referenced images are used]
	bool SetReferencedImages(const ReferencedImageSequence &referencedimagesequence);
	/// @see SetReferencedImages
	bool GetReferencedImages(ReferencedImageSequence &referencedimagesequence)const;
	/// Allocate Referenced Image
	void AllocateReferencedImages();
	/// @see SetReferencedImages
	ReferencedImageSequence* GetReferencedImages();
	/// @see SetReferencedImages
	const ReferencedImageSequence* GetReferencedImages()const;
	/// Delete Referenced Image Sequence
	void DeleteReferencedImageSequence();

	/// Derivation Image Sequence [required if derived images are used]
	bool SetDerivationImageSequence(const DerivationImageSequence &derivationimage);
	/// @see SetDerivationImageSequence
	bool GetDerivationImageSequence(DerivationImageSequence &derivationimage)const;
	/// Allocate Derivation Image Sequence
	void AllocateDerivationImageSequence();
	/// @see SetDerivationImageSequence
	DerivationImageSequence* GetDerivationImageSequence();
	/// @see SetDerivationImageSequence
	const DerivationImageSequence* GetDerivationImageSequence()const;
	/// Delete Derivation Image Sequence
	void DeleteDerivationImageSequence();

	/// Frame VOI LUT Sequence [optional]
	bool SetFrameVoiLut(const FrameVoiLut &framevoilut);
	/// @see SetFrameVoiLut
	bool GetFrameVoiLut(FrameVoiLut &framevoilut)const;
	/// Allocate Frame VOI LUT
	void AllocateFrameVoiLut();
	/// @see SetFrameVoiLut
	FrameVoiLut* GetFrameVoiLut();
	/// @see SetFrameVoiLut
	const FrameVoiLut* GetFrameVoiLut()const;
	/// Delete Frame VOI LUT Sequence
	void DeleteFrameVoiLut();

	/// Real World Value Mapping [optional]
	bool SetRealWorldValueMapping(const RealWorldValueMappingSequence &realworldvaluemapping);
	/// @see SetRealWorldValueMapping
	bool GetRealWorldValueMapping(RealWorldValueMappingSequence &realworldvaluemapping)const;
	/// Allocate Real World Value Mapping
	void AllocateRealWorldValueMapping();
	/// @see SetRealWorldValueMapping
	RealWorldValueMappingSequence* GetRealWorldValueMapping();
	/// @see SetRealWorldValueMapping
	const RealWorldValueMappingSequence* GetRealWorldValueMapping()const;
	/// Delete Real World Value Mapping
	void DeleteRealWorldValueMappingSequence();

	/// 3D AIT Image Frame Type [required]
	bool SetImageFrameType(const AIT3DTypes::AIT3DImageFrameType &ift);
	/// @see SetImageFrameType
	bool GetImageFrameType(AIT3DTypes::AIT3DImageFrameType &ift)const;
	/// Allocate Image Frame Type
	void AllocateImageFrameType();
	/// @see SetImageFrameType
	AIT3DTypes::AIT3DImageFrameType* GetImageFrameType();
	/// @see SetImageFrameType
	const AIT3DTypes::AIT3DImageFrameType* GetImageFrameType()const;
	/// Delete 3D AIT Image Frame Type
	void DeleteAIT3DImageFrameType();

	/// Pixel Intensity Relationship LUT Sequence [optional]
	bool SetPixelIntensityRelationshipLut(const PixelIntensityRelationshipLutSequence &pil);
	/// @see SetPixelIntensityRelationshipLut
	bool GetPixelIntensityRelationshipLut(PixelIntensityRelationshipLutSequence &pil)const;
	/// Allocate Pixel Intensity Relationship LUT
	void AllocatePixelIntensityRelationshipLut();
	/// @see SetPixelIntensityRelationshipLut
	PixelIntensityRelationshipLutSequence* GetPixelIntensityRelationshipLut();
	/// @see SetPixelIntensityRelationshipLut
	const PixelIntensityRelationshipLutSequence* GetPixelIntensityRelationshipLut()const;
	/// Delete Pixel Intensity Relationship LUT Sequence
	void DeletePixelIntensityRelationshipLut();

protected:
	class ImplAIT3DMultiframeFunctionalGroupMacros;
	ImplAIT3DMultiframeFunctionalGroupMacros* m_pImplAIT3DMFGM; ///< Internal implementation
};

}//namespace AIT3DTypes
}//namespace SDICOS

#endif
