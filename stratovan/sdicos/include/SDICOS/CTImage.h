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
#ifndef _STRATOVAN_DICOS_CT_IMAGE_H_
#define _STRATOVAN_DICOS_CT_IMAGE_H_

#include <list>

#include "SDICOS/ImagePixelModule.h"
#include "SDICOS/IconImage.h"
#include "SDICOS/CommonImageDescription.h"
#include "SDICOS/HierarchicalReferences.h"
#include "SDICOS/ImageCharacteristics.h"
#include "SDICOS/ImageBase.h"
namespace SDICOS
{

namespace CTTypes
{

///
/// \class CTImage
///
/// Implements CT Image 
/// SPECREF V03 Section 7.4.2, Table 20
///
/// The base class ImagePixelModule contains
/// the attributes for the Image Pixel Module in the CT Image IOD Modules listing
/// SPECREF V03 Section 7.3, Table 17
///
/// Tags with changed requirements:
/// Image Pixel Module
///	-Scanner Sets or Limits the Following Tags:
///		*Sets "Samples Per Pixel" Tag (0028, 0002) to "1"
///		*Limits "Photometric Interpretation" Tag (0028, 0004) to: "MONOCHROME1", "MONOCHROME2"
/// Presentation LUT Shape : Tag (2050, 0020), VR = CS [required]
///		Value set to "IDENTITY"
///
class CTImage : public ImagePixelModule, public ImageCharacteristics, public ImageCommon
{
public:
	/// Constructor
	CTImage();
	
	/// Copy Constructor
	CTImage(const CTImage &ctimage);
	
	/// Destructor
	virtual ~CTImage();

	/// Free all used memory
	void FreeMemory();

	/// Assignment operator
	CTImage& operator=(const CTImage &ctimage);
	
	/// Equality comparison operator
	bool operator==(const CTImage &ctimage)const;
	
	/// Inequality comparison operator
	bool operator!=(const CTImage &ctimage)const;

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

	/// Check that all mandatory attributes have valid values
	/// @return true/false false if one or more attributes are not valid
	bool IsValid() const;

	/////////////////////////////////////////////////
	//  Tags with changed requirements

	// Image Pixel Module
	//	-Scanner Sets or Limits the Following Tags:
	//		*Sets "Samples Per Pixel" Tag (0028, 0002) to "1"
	//		*Limits "Photometric Interpretation" Tag (0028, 0004) to: "MONOCHROME1", "MONOCHROME2"
	
	// Presentation LUT Shape : Tag (2050, 0020), VR = CS [required]
	//	-Value set to "IDENTITY"

	/////////////////////////////////////////////////

	typedef enum
	{
		enumUnknownCTPixelDataCharacteristics = 0, ///< Unknown pixel characteristics

		enumOriginal,		///< "ORIGINAL"
		enumDerived,		///< "DERIVED"
		enumMixedPixelData,	///< "MIXED"

	}CT_PIXEL_DATA_CHARACTERISTICS;

	typedef enum
	{
		enumUnknownImageFlavor = 0, //< Unknown Image Flavor

		enumProjection,	///< "PROJECTION"
		enumVolume,		///< "VOLUME"

	}IMAGE_FLAVOR;

	typedef enum
	{
		enumUnknownDerivedPixelContrast = 0, //< Unknown Pixel Contrast

		enumAddition,			///< "ADDITION"
		enumDivision,			///< "DIVISION"
		enumMasked,				///< "MASKED"
		enumMaximum,			///< "MAXIMUM"
		enumMultiplication,		///< "MULTIPLICATION"
		enumResampled,			///< "RESAMPLED"
		enumStdDeviation,		///< "STD_DEVIATION"
		enumSubtraction,		///< "SUBTRACTION"
		enumNone,				///< "NONE"
		enumMixedContrast,		///< "MIXED"
		enumFiltered,			///< "FILTERED"
		enumMedian,				///< "MEDIAN"
	}DERIVED_PIXEL_CONTRAST;

	/// \typedef std::list<HierarchicalSopInstanceReference> ReferencedDataSequence
	/// object used to store SOP Instance references for sequence attributes (0x0008, (0x9121, 0x9092, 0x9154, 0x9237))
	typedef std::list<HierarchicalSopInstanceReference> ReferencedDataSequence;
	
