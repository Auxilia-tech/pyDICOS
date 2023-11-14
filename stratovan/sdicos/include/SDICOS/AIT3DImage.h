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
#ifndef _STRATOVAN_DICOS_AIT_3D_IMAGE_H_
#define _STRATOVAN_DICOS_AIT_3D_IMAGE_H_

#include "SDICOS/ImagePixelModule.h"
#include "SDICOS/GeneralImageModule.h"
#include "SDICOS/HierarchicalReferences.h"
#include "SDICOS/CommonImageDescription.h"
#include "SDICOS/ImageBase.h"
#include "SDICOS/AITImageType.h"

namespace SDICOS
{
namespace AIT3DTypes
{

///
/// \class AIT3DImage
/// \brief Implements 3D AIT Image
/// SPECREF V03 Section 9.3.3.2, Table 48
///
/////////////////////////////////////////////////
///  Updated requirements:
///
/// Samples per Pixel : Tag (0028, 0002), VR = US [Redefined from "Image Pixel Module", sets value]
///	-Value set to 1
///
/// Photometric Interpretation : Tag (0028, 0004), VR = CS [redefined from "Image Pixel Module", limits values]
///	-Values: enumMonochrome1, enumMonochrome2, enumPaletteColor
/////////////////////////////////////////////////
class AIT3DImage :	public ImagePixelModule, public ImageCommon
{
public:
	/// Constructor
	AIT3DImage();
	/// Copy Constructor
	AIT3DImage(const AIT3DImage &ait);
	/// Destructor
	~AIT3DImage();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	AIT3DImage& operator=(const AIT3DImage &ait);
	/// Comparison operator
	bool operator==(const AIT3DImage &ait)const;
	/// Comparison operator
	bool operator!=(const AIT3DImage &ait)const;


	/// Pixel Data Characteristics enumerations
	typedef enum
	{
		enumUnknownAIT3DPixelDataCharacteristics, ///< Unknown enumeration

		enumOriginal,				///< "ORIGINAL"
		enumDerived,				///< "DERIVED"
		enumMixedCharacteristics,	///< "MIXED"

	}AIT3D_PIXEL_DATA_CHARACTERISTICS;

	/// Image Flavor enumerations
	typedef enum
	{
		enumUnknownImageFlavor, ///< Unknown enumeration

		enumProjection,	///< "PROJECTION"
		enumVolume,		///< "VOLUME"

	}IMAGE_FLAVOR;

	/// Derived Pixel Contrast enumerations
	typedef enum
	{
		enumUnknownDerivedPixelContrast, ///< Unknown enumeration

		enumAddition,			///< "ADDITION"
		enumDivision,			///< "DIVISION"
		enumMasked,				///< "MASKED"
		enumMaximum,			///< "MAXIMUM"
		enumMultiplication,		///< "MULTIPLICATION"
		enumResampled,			///< "RESAMPLED"
		enumStdDeviation,		///< "STD_DEVIATION"
		enumSubtraction,		///< "SUBTRACTION"
		enumNone,				///< "NONE"
		enumMixedContrast,		///< "MIXED"

	}DERIVED_PIXEL_CONTRAST;
	
	/// AIT Device Type enumerations
	typedef enum
	{
		enumUnknownAitDeviceType,		///< Unknown enumeration

		enumPassiveMillimeterWave,		///< "PASSIVE_MMW"
		enumActiveMillimeterWave,		///< "ACTIVE_MMW"
		enumTerahertzImaging,			///< "THZ"

	}AIT_DEVICE_TYPE;

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

	/// Image Type : Tag (0008, 0008), VM = 4, VR = CS [required]
	bool SetImageTypeAIT3D(	const AIT3D_PIXEL_DATA_CHARACTERISTICS nPixel,
							const SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS nImage, 
							const IMAGE_FLAVOR nFlavor,
							const DERIVED_PIXEL_CONTRAST nContrast);
	/// @see SetImageTypeAIT3D
	bool GetImageTypeAIT3D(	AIT3D_PIXEL_DATA_CHARACTERISTICS &nPixel,
							SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS &nImage, 
							IMAGE_FLAVOR &nFlavor, 
							DERIVED_PIXEL_CONTRAST &nContrast)const;
	/// @see SetImageTypeAIT3D
	bool GetImageTypeAIT3D(DcsString &strPixel, DcsString &strImage, DcsString &strFlavor, DcsString &strContrast)const;

	/// AIT Device Type : Tag (4010, 1070), VR = CS [required]
	bool SetAitDeviceType(const AIT_DEVICE_TYPE nType);
	/// @see SetAitDeviceType
	AIT_DEVICE_TYPE GetAitDeviceType()const;
	/// @see SetAitDeviceType
	DcsString GetAitDeviceTypeAsString()const;

	/// Common Image Description [required]
	bool SetCommonImageDescription(const CommonImageDescription &commonimagedescription);
	/// @see SetCommonImageDescription
	bool GetCommonImageDescription(CommonImageDescription &commonimagedescription)const;
	/// @see SetCommonImageDescription
	CommonImageDescription& GetCommonImageDescription();
	/// @see SetCommonImageDescription
	const CommonImageDescription& GetCommonImageDescription()const;

