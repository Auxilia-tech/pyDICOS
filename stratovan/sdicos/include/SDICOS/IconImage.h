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
#ifndef _STRATOVAN_DICOS_ICON_IMAGE_H_
#define _STRATOVAN_DICOS_ICON_IMAGE_H_

#include "SDICOS/ImagePixelMacro.h"

namespace SDICOS
{

///
/// \class IconImage
/// \brief Implements icon image, a single item sequence (0088, 0200) [optional]
/// SPECREF V03 Section 14.3.1.1.5
///
/// Samples per pixel set to 1
/// Photometric Interpretation restricted to Monochrome1, Monochrome2, and Palette Color
/// Bits allocated and bits stored restricted to 8
/// Pixel representation restricted to unsigned
/// Pixel aspect ratio locked to default 1:1
class IconImage : protected ImagePixelMacro
{
public:

	///
	/// Initialize with default values
	///
	IconImage();
	///
	/// Copy constructor
	///
	IconImage(const IconImage &iconimage);

	///
	/// Destructor
	///
	virtual ~IconImage();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	IconImage& operator=(const IconImage &iconimage);

	///
	/// Comparison operator
	///
	bool operator==(const IconImage &iconimage)const;
	///
	/// Comparison operator
	///
	bool operator!=(const IconImage &iconimage)const;

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
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;
	
	///
	/// Get the samples per pixel : Tag (0028, 0002), VR = US [required]
	///
	S_UINT16 GetSamplesPerPixel()const;
	
	///
	/// Set the Photometric Interpretation.  Values restricted to Monochrome1, Monochrome2, and Palette Color.
	///
	/// @param nPhotometricInterpretation Photometric Interpretation : Tag (0028, 0004), VR = CS [required]
	///
	virtual bool SetPhotometricInterpretation(const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPhotometricInterpretation);

	/// @see SetPhotometricInterpretation
	ImagePixelMacro::PHOTOMETRIC_INTERPRETATION GetPhotometricInterpretation()const;

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

