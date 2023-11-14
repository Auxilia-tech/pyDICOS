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
#ifndef _STRATOVAN_DICOS_AIT_3D_IMAGE_FRAME_TYPE_H_
#define _STRATOVAN_DICOS_AIT_3D_IMAGE_FRAME_TYPE_H_

#include "SDICOS/CommonImageDescription.h"
#include "SDICOS/AIT3DImage.h"

namespace SDICOS
{
namespace AIT3DTypes
{

///
/// \class AIT3DImageFrameType
/// \brief Implements 3D AIT Image Frame Type, a required single item sequence (0018, 9329)
/// SPECREF V03 Section 9.3.3.3.1, Table 50
///
class AIT3DImageFrameType
{
public:
	/// Constructor
	AIT3DImageFrameType();
	/// Copy constructor
	AIT3DImageFrameType(const AIT3DImageFrameType &ift);
	/// Destructor
	virtual ~AIT3DImageFrameType();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	AIT3DImageFrameType& operator=(const AIT3DImageFrameType &ift);
	/// Comparison operator
	bool operator==(const AIT3DImageFrameType &ift)const;
	/// Comparison operator
	bool operator!=(const AIT3DImageFrameType &ift)const;

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

	/// Frame Type : Tag (0008, 9007), VM = 4, VR = CS [required]
	/// @param nCharacteristics Values: enumOriginal, enumDerived
	/// @param nImageCharacteristics Values: enumCNT_AMP, enumCNT_CPX_AMP, enumNoImageCharacteristic
	/// @param nFlavor Values: enumProjection, enumVolume
	/// @param nContrast enumAddition, enumDivision, enumMasked, enumMaximum, enumMultiplication, enumResampled, enumStdDeviation, enumSubtraction, enumNone
	bool SetFrameType(	const AIT3DImage::AIT3D_PIXEL_DATA_CHARACTERISTICS nCharacteristics, 
						const AITImageType::AIT_IMAGE_CHARACTERISTICS nImageCharacteristics,
						const AIT3DImage::IMAGE_FLAVOR nFlavor, 
						const AIT3DImage::DERIVED_PIXEL_CONTRAST nContrast);
	/// @see SetFrameType
	bool GetFrameType(	AIT3DImage::AIT3D_PIXEL_DATA_CHARACTERISTICS &nCharacteristics, 
						AITImageType::AIT_IMAGE_CHARACTERISTICS &nImageCharacteristics,
						AIT3DImage::IMAGE_FLAVOR &nFlavor, 
						AIT3DImage::DERIVED_PIXEL_CONTRAST &nContrast)const;
	
	/// @see GetFrameType
	AIT3DImage::AIT3D_PIXEL_DATA_CHARACTERISTICS GetPixelDataCharacteristics() const;
	
	AITImageType::AIT_IMAGE_CHARACTERISTICS GetImageCharacteristics() const;

	/// @see GetFrameType
	AIT3DImage::IMAGE_FLAVOR GetImageFlavor() const;
	
	/// @see GetFrameType
	AIT3DImage::DERIVED_PIXEL_CONTRAST GetDerivedPixelContrast() const;
	
	/// @see SetFrameType
	bool GetFrameType(DcsString &strCharacteristics, DcsString &strImageCharacteristics, DcsString &strFlavor, DcsString &strContrast)const;

	/// Common CT Image Description [required]
	bool SetCommonImageDescription(const CommonImageDescription &commonimagedescription);
	/// @see SetCommonImageDescription
	bool GetCommonImageDescription(CommonImageDescription &commonimagedescription)const;
	/// @see SetCommonImageDescription
	CommonImageDescription& GetCommonImageDescription();
	/// @see SetCommonImageDescription
	const CommonImageDescription& GetCommonImageDescription()const;

protected:
	class ImplAIT3DImageFrameType;
	ImplAIT3DImageFrameType	*m_pImplAIT3DImageFrameType; ///< Internal implementation
};

}//namespace AIT3DTypes
}//namespace SDICOS

#endif
