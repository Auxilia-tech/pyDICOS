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
#ifndef _STRATOVAN_DICOS_GENERAL_IMAGE_MODULE_H_
#define _STRATOVAN_DICOS_GENERAL_IMAGE_MODULE_H_

#include "SDICOS/String.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/ImagePixelMacro.h"
#include "SDICOS/ImageSopInstanceReference.h"
#include "SDICOS/PurposeOfReferenceCode.h"
#include "SDICOS/IconImage.h"
#include "SDICOS/ImageType.h"

namespace SDICOS
{

///
/// \class GeneralImageModule
/// \brief Implements General Image
/// SPECREF V03 Section 14.3.1, Table 95
///
class GeneralImageModule : public ImageType
{
public:
	///
	/// Constructor
	///
	GeneralImageModule();
	///
	/// Copy Constructor
	///
	GeneralImageModule(const GeneralImageModule &generalimagemodule);
	///
	/// Destructor
	///
	virtual ~GeneralImageModule();

	///
	/// Reset to default values
	///
	virtual void FreeMemory();

	///
	/// Copy operator
	///
	GeneralImageModule& operator=(const GeneralImageModule &generalimagemodule);
	///
	/// Comparison operator
	///
	bool operator==(const GeneralImageModule &generalimagemodule)const;
	///
	/// Comparison operator
	///
	bool operator!=(const GeneralImageModule &generalimagemodule)const;

	typedef enum
	{
		enumUnknownLossyImageCompressionMethod, ///< Unknown enumeration

		enumISO_10918_1,	///< "ISO_10918_1" = JPEG Lossy Compression, 
		enumISO_14495_1,	///< "ISO_14495_1" = JPEG-LS Near-Lossless Compression, 
		enumISO_15444_1,	///< "ISO_15444_1" = JPEG 2000 Irreversible Compression, 
		enumISO_13818_2,	///< "ISO_13818_2" = MPEG2 Compression

	}LOSSY_IMAGE_COMPRESSION_METHOD;

	typedef enum
	{
		enumUnknownPresentationLutShape, ///< Unknown enumeration

		enumIdentity,	///< "IDENTITY", 
		enumInverse,	///< "INVERSE"

	}PRESENTATION_LUT_SHAPE;

	///
	/// \class ImageSequenceItem
	/// \brief Implements a sequence item used for reference and source image sequences
	///
	class ImageSequenceItem
	{
	public:
		///
		/// Constructor
		///
		ImageSequenceItem();
		///
		/// Copy constructor
		///
		ImageSequenceItem(const ImageSequenceItem &imagesequenceitem);
		///
		/// Destructor
		///
		virtual ~ImageSequenceItem();

		///
		/// Reset to default values
		///
		void FreeMemory();

		///
		/// Copy operator
		///
		ImageSequenceItem& operator=(const ImageSequenceItem &imagesequenceitem);
		///
		/// Comparison operator
		///
		bool operator==(const ImageSequenceItem &imagesequenceitem)const;
		///
		/// Comparison operator
		///
		bool operator!=(const ImageSequenceItem &imagesequenceitem)const;

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

		///
		/// Set the image SOP instance reference
		///
		bool SetImageSopInstanceReference(const ImageSopInstanceReference &imagesopinstancereference);

		/// @see SetImageSopInstanceReference
		bool GetImageSopInstanceReference(ImageSopInstanceReference &imagesopinstancereference)const;

		/// @see SetImageSopInstanceReference
		ImageSopInstanceReference& GetImageSopInstanceReference();
		/// @see SetImageSopInstanceReference
		const ImageSopInstanceReference& GetImageSopInstanceReference()const;

		///
		/// Set the Purpose of Reference (Single Item Sequence) : Tag (0040, A170), VR = SQ [optional]
		///
		bool SetPurposeOfReference(const PurposeOfReferenceReferencedImage &purposeofreferencecode);

		/// @see SetPurposeOfReference
		bool GetPurposeOfReference(CodeSequence &purposeofreferencecode)const;

		///
		/// Delete the Purpose of Reference
		///
		void DeletePurposeOfReference();

	protected:
		class ImplImageSequenceItem;
		ImplImageSequenceItem *m_pImplImageSequenceItem; ///< Internal implementation
	};

