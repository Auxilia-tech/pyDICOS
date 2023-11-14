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
#ifndef _STRATOVAN_DICOS_SDCS_TEMPLATE_AIT3D_H_
#define	_STRATOVAN_DICOS_SDCS_TEMPLATE_AIT3D_H_

#include "SDICOS/TemplateBase.h"
#include "SDICOS/ModuleAIT3D.h"
#include "SDICOS/TemplateCommon.h"

#include "SDICOS/PlanePositionUser.h"
#include "SDICOS/PixelIntensityRelationshipLUTUser.h"
#include "SDICOS/HierarchicalReferencesUser.h"
#include "SDICOS/FrameOfReferenceUser.h"
#include "SDICOS/ImageBaseUser.h"
#include "SDICOS/AcquisitionContextUser.h"

namespace SDICOS 
{

class AIT3D;

///
/// \class SectionAIT
/// \brief A section of an AIT3D volume
///
/// An AIT3D Series is composed of one or more 3D volumes called Sections. 
///
/// The SDICOS::AIT3D object contains methods for adding and removing Sections.
/// The volume data is represented using the SDICOS::Volume16Bit class.
/// It stores signed or unsigned 16-bit values and contains attributes common to all AIT3D volumes.
///
/// Valid default values are provided for many attributes required by the DICOS specification.
/// Default values for attributes that can be set through the SectionAIT API are as follows:
///
/// - Section Id defaults to 0
/// - PrcsToRcsOrientation defaults to unused
/// - AIT Image Frame Type
///		- Pixel Data Characteristics defaults to ORIGINAL indicating that it contains original, unaltered data.
///		- Image Flavor defaults to VOLUME indicating a regularly sampled volume
///		- Derived Pixel Contrast defaults to none
/// - Common Image Description
///		- Pixel Presentation defaults to MONOCHROME
///		- Volumetric Property defaults to VOLUME
///		- Volume Calculation Technique defaults to NONE
class SectionAIT : public SectionCommon
{

public:
	friend class AIT3D;

	/// Constructor
	SectionAIT();

	/// Construct with identifier
	SectionAIT(const S_UINT32 sectionId);

	/// Copy constructor
	SectionAIT(const SectionAIT &sec);
	/// Destructor
	virtual ~SectionAIT();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	SectionAIT& operator=(const SectionAIT &sec);
	/// Comparison operator
	bool operator==(const SectionAIT &sec)const;
	/// Comparison operator
	bool operator!=(const SectionAIT &sec)const;

	// Attributes from 3D AIT Image Multiframe Functional Groups Macros
	// Pixel Measures in SectionCommon
	// Frame Content is optional and no implemented
	// Plane Position in SectionCommon
	// Plane Orientation in SectionCommon
	// Referenced Image and Derivation Image are conditional and not implemented

	/// Set Person Referenced Coordinate System(PRCS) to Referenced Coordinate System(RCS) 
	/// orientation as two vectors describing the left (+x axis) and front (+y axis) facing directions of the person 
	/// relative to the Reference Coordinate System (RCS).
	/// This attribute is optional and by default not written to the DICOS file.
	/// @param vLeft Directional cosines towards the person's left side
	/// @param vFront Directional cosines towards the person's front side
	/// @return true/false false if 
	bool SetPrcsToRcsOrientation(const Vector3D<float>& vLeft, const Vector3D<float>& vFront);

	/// @see SetPrcsToRcsOrientation
	bool SetPrcsToRcsOrientation(const float fXx, const float fYx, const float fZx, 
							const float fXy, const float fYy, const float fZy);

	/// @see SetPrcsToRcsOrientation
	bool GetPrcsToRcsOrientation(Vector3D<float>& XAxis, Vector3D<float>& YAxis) const;

	/// Determine if the Prcs To Rcs axes have been set
	bool PrcsToRcsSet() const;

	/// Delete so that axes are not written to the DICOS file
	void DeletePrcsToRcs();

	// 3D AIT Image Frame Type

	/// Set the Image characteristics of the pixel/voxel data.
	/// @param pixelDataCharacteristics	Pixel data is 'ORIGINAL' or 'DERIVED'. Defaults to 'ORIGINAL'.
	/// @param imageCharacteristics Image characteristic is 'CNT_AMP', 'CNT_CPX_AMP' or ''. Defaults to ''
	/// @param imageFlavor Image Flavor is 'PROJECTION' or 'VOLUME'. Defaults to 'VOLUME'
	/// @param pixelContrast Derived pixel contrast indicating how images have been combined. Defaults to 'NONE'. 'MIXED' is not allowed.
	/// @return true/false
	bool SetImageType(
		const SDICOS::AIT3DTypes::AIT3DImage::AIT3D_PIXEL_DATA_CHARACTERISTICS pixelDataCharacteristics,
		const SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS imageCharacteristics = SDICOS::AITImageType::enumNoImageCharacteristic,
		const SDICOS::AIT3DTypes::AIT3DImage::IMAGE_FLAVOR imageFlavor = SDICOS::AIT3DTypes::AIT3DImage::enumVolume,
		const SDICOS::AIT3DTypes::AIT3DImage::DERIVED_PIXEL_CONTRAST pixelContrast = SDICOS::AIT3DTypes::AIT3DImage::enumNone
	);

