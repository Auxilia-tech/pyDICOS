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
#ifndef _STRATOVAN_DICOS_IMAGETYPE_H_
#define _STRATOVAN_DICOS_IMAGETYPE_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class ImageType
/// \brief Implements General Image Module's Image Type. Provides overridable functions for V02A and above.
/// SPECREF V03 Section 14.3.1, Table 95
///
class ImageType
{
public:
	/// Constructor
	ImageType();
	/// Copy Constructor
	ImageType(const ImageType &it);
	/// Destructor
	virtual ~ImageType();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	ImageType& operator=(const ImageType &it);
	/// Comparison operator
	bool operator==(const ImageType &it)const;
	/// Comparison operator
	bool operator!=(const ImageType &it)const;

	/// Enumeration of pixel data characteristics
	typedef enum
	{
		enumUnknownPixelDataCharacteristics, ///< Unknown enumeration

		enumOriginal,	///< "ORIGINAL"
		enumDerived,	///< "DERIVED"

	}PIXEL_DATA_CHARACTERISTICS;

	typedef enum
	{
		enumUnknownImageCharacteristics, ///< Unknown enumeration

		enumPrimary,	///< "PRIMARY"
		enumSecondary,	///< "SECONDARY"

	}IMAGE_CHARACTERISTICS;

	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;


	///
	/// Set Image Type : Tag (0008, 0008), VR = CS [optional]
	///
	/// @param nPixelDataCharacteristics Pixel Data Characteristics (Value 1 in attribute)
	///
	virtual bool SetImageType(const PIXEL_DATA_CHARACTERISTICS nPixelDataCharacteristics);

	///
	/// Set Image Type : Tag (0008, 0008), VR = CS [optional]
	///
	/// @param nPixelDataCharacteristics Pixel Data Characteristics (Value 1 in attribute)
	/// @param nImageCharacteristics Image Characteristics (Value 2 in attribute)
	///
	virtual bool SetImageType(const PIXEL_DATA_CHARACTERISTICS nPixelDataCharacteristics, const IMAGE_CHARACTERISTICS nImageCharacteristics);

	/// @see SetImageType
	virtual PIXEL_DATA_CHARACTERISTICS GetImageType()const;
	/// Returns string of PIXEL_DATA_CHARACTERISTICS value
	virtual DcsString GetImageTypeAsString()const;
	/// @see SetImageType
	virtual bool GetImageType(PIXEL_DATA_CHARACTERISTICS &nPixelDataCharacteristics, IMAGE_CHARACTERISTICS &nImageCharacteristics)const;
	/// @see SetImageType
	virtual bool GetImageType(DcsString &strPixelDataCharacteristics, DcsString &strImageCharacteristics)const;
	/// Delete attribute
	virtual void DeleteImageType();
protected:

	void UseV02ImageType();
	void UseCustomImageType();

	class ImplImageType;
	ImplImageType	*m_pImplImageType; ///< Internal implementation
};

}//namespace SDICOS

#endif