	///
	/// Set the Image Type : Tag (0008, 0008), VR = CS [required], VM = 4 : Stored in a single tag
	///
	/// @param nPixel Pixel Data Characteristics
	///			i) Values: "ORIGINAL", "DERIVED", "MIXED"
	/// @param nOOI OOI Image Characteristics
	///			i) Values: "HIGH ENERGY", "LOW ENERGY", "Z_EFFECTIVE", "BASIS_MATERIAL_1", "BASIS_MATERIAL_2", "COMPTON", "PHOTOELECTRIC", "INTENSITY", "DENSITY", "MU", "MULTI ENERGY"
	/// @param nFlavor Image Flavor
	///			i) Values: "PROJECTION", "VOLUME"
	/// @param nContrast Derived Pixel Contrast
	///			i) Values: "ADDITION", "DIVISION", "MASKED", "MAXIMUM", "MULTIPLICATION", "RESAMPLED", "STD_DEVIATION", "SUBTRACTION", "NONE", "MIXED"
	///
	/// @return true/false false if the Image Types given violate the restrictions in Section 7.5.1 if the DICOS Spec
	///
	bool SetImageTypeCT(const CT_PIXEL_DATA_CHARACTERISTICS nPixel, 
						const OOI_IMAGE_CHARACTERISTICS nOOI, 
						const IMAGE_FLAVOR nFlavor, 
						const DERIVED_PIXEL_CONTRAST nContrast);
	
	/// @see SetImageTypeCT
	bool GetImageTypeCT(CT_PIXEL_DATA_CHARACTERISTICS &nPixel, OOI_IMAGE_CHARACTERISTICS &nOOI, IMAGE_FLAVOR &nFlavor, DERIVED_PIXEL_CONTRAST &nContrast)const;
	
	/// @see SetImageTypeCT
	bool GetImageTypeCT(DcsString &nPixel, DcsString &nOOI, DcsString &nFlavor, DcsString &nContrast)const;
	
	/// Set Basis Materials Code Sequence (Single Item Sequence) : Tag (4010, 1045), VR = SQ [required if "Image Type" is "BASIS_MATERIAL_1" or "BASIS_MATERIAL_2"]
	/// @param csBasisMaterial Basis Material Code Sequence
	///			i) Context ID not defined
	bool SetBasisMaterial(const CodeSequence &csBasisMaterial);

	/// @see SetBasisMaterial
	bool GetBasisMaterial(CodeSequence &csBasisMaterial)const;

	/// @see SetBasisMaterial
	CodeSequence* GetBasisMaterial();
	
	/// @see SetBasisMaterial
	const CodeSequence* GetBasisMaterial()const;

	/// Delete conditionally required attribute so that it is not written to DICOS file
	void DeleteBasisMaterial();

	/// Set Common Image Description Macro [required]
	/// @param commonImageDescription CommonImageDescription object
	/// @return true/false false if commonImageDescription is invalid
	bool SetCommonImageDescription(const CommonImageDescription &commonImageDescription);
	
	/// @see SetCommonImageDescription
	bool GetCommonImageDescription(CommonImageDescription &commonimagedescription)const;
	
	/// @see SetCommonImageDescription
	CommonImageDescription* GetCommonImageDescription();
	
	/// @see SetCommonImageDescription
	const CommonImageDescription* GetCommonImageDescription()const;

	/// Set Photometric Interpretation [redefined from "Image Pixel Module", limits values]
	/// @param nPhotometricInterpretation Photometric Interpretation : Tag (0028, 0004), VR = CS [required]
	///			i) Values: CTImage::enumMonochrome1, CTImage::enumMonochrome2
	///			'Get' functions inherited from ImagePixelMacro
	/// @return true/false
	virtual bool SetPhotometricInterpretation(const PHOTOMETRIC_INTERPRETATION nPhotometricInterpretation);

	/// Set Burned In Annotation : Tag (0028, 0301) Defaults to false.
	/// @param bHasBurnedInAnnotation Has Burned In Annotation Flag : Tag (0028, 0301), VR = CS [required]
	///			i) true = "YES", false = "NO"
	/// @return true/false
	bool SetBurnedInAnnotation(const bool bHasBurnedInAnnotation);

