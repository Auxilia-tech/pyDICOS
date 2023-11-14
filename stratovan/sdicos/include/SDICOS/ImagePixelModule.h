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
#ifndef _STRATOVAN_DICOS_IMAGE_PIXEL_MODULE_H_
#define _STRATOVAN_DICOS_IMAGE_PIXEL_MODULE_H_

#include "SDICOS/Types.h"
#include "SDICOS/String.h"
#include "SDICOS/ImagePixelMacro.h"

namespace SDICOS
{

///
/// \class ImagePixelModule
/// \brief Implements image pixel module
/// SPECREF V03 Section 14.2.1, Table 85
///
class ImagePixelModule : public ImagePixelMacro
{
public:
	///
	/// Initialize with default values
	///
	ImagePixelModule();
	///
	/// Copy constructor
	///
	ImagePixelModule(const ImagePixelModule &imagepixelmodule);
	///
	/// Destructor
	///
	virtual ~ImagePixelModule();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	ImagePixelModule& operator=(const ImagePixelModule &imagepixelmodule);

	///
	/// Comparison operator
	///
	bool operator==(const ImagePixelModule &imagepixelmodule)const;
	///
	/// Comparison operator
	///
	bool operator!=(const ImagePixelModule &imagepixelmodule)const;

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
	/// Set Pixel Data Provider URL (0028, 7FE0).  Must also provide pixel data information.  Pixel data (7FE0, 0010) must not be present to call this function.
	/// 
	/// @param strURL Pixel Data Provider URL : Tag (0028, 7FE0), VR = UT [Required if transfer syntax (0002, 0010) is "1.2.840.10008.1.2.4.94" or "1.2.840.10008.1.2.4.95"]
	/// @param nSamplesPerPixel Samples per pixel
	/// @param nRows Rows in image
	/// @param nColumns Columns in image
	/// @param nBitsAllocated Bits allocated per sample. Must be an even number in the range 8-16
	/// @param nBitsStored Bits stored. Must be an even number less than bits allocated and restricted to the range 8-16
	/// @param nHighBit High bit
	/// @param nPixelRepresentation Pixel representation. Signed or unsigned data
	///
	bool SetPixelDataProviderURL(	const DcsUnlimitedText &strURL, 
									const S_UINT16 nSamplesPerPixel,
									const S_UINT16 nRows, const S_UINT16 nColumns, 
									const S_UINT16 nBitsAllocated, const S_UINT16 nBitsStored, const S_UINT16 nHighBit,
									const PIXEL_REPRESENTATION nPixelRepresentation);

	/// @see SetPixelDataProviderURL
	DcsString GetPixelDataProviderURL()const;
	/// Returns true if data is set
	bool HasPixelDataProviderURL()const;
	/// Deletes data
	void DeletePixelDataProviderURL();

	/// Set Pixel Padding Range Limit : Tag (0028, 0121), VR = SS [optional]
	/// VR is based on Pixel Representation (0028, 0103) from 'Image Pixel Macro'
	bool SetPixelPaddingRangeLimit(const S_INT16 nRangeLimit);
	/// @see SetPixelPaddingRangeLimit
	bool GetPixelPaddingRangeLimit(S_INT16 &nRangeLimit)const;

	/// Set Pixel Padding Range Limit : Tag (0028, 0121), VR = US [optional]
	/// VR is based on Pixel Representation (0028, 0103) from 'Image Pixel Macro'
	bool SetPixelPaddingRangeLimit(const S_UINT16 nRangeLimit);
	/// @see SetPixelPaddingRangeLimit
	bool GetPixelPaddingRangeLimit(S_UINT16 &nRangeLimit)const;

	/// Set Pixel Padding Range Limit : Tag (0028, 1121), VR = SL [optional]
	/// VR is based on Pixel Representation (0028, 0103) from 'Image Pixel Macro'
	bool SetPixelPaddingRangeLimit(const S_INT32 nRangeLimit);
	/// @see SetPixelPaddingRangeLimit
	bool GetPixelPaddingRangeLimit(S_INT32 &nRangeLimit)const;

	/// Set Pixel Padding Range Limit : Tag (0028, 1121), VR = UL [optional]
	/// VR is based on Pixel Representation (0028, 0103) from 'Image Pixel Macro'
	bool SetPixelPaddingRangeLimit(const S_UINT32 nRangeLimit);
	/// @see SetPixelPaddingRangeLimit
	bool GetPixelPaddingRangeLimit(S_UINT32 &nRangeLimit)const;

	/// Set Pixel Padding Range Limit : Tag (0028, 2121), VR = SD [optional]
	/// VR is based on Pixel Representation (0028, 0103) from 'Image Pixel Macro'
	bool SetPixelPaddingRangeLimit(const S_INT64 nRangeLimit);
	/// @see SetPixelPaddingRangeLimit
	bool GetPixelPaddingRangeLimit(S_INT64 &nRangeLimit)const;

	/// Set Pixel Padding Range Limit : Tag (0028, 2121), VR = UD [optional]
	/// VR is based on Pixel Representation (0028, 0103) from 'Image Pixel Macro'
	bool SetPixelPaddingRangeLimit(const S_UINT64 nRangeLimit);
	/// @see SetPixelPaddingRangeLimit
	bool GetPixelPaddingRangeLimit(S_UINT64 &nRangeLimit)const;

	/// Set Pixel Padding Range Limit : Tag (0028, 3121), VR = FL [optional]
	/// VR is based on Pixel Representation (0028, 0103) from 'Image Pixel Macro'
	bool SetPixelPaddingRangeLimit(const float nRangeLimit);
	/// @see SetPixelPaddingRangeLimit
	bool GetPixelPaddingRangeLimit(float &nRangeLimit)const;

	/// Returns true if 16bit data is present
	bool HasPixelPaddingRangeLimit16Bit()const;
	/// Returns true if 32bit data is present
	bool HasPixelPaddingRangeLimit32Bit()const;
	/// Returns true if 64bit data is present
	bool HasPixelPaddingRangeLimit64Bit()const;
	/// Returns true if 32bit float data is present
	bool HasPixelPaddingRangeLimit32BitFloat()const;
	/// Deletes data (16-64bit and float)
	void DeletePixelPaddingRangeLimit();
	////////////////////////////////////////////////////////////////////////

protected:
	class ImplImagePixelModule;
	ImplImagePixelModule *m_pImplImagePixelModule; ///< Internal implementation
};

}//namespace SDICOS

#endif