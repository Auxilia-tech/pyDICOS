//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2022 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_AIT_IMAGE_TYPE_H_
#define _STRATOVAN_DICOS_AIT_IMAGE_TYPE_H_

namespace SDICOS
{
namespace AITImageType
{

/// AIT_IMAGE_CHARACTERISTICS
/// AIT Image Characteristic, value 2 for Image Type (0008, 0008), specialized for AIT 2D and AIT 3D
typedef enum
{
	enumUnknownAITImageCharacteristic, ///< Unknown AIT Image Characteristic

	enumNoImageCharacteristic,		///< Sets Image Type value 2 to NULL
	enumContentAmplitude,			///< "CNT_AMP"
	enumContentComplexAmplitude,	///< "CNT_CPX_AMP"
}AIT_IMAGE_CHARACTERISTICS;

/// @return AIT_IMAGE_CHARACTERISTICS as a string
const char* GetAsString(const SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS nVal);

/// @return String as a AIT_IMAGE_CHARACTERISTICS
SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS GetAsAITImageCharacteristicEnum(const char* pstr);

/// @return Verify AIT_IMAGE_CHARACTERISTICS is valid. Only enumUnknownAITImageCharacteristic is invalid.
bool IsValid(const SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS nVal);

/// @return Verify string is a valid AIT_IMAGE_CHARACTERISTICS
bool IsAITImageCharacteristicsValid(const char* pstr);

}
}

#endif
