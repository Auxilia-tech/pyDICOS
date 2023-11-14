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
#ifndef _STRATOVAN_DICOS_SDCS_TEMPLATE_AIT2D_H_
#define	_STRATOVAN_DICOS_SDCS_TEMPLATE_AIT2D_H_

#include "SDICOS/DicosFile.h"
#include "SDICOS/SopClassUID.h"
#include "SDICOS/TemplateBase.h"
#include "SDICOS/TemplateCommon.h"
#include "SDICOS/ModuleAIT2D.h"
#include "SDICOS/Image2D.h"
#include "SDICOS/PixelMeasurementUser.h"
#include "SDICOS/PlanePositionUser.h"
#include "SDICOS/PlaneOrientationAITUser.h"
#include "SDICOS/RealWorldValueMappingUser.h"
#include "SDICOS/ImageBaseUser.h"
#include "SDICOS/ImageHistogramUser.h"
#include "SDICOS/FrameOfReferenceUser.h"
#include "SDICOS/AcquisitionContextUser.h"

namespace SDICOS 
{

///
/// \class AIT2D
/// \brief AIT2D represents a single AIT 2D scan. The class is not thread safe.
///
/// The AIT2D class is not thread safe.
/// This class abstracts away the hierarchy of the DICOS specification
/// and provides an API that contains methods for setting the attributes needed for a DICOS AIT2D object.
/// This class implements an AIT2D IOD that contains a single image scan.
/// The image consists of unsigned 16/32/64-bit integer or float data and an optional 16-bit LUT if the IOD is for presentation.
///
/// Default values for various DICOS attributes:
///		Presentation Intent Type:	'FOR PROCESSING'
///		Image Characteristics:		'PRIMARY'
/// 
class AIT2D : public IODCommon,
			  public ScanCommon,
			  public ImageCommonUser,
			  public PixelMeasurementUser,
			  public PlanePositionUser,
			  public AitPlaneOrientationUser,
			  public RealWorldValueMappingSequenceUser,
			  public ImageHistogramUser,
			  public FrameOfReferenceUser, // An optional module. See AIT2D::EnableFrameOfReference() and AIT2D::DisableFrameOfReference()
			  public AcquisitionContextUser
{
public:
	/// Default constructor
	AIT2D();
		
	/// Construct AIT2D object with Object of Inspection Type, AIT Device Type, presentation intent type and photometric interpretation
	AIT2D(
		const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE nOOIType,
		const AIT2DTypes::AIT2DImage::AIT_DEVICE_TYPE nDeviceType = AIT2DTypes::AIT2DImage::enumActiveMillimeterWave,
		const AIT2DTypes::AIT2DSeries::PRESENTATION_INTENT_TYPE presentationIntentType = AIT2DTypes::AIT2DSeries::enumProcessing,
		const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI = ImagePixelMacro::enumMonochrome2
	);
	
	/// Construct AIT2D object with Object of Inspection Gender, AIT Device Type, presentation intent type and photometric interpretation
	/// OOI Type is set to enumTyoePerson
	AIT2D(
		const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_GENDER nOOIGender,
		const AIT2DTypes::AIT2DImage::AIT_DEVICE_TYPE nDeviceType = AIT2DTypes::AIT2DImage::enumActiveMillimeterWave,
		const AIT2DTypes::AIT2DSeries::PRESENTATION_INTENT_TYPE presentationIntentType = AIT2DTypes::AIT2DSeries::enumProcessing,
		const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI = ImagePixelMacro::enumMonochrome2
	);
		
	/// Copy constructor
	AIT2D(const AIT2D&);
		
	/// Destructor
	virtual ~AIT2D();
	
	/// Assignment operator
	AIT2D& operator=(const AIT2D&);
		
	/// Comparison operator
	bool operator==(const AIT2D&) const;
		
	/// Comparison operator
	bool operator!=(const AIT2D& ) const;
	
	/// Initialize with OOI Type. presentation intent type and photometric interpretation.
	/// All other attributes are set to valid DICOS defaults.
	/// @param nOOIType					Object of Inspection Type. What kind of object is this?
	/// @param nDeviceType				What kind of AIT device is the data from.
	/// @param presentationIntentType	Is the object meant for further processing(default) or immediate presentation.
	/// @param nPI						Photometric Interpretation. Supported values are enumMonochrome1, enumMonochrome2(default) and enumPaletteColor.
	/// @return true/false	false if supplied parameters are an invalid combination
	bool Initialize(
		const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE nOOIType,
		const AIT2DTypes::AIT2DImage::AIT_DEVICE_TYPE nDeviceType = AIT2DTypes::AIT2DImage::enumActiveMillimeterWave,
		const AIT2DTypes::AIT2DSeries::PRESENTATION_INTENT_TYPE presentationIntentType = AIT2DTypes::AIT2DSeries::enumProcessing,
		const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI = ImagePixelMacro::enumMonochrome2
	);

	/// Initialize with an AIT2D object
	/// @param ait AIT2D to initialize from
	/// @param errorlog Error Log
	/// @param bMoveData	true = Move data (such as pixel data), instead of copying, from vSeries
	///						false = Copy data from vSeries
	bool Initialize(AIT2DModule &ait, ErrorLog &errorlog, const bool bMoveData);
		
	/// Free Allocated memory
	void FreeMemory();

	/// Convenience method to read a series that contains a single file
	/// @param filename Filename for the file to be read
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
	/// @param vSendTimes vector of ClientMetrics to store send time metrics
	/// @return Returns number of clients that successfully sent DICOS data
	virtual S_UINT32 SendOverNetwork(SDICOS::Network::DcsClientManager &clientManager, ErrorLog &errorlog, std::vector< Network::DcsClientManager::ClientMetrics > &vSendTimes);

	/// Modality is set to enumAIT2D
	virtual MODALITY GetModality()const;
		
	/// Set criteria for selecting the OOI for inspection. Default value is 'RANDOM'.
	/// @param nSelectionCriteria	Options are RANDOM, BEVAIORAL, ALL
	/// @return true/false
	bool SetInspectionSelectionCriteria(const SDICOS::InspectionSelectionCriteria::INSPECTION_SELECTION_CRITERIA nSelectionCriteria);
	
	/// Set Presentation Intent Type.
	/// @param nIntentType	Presentation Intent Type. Options are 'FOR PRESENTATION' and 'FOR PROCESSING'
	/// @return true/false
	bool SetPresentationIntentType(SDICOS::AIT2DTypes::AIT2DSeries::PRESENTATION_INTENT_TYPE nIntentType);
	/// @see SetPresentationIntentType
	AIT2DTypes::AIT2DSeries::PRESENTATION_INTENT_TYPE GetPresentationIntentType() const;

	// Frame of Reference Module (optional)
	//

	/// Enable Frame of Reference attributes to be written during Write()
	/// FrameOfReferenceUser attributes are disabled by default
	void EnableFrameOfReference();

	/// Frame Of Reference attributes will not be written during Write()
	void DisableFrameOfReference();

	/// @see EnableFrameOfReference
	/// @return true/false
	bool IsFrameOfReferenceEnabled() const;


	// General Image Module attributes
	//

	/// Set Instance Number to identify this DX Series object.
	/// @param nInstanceNumber A number that identifies this image. Default value is 0.
	bool SetInstanceNumber(const S_INT32 nInstanceNumber);
	/// @see SetInstanceNumber
	S_INT32 GetInstanceNumber()const;
	
	/// Set Content Date and Time. Default value is object creation date and time.
	/// @param strDate Date the image pixel creation started. Default value is DcsDate::Today()
	/// @param strTime Time the image pixel creation started. Default value is DcsTime::Now()
	/// @return true/false false if strDate or strTime is not valid
	bool SetContentDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetContentDateAndTime
	const DcsDate& GetContentDate()const;
	/// @see SetContentDateAndTime
	const DcsTime& GetContentTime()const;
	
	/// Flag the image as having a burned in annotation. Default value is false.
	bool SetBurnedInAnnotation(const bool bUsesAnnotation);
	/// @see SetBurnedInAnnotation
	bool HasBurnedInAnnotation()const;
	
	// AIT Image Module attributes
	//

	/// Set the ImageType 
	/// @param nPixelDataCharacteristics	Pixel data is enumOriginal or enumDerived
	/// @param nImageCharacteristic			Image is enumNoImageCharacteristic (Default), enumContentAmplitude, or enumContentComplexAmplitude
	/// @return true/false
	bool SetImageType(const SDICOS::GeneralImageModule::PIXEL_DATA_CHARACTERISTICS nPixelDataCharacteristics, const SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS nImageCharacteristic = SDICOS::AITImageType::enumNoImageCharacteristic);
		
	/// @see SetImageType
	/// @return PIXEL_DATA_CHARACTERISTICS or enumUnknownPixelDataCharacteristics if no pixel data set
	SDICOS::GeneralImageModule::PIXEL_DATA_CHARACTERISTICS GetPixelDataCharacteristics() const;
	/// @see SetImageType
	/// @return AIT_IMAGE_CHARACTERISTICS
	SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS GetImageCharacteristic() const;

	/// Set AIT Device Type
	/// @param nAitDeviceType	Device types: Passive MMW, Active MMW, XBS, TX, THZ, Active IR, Passive IR
	/// @return true/false
	bool SetAitDeviceType(const SDICOS::AIT2DTypes::AIT2DImage::AIT_DEVICE_TYPE nAitDeviceType);

	/// @see SetAitDeviceType
	SDICOS::AIT2DTypes:: AIT2DImage::AIT_DEVICE_TYPE GetAitDeviceType()const;

	/// Set Photometric Interpretation. Default value is MonoChrome2
	/// @param nPI Pixel data interpretation. Valid values are MONOCHROME1, MONOCHROME2, PALETTE COLOR.
	/// @return true/false false if nPI is not one of the valid values
	bool SetPhotometricInterpretation(const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI);
		
	/// @see SetPhotometricInterpretation
	ImagePixelMacro::PHOTOMETRIC_INTERPRETATION GetPhotometricInterpretation()const;
		
	/// Get bits per pixel
	/// @return Return one of [8, 16, 32, 64]
	S_UINT32 GetBitsAllocated() const;

	/// Get bits stored per pixel
	S_UINT32 GetBitsStored() const;

	/// Most significant but for pixel data.
	/// @return (GetBitsStored() - 1)
	S_UINT32 GetHighBit() const;

	/// Set Pixel Intensity Relationship. Default value is Linear.
	/// @param nRelationship Pixel Intensity Relationship. Values are "LIN", "LOG"
	/// @return true/false	false if sign could not be set
	bool SetPixelIntensityRelationship(const AIT2DTypes::AIT2DImage::PIXEL_INTENSITY_RELATIONSHIP nRelationship);
	/// @see SetPixelIntensityRelationship
	AIT2DTypes::AIT2DImage::PIXEL_INTENSITY_RELATIONSHIP GetPixelIntensityRelationship()const;

	/// Pixel Representation for AIT2D is always unsigned integer
	ImagePixelMacro::PIXEL_REPRESENTATION GetPixelRepresentation() const;

	/// Set Pixel Intensity Sign. Default value is Low Value equals Low Intensity
	/// @param nSign Pixel Intensity Relationship Sign. Values are enumLowValueLowIntensity and enumHighValueLowIntensity
	/// @return true/false	false if sign could not be set
	bool SetPixelIntensitySign(const AIT2DTypes::AIT2DImage::PIXEL_INTENSITY_RELATIONSHIP_SIGN nSign);

	/// Get Pixel Intensity Relationship Sign
	AIT2DTypes::AIT2DImage::PIXEL_INTENSITY_RELATIONSHIP_SIGN GetPixelIntensitySign()const;
		
	/// Set presentation LUT shape for when Photometric Interpretation is PALETTE COLOR. Default value is IDENTITY.
	/// Presentation LUT Shape is internally set to enumInverse when Photometric Interpretation is enumMonochrome1.
	/// Presentation LUT Shape is internally set to enumIdentity when Photometric Interpretation is enumMonochrome2.
	/// The LUT Shape will be set according to the above restrictions for both monochrome interpretations, meaning
	/// this value is updated as Photometric interpretation is changed.
	/// @see SetPhotometricInterpretation
	bool SetPresentationLUTShape(const GeneralImageModule::PRESENTATION_LUT_SHAPE nLutShape);

#if 0
	/// @see SetPresentationLUTShape
	GeneralImageModule::PRESENTATION_LUT_SHAPE GetPresentationLUTShape()const;
#endif

	/// Get LUT Shape based on Photometric Interpretation.
	/// @return	(Monochrome1 => Inverse), (Monochrome2 and others => Identity) o
	AIT2DTypes::AIT2DImage::PRESENTATION_LUT_SHAPE GetPresentationLutShape() const;
		
	/// [Optional] A text description og how this image was derived
	/// @param strDescription Descrtiption 
	/// @return true/false
	bool SetDerivationDescription(const DcsShortText& strDescription);
	/// @see SetDerivationDescriptioin
	/// @return DcsShortText
	DcsShortText GetDerivationDescription() const;
	/// Has a valid Derivation Description been set
	/// @return true/false
	bool HasDerivationDescription() const;
	/// Delete Derivation Description
	void DeleteDerivationDescription();

	/// Set Acquisition Device Processing Description : Tag (0018, 1400)
	///	@param strDescription	Acquisition Device Processing Description : Tag (0018, 1400), VR = LO [optional]
	/// @return true/false
	bool SetAcquisitionDeviceProcessingDescription(const DcsLongString& strDescription);
	/// @see SetAcquisitionDeviceProcessingDescription
	DcsString GetAcquisitionDeviceProcessingDescription() const;
	bool HasAcquisitionDeviceProcessingDescription() const;
	/// Delete attribute so that it is not written to DICOS file.
	void DeleteAcquisitionDeviceProcessingDescription();

	/// Set Acquisition Device Processing Code : Tag (0018, 1401)
	///	@param strProcessingCode Acquisition Device Processing Code : Tag (0018, 1401), VR = LO [optional]
	/// @return true/false
	bool SetAcquisitionDeviceProcessingCode(const DcsLongString& strProcessingCode);
	/// @see SetAcquisitionDeviceProcessingCode
	DcsString GetAcquisitionDeviceProcessingCode()const;
	bool HasAcquisitionDeviceProcessingCode() const;
	/// Delete the attribute so that it is not written to the DICOS file
	void DeleteAcquisitionDeviceProcessingCode();

	/// Set Calibration Image : Tag (0050, 0004)
	/// @param nIsCalibrationImage Is a Calibration Image : Tag (0050, 0004), VR = CS [optional]
	///			i) true = "YES", false = "NO"
	/// @return true/false
	bool SetCalibrationImage(const bool nIsCalibrationImage);
	/// @see SetCalibrationImage
	bool IsCalibrationImage()const;
	/// @see SetCalibrationImage
	DcsString IsCalibrationImageAsString()const;

	///
	/// \brief Set Window Center and Width.
	/// Set Window Center and Width to define a linear LUT transformation.
	/// The range of values around center defined by +/-width is mapped to the full output range.
	/// Input values <= (center-width) map to minimum output value.
	/// Input values >= (center+width) map to the maximum output value.
	/// The Window Center and Width are only needed if the DX 'Presentation Intent Type' is 'FOR PRESENTATION' and a LUT is not specified.
	/// Center and Width arrays must be the same size, within the  and width >= 1.0f.
	///
	/// Set one Window Center and Width
	/// @param fCenter window center 
	/// @param fWidth window width must be >= 1.0
	/// @return true/false false if parameters are invalid.
	bool SetWindowCenterAndWidth(const float fCenter, const float fWidth);

	/// Get one Window Center and Width. 
	/// If more than one center and width are available, the first center and width found are returned.
	/// @param fCenter	Window Center value or 0.0f if it has not been set.
	/// @param fWidth	Window width value or 0.0f if it has not been set.
	/// @return true/false false if Center and Width have not been set.
	bool GetWindowCenterAndWidth(float &fCenter, float &fWidth)const;

	/// Delete the Window Center and Width attribute so that it is not written to the DICOS file.
	bool DeleteWindowCenterAndWidth();
	
	/// Set LUT as unsigned 16-bit values
	/// The LUT is only needed is DX 'Presentation Intent Type' is 'FOR PRESENTATION' and Window Center and Width are not used.
	/// @param lutData				Array of LUT values. An array of 0 size removes the existing LUT.
	///	@param nFirstValueMapped 	First Input Value Mapped to LUT entry 0. Can be signed or unsigned.
	/// @param nBitsPerEntry		Bits per LUT Entry. Must be in [10,16]. Default value is 16.
	/// @return true/false			false if LUT values are invalid
	bool SetLUTData(const Array1D<S_UINT16>& lutData, const S_UINT16 nFirstValueMapped, const S_UINT16 nBitsPerEntry = 16);
	
	/// Set LUT as signed 16-bit values and remove any existing signed or unsigned LUT.
	bool SetLUTData(const Array1D<S_INT16>& lutData, const S_UINT16 nFirstValueMapped, const S_UINT16 nBitsPerEntry = 16);

	/// Set LUT as unsigned 16-bit values and remove any existing signed unsigned LUT
	/// The LUT is only needed is DX 'Presentation Intent Type' is 'FOR PRESENTATION' and Window Center and Width
	/// are not used to specify how the DX data is to be presented.
	bool SetLUTData(const Array1D<S_UINT16>& lutData, const S_INT16 nFirstValueMapped, const S_UINT16 nBitsPerEntry = 16);
	
	/// Set LUT as signed 16-bit values and remove any existing signed or unsigned LUT.
	bool SetLUTData(const Array1D<S_INT16>& lutData, const S_INT16 nFirstValueMapped, const S_UINT16 nBitsPerEntry = 16);
	
	/// Get a copy of the LUT as unsigned shorts
	/// @return true/false false if no LUT exists
	bool GetLUTData(Array1D<S_UINT16>& lutData) const;
	
	/// Get a copy of the LUT as signed shorts
	/// @return true/false false if no LUT exists
	bool GetLUTData(Array1D<S_INT16>& lutData);
		
	/// Set the first input value mapped to value 0 in the LUT.
	///	@param nFirstValueMapped 	First Input Value Mapped as an unsigned short.
	///	@return true/false			false if any parameters are invalid.
	bool SetFirstValueMapped(const S_UINT16 nFirstValueMapped);
	
	/// Set the first input value mapped to value 0 in the LUT.
	///	@param nFirstValueMapped 	First Input Value Mapped as a signed short.
	///	@return true/false			false if any parameters are invalid.
	bool SetFirstValueMapped(const S_INT16 nFirstValueMapped);
	
	/// @see SetFirstValueMapped
	bool GetFirstValueMapped(S_UINT16& firstValue) const;
	
	/// @see SetFirstValueMapped
	bool GetFirstValueMapped(S_INT16& firstValue) const;
	
	/// @see SetLUTDescriptor
	/// @return true/false false if no LUT exists
	bool GetLUTDescriptor(S_UINT16& numEntries, S_UINT16& firstValueMapped, S_UINT16& bitsPerEntry) const;
	
	/// @see SetLUTDescriptor
	/// @return true/false false if no LUT exists
	bool GetLUTDescriptor(S_UINT16& numEntries, S_INT16& firstValueMapped, S_UINT16& bitsPerEntry);

	/// Red color LUT used when photometric interpretation is set to color palette
	SDICOS::Array1D<S_UINT8>& GetRedLUT();
	/// Red color LUT used when photometric interpretation is set to color palette
	const SDICOS::Array1D<S_UINT8>& GetRedLUT()const;

	/// Green color LUT used when photometric interpretation is set to color palette
	SDICOS::Array1D<S_UINT8>& GetGreenLUT();
	/// Green color LUT used when photometric interpretation is set to color palette
	const SDICOS::Array1D<S_UINT8>& GetGreenLUT()const;

	/// Blue color LUT used when photometric interpretation is set to color palette
	SDICOS::Array1D<S_UINT8>& GetBlueLUT();
	/// Blue color LUT used when photometric interpretation is set to color palette
	const SDICOS::Array1D<S_UINT8>& GetBlueLUT()const;

	/// Set pixel spacing for rows and columns in MM. Distances between centers of two adjacent pixels.
	/// Pixel spacing is optional and included only if valid values are specified.
	/// @param rowSpacing	Space between two rows
	/// @param colSpacing	Space between two columns.
	/// @return true/false	false if values are < 0
	bool SetPixelMeasures(const float rowSpacing, const float colSpacing);
		
	/// @see SetPixelMeasures
	bool SetRowSpacing(const float rowSpacing);
		
	/// @see SetPixelMeasures
	bool SetColSpacing(const float colSpacing);
	
	/// Get the row and column spacing in MM.
	/// @param rowSpacing Row spacing in MM. Set to 0 if pixel measurements do not exists.
	/// @param colSpacing Column spacing in MM. 
	/// @return true/false false if rowSpacing and/or colSpacing is < 0
	bool GetPixelMeasures(float& rowSpacing, float& colSpacing) const;
		
	/// Set (x,y,z) coordinates in millimeters (MM) of the center of
	/// the upper left corner voxel (first voxel transmitted).
	/// Image Position for AIT2D is optional and by default is set to (0,0,0).
	/// @return true/false
	bool SetImagePosition(const float x, const float y, const float z);
		
	/// @see SetImagePosition
	bool GetImagePosition(float& x, float& y, float& z)const;
		
	/// Set the Image Orientation vectors. Units are millimeters(MM).
	/// The Image Orientation is optional. 
	/// The default orientation vectors are XAxis=(1,0,0) and YAxis=(0,1,0).
	///
	/// The coordinate frame describing the image orientation is a left handed system.
	/// The axes are defined by looking at the front of the volume(facing front-to-back) the
	/// positive, horizontal x-axis points to the right and the positive, vertical z-axis points up
	/// and the positive y-axis points towards the observer.
	///
	/// @param XAxis	Direction vector for the first row of the image
	/// @param YAxis	Direction vector for the first column of the image.
	/// @return true/false		false if the the vectors are not close to being orthogonal
	bool SetImageOrientation(const Vector3D<float>& XAxis, const Vector3D<float>& YAxis);
		
	/// @see SetImageOrientation
	bool GetImageOrientation(Vector3D<float>& xAxis, Vector3D<float>& yAxis) const;
	
	/// Delete Image Orientation so that it is not written to the DICOS file.
	void DeleteImageOrientation();
	
	/// Set the Person Reference Coordinate System to Reference Coordinate System Orientation.
	/// The Person Orientation is optional. 
	/// By default the Person Orientation is not written to the DICOS file.
	///
	/// It is the actual Object of Inspection (OOI) orientation during the scanning process
	/// and is relative to the coordinate frame described by SetImageOrientation.
	///
	/// @param leftOrientation		Direction vector from the OOI center out its left side. (XAxis)
	/// @param frontOrientation		Direction vector that the OOI is facing. (YAxis)
	/// @return true/false			false if front and left vectors are not close to orthogonal
	bool SetPersonOrientation(const Vector3D<float>& leftOrientation, const Vector3D<float>& frontOrientation);
		
	/// @see SetPersonOrientation
	bool GetPersonOrientation(Vector3D<float>& leftOrientation, Vector3D<float>& frontOrientation) const;
	
	/// Delete person orientation so that it is not written to the DICOS file
	void DeletePersonOrientation();

	/// Set the 2D Image data. Data can only be unsigned.
	/// @param data Unsigned 16-bit 2D Image data
	/// @return true/false
	bool SetData(const Image2D& data);

	/// Get a reference to the Image data object
	const Image2D& GetData() const;
	
	/// Get a reference to the Image data object
	Image2D& GetData();
	
	/// Returns SOP Class UID based on the pixel data type. Returns empty string if pixel data is not allocated.
	/// Ex. If the image data is 64-bit unsigned, then the return value is SOPClassUID::GetAIT2D_64Bit()
	virtual DcsUniqueIdentifier GetSopClassUID()const;
protected:

	/// Override to allocate a derived module-level API object.
	/// By default allocates AIT2DModule.  This module is internally
	/// used for reading, writing, and networking.
	/// @return Dynamically allocated module-level API object
	virtual AIT2DModule* AllocateModule()const;

	/// Override this function to set attributes in the SDICOS::AIT2DModule object that are not set with AIT2D
	/// WriteDerived_internal is called by the AIT2DModule::Write() methods before attributes in the AIT2D class are written.
	/// If the derived class wishes to further restrict values 
	/// @param ait AIT2D object to set new values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors writing data
	virtual bool WriteDerived_internal(SDICOS::AIT2DModule &ait, ErrorLog &errorlog)const;
	
	/// Override this function to retrieve attributes from the SDICOS::AIT2DModule object that are not retrieved by AIT2D
	/// ReadDerived_internal is called by AIT2DModule::Read() methods before attributes in the AIT2D class are read.
	/// @param ait AIT2D object to retrieve read values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors reading data
	virtual bool ReadDerived_internal(const SDICOS::AIT2DModule &ait, ErrorLog &errorlog);
	
	class ImplAIT2DSeriesBase;

	ImplAIT2DSeriesBase* GetImpl();
	const ImplAIT2DSeriesBase* GetImpl() const;
		
private:
	ImplAIT2DSeriesBase * m_pImplAIT2DSeriesBase; ///< Internal implementation
};

} // SDICOS

#endif	/* _STRATOVAN_DICOS_SDCS_TEMPLATE_AIT2D_H_ */

