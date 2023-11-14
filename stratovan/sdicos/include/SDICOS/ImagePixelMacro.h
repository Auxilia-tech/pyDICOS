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
#ifndef _STRATOVAN_DICOS_IMAGE_PIXEL_MACRO_H_
#define _STRATOVAN_DICOS_IMAGE_PIXEL_MACRO_H_

#include "SDICOS/Types.h"
#include "SDICOS/String.h"
#include "SDICOS/PaletteColorLookupTable.h"

namespace SDICOS
{

class Volume;

///
/// \class ImagePixelMacro
/// \brief Implements image pixel macro
/// SPECREF V03 Section 14.2.1, Table 86
///
class ImagePixelMacro
{
public:

	///
	/// Enumeration of photometric interpretation
	///	Describes how the image data is interpreted.
	///
	typedef enum
	{
		enumUnknownPhotometricInterpretation,	///< Does not match defined terms

		enumMonochrome1,		///< "MONOCHROME1", Minimum pixel value is white
		enumMonochrome2,		///< "MONOCHROME2", Minimum pixel value is black
		enumPaletteColor,		///< "PALETTE COLOR", 
		enumRGB,				///< "RGB", 
		enumYBR_Full,			///< "YBR_FULL", 
		enumYBR_Full_422,		///< "YBR_FULL_422", 
		enumYBR_Partial_422,	///< "YBR_PARTIAL_422", 
		enumYBR_Partial_420,	///< "YBR_PARTIAL_420", 
		enumYBR_ICT,			///< "YBR_ICT", 
		enumYBR_RCT,			///< "YBR_RCT"

	}PHOTOMETRIC_INTERPRETATION;
	
	///
	/// Enumeration of pixel representation
	///
	typedef enum
	{
		enumUnknownPixelRepresentation,	///< Does not match defined terms

		enumUnsignedInteger,	///< Image data uses unsigned integer
		enumSignedInteger,		///< Image data uses signed integer

	}PIXEL_REPRESENTATION;

	///
	/// Enumeration of planar configuration
	///
	typedef enum
	{
		enumUnknownPlanarConfiguration,	///< Does not match defined terms

		enumColorByPixel,	///< rgb image saved as "R0, G0, B0, R1, G1,...".
		enumColorByPlane,	///< image saved as "R0, R1, R2,..., G0, G1, G2,..., B0, B1, B2..."

	}PLANAR_CONFIGURATION;

	///
	/// Initialize with default values
	///
	ImagePixelMacro();
	///
	/// Copy constructor
	///
	ImagePixelMacro(const ImagePixelMacro &imagepixelmacro);

	///
	/// Destructor
	///
	virtual ~ImagePixelMacro();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	ImagePixelMacro& operator=(const ImagePixelMacro &imagepixelmacro);

	///
	/// Comparison operator
	///
	bool operator==(const ImagePixelMacro &imagepixelmacro)const;
	///
	/// Comparison operator
	///
	bool operator!=(const ImagePixelMacro &imagepixelmacro)const;

	///
	/// Initialize the class attributes from the given AttributeManager.
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager.
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager.
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	/// 
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;
	
	///
	/// Set the samples per pixel. Value set by SetPixelData()
	///
	/// @param nSamplesPerPixel Samples per Pixel : Tag (0028, 0002), VR = US [required]
	/// @see SetPixelData
	virtual bool SetSamplesPerPixel(const S_UINT16 nSamplesPerPixel);

	/// @see SetSamplesPerPixel
	S_UINT16 GetSamplesPerPixel()const;
	
	///
	/// Set the Photometric Interpretation. Describes how the image data is interpreted.
	///
	/// @param nPhotometricInterpretation Photometric Interpretation : Tag (0028, 0004), VR = CS [required]
	///
	virtual bool SetPhotometricInterpretation(const PHOTOMETRIC_INTERPRETATION nPhotometricInterpretation);

	/// @see SetPhotometricInterpretation
	PHOTOMETRIC_INTERPRETATION GetPhotometricInterpretation()const;

	/// @see SetPhotometricInterpretation
	DcsString GetPhotometricInterpretationAsString()const;