	///
	/// Photometric Interpretation : Tag (0028, 0004), VR = CS (redefined from "Image Pixel Module", limits values) [required]
	/// @param nPhotometricInterpretation Values: Image3DAIT::enumMonochrome1, Image3DAIT::enumMonochrome2, Image3DAIT::enumPaletteColor
	///
	virtual bool SetPhotometricInterpretation(const PHOTOMETRIC_INTERPRETATION nPhotometricInterpretation);

	/// Acquisition DateTime : Tag (0008, 002A), VR = DT [required if "Image Type" (AIT3D_PIXEL_DATA_CHARACTERISTICS) is "ORIGINAL" or "MIXED"]
	bool SetAcquisitionDateAndTime(const DcsDateTime &strDateTime);
	/// @see SetAcquisitionDateAndTime
	bool GetAcquisitionDateAndTime(DcsDate &strDate, DcsTime &strTime)const;
	/// Returns in VR = DT format
	DcsDateTime GetAcquisitionDateAndTime()const;

	/// Acquisition Duration : Tag (0018, 9073), VR = FD [required if "Image Type" (AIT3D_PIXEL_DATA_CHARACTERISTICS) is "ORIGINAL" or "MIXED"]
	bool SetAcquisitionDuration(const double nAcquisitionDuration);
	/// @see SetAcquisitionDuration
	double GetAcquisitionDuration()const;

	/// Set Acquisition Number : Tag (0020, 0012).
	/// @param nAcquisitionNumber Acquisition Number : Tag (0020, 0012), VR = IS [optional]
	/// @return true/false 
	bool SetAcquisitionNumber(const S_INT32 nAcquisitionNumber);
	/// @see SetAcquisitionNumber
	S_INT32 GetAcquisitionNumber()const;
	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteAcquisitionNumber();
	/// Returns true if a acquisition number has been set and not deleted
	bool HasAcquisitionNumber() const;
	
	/// Referenced Raw Data Sequence : Tag (0008, 9121), VR = SQ [optional]
	bool SetReferencedRawData(const Array1D<HierarchicalSopInstanceReference> &arrayReferences);
	/// @see SetReferencedRawData
	bool GetReferencedRawData(Array1D<HierarchicalSopInstanceReference> &arrayReferences)const;
	/// @see SetReferencedRawData
	Array1D<HierarchicalSopInstanceReference>& GetReferencedRawData();
	/// @see SetReferencedRawData
	const Array1D<HierarchicalSopInstanceReference>& GetReferencedRawData()const;
	/// Delete Referenced Raw Data Sequence
	void DeleteReferencedRawData();

	/// Referenced Image Evidence Sequence : Tag (0008, 9092), VR = SQ [optional]
	bool SetReferencedImageEvidence(const Array1D<HierarchicalSopInstanceReference> &arrayReferences);
	/// @see SetReferencedImageEvidence
	bool GetReferencedImageEvidence(Array1D<HierarchicalSopInstanceReference> &arrayReferences)const;
	/// @see SetReferencedImageEvidence
	Array1D<HierarchicalSopInstanceReference>& GetReferencedImageEvidence();
	/// @see SetReferencedImageEvidence
	const Array1D<HierarchicalSopInstanceReference>& GetReferencedImageEvidence()const;
	/// Delete Referenced Image Evidence Sequence
	void DeleteReferencedImageEvidence();

	/// Source Image Evidence Sequence : Tag (0008, 9154), VR = SQ [optional]
	bool SetSourceImageEvidence(const Array1D<HierarchicalSopInstanceReference> &arrayReferences);
	/// @see SetSourceImageEvidence
	bool GetSourceImageEvidence(Array1D<HierarchicalSopInstanceReference> &arrayReferences)const;
	/// @see SetSourceImageEvidence
	Array1D<HierarchicalSopInstanceReference>& GetSourceImageEvidence();
	/// @see SetSourceImageEvidence
	const Array1D<HierarchicalSopInstanceReference>& GetSourceImageEvidence()const;
	/// Delete Source Image Evidence Sequence
	void DeleteSourceImageEvidence();

	/// Referenced Presentation State Sequence : Tag (0008, 9237), VR = SQ [optional]
	bool SetReferencedPresentationState(const Array1D<HierarchicalSopInstanceReference> &arrayReferences);
	/// @see SetReferencedPresentationState
	bool GetReferencedPresentationState(Array1D<HierarchicalSopInstanceReference> &arrayReferences)const;
	/// @see SetReferencedPresentationState
	Array1D<HierarchicalSopInstanceReference>& GetReferencedPresentationState();
	/// @see SetReferencedPresentationState
	const Array1D<HierarchicalSopInstanceReference>& GetReferencedPresentationState()const;
	/// Delete Referenced Presentation State Sequence
	void DeleteReferencedPresentationState();

	/// Image Comments : Tag (0020, 4000), VR = LT [optional]
	bool SetImageComments(const DcsLongText &strComments);
	/// @see SetImageComments
	DcsString GetImageComments()const;
	/// Delete Image Comments
	void DeleteImageComments();

protected:
	class ImplAIT3DImage;
	ImplAIT3DImage	*m_pImplAIT3DImage; ///< Internal implementation
	
	///
	/// Samples per Pixel : Tag (0028, 0002), VR = US [required]
	///	@param nSamplesPerPixel Value set to 1
	///
	virtual bool SetSamplesPerPixel(const S_UINT16 nSamplesPerPixel);
};

}//namespace AIT3DTypes
}//namespace SDICOS

#endif
