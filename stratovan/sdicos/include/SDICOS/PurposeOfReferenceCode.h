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
#ifndef _STRATOVAN_DICOS_PURPOSE_OF_REFERENCE_CODE_H_
#define _STRATOVAN_DICOS_PURPOSE_OF_REFERENCE_CODE_H_

#include "SDICOS/CodeSequence.h"

/// Purpose of Reference Classes:
///	-Context ID = 7005 : class PurposeOfReferenceContributingEquipment
///	-Context ID = 7201 : class PurposeOfReferenceReferencedImage
///	-Context ID = 7202 : class PurposeOfReferenceImageSource
///	-Context ID = 7203 : class PurposeOfReferenceImageDerivation

namespace SDICOS
{

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

///
/// \class PurposeOfReferenceReferencedImage
/// \brief Implements a specialized Code Sequence with Context ID = 7201
/// SPECREF V03 Section 14.11.8, Table 108
///
/// Context ID = 7201
/// Code Scheme Designator = DCM
class PurposeOfReferenceReferencedImage : public CodeSequence
{
public:

	///
	/// Constructor
	///
	PurposeOfReferenceReferencedImage();
	///
	/// Copy constructor
	///
	PurposeOfReferenceReferencedImage(const PurposeOfReferenceReferencedImage &purposeofreferencereferencedimage);
	///
	/// Destructor
	///
	~PurposeOfReferenceReferencedImage();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	PurposeOfReferenceReferencedImage& operator=(const PurposeOfReferenceReferencedImage &purposeofreferencereferencedimage);
	///
	/// Comparison operator
	///
	bool operator==(const PurposeOfReferenceReferencedImage &purposeofreferencereferencedimage)const;
	///
	/// Comparison operator
	///
	bool operator!=(const PurposeOfReferenceReferencedImage &purposeofreferencereferencedimage)const;
	///
	/// Comparison operator
	///
	bool operator==(const CodeSequence &codesequence)const;
	///
	/// Comparison operator
	///
	bool operator!=(const CodeSequence &codesequence)const;

	/// Enumerations for code values and code meanings (ex. enum121311: Code Value = 121311)
	typedef enum
	{
		enumUnknownReferencedImageCodeValue, ///< Unknown code value

		enum121311,	///< Sets Code meaning: "Localizer"
		enum121312,	///< Sets Code meaning: "Biopsy localizer"
		enum121313,	///< Sets Code meaning: "Other partial views"
		enum121314,	///< Sets Code meaning: "Other image of biplane pair"
		enum121315,	///< Sets Code meaning: "Other image of stereoscopic pair"

		enum121316,	///< Sets Code meaning: "Images related to standalone object"
		enum121317,	///< Sets Code meaning: "Spectroscopy"
		enum121338,	///< Sets Code meaning: "Anatomic image"
		enum121339,	///< Sets Code meaning: "Functional image"
		enum121340,	///< Sets Code meaning: "Spectral filtered image"

		enum121341,	///< Sets Code meaning: "Device localizer"
		enum121346,	///< Sets Code meaning: "Acquisition frames corresponding to volume"
		enum121347,	///< Sets Code meaning: "Volume corresponding to spatially-related acquisition frames"
		enum121348,	///< Sets Code meaning: "Temporal predecessor"
		enum121349,	///< Sets Code meaning: "Temporal successor"

	}REFERENCED_IMAGE_CODE_VALUE;

	///
	/// Get a list of all the enumerations with the corresponding code meaning strings (i.e. arrayCodeValue[0] = enum121311 and arrayCodeValueString[0] = "Localizer")
	///
	/// @param arrayCodeValue Array of REFERENCED_IMAGE_CODE_VALUE enumeration
	/// @param arrayCodeValueString Array of code meaning strings
	///
	static void GetCodeList(Array1D<REFERENCED_IMAGE_CODE_VALUE> &arrayCodeValue, Array1D<DcsString> &arrayCodeValueString);

	///
	/// Sets Code Value(Tag (0008, 0100)) and Code Meaning (Tag (0008, 0104)) [required]
	///
	bool SetCodeValue(const REFERENCED_IMAGE_CODE_VALUE nCodeValue);

	///
	/// Determine if all attributes are properly set
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

private:
	///
	/// Code Scheme Designator set to "DCM" : Tag (0008, 0102), VR = SH [required]
	///
	virtual bool SetSchemeDesignator(const DcsShortString &strSchemeDesignator);		

	///
	/// Context Identifier set to 7201 : Tag (0008, 010F), VR = CS [optional]
	///
	virtual bool SetContextID(const DcsCodeString &strContextID);

	///
	/// Replaced with enumeration version of function
	///
	virtual bool SetCodeValue(const DcsShortString &strCodeValue);

