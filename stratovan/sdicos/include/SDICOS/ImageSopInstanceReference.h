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
#ifndef _STRATOVAN_DICOS_IMAGE_SOP_INSTANCE_REFERENCE_H_
#define _STRATOVAN_DICOS_IMAGE_SOP_INSTANCE_REFERENCE_H_

#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/SopInstanceReference.h"

namespace SDICOS
{

///
/// \class ImageSopInstanceReference
/// \brief Implements Image SOP Instance Reference Macro
/// SPECREF V03 Section 14.18, Table 124
///
class ImageSopInstanceReference : public SopInstanceReference
{
public:
	///
	/// Constructor
	///
	ImageSopInstanceReference();
	///
	/// Copy constructor
	///
	ImageSopInstanceReference(const ImageSopInstanceReference &imagesopinstancereference);
	///
	/// Destructor
	///
	~ImageSopInstanceReference();

	///
	/// Reset to default values
	///
	virtual void FreeMemory();

	///
	/// Copy operator
	///
	ImageSopInstanceReference& operator=(const ImageSopInstanceReference &imagesopinstancereference);
	///
	/// Comparison operator
	///
	bool operator==(const ImageSopInstanceReference &imagesopinstancereference)const;
	///
	/// Comparison operator
	///
	bool operator!=(const ImageSopInstanceReference &imagesopinstancereference)const;

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
	/// Set Referenced Frame Number.  Indicates frames to which the reference applies.  First frame in volume is 1. (Tag (0008, 1160), VR = IS [required (type 1C) if Referenced SOP Instance is a multi-frame image and the reference does not apply to all frames])
	///
	bool SetReferencedFrameNumbers(const Array1D<S_INT32> &arrayReferencedFrameNumbers);

	/// @see SetReferencedFrameNumbers
	bool GetReferencedFrameNumbers(Array1D<S_INT32> &arrayReferencedFrameNumbers)const;
	/// @see SetReferencedFrameNumbers
	bool GetReferencedFrameNumbersAsString(Array1D<DcsString> &arrayReferencedFrameNumbers)const;
	/// @see SetReferencedFrameNumbers
	const Array1D<S_INT32>& GetReferencedFrameNumbers()const;

	///
	/// Set Referenced Segment Number.  Indicates segments to which the reference applies. First segment is 1. (Tag (0062, 000B), VR = US [required (type 1C) if Referenced SOP Instance is a segmentation and the reference does not apply to all frames])
	///
	bool SetReferencedSegmentNumbers(const Array1D<S_UINT16> &arrayReferencedSegmentNumbers);

	/// @see SetReferencedSegmentNumbers
	bool GetReferencedSegmentNumbers(Array1D<S_UINT16> &arrayReferencedSegmentNumbers)const;
	/// @see SetReferencedSegmentNumbers
	const Array1D<S_UINT16>& GetReferencedSegmentNumbers()const;

protected:
	class ImplImageSopInstanceReference;
	ImplImageSopInstanceReference *m_pImplImageSopInstanceReference; ///< Internal implementation
};
//////////////////////////////////////////////////////////////

}//namespace SDICOS
#endif