	/// @see SetBurnedInAnnotation
	bool HasBurnedInAnnotation() const;
	
	/// Always return "IDENTITY"
	DcsString GetPresentationLUTShape() const;
	
	/// Set Presentation LUT Shape to IDENTITY
	/// @return true/false
	bool SetPresentationLUTShape();
	
	/// Set Acquisition DateTime : Tag (0008, 002A)
	/// @param strDateTime Acquisition Date and Time : Tag (0008, 002A), VR = DT [required if "Image Type" (CT_PIXEL_DATA_CHARACTERISTICS) is "ORIGINAL" or "MIXED"]
	/// @return true/false false if strDateTime is not valid
	bool SetAcquisitionDateAndTime(const DcsDateTime &strDateTime);
	
	/// @see SetAcquisitionDateAndTime
	DcsDateTime GetAcquisitionDateAndTime()const;
	
	/// Convenience method to return result of DcsDateTime::GetCombinedString())
	DcsString GetAcquisitionDateAndTimeAsString()const;
	
	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteAcquisitionDateAndTime();

	/// Set Acquisition Duration : Tag (0018, 9073) in Seconds
	/// @param nAcquisitionDurationSeconds Acquisition Duration : Tag (0018, 9073), VR = FD [required (type 2C) if "Image Type" (CT_PIXEL_DATA_CHARACTERISTICS) is "ORIGINAL" or "MIXED", can be empty]
	/// @return true/false false if duration is invalid
	bool SetAcquisitionDuration(const double nAcquisitionDurationSeconds);
	
	/// @see SetAcquisitionDuration
	double GetAcquisitionDuration()const;
	
	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteAcquisitionDuration();
	
	/// Set Acquisition Number : Tag (0020, 0012).
	/// To invalidate this optional attribute set to -1.
	/// @param nAcquisitionNumber Acquisition Number : Tag (0020, 0012), VR = IS [optional]
	/// @return true/false 
	bool SetAcquisitionNumber(const S_INT32 nAcquisitionNumber);

	/// @see SetAcquisitionNumber
	S_INT32 GetAcquisitionNumber()const;
	
	/// @see SetAcquisitionNumber
	DcsString GetAcquisitionNumberAsString()const;
	
	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteAcquisitionNumber();
	
	/// Set Referenced Raw Data Sequence : Tag (0008, 9121), VR = SQ [optional]
	/// @param arrayReferences Referenced Raw Data as HierarchicalSopInstanceReference objects
	/// @return true/false false if data is invalid
	bool SetReferencedRawData(const Array1D<HierarchicalSopInstanceReference> &arrayReferences);

	/// Add a single raw dfata reference to the "Referenced Raw Data Sequence"
	/// @param hierarchicalSopInstanceRef Raw Data Reference Tag (0008, 9121)
	/// @return true/false 
	bool AddReferencedRawData(const HierarchicalSopInstanceReference& hierarchicalSopInstanceRef);
	
	/// @see SetReferencedRawData
	ReferencedDataSequence& GetReferencedRawData();
	
	/// @see SetReferencedRawData
	const ReferencedDataSequence& GetReferencedRawData()const;
	
	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteReferencedRawData();
	
	/// Set Referenced Image Evidence Sequence : Tag (0008, 9092), VR = SQ [required if "Reference Image Sequence" Tag (0008, 1140) is set]
	/// Invalid HierarchicalSopInstanceReference objects passed in will not be added to the sequence
	/// @param arrayReferences Referenced Image Evidence as HierarchicalSopInstanceReference objects
	/// @return true/false false if data is invalid
	bool SetReferencedImageEvidence(const Array1D<HierarchicalSopInstanceReference> &arrayReferences);

	/// Add a single image evidence reference to the "Referenced Image Evidence Sequence"
	/// @param hierarchicalSopInstanceRef Image Evidence Reference Tag (0008, 9092)
	/// @return true/false 
	bool AddReferencedImageEvidence(const HierarchicalSopInstanceReference& hierarchicalSopInstanceRef);
	
	/// @see SetReferencedImageEvidence
	const ReferencedDataSequence& GetReferencedImageEvidence()const;
	
	/// @see SetReferencedImageEvidence
	ReferencedDataSequence& GetReferencedImageEvidence();

	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteReferencedImageEvidence();
	