	///
	/// Code Meaning set in SetCodeValue(REFERENCED_IMAGE_CODE_VALUE) : Tag (0008, 0104), VR = LO [required]	
	///
	virtual bool SetCodeMeaning(const DcsLongString &strCodeMeaning);
};

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

///
/// \class PurposeOfReferenceImageSource
/// \brief Implements a specialized Code Sequence with Context ID = 7202
/// SPECREF V03 Section 14.11.8, Table 108
///
/// Context ID = 7202
/// Code Scheme Designator = DCM
class PurposeOfReferenceImageSource : public CodeSequence
{
public:

	///
	/// Constructor
	///
	PurposeOfReferenceImageSource();
	///
	/// Copy constructor
	///
	PurposeOfReferenceImageSource(const PurposeOfReferenceImageSource &purposeofreferenceimagesource);
	
	///
	/// Destructor
	///
	~PurposeOfReferenceImageSource();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	PurposeOfReferenceImageSource& operator=(const PurposeOfReferenceImageSource &purposeofreferenceimagesource);
	///
	/// Comparison operator
	///
	bool operator==(const PurposeOfReferenceImageSource &purposeofreferenceimagesource)const;
	///
	/// Comparison operator
	///
	bool operator!=(const PurposeOfReferenceImageSource &purposeofreferenceimagesource)const;
	///
	/// Comparison operator
	///
	bool operator==(const CodeSequence &codesequence)const;
	///
	/// Comparison operator
	///
	bool operator!=(const CodeSequence &codesequence)const;

	/// Enumerations for code values and code meanings (ex. enum121320: Code Value = 121320)
	typedef enum
	{
		enumUnknownImageSourceCodeValue, ///< Unknown code value

		enum121320, ///< Sets Code meaning: "Uncompressed predecessor"
		enum121321, ///< Sets Code meaning: "Mask image for image processing operation"
		enum121322, ///< Sets Code meaning: "Source image for image processing operation"
		enum121329, ///< Sets Code meaning: "Source image montage"
		enum121330, ///< Sets Code meaning: "Lossy compressed predecessor"
		enum121358, ///< Sets Code meaning: "For Processing predecessor"

	}IMAGE_SOURCE_CODE_VALUE;

	///
	/// Get a list of all the enumerations with the corresponding code meaning strings (i.e. arrayCodeValue[0] = enum121320 and arrayCodeValueString[0] = "Uncompressed predecessor")
	///
	/// @param arrayCodeValue Array of IMAGE_SOURCE_CODE_VALUE enumeration
	/// @param arrayCodeValueString Array of code meaning strings
	///
	static void GetCodeList(Array1D<IMAGE_SOURCE_CODE_VALUE> &arrayCodeValue, Array1D<DcsString> &arrayCodeValueString);

	///
	/// Sets Code Value(Tag (0008, 0100)) and Code Meaning (Tag (0008, 0104)) [required]
	///
	bool SetCodeValue(const IMAGE_SOURCE_CODE_VALUE nCodeValue);

	///
	/// Determine if all attributes are properly set
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

private:
	///
	/// Code Scheme Designator set to "DCM" : Tag (0008, 0102), VR = SH [required]
	///
	virtual bool SetSchemeDesignator(const DcsShortString &strSchemeDesignator);		

	///
	/// Context Identifier set to 7202 : Tag (0008, 010F), VR = CS [optional]
	///
	virtual bool SetContextID(const DcsCodeString &strContextID);

	///
	/// Replaced with enumeration version of function
	///
	virtual bool SetCodeValue(const DcsShortString &strCodeValue);

	///
	/// Code Meaning set in SetCodeValue(IMAGE_SOURCE_CODE_VALUE) : Tag (0008, 0104), VR = LO [required]	
	///
	virtual bool SetCodeMeaning(const DcsLongString &strCodeMeaning);
};

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

///
/// \class PurposeOfReferenceImageDerivation
/// \brief Implements a specialized Code Sequence with Context ID = 7203
/// SPECREF V03 Section 14.11.8, Table 108
///
/// Context ID = 7203
/// Code Scheme Designator = DCM
class PurposeOfReferenceImageDerivation : public CodeSequence
{
public:

	///
	/// Constructor
	///
	PurposeOfReferenceImageDerivation();
	///
	/// Copy constructor
	///
	PurposeOfReferenceImageDerivation(const PurposeOfReferenceImageDerivation &purposeofreferenceimagederivation);
	///
	/// Destructor
	///
	~PurposeOfReferenceImageDerivation();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	PurposeOfReferenceImageDerivation& operator=(const PurposeOfReferenceImageDerivation &purposeofreferenceimagederivation);
	///
	/// Comparison operator
	///
	bool operator==(const PurposeOfReferenceImageDerivation &purposeofreferenceimagederivation)const;
	///
	/// Comparison operator
	///
	bool operator!=(const PurposeOfReferenceImageDerivation &purposeofreferenceimagederivation)const;
	///
	/// Comparison operator
	///
	bool operator==(const CodeSequence &codesequence)const;
	///
	/// Comparison operator
	///
	bool operator!=(const CodeSequence &codesequence)const;