	////////////////////////////////////////////////////////////////////////
	/// Rows : Tag (0028, 0010), VR = US [required]
	/// Set with call to SetPixelData()
	///
	/// Get number of rows (0028, 0010) in pixel data
	///
	S_UINT16 GetRows()const;
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	/// Columns : Tag (0028, 0011), VR = US [required]
	/// Set with call to SetPixelData()
	///
	/// Get number of columns (0028, 0011) in pixel data
	///
	S_UINT16 GetColumns()const;
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	/// Bits Allocated : Tag (0028, 0100), VR = US [required] (Must be an even number)
	/// Set with call to SetPixelData()
	///
	/// Get bits allocated (0028, 0100) per value for pixel data
	///
	S_UINT16 GetBitsAllocated()const;
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	/// Bits Stored : Tag (0028, 0101), VR = US [required] (Must be an even number)
	/// Set with call to SetPixelData()
	///
	/// Get bits stored (0028, 0101) per value for pixel data
	///
	S_UINT16 GetBitsStored()const;
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	/// High Bit (Most Significant Bit) : Tag (0028, 0102), VR = US [required] (ex. For 8bit data, bit 7 is the most significant bit)
	/// Set with call to SetPixelData()
	///
	/// Get the high bit (0028, 0102) per value for pixel data
	///
	S_UINT16 GetHighBit()const;
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	/// Pixel Representation : Tag (0028, 0103), VR = US [required]
	/// Set with call to SetPixelData()
	/// Values: "0x0000" = unsigned integer, "0x0001" = 2's complement
	///
	/// Get pixel representation (0028, 0103) for the pixel data
	///
	PIXEL_REPRESENTATION GetPixelRepresentation()const;

	///
	/// Get pixel representation (0028, 0103) for the pixel data
	///
	/// @return 0 = unsigned, 1 = signed
	///
	S_UINT16 GetPixelRepresentationAsUnsignedInt()const;
	////////////////////////////////////////////////////////////////////////

	///
	/// Set all information related to integer pixel data.  Cannot be used if SetPixelData() has been called.
	///
	/// @param nRows Rows in image
	/// @param nColumns Columns in image
	/// @param nBitsAllocated Bits allocated per sample. Must be an even number in the range 8-64
	/// @param nBitsStored Bits stored. Must be an even number less than bits allocated and restricted to the range 8-64
	/// @param nHighBit High bit
	/// @param nPixelRepresentation Pixel representation. Signed or unsigned data
	///
	virtual bool SetImageInfo(	const S_UINT16 nRows, const S_UINT16 nColumns, 
								const S_UINT16 nBitsAllocated, const S_UINT16 nBitsStored, const S_UINT16 nHighBit,
								const PIXEL_REPRESENTATION nPixelRepresentation);

	/// Set all information related to float pixel data.  Cannot be used if SetPixelData() has been called.
	///
	/// @param nRows Rows in image
	/// @param nColumns Columns in image
	virtual bool SetImageInfo32Float(const S_UINT16 nRows, const S_UINT16 nColumns);