	/// Set Source Image Evidence Sequence : Tag (0008, 9154), VR = SQ [required if "Source Image Sequence" Tag (0008, 2112) is set]
	/// @param arrayReferences	Source Image Evidence as HierarchicalSopInstanceReference objects
	/// @return true/false false if the data is invalid
	bool SetSourceImageEvidence(const Array1D<HierarchicalSopInstanceReference> &arrayReferences);

	/// Add a single image evidence reference to the "Source Image Evidence Sequence"
	/// @param hierarchicalSopInstanceRef Source Image Evidence Reference Tag(0008, 9154)
	/// @return true/false 
	bool AddSourceImageEvidence(const HierarchicalSopInstanceReference& hierarchicalSopInstanceRef);
	
	/// @see SetSourceImageEvidence
	ReferencedDataSequence& GetSourceImageEvidence();
	
	/// @see SetSourceImageEvidence
	const ReferencedDataSequence& GetSourceImageEvidence()const;

	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteSourceImageEvidence();
	
	/// Set Referenced Presentation State Sequence : Tag (0008, 9237), VR = SQ [required if "Presentation State" is generated during acquisition]
	/// @param	arrayReferences Referenced Presentation State as HierarchicalSopInstanceReference objects
	/// @return true/false false if the data is invalid
	bool SetReferencedPresentationState(const Array1D<HierarchicalSopInstanceReference> &arrayReferences);

	/// Add a single presentation state reference to the "Source Image Evidence Sequence"
	/// @param hierarchicalSopInstanceRef Presentation State Reference Tag(0008, 9237)
	/// @return true/false 
	bool AddReferencedPresentationState(const HierarchicalSopInstanceReference& hierarchicalSopInstanceRef);
	
	/// @see SetReferencedPresentationState
	ReferencedDataSequence& GetReferencedPresentationState();
	
	/// @see SetReferencedPresentationState
	const ReferencedDataSequence& GetReferencedPresentationState()const;
	
	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteReferencedPresentationState();
	
	/// Set Image Comments : Tag (0020, 4000)
	/// @param strComments Image Comments : Tag (0020, 4000), VR = LT [optional]
	bool SetImageComments(const DcsLongText &strComments);

	/// @see SetImageComments
	DcsString GetImageComments()const;
	
	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteImageComments();

	/// Set Icon Image Sequence (Single Item Sequence) : Tag (0088, 0200), VR = SQ [optional]
	/// @param iconImage	Icon Image
	bool SetIconImage(const IconImage &iconImage);

	/// @see SetIconImage
	bool GetIconImage(IconImage &iconimage)const;

	/// @see SetIconImage
	IconImage* GetIconImage();
	
	/// @see SetIconImage
	const IconImage* GetIconImage()const;
	
	/// Delete optional attribute so that it is not written to the DICOS file
	void DeleteIconImage();

protected:
	class ImplCTImage;
	mutable ImplCTImage	*m_pImplCTImage; ///< Internal implementation

	ImplCTImage* GetImpl();
	const ImplCTImage* GetImpl() const;
	
	/// Virtual methods implemented as SetImageTypeCT(), GetImageTypeCT()
	//virtual bool SetImageType(const PIXEL_DATA_CHARACTERISTICS nPixelDataCharacteristics, const IMAGE_CHARACTERISTICS nImageCharacteristics);

	/// @see CTImage::SetImageType
	//virtual bool GetImageType(PIXEL_DATA_CHARACTERISTICS &nPixelDataCharacteristics, IMAGE_CHARACTERISTICS &nImageCharacteristics)const;

	/// @see CTImage::SetImageType
	//virtual bool GetImageType(DcsString &strPixelDataCharacteristics, DcsString &strImageCharacteristics)const;
	///////////////////////////////////////////////////////////
	
	/// Samples per Pixel : Tag (0028, 0002)
	///	-Value is always set to 1 for CT Tag (0028, 0002), VR = US [required]
	/// @param nSamplesPerPixel	Samples per pixel
	/// @return true/false false if nSamplesPerPixel is not 1
	virtual bool SetSamplesPerPixel(const S_UINT16 nSamplesPerPixel);
};

}//namespace CTTypes

}//namespace SDICOS

#endif
