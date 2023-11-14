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
#ifndef _STRATOVAN_DICOS_AIT_2D_IMAGE_H_
#define _STRATOVAN_DICOS_AIT_2D_IMAGE_H_

#include "SDICOS/VoiLut.h"
#include "SDICOS/ImagePixelModule.h"
#include "SDICOS/GeneralImageModule.h"
#include "SDICOS/ImageBase.h"
#include "SDICOS/AITImageType.h"

namespace SDICOS
{
namespace AIT2DTypes
{

///
/// \class AIT2DImage 
/// Implementation of 2D AIT Image which specializes
/// General Image Module and Image Pixel Module that also appear in 
/// the 2D AIT IOD Modules.
///
/// Tags with Updated meaning, definition, and values:
///		Image Type : Tag (0008, 0008) [Redefined from "General Image", changed to "required" from "optional" and overrides value 2]
///		Presentation LUT Shape : Tag (2050, 0020) [Redefined from "General Image", changed to "required" from "optional"]
///		Samples per Pixel [Redefined from "Image Pixel Module", sets value to "1"]
///
/// SPECREF V03 Section 9.2.3.2, Table 42
///
class AIT2DImage :	public ImagePixelModule,
					public GeneralImageModule,
					public ImageCommon
{
public:
	/// Constructor
	AIT2DImage();
	
	/// Copy Constructor
	AIT2DImage(const AIT2DImage &image);
	
	/// Destructor
	virtual ~AIT2DImage();

	/// Delete allocated resources
	void FreeMemory();

	/// Assignment operator
	AIT2DImage& operator=(const AIT2DImage &image);
	
	/// Equality Comparison operator
	bool operator==(const AIT2DImage &image)const;
	
	/// Inequality comparison operator
	bool operator!=(const AIT2DImage &image)const;

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if some attributes failed IsValid()
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// \enum AIT_DEVICE_TYPE
	/// Enumeration for AIT Device Type (0x4010, 0x1070)
	typedef enum
	{
		enumUnknownAitDeviceType,		///< Does not match defined terms

		enumPassiveMillimeterWave,		///< "PASSIVE_MMW"
		enumActiveMillimeterWave,		///< "ACTIVE_MMW"
		enumXrayBackscatter,			///< "XBS"
		enumTransmissionXray,			///< "TX"
		enumTerahertzImaging,			///< "THZ"
		enumActiveInfraredImaging,		///< "ACTIVE_IR"
		enumPassiveInfraredImaging,		///< "PASSIVE_IR"
		enumHDActiveMMW,				///< "HD_ACTIVE_MMW"
		enumWTActiveMMW,				///< "WT_ACTIVE_MMW" (WT = Walk-Through)

	}AIT_DEVICE_TYPE;

	/// \enum PIXEL_INTENSITY_RELATIONSHIP
	typedef enum
	{
		enumUnknownPixelIntensityRelationship,	///< Does not match defined terms

		enumLinear,			///< "LIN"
		enumLogarithmic,	///< "LOG"

	}PIXEL_INTENSITY_RELATIONSHIP;

	/// \enum PIXEL_INTENSITY_RELATIONSHIP_SIGN
	/// Attribute VR = SS (Signed Short)
	typedef enum
	{
		enumUnknownPixelIntensityRelationshipSign,	///< Does not match defined terms

		enumLowValueLowIntensity,	///< "1" : low pixel data values represent low detector intensities
		enumHighValueLowIntensity,	///< "-1" : high pixel data values represent low detector intensities

	}PIXEL_INTENSITY_RELATIONSHIP_SIGN;

	/// Set Pixel Data Characteristics, value 1 in Image Type : Tag (0008, 0008), VR = CS [required]
	/// @param nVal Pixel Data Characteristics
	/// @return true/false
	bool SetImageTypePixelCharacteristic(const ImageType::PIXEL_DATA_CHARACTERISTICS nVal);
	/// @return Pixel Data Characteristics
	/// @see SetImageTypePixelCharacteristic
	ImageType::PIXEL_DATA_CHARACTERISTICS GetImageTypePixelCharacteristic()const;
	/// @return Pixel Data Characteristics
	/// @see SetImageTypePixelCharacteristic
	DcsString GetImageTypePixelCharacteristicAsString()const;

	/// Set Image Characteristic, value 2 in Image Type : Tag (0008, 0008), VR = CS [required]
	/// @param nVal Image Characteristic
	/// @return true/false
	bool SetImageTypeAITImageCharacteristic(const SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS nVal);
	/// @return Image Characteristic
	/// @see SetImageTypeAITImageCharacteristic
	SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS GetImageTypeAITImageCharacteristic()const;
	/// @return Image Characteristic
	/// @see SetImageTypeAITImageCharacteristic
	DcsString GetImageTypeAITImageCharacteristicAsString()const;

	/// Set AIT Device Type
	///	@param nAitDeviceType AIT Device Type : Tag (4010, 1070), VR = CS [required]
	///			i) Values: "PASSIVE_MMW", "ACTIVE_MMW", "XBS", "TX", "THZ", "ACTIVE_IR", "PASSIVE_IR"
	/// @return true/false
	bool SetAitDeviceType(const AIT_DEVICE_TYPE nAitDeviceType);

	/// @see SetAitDeviceType
	AIT_DEVICE_TYPE GetAitDeviceType()const;
	
	/// @see SetAitDeviceType
	DcsString GetAitDeviceTypeAsString()const;

	/// Set the Photometric Interpretation.
	/// Photometric Interpretation is limited to MONOCHROME1, MONOCHROME2, PALETTE COLOR
	/// @param nPhotometricInterpretation Photometric Interpretation : Tag (0028, 0004), VR = CS [required]
	/// @return true/false
	virtual bool SetPhotometricInterpretation(const PHOTOMETRIC_INTERPRETATION nPhotometricInterpretation);

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

	/// Set Pixel Intensity Relationship : Tag (0028, 1040)
	/// @param nRelationship Pixel Intensity Relationship : Tag (0028, 1040), VR = CS [required]
	///			i) Values: "LIN", "LOG"
	/// @return true/false
	bool SetPixelIntensityRelationship(const PIXEL_INTENSITY_RELATIONSHIP nRelationship);

	/// @see SetPixelIntensityRelationship
	PIXEL_INTENSITY_RELATIONSHIP GetPixelIntensityRelationship()const;
	
	/// @see SetPixelIntensityRelationship
	DcsString GetPixelIntensityRelationshipAsString()const;
	
	/// Set Pixel Intensity Sign : Tag (0028, 1041)
	/// @param nSign Pixel Intensity Relationship Sign : Tag (0028, 1041), VR = SS [required]
	///			Values: "1" = low pixel data values represent low detector intensities, 
	///					"-1" = high pixel data values represent low detector intensities
	/// @return true/false
	bool SetPixelIntensitySign(const PIXEL_INTENSITY_RELATIONSHIP_SIGN nSign);

	/// @see SetPixelIntensitySign
	PIXEL_INTENSITY_RELATIONSHIP_SIGN GetPixelIntensitySign()const;
	
	/// @see SetPixelIntensitySign
	DcsString GetPixelIntensitySignAsString()const;
	
	/// Set Acquisition Device Processing Description : Tag (0018, 1400)
	///	@param strDescription	Acquisition Device Processing Description : Tag (0018, 1400), VR = LO [optional]
	/// @return true/false
	bool SetAcquisitionDeviceProcessingDescription(const DcsLongString &strDescription);

	/// @see SetAcquisitionDeviceProcessingDescription
	DcsString GetAcquisitionDeviceProcessingDescription() const;
	
	/// Has the Acquisition Device Processing Description attribute been set
	/// @return true/false
	bool HasAcquisitionDeviceProcessingDescription() const;

	/// Delete attribute so that it is not written to DICOS file.
	void DeleteAcquisitionDeviceProcessingDescription();
	
	/// Set Acquisition Device Processing Code : Tag (0018, 1401)
	///	@param strProcessingCode Acquisition Device Processing Code : Tag (0018, 1401), VR = LO [optional]
	/// @return true/false
	bool SetAcquisitionDeviceProcessingCode(const DcsLongString &strProcessingCode);

	/// @see SetAcquisitionDeviceProcessingCode
	DcsString GetAcquisitionDeviceProcessingCode()const;
	
	/// Has the Acquisition Device Processing Code been sent
	/// @return true/false
	bool HasAcquisitionDeviceProcessingCode() const;

	/// Delete the attribute so that it is not written to the DICOS file
	void DeleteAcquisitionDeviceProcessingCode();
	
	/// Set Calibration Image : Tag (0050, 0004)
	/// @param nIsCalibrationImage Is a Calibration Image : Tag (0050, 0004), VR = CS [optional]
	///			i) true = "YES", false = "NO"
	/// @return true/false
	bool SetCalibrationImage(const bool nIsCalibrationImage);

	/// @see SetCalibrationImage
	bool IsCalibrationImage()const;
	
	/// @see SetCalibrationImage
	DcsString IsCalibrationImageAsString()const;
	
	/// @see SetCalibrationImage
	/// @param bIsCalibrationImage true/false indicating calibration image
	/// @return DcsString
	static DcsString CalibrationImageAsString(const bool bIsCalibrationImage);

	/// Set VOI LUT Sequence
	///	Updated requirement:
	///		Required if Presentation Intent Type (0008, 0068), in AIT2DSeries, 
	///		is "FOR PRESENTATION" and Window Center (0028, 1050) is not set]
	///		May be present if Window Center is present.
	///		The 'VOI LUT FUNCTION' attribute is not used.
	/// @param lut	VoiLut Sequence object
	/// @return true/false
	bool SetVoiLut(const VoiLut &lut);

	/// @see SetVoiLut
	bool GetVoiLut(VoiLut &lut)const;

	/// @see SetVoiLut
	VoiLut& GetVoiLut();
	
	/// @see SetVoiLut
	const VoiLut& GetVoiLut() const;
	
	/// Convert Device Type to DcsString representation
	static DcsString DeviceTypeToString(const AIT_DEVICE_TYPE dt);
	
protected:
	class ImplAIT2DImage;
	ImplAIT2DImage	*m_pImplAIT2DImage; ///< Internal implementation

	ImplAIT2DImage* GetImpl();
	const ImplAIT2DImage* GetImpl() const;
	
	/// Set Samples per Pixel : Tag (0028, 0002)
	/// @param nSamplesPerPixel Samples per Pixel : Tag (0028, 0002), VR = US [required]
	///			i) Value: "1"
	/// @return true/false
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

private:

	/// This method from ImageType always returns false
	/// @return false
	virtual bool SetImageType(const PIXEL_DATA_CHARACTERISTICS);

	/// This method from ImageType always returns false
	virtual bool SetImageType(const PIXEL_DATA_CHARACTERISTICS, const IMAGE_CHARACTERISTICS);
};

}//namespace AIT2DTypes
}//namespace SDICOS

#endif
