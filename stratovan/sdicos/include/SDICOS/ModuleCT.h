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
#ifndef _STRATOVAN_DICOS_CT_H_
#define _STRATOVAN_DICOS_CT_H_

#include "SDICOS/ScannerCommon.h"
#include "SDICOS/CTSeries.h"
#include "SDICOS/CTImage.h"
#include "SDICOS/CTMultiframeFunctionalGroups.h"
#include "SDICOS/AcquisitionContextModule.h"
#include "SDICOS/MultiframeDimensionModule.h"
#include "SDICOS/FrameOfReference.h"
#include "SDICOS/TipImage.h"
#include "SDICOS/DicosFile.h"
#include "SDICOS/XRayEquipmentModule.h"

namespace SDICOS
{

///
/// \class CTModule
/// \brief Implements CT IOD
/// SPECREF V03 Section 7.3, Table 17
///
/// Note: This class is not thread safe
///	DICOS SOP Class Name and UID:
///		Name:	"DICOS CT Image Storage"	
///		UID:	"1.2.840.10008.5.1.4.1.1.501.1"
///
class CTModule : public ScannerCommon
{
public:
	/// Constructor
	CTModule();
	/// Copy constructor
	CTModule(const CTModule &ct);
	/// Destructor
	~CTModule();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	CTModule& operator=(const CTModule &ct);
	/// Comparison operator
	bool operator==(const CTModule &ct)const;
	/// Comparison operator
	bool operator!=(const CTModule &ct)const;

	/// Read file
	/// @param filename Name of file to read from
	/// @param errorlog Error log
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	bool Read(const Filename &filename, ErrorLog &errorlog, IMemoryManager *pMemMgr = S_NULL);
	/// Read file and provide a manager of unknown attributes (Uses AttributeManager::enumNotSearchedOnly as filter).
	/// Known sequences containing unknown attributes are included as hierarchy references
	/// @param filename Name of file to read from
	/// @param errorlog Error log
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
	/// @param filename Name of file to write to
	/// @param nSyntax Transfer syntax to use
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

	/// Write a list of DICOS attributes as text to file
	bool WriteAttributeList(const Filename &filename, ErrorLog &errorlog)const;

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

	///
	/// Initialize with attributes from an attribute manager
	///
	bool Init(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	bool IsValid(ErrorLog &errorlog)const;

	/// CT Series Module [required]
	bool SetSeries(const CTTypes::CTSeries &ctseries);
	/// @see SetSeries
	bool GetSeries(CTTypes::CTSeries &ctseries)const;
	/// @see SetSeries
	CTTypes::CTSeries& GetSeries();
	/// @see SetSeries
	const CTTypes::CTSeries& GetSeries()const;

	/// Frame of Reference [required]
	bool SetFrameOfReference(const FrameOfReference &frameofreference);
	/// @see SetFrameOfReference
	bool GetFrameOfReference(FrameOfReference &frameofreference)const;
	/// @see SetFrameOfReference
	FrameOfReference& GetFrameOfReference();
	/// @see SetFrameOfReference
	const FrameOfReference& GetFrameOfReference()const;

	/// XRay Equipment Module [required]
	bool SetXRayEquipment(const XRayEquipmentModule &xRayEquipment);
	/// @see SetXRayEquipment
	bool GetXRayEquipment(XRayEquipmentModule &xRayEquipment)const;
	/// @see SetXRayEquipment
	XRayEquipmentModule& GetXRayEquipment();
	/// @see SetXRayEquipment
	const XRayEquipmentModule& GetXRayEquipment()const;

	/// CT Image [required]
	bool SetCTImage(const CTTypes::CTImage &ctimage);
	/// @see SetCTImage
	bool GetCTImage(CTTypes::CTImage &ctimage)const;
	/// @see SetCTImage
	CTTypes::CTImage& GetCTImage();
	/// @see SetCTImage
	const CTTypes::CTImage& GetCTImage()const;

	/// Multiframe Functional Groups [required]
	bool SetMultiframeFunctionalGroups(const CTTypes::CTMultiframeFunctionalGroups &mfg);
	/// @see SetMultiframeFunctionalGroups
	bool GetMultiframeFunctionalGroups(CTTypes::CTMultiframeFunctionalGroups &mfg)const;
	/// @see SetMultiframeFunctionalGroups
	CTTypes::CTMultiframeFunctionalGroups& GetMultiframeFunctionalGroups();
	/// @see SetMultiframeFunctionalGroups
	const CTTypes::CTMultiframeFunctionalGroups& GetMultiframeFunctionalGroups()const;

	/// Multiframe Dimension [optional]
	bool SetMultiframeDimension(const MultiframeDimensionModule &mdm);
	/// @see SetMultiframeDimension
	bool GetMultiframeDimension(MultiframeDimensionModule &mdm)const;
	/// Allocate Multiframe Dimension
	void AllocateMultiframeDimension();
	/// @see SetMultiframeDimension
	MultiframeDimensionModule* GetMultiframeDimension();
	/// @see SetMultiframeDimension
	const MultiframeDimensionModule* GetMultiframeDimension()const;
	/// Delete Multiframe Dimension
	void DeleteMultiframeDimensionModule();

	/// Acquisition Context [required]
	bool SetAcquisitionContext(const AcquisitionContextSequence &acs);
	/// @see SetAcquisitionContext
	bool GetAcquisitionContext(AcquisitionContextSequence &acs)const;
	/// @see SetAcquisitionContext
	AcquisitionContextSequence& GetAcquisitionContext();
	/// @see SetAcquisitionContext
	const AcquisitionContextSequence& GetAcquisitionContext()const;

	/// TIP Image [required if the image is a TIP image]
	bool SetTipImage(const TipImage &tipimage);
	/// @see SetTipImage
	bool GetTipImage(TipImage &tipimage)const;
	/// Allocate TIP Image
	void AllocateTIPImage();
	/// @see SetTipImage
	TipImage* GetTipImage();
	/// @see SetTipImage
	const TipImage* GetTipImage()const;
	/// Delete TIP Image
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
	class ImplCT;
	ImplCT	*m_pImplCT; ///< Internal implementation

	/// Hidden for internal use only
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;
	/// Hidden for internal use only
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
	/// Hidden for internal use only
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;
};

}//namespace SDICOS

#endif
