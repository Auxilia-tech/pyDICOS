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
#ifndef _STRATOVAN_DICOS_DX_IMAGE_H_
#define _STRATOVAN_DICOS_DX_IMAGE_H_

#include "SDICOS/VoiLut.h"
#include "SDICOS/ImageBase.h"
#include "SDICOS/ImagePixelModule.h"
#include "SDICOS/GeneralImageModule.h"
#include "SDICOS/ImageCharacteristics.h"

namespace SDICOS
{
namespace DXTypes
{

///
/// \class DXImage
/// \brief Implements DX/X-Ray Image
/// SPECREF V03 Section 8.2.2.2, Table 35
///
////////////////////////////////////////////////////////
///  Updated attributes:
/// Image Type : Tag (0008, 0008)[Redefined from "General Image", changed to "required" from "optional"]
/// Presentation LUT Shape : Tag (2050, 0020) [Redefined from "General Image", changed to "required" from "optional"]
/// Photometric Interpretation : Tag (0028, 0004) [Redefined from "Image Pixel Module", limits enumerated values]
/// -Values: DXImage::enumMonochrome1, DXImage::enumMonochrome2, DXImage::enumPaletteColor
/// Samples per Pixel [Redefined from "Image Pixel Module", sets value to "1"]
////////////////////////////////////////////////////////
///
class DXImage : public ImagePixelModule,
				public GeneralImageModule,
				public ImageCharacteristics,
				public ImageCommon
{
public:
	/// Constructor
	DXImage();
	/// Copy constructor
	DXImage(const DXImage &dximage);
	/// Destructor
	~DXImage();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	DXImage& operator=(const DXImage &dximage);
	/// Comparison operator
	bool operator==(const DXImage &dximage)const;
	/// Comparison operator
	bool operator!=(const DXImage &dximage)const;

	/// Pixel Intensity Relationship enumerations
	typedef enum
	{
		enumUnknownPixelIntensityRelationship, ///< Unknown enumeration

		enumLinear,			///< "LIN"
		enumLogarithmic,	///< "LOG"

	}PIXEL_INTENSITY_RELATIONSHIP;

	/// Pixel Intensity Relationship Sign enumerations
	typedef enum
	{
		enumUnknownPixelIntensityRelationshipSign, ///< Unknown enumeration

		enumLowValueLowIntensity,	///< "1" : low pixel data values represent low detector intensities
		enumHighValueLowIntensity,	///< "-1" : high pixel data values represent low detector intensities

	}PIXEL_INTENSITY_RELATIONSHIP_SIGN;

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

	///
	/// Photometric Interpretation : Tag (0028, 0004), VR = CS [required]
	/// When set to enumMonochrome1, Presentation LUT Shape is set to enumInverse
	/// When set to enumMonochrome2, Presentation LUT Shape is set to enumIdentity
	///
	/// @param nPhotometricInterpretation Values restricted to: enumMonochrome1, enumMonochrome2, enumPaletteColor
	virtual bool SetPhotometricInterpretation(const PHOTOMETRIC_INTERPRETATION nPhotometricInterpretation);

	/// Pixel Intensity Relationship : Tag (0028, 1040), VR = CS [required]
	bool SetPixelIntensityRelationship(const PIXEL_INTENSITY_RELATIONSHIP nRelationship);
	/// @see SetPixelIntensityRelationship
	PIXEL_INTENSITY_RELATIONSHIP GetPixelIntensityRelationship()const;
	/// @see SetPixelIntensityRelationship
	DcsString GetPixelIntensityRelationshipAsString()const;

	/// Pixel Intensity Sign : Tag (0028, 1041), VR = SS [required]
	bool SetPixelIntensitySign(const PIXEL_INTENSITY_RELATIONSHIP_SIGN nSign);
	/// @see SetPixelIntensitySign
	PIXEL_INTENSITY_RELATIONSHIP_SIGN GetPixelIntensitySign()const;
	/// @see SetPixelIntensitySign
	S_INT16 GetPixelIntensitySignAsInt()const;

	/// Rescale Slope (Set to 1) : Tag (0028, 1053), VR = DS [required]
	/// @return Returns 1
	float GetRescaleSlope()const;
	/// @see GetRescaleSlope
	DcsString GetRescaleSlopeAsString()const;

	/// Rescale Intercept (Set to 0) : Tag (0028, 1052), VR = DS [required]
	/// @return Returns 0
	float GetRescaleIntercept()const;
	/// @see GetRescaleIntercept
	DcsString GetRescaleInterceptAsString()const;

	/// Rescale Type (Specifies output units) : Tag (0028, 1054), VR = LO [required]
	bool SetRescaleType(const DcsLongString &strType);
	/// @see SetRescaleType
	DcsString GetRescaleType()const;

	/// Acquisition Device Processing Description : Tag (0018, 1400), VR = LO [optional]
	bool SetAcquisitionDeviceProcessingDescription(const DcsLongString &strDescription);
	/// @see SetAcquisitionDeviceProcessingDescription
	DcsString GetAcquisitionDeviceProcessingDescription();
	/// @see SetAcquisitionDeviceProcessingDescription
	void DeleteAcquisitionDeviceProcessingDescription();

	/// Acquisition Device Processing Code : Tag (0018, 1401), VR = LO [optional]
	bool SetAcquisitionDeviceProcessingCode(const DcsLongString &strProcessingCode);
	/// @see SetAcquisitionDeviceProcessingCode
	DcsString GetAcquisitionDeviceProcessingCode()const;
	/// Delete Acquisition Device Processing Code
	void DeleteAcquisitionDeviceProcessingCode();

	/// Calibration Image : Tag (0050, 0004), VR = CS [optional]
	/// @param nIsCalibrationImage true = "YES", false = "NO"
	bool SetCalibrationImage(const bool nIsCalibrationImage);
	/// @see SetCalibrationImage
	bool IsCalibrationImage()const;
	/// @see SetCalibrationImage
	DcsString GetCalibrationImageAsString()const;
	/// Delete Calibration Image
	void DeleteCalibrationImage();

	/// VOI LUT [required if Presentation Intent Type (0008, 0068) is "FOR PRESENTATION" and Window Center (0028, 1050) is not present]
	bool SetVoiLut(const VoiLut &lut);
	/// @see SetVoiLut
	bool GetVoiLut(VoiLut &lut)const;
	/// @see SetVoiLut
	VoiLut& GetVoiLut();
	/// @see SetVoiLut
	const VoiLut& GetVoiLut()const;

	/// Distance between pixel centers in millimeters [optional]
	bool SetReportedPixelSpacingInMM(const float fRow, const float fCol);
	/// @see SetReportedPixelSpacingInMM
	float GetReportedPixelSpacingRowInMM()const;
	/// @see SetReportedPixelSpacingInMM
	float GetReportedPixelSpacingColumnInMM()const;
	/// Returns true if data is present
	bool HasReportedPixelSpacing()const;
	/// @see SetReportedPixelSpacingInMM
	void DeleteReportedPixelSpacing();

	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 8, bits stored to 8, high bit to 7, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OB [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_UINT8> &arrayData);

	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 16, bits stored to 16, high bit to 15, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_UINT16> &arrayData);