	////////////////////////////////////////////////////////////////////////
	// Pixel Data : Tag (7FE0, 0010)
	// These functions internally set 'Bits Allocated', 'Bits Stored', 'High Bit', 'Pixel Representation'

	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 8, bits stored to 8, high bit to 7, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OB [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_UINT8> &arrayData);
	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 8, bits stored to 8, high bit to 7, samples per pixel to 1, and pixel representation to signed.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OB [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_INT8> &arrayData);
	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 8, bits stored to 8, high bit to 7, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OB [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array3DLarge<S_UINT8> &arrayData);
	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 8, bits stored to 8, high bit to 7, samples per pixel to 1, and pixel representation to signed.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OB [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array3DLarge<S_INT8> &arrayData);
	
	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 16, bits stored to 16, high bit to 15, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_UINT16> &arrayData);
	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 16, bits stored to 16, high bit to 15, samples per pixel to 1, and pixel representation to signed.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_INT16> &arrayData);
	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 16, bits stored to 16, high bit to 15, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array3DLarge<S_UINT16> &arrayData);
	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 16, bits stored to 16, high bit to 15, samples per pixel to 1, and pixel representation to signed.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array3DLarge<S_INT16> &arrayData);

	/// Set pixel data (7FE0, 0011).  Sets bits allocated to 32, bits stored to 32, high bit to 31, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_UINT32> &arrayData);
	/// Set pixel data (7FE0, 0011).  Sets bits allocated to 32, bits stored to 32, high bit to 31, samples per pixel to 1, and pixel representation to signed.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_INT32> &arrayData);
	/// Set pixel data (7FE0, 0011).  Sets bits allocated to 32, bits stored to 32, high bit to 31, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data [required if "Pixel Data Provider URL" (0028, 7FE0) not used and SOP Class UID requires 32bit data]
	virtual bool SetPixelData(const Array3DLarge<S_UINT32> &arrayData);
	/// Set pixel data (7FE0, 0011).  Sets bits allocated to 32, bits stored to 32, high bit to 31, samples per pixel to 1, and pixel representation to signed.
	/// @param arrayData Pixel data [required if "Pixel Data Provider URL" (0028, 7FE0) not used and SOP Class UID requires 32bit data]
	virtual bool SetPixelData(const Array3DLarge<S_INT32> &arrayData);

	/// Set pixel data (7FE0, 0012).  Sets bits allocated to 64, bits stored to 64, high bit to 63, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_UINT64> &arrayData);
	/// Set pixel data (7FE0, 0012).  Sets bits allocated to 64, bits stored to 64, high bit to 63, samples per pixel to 1, and pixel representation to signed.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<S_INT64> &arrayData);
	/// Set pixel data (7FE0, 0012).  Sets bits allocated to 64, bits stored to 64, high bit to 63, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data [required if "Pixel Data Provider URL" (0028, 7FE0) not used and SOP Class UID requires 64bit data]
	virtual bool SetPixelData(const Array3DLarge<S_UINT64> &arrayData);
	/// Set pixel data (7FE0, 0012).  Sets bits allocated to 64, bits stored to 64, high bit to 63, samples per pixel to 1, and pixel representation to signed.
	/// @param arrayData Pixel data [required if "Pixel Data Provider URL" (0028, 7FE0) not used and SOP Class UID requires 64bit data]
	virtual bool SetPixelData(const Array3DLarge<S_INT64> &arrayData);

	/// Set pixel data (7FE0, 0013).  Sets bits allocated to 32, bits stored to 32, high bit to 31, samples per pixel to 1, and pixel representation to unsigned.
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	virtual bool SetPixelData(const Array2D<float> &arrayData);
	/// Set pixel data (7FE0, 0013).  Sets bits allocated to 32, bits stored to 32, high bit to 31, samples per pixel to 1, and pixel representation to signed.
	/// @param arrayData Pixel data [required if "Pixel Data Provider URL" (0028, 7FE0) not used and SOP Class UID requires 32bit float data]
	virtual bool SetPixelData(const Array3DLarge<float> &arrayData);

	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_UINT8> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_INT8> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array3DLarge<S_UINT8> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array3DLarge<S_INT8> &arrayData)const;
	
	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_UINT16> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_INT16> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array3DLarge<S_UINT16> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array3DLarge<S_INT16> &arrayData)const;

	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_UINT32> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_INT32> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array3DLarge<S_UINT32> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array3DLarge<S_INT32> &arrayData)const;

	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_UINT64> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_INT64> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array3DLarge<S_UINT64> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array3DLarge<S_INT64> &arrayData)const;

	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<float> &arrayData)const;
	/// @see SetPixelData
	virtual bool GetPixelData(Array3DLarge<float> &arrayData)const;

	/// Move data from this object to volDst. This resets all pixel data related values to default.
	/// Pixel data related values: rows, columns, bits stored/allocated, high bit, number of samples, pixel data
	/// For 2D data, volume has a depth of 1
	/// If this object does not own the data, then volDst is set to also not own the data
	bool MoveDataFrom(Volume &volDst);

	/// Move data from volSrc to this object.
	/// For 2D data, volume has a depth of 1.
	/// If volSrc does not own the data, then this object is set to also not own the data
	///
	/// @param volSrc pixel data moved from this parameter into the object
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Only used if number of samples is not 1. 
	///							nPlanarConfig = enumColorByPixel : Samples stored as Sample(0,1,2,3) = volSrc[SLICE][ROW][COL + 0,1,2,3]
	///							nPlanarConfig = enumColorByPlane : Samples stored as Sample(0,1,2,3) = volSrc[SLICE + 0,1,2,3][ROW][COL]
	bool MoveDataInto(Volume &volSrc, const S_UINT16 nNumSamples = 1, const PLANAR_CONFIGURATION nPlanarConfig = enumColorByPixel);

	/// Reference pixel data owned by volSrc. This object will not take ownership of the data.
	/// For 2D data, volume has a depth of 1.
	///
	/// @param volSrc Pixel data to reference
	/// @param nNumSamples Number of samples
	/// @param nPlanarConfig	Only used if number of samples is not 1. 
	///							nPlanarConfig = enumColorByPixel : Samples stored as Sample(0,1,2,3) = volSrc[SLICE][ROW][COL + 0,1,2,3]
	///							nPlanarConfig = enumColorByPlane : Samples stored as Sample(0,1,2,3) = volSrc[SLICE + 0,1,2,3][ROW][COL]
	bool SetAsReference(Volume &volSrc, const S_UINT16 nNumSamples = 1, const PLANAR_CONFIGURATION nPlanarConfig = enumColorByPixel);
	/// Set volDst as a reference to this object's pixel data. This object can either reference other pixel data or own the pixel data.
	///
	/// @param volDst Volume that will reference this object's pixel data
	bool GetReference(Volume &volDst);
	/// Returns true if this object owns the pixel data; otherwise, returns false.
	bool OwnsData()const;

	/// Returns true if data is unsigned 8-bit
	bool IsPixelDataUnsigned8Bit()const;
	/// Returns true if data is signed 8-bit
	bool IsPixelDataSigned8Bit()const;
	/// Returns true if data is unsigned 16-bit
	bool IsPixelDataUnsigned16Bit()const;
	/// Returns true if data is signed 16-bit
	bool IsPixelDataSigned16Bit()const;
	/// Returns true if data is unsigned 32-bit
	bool IsPixelDataUnsigned32Bit()const;
	/// Returns true if data is signed 32-bit
	bool IsPixelDataSigned32Bit()const;
	/// Returns true if data is unsigned 64-bit
	bool IsPixelDataUnsigned64Bit()const;
	/// Returns true if data is signed 64-bit
	bool IsPixelDataSigned64Bit()const;
	/// Returns true if data is float
	bool IsPixelDataFloat()const;

	///
	/// Set the planar configuration (0028, 0006)
	/// Passing in enumColorByPixel indicated each frame is an image saved as 'R0, G0, B0, R1, G1,...'
	/// Passing in enumColorByPlane indicates each frame is an image saved as 'R0, R1, R2,..., G0, G1, G2,..., B0, B1, B2...'
	///
	/// @param nPlanarConfiguration Planar configuration : Tag (0028, 0006), VR = US [required if 'Samples per Pixel' is greater than 1]
	///
	virtual bool SetPlanarConfiguration(const PLANAR_CONFIGURATION nPlanarConfiguration);

	/// @see SetPlanarConfiguration
	PLANAR_CONFIGURATION GetPlanarConfiguration()const;
	///
	/// Return values: 0 = Color by pixel, 1 = Color by plane
	///
	S_UINT16 GetPlanarConfigurationAsUnsignedInt()const;

	///
	/// Set the pixel aspect ratio : Tag (0028, 0034) VR = IS (Integer String) [required if ratio is not 1:1]
	///
	/// @param nVertical Vertical component to ratio
	/// @param nHorizontal Horizontal component to ratio
	///
	bool SetPixelAspectRatio(const S_INT32 nVertical, const S_INT32 nHorizontal);

	/// @see SetPixelAspectRatio
	bool GetPixelAspectRatio(S_INT32 &nVertical, S_INT32 &nHorizontal)const;

	/// Set the smallest image pixel value : Tag (0028, 0106), VR = US [optional]
	bool SetSmallestImagePixelValue(const S_UINT16 nSmallestImagePixelValue);
	/// Set the smallest image pixel value : Tag (0028, 0106), VR = SS [optional]
	bool SetSmallestImagePixelValue(const S_INT16 nSmallestImagePixelValue);
	/// Set the smallest image pixel value : Tag (0028, 1106), VR = UL [optional]
	bool SetSmallestImagePixelValue(const S_UINT32 nSmallestImagePixelValue);
	/// Set the smallest image pixel value : Tag (0028, 1106), VR = SL [optional]
	bool SetSmallestImagePixelValue(const S_INT32 nSmallestImagePixelValue);
	/// Set the smallest image pixel value : Tag (0028, 2106), VR = UD [optional]
	bool SetSmallestImagePixelValue(const S_UINT64 nSmallestImagePixelValue);
	/// Set the smallest image pixel value : Tag (0028, 2106), VR = SD [optional]
	bool SetSmallestImagePixelValue(const S_INT64 nSmallestImagePixelValue);
	/// Set the smallest image pixel value : Tag (0028, 3106), VR = FL [optional]
	bool SetSmallestImagePixelValue(const float nSmallestImagePixelValue);

	/// @see SetSmallestImagePixelValue
	bool GetSmallestImagePixelValue(S_UINT16 &nSmallestImagePixelValue)const;
	/// @see SetSmallestImagePixelValue
	bool GetSmallestImagePixelValue(S_INT16 &nSmallestImagePixelValue)const;
	/// @see SetSmallestImagePixelValue
	bool GetSmallestImagePixelValue(S_UINT32 &nSmallestImagePixelValue)const;
	/// @see SetSmallestImagePixelValue
	bool GetSmallestImagePixelValue(S_INT32 &nSmallestImagePixelValue)const;
	/// @see SetSmallestImagePixelValue
	bool GetSmallestImagePixelValue(S_UINT64 &nSmallestImagePixelValue)const;
	/// @see SetSmallestImagePixelValue
	bool GetSmallestImagePixelValue(S_INT64 &nSmallestImagePixelValue)const;
	/// @see SetSmallestImagePixelValue
	bool GetSmallestImagePixelValue(float &nSmallestImagePixelValue)const;

	/// Set the largest image pixel value : Tag (0028, 0107), VR = US [optional]
	bool SetLargestImagePixelValue(const S_UINT16 nLargestImagePixelValue);
	/// Set the largest image pixel value : Tag (0028, 0107), VR = SS [optional]
	bool SetLargestImagePixelValue(const S_INT16 nLargestImagePixelValue);
	/// Set the largest image pixel value : Tag (0028, 1107), VR = UL [optional]
	bool SetLargestImagePixelValue(const S_UINT32 nLargestImagePixelValue);
	/// Set the largest image pixel value : Tag (0028, 1107), VR = SL [optional]
	bool SetLargestImagePixelValue(const S_INT32 nLargestImagePixelValue);
	/// Set the largest image pixel value : Tag (0028, 2107), VR = UD [optional]
	bool SetLargestImagePixelValue(const S_UINT64 nLargestImagePixelValue);
	/// Set the largest image pixel value : Tag (0028, 2107), VR = SD [optional]
	bool SetLargestImagePixelValue(const S_INT64 nLargestImagePixelValue);
	/// Set the largest image pixel value : Tag (0028, 3107), VR = FL [optional]
	bool SetLargestImagePixelValue(const float nLargestImagePixelValue);

	/// @see SetLargestImagePixelValue
	bool GetLargestImagePixelValue(S_UINT16 &nLargestImagePixelValue)const;
	/// @see SetLargestImagePixelValue
	bool GetLargestImagePixelValue(S_INT16 &nLargestImagePixelValue)const;
	/// @see SetLargestImagePixelValue
	bool GetLargestImagePixelValue(S_UINT32 &nLargestImagePixelValue)const;
	/// @see SetLargestImagePixelValue
	bool GetLargestImagePixelValue(S_INT32 &nLargestImagePixelValue)const;
	/// @see SetLargestImagePixelValue
	bool GetLargestImagePixelValue(S_UINT64 &nLargestImagePixelValue)const;
	/// @see SetLargestImagePixelValue
	bool GetLargestImagePixelValue(S_INT64 &nLargestImagePixelValue)const;
	/// @see SetLargestImagePixelValue
	bool GetLargestImagePixelValue(float &nLargestImagePixelValue)const;

	///
	/// Set red palette color lookup table [Required if Photometric interpretation (0028, 0004) is "PALETTE COLOR" or Pixel presentation (0008, 9205) is "COLOR" or "MIXED"]
	///
	bool SetRedPaletteColorLookupTable(const PaletteColorLookupTableRed &palettecolorlookuptablered);
	///
	/// Set green palette color lookup table [Required if Photometric interpretation (0028, 0004) is "PALETTE COLOR" or Pixel presentation (0008, 9205) is "COLOR" or "MIXED"]
	///
	bool SetGreenPaletteColorLookupTable(const PaletteColorLookupTableGreen &palettecolorlookuptablegreen);
	///
	/// Set blue palette color lookup table [Required if Photometric interpretation (0028, 0004) is "PALETTE COLOR" or Pixel presentation (0008, 9205) is "COLOR" or "MIXED"]
	///
	bool SetBluePaletteColorLookupTable(const PaletteColorLookupTableBlue &palettecolorlookuptableblue);

	/// @see SetRedPaletteColorLookupTable
	bool GetRedPaletteColorLookupTable(PaletteColorLookupTableRed &palettecolorlookuptablered)const;
	/// @see SetGreenPaletteColorLookupTable
	bool GetGreenPaletteColorLookupTable(PaletteColorLookupTableGreen &palettecolorlookuptablegreen)const;
	/// @see SetBluePaletteColorLookupTable
	bool GetBluePaletteColorLookupTable(PaletteColorLookupTableBlue &palettecolorlookuptableblue)const;

	///
	/// Get the red palette color lookup table. Returns S_NULL if no table is available. This can only be used with 8-16bit data.
	///
	PaletteColorLookupTableRed* GetRedPaletteColorLookupTable();
	
	///
	/// Get the blue palette color lookup table. Returns S_NULL if no table is available. This can only be used with 8-16bit data.
	///
	PaletteColorLookupTableGreen* GetGreenPaletteColorLookupTable();
	
	///
	/// Get the green palette color lookup table. Returns S_NULL if no table is available. This can only be used with 8-16bit data.
	///
	PaletteColorLookupTableBlue* GetBluePaletteColorLookupTable();

	///
	/// Get the red palette color lookup table. Returns S_NULL if no table is available
	///
	const PaletteColorLookupTableRed* GetRedPaletteColorLookupTable()const;
	
	///
	/// Get the blue palette color lookup table. Returns S_NULL if no table is available
	///
	const PaletteColorLookupTableGreen* GetGreenPaletteColorLookupTable()const;
	
	///
	/// Get the green palette color lookup table. Returns S_NULL if no table is available
	///
	const PaletteColorLookupTableBlue* GetBluePaletteColorLookupTable()const;

	///
	/// Set ICC Profile : Tag (0028, 2000), VR = OB [optional]
	///
	bool SetICCProfile(const MemoryBuffer &membuffer);
	/// @see SetICCProfile
	bool GetICCProfile(MemoryBuffer &membuffer)const;
	
	/// Delete pixel data (8-64bit, float)
	void DeletePixelData();

	/// Delete the smallest image pixel value (8-64bit, float)
	void DeleteSmallestImagePixelValue();

	/// Delete the largest image pixel value (8-64bit, float)
	void DeleteLargestImagePixelValue();

	/// Delete red, green, and blue palette color lookup tables
	void DeletePaletteColorLookupTables();

	/// Delete the ICC Profile : Tag (0028, 2000), VR = OB [optional]
	void DeleteICCProfile();

	/// Convert Photometric Interpretation to DcsString
	static DcsString PhotometricInterpretationToString(const PHOTOMETRIC_INTERPRETATION pi);

private:
	class ImplImagePixelMacro;
	ImplImagePixelMacro	*m_pImplImagePixelMacro; ///< Internal implementation
};

}//namespace SDICOS

#endif