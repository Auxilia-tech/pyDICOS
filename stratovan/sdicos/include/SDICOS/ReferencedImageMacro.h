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
#ifndef _STRATOVAN_DICOS_REFERENCED_IMAGE_MACRO_H_
#define _STRATOVAN_DICOS_REFERENCED_IMAGE_MACRO_H_

#include "SDICOS/ImageSopInstanceReference.h"
#include "SDICOS/PurposeOfReferenceCode.h"

namespace SDICOS
{

///
/// \class ReferencedImageSequence
/// \brief Implements Referenced Image Sequence, a required sequence (0008, 1140)
/// SPECREF V03 Section 14.14.6, Table 116
///
class ReferencedImageSequence
{
public:
	/// Constructor
	ReferencedImageSequence();
	/// Copy constructor
	ReferencedImageSequence(const ReferencedImageSequence &ref);
	/// Destructor
	virtual ~ReferencedImageSequence();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	ReferencedImageSequence& operator=(const ReferencedImageSequence &ref);
	/// Comparison operator
	bool operator==(const ReferencedImageSequence &ref)const;
	/// Comparison operator
	bool operator!=(const ReferencedImageSequence &ref)const;

	///
	/// \class ReferencedImageMacro
	/// \brief An item used in Referenced Image Sequence
	///
	class ReferencedImageMacro
	{
	public:
		/// Constructor
		ReferencedImageMacro();
		/// Copy constructor
		ReferencedImageMacro(const ReferencedImageMacro &ref);
		/// Destructor
		~ReferencedImageMacro();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		ReferencedImageMacro& operator=(const ReferencedImageMacro &ref);
		/// Comparison operator
		bool operator==(const ReferencedImageMacro &ref)const;
		/// Comparison operator
		bool operator!=(const ReferencedImageMacro &ref)const;

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
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		///
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

		/// Image SOP Instance Reference [required]
		bool SetImageSopInstanceReference(const ImageSopInstanceReference &imagesopinstancereference);
		/// @see SetImageSopInstanceReference
		bool GetImageSopInstanceReference(ImageSopInstanceReference &imagesopinstancereference)const;
		/// @see SetImageSopInstanceReference
		ImageSopInstanceReference& GetImageSopInstanceReference();
		/// @see SetImageSopInstanceReference
		const ImageSopInstanceReference& GetImageSopInstanceReference()const;

		/// Purpose of Reference Code (Single Item Sequence) : Tag (0040, A170), VR = SQ [required]
		bool SetPurposeOfReferenceCode(const PurposeOfReferenceReferencedImage &purposeofreferencecode);
		/// @see SetPurposeOfReferenceCode
		bool GetPurposeOfReferenceCode(CodeSequence &purposeofreferencecode)const;
		/// @see SetPurposeOfReferenceCode
		PurposeOfReferenceReferencedImage& GetPurposeOfReferenceCode();
		/// @see SetPurposeOfReferenceCode
		PurposeOfReferenceReferencedImage& GetPurposeOfReferenceCode()const;

	protected:
		class ImplReferencedImageMacro;
		ImplReferencedImageMacro	*m_pImplReferencedImageMacro; ///< Internal implementation
	};

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

	/// Referenced Image Sequence : Tag (0008, 1140), VR = SQ [required (type 2), can be empty]
	bool SetReferencedImages(const Array1D<ReferencedImageMacro> &arrayReferencedImages);
	/// @see SetReferencedImages
	bool GetReferencedImages(Array1D<ReferencedImageMacro> &arrayReferencedImages)const;
	/// @see SetReferencedImages
	Array1D<ReferencedImageMacro>& GetReferencedImages();
	/// @see SetReferencedImages
	const Array1D<ReferencedImageMacro>& GetReferencedImages()const;

protected:
	class ImplReferencedImageSequence;
	ImplReferencedImageSequence	*m_pImplReferencedImageSequence; ///< Internal implementation
};

}//namespace SDICOS

#endif