	/// Enumerations for code values and code meanings (ex. enum113040: Code Value = 113040)
	typedef enum
	{
		enumUnknownImageDerivationCodeValue, ///< Unknown code value

		enum113040, ///< Sets Code meaning: "Lossy Compression"
		enum113041, ///< Sets Code meaning: "Apparent Diffusion Coefficient"
		enum113042, ///< Sets Code meaning: "Pixel by pixel addition"
		enum113043, ///< Sets Code meaning: "Diffusion weighted"
		enum113044, ///< Sets Code meaning: "Diffusion Anisotropy"
		
		enum113045, ///< Sets Code meaning: "Diffusion Attenuated"
		enum113046, ///< Sets Code meaning: "Pixel by pixel division"
		enum113047, ///< Sets Code meaning: "Pixel by pixel mask"
		enum113048, ///< Sets Code meaning: "Pixel by pixel Maximum"
		enum113049, ///< Sets Code meaning: "Pixel by pixel mean"
		
		enum113050, ///< Sets Code meaning: "Metabolite Maps from spectroscopy data"
		enum113051, ///< Sets Code meaning: "Pixel by pixel Minimum"
		enum113052, ///< Sets Code meaning: "Mean Transit Time"
		enum113053, ///< Sets Code meaning: "Pixel by pixel multiplication"
		enum113054, ///< Sets Code meaning: "Negative Enhancement Integral"
		
		enum113055, ///< Sets Code meaning: "Regional Cerebral Blood Flow"
		enum113056, ///< Sets Code meaning: "Regional Cerebral Blood Volume"
		enum113057, ///< Sets Code meaning: "R-Coefficient Map"
		enum113058, ///< Sets Code meaning: "Proton Density map"
		enum113059, ///< Sets Code meaning: "Signal Change Map"
		
		enum113060, ///< Sets Code meaning: "Signal to Noise Map"
		enum113061, ///< Sets Code meaning: "Standard Deviation"
		enum113062, ///< Sets Code meaning: "Pixel by pixel subtraction"
		enum113063, ///< Sets Code meaning: "T1 Map"
		enum113064, ///< Sets Code meaning: "T2* Map"
		
		enum113065, ///< Sets Code meaning: "T2 Map"
		enum113066, ///< Sets Code meaning: "Time Course of Signal"
		enum113067, ///< Sets Code meaning: "Temperature encoded"
		enum113068, ///< Sets Code meaning: "Student's-Test"
		enum113069, ///< Sets Code meaning: "Time To Peak map"
		
		enum113070, ///< Sets Code meaning: "Velocity encoded"
		enum113071, ///< Sets Code meaning: "Z-Score Map"
		enum113072, ///< Sets Code meaning: "Multiplanar reformatting"
		enum113073, ///< Sets Code meaning: "Curved multiplanar reformatting"
		enum113074, ///< Sets Code meaning: "Volume rendering"
		
		enum113075, ///< Sets Code meaning: "Surface rendering"
		enum113076, ///< Sets Code meaning: "Segmentation"
		enum113077, ///< Sets Code meaning: "Volume editing"
		enum113078, ///< Sets Code meaning: "Maximum intensity projection"
		enum113079, ///< Sets Code meaning: "Minimum intensity projection"
		
		enum113085, ///< Sets Code meaning: "Spatial resampling"
		enum113086, ///< Sets Code meaning: "Edge enhancement"
		enum113087, ///< Sets Code meaning: "Smoothing"
		enum113088, ///< Sets Code meaning: "Gaussian blur"
		enum113089, ///< Sets Code meaning: "Unsharp mask"
		
		enum113090, ///< Sets Code meaning: "Image stitching"
		enum113091, ///< Sets Code meaning: "Spatially-related frames extracted from the volume"
		enum113092, ///< Sets Code meaning: "Temporally-related frames extracted from the set of volumes"
		enum113097, ///< Sets Code meaning: "Multi-energy proportional weighting"
		enum113093, ///< Sets Code meaning: "Polar to Rectangular Scan Conversion"

	}IMAGE_DERIVATION_CODE_VALUE;

	///
	/// Get a list of all the enumerations with the corresponding code meaning strings (i.e. arrayCodeValue[0] = enum113040 and arrayCodeValueString[0] = "Lossy Compression")
	///
	/// @param arrayCodeValue Array of IMAGE_DERIVATION_CODE_VALUE enumeration
	/// @param arrayCodeValueString Array of code meaning strings
	///
	static void GetCodeList(Array1D<IMAGE_DERIVATION_CODE_VALUE> &arrayCodeValue, Array1D<DcsString> &arrayCodeValueString);

