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
#ifndef _STRATOVAN_DICOS_PALETTE_COLOR_LOOKUP_TABLE_H_
#define _STRATOVAN_DICOS_PALETTE_COLOR_LOOKUP_TABLE_H_

#include "SDICOS/Types.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class PaletteColorLookupTable
/// \brief Implements color palette tags in Image Pixel Macro and Supplemental Palette Color Lookup Table Module
/// SPECREF V03 Section 14.2.1, Table 86
/// SPECREF V03 Section 14.2.2, Table 87
///
////////////////////////////////////////
/// Referenced tags not in this object
/// "Pixel Presentation" tag (0008, 9205) - In each scanner's "Image Description" macro
/// "Photometric Representation" tag (0028, 0004) - In "Image Pixel Macro"
/// "Pixel Representation" tag (0028, 0103) - In "Image Pixel Macro"
////////////////////////////////////////
class PaletteColorLookupTable
{
public:

	///
	/// Enumeration of palette color
	///
	typedef enum
	{
		enumUnknownColor,	///< Does not match defined terms

		enumRed,	///< Descriptor Tag (0028, 1101), Data Tag (0028, 1201)
		enumGreen,	///< Descriptor Tag (0028, 1102), Data Tag (0028, 1202)
		enumBlue,	///< Descriptor Tag (0028, 1103), Data Tag (0028, 1203)

	}COLOR;

	///
	/// Enumeration of bits per entry
	///
	typedef enum
	{
		enumUnknownBitsPerEntry,	///< Does not match defined terms

		enum8Bit,	///< 8 bits
		enum16Bit,	///< 16 bits

	}BITS_PER_ENTRY;

	///
	/// Initialize as a specific color
	///
	PaletteColorLookupTable(const COLOR nColor);

	///
	/// Initialize with another PaletteColorLookupTable object
	///
	PaletteColorLookupTable(const PaletteColorLookupTable &palettecolorlookuptable);

	///
	/// Destructor
	///
	virtual ~PaletteColorLookupTable();

	///
	/// Delete allcated memory
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	PaletteColorLookupTable& operator=(const PaletteColorLookupTable &palettecolorlookuptable);

	///
	/// Comparison operator
	///
	bool operator==(const PaletteColorLookupTable &palettecolorlookuptable)const;
	///
	/// Comparison operator
	///
	bool operator!=(const PaletteColorLookupTable &palettecolorlookuptable)const;


	///
	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	/// 
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// The descriptor and data attributes both have conditional requirements:
	///	1. Photometric interpretation (0028, 0004) is "PALETTE COLOR"
	/// OR
	/// 2. Pixel presentation (0008, 9205) is "COLOR" or "MIXED"
	///
	/// @param attribManager Attribute manager
	/// @return true/false
	///
	static bool IsRequired(const AttributeManager &attribManager);

	/// Determine if the lookup table has any data
	/// @return true/false
	bool IsEmpty() const;
		
	///
	/// Sets the lookup table data (0028, 1201), (0028, 1202), or (0028, 1203) and the descriptor (0028, 1101), (0028, 1102), or (0028, 1103).
	/// Sets Descriptor's VR to US and bits per entry to 16.
	///
	/// @param arrayData Lookup table data (0028, 1201), (0028, 1202), or (0028, 1203) [VR = OW]
	/// @param nFirstImagePixelValueMapped First value mapped (i.e. arrayData[nFirstImagePixelValueMapped] translates to arrayData[0]).  Second value of descriptor.
	/// @return true/false
	///
	bool SetData(const Array1D<S_UINT16> &arrayData, const S_UINT16 nFirstImagePixelValueMapped);
	///
	/// Sets the lookup table data (0028, 1201), (0028, 1202), or (0028, 1203) and the descriptor (0028, 1101), (0028, 1102), or (0028, 1103).
	/// Sets Descriptor's VR to SS and bits per entry to 16.
	///
	/// @param arrayData Lookup table data (0028, 1201), (0028, 1202), or (0028, 1203) [VR = OW]
	/// @param nFirstImagePixelValueMapped First value mapped (i.e. arrayData[nFirstImagePixelValueMapped] translates to arrayData[0])  Second value of descriptor.
	/// @return true/false
	///
	bool SetData(const Array1D<S_UINT16> &arrayData, const S_INT16 nFirstImagePixelValueMapped);

	///
	/// Sets the lookup table data (0028, 1201), (0028, 1202), or (0028, 1203) and the descriptor (0028, 1101), (0028, 1102), or (0028, 1103).
	/// Sets Descriptor's VR to US and bits per entry to 8.
	///
	/// @param arrayData Lookup table data (0028, 1201), (0028, 1202), or (0028, 1203) [VR = OW]
	/// @param nFirstImagePixelValueMapped First value mapped (i.e. arrayData[nFirstImagePixelValueMapped] translates to arrayData[0])  Second value of descriptor.
	/// @return true/false
	///
	bool SetData(const Array1D<S_UINT8> &arrayData, const S_UINT16 nFirstImagePixelValueMapped);
	///
	/// Sets the lookup table data (0028, 1201), (0028, 1202), or (0028, 1203) and the descriptor (0028, 1101), (0028, 1102), or (0028, 1103).
	/// Sets Descriptor's VR to SS and bits per entry to 8.
	///
	/// @param arrayData Lookup table data (0028, 1201), (0028, 1202), or (0028, 1203) [VR = OW]
	/// @param nFirstImagePixelValueMapped First value mapped (i.e. arrayData[nFirstImagePixelValueMapped] translates to arrayData[0])  Second value of descriptor.
	/// @return true/false
	///
	bool SetData(const Array1D<S_UINT8> &arrayData, const S_INT16 nFirstImagePixelValueMapped);

