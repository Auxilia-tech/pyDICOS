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
#ifndef _STRATOVAN_DICOS_DX_H_
#define _STRATOVAN_DICOS_DX_H_

#include "SDICOS/ScannerCommon.h"
#include "SDICOS/AcquisitionContextModule.h"
#include "SDICOS/OverlayPlaneModule.h"
#include "SDICOS/FrameOfReference.h"
#include "SDICOS/TipImage.h"
#include "SDICOS/ImageHistogramModule.h"
#include "SDICOS/DXSeries.h"
#include "SDICOS/DXImage.h"
#include "SDICOS/DXDetector.h"
#include "SDICOS/DXPositioning.h"
#include "SDICOS/XRayGeneration.h"
#include "SDICOS/XRayFiltration.h"
#include "SDICOS/BasicPixelSpacingCalibrationMacro.h"
#include "SDICOS/DicosFile.h"
#include "SDICOS/XRayEquipmentModule.h"

namespace SDICOS
{

///
/// \class DXModule
/// \brief Implements DX IOD
/// SPECREF V03 Section 8.2.1, Table 33
///
/// Note: This class is not thread safe
/// DICOS SOP Class Name and UID (For Processing):	
///		Name:	"DICOS Digital X-Ray (DX) Image Storage-For Processing"	
/// 	UID:	"1.2.840.10008.5.1.4.1.1.501.2.2"
///
/// DICOS SOP Class Name and UID (For Presentation):	
/// 	Name:	"DICOS Digital X-Ray (DX) Image Storage-For Presentation"	
/// 	UID:	"1.2.840.10008.5.1.4.1.1.501.2.1"
///
class DXModule : public ScannerCommon
{
public:
	/// Constructor
	DXModule();
	/// Copy constructor
	DXModule(const DXModule &dx);
	/// Destructor
	~DXModule();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	DXModule& operator=(const DXModule &dx);
	/// Comparison operator
	bool operator==(const DXModule &dx)const;
	/// Comparison operator
	bool operator!=(const DXModule &dx)const;

	/// Read file
	/// @param filename Filename for the file to be read
	/// @param errorlog Errorlog to store read errors
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	bool Read(const Filename &filename, ErrorLog &errorlog, IMemoryManager *pMemMgr = S_NULL);
	///
	/// Read file and provide a manager of unknown attributes (Uses AttributeManager::enumNotSearchedOnly as filter)
	/// Known sequences containing unknown attributes are included as hierarchy references
	///
	/// @param filename Filename for the file to be read
	/// @param errorlog Errorlog to store read errors
	/// @param managerExcluded Manager with unknown or private attributes
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	bool Read(const Filename &filename, ErrorLog &errorlog, AttributeManager &managerExcluded, IMemoryManager *pMemMgr = S_NULL);
	/// Read from memory buffer
	/// @param membuffer Buffer to read from
	/// @param errorlog Error log
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	bool Read(MemoryBuffer &membuffer, ErrorLog &errorlog, IMemoryManager *pMemMgr = S_NULL);
	/// Read from memory bufferand provide a manager of unknown attributes (Uses AttributeManager::enumNotSearchedOnly as filter).
	/// Known sequences containing unknown attributes are included as hierarchy references
	/// @param membuffer Buffer to read from
	/// @param errorlog Error log
	/// @param managerExcluded Manager with unknown or private attributes
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	bool Read(MemoryBuffer &membuffer, ErrorLog &errorlog, AttributeManager &managerExcluded, IMemoryManager *pMemMgr = S_NULL);
	/// Read from memory file
	/// @param memfile Buffer to read from
	/// @param errorlog Error log
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	bool Read(MemoryFile &memfile, ErrorLog &errorlog, IMemoryManager *pMemMgr = S_NULL);
	/// Read data from memory buffer using DICOM network protocol (i.e. C-Store)
	/// @param membuffer Buffer to read from
	/// @param strTransferSyntax Transfer syntax to use while reading
	/// @param errorlog Error log
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @return Returns false if IsValid() fails
	/// @see AttributeManager::SetPixelDataMemoryManager
	bool ReadForNetworkProtocol(MemoryFile &membuffer, const DcsString &strTransferSyntax, ErrorLog &errorlog, IMemoryManager *pMemMgr = S_NULL);

