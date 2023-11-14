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
#ifndef _STRATOVAN_DICOS_AIT_2D_H_
#define _STRATOVAN_DICOS_AIT_2D_H_

#include "SDICOS/DicosFile.h"
#include "SDICOS/ScannerCommon.h"
#include "SDICOS/AcquisitionContextModule.h"
#include "SDICOS/ImagePixelModule.h"
#include "SDICOS/InspectionSelectionCriteria.h"
#include "SDICOS/OverlayPlaneModule.h"
#include "SDICOS/FrameOfReference.h"
#include "SDICOS/TipImage.h"
#include "SDICOS/AIT2DSeries.h"
#include "SDICOS/AIT2DImage.h"
#include "SDICOS/AIT2DFunctionalMacros.h"
#include "SDICOS/PaletteColorLookupTable.h"
#include "SDICOS/ImageHistogramModule.h"

namespace SDICOS
{
	
///
/// \class AIT2DModule
/// Implements 2D AIT IOD Module
/// SPECREF V03 Section 9.2.2, Table 40
///
/// Note: This class is not thread safe
/// DICOS SOP Class Name and UID:
///		Name:	"DICOS 2D AIT Storage"	
///		UID:	"1.2.840.10008.5.1.4.1.1.501.4"
///
/// Derives from ScannerCommon which contains the modules:
///		Owner
///		Object of Inspection
///		Itinerary
///		GeneralScanModule
///		GeneralEquipmentModule
///		SopCommonModule
///		CommonInstanceReferenceModule
///
class AIT2DModule : public ScannerCommon
{
public:
	/// Constructor
	AIT2DModule();
	
	/// Copy Constructor
	AIT2DModule(const AIT2DModule &ait);
	
	/// Destructor
	virtual ~AIT2DModule();

	/// Delete Allocated memory
	virtual void FreeMemory();

	/// Assignment operator
	AIT2DModule& operator=(const AIT2DModule &ait);
	
	/// equality comparison operator
	bool operator==(const AIT2DModule &ait)const;
	
	/// Inequality comparison operator
	bool operator!=(const AIT2DModule &ait)const;

	/// Read file
	/// @param filename Filename for the file to be read
	/// @param errorlog Errorlog to store read errors
	/// @param pMemMgr  Memory manager for custom pixel data allocation
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

	/// Initialize with attributes from an attribute manager
	bool Init(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Write a list of DICOS attributes as text to file
	bool WriteAttributeList(const Filename &filename, ErrorLog &errorlog)const;

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	bool IsValid(ErrorLog &errorlog)const;
	
	/// Set SOP Common [required]
	///'GetSopCommon' inherited from 'ScannerCommon'
	///		-Override to automatically set the correct SOP Class UID
	///		See SdcsSopClassUID.h
	virtual bool SetSopCommon(const SopCommonModule &sopcommon);
	
	/// Set General Series [required]
	bool SetSeries(const AIT2DTypes::AIT2DSeries &series);
	/// @see SetSeries
	bool GetSeries(AIT2DTypes::AIT2DSeries &series)const;
	/// @see SetSeries
	AIT2DTypes::AIT2DSeries& GetSeries();
	/// @see SetSeries
	const AIT2DTypes::AIT2DSeries& GetSeries()const;
	
	/// Set Inspection Selection Criteria Module [required]
	bool SetInspectionSelectionCriteria(const InspectionSelectionCriteria &isc);
	/// @see SetInspectionSelectionCriteria
	bool GetInspectionSelectionCriteria(InspectionSelectionCriteria &isc)const;
	/// @see SetInspectionSelectionCriteria
	InspectionSelectionCriteria& GetInspectionSelectionCriteria();
	/// @see SetInspectionSelectionCriteria
	const InspectionSelectionCriteria& GetInspectionSelectionCriteria()const;
	
	/// Set Frame of Reference [optional]
	bool SetFrameOfReference(const FrameOfReference &ref);
	/// @see SetFrameOfReference
	bool GetFrameOfReference(FrameOfReference &ref)const;
	/// Allocate Frame Of Reference
	void AllocateFrameOfReference();
	/// @see SetFrameOfReference
	FrameOfReference* GetFrameOfReference();
	/// @see SetFrameOfReference
	const FrameOfReference* GetFrameOfReference()const;
	/// Delete module so it is not written to the DICOS file
	void DeleteFrameOfReference();
	
	/// Set Image 2D AIT [required]
	bool SetImage(const AIT2DTypes::AIT2DImage &image);
	/// @see SetImage
	bool GetImage(AIT2DTypes::AIT2DImage &image)const;
	/// @see SetImage
	AIT2DTypes::AIT2DImage& GetImage();
	/// @see SetImage
	const AIT2DTypes::AIT2DImage& GetImage()const;
	
	/// Set 2D AIT Functional Macros [required]
	bool SetFunctionalMacros(const AIT2DTypes::AIT2DFunctionalMacros &macros);
	/// @see SetFunctionalMacros
	bool GetFunctionalMacros(AIT2DTypes::AIT2DFunctionalMacros &macros)const;
	/// @see SetFunctionalMacros
	AIT2DTypes::AIT2DFunctionalMacros& GetFunctionalMacros();
	/// @see SetFunctionalMacros
	const AIT2DTypes::AIT2DFunctionalMacros& GetFunctionalMacros()const;
	
	/// Set Overlay Plane Module [required if graphic annotation is preset]
	bool SetOverlayPlane(const OverlayPlaneModule &overlayplanemodule);
	/// @see SetOverlayPlane
	bool GetOverlayPlane(OverlayPlaneModule &overlayplanemodule)const;
	/// Allocate Overlay Plane
	void AllocateOverlayPlane();
	/// @see SetOverlayPlane
	OverlayPlaneModule* GetOverlayPlane();
	/// @see SetOverlayPlane
	const OverlayPlaneModule* GetOverlayPlane()const;
	/// Delete module so it is not written to the DICOS file
	void DeleteOverlayPlane();
	
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
	/// Delete module so it is not written to the DICOS file
	void DeleteImageHistogram();
	
	/// Set Acquisition Context [required]
	bool SetAcquisitionContext(const AcquisitionContextSequence &acqcontext);
	/// @see SetAcquisitionContext
	bool GetAcquisitionContext(AcquisitionContextSequence &acqcontext)const;
	/// @see SetAcquisitionContext
	AcquisitionContextSequence& GetAcquisitionContext();
	/// @see SetAcquisitionContext
	const AcquisitionContextSequence& GetAcquisitionContext()const;

	/// Set TIP Image [required if the image is a TIP image]
	bool SetTipImage(const TipImage &tipimage);
	/// @see SetTipImage
	bool GetTipImage(TipImage &tipimage)const;
	/// Allocate TIP Image
	void AllocateTipImage();
	/// @see SetTipImage
	TipImage* GetTipImage();
	/// @see SetTipImage
	const TipImage* GetTipImage()const;
	/// Delete module so it is not written to the DICOS file
	void DeleteTipImage();
	
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
	class ImplAIT2D;
	mutable ImplAIT2D	*m_pImplAIT2D; ///< Internal implementation
	
	ImplAIT2D* GetImpl();
	const ImplAIT2D* GetImpl() const;
	
	/// Hidden for internal use only
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;
	/// Hidden for internal use only
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
	/// Hidden for internal use only
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;
};

}//namespace SDICOS

#endif