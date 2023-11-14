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
#ifndef _STRATOVAN_DICOS_CT_IMAGE_FRAME_TYPE_H_
#define _STRATOVAN_DICOS_CT_IMAGE_FRAME_TYPE_H_

#include "SDICOS/CTImage.h"

namespace SDICOS
{

namespace CTTypes
{

///
/// \class CTImageFrameType
/// \brief Implements CT Image Frame Type, a required single item sequence (0018, 9329)
/// SPECREF V03 Section 7.4.3.1, Table 22
///
class CTImageFrameType
{
public:
	/// Constructor
	CTImageFrameType();
	/// Copy constructor
	CTImageFrameType(const CTImageFrameType &ift);
	/// Destructor
	virtual ~CTImageFrameType();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	CTImageFrameType& operator=(const CTImageFrameType &ift);
	/// Comparison operator
	bool operator==(const CTImageFrameType &ift)const;
	/// Comparison operator
	bool operator!=(const CTImageFrameType &ift)const;

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

	/// Frame Type : Tag (0008, 9007), VR = CS [required]
	/// @param nPixel Pixel Data Characteristics. Values: CTImage::enumOriginal, CTImage::enumDerived
	/// @param nOOI OOI Image Characteristics. Values: CTImage::enumHighEnergy, CTImage::enumLowEnergy, CTImage::enumZ_Effective, CTImage::enumBasisMaterial_1, CTImage::enumBasisMaterial_2, CTImage::enumCompton, CTImage::enumPhotoelectric
	/// @param nFlavor Image Flavor. CTImage::enumProjection, CTImage::enumVolume
	/// @param nContrast Derived Pixel Contrast CTImage::enumAddition, CTImage::enumDivision, CTImage::enumMasked, CTImage::enumMaximum, CTImage::enumMultiplication, CTImage::enumResampled, CTImage::enumStdDeviation, CTImage::enumSubtraction, CTImage::enumNone
	bool SetFrameType(	const CTImage::CT_PIXEL_DATA_CHARACTERISTICS nPixel, 
						const CTImage::OOI_IMAGE_CHARACTERISTICS nOOI, 
						const CTImage::IMAGE_FLAVOR nFlavor, 
						const CTImage::DERIVED_PIXEL_CONTRAST nContrast);
	/// @see SetFrameType
	bool GetFrameType(	CTImage::CT_PIXEL_DATA_CHARACTERISTICS &nPixel, 
						CTImage::OOI_IMAGE_CHARACTERISTICS &nOOI, 
						CTImage::IMAGE_FLAVOR &nFlavor, 
						CTImage::DERIVED_PIXEL_CONTRAST &nContrast)const;
	/// @see SetFrameType
	bool GetFrameType(DcsString &strPixel, DcsString &strOOI, DcsString &strFlavor, DcsString &strContrast)const;

	/// Basis Materials Code Sequence (Single Item Sequence) : Tag (4010, 1045), VR = SQ [optional]
	bool SetBasisMaterial(const CodeSequence &csBasisMaterial);
	//		a) Param 1, Basis Materials Code Sequence
	//			i) Context ID not defined
	/// @see SetBasisMaterial
	bool GetBasisMaterial(CodeSequence &csBasisMaterial)const;
	/// AllocateBasis Material
	void AllocateBasisMaterial();
	/// Get Basis Materials
	CodeSequence* GetBasisMaterial();
	/// @see SetBasisMaterial
	const CodeSequence* GetBasisMaterial()const;
	/// Delete Basis Materials
	void DeleteBasisMaterial();

	/// Common CT Image Description [required]
	bool SetCommonImageDescription(const CommonImageDescription &commonimagedescription);
	/// @see SetCommonImageDescription
	bool GetCommonImageDescription(CommonImageDescription &commonimagedescription)const;
	/// @see SetCommonImageDescription
	CommonImageDescription& GetCommonImageDescription();
	/// @see SetCommonImageDescription
	const CommonImageDescription& GetCommonImageDescription()const;

protected:
	class ImplCTImageFrameType;
	ImplCTImageFrameType	*m_pImplCTImageFrameType; ///< Internal implementation
};

}//namespace CTTypes

}//namespace SDICOS

#endif
	