	/// Set pixel data (7FE0, 0011).  Sets bits allocated to 32, bits stored to 32, high bit to 31, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_UINT32> &arrayData);

	/// Set pixel data (7FE0, 0012).  Sets bits allocated to 64, bits stored to 64, high bit to 63, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_UINT64> &arrayData);

	/// Set pixel data (7FE0, 0013).  Sets bits allocated to 32, bits stored to 32, high bit to 31, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<float> &arrayData);

	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_UINT8> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_UINT16> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_UINT32> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_UINT64> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<float> &arrayData)const;
	
	///
	/// Set Pixel Data Provider URL (0028, 7FE0).  Must also provide pixel data information.  Pixel data (7FE0, 0010) must not be present to call this function.
	///	Samples per pixel set to 1. Pixel Representation set to unsigned.
	/// 
	/// @param strURL Pixel Data Provider URL : Tag (0028, 7FE0), VR = UT [Required if transfer syntax (0002, 0010) is "1.2.840.10008.1.2.4.94" or "1.2.840.10008.1.2.4.95"]
	/// @param nRows Rows in image
	/// @param nColumns Columns in image
	/// @param nBitsAllocated Bits allocated per sample. Must be an even number one of [8, 16, 32, 64].
	/// @param nBitsStored Bits stored. Must be an even number less than bits allocated and restricted to [8, 16, 32, 64]
	/// @param nHighBit High bit
	///	@return true/false
	///
	virtual bool SetPixelDataProviderURL(const DcsUnlimitedText &strURL, 
										const S_UINT16 nRows, const S_UINT16 nColumns, 
										const S_UINT16 nBitsAllocated, const S_UINT16 nBitsStored, const S_UINT16 nHighBit);

	/// Set Image Type : Tag (0008, 0008), VR = CS [required]
	///
	/// @param nPixelDataCharacteristics Pixel Data Characteristics (Value 1 in attribute)
	/// @param nImgCharacteristics Image Characteristics (Value 2 in attribute)
	virtual bool SetImageType(const PIXEL_DATA_CHARACTERISTICS nPixelDataCharacteristics, OOI_IMAGE_CHARACTERISTICS nImgCharacteristics);
	
