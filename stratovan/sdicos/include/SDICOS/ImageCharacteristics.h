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
#ifndef _STRATOVAN_DICOS_IMAGE_CHARACTERISTCS_H_
#define _STRATOVAN_DICOS_IMAGE_CHARACTERISTCS_H_

namespace SDICOS
{

///
/// \class ImageCharacteristics
/// Class to hold enumerations for Image Type's and Frame Type's Image Characteristics
class ImageCharacteristics
{
public:

	typedef enum
	{
		enumUnknownOOIImageCharacteristics = 0, ///< Unknown image characteristics

		enumHighEnergy,			///< "HIGH ENERGY"
		enumLowEnergy,			///< "LOW ENERGY"
		enumZ_Effective,		///< "Z_EFFECTIVE"
		enumBasisMaterial_1,	///< "BASIS_MATERIAL_1"
		enumBasisMaterial_2,	///< "BASIS_MATERIAL_2"
		enumCompton,			///< "COMPTON"
		enumPhotoelectric,		///< "PHOTOELECTRIC"

		enumDensity,			///< "DENSITY"
		enumIntensity,			///< "INTENSITY"
		enumMu,					///< "MU"
		enumMultiEnergy,		///< "MULTI ENERGY"


	}OOI_IMAGE_CHARACTERISTICS;
};

}//namespace SDICOS

#endif
