//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2018 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_IMAGE_DATA_BASE_H_
#define _STRATOVAN_DICOS_IMAGE_DATA_BASE_H_

namespace SDICOS
{

class ImageDataBase
{
public:
	/// Data type enumerations
	typedef enum
	{
		enumUndefinedDataType = -1,	///< Unknown data type

		enumSigned8Bit,		///< signed 8-bit
		enumUnsigned8Bit,	///< unsigned 8-bit

		enumSigned16Bit,	///< signed 16-bit
		enumUnsigned16Bit,	///< unsigned 16-bit

		enumSigned32Bit,	///< signed 32-bit
		enumUnsigned32Bit,	///< unsigned 32-bit

		enumSigned64Bit,	///< signed 64-bit
		enumUnsigned64Bit,	///< unsigned 64-bit

		enumFloat,			///< floating point precision

	}IMAGE_DATA_TYPE;

	/// Return number of bytes associated with the data type
	/// @param idt Image Data Type
	/// @return Number of bytes
	static S_UINT32 SizeOf(const IMAGE_DATA_TYPE idt);
};


}//namespace SDICOS

#endif //_STRATOVAN_DICOS_IMAGE_DATA_BASE_H_