	///
	/// \class ReferencedInstanceSequenceItem
	/// \brief Implements a sequence item for referenced instance sequence (0008, 114A)
	///
	class ReferencedInstanceSequenceItem
	{
	public:
		///
		/// Constructor
		///
		ReferencedInstanceSequenceItem();
		///
		/// Copy constructor
		///
		ReferencedInstanceSequenceItem(const ReferencedInstanceSequenceItem &referencedinstancesequenceitem);
		///
		/// Destructor
		///
		virtual ~ReferencedInstanceSequenceItem();

		///
		/// Reset to default values
		///
		void FreeMemory();

		///
		/// Copy operator
		///
		ReferencedInstanceSequenceItem& operator=(const ReferencedInstanceSequenceItem &referencedinstancesequenceitem);
		///
		/// Comparison operator
		///
		bool operator==(const ReferencedInstanceSequenceItem &referencedinstancesequenceitem)const;
		///
		/// Comparison operator
		///
		bool operator!=(const ReferencedInstanceSequenceItem &referencedinstancesequenceitem)const;

		/// Enumerations for spatial location reserved
		typedef enum
		{
			enumUnkownSpatialLocationFlag, ///< Unknown enumeration

			enumYes,			///< "YES" 
			enumNo,				///< "NO"
			enumReorientedOnly,	///< "REORIENTED_ONLY"

		}SPATIAL_LOCATION_PRESERVED;

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

		///
		/// Set SOP Instance Reference
		///
		bool SetSopInstanceReference(const SopInstanceReference &sopinstancereference);
		/// @see SetSopInstanceReference
		bool GetSopInstanceReference(SopInstanceReference &sopinstancereference)const;
		/// @see SetSopInstanceReference
		SopInstanceReference& GetSopInstanceReference();
		/// @see SetSopInstanceReference
		const SopInstanceReference& GetSopInstanceReference()const;

		///
		/// Set Purpose of Reference (Single Item Sequence) : Tag (0040, A170), VR = SQ [optional]
		///
		bool SetPurposeOfReference(const PurposeOfReferenceReferencedImage &purposeofreferencecode);
		/// @see SetPurposeOfReference
		bool GetPurposeOfReference(CodeSequence &purposeofreferencecode)const;

		///
		/// Delete Purpose of Reference
		///
		void DeletePurposeOfReference();

		///
		/// Set Spatial Locations Preserved : Tag (0028, 135A), VR = CS [optional]
		///
		bool SetSpatialLocationsPreserved(const SPATIAL_LOCATION_PRESERVED nSpatialLocationPreserved);

		/// @see SetSpatialLocationsPreserved
		SPATIAL_LOCATION_PRESERVED GetSpatialLocationsPreserved()const;
		/// @see SetSpatialLocationsPreserved
		DcsString GetSpatialLocationsPreservedAsString()const;

		///
		/// Delete Spatial Locations Preserved
		///
		void DeleteSpatialLocationPreserved();

	private:
		class ImplReferencedInstanceSequenceItem;
		ImplReferencedInstanceSequenceItem *m_pImplReferencedInstanceSequenceItem; ///< Internal implementation
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

	///
	/// Instance Number. A number to identify the image within the same series : Tag (0020, 0013), VR = IS [required]
	///
	bool SetInstanceNumber(const S_INT32 nInstanceNumber);

	/// @see SetInstanceNumber
	S_INT32 GetInstanceNumber()const;
	/// @see SetInstanceNumber
	DcsString GetInstanceNumberAsString()const;

	///
	/// Set Content Date and Time : Tags (0008, 0023) & (0008, 0033)
	///
	/// @param strDate Date image was created : Tag (0008, 0023), VR = DA [required]
	/// @param strTime Time image was created : Tag (0008, 0033), VR = TM [required]
	///
	bool SetContentTimeAndDate(const DcsDate &strDate, const DcsTime &strTime);

	/// @see SetContentTimeAndDate
	DcsTime GetContentTime()const;
	/// @see SetContentTimeAndDate
	DcsDate GetContentDate()const;

	///
	/// Set Acquisition Number : Tag (0020, 0012), VR = IS [optional]
	///
	bool SetAcquisitionNumber(const S_INT32 nAcquisitionNumber);

	/// @see SetAcquisitionNumber
	S_INT32 GetAcquisitionNumber()const;
	/// @see SetAcquisitionNumber
	DcsString GetAcquisitionNumberAsString()const;
	///
	/// Delete attribute
	///
	void DeleteAcquisitionNumber();
	/// Valid Acquisition Number has been set
	bool HasAcquisitionNumber() const;