	///
	/// Get the descriptor (0028, 1101), (0028, 1102), or (0028, 1103).  Returns false if not set of if descriptor is signed.
	///
	/// @param nNumberOfEntries Number Of Table Entries
	/// @param nFirstImagePixelValueMapped First Image Pixel Value Mapped.  This is the index of the first value in the lookup table.
	/// @param nBitsPerEntry Bits per Entry. Stored as unsigned short if VR = US or stored as signed short if VR = SS.  Values: enum8Bit, enum16Bit.
	/// @return true/false
	///
	bool GetDescriptor(S_UINT16 &nNumberOfEntries, S_UINT16 &nFirstImagePixelValueMapped, S_UINT16 &nBitsPerEntry)const;
	///
	/// Get the descriptor (0028, 1101), (0028, 1102), or (0028, 1103).  Returns false if not set of if descriptor is unsigned.
	///
	/// @param nNumberOfEntries Number Of Table Entries
	/// @param nFirstImagePixelValueMapped First Image Pixel Value Mapped.  This is the index of the first value in the lookup table.
	/// @param nBitsPerEntry Bits per Entry. Stored as unsigned short if VR = US or stored as signed short if VR = SS.  Values: enum8Bit, enum16Bit.
	/// @return true/false
	///
	bool GetDescriptor(S_INT16 &nNumberOfEntries, S_INT16 &nFirstImagePixelValueMapped, S_INT16 &nBitsPerEntry)const;

	///
	/// Returns false if data is not 8 bits per entry.  Indices into the data are clamped to the descriptor's first image pixel value mapped, nFirstImagePixelValueMapped, and 'nFirstImagePixelValueMapped + arrayData.GetSize()'.
	///
	bool GetData(Array1D<S_UINT8> &arrayData)const;
	///
	/// Returns false if data is not 16 bits per entry.  Indices into the data are clamped to the descriptor's first image pixel value mapped, nFirstImagePixelValueMapped, and 'nFirstImagePixelValueMapped + arrayData.GetSize()'.
	///
	bool GetData(Array1D<S_UINT16> &arrayData)const;

	///
	/// Returns true if the descriptor uses a VR of SS
	///
	bool IsDescriptorSigned()const;

	///
	/// Returns true if the descriptor uses a VR of US
	///
	bool IsDescriptorUnsigned()const;

	///
	/// Returns true if the data is 8 bits per entry. This is the third value of the descriptor.
	///
	bool Is8BitsPerEntry()const;

	///
	/// Returns true if the data is 16 bits per entry. This is the third value of the descriptor.
	///
	bool Is16BitsPerEntry()const;

private:
	PaletteColorLookupTable();

	class ImplPaletteColorLookupTable;
	ImplPaletteColorLookupTable	*m_pImplPaletteColorLookupTable; ///< Internal implementation
};
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
class PaletteColorLookupTableRed : public PaletteColorLookupTable
{
public:
	///
	/// Calls base class with enumRed
	///
	PaletteColorLookupTableRed();
	///
	/// Copy constructor
	///
	PaletteColorLookupTableRed(const PaletteColorLookupTableRed &palettecolorlookuptablered);

	///
	/// Copy operator
	///
	PaletteColorLookupTableRed& operator=(const PaletteColorLookupTableRed &palettecolorlookuptablered);

	///
	/// Comparison operator
	///
	bool operator==(const PaletteColorLookupTableRed &palettecolorlookuptablered)const;
	///
	/// Comparison operator
	///
	bool operator!=(const PaletteColorLookupTableRed &palettecolorlookuptablered)const;
};
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
class PaletteColorLookupTableGreen : public PaletteColorLookupTable
{
public:
	///
	/// Calls base class with enumGreen
	///
	PaletteColorLookupTableGreen();
	///
	/// Copy constructor
	///
	PaletteColorLookupTableGreen(const PaletteColorLookupTableGreen &palettecolorlookuptablegreen);

	///
	/// Copy operator
	///
	PaletteColorLookupTableGreen& operator=(const PaletteColorLookupTableGreen &palettecolorlookuptablegreen);

	///
	/// Comparison operator
	///
	bool operator==(const PaletteColorLookupTableGreen &palettecolorlookuptablegreen)const;
	///
	/// Comparison operator
	///
	bool operator!=(const PaletteColorLookupTableGreen &palettecolorlookuptablegreen)const;
};
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
class PaletteColorLookupTableBlue : public PaletteColorLookupTable
{
public:
	///
	/// Calls base class with enumBlue
	///
	PaletteColorLookupTableBlue();
	///
	/// Copy constructor
	///
	PaletteColorLookupTableBlue(const PaletteColorLookupTableBlue &palettecolorlookuptableblue);

	///
	/// Copy operator
	///
	PaletteColorLookupTableBlue& operator=(const PaletteColorLookupTableBlue &palettecolorlookuptableblue);

	///
	/// Comparison operator
	///
	bool operator==(const PaletteColorLookupTableBlue &palettecolorlookuptableblue)const;
	///
	/// Comparison operator
	///
	bool operator!=(const PaletteColorLookupTableBlue &palettecolorlookuptableblue)const;
};
///////////////////////////////////////////////////////////////

}//namespace SDICOS

#endif
