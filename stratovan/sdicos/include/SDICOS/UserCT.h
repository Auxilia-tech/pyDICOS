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
#ifndef _STRATOVAN_DICOS_TEMPLATE_CLASSES_CT_H_
#define _STRATOVAN_DICOS_TEMPLATE_CLASSES_CT_H_

#include "SDICOS/ModuleCT.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/Point3D.h"
#include "SDICOS/TemplateCommon.h"
#include "SDICOS/TemplateBase.h"
#include "SDICOS/ClientManager.h"
#include "SDICOS/MemoryPolicy.h"
#include "SDICOS/AcquisitionContextUser.h"
#include "SDICOS/ImageBaseUser.h"
#include "SDICOS/XRayEquipmentUser.h"
#include "SDICOS/FrameOfReferenceUser.h"
#include <map>

namespace SDICOS
{

///
/// \class Section
/// \brief A section of a CT volume
/// A CT Volume is composed of one or more Sections.
/// The SDICOS::TemplateCT::CT object contains methods for manipulating Sections.
/// The volume data is represented using the SDICOS::Volume class.
///
class Section : public SectionCommon
{
public:
	/// Constructor
	Section();
		
	/// Construct with a unique identifier
	Section(const SDICOS::S_UINT32 sectionId);
		
	/// Copy constructor
	Section(const Section &sec);
	/// Destructor
	virtual ~Section();

	/// Copy operator
	Section& operator=(const Section &sec);
	/// Comparison operator
	bool operator==(const Section &sec)const;
	/// Comparison operator
	bool operator!=(const Section &sec)const;

	/// Reset to default values
	virtual void FreeMemory();

	////////////////////////////
	//  Functional Groups
	
	/// Image Pixel Presentation
	/// Default set to CommonImageDescription::enumPP_Monochrome
	void SetImagePixelPresentation(const CommonImageDescription::PIXEL_PRESENTATION nPresentation);
	/// @see SetImagePixelPresentation
	CommonImageDescription::PIXEL_PRESENTATION GetImagePixelPresentation()const;

	/// Image Volume Based Calculation Technique
	/// Default set to CommonImageDescription::enumVC_None
	void SetImageVolumeBasedCalculationTechnique(const CommonImageDescription::VOLUME_BASED_CALCULATION_TECHNIQUE nTechnique);
	/// @see SetImageVolumeBasedCalculationTechnique
	CommonImageDescription::VOLUME_BASED_CALCULATION_TECHNIQUE GetImageVolumeBasedCalculationTechnique()const;

	/// Image Volumetric Properties
	/// Default set to CommonImageDescription::enumVP_Volume
	void SetImageVolumetricProperties(const CommonImageDescription::VOLUMETRIC_PROPERTIES nProperties);
	/// @see SetImageVolumetricProperties
	CommonImageDescription::VOLUMETRIC_PROPERTIES GetImageVolumetricProperties()const;
	
	/// Slope to convert data to units defined by rescale type
	/// Default value set to 1.
	void SetRescaleSlope(const float fSlope);
	/// @see SetRescaleSlope
	float GetRescaleSlope()const;

	/// Intercept to convert data to units defined by rescale type
	/// Default value set to 0.
	void SetRescaleIntercept(const float fIntercept);
	/// @see SetRescaleIntercept
	float GetRescaleIntercept()const;

	/// The units used by the pixel data after applying the rescale slope and intercept
	/// Default value set to "unknown".
	void SetRescaleType(const DcsLongString &strType);
	/// @see SetRescaleType
	const DcsLongString& GetRescaleType()const;

	/// Filter material - Only one material
	void SetFilterMaterial(const CTTypes::CTXRayDetails::FILTER_MATERIAL nFilterMaterial);
	/// @see SetFilterMaterial
	CTTypes::CTXRayDetails::FILTER_MATERIAL GetFilterMaterial()const;
	/// Filter materials - Multiple materials
	void SetFilterMaterials(const Array1D<CTTypes::CTXRayDetails::FILTER_MATERIAL> &vFilterMaterial);
	/// @see SetFilterMaterial
	const Array1D<CTTypes::CTXRayDetails::FILTER_MATERIAL>& GetFilterMaterials()const;
	
	/// Filter type
	/// Default set to CTTypes::CTXRayDetails::enumNone
	void SetFilterType(const CTTypes::CTXRayDetails::FILTER_TYPE nFilterType);
	/// @see SetFilterType
	CTTypes::CTXRayDetails::FILTER_TYPE GetFilterType()const;

