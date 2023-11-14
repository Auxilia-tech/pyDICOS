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
#ifndef _STRATOVAN_DICOS_DERIVATION_IMAGE_MACRO_H_
#define _STRATOVAN_DICOS_DERIVATION_IMAGE_MACRO_H_

#include "SDICOS/ReferencedImageMacro.h"

namespace SDICOS
{

///
/// \class DerivationImageSequence
/// \brief Implements Derivation Image Sequence, a required sequence (0008, 9124)
/// SPECREF V03 Section 14.14.7, Table 117
///
class DerivationImageSequence
{
public:
	/// Constructor
	DerivationImageSequence();
	/// Copy constructor
	DerivationImageSequence(const DerivationImageSequence &der);
	/// Destructor
	virtual ~DerivationImageSequence();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	DerivationImageSequence& operator=(const DerivationImageSequence &der);
	/// Comparison operator
	bool operator==(const DerivationImageSequence &der)const;
	/// Comparison operator
	bool operator!=(const DerivationImageSequence &der)const;

	///
	/// \class DerivationImageMacro
	/// \brief Item in Derivation Image Sequence
	///
	class DerivationImageMacro
	{
	public:
		/// Constructor
		DerivationImageMacro();
		/// Copy constructor
		DerivationImageMacro(const DerivationImageMacro &derivationimagemacro);
		/// Destructor
		~DerivationImageMacro();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		DerivationImageMacro& operator=(const DerivationImageMacro &derivationimagemacro);
		/// Comparison operator
		bool operator==(const DerivationImageMacro &derivationimagemacro)const;
		/// Comparison operator
		bool operator!=(const DerivationImageMacro &derivationimagemacro)const;

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

		/// Derivation Description : Tag (0008, 2111), VR = ST [optional]
		bool SetDerivationDescription(const DcsShortText &strDescription);
		/// @see SetDerivationDescription
		DcsString GetDerivationDescription()const;

		/// Derivation Code Sequence : Tag (0008, 9215), VR = SQ [required]
		bool SetDerivationCodeSequence(const Array1D<PurposeOfReferenceImageDerivation> &arrayDescription);
		/// @see SetDerivationDescription
		bool GetDerivationCodeSequence(Array1D<CodeSequence> &arrayDescription)const;
		/// @see SetDerivationDescription
		Array1D<PurposeOfReferenceImageDerivation>& GetDerivationCodeSequence();
		/// @see SetDerivationDescription
		const Array1D<PurposeOfReferenceImageDerivation>& GetDerivationCodeSequence()const;

		/// Source Image Sequence : Tag (0008, 2112), VR = SQ [required (type 2), but can be empty]
		bool SetSourceImage(const Array1D<ReferencedImageSequence::ReferencedImageMacro> &arraySourceImage);
		/// @see SetSourceImage
		bool GetSourceImage(Array1D<ReferencedImageSequence::ReferencedImageMacro> &arraySourceImage)const;
		/// @see SetSourceImage
		Array1D<ReferencedImageSequence::ReferencedImageMacro>& GetSourceImage();
		/// @see SetSourceImage
		const Array1D<ReferencedImageSequence::ReferencedImageMacro>& GetSourceImage()const;

	protected:
		class ImplDerivationImageMacro;
		ImplDerivationImageMacro	*m_pImplDerivationImageMacro; ///< Internal implementation
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

	/// Derivation Image Sequence : Tag (0008, 9124), VR = SQ [required (type 2), can be empty]
	bool SetDerivedImages(const Array1D<DerivationImageMacro> &arrayImages);
	/// @see SetDerivedImages
	bool GetDerivedImages(Array1D<DerivationImageMacro> &arrayImages)const;
	/// @see SetDerivedImages
	Array1D<DerivationImageMacro>& GetDerivedImages();
	/// @see SetDerivedImages
	const Array1D<DerivationImageMacro>& GetDerivedImages()const;

protected:
	class ImplDerivationImageSequence;
	ImplDerivationImageSequence	*m_pImplDerivationImageSequence; ///< Internal implementation
};

}//namespace SDICOS

#endif