	/// @see SetImageType
	/// @return PIXEL_DATA_CHARACTERISTICS or enumUnknownPixelDataCharacteristics if no pixel data set
	SDICOS::AIT3DTypes::AIT3DImage::AIT3D_PIXEL_DATA_CHARACTERISTICS GetPixelDataCharacteristics() const;

	///@see SetImageType
	///@return AIT3D_IMAGE_CHARACTERISTICS or enumUnknownAIT3DImageCharacteristics if no pixel data is set
	SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS GetImageCharacteristics() const;

	/// @see SetImageType
	/// @return IMAGE_FLAVOR or enumUnknownImageFlavor is no pixel data is set
	SDICOS::AIT3DTypes::AIT3DImage::IMAGE_FLAVOR GetImageFlavor() const;

	/// @see SetImageType
	SDICOS::AIT3DTypes::AIT3DImage::DERIVED_PIXEL_CONTRAST GetDerivedPixelContrast() const;

	/// Set AIT3D Image Description Information. The default values for these attributes are set
	/// for a Monochrome volume with original pixel data (Image Type set using SetImageType() is 'ORIGINAL').
	/// These values can vary across Sections within an
	/// @param pixelPresentation Pixel Presentation indicates presence or absence of color information. Default value is 'MONOCHROME'.
	///			If Pixel Presentation is set to 'COLOR' or 'MIXED', use SetPaletteColorLookupTable() to set LUTs.
	/// @param volumetricProperty Volumetric Property indicates if geometric manipulations on the pixel/voxel data are possible. Default value is 'VOLUME'.
	/// @param volumeCalculationTechnique Indicates the method used for calculating pixels based on geometry. Default value is 'NONE'.
	/// @return true/false false if values could not be set.
	bool SetCommonImageDescription(
		const CommonImageDescription::PIXEL_PRESENTATION pixelPresentation,
		const CommonImageDescription::VOLUMETRIC_PROPERTIES volumetricProperty,
		const CommonImageDescription::VOLUME_BASED_CALCULATION_TECHNIQUE volumeCalculationTechnique
	);

	/// @see SetImageDescription
	bool SetPixelPresentation(const CommonImageDescription::PIXEL_PRESENTATION pixelPresentation);

	/// @see SetImageDescription
	CommonImageDescription::PIXEL_PRESENTATION GetPixelPresentation()const;

	/// @see SetImageDescription
	bool SetVolumetricProperties(const CommonImageDescription::VOLUMETRIC_PROPERTIES volumetricProperty);

	/// @see SetImageDescription
	CommonImageDescription::VOLUMETRIC_PROPERTIES GetVolumetricProperties()const;

	/// @see SetImageDescription
	bool SetVolumeBasedCalculationTechnique(const CommonImageDescription::VOLUME_BASED_CALCULATION_TECHNIQUE volumeCalculationTechnique);

	/// @see SetImageDescription
	CommonImageDescription::VOLUME_BASED_CALCULATION_TECHNIQUE GetVolumeBasedCalculationTechnique()const;

protected:
	class ImplAITSection;

