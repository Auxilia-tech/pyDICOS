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
#ifndef _STRATOVAN_DICOS_TEMPLATE_CLASSES_DX_H_
#define	_STRATOVAN_DICOS_TEMPLATE_CLASSES_DX_H_

#include "SDICOS/ModuleDX.h"
#include "SDICOS/TemplateBase.h"
#include "SDICOS/Array1D.h"
#include "SDICOS/Point3D.h"
#include "SDICOS/Vector3D.h"
#include "SDICOS/TemplateCommon.h"
#include "SDICOS/Image2D.h"
#include "SDICOS/ImageBaseUser.h"
#include "SDICOS/XRayEquipmentUser.h"
#include "SDICOS/XRayGenerationUser.h"
#include "SDICOS/DXDetectorUser.h"
#include "SDICOS/DXPositioningUser.h"
#include "SDICOS/XRayFiltrationUser.h"
#include "SDICOS/FrameOfReferenceUser.h"
#include "SDICOS/AcquisitionContextUser.h"

namespace SDICOS 
{

///
/// \class DX
/// \brief DX represents a single DX/X-Ray Scan. This class is not thread safe.
///
/// This class is not thread safe.
/// It abstracts away the hierarchy of the DICOS specification
/// and provides an API that contains methods for setting the attributes needed for a DICOS DX object.
/// This class implements a DX IOD that contains a single Digital X-Ray image.
/// The image consists of unsigned 16/32/64-bit integer or float data and an optional 16-bit LUT if the IOD is for presentation.
///
/// The default presentation intent type is 'FOR PROCESSING'.
/// The default SOP class UID is set to SOPClassUID::GetDXProcessing().
/// Default image position is (0,0,0) and image orientation is X = (1,0,0) and Y = (0,1,0).
/// 
/// Default values for each attribute are documented with the set and get functions
/// 
/// DX/X-Ray Specific Modules
///   - Modules in the DICOS DX/X-Ray Modality specification, are implemented as base classes of SDICOS::DX
///   - XRay Equipment, DX Detector, DX Positioning, XRayGeneration, and XRay Filtration
/// 
class DX 
	: public IODCommon, 
	  public ScanCommon, 
	  public XRayEquipmentUser, 
	  public ImageCommonUser,		// Coordinate System and Image Origin
	  public DXDetectorUser,		// See DXDetectorUser.h. Add X-Ray Detector Module Attributes to the SDICOS::DX User Level API.
	  public DXPositioningUser,		// See DXPositioningUser.h. Add X-Ray Positioning Module Attribute to the SDICOS::DX User Level API
	  public XRayGenerationUser,	// See XRayGenerationUser.h Add X-Ray Generation Module Attributes to the SDICOS::DX User Level API.
	  public XRayFiltrationUser,	// See XRayFiltrationUser.h Add X-Ray Filtration Module Attributes to the SDICOS::DX User Level API.
	  public FrameOfReferenceUser,  // An optional module. See DX::EnableFrameOfReference() and AIT2D::DisableFrameOfReference()
	  public AcquisitionContextUser // See AcquisitionContextUser.h  Add Acquisition Context Module Attributes to the SDICOS::DX User Level API
{
public:
	/// Default Constructor
	DX();
	/// Construct DX IOD Object of Inspection Type, presentation type, pixel data type and photometric interpretation
	DX(
		const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE nOOIType,
		const DXTypes::DXSeries::PRESENTATION_INTENT_TYPE presentationIntentType = DXTypes::DXSeries::enumProcessing,
		const GeneralImageModule::PIXEL_DATA_CHARACTERISTICS pixelDataCharacteristics = GeneralImageModule::enumOriginal, 
		const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI = ImagePixelMacro::enumMonochrome2
	);
	
	/// Copy Constructor
	DX(const DX&);
	
	/// Destructor
	virtual ~DX();
	
	/// Free Allocated Memory
	virtual void FreeMemory();
	
	/// Assignment operator
	DX& operator=(const DX&);
	
	/// Comparison operator
	bool operator==(const DX&) const;
	/// Comparison operator
	bool operator!=(const DX&) const;
	
	/// Initialize with OOI Type, presentation intent type, pixel data and photometric interpretation
	/// All other values are set to valid DICOS defaults.
	/// Image Characteristics defaults to DXTypes::DXImage::enumIntensity.
	/// @return true/false false if supplied parameters are an invalid combination
	bool Initialize(
		const ObjectOfInspectionModule::OBJECT_OF_INSPECTION_TYPE nOOIType,
		const DXTypes::DXSeries::PRESENTATION_INTENT_TYPE presentationIntentType,
		const GeneralImageModule::PIXEL_DATA_CHARACTERISTICS pixelDataCharacteristics = GeneralImageModule::enumOriginal, 
		const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI = ImagePixelMacro::enumMonochrome2
	);

	/// Initialize with a DX object
	/// @param dx DX to initialize from
	/// @param errorlog Error Log
	/// @param bMoveData	true = Move data (such as pixel data), instead of copying, from vSeries
	///						false = Copy data from vSeries
	bool Initialize(DXModule &dx, ErrorLog &errorlog, const bool bMoveData);
	
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
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Returns number of clients that successfully sent DICOS data
	virtual S_UINT32 SendOverNetwork(SDICOS::Network::DcsClientManager &clientManager, ErrorLog &errorlog, std::vector< Network::DcsClientManager::ClientMetrics > &vSendTimes);

	/// Return enumXRAY
	virtual MODALITY GetModality()const;

	/// Check the attributes in the DX object against the DICOS specification
	virtual bool Validate(ErrorLog& errorlog) const;

	/////////////
	// X-Ray Series Module

	/// Set presentation intent type. Default value is 'FOR PROCESSING'
	/// @param presentationIntentType Intent of images within this series. 'FOR PROCESSING:' or 'FOR PRESENTATION'
	/// @return true/false 
	bool SetPresentationIntentType(const DXTypes::DXSeries::PRESENTATION_INTENT_TYPE presentationIntentType);
	/// @see SetPresentationIntentType
	DXTypes::DXSeries::PRESENTATION_INTENT_TYPE GetPresentationIntentType() const;

	/////////////
	// Frame of Reference

	/// Enable Frame of Reference attributes to be written during Write()
	/// FrameOfReferenceUser attributes are disabled by default
	void EnableFrameOfReference();

	/// Frame Of Reference attributes will not be written during Write()
	void DisableFrameOfReference();

	/// @see EnableFrameOfReference
	/// @return true/false
	bool IsFrameOfReferenceEnabled() const;
	
	/////////////
	// X-Ray Image Module

	/// Set Image Type properties. Default values are ORIGINAL and PRIMARY
	/// @param pixelDataCharacteristics Pixel data is either 'ORIGINAL' or 'DERIVED'.
	/// @param imageCharacteristics Pixel data defaults to "INTENSITY'
	/// @return true/false false if pixelDataCharacteristics or imageCharacteristics is not valid
	bool SetImageType(	const GeneralImageModule::PIXEL_DATA_CHARACTERISTICS pixelDataCharacteristics, 
						const ImageCharacteristics::OOI_IMAGE_CHARACTERISTICS imageCharacteristics = ImageCharacteristics::enumIntensity);
	
	/// @see SetImageType
	bool GetImageType(GeneralImageModule::PIXEL_DATA_CHARACTERISTICS& pixelDataCharacteristics, 
					  ImageCharacteristics::OOI_IMAGE_CHARACTERISTICS& imageCharacteristics);
	/// @see SetImageType
	GeneralImageModule::PIXEL_DATA_CHARACTERISTICS GetPixelDataCharacteristics() const;
	/// @see SetImageType
	ImageCharacteristics::OOI_IMAGE_CHARACTERISTICS GetImageCharacteristics() const;
	
	/// Set Photometric Interpretation. Default value is MONOCHROME2
	/// @param nPI Pixel data interpretation. Valid values are MONOCHROME1, MONOCHROME2, PALETTE COLOR.
	/// @return true/false false if nPI is not one of the valid values
	bool SetPhotometricInterpretation(const ImagePixelMacro::PHOTOMETRIC_INTERPRETATION nPI);
	/// @see SetPhotometricInterpretation
	ImagePixelMacro::PHOTOMETRIC_INTERPRETATION GetPhotometricInterpretation()const;

	/// Number bits per pixel in [8, 16, 32, 64]
	/// @return Bits per pixel or 0 if no data present
	SDICOS::S_UINT32 GetBitsAllocated() const;

	/// Number of bits stored for each pixe;
	/// @return Bits stored per pixel or 0 if no data present.
	SDICOS::S_UINT32 GetBitsStored() const;
	
	/// Most significnt bit for pixel data
	/// @return Most significant bit
	S_UINT32 GetHighBit() const;

	/// Set Pixel Intensity Relationship. Default value is Linear.
	/// The default value is linear.
	/// @param pixelIntensityRelationship Relationship between pixel intensity values and x-ray beam intensity. LIN or LOG
	/// @return true/false false if pixelIntensityRelationship is not valid
	bool SetPixelIntensityRelationship(const DXTypes::DXImage::PIXEL_INTENSITY_RELATIONSHIP pixelIntensityRelationship);
	/// @see SetPixelIntensityRelationship
	DXTypes::DXImage::PIXEL_INTENSITY_RELATIONSHIP GetPixelIntensityRelationship() const;

	/// Set Pixel Intensity Relationship Sign. Default value is enumLowValueLowIntensity.
	/// The default value is Low Value is Low Intensity.
	/// @param pixelIntensityRelationshipSign Indicates whether low values = low intensity or high-values = high intensity
	/// @return true/false false if pixelIntensityRelationshipSign is not valid.
	bool SetPixelIntensityRelationshipSign(const DXTypes::DXImage::PIXEL_INTENSITY_RELATIONSHIP_SIGN pixelIntensityRelationshipSign);
	/// @see SetPixelIntensityRelationshipSign
	DXTypes::DXImage::PIXEL_INTENSITY_RELATIONSHIP_SIGN GetPixelIntensityRelationshipSign() const;
	
	/// Set the Rescale Type units after scale and intercept are applied.
	/// For DX IODs slope and intercept are always set to 1 and 0 so this
	/// method is provided as a convenience to change the units from 
	/// the default value which is 'HU'.
	bool SetRescaleType(const DcsLongString& rescaleType);
	/// @see SetRescaleType
	DcsLongString GetRescaleType() const;
	
	/// The distance between pixel centers in millimeters
	bool SetReportedPixelSpacingInMM(const float fRow, const float fCol);
	/// @see SetReportedPixelSpacingInMM
	float GetReportedPixelSpacingColumn()const;
	/// @see SetReportedPixelSpacingInMM
	float GetReportedPixelSpacingRow()const;
	/// Returns true if data is set
	bool HasReportedPixelSpacing()const;
	/// Delete data
	void DeleteReportedPixelSpacing();

	/// Set presentation LUT shape for when Photometric Interpretation is PALETTE COLOR. Default value is IDENTITY.
	/// Presentation LUT Shape is internally set to enumInverse when Photometric Interpretation is enumMonochrome1.
	/// Presentation LUT Shape is internally set to enumIdentity when Photometric Interpretation is enumMonochrome2.
	/// The LUT Shape will be set according to the above restrictions for both monochrome interpretations, meaning
	/// this value is updated as Photometric interpretation is changed.
	/// @see SetPhotometricInterpretation
	bool SetPresentationLUTShape(const GeneralImageModule::PRESENTATION_LUT_SHAPE nLutShape);
	/// @see SetPresentationLUTShape
	GeneralImageModule::PRESENTATION_LUT_SHAPE GetPresentationLUTShape()const;

	/// [Optional] Derivation Description when Image Type (0008, 0008) is Derived Image
	/// @param dsDerivationDescription Derivation Description
	/// @return true/false
	bool SetDerivationDescription(const DcsShortText& dsDerivationDescription);
	/// @see SetDerivationDescription
	/// @return DcsShortString
	DcsShortText GetDerivationDescription();
	/// Delete Derivation Description String
	void DeleteDerivationDescription();

	/// [Optional] Acquisition Device Processing Description is a human-readable text 
	/// of the digital processing on the images before exchange. 
	/// Examples of this processing are: edge enhanced, subtracted, time filtered, gamma-corrected, convolved (spatially filtered).
	/// @param dsDescription Acquisition processing description
	/// @return true/false
	bool SetAcquisitionDeviceProcessingDescription(const DcsLongString& dsDescription);
	/// @see SetAcquisitionDeviceProcessingDescription
	/// @return DcsLongString
	DcsLongString GetAcquisitionDeviceProcessingDescription() const;
	/// Delete Acquisition Device Processing Description
	void DeleteAcquisitionDeviceProcessingDescription();

	/// [Optional] Manufacturer specific code representing the device-specific processing associated with the image.
	/// @param dsProcessingCode Processing Code
	/// @return true/false
	bool SetAcquisitionDeviceProcessingCode(const DcsLongString& dsProcessingCode);
	/// @see SetAcquisitionDeviceProcessingCode
	/// @return DcsLongString
	DcsLongString GetAcquisitionDeviceProcessingCode() const;
	/// Delete Acquisition Device Processing Code
	void DeleteAcquisitionDeviceProcessingCode();

	///
	/// Set Window Center and Width to define a linear LUT transformation.
	/// The range of values around center defined by +/-width is mapped to the full output range.
	/// Input values <= (center-width) map to minimum output value.
	/// Input values >= (center+width) map to the maximum output value.
	/// The Window Center and Width are only needed if the DX 'Presentation Intent Type' is 'FOR PRESENTATION' and a LUT is not specified.
	/// Center and Width arrays must be the same size, within the  and width >= 1.0f.
	///
	/// \brief Set Window Center and Width.
	/// @param arrayCenter Center of input range that maps to output range
	/// @param arrayWidth  Width if input range around center that maps to output range.
	/// @return true/false	false if arrays are not the proper size and value.
	///
	bool SetWindowCenterAndWidth(const Array1D<float> &arrayCenter, const Array1D<float> &arrayWidth);
	
	/// Set one Window Center and Width
	/// @param fCenter window center 
	/// @param fWidth window width must be >= 1.0
	/// @return true/false false if parameters are invalid.
	bool SetWindowCenterAndWidth(const float fCenter, const float fWidth);

	///
	/// Get Window Center and Width. If no window center and width have been set
	/// arrayCenter and arrayWidth are unchanged.
	///
	/// @see SetWindowCenterAndWidth(const Array1D<float> &, const Array1D<float> &)
	/// @return true/false	false if Window Center and Width have not been set.
	bool GetWindowCenterAndWidth(Array1D<float> &arrayCenter, Array1D<float> &arrayWidth)const;
	
	/// Get one Window Center and Width. 
	/// If more than one center and width are available, the first center and width found are returned.
	/// @param fCenter	Window Center value or 0.0f if it has not been set.
	/// @param fWidth	Window width value or 0.0f if it has not been set.
	/// @return true/false false if Center and Width have not been set.
	bool GetWindowCenterAndWidth(float &fCenter, float &fWidth)const;

	/// Delete the Window Center and Width attribute so that it is not written to the DICOS file.
	bool DeleteWindowCenterAndWidth();

	///
	/// Set Window Center and Width Explanation : Tag (0028, 1055)
	/// This attribute is optional and is provided only for convenience.
	/// This method does not check that the size of the array is equivalent to the size of the window center and window width.
	/// @param strExplanation Window Center and Width Explanation must be valid DcsLongString objects
	///			i) All values stored in a single tag (Ex. "Expl1\Expl2") \n
	///			ii) Array size must be equal to SetWindowCenterAndWidth() parameters
	/// @return true/false	false if DcsLongString objects are invalid
	///
	bool SetWindowCenterAndWidthExplanation(const Array1D<DcsLongString> &strExplanation);
	/// @see SetWindowCenterAndWidthExplanation
	bool SetWindowCenterAndWidthExplanation(const DcsLongString& strExplanation);
	///
	/// Get Window Center and Width Explanation.
	/// @param strExplanation Put explanations here. If no explanations are set this array is untouched.
	/// @return true/false	false if no explanation has been set.
	bool GetWindowCenterAndWidthExplanation(Array1D<DcsLongString> &strExplanation)const;

	/// Delete the Window Center and Width Explanation Attribute so that it is not written to the DICOS file.
	bool DeleteWindowCenterAndWidthExplanation();
	
	//////////////
	// VOI LUT Module

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
	
	/// @see SetLUTData
	/// @return true/false false if no LUT exists
	bool GetLUTDescriptor(S_UINT16& numEntries, S_UINT16& firstValueMapped, S_UINT16& bitsPerEntry) const;
	
	/// @see SetLUTData
	/// @return true/false false if no LUT exists
	bool GetLUTDescriptor(S_UINT16& numEntries, S_INT16& firstValueMapped, S_UINT16& bitsPerEntry);
	
	/// LUT Explanation [optional]
	/// @param dsExplanation Explanation of LUT meaning
	/// @return true/false
	bool SetLUTExplanation(const DcsLongString& dsExplanation);
	/// @see SetLUTExplanation
	/// @return DcsLongString
	DcsLongString GetLUTExplanation() const;
	/// Delete LUT Explanation string
	void DeleteLUTExplanation();

	/// Set the pixel aspect ratio. Required if the aspect ratio is not 1:1
	/// The default values are set to 1.
	/// @param rowPixelSize The vertical pixel size. How thick is a row.
	/// @param colPixelSize The horizontal pixel size. How wide is a column
	/// @return true/false false if the aspect ratio values are invalid (e.g. <= 0)
	bool SetPixelAspectRatio(const S_INT32 rowPixelSize, const S_INT32 colPixelSize);
	
	/// Get pixel aspect ratio. If no pixel aspect ratio has been set (1,1) is returned.
	/// @return true/false false if the pixel aspect ratio is invalid. e.g. equal to 0.
	bool GetPixelAspectRatio(S_INT32& rowPixelSize, S_INT32& colPixelSize) const;
	
	/// Get the size of a row pixel in the vertical direction
	S_INT32 GetVerticalAspectSize() const;
	
	/// Get the size of a column pixel in the horizontal direction
	S_INT32 GetHorizontalAspectSize() const;
	
	//////////
	// General Image Module

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

	/// The General Image Module Acquisition Number identifies a single continuous 
	/// gathering of data over a period of time that resulted in the AIT3D image data.
	/// This parameter is optional and defaults to 0.
	/// @param acquisitionNumber Numeric identifier for the AIT3D object acquisition period.
	/// @return true/false
	bool SetAcquisitionNumber(const S_INT32 acquisitionNumber);
	/// @see SetAcquisitionNumber
	/// @return true/false false if no acquisition number was set.
	bool GetAcquisitionNumber(S_INT32& acquisitionNumber) const;
	/// Acquisition Number has been set
	/// @return true/false
	bool HasAcquisitionNumber() const;
	/// Remove Acquisition Number so that it is not written to the DICOS file
	void DeleteAcquisitionNumber();

	/// Image Acquisition Date and Time
	bool SetImageAcquisitionDateAndTime(const DcsDateTime& strDateTime);
	/// Image Acquisition Date and Time
	bool SetImageAcquisitionDateAndTime(const DcsDate& strDate, const DcsTime& strTime);
	/// @see SetImageAcquisitionDateAndTime
	/// @return Empty DateTime() if no valid and and time are set
	const DcsDateTime& GetImageAcquisitionDateTime()const;
	/// Image Acquisition Date and Time are set
	/// @return true/false
	bool HasImageAcquisitionDateAndTime() const;
	/// Remove Image Acquisition Date and Time
	void DeleteImageAcquisitionDateAndTime();

	/// Image Acquisition Duration in seconds. Defaults to 0.0f indicating no value is set
	/// @return false if duration < 0
	bool SetImageAcquisitionDuration(const double nAcquisitionDuration);
	/// @see SetImageAcquisitionDuration
	double GetImageAcquisitionDuration()const;
	/// Image Acquisition Duration has been set
	/// @return true/false
	bool HasImageAcquisitionDuration() const;
	/// Remove Image Acquisition Duration
	void DeleteImageAcquisitionDuration();

	/// Flag the image as having a burned in annotation. Default value is false.
	bool SetBurnedInAnnotation(const bool bUsesAnnotation);
	/// @see SetBurnedInAnnotation
	bool HasBurnedInAnnotation()const;

	//////////
	// Image Pixel Module

	/// Set the 2D Image data for the XRay. Data can only be unsigned.
	/// If photometric interpretation is set to color palette, these values are indices into the red, green, and blue LUT's
	/// @param data Unsigned 16/32/64-bit integer or float 2D Image data
	/// @return true/false
	bool SetXRayData(const Image2D& data);

	/// Get a reference to the Image data object
	const Image2D& GetXRayData() const;
	/// Get a reference to the Image data object
	Image2D& GetXRayData();

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

	/// Set image pixel spacing
	/// Default is to not use pixel spacing.
	/// @param fRow Row pixel spacing
	/// @param fColumn Column pixel spacing
	/// @param dsSpacingDescription Description for pixel spacing
	void SetPixelSpacing(const float fRow, const float fColumn, const DcsLongString &dsSpacingDescription);
	/// Returns true if pixel spacing is available
	bool HasPixelSpacing()const;
	/// @see SetPixelSpacing
	float GetPixelSpacingRow()const;
	/// @see SetPixelSpacing
	float GetPixelSpacingColumn()const;
	/// @see SetPixelSpacing
	DcsString GetPixelSpacingDescription()const;

	/// Returns SOP Class UID based on the pixel data type and presentation type. Returns empty string if pixel data is not allocated.
	/// Ex. If the image data is 64-bit unsigned and presentation type is for processing, then 
	/// the return value is SOPClassUID::GetDXProcessing_64Bit()
	virtual DcsUniqueIdentifier GetSopClassUID()const;

protected:

	/// Convert SDICOS::DX to SDICOS::DXModule
	/// @return Pointer to DXModule
	DXModule* ConvertToDXModule(ErrorLog& errorlog);

	/// Override to allocate a derived module-level API object.
	/// By default allocates DXModule.  This module is internally
	/// used for reading, writing, and networking.
	/// @return Dynamically allocated module-level API object
	virtual DXModule* AllocateModule()const;

	/// Override this function to set attributes in the SDICOS::DXModule object that are not set with DX
	/// WriteDerived_internal is called by the DXModule::Write() methods after attributes in the DX class are written.
	/// @param dx DX object to set new values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors writing data
	virtual bool WriteDerived_internal(DXModule &dx, ErrorLog &errorlog)const;
	
	/// Override this function to retrieve attributes from the SDICOS::DX object that are not retrieved by DX
	/// ReadDerived_internal is called by DX::Read() methods before ReadDerived_internal()
	/// @param dx DX object to retrieve read values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors reading data
	virtual bool ReadDerived_internal(const DXModule &dx, ErrorLog &errorlog);
		
	class ImplDXSeriesBase;
	
	ImplDXSeriesBase* GetImpl();
	const ImplDXSeriesBase* GetImpl() const;
	
private:
	ImplDXSeriesBase * m_pImplDXSeriesBase; ///< Internal implementation
};
	
} // SDICOS

#endif	/* _STRATOVAN_DICOS_TEMPLATE_CLASSES_DX_H_ */