	///
	/// Set Acquisition Date and Time : Tag (0008, 002A), VR = DT [optional]
	///
	virtual bool SetAcquisitionDateAndTime(const DcsDateTime &strDateTime);

	/// @see SetAcquisitionDateAndTime
	DcsDateTime GetAcquisitionDateAndTime()const;
	///
	/// Delete attribute
	///
	void DeleteAcquisitionDateAndTime();

	///
	/// Acquisition Duration : Tag (0018, 9073), VR = FD [optional]
	///
	virtual bool SetAcquisitionDuration(const double nAcquisitionDuration);

	/// @see SetAcquisitionDuration
	double GetAcquisitionDuration()const;
	///
	/// Delete attribute
	///
	void DeleteAcquisitionDuration();
	/// Acquisition Duration is set
	/// @return true/false
	bool HasAcquisitionDuration() const;

	///
	/// Referenced Image Sequence : Tag (0008, 1140), VR = SQ [optional]
	///
	bool SetReferencedImages(const Array1D<ImageSequenceItem> &arrayImageReferences);

	/// @see SetReferencedImages
	bool GetReferencedImages(Array1D<ImageSequenceItem> &arrayImageReferences)const;

	///
	/// Set number of sequence items for Referenced Image Sequence [optional]
	///
	void SetNumberOfReferencedImages(const S_UINT32 nNumImages);
	/// @see SetReferencedImages
	Array1D<ImageSequenceItem>& GetReferencedImages();
	/// @see SetReferencedImages
	const Array1D<ImageSequenceItem>& GetReferencedImages()const;
	///
	/// Delete attribute
	///
	void DeleteReferencedImages();

	///
	/// Derivation Description : Tag (0008, 2111), VR = ST [optional]
	///
	bool SetDerivationDescription(const DcsShortText &strDerivationDescription);

	/// @see SetDerivationDescription
	DcsString GetDerivationDescription()const;

	/// Has the Derivation Description been set
	/// @return true/false
	bool HasDerivationDescription() const;

	///
	/// Delete attribute
	///
	void DeleteDerivationDescription();
			
	///
	/// Derivation Code Sequence : Tag (0008, 9215), VR = SQ [optional]
	///
	bool SetDerivationCode(const Array1D<PurposeOfReferenceImageDerivation> &arrayDerivationCode);

	/// @see SetDerivationCode
	bool GetDerivationCode(Array1D<CodeSequence> &arrayDerivationCode)const;

	///
	/// Set number of sequence items for Derivation Code Sequence [optional]
	///
	void SetNumberOfDerivationCodeItems(const S_UINT32 nNumItems);
	/// @see SetDerivationCode
	Array1D<PurposeOfReferenceImageDerivation>& GetDerivationCode();
	/// @see SetDerivationCode
	const Array1D<PurposeOfReferenceImageDerivation>& GetDerivationCode()const;
	///
	/// Delete attribute
	///
	void DeleteDerivationCode();

	///
	/// Source Image Sequence : Tag (0008, 2112), VR = SQ [optional]
	///
	bool SetSourceImages(const Array1D<ImageSequenceItem> &arraySourceImages);
	/// @see SetSourceImages
	bool GetSourceImages(Array1D<ImageSequenceItem> &arraySourceImages)const;

	///
	/// Set number of sequence items for Source Image Sequence [optional]
	///
	void SetNumberOfSourceImageItems(const S_UINT32 nNumItems);
	/// @see SetSourceImages
	Array1D<ImageSequenceItem>& GetSourceImages();
	/// @see SetSourceImages
	const Array1D<ImageSequenceItem>& GetSourceImages()const;
	///
	/// Delete attribute
	///
	void DeleteSourceImages();

	///
	/// Referenced Instance Sequence : Tag (0008, 114A), VR = SQ [optional]
	///
	bool SetReferencedInstances(const Array1D<ReferencedInstanceSequenceItem> &arrayReferencedInstances);
	/// @see SetReferencedInstances
	bool GetReferencedInstances(Array1D<ReferencedInstanceSequenceItem> &arrayReferencedInstances)const;