	/// Write file
	/// @param filename Filename to write DX DICOS file
	/// @param nSyntax Transfer syntax to use while reading
	/// @param errorlog Error log
	/// @return Returns false if IsValid() fails
	bool Write(const Filename &filename, const DicosFile::TRANSFER_SYNTAX nSyntax, ErrorLog &errorlog);
	/// Write file to memory buffer
	/// @param membuffer Output memory buffer
	/// @param nSyntax Transfer syntax to use
	/// @param errorlog Error log
	/// @return Returns false if IsValid() fails
	bool Write(MemoryBuffer &membuffer, const DicosFile::TRANSFER_SYNTAX nSyntax, ErrorLog &errorlog);
	/// Write file to memory file
	/// @param memfile Output memory buffer
	/// @param nSyntax Transfer syntax to use
	/// @param errorlog Error log
	/// @return Returns false if IsValid() fails
	bool Write(MemoryFile &memfile, const DicosFile::TRANSFER_SYNTAX nSyntax, ErrorLog &errorlog);
	/// Write data to memory buffer for DICOM network protocol (i.e. C-Store)
	/// @param membuffer Output memory buffer
	/// @param nSyntax Transfer syntax to use
	/// @param errorlog Error log
	/// @return Returns false if IsValid() fails
	bool WriteForNetworkProtocol(MemoryFile &membuffer, const DicosFile::TRANSFER_SYNTAX nSyntax, ErrorLog &errorlog);

	/// Send data to another device using a TCP/IP connection
	/// @param nPort Port of target device
	/// @param dsIP IP Address of target device
	/// @param aeSrc Name of application listening for DICOS connections
	/// @param aeDst Name of application sending DICOS data
	/// @param errorlog Error log
	/// @param dsUserID User ID. Set if target device requires a user ID. Only non-empty strings allowed.
	/// @param dsPasscode Passcode. Set if target device requires a user ID. Only non-empty strings allowed.
	/// @return Returns true if data was sent without error. Returns false if parameters are invalid or data was not successfully received by the target device.
	bool SendOverNetwork(const S_UINT32 nPort, const DcsString &dsIP, const DcsApplicationEntity &aeSrc, 
						const DcsApplicationEntity &aeDst, ErrorLog &errorlog, 
						const DcsString &dsUserID = DcsString(), const DcsString &dsPasscode = DcsString());

	/// Send data over TCP/IP connection. The passed in client must already be connected to a host.
	/// Handles Starting and ending a DICOS session if a session is not already in progress.
	/// @param dclient Client already connected to host.
	/// @param errorlog Error log
	bool SendOverNetwork(SDICOS::Network::DcsClient &dclient, ErrorLog &errorlog);

	/// Write a list of DICOS attributes as text to file
	bool WriteAttributeList(const Filename &filename, ErrorLog &errorlog)const;

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	bool IsValid(ErrorLog &errorlog)const;

	/// Sets DICOS SOP Class UID (0008, 0016) to "For Processing" and Presentation Intent Type (0008, 0068) to "FOR PROCESSING"
	void SetForProcessing();
	/// Sets DICOS SOP Class UID (0008, 0016) to "For Presentation" and Presentation Intent Type (0008, 0068) to "FOR PRESENTATION"
	void SetForPresentation();

	/// DX Series [required]
	bool SetSeries(const DXTypes::DXSeries &dxseries);
	/// @see SetSeries
	bool GetSeries(DXTypes::DXSeries &dxseries);
	/// @see SetSeries
	DXTypes::DXSeries& GetSeries();
	/// @see SetSeries
	const DXTypes::DXSeries& GetSeries()const;

	/// XRay Equipment Module [required]
	bool SetXRayEquipment(const XRayEquipmentModule &xRayEquipment);
	/// @see SetXRayEquipment
	bool GetXRayEquipment(XRayEquipmentModule &xRayEquipment)const;
	/// @see SetXRayEquipment
	XRayEquipmentModule& GetXRayEquipment();
	/// @see SetXRayEquipment
	const XRayEquipmentModule& GetXRayEquipment()const;

	/// Frame of Reference [optional]
	bool SetFrameOfReference(const FrameOfReference &ref);
	/// @see SetFrameOfReference
	bool GetFrameOfReference(FrameOfReference &ref)const;
	/// Allocate Frame Of Reference
	void AllocateFrameOfReference();
	/// @see SetFrameOfReference
	FrameOfReference* GetFrameOfReference();
	/// @see SetFrameOfReference
	const FrameOfReference* GetFrameOfReference()const;

	/// DX Image [required]
	bool SetImage(const DXTypes::DXImage &image);
	/// @see SetImage
	bool GetImage(DXTypes::DXImage &image)const;
	/// @see SetImage
	DXTypes::DXImage& GetImage();
	/// @see SetImage
	const DXTypes::DXImage& GetImage()const;

	/// DX Detector [required]
	bool SetDetector(const DXTypes::DXDetector &detector);
	/// @see SetDetector
	bool GetDetector(DXTypes::DXDetector &detector)const;
	/// @see SetDetector
	DXTypes::DXDetector& GetDetector();
	/// @see SetDetector
	const DXTypes::DXDetector& GetDetector()const;

