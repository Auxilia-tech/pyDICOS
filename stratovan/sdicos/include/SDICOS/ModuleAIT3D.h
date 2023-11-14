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
#ifndef _STRATOVAN_DICOS_AIT_3D_H_
#define _STRATOVAN_DICOS_AIT_3D_H_

#include "SDICOS/ScannerCommon.h"
#include "SDICOS/AcquisitionContextModule.h"
#include "SDICOS/MultiframeDimensionModule.h"
#include "SDICOS/FrameOfReference.h"
#include "SDICOS/TipImage.h"
#include "SDICOS/AIT3DSeries.h"
#include "SDICOS/AIT3DImage.h"
#include "SDICOS/AIT3DMultiframeFunctionalGroups.h"
#include "SDICOS/InspectionSelectionCriteria.h"
#include "SDICOS/TipImage.h"
#include "SDICOS/DicosFile.h"

namespace SDICOS
{

///
/// \class AIT3DModule
/// \brief Implements 3D AIT Image IOD
/// SPECREF V03 Section 9.3.2, Table 45
///
/// Note: This class is not thread safe
/// DICOS SOP Class Name and UID:
/// 		Name:	"DICOS 3D AIT Storage"	
/// 		UID:	"1.2.840.10008.5.1.4.1.1.501.5"
///
class AIT3DModule : public ScannerCommon
{
public:
	/// Constructor
	AIT3DModule();
	/// Copy constructor
	AIT3DModule(const AIT3DModule &ait);
	/// Destructor
	~AIT3DModule();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	AIT3DModule& operator=(const AIT3DModule &ait);
	/// Comparison operator
	bool operator==(const AIT3DModule &ait)const;
	/// Comparison operator
	bool operator!=(const AIT3DModule &ait)const;

	/// Read file
	/// @param filename Filename to be read
	/// @param errorlog Errorlog to store read errors
	/// @param pMemMgr Memory manager for custom pixel data allocation
	/// @see AttributeManager::SetPixelDataMemoryManager
	bool Read(const Filename &filename, ErrorLog &errorlog, IMemoryManager *pMemMgr = S_NULL);
	///
	/// Read file and provide a manager of unknown attributes (Uses AttributeManager::enumNotSearchedOnly as filter)
	/// Known sequences containing unknown attributes are included as hierarchy references
	///
	/// @param filename Filename to be read
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

	/// Write a list of DICOS attributes as text to file
	bool WriteAttributeList(const Filename &filename, ErrorLog &errorlog)const;

	/// Initialize with attributes from an attribute manager
	bool Init(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set.
	bool IsValid(ErrorLog &errorlog)const;

	/// 3D AIT Series [required]
	bool SetSeries(const AIT3DTypes::AIT3DSeries &series);
	/// @see SetSeries
	bool GetSeries(AIT3DTypes::AIT3DSeries &series)const;
	/// @see SetSeries
	AIT3DTypes::AIT3DSeries& GetSeries();
	/// @see SetSeries
	const AIT3DTypes::AIT3DSeries& GetSeries()const;

	/// Inspection Selection Criteria Module [required]
	bool SetInspectionSelectionCriteria(const InspectionSelectionCriteria &inspectionselectioncriteria);
	/// @see SetInspectionSelectionCriteria
	bool GetInspectionSelectionCriteria(InspectionSelectionCriteria &inspectionselectioncriteria)const;
	/// @see SetInspectionSelectionCriteria
	InspectionSelectionCriteria& GetInspectionSelectionCriteria();
	/// @see SetInspectionSelectionCriteria
	const InspectionSelectionCriteria& GetInspectionSelectionCriteria()const;

	/// Frame of Reference [required]
	bool SetFrameOfReference(const FrameOfReference &frameofreference);
	/// @see SetFrameOfReference
	bool GetFrameOfReference(FrameOfReference &frameofreference)const;
	/// @see SetFrameOfReference
	FrameOfReference& GetFrameOfReference();
	/// @see SetFrameOfReference
	const FrameOfReference& GetFrameOfReference()const;

	/// Multiframe Functional Groups [required]
	bool SetMultiframeFunctionalGroups(const AIT3DTypes::AIT3DMultiframeFunctionalGroups &mfg);
	/// @see SetMultiframeFunctionalGroups
	bool GetMultiframeFunctionalGroups(AIT3DTypes::AIT3DMultiframeFunctionalGroups &mfg)const;
	/// @see SetMultiframeFunctionalGroups
	AIT3DTypes::AIT3DMultiframeFunctionalGroups& GetMultiframeFunctionalGroups();
	/// @see SetMultiframeFunctionalGroups
	const AIT3DTypes::AIT3DMultiframeFunctionalGroups& GetMultiframeFunctionalGroups()const;

	/// Multiframe Dimension [optional]
	bool SetMultiframeDimension(const MultiframeDimensionModule &multiframedimension);
	/// @see SetMultiframeDimension
	bool GetMultiframeDimension(MultiframeDimensionModule &multiframedimension)const;
	/// Allocate Multiframe Dimension
	void AllocateMultiframeDimension();
	/// @see SetMultiframeDimension
	MultiframeDimensionModule* GetMultiframeDimension();
	/// @see SetMultiframeDimension
	const MultiframeDimensionModule* GetMultiframeDimension()const;
	/// Delete Multiframe Dimension
	void DeleteMultiframeDimensionModule();

	/// Acquisition Context [required]
	bool SetAcquisitionContext(const AcquisitionContextSequence &acqcontext);
	/// @see SetAcquisitionContext
	bool GetAcquisitionContext(AcquisitionContextSequence &acqcontext)const;
	/// @see SetAcquisitionContext
	AcquisitionContextSequence& GetAcquisitionContext();
	/// @see SetAcquisitionContext
	const AcquisitionContextSequence& GetAcquisitionContext()const;
	
	/// 3D AIT Image [required]
	bool SetImage(const AIT3DTypes::AIT3DImage &image);
	/// @see SetImage
	bool GetImage(AIT3DTypes::AIT3DImage &image)const;
	/// @see SetImage
	AIT3DTypes::AIT3DImage& GetImage();
	/// @see SetImage
	const AIT3DTypes::AIT3DImage& GetImage()const;

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
	class ImplAIT3D;
	ImplAIT3D	*m_pImplAIT3D; ///< Internal implementation
	
	/// Hidden for internal use only
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;
	/// Hidden for internal use only
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
	/// Hidden for internal use only
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;
};

}//namespace SDICOS

#endif