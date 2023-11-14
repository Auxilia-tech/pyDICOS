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
#ifndef _STRATOVAN_DICOS_QR_H_
#define _STRATOVAN_DICOS_QR_H_

#include "SDICOS/QRSeries.h"
#include "SDICOS/QRMeasurements.h"
#include "SDICOS/ScannerCommon.h"
#include "SDICOS/InspectionSelectionCriteria.h"
#include "SDICOS/AcquisitionContextModule.h"
#include "SDICOS/TipImage.h"
#include "SDICOS/DicosFile.h"

namespace SDICOS
{

///
/// \class QRModule
/// \brief Implements QR IOD
/// SPECREF V03 Section 10.2, Table 59
///
/// Note: This class is not thread safe
/// DICOS SOP Class Name and UID:
/// 		Name:	"DICOS Quadrupole Resonance (QR) Storage"	
/// 		UID:	"1.2.840.10008.5.1.4.1.1.501.6"
///
///////////////////////////////////////////////////
///  Updated Tags
/// Instance Number : Tag (0020, 0013) [changed to 'required' from 'optional', found in 'SopCommonModule']
///////////////////////////////////////////////////
class QRModule : public ScannerCommon
{
public:
	/// Constructor
	QRModule();
	/// Copy constructor
	QRModule(const QRModule &qr);
	/// Destructor
	~QRModule();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	QRModule& operator=(const QRModule &qr);
	/// Comparison operator
	bool operator==(const QRModule &qr)const;
	/// Comparison operator
	bool operator!=(const QRModule &qr)const;

	/// Read file
	bool Read(const Filename &filename, ErrorLog &errorlog);
	///
	/// Read file and provides a manager of unknown attributes (Uses AttributeManager::enumNotSearchedOnly as filter)
	/// Known sequences containing unknown attributes are included as hierarchy references
	///
	/// @return true/false
	bool Read(const Filename &filename, ErrorLog &errorlog, AttributeManager &managerExcluded);
	/// Read from memory buffer
	/// @param membuffer Buffer to read from
	/// @param errorlog Error log
	/// @return true/false
	bool Read(MemoryBuffer &membuffer, ErrorLog &errorlog);
	/// Read from memory buffer and provide a manager of unknown attributes (Uses AttributeManager::enumNotSearchedOnly as filter).
	/// Known sequences containing unknown attributes are included as hierarchy references
	/// @param membuffer Memory Buffer that contains DICOS data. 
	/// @param errorlog Error log
	/// @param managerExcluded Manager with unknown or private attributes
	/// @return true/false
	bool Read(MemoryBuffer &membuffer, ErrorLog &errorlog, AttributeManager &managerExcluded);
	/// Read from memory file
	/// @param memfile Buffer to read from
	/// @param errorlog Error log
	/// @return true/false
	bool Read(MemoryFile &memfile, ErrorLog &errorlog);
	/// Read data from memory buffer using DICOM network protocol (i.e. C-Store)
	/// @param membuffer Buffer to read from
	/// @param strTransferSyntax Transfer syntax to use while reading
	/// @param errorlog Error log
	/// @return true/false
	bool ReadForNetworkProtocol(MemoryFile &membuffer, const DcsString &strTransferSyntax, ErrorLog &errorlog);

	/// Write file
	/// @return Returns false if IsValid() fails
	bool Write(const Filename &filename, const DicosFile::TRANSFER_SYNTAX nSyntax, ErrorLog &errorlog);
	/// Write file to memory buffer
	/// @param membuffer Output memory buffer
	/// @param strTransferSyntax Transfer syntax to use
	/// @param errorlog Error log
	/// @return Returns false if IsValid() fails
	bool Write(MemoryBuffer &membuffer, const DicosFile::TRANSFER_SYNTAX strTransferSyntax, ErrorLog &errorlog);
	/// Write file to memory file
	/// @param memfile Output memory buffer
	/// @param strTransferSyntax Transfer syntax to use
	/// @param errorlog Error log
	/// @return Returns false if IsValid() fails
	bool Write(MemoryFile &memfile, const DicosFile::TRANSFER_SYNTAX strTransferSyntax, ErrorLog &errorlog);
	/// Write data to memory buffer for DICOM network protocol (i.e. C-Store)
	/// @param membuffer Output memory buffer
	/// @param strTransferSyntax Transfer syntax to use
	/// @param errorlog Error log
	/// @return Returns false if IsValid() fails
	bool WriteForNetworkProtocol(MemoryFile &membuffer, const DicosFile::TRANSFER_SYNTAX strTransferSyntax, ErrorLog &errorlog);

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

	/// QR Series [required]
	bool SetSeries(const QRTypes::QRSeries &series);
	/// @see SetSeries
	bool GetSeries(QRTypes::QRSeries &series)const;
	/// @see SetSeries
	QRTypes::QRSeries& GetSeries();
	/// @see SetSeries
	const QRTypes::QRSeries& GetSeries()const;

	/// Inspection Selection Criteria [required]
	bool SetInspectionSelectionCriteria(const InspectionSelectionCriteria &isc);
	/// @see SetInspectionSelectionCriteria
	bool GetInspectionSelectionCriteria(InspectionSelectionCriteria &isc)const;
	/// @see SetInspectionSelectionCriteria
	InspectionSelectionCriteria& GetInspectionSelectionCriteria();
	/// @see SetInspectionSelectionCriteria
	const InspectionSelectionCriteria& GetInspectionSelectionCriteria()const;

	/// QR Measurements [required]
	bool SetQRMeasurements(const QRTypes::QRMeasurements &qrmeasurements);
	/// @see SetQRMeasurements
	bool GetQRMeasurements(QRTypes::QRMeasurements &qrmeasurements)const;
	/// @see SetQRMeasurements
	QRTypes::QRMeasurements& GetQRMeasurements();
	/// @see SetQRMeasurements
	const QRTypes::QRMeasurements& GetQRMeasurements()const;

	/// Acquisition Context [required]
	bool SetAcquisitionContext(const AcquisitionContextSequence &acquisitioncontextsequence);
	/// @see SetAcquisitionContext
	bool GetAcquisitionContext(AcquisitionContextSequence &acquisitioncontextsequence)const;
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
	class ImplQR;
	ImplQR	*m_pImplQR; ///< Internal implementation
	
	/// Hidden for internal use only
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;
	/// Hidden for internal use only
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);
	/// Hidden for internal use only
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;
};

}//namespace SDICOS

#endif