	/// DX Positioning [optional]
	bool SetPositioning(const DXTypes::DXPositioning &pos);
	/// @see SetPositioning
	bool GetPositioning(DXTypes::DXPositioning &pos)const;
	/// Allocate Positioning
	void AllocatePositioning();
	/// @see SetPositioning
	DXTypes::DXPositioning* GetPositioning();
	/// @see SetPositioning
	const DXTypes::DXPositioning* GetPositioning()const;

	/// X-Ray Generation [required]
	bool SetXRayGeneration(const DXTypes::XRayGeneration &xrgen);
	/// @see SetXRayGeneration
	bool GetXRayGeneration(DXTypes::XRayGeneration &xrgen)const;
	/// @see SetXRayGeneration
	DXTypes::XRayGeneration& GetXRayGeneration();
	/// @see SetXRayGeneration
	const DXTypes::XRayGeneration& GetXRayGeneration()const;

	/// X-Ray Filtration [optional]
	bool SetXRayFiltration(const DXTypes::XRayFiltration &xrfilt);
	/// @see SetXRayFiltration
	bool GetXRayFiltration(DXTypes::XRayFiltration &xrfilt)const;
	/// Allocate X-Ray Filtration
	void AllocateXRayFiltration();
	/// @see SetXRayFiltration
	DXTypes::XRayFiltration* GetXRayFiltration();
	/// @see SetXRayFiltration
	const DXTypes::XRayFiltration* GetXRayFiltration()const;

	/// Overlay Plane Module [required if graphic annotation is present]
	bool SetOverlayPlane(const OverlayPlaneModule &plane);
	/// @see SetOverlayPlane
	bool GetOverlayPlane(OverlayPlaneModule &plane);
	/// Allocate Overlay Plane
	void AllocateOverlayPlane();
	/// @see SetOverlayPlane
	OverlayPlaneModule* GetOverlayPlane();
	/// @see SetOverlayPlane
	const OverlayPlaneModule* GetOverlayPlane()const;

	/// Image Histogram [optional]
	bool SetImageHistogram(const ImageHistogramModule &hist);
	/// @see SetImageHistogram
	bool GetImageHistogram(ImageHistogramModule &hist)const;
	/// Allocate Image Histogram
	void AllocateImageHistogram();
	/// @see SetImageHistogram
	ImageHistogramModule* GetImageHistogram();
	/// @see SetImageHistogram
	const ImageHistogramModule* GetImageHistogram()const;

	/// Acquisition Context [required]
	bool SetAcquisitionContext(const AcquisitionContextSequence &acqcontext);
	/// @see SetAcquisitionContext
	bool GetAcquisitionContext(AcquisitionContextSequence &acqcontext)const;
	/// @see SetAcquisitionContext
	AcquisitionContextSequence& GetAcquisitionContext();
	/// @see SetAcquisitionContext
	const AcquisitionContextSequence& GetAcquisitionContext()const;

	/// TIP Image [required if the image is a TIP image]
	bool SetTipImage(const TipImage &tipimage);
	/// @see SetTipImage
	bool GetTipImage(TipImage &tipimage)const;
	/// Allocate TIP Image
	void AllocateTipImage();
	/// @see SetTipImage
	TipImage* GetTipImage();
	/// @see SetTipImage
	const TipImage* GetTipImage()const;

	/// Basic Pixel Spacing Calibration Macro [optional]
	bool SetBasicPixelSpacingCalibrationMacro(const BasicPixelSpacingCalibrationMacro &macro);
	/// @see SetBasicPixelSpacingCalibrationMacro
	bool GetBasicPixelSpacingCalibrationMacro(BasicPixelSpacingCalibrationMacro &macro)const;
	///  Allocate Basic Pixel Spacing Calibration Macro
	void AllocateBasicPixelSpacingCalibrationMacro();
	/// @see SetBasicPixelSpacingCalibrationMacro
	BasicPixelSpacingCalibrationMacro* GetBasicPixelSpacingCalibrationMacro();
	/// @see SetBasicPixelSpacingCalibrationMacro
	const BasicPixelSpacingCalibrationMacro* GetBasicPixelSpacingCalibrationMacro()const;
	
	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		Returns false if any required attribute is missing or invalid
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// If this class is valid, get a copy of the attributes
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		Returns false if any required attribute is invalid or not set.
	virtual bool GetAttributesAndValidate(AttributeManager &attribManager, ErrorLog &errorlog)const;

protected:
	class ImplDX;
	ImplDX	*m_pImplDX; ///< Internal implementation
	
	/// Hidden for internal use only
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;
	/// Hidden for internal use only
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
	/// Hidden for internal use only
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;
};

}//namespace SDICOS

#endif