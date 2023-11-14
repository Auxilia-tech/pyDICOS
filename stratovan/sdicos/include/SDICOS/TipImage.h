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
#ifndef _STRATOVAN_DICOS_TIP_IMAGE_H_
#define _STRATOVAN_DICOS_TIP_IMAGE_H_

#include <ostream>

#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/ErrorLog.h"

namespace SDICOS
{

///
/// \class TipImage
///
/// The SDICOS::TipImage class implements the TIP Image Module
/// SPECREF V03 Section 14.2.8, Table 94
///
class TipImage
{
public:
	/// Constructor
	TipImage();

	/// Copy Constructor
	TipImage(const TipImage &tipimage);

	/// Destructor
	virtual ~TipImage();
	
	/// Assignment operator
	TipImage& operator=(const TipImage &tipimage);
	
	/// Comparison operators
	bool operator==(const TipImage &tipimage)const;
	bool operator!=(const TipImage &tipimage)const;

	/// stream insertion operator
	friend std::ostream& operator<<(std::ostream& os, const TipImage& tipImage);
	
	/// Delete allocated resources
	void FreeMemory();
	
	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false is returned if attributes were specified or if some were invalid.
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	///
	/// Enumeration for TIP Image Type : Tag (4010, 1039)
	/// SPECREF V03 Section 14.2.8, Table 94
	///
	typedef enum
	{
		enumUnknownTipImageType, ///< Unknown Tip Image Type

		enumFTI,	///< FTI - Fictitious Threat Image
		enumCTI		///< CTI - Composite Threat Image

	}TIP_IMAGE_TYPE;

	///
	/// Set TIP Image Type : Tag (4010, 1039), VR = CS [required]
	/// @param nType TIP Type
	/// @return true/false
	/// @see TIP_IMAGE_TYPE
	///
	bool SetTipImageType(const TIP_IMAGE_TYPE nType);

	/// Get the TIP Image Type
	/// @return TIP_IMAGE_TYPE
	TIP_IMAGE_TYPE GetTipImageType()const;

	/// Get TIP Image Type as a string
	/// @return DcsString
	DcsString GetTipImageTypeAsString()const;

	///
	///	Set TIP Library Name : Tag (4010, 2041), VR = ST [optional]
	/// @param strName TIP Library Name
	/// @return true/false
	///
	bool SetTipLibraryName(const DcsShortText &strName);

	/// @see SetTipLibrarName
	DcsShortText GetTipLibraryName()const;

	/// @see SetTipLibraryName
	bool HasTipLibraryName()const;

	/// @see SetTipLibraryName
	void DeleteTipLibraryName();

	///
	/// Set TIP Library Date : Tag (4010, 2043), VR = DT [optional]
	/// @param dtLibraryDate TIP Library Date
	/// @return true/false
	///
	bool SetTipLibraryDate(const DcsDateTime &dtLibraryDate);

	/// @see SetTipLibraryDate
	DcsDateTime GetTipLibraryDate()const;

	/// @see SetTipLibraryDate
	bool HasTipLibraryDate()const;

	/// @see SetTipLibraryDate
	void DeleteTipLibraryDate();

	///
	/// Set TIP Image Identifier : Tag (4010, 2045), VR = ST [optional]
	/// @param strImageIdentifier TIP Image Identifier
	/// @return true/false
	///
	bool SetTipImageIdentifier(const DcsShortText &strImageIdentifier);

	/// @see SetTipImageIdentifier
	DcsShortText GetTipImageIdentifier()const;

	/// @see SetTipImageIdentifier
	bool HasTipImageIdentifier()const;

	/// @see SetTipImageIdentifier
	void DeleteTipImageIdentifier();

private:
	class ImplTipImage;
	ImplTipImage	*m_pImplTipImage; ///< Internal implementation
	
	ImplTipImage* GetImpl();
	const ImplTipImage* GetImpl() const;
};

}//namespace SDICOS

#endif