	///
	/// Sets Code Value(Tag (0008, 0100)) and Code Meaning (Tag (0008, 0104)) [required]
	///
	bool SetCodeValue(const IMAGE_DERIVATION_CODE_VALUE nCodeValue);

	///
	/// Determine if all attributes are properly set
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

private:
	///
	/// Code Scheme Designator set to "DCM" : Tag (0008, 0102), VR = SH [required]
	///
	virtual bool SetSchemeDesignator(const DcsShortString &strSchemeDesignator);		

	///
	/// Context Identifier set to 7203 : Tag (0008, 010F), VR = CS [optional]
	///
	virtual bool SetContextID(const DcsCodeString &strContextID);

	///
	/// Replaced with enumeration version of function
	///
	virtual bool SetCodeValue(const DcsShortString &strCodeValue);

	///
	/// Code Meaning set in SetCodeValue(IMAGE_DERIVATION_CODE_VALUE) : Tag (0008, 0104), VR = LO [required]	
	///
	virtual bool SetCodeMeaning(const DcsLongString &strCodeMeaning);
};

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

///
/// \class PurposeOfReferenceContributingEquipment
/// \brief Implements a specialized Code Sequence with Context ID = 7005
/// SPECREF V03 Section 14.11.8, Table 108
/// 
/// Context ID = 7005
/// Code Scheme Designator = DCM
class PurposeOfReferenceContributingEquipment : public CodeSequence
{
public:
	///
	/// Constructor
	///
	PurposeOfReferenceContributingEquipment();
	///
	/// Copy constructor
	///
	PurposeOfReferenceContributingEquipment(const PurposeOfReferenceContributingEquipment &purposeofreferencecontributingequipment);
	///
	/// Destructor
	///
	~PurposeOfReferenceContributingEquipment();

	///
	/// Reset to default values
	///
	void FreeMemory();

	///
	/// Copy operator
	///
	PurposeOfReferenceContributingEquipment& operator=(const PurposeOfReferenceContributingEquipment &purposeofreferencecontributingequipment);
	///
	/// Comparison operator
	///
	bool operator==(const PurposeOfReferenceContributingEquipment &purposeofreferencecontributingequipment)const;
	///
	/// Comparison operator
	///
	bool operator!=(const PurposeOfReferenceContributingEquipment &purposeofreferencecontributingequipment)const;
	///
	/// Comparison operator
	///
	bool operator==(const CodeSequence &codesequence)const;
	///
	/// Comparison operator
	///
	bool operator!=(const CodeSequence &codesequence)const;

	/// Enumerations for code values and code meanings (ex. enum113040: Code Value = 113040)
	typedef enum
	{
		enumUnknownContributingEquipmentCodeValue, ///< Unknown code value

		enum109101, ///< Sets Code meaning: "Acquisition Equipment"
		enum109102, ///< Sets Code meaning: "Processing Equipment"
		enum109103, ///< Sets Code meaning: "Modifying Equipment"
		enum109104, ///< Sets Code meaning: "De-identifying Equipment"
		enum109105, ///< Sets Code meaning: "Frame Extracting Equipment"
		
		enumMEDIM, 	///< Sets Code meaning: "Portable Media Importer Equipment"
		enumFILMD, 	///< Sets Code meaning: "Film Digitizer"
		enumDOCD, 	///< Sets Code meaning: "Document Digitizer Equipment"
		enumVIDD, 	///< Sets Code meaning: "Video Tape Digitizer Equipment"

	}CONTRIBUTING_EQUIPMENT_CODE_VALUE;

	///
	/// Sets Code Value(Tag (0008, 0100)) and Code Meaning (Tag (0008, 0104)) [required]
	///
	bool SetCodeValue(const CONTRIBUTING_EQUIPMENT_CODE_VALUE nCodeValue);

	///
	/// Determine if all attributes are properly set
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

private:
	///
	/// Code Scheme Designator set to "DCM" : Tag (0008, 0102), VR = SH [required]
	///
	virtual bool SetSchemeDesignator(const DcsShortString &strSchemeDesignator);		

	///
	/// Context Identifier set to 7005 : Tag (0008, 010F), VR = CS [optional]
	///
	virtual bool SetContextID(const DcsCodeString &strContextID);

	///
	/// Replaced with enumeration version of function
	///
	virtual bool SetCodeValue(const DcsShortString &strCodeValue);

	///
	/// Code Meaning set in SetCodeValue(CONTRIBUTING_EQUIPMENT_CODE_VALUE) : Tag (0008, 0104), VR = LO [required]	
	///
	virtual bool SetCodeMeaning(const DcsLongString &strCodeMeaning);
};

}//namespace SDICOS

#endif