	///
	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 8, bits stored to 8, high bit to 7, samples per pixel to 1, and pixel representation to unsigned.
	///
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OB [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	///
	virtual bool SetPixelData(const Array2D<S_UINT8> &arrayData);
	///
	/// Set pixel data (7FE0, 0010).  Sets bits allocated to 8, bits stored to 8, high bit to 7, samples per pixel to 1, and pixel representation to signed.
	///
	/// @param arrayData Pixel data : Tag (7FE0, 0010), VR = OB [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	///

	/// @see SetPixelData
	virtual bool GetPixelData(Array2D<S_UINT8> &arrayData)const;

	///
	/// Get the pixel aspect ratio : Tag (0028, 0034) VR = IS (Integer String) [required if ratio is not 1:1]
	///
	bool GetPixelAspectRatio(S_INT32 &nVertical, S_INT32 &nHorizontal)const;

	///
	/// Set the smallest image pixel value : Tag (0028, 0106), VR = US [optional]
	///
	bool SetSmallestImagePixelValue(const S_UINT16 nSmallestImagePixelValue);
	///
	/// Set the smallest image pixel value : Tag (0028, 0106), VR = SS [optional]
	///
	bool SetSmallestImagePixelValue(const S_INT16 nSmallestImagePixelValue);

	/// @see SetSmallestImagePixelValue
	bool GetSmallestImagePixelValue(S_UINT16 &nSmallestImagePixelValue)const;
	/// @see SetSmallestImagePixelValue
	bool GetSmallestImagePixelValue(S_INT16 &nSmallestImagePixelValue)const;

	///
	/// Set the largest image pixel value : Tag (0028, 0107), VR = US [optional]
	///
	bool SetLargestImagePixelValue(const S_UINT16 nLargestImagePixelValue);
	///
	/// Set the largest image pixel value : Tag (0028, 0107), VR = SS [optional]
	///
	bool SetLargestImagePixelValue(const S_INT16 nLargestImagePixelValue);

	/// @see SetLargestImagePixelValue
	bool GetLargestImagePixelValue(S_UINT16 &nLargestImagePixelValue)const;
	/// @see SetLargestImagePixelValue
	bool GetLargestImagePixelValue(S_INT16 &nLargestImagePixelValue)const;

	///
	/// Set red palette color lookup table 
	///
	bool SetRedPaletteColorLookupTable(const PaletteColorLookupTableRed &palettecolorlookuptablered);
	///
	/// Set green palette color lookup table 
	///
	bool SetGreenPaletteColorLookupTable(const PaletteColorLookupTableGreen &palettecolorlookuptablegreen);
	///
	/// Set blue palette color lookup table 
	///
	bool SetBluePaletteColorLookupTable(const PaletteColorLookupTableBlue &palettecolorlookuptableblue);

	/// @see SetRedPaletteColorLookupTable
	bool GetRedPaletteColorLookupTable(PaletteColorLookupTableRed &palettecolorlookuptablered)const;
	/// @see SetGreenPaletteColorLookupTable
	bool GetGreenPaletteColorLookupTable(PaletteColorLookupTableGreen &palettecolorlookuptablegreen)const;
	/// @see SetBluePaletteColorLookupTable
	bool GetBluePaletteColorLookupTable(PaletteColorLookupTableBlue &palettecolorlookuptableblue)const;

	///
	/// Get the red palette color lookup table. Returns S_NULL if no table is available
	///
	PaletteColorLookupTableRed* GetRedPaletteColorLookupTable();
	
	///
	/// Get the blue palette color lookup table. Returns S_NULL if no table is available
	///
	PaletteColorLookupTableGreen* GetGreenPaletteColorLookupTable();
	
	///
	/// Get the green palette color lookup table. Returns S_NULL if no table is available
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
	
	///
	/// Delete pixel data: Tag (7FE0, 0010), VR = OB/OW [required if "Pixel Data Provider URL" (0028, 7FE0) not used]
	///
	void DeletePixelData();

	///
	/// Delete the smallest image pixel value : Tag (0028, 0106), VR = US/SS [optional]
	///
	void DeleteSmallestImagePixelValue();

	///
	/// Delete the largest image pixel value : Tag (0028, 0107), VR = US/SS [optional]
	///
	void DeleteLargestImagePixelValue();

	///
	/// Delete red, green, and blue palette color lookup tables
	///
	void DeletePaletteColorLookupTables();

	///
	/// Delete the ICC Profile : Tag (0028, 2000), VR = OB [optional]
	///
	void DeleteICCProfile();
protected:

	///
	/// Disabled
	///
	virtual bool SetImageInfo(	const S_UINT16 nRows, const S_UINT16 nColumns, 
								const S_UINT16 nBitsAllocated, const S_UINT16 nBitsStored, const S_UINT16 nHighBit,
								const PIXEL_REPRESENTATION nPixelRepresentation);

	///
	/// Disabled
	///
	virtual bool SetPixelData(const Array2D<S_INT8> &arrayData);
	///
	/// Disabled
	///
	virtual bool SetPixelData(const Array3DLarge<S_UINT8> &arrayData);
	///
	/// Disabled
	///
	virtual bool SetPixelData(const Array3DLarge<S_INT8> &arrayData);
	///
	/// Disabled
	///
	virtual bool SetPixelData(const Array2D<S_UINT16> &arrayData);
	///
	/// Disabled
	///
	virtual bool SetPixelData(const Array2D<S_INT16> &arrayData);
	///
	/// Disabled
	///
	virtual bool SetPixelData(const Array3DLarge<S_UINT16> &arrayData);
	///
	/// Disabled
	///
	virtual bool SetPixelData(const Array3DLarge<S_INT16> &arrayData);

	///
	/// Disabled
	///
	virtual bool GetPixelData(Array2D<S_INT8> &arrayData)const;
	///
	/// Disabled
	///
	virtual bool GetPixelData(Array3DLarge<S_UINT8> &arrayData)const;
	///
	/// Disabled
	///
	virtual bool GetPixelData(Array3DLarge<S_INT8> &arrayData)const;
	///
	/// Disabled
	///
	virtual bool GetPixelData(Array2D<S_UINT16> &arrayData)const;
	///
	/// Disabled
	///
	virtual bool GetPixelData(Array2D<S_INT16> &arrayData)const;
	///
	/// Disabled
	///
	virtual bool GetPixelData(Array3DLarge<S_UINT16> &arrayData)const;
	///
	/// Disabled
	///
	virtual bool GetPixelData(Array3DLarge<S_INT16> &arrayData)const;
};

}//namespace SDICOS

#endif