	const ImplAITSection* GetImpl() const;
	ImplAITSection* GetImpl();

private:
	ImplAITSection * m_pImplAITSection; ///< Internal implementation
};

///
/// \class AIT3D
/// \brief Represents a single series in a AIT3D scan with original pixel data.
///
/// The SDICOS::AIT3D object abstracts away the hierarchy of the DICOS 
/// specification and provides an API that contains methods for setting all of
/// the attributes needed for a DICOS CT object.
///
/// This class represents a single Scan in an Object of Inspection (OOI) with original pixel data.
/// Required and optional attributes not explicitly set using the API methods are set to default values.
///
/// The volume data for a single AIT3D scan is contained in one or more volumes called Sections
/// represented using the SDICOS::SectionAIT class. Sections are independently allocated.
///
/// Valid default values are provided for many attributes required by the DICOS specification.
/// Default values for attributes set using the SDICOS::AIT3D API are as follows:
///
/// - Inspection Selection Criteria: Defaults to enumAll
/// - Modality is always AIT
/// - Inspection Selection Criteria defaults to All.
/// - Image Common
///     - Coordinate System
///     - Image Origin
/// - Frame Of Reference UID
///		- Required attribute set to randomly generated UID
/// - Pixel Data Creation Date and Time default to empty Date and Time objects.
/// - Instance Number is initialized to 0
/// - Image Type
///		- Pixel Data Characteristics defaults to Original
///		- Image Flavor defaults to Volume
///		- Derived Pixel Contrast defaults to None
/// - AIT Device Type defaults to PASSIVE_MMW
/// - Common Image Description
///		- Pixel Presentation defaults to MONOCHROME
///		- Volumetric Property defaults to VOLUME
///		- Volume Calculation Technique defaults to NONE
///	- Photometric Interpretation defaults to MONOCHROME2
///		- Indicates that low data values ma to empty Date and Time objects.
/// - Acquisition Date and Time default to empty DcsDate and DcsTime objects
/// - Acquisition Duration defaults to 0.0
/// - Acquisition Number is optional and by default is not written to the DICOS file
/// - Image Comments is optional and defaults to an empty string
/// - Palette Color Lookup Tables
///		- Empty by default and not written to the DICOS file
/// - Pixel Intensity Relationship LUT
///     - Disabled by default. See EnablePixelIntensityRelationshipLUT().
///   
class AIT3D : 
	public IODCommon, 
	public ScanCommon,
	public ImageCommonUser, // See ImageBaseUser.h Add coordinate system and image origin 
	public PixelIntensityRelationshipLUTUser, // See Pixel Intensity Relationship LUT Module Section below.
	public FrameOfReferenceUser, // See FrameOfReferenceUser.h Adds FrameOfReference Module Attributes to the SDICOS::AIT3D User Level API.
	public AcquisitionContextUser

{
public:

	/// Default constructor
	AIT3D();

	/// Construct AIT3D object with Object of Inspection Type, AIT Device Type, presentation intent type and photometric interpretation
	AIT3D(
		const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE nOOIType,
		const AIT3DTypes::AIT3DImage::AIT_DEVICE_TYPE nDeviceType,
		const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI = ImagePixelMacro::enumMonochrome2
	);

	/// Construct AIT3D object with Object of Inspection Gender, AIT Device Type, and photometric interpretation
	/// OOI Type is set to enumTyoePerson
	AIT3D(
		const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER nOOIGender,
		const AIT3DTypes::AIT3DImage::AIT_DEVICE_TYPE nDeviceType = AIT3DTypes::AIT3DImage::enumActiveMillimeterWave,
		const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI = ImagePixelMacro::enumMonochrome2
	);

	/// Copy constructor
	AIT3D(const AIT3D &ait3d);

	~AIT3D();

	/// Copy operator
	AIT3D& operator=(const AIT3D &ait3d);

	/// Comparison operator
	bool operator==(const AIT3D&) const;
	/// Comparison operator
	bool operator!=(const AIT3D&) const;

	/// Free Allocated memory
	void FreeMemory();

	/// Initialize with a vector of AIT3D objects belonging to the same series
	/// @param vSeries Series of AIT3D objects
	/// @param errorlog Error Log. If false is returned, error messages are stored here
	/// @param bMoveData	true = Move data (such as pixel data), instead of copying, from vSeries
	///						false = Copy data from vSeries.
	/// @return true/false false if the AIT3D files do not belong together. Including mismatched OOI ID, Scan Instance UID, Series Instance IOD
	bool Initialize(const std::vector<SDICOS::AIT3DModule*> &vSeries, ErrorLog &errorlog, const bool bMoveData);

	/// Read a series. One error log per file read
	/// @param sopinstance SopInstance object containing filenames to be read
	/// @param vErrorlogs Vector of filename errorlog pairs
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	virtual bool Read(const DicosFileListing::SopInstance& sopinstance, Array1D< std::pair<Filename, ErrorLog> > &vErrorlogs, IMemoryManager *pMemMgr = S_NULL);

	/// Convenience method to read a series that contains a single file
	/// @param filename Filename to be read
	/// @param errorLog Errorlog to store read errors
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	virtual bool Read(const Filename& filename, ErrorLog& errorLog, IMemoryManager *pMemMgr = S_NULL);

	/// Read from a memory buffer, same as reading from a single file
	/// @param memfile Memory file to be read
	/// @param errorlog Errorlog to store read errors
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	virtual bool Read(MemoryFile &memfile, ErrorLog &errorlog, IMemoryManager *pMemMgr = S_NULL);

	/// Write to file
	virtual bool Write(const Filename &filename, ErrorLog &errorlog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG)const;

	/// Write function used for a series that requires more than one file
	/// @see GetNumberOfFilesToCreate
	/// @param filenameBase The base file name, which defines the folder and base name.  Ex. filenameBase = "C:\MyFolder\dcsfile", files will have the name pattern "dcsfile0000", "dcsfile0001", etc.
	/// @param vErrorlogs An error log for the corresponding file
	/// @param nTransferSyntax Transfer syntax use when creating DICOS file(s)
	virtual bool Write(const Filename &filenameBase, Array1D< std::pair<Filename, ErrorLog> > &vErrorlogs, 
						const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG)const;

	/// Write to a memory file
	virtual bool Write(MemoryFile &memfile, ErrorLog &errorlog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG)const;

	/// Send data over TCP/IP connection. Handles opening and closing a socket connection and starting 
	/// and ending a DICOS session.
	/// @param nPort Host port
	/// @param dsIP Host IP address
	/// @param aeSrcAppName Name of source application (i.e. Name of application calling this function)
	/// @param aeDstAppName Name of destination application
	/// @param errorlog Error log
	/// @param dsUserID User ID. Leave empty if not used.
	/// @param dsPasscode Passcode. If used, user ID must be set.
	/// @return true/false
	virtual bool SendOverNetwork(const S_INT32 nPort, const DcsString &dsIP, const DcsApplicationEntity &aeSrcAppName, 
							const DcsApplicationEntity &aeDstAppName, ErrorLog &errorlog, 
							const DcsString &dsUserID = "", const DcsString dsPasscode = "");

	/// Send data over TCP/IP connection. The passed in client must already be connected to a host.
	/// Handles Starting and ending a DICOS session if a session is not already in progress.
	/// @param dclient Client already connected to host.
	/// @param errorlog Error log
	/// @return true/false
	virtual bool SendOverNetwork(SDICOS::Network::DcsClient &dclient, ErrorLog &errorlog);
	/// Send data over TCP/IP connection to multiple clients.
	/// Handles Starting and ending a DICOS sessions if not already in progress.
	/// @param clientManager Clients already connected to host.
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Returns number of clients that successfully sent DICOS data
	virtual S_UINT32 SendOverNetwork(SDICOS::Network::DcsClientManager &clientManager, ErrorLog &errorlog, std::vector< Network::DcsClientManager::ClientMetrics > &vSendTimes);

	/// Modality is set to enumAIT3D
	virtual MODALITY GetModality()const;

	/// Set criteria for selecting the OOI for inspection. Default value is 'ALL'.
	/// @param nSelectionCriteria	Options are RANDOM, BEVAIORAL and ALL
	/// @return true/false
	bool SetInspectionSelectionCriteria(const SDICOS::InspectionSelectionCriteria::INSPECTION_SELECTION_CRITERIA nSelectionCriteria);

	/// @see SetInspectionSelectionCriteria
	SDICOS::InspectionSelectionCriteria::INSPECTION_SELECTION_CRITERIA GetInspectionSelectionCriteria() const;

	/// Set the date and time that the content was created.
	/// @param strDate Defaults to an empty date
	/// @param strTime Defaults to an empty time
	/// @return true/false false if strDate or strTime are not valid
	bool SetContentDateAndTime(const DcsDate &strDate, const DcsTime &strTime);

	/// @see SetContentDateAndTime
	DcsDate GetContentDate()const;

	/// @see SetContentDateAndTime
	DcsTime GetContentTime()const;

	/// Set the date and time that the content was created.
	/// @param strDate Defaults to an empty date
	/// @param strTime Defaults to an empty time
	/// @return true/false false if strDate or strTime are not valid
	bool SetPixelDataCreationDateAndTime(const DcsDate &strDate, const DcsTime &strTime);

	/// @see SetPixelDataCreationDateAndTime
	DcsDate GetPixelDataCreationDate()const;

	/// @see SetPixelDataCreationDateAndTime
	DcsTime GetPixelDataCreationTime()const;

	/// The instance number identifies this AIT3D instance
	bool SetInstanceNumber(const S_INT32 nInstanceNumber);

	/// @see SetInstanceNumber
	S_INT32 GetInstanceNumber()const;
	
	/////////////////////////////////////
	// Pixel Intensity Relationship LUT Module
	//

	/// Indicate that Pixel Intensity Relationship LUT is written.
	/// @return true/false
	bool EnablePixelIntensityRelationshipLUT();

	/// Indicate that Pixel Intensity Relationship LUT is not written. 
	/// @return true/false
	bool DisablePixelIntensityRelationshipLUT();

	/// Is Pixel Intensity Relationship LUT enabled
	/// @return true/false
	bool IsPixelIntensityRelationshipLUTEnabled() const;

	/// Set the Image characteristics of the pixel/voxel data.
	/// @param pixelDataCharacteristics	Pixel data is 'ORIGINAL', 'DERIVED' or 'MIXED'. Defaults to 'ORIGINAL'.
	/// @param imageCharacteristics Image characteristic is enumContentAmplitude, enumContentComplexAmplitude or enumNoImageCharacteristic. Defaults to enumNoImageCharacteristic
	/// @param imageFlavor Image Flavor is 'PROJECTION' or 'VOLUME'. Defaults to 'VOLUME'
	/// @param pixelContrast Derived pixel contrast indicating how images have been combined. Defaults to 'NONE'
	/// @return true/false
	bool SetImageType(
		const SDICOS::AIT3DTypes::AIT3DImage::AIT3D_PIXEL_DATA_CHARACTERISTICS pixelDataCharacteristics,
		const SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS imageCharacteristics = SDICOS::AITImageType::enumNoImageCharacteristic,
		const SDICOS::AIT3DTypes::AIT3DImage::IMAGE_FLAVOR imageFlavor = SDICOS::AIT3DTypes::AIT3DImage::enumVolume,
		const SDICOS::AIT3DTypes::AIT3DImage::DERIVED_PIXEL_CONTRAST pixelContrast = SDICOS::AIT3DTypes::AIT3DImage::enumNone
	);

	/// @see SetImageType
	/// @return PIXEL_DATA_CHARACTERISTICS or enumUnknownPixelDataCharacteristics if no pixel data set
	SDICOS::AIT3DTypes::AIT3DImage::AIT3D_PIXEL_DATA_CHARACTERISTICS GetPixelDataCharacteristics() const;

	///@see SetImageType
	///@return AIT3D_IMAGE_CHARACTERISTICS or enumUnknownAIT3DImageCharacteristics if no pixel data is set
	SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS GetImageCharacteristics() const;

	/// @see SetImageType
	/// @return IMAGE_FLAVOR or enumUnknownImageFlavor is no pixel data is set
	SDICOS::AIT3DTypes::AIT3DImage::IMAGE_FLAVOR GetImageFlavor() const;

	/// @see SetImageType
	SDICOS::AIT3DTypes::AIT3DImage::DERIVED_PIXEL_CONTRAST GetDerivedPixelContrast() const;

	/// Set the AIT acquisition device type.
	/// @param deviceType Device type is 'PASSIVE_MMW', 'ACTIVE_MMW', or 'THZ'.
	/// @return true/false
	bool SetAITDeviceType(const SDICOS::AIT3DTypes::AIT3DImage::AIT_DEVICE_TYPE deviceType);

	/// @see SetAITDeviceType
	SDICOS::AIT3DTypes::AIT3DImage::AIT_DEVICE_TYPE GetAITDeviceType() const;

	/// Set Photometric Interpretation. Default value is MONOCHROME2
	/// @param photometricInterpretation Pixel data interpretation. Valid values are MONOCHROME1, MONOCHROME2, PALETTE COLOR.
	/// @return true/false false if Photometric Interpretation is not one of the valid values
	bool SetPhotometricInterpretation(const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION photometricInterpretation);

	/// @see SetPhotometricInterpretation
	ImagePixelMacro::PHOTOMETRIC_INTERPRETATION GetPhotometricInterpretation()const;

	/// Indicate if the image data contains a Burned In Annotation. Default is false;
	bool SetBurnedInAnnotation(const bool b);

	/// @see SetBurnedInAnnotation
	bool GetBurnedInAnnotation() const;

	/// Always returns 'IDENTITY'.
	SDICOS::GeneralImageModule::PRESENTATION_LUT_SHAPE GetPresentationLUTShape() const;

	/// Set date ad time that acquisition of data started
	/// @param date Date acquisition started. Defaults to an empty date.
	/// @param time Time acquisition started. Defaults to an empty date.
	/// @return true/false
	bool SetAcquisitionDateTime(const DcsDate& date, const DcsTime& time);

	/// @see SetAcquisitionDateTime
	bool GetAcquisitionDateTime(DcsDate& date, DcsTime& dcsTime) const;

	/// Time in seconds needed to complete acquisition. Defaults to 0.
	/// @param durationInSeconds Acquisition time in seconds. Values < 0 are not written to the DICOS file.
	/// @return true/false 
	bool SetAcquisitionDuration(const double durationInSeconds);

	/// @see SetAcquisitionDuration
	double GetAcquisitionDuration() const;

	/// The Acquisition Number identifies a single continuous 
	/// gathering of data over a period of time that resulted in the AIT3D image data.
	/// This parameter is optional and defaults to 0.
	/// @param acquisitionNumber Numeric identifier for the AIT3D object acquisition period.
	/// @return true/false
	bool SetAcquisitionNumber(const S_INT32 acquisitionNumber);

	/// @see SetAcquisitionNumber
	/// @return true/false false if no acquisition number was set.
	bool GetAcquisitionNumber(S_INT32& acquisitionNumber) const;

	/// Remove Acquisition Number so that it is not written to the DICOS file
	void DeleteAcquisitionNumber();
	
	/// Set Referenced Raw Data
	/// @param referencedRawData Scan, Series, and Sop Instance UIDs
	/// @return true/false
	bool SetReferencedRawData(const Array1D<SDICOS::HierarchicalReferences::ScanInstance>& referencedRawData);
	/// @see SetReferencedRawData
	bool GetReferencedRawData(Array1D<SDICOS::HierarchicalReferences::ScanInstance>& referencedRawData) const;
	/// @see SetReferencedRawData
	bool HasReferencedRawData() const;
	/// @see SetReferencedRawData
	void DeleteReferencedRawData();

	/// Set Referenced Image Evidence Sequence 
	/// @param referencedImageEvidenceData  Scan, Series, and Sop Instance UIDs
	/// @return true/false
	bool SetReferencedImageEvidence(const Array1D<SDICOS::HierarchicalReferences::ScanInstance>& referencedImageEvidenceData);
	/// @see SetReferencedImageEvidence
	bool GetReferencedImageEvidence(Array1D<SDICOS::HierarchicalReferences::ScanInstance>& referencedImageEvidenceData) const;
	/// @see SetReferencedImageEvidence
	bool HasReferencedImageEvidence() const;
	/// @see SetReferencedImageEvidence
	void DeleteReferencedImageEvidence();
	
	/// Set Source Image Evidence 
	/// @param sourceImageEvidenceData Scan, Series, and Sop Instance UIDs
	/// @return true/false
	bool SetSourceImageEvidence(const Array1D<SDICOS::HierarchicalReferences::ScanInstance>& sourceImageEvidenceData);
	/// @see SetSourceImageEvidence
	bool GetSourceImageEvidence(Array1D<SDICOS::HierarchicalReferences::ScanInstance>& sourceImageEvidenceData) const;
	/// @see SetSourceImageEvidence
	bool HasSourceImageEvidence() const;
	/// @see SetSourceImageEvidence
	void DeleteSourceImageEvidence();

	/// Set Referenced Presentation State
	/// @param referencedPresentationState Scan, Series, and Sop Instance UIDs
	/// @return true/false
	bool SetReferencedPresentationState(const Array1D<SDICOS::HierarchicalReferences::ScanInstance>& referencedPresentationState);
	/// @see SetReferencedPresentationState
	bool GetReferencedPresentationState(Array1D<SDICOS::HierarchicalReferences::ScanInstance>& referencedPresentationState) const;
	/// @see SetReferencedPresentationState
	bool HasReferencedPresentationState() const;
	/// @see SetReferencedPresentationState
	void DeleteReferencedPresentationState();

	/// Set optional human readable comments
	bool SetImageComments(const DcsLongText& imageComments);

	/// @see SetImageComments
	bool GetImageComments(DcsLongText& imageComments) const;

	/// Set supplemental palette color lookup tables.
	/// Required only if the Pixel Presentation value set using SetImageDescription() or SetPixelPresentation() is 'COLOR' or 'MIXED'.
	/// @param red LUT for red channel
	/// @param green LUT for green channel
	/// @param blue LUT for blue channel
	/// @return true/false
	bool SetPaletteColorLookupTable(
		const PaletteColorLookupTableRed& red, 
		const PaletteColorLookupTableGreen& green, 
		const PaletteColorLookupTableBlue& blue
	);

	/// @see SetPaletteColorLookupTable
	bool GetPaletteColorLookupTable(
		PaletteColorLookupTableRed& red, 
		PaletteColorLookupTableGreen& green, 
		PaletteColorLookupTableBlue& blue
	) const;

	/// Remove all existing sections and add the number of indicated sections
	/// Section indexing starts at 0.
	bool SetNumberOfSections(const S_UINT32 numSections);

	/// Get number of sections
	S_UINT32 GetNumberOfSections()const;

	/// Returns SOP Class UID based on the pixel data type. Returns empty string if pixel data is not allocated.
	/// Ex. If the image data is 64-bit unsigned or signed, then the return value is SOPClassUID::GetAIT3D_64Bit()
	virtual DcsUniqueIdentifier GetSopClassUID()const;

	/// Number of unique files that will be created from the volume sections.
	/// This can be less than GetNumberOfSections() if sections are merged because they are part of the same volume.
	S_UINT32 GetNumberOfFilesToCreate()const;

	/// Add a volume Section and return a handle to it.
	/// @param sectionId Unique identifier for the section in the AIT3D instance.
	///			The Section Id is not part of the DICOS file and is not restored when reading.
	/// @return Point to a SectionAIT or NULL
	SDICOS::SectionAIT* AddSection(const S_UINT32 sectionId);

	/// Add a volume Section and return a handle to it
	/// The Section Id is assigned a free value in the range [0,GetNumberOfSections()]
	SDICOS::SectionAIT* AddSection();

	/// Add a volume SectionAIT, allocate space for pixel data and return a pointer to it.
	SDICOS::SectionAIT* AddSection(const S_UINT32 nSectionId, const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth, const Volume::IMAGE_DATA_TYPE nDataType);

	/// Add a volume SectionAIT, allocate space for pixel data and return a pointer to it.
	SDICOS::SectionAIT* AddSection(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth, const Volume::IMAGE_DATA_TYPE nDataType);

	/// Add a new section with the given volume
	/// Set memory policy to OWNS_SLICES to transfer data ownership to the new section.
	/// Set memory policy to DOES_NOT_OWN_SLICES to add references of the volume to the new section. This means
	///	the section and the source volume share data, but the source is responsible to deleting the data.
	/// @return Returns added section 
	SectionAIT* AddSection(Array3DLarge<S_INT8> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_UINT8> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_INT16> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_UINT16> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_INT32> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_UINT32> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_INT64> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_UINT64> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<float> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Volume &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);


	/// Create a new Section using Array3DLarge iterators.
	/// Set memory policy to OWNS_SLICES to transfer data ownership to the new section.
	/// Set memory policy to DOES_NOT_OWN_SLICES to add references of the volume to the new section. This means
	///	the section and the source volume share data, but the source is responsible to deleting the data.
	/// @return Returns added section 
	SectionAIT* AddSection(Array3DLarge<S_INT8>::Iterator &itStart, const Array3DLarge<S_INT8>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_UINT8>::Iterator &itStart, const Array3DLarge<S_UINT8>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_INT16>::Iterator &itStart, const Array3DLarge<S_INT16>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_UINT16>::Iterator &itStart, const Array3DLarge<S_UINT16>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_INT32>::Iterator &itStart, const Array3DLarge<S_INT32>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_UINT32>::Iterator &itStart, const Array3DLarge<S_UINT32>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_INT64>::Iterator &itStart, const Array3DLarge<S_INT64>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<S_UINT64>::Iterator &itStart, const Array3DLarge<S_UINT64>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	SectionAIT* AddSection(Array3DLarge<float>::Iterator &itStart, const Array3DLarge<float>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);

private:
	/// Create a new Section using iterators similar to stl iterators
	template<typename ARRAY3D_TYPE, typename ITERATOR>
	SectionAIT* AddSection(ITERATOR itStart, const ITERATOR &itEnd,
						const Volume::IMAGE_DATA_TYPE nDataType,
						const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy,
						const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy,
						ARRAY3D_TYPE* (Volume::*pfnGetAs)());
public:

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	SectionAIT* AddSectionUnsigned8Bit(const ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_UINT8> >(itStart, itEnd, Volume::enumUnsigned8Bit, nMemPolicy, nFailurePolicy, &Volume::GetUnsigned8); }
	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	SectionAIT* AddSectionSigned8Bit(const ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_INT8> >(itStart, itEnd, Volume::enumSigned8Bit, nMemPolicy, nFailurePolicy, &Volume::GetSigned8); }

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	SectionAIT* AddSectionUnsigned16Bit(const ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_UINT16> >(itStart, itEnd, Volume::enumUnsigned16Bit, nMemPolicy, nFailurePolicy, &Volume::GetUnsigned16); }
	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	SectionAIT* AddSectionSigned16Bit(const ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_INT16> >(itStart, itEnd, Volume::enumSigned16Bit, nMemPolicy, nFailurePolicy, &Volume::GetSigned16); }

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	SectionAIT* AddSectionUnsigned32Bit(const ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_UINT32> >(itStart, itEnd, Volume::enumUnsigned32Bit, nMemPolicy, nFailurePolicy, &Volume::GetUnsigned32); }
	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	SectionAIT* AddSectionSigned32Bit(const ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_INT32> >(itStart, itEnd, Volume::enumSigned32Bit, nMemPolicy, nFailurePolicy, &Volume::GetSigned32); }

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	SectionAIT* AddSectionUnsigned64Bit(const ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_UINT64> >(itStart, itEnd, Volume::enumUnsigned64Bit, nMemPolicy, nFailurePolicy, &Volume::GetUnsigned64); }
	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	SectionAIT* AddSectionSigned64Bit(const ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_INT64> >(itStart, itEnd, Volume::enumSigned64Bit, nMemPolicy, nFailurePolicy, &Volume::GetSigned64); }

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	SectionAIT* AddSectionFloat(const ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<float> >(itStart, itEnd, Volume::enumFloat, nMemPolicy, nFailurePolicy, &Volume::GetFloat); }

	/// Delete a section by index.
	/// @param nSectionIndex Index in the range [0,GetNumberOfSections()-1]
	/// @return true/false false if nSectionIndex is out of range
	bool DeleteSection(const S_UINT32 nSectionIndex);

	/// Delete the indicated SectionAIT
	/// @param nSectionId Unique identifier for the section in the AIT3D instance
	/// @return true/false false if the section did not exist
	bool DeleteSectionById(const S_UINT32 nSectionId);

	/// If the indicated section exists in the AIT3D object remove it
	/// @param pSection 
	/// @return true/falsle false if the section did not exist
	bool DeleteSection(const SectionAIT* pSection);

	/// Delete all sections
	void DeleteAllSections();

	/// Get a pointer to the indicated SectionAIT
	/// @param sectionId Unique identifier for the section in the AIT3D instance
	/// @return Point to a SectionAIT or NULL is add failed
	SDICOS::SectionAIT* GetSection(const S_UINT32 sectionId);

	/// @see GetSection
	const SDICOS::SectionAIT* GetSection(const S_UINT32 sectionId) const;

	/// Get a section using an index in the range [0,GetNumberOfSections()-1]
	/// This corresponds to the SectionAIT order returned by iterating over all sections.
	SDICOS::SectionAIT* GetSectionByIndex(const S_UINT32 sectionIndex);

	/// @see GetSectionByIndex
	const SDICOS::SectionAIT* GetSectionByIndex(const S_UINT32 sectionIndex) const;

	/// Insert a new section at the index indicated by nSection
	SectionAIT* InsertSection(const S_UINT32 nSection);

	/// Ask if the given section is in this AIT3D Object's Sections
	bool Contains(const SectionAIT *) const;

	///
	/// \class Iterator
	/// \brief An iterator over all of the Sections in the AIT3D object
	///
	/// Iterate over all Section objects added to the volume.
	///
	class Iterator
	{
		public:
			/// Default constructor
			Iterator();

			/// Copy Constructor
			Iterator(const Iterator&);

			/// Construct with the indicated AIT3D Object
			/// ITERATION_DIRECTION_BACKWARD is not supported
			Iterator(const AIT3D& ait, const ITERATION_DIRECTION dir = ITERATION_DIRECTION_FORWARD);

			/// Destructor
			~Iterator();

			/// Assignment operator
			Iterator& operator=(const Iterator&);

			/// Comparison operator
			bool operator==(const Iterator&) const;

			/// Comparison operator
			bool operator!=(const Iterator&) const;

			/// Preincrement operator
			Iterator& operator++();

			/// Predecrement operator
			Iterator& operator--();

			/// Dereference operator
			SectionAIT* operator*();

			/// Const Dereference Operator
			const SectionAIT* operator*() const;

			/// Integer index to access the section using GetSection())
			/// @return Index to access the section or INVALID_SECTION_INDEX
			SDICOS::S_UINT32 GetIndex() const;

			static const S_UINT32 INVALID_SECTION_INDEX = 0xFFFFFFFF;
		private:
			class Impl;
			Impl* m_pImpl; ///< Internal implementation

			Impl* GetImpl();
			const Impl* GetImpl() const;
	};

	/// Get an Iterator that references the first Section in the AIT3D Series
	Iterator Begin() const;

	/// Get an Iterator that references the end of the Sections in the AIT3D Series
	Iterator End() const;

protected:

	/// Override to allocate a derived module-level API object.
	/// By default allocates AIT3DModule.  This module is internally
	/// used for reading, writing, and networking.
	/// @return Dynamically allocated module-level API object
	virtual AIT3DModule* AllocateModule()const;

	/// Override this function to set attributes in the SDICOS::AIT3DModule object that are not set with AIT3D
	/// WriteDerived_internal is called by the AIT3D::Write() methods before attributes in the AIT3D class are written.
	/// If the derived class wishes to further restrict values 
	/// @param ait AIT3D object to set new values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors writing data
	virtual bool WriteDerived_internal(SDICOS::AIT3DModule& ait, ErrorLog&errorlog)const;

	/// Override this function to retrieve attributes from the SDICOS::AIT3DModule object that are not retrieved by AIT3D
	/// ReadDerived_internal is called by AIT3D::Read() methods before attributes in the AIT3D class are read.
	/// @param ait AIT3D object to retrieve read values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors reading data
	virtual bool ReadDerived_internal(const SDICOS::AIT3DModule& ait, ErrorLog& errorlog);

	class ImplAIT3D;

	ImplAIT3D* GetImpl(); ///< Internal implementation
	const ImplAIT3D* GetImpl() const;

private:
	ImplAIT3D * m_pImplAIT3D;

	/// Initialize the given AIT3D object with the data in the AIT3D object
	/// in preparation for writing to file, network, membuffer etc.
	bool WriteToAIT3D_internal(AIT3DModule& pAIT, ErrorLog &errorlog) const;

	/// Initialize the AIT3DSeries Base from the given AIT3D object
	bool ReadFromAIT3D_internal(const AIT3DModule& pAIT, ErrorLog& errorlog);
};

template<typename ARRAY3D_TYPE, typename ITERATOR>
SectionAIT* AIT3D::AddSection(ITERATOR itStart, const ITERATOR &itEnd, 
					const Volume::IMAGE_DATA_TYPE nDataType,
					const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy,
					const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy,
					ARRAY3D_TYPE* (Volume::*pfnGetAs)())
{
	SectionAIT *pNewSection(AddSection());

	if (S_NULL == pNewSection)
		return S_NULL;

	Volume &volume = pNewSection->GetPixelData();

	volume.SetMemoryPolicy(nMemPolicy);

	if (!volume.Allocate(nDataType))
	{
		volume.FreeMemory();
		return S_NULL;
	}

	ARRAY3D_TYPE* pVol((volume.*pfnGetAs)());

	for (; itStart != itEnd; ++itStart)
		pVol->AddSlice(*itStart, nFailurePolicy);

	return pNewSection;
}

} // SDICOS

#endif	/* _STRATOVAN_DICOS_SDCS_TEMPLATE_AIT3D_H_ */