	/// Focal spot size in mm used by machine
	/// Default value set to 0.
	void SetFocalSpotSizeInMM(const float fNominalDimension);
	/// @see SetFocalSpotSizeInMM
	float GetFocalSpotSize()const;
	/// @see SetFocalSpotSizeInMM
	bool HasOneFocalSpotSize()const;

	/// Focal spot sizes in mm used by machine.
	void SetFocalSpotSizesInMM(const float fSmallSize, const float fLargeSize);
	/// @see SetFocalSpotSizesInMM
	void GetFocalSpotSize(float &fSmallSize, float &fLargeSize)const;
	/// @see SetFocalSpotSizesInMM
	float GetFocalSpotSmallSize()const;
	/// @see SetFocalSpotSizesInMM
	float GetFocalSpotLargeSize()const;
	/// @see SetFocalSpotSizesInMM
	bool HasTwoFocalSpotSizes()const;

	/// KVP (Peak Kilo Voltage) used by machine
	/// Default value set to 0.
	void SetKVP(const float fKVP);
	/// @see SetKVP
	float GetKVP()const;

	/// Applies the rescale slope and intercept to the image data: Rescaled = Data * Slope + Intercept.  
	/// Resets slope to 1 and intercept to 0.
	void ApplyRescaleToImage();
protected:
	class SectionImpl;
	SectionImpl	*m_pSectionImpl;
};

///
/// \class CT
/// \brief Represents a single CT scan with original pixel data.
///
/// This class abstracts away the hierarchy of the DICOS 
/// specification and provides an API that contains methods for setting all of
/// the attributes needed for a DICOS CT object.
///
/// It represents a single Series in a Scan in an Object of Inspection (OOI) with original pixel data.
/// Required and optional attributes not explicitly set using the API methods are set to default values.
///
/// The volume data for a single CT scan is contained in one or more volumes called Sections
/// represented using the SDICOS::Section class.
/// Sections are independently allocated.
/// 
/// The two types of Sections are called related and independent.
/// Related Sections:
///	For CT Data, a larger volume can be broken down into smaller sections along the Z-direction (Depth).
///	These sections must shared the same Width(W), Height(H).
///	For example a 512x512x512 (WxHxD) volume can be broken down into three Sections
///	of dimensions 512x512x100, 512x512x200 and 512x512x212.
///	The data can be set for these Sections independently, but when the CT data is written to a file
///	the related sections are combined into a single volume and the original Sections are not
///	restored when read.
///
/// Independent Sections:
///	Independent sections cannot be combined to form a larger volume. These are
///	Sections that have different dimensions, spacing or location.
///	Independent Sections are saved to separate DICOS files.
///
///	For example, for a particular OOI and Scan, a Series could have a normal
///	resolution CT volume for the whole OOI and a small higher-resolution volume
///	for a sub-volume that is of particular interest.
///	These are stored as independent sections.
///
class CT : public IODCommon,
		   public ScanCommon,
		   public AcquisitionContextUser,
		   public XRayEquipmentUser,
		   public ImageCommonUser,
		   public FrameOfReferenceUser // See FrameOfReferenceUser.h Adds FrameOfReference Module Attributes to the SDICOS::CT User Level API.
{
public:
	/// Constructor
	CT();
	/// Construct with Object Type, Image Type and Photometric Interpretation
	CT(
		const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE nOOIType,
		const CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS nOOI,
		const CTTypes::CTImage::IMAGE_FLAVOR nFlavor = CTTypes::CTImage::enumVolume,
		const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI = ImagePixelMacro::enumMonochrome2
	);
		
	/// Copy constructor
	CT(const CT &ct);
	/// Destructor
	virtual ~CT();

	/// Reset to default values.
	virtual void FreeMemory();

	/// Copy operator
	CT& operator=(const CT &ct);
	/// Comparison operator
	bool operator==(const CT &ct)const;
	/// Comparison operator
	bool operator!=(const CT &ct)const;

	/// Initialize with Object Type, Image Type and Photometric Interpretation
	/// All attributes are set to valid defaults according to the DICOS standard.
	/// @return true/false
	bool Initialize(const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE nOOIType,
					const CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS nOOI,
					const CTTypes::CTImage::IMAGE_FLAVOR nFlavor = CTTypes::CTImage::enumVolume,
					const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI = ImagePixelMacro::enumMonochrome2);

	/// Initialize with a vector of CT objects belonging to the same series
	/// @param vSeries Series of CT's
	/// @param errorlog Error Log
	/// @param bMoveData	true = Move data (such as pixel data), instead of copying, from vSeries
	///						false = Copy data from vSeries
	bool Initialize(std::vector<CTModule*> &vSeries, ErrorLog &errorlog, const bool bMoveData);

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
	virtual bool Read(const Filename &filename, ErrorLog& errorLog, IMemoryManager *pMemMgr = S_NULL);
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
	virtual bool SendOverNetwork(const S_INT32 nPort, const DcsString &dsIP, const DcsApplicationEntity &aeSrcAppName, 
							const DcsApplicationEntity &aeDstAppName, ErrorLog &errorlog, 
							const DcsString &dsUserID = "", const DcsString dsPasscode = "");

	/// Send data over TCP/IP connection. The passed in client must already be connected to a host.
	/// Handles Starting and ending a DICOS session if a session is not already in progress.
	/// @param dclient Client already connected to host.
	/// @param errorlog Error log
	virtual bool SendOverNetwork(SDICOS::Network::DcsClient &dclient, ErrorLog &errorlog);
	/// Send data over TCP/IP connection to multiple clients.
	/// Handles Starting and ending a DICOS sessions if not already in progress.
	/// @param clientManager Clients already connected to host.
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Returns number of clients that successfully sent DICOS data
	virtual S_UINT32 SendOverNetwork(SDICOS::Network::DcsClientManager &clientManager, ErrorLog &errorlog, std::vector< Network::DcsClientManager::ClientMetrics > &vSendTimes);
	

	/// Returns enumCT
	virtual MODALITY GetModality()const;
	
	/// Returns the number of files required to create for writing.
	/// The number depends on the dimensions of the volume in each section.
	/// If all of the sections' volumes have equal width and height, then a single file
	/// is created. If one section contains different width or height, then 2 files are
	/// created.
	S_UINT32 GetNumberOfFilesToCreate()const;

	/////////////////
	//  Image

	/// Image Acquisition Date and Time
	bool SetImageAcquisitionDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetImageAcquisitionDateAndTime
	const DcsDate& GetImageAcquisitionDate()const;
	/// @see SetImageAcquisitionDateAndTime
	const DcsTime& GetImageAcquisitionTime()const;

	/// Flag the image as having a burned in annotation
	void SetBurnedInAnnotation(const bool bUsesAnnotation);
	/// @see SetBurnedInAnnotation
	bool HasBurnedInAnnotation()const;

	/// Photometric Interpretation
	bool SetPhotometricInterpretation(const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI);
	/// @see SetPhotometricInterpretation
	ImagePixelMacro::PHOTOMETRIC_INTERPRETATION GetPhotometricInterpretation()const;

	/// Image Type
	bool SetImageType(	const CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS nOOI, 
						const CTTypes::CTImage::IMAGE_FLAVOR nFlavor = CTTypes::CTImage::enumVolume);
	/// @see SetImageType
	void GetImageType(	CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS &nOOI, 
						CTTypes::CTImage::IMAGE_FLAVOR &nFlavor)const; 
	/// @see SetImageType
	CTTypes::CTImage::OOI_IMAGE_CHARACTERISTICS GetOOIImageCharacteristics()const;
	/// @see SetImageType
	CTTypes::CTImage::IMAGE_FLAVOR GetImageFlavor()const;

	/// Set the Image Data Type to SDI (Sensor Data Interface) 
	void SetSDI();
	/// @see SetSDI
	bool IsSDI()const;

	/// Set the Image Data Type to CDI (Constructed/Corrected Data Interface)
	void SetCDI();
	/// @see SetCDI
	bool IsCDI()const;

	/// Set the Image Data Type to Standard (default)
	void SetStandard();
	/// @see SetStandard
	bool IsStandard()const;


	/// Image Acquisition Duration in seconds
	/// @return false if duration < 0
	bool SetImageAcquisitionDuration(const double nAcquisitionDuration);
	/// @see SetImageAcquisitionDuration
	double GetImageAcquisitionDuration()const;

	///////////////////////////////////////
	// Multiframe Functional Groups

	/// Content Date and Time
	bool SetContentDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetContentDateAndTime
	const DcsDate& GetContentDate()const;
	/// @see SetContentDateAndTime
	const DcsTime& GetContentTime()const;

	/// Instance Number
	/// Default set to 0
	void SetInstanceNumber(const S_INT32 nInstanceNumber);
	/// @see SetInstanceNumber
	const S_INT32& GetInstanceNumber()const;

	////////////////////
	//  Sections

	/// Set number of sections
	void SetNumberOfSections(const S_UINT32 nNum);
		
	/// Get number of sections
	S_UINT32 GetNumberOfSections()const;

	/// Returns SOP Class UID based on the pixel data type. Returns empty string if pixel data is not allocated.
	/// Ex. If the image data is 64-bit unsigned or signed, then the return value is SOPClassUID::GetCT_64Bit()
	virtual DcsUniqueIdentifier GetSopClassUID()const;
		
	/// Add a new section
	/// @return Returns added section 
	Section* AddSection();
		
	/// Add a new section with an allocated pixel data volume
	/// @return Returns added section 
	Section* AddSection(const S_UINT32 nWidth, const S_UINT32 nHeight, const S_UINT32 nDepth, const Volume::IMAGE_DATA_TYPE nDataType);

	/// Add a new section with the given volume
	/// Set memory policy to OWNS_SLICES to transfer data ownership to the new section.
	/// Set memory policy to DOES_NOT_OWN_SLICES to add references of the volume to the new section. This means
	///	the section and the source volume share data, but the source is responsible to deleting the data.
	/// @return Returns added section 
	Section* AddSection(Array3DLarge<S_INT8> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_UINT8> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_INT16> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_UINT16> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_INT32> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_UINT32> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_INT64> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_UINT64> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<float> &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Volume &vol, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);


	/// Create a new Section using Array3DLarge iterators.
	/// Set memory policy to OWNS_SLICES to transfer data ownership to the new section.
	/// Set memory policy to DOES_NOT_OWN_SLICES to add references of the volume to the new section. This means
	///	the section and the source volume share data, but the source is responsible to deleting the data.
	/// @return Returns added section 
	Section* AddSection(Array3DLarge<S_INT8>::Iterator &itStart, const Array3DLarge<S_INT8>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_UINT8>::Iterator &itStart, const Array3DLarge<S_UINT8>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_INT16>::Iterator &itStart, const Array3DLarge<S_INT16>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_UINT16>::Iterator &itStart, const Array3DLarge<S_UINT16>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_INT32>::Iterator &itStart, const Array3DLarge<S_INT32>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_UINT32>::Iterator &itStart, const Array3DLarge<S_UINT32>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_INT64>::Iterator &itStart, const Array3DLarge<S_INT64>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<S_UINT64>::Iterator &itStart, const Array3DLarge<S_UINT64>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	/// @see AddSection(Array3DLarge<S_INT8>::Iterator&, const Array3DLarge<S_UINT8>::Iterator&, const MemoryPolicy::VOLUME_MEMORY_POLICY, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY)
	Section* AddSection(Array3DLarge<float>::Iterator &itStart, const Array3DLarge<float>::Iterator& itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT);
	
private:
	/// Create a new Section using iterators similar to stl iterators
	template<typename ARRAY3D_TYPE, typename ITERATOR>
	Section* AddSection(ITERATOR itStart, const ITERATOR &itEnd, 
						const Volume::IMAGE_DATA_TYPE nDataType,
						const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy,
						const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy,
						ARRAY3D_TYPE* (Volume::*pfnGetAs)());
public:

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	Section* AddSectionUnsigned8Bit(ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_UINT8> >(itStart, itEnd, Volume::enumUnsigned8Bit, nMemPolicy, nFailurePolicy, &Volume::GetUnsigned8); }
	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	Section* AddSectionSigned8Bit(ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_INT8> >(itStart, itEnd, Volume::enumSigned8Bit, nMemPolicy, nFailurePolicy, &Volume::GetSigned8); }

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	Section* AddSectionUnsigned16Bit(ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_UINT16> >(itStart, itEnd, Volume::enumUnsigned16Bit, nMemPolicy, nFailurePolicy, &Volume::GetUnsigned16); }
	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	Section* AddSectionSigned16Bit(ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_INT16> >(itStart, itEnd, Volume::enumSigned16Bit, nMemPolicy, nFailurePolicy, &Volume::GetSigned16); }

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	Section* AddSectionUnsigned32Bit(ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_UINT32> >(itStart, itEnd, Volume::enumUnsigned32Bit, nMemPolicy, nFailurePolicy, &Volume::GetUnsigned32); }
	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	Section* AddSectionSigned32Bit(ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_INT32> >(itStart, itEnd, Volume::enumSigned32Bit, nMemPolicy, nFailurePolicy, &Volume::GetSigned32); }

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	Section* AddSectionUnsigned64Bit(ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_UINT64> >(itStart, itEnd, Volume::enumUnsigned64Bit, nMemPolicy, nFailurePolicy, &Volume::GetUnsigned64); }
	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	Section* AddSectionSigned64Bit(ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<S_INT64> >(itStart, itEnd, Volume::enumSigned64Bit, nMemPolicy, nFailurePolicy, &Volume::GetSigned64); }

	/// Create a new Section using iterators similar to stl iterators
	template<typename ITERATOR>
	Section* AddSectionFloat(ITERATOR &itStart, const ITERATOR &itEnd, const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy = MemoryPolicy::OWNS_SLICES, const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy = Array3DLargeBase::EARLY_OUT)
	{ return AddSection< Array3DLarge<float> >(itStart, itEnd, Volume::enumFloat, nMemPolicy, nFailurePolicy, &Volume::GetFloat); }

	/// Insert a new section at the given index
	Section* InsertSection(const S_UINT32 nSectionIndex);
		
	/// Delete a section by index.
	bool DeleteSection(const S_UINT32 nSectionIndex);
		
	/// If the indicated section exists in the CT object remove it
	bool DeleteSection(const Section* pSection);

	/// Delete all sections
	void DeleteAllSections();
		
	/// Get a section by Index
	Section* GetSectionByIndex(const S_UINT32 nSectionIndex);
		
	/// Get a section
	const Section* GetSectionByIndex(const S_UINT32 nSectionIndex)const;

	/// Ask if the given section is in this CT Object's Sections
	bool Contains(const Section *) const;
		
	///
	/// \class Iterator
	/// \brief Iterate over all of the Sections in the CT object
	///
	class Iterator
	{
		public:
			/// Default constructor
			Iterator();

			/// Copy Constructor
			Iterator(const Iterator&);

			/// Construct with the indicated CT Object
			/// ITERATION_DIRECTION_BACKWARD is not supported
			Iterator(const CT& ct, const ITERATION_DIRECTION dir = ITERATION_DIRECTION_FORWARD);

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
			Section* operator*();

			/// Const Dereference Operator
			const Section* operator*() const;

			/// Integer index to access the section using GetSection())
			/// @return Index to access the section or INVALID_SECTION_INDEX
			S_UINT32 GetIndex() const;

			static const S_UINT32 INVALID_SECTION_INDEX = 0xFFFFFFFF;
		private:
			class Impl;
			Impl* m_pImpl; ///< Internal implementation

			Impl* GetImpl();
			const Impl* GetImpl() const;
	};

	/// Get an Iterator that references the first Section in the CT Series
	Iterator Begin() const;
		
	/// Get an Iterator that references the end of the Sections in the CT Series
	Iterator End() const;

protected:

	/// Override to allocate a derived module-level API object.
	/// By default allocates CTModule.  This module is internally
	/// used for reading, writing, and networking.
	/// @return Dynamically allocated module-level API object
	virtual CTModule* AllocateModule()const;

	/// Override this function to set attributes in the SDICOS::CTModule object that are not
	/// set with CT
	/// @param ct CT object to set new values
	/// @param errorlog Error log
	virtual bool WriteDerived_internal(SDICOS::CTModule &ct, ErrorLog &errorlog)const;
	/// Override this function to retrieve attributes from the SDICOS::CTModule object that are not
	/// retrieved by CT
	/// @param ct CT object to retrieve read values
	/// @param errorlog Error log
	virtual bool ReadDerived_internal(const SDICOS::CTModule &ct, ErrorLog &errorlog);

private:
	class CTImpl;
	CTImpl *m_pCTImpl;

};

template<typename ARRAY3D_TYPE, typename ITERATOR>
Section* CT::AddSection(ITERATOR itStart, const ITERATOR &itEnd, 
					const Volume::IMAGE_DATA_TYPE nDataType,
					const MemoryPolicy::VOLUME_MEMORY_POLICY nMemPolicy,
					const Array3DLargeBase::ADD_SLICE_FAILURE_POLICY nFailurePolicy,
					ARRAY3D_TYPE* (Volume::*pfnGetAs)())
{
	Section *pNewSection(AddSection());

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

}//namespace SDICOS

#endif