	/// Set Image Type : Tag (0008, 0008), VR = CS [required]
	///
	/// @param nPixelDataCharacteristics Pixel Data Characteristics (Value 1 in attribute)
	/// @param nImgCharacteristics Image Characteristics (Value 2 in attribute)
	/// @param dsLowLevelEnergyThreshold Multi-energy, higher-level energy threshold (Value 3 in attribute)
	/// @param dsHighLevelEnergyThreshold Multi-energy, lower-level energy threshold (Value 4 in attribute)
	/// @param dsEnergyResolution Energy Resolution (Value 5 in attribute)
	virtual bool SetImageType(const PIXEL_DATA_CHARACTERISTICS nPixelDataCharacteristics, OOI_IMAGE_CHARACTERISTICS nImgCharacteristics,
								const DcsCodeString &dsLowLevelEnergyThreshold, const DcsCodeString &dsHighLevelEnergyThreshold, const DcsCodeString &dsEnergyResolution);

	/// @see SetImageType
	PIXEL_DATA_CHARACTERISTICS GetPixelDataCharacteristics()const;
	/// @see SetImageType
	OOI_IMAGE_CHARACTERISTICS GetImageCharacteristics()const;
	/// @see SetImageType
	DcsString GetLowLevelEnergyThreshold()const;
	/// @see SetImageType
	DcsString GetHighLevelEnergyThreshold()const;
	/// @see SetImageType
	DcsString GetEnergyResolution()const;
	
	/// @see SetImageType
	virtual bool GetImageType(PIXEL_DATA_CHARACTERISTICS &nPixelDataCharacteristics, OOI_IMAGE_CHARACTERISTICS &nImageCharacteristics)const;
	/// @see SetImageType
	virtual bool GetImageType(DcsString &strPixelDataCharacteristics, DcsString &strImageCharacteristics)const;
	
	/// Delete attribute
	virtual void DeleteImageType();
protected:
	class ImplDXImage;
	ImplDXImage	*m_pImplDXImage; ///< Internal implementation

	/// Disabled V02 function
	virtual PIXEL_DATA_CHARACTERISTICS GetImageType()const;
	/// Disabled V02 function
	virtual DcsString GetImageTypeAsString()const;
	/// Disabled V02 function
	virtual bool GetImageType(PIXEL_DATA_CHARACTERISTICS &nPixelDataCharacteristics, IMAGE_CHARACTERISTICS &nImageCharacteristics)const;

	/// Samples per Pixel set to 1
	virtual bool SetSamplesPerPixel(const S_UINT16 nSamplesPerPixel);
	/// Signed data not allowed
	virtual bool SetPixelData(const Array2D<S_INT8> &arrayData);
	virtual bool SetPixelData(const Array2D<S_INT16> &arrayData);
	virtual bool SetPixelData(const Array2D<S_INT32> &arrayData);
	virtual bool SetPixelData(const Array2D<S_INT64> &arrayData);
	virtual bool GetPixelData(Array2D<S_INT8> &arrayData)const;
	virtual bool GetPixelData(Array2D<S_INT16> &arrayData)const;
	virtual bool GetPixelData(Array2D<S_INT32> &arrayData)const;
	virtual bool GetPixelData(Array2D<S_INT64> &arrayData)const;

	/// Disable 3D data
	virtual bool SetPixelData(const Array3DLarge<S_INT8> &arrayData);
	virtual bool SetPixelData(const Array3DLarge<S_INT16> &arrayData);
	virtual bool SetPixelData(const Array3DLarge<S_INT32> &arrayData);
	virtual bool SetPixelData(const Array3DLarge<S_INT64> &arrayData);
	virtual bool SetPixelData(const Array3DLarge<S_UINT8> &arrayData);
	virtual bool SetPixelData(const Array3DLarge<S_UINT16> &arrayData);
	virtual bool SetPixelData(const Array3DLarge<S_UINT32> &arrayData);
	virtual bool SetPixelData(const Array3DLarge<S_UINT64> &arrayData);
	virtual bool SetPixelData(const Array3DLarge<float> &arrayData);
	virtual bool GetPixelData(Array3DLarge<S_UINT8> &arrayData)const;
	virtual bool GetPixelData(Array3DLarge<S_UINT16> &arrayData)const;
	virtual bool GetPixelData(Array3DLarge<S_UINT32> &arrayData)const;
	virtual bool GetPixelData(Array3DLarge<S_UINT64> &arrayData)const;
	virtual bool GetPixelData(Array3DLarge<S_INT8> &arrayData)const;
	virtual bool GetPixelData(Array3DLarge<S_INT16> &arrayData)const;
	virtual bool GetPixelData(Array3DLarge<S_INT32> &arrayData)const;
	virtual bool GetPixelData(Array3DLarge<S_INT64> &arrayData)const;
	virtual bool GetPixelData(Array3DLarge<float> &arrayData)const;

	virtual bool SetImageType(const PIXEL_DATA_CHARACTERISTICS nPixelDataCharacteristics);
	virtual bool SetImageType(const PIXEL_DATA_CHARACTERISTICS nPixelDataCharacteristics, const IMAGE_CHARACTERISTICS nImageCharacteristics);
};

}//namespace DXTypes
}//namespace SDICOS

#endif