	///
	/// Set number of sequence items for Referenced Instance Sequence [optional]
	///
	void SetNumberOfReferencedInstances(const S_UINT32 nNumItems);
	/// @see SetReferencedInstances
	Array1D<ReferencedInstanceSequenceItem>& GetReferencedInstances();
	/// @see SetReferencedInstances
	const Array1D<ReferencedInstanceSequenceItem>& GetReferencedInstances()const;
	///
	/// Delete attribute
	///
	void DeleteReferencedInstances();

	///
	/// Images in Acquisition : Tag (0020, 1002), VR = IS [optional]
	///
	bool SetNumberOfImagesInAcquisition(const S_INT32 nNumberOfImagesInAcquisition);
	/// @see SetNumberOfImagesInAcquisition
	S_INT32 GetNumberOfImagesInAcquisition()const;
	/// @see SetNumberOfImagesInAcquisition
	DcsString GetNumberOfImagesInAcquisitionAsString()const;
	///
	/// Delete attribute
	///
	void DeleteNumberOfImagesInAcquisition();

	///
	/// Image Comments : Tag (0020, 4000), VR = LT [optional]
	///
	bool SetImageComments(const DcsLongText &strImageComments);
	/// @see SetImageComments
	DcsString GetImageComments()const;
	///
	/// Delete attribute
	///
	void DeleteImageComments();

	///
	/// Quality Image Control : Tag (0028, 0300), VR = CS [optional]
	/// 
	bool SetQualityImageControl(const bool bIsQualityImageControl);
	/// @see SetQualityImageControl
	bool IsQualityImageControl()const;
	/// @see SetQualityImageControl
	DcsString GetQualityImageControlFlag()const;
	///
	/// Delete attribute
	///
	void DeleteQualityImageControlFlag();

	///
	/// Burned In Annotation : Tag (0028, 0301), VR = CS [required]
	///
	bool SetBurnedInAnnotation(const bool bHasBurnedInAnnotation);
	/// @see SetBurnedInAnnotation
	bool HasBurnedInAnnotation()const;
	/// @see SetBurnedInAnnotation
	DcsString GetBurnedInAnnotationFlag()const;

	///
	/// Get Lossy Image Compression : Tag (0028, 2110), VR = CS [required]
	///
	bool HasLossyImageCompression()const;
	/// @see HasLossyImageCompression
	DcsString GetLossyImageCompressionFlag()const;

	///
	/// Get Lossy Image Compression Ratio : Tag (0028, 2112), VR = DS [required if "Lossy Image Compression", Tag (0028, 2110), is "01"]
	///
	bool GetLossyImageCompressionRatio(Array1D<float> &arrayCompressionRatios)const;
	/// @see GetLossyImageCompressionRatio
	bool GetLossyImageCompressionRatio(Array1D<DcsString> &arrayCompressionRatios)const;

	///
	/// Get Lossy Image Compression Method : Tag (0028, 2114), VR = CS [required if "Lossy Image Compression", Tag (0028, 2110), is "01"]
	///
	bool GetLossyImageCompressionMethods(Array1D<LOSSY_IMAGE_COMPRESSION_METHOD> &arrayCompressionMethods)const;
	/// @see GetLossyImageCompressionMethods
	bool GetLossyImageCompressionMethods(Array1D<DcsString> &arrayCompressionMethods)const;

	///
	/// Set Icon Image Sequence (Single Item Sequence) : Tag (0088, 0200), VR = SQ [optional]
	///
	bool SetIconImage(const IconImage &iconimage);
	/// @see SetIconImage
	bool GetIconImage(IconImage &iconimage)const;
	/// Allocate Icon Image
	void AllocateIconImage();
	/// Get the icon image.  Allocate it if no image is present.
	IconImage* GetIconImage();
	/// @see SetIconImage
	const IconImage* GetIconImage()const;
	///
	/// Delete attribute
	///
	void DeleteIconImage();

	///
	/// Presentation LUT Shape : Tag (2050, 0020), VR = CS [optional]
	///
	virtual bool SetPresentationLutShape(const PRESENTATION_LUT_SHAPE nPresentationLutShape);
	/// @see SetPresentationLutShape
	PRESENTATION_LUT_SHAPE GetPresentationLutShape()const;
	/// @see SetPresentationLutShape
	DcsString GetPresentationLutShapeAsString()const;
	///
	/// Delete attribute
	///
	void DeletePresentationLutShape();

private:
	class ImplGeneralImage;
	ImplGeneralImage *m_pImplGeneralImage; ///< Internal implementation
};

}//namespace SDICOS

#endif