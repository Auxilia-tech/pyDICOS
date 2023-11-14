//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2015 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_SDCS_TEMPLATE_QR_H_
#define	_STRATOVAN_DICOS_SDCS_TEMPLATE_QR_H_

#include "SDICOS/DicosFile.h"
#include "SDICOS/SopClassUID.h"
#include "SDICOS/TemplateBase.h"
#include "SDICOS/ModuleQR.h"
#include "SDICOS/AcquisitionContextUser.h"

namespace SDICOS
{

///
/// \class QR
/// \brief Represents a Quadrupole Resonance (QR) 
/// 
/// The QR class is not thread safe.
///
/// The SDICOS::QR class abstracts away the hierarchy of the DICOS specification 
/// and provides an API that contains methods for setting the attributes needed for a DICOS QR object.
///
class QR :	public IODCommon,
			public ScanCommon,
			public AcquisitionContextUser
{
public:
	/// Default constructor
	QR();
	/// Copy constructor
	QR(const QR &qr);
	/// Destructor
	virtual ~QR();

	/// Copy operator
	QR& operator=(const QR &qr);

	/// Reset to default values
	virtual void FreeMemory();

	/// Comparison operator
	bool operator==(const QR &qr)const;
	/// Comparison operator
	bool operator!=(const QR &qr)const;

	/// Initialize with a QR object
	/// @param qr QR to initialize from
	/// @param errorlog Error Log
	/// @param bMoveData true: Move data out of the passed in C-Move-RSP. false: Copy data.
	bool Initialize(const QRModule &qr, ErrorLog &errorlog, const bool bMoveData = false);

	/// Write to file
	virtual bool Write(const Filename &filename, ErrorLog &errorlog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG)const;
	/// Write to memory file
	virtual bool Write(MemoryFile &memfile, ErrorLog &errorlog, const DicosFile::TRANSFER_SYNTAX nTransferSyntax = DicosFile::enumLosslessJPEG)const;

	/// Convenience method to read a series that contains a single file
	/// @param filename Filename for the file to be read
	/// @param errorLog Errorlog to store read errors
	/// @param pMemMgr Currently not used in QR
	virtual bool Read(const Filename &filename, ErrorLog &errorLog, IMemoryManager *pMemMgr = S_NULL);
	/// Read from a memory file
	/// @param memfile Memory file to read
	/// @param errorLog Errorlog to store read errors
	/// @param pMemMgr Currently not used in QR
	virtual bool Read(MemoryFile &memfile, ErrorLog &errorLog, IMemoryManager *pMemMgr = S_NULL);

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

	/// Returns enumQR
	virtual MODALITY GetModality()const;

	/// Sets inspection selection criteria to random
	void SetInspectionRandom();
	/// Sets inspection selection criteria to behavioral
	void SetInspectionBehavioral();
	/// Sets inspection selection criteria to random and behavioral
	void SetInspectionRandomAndBehavioral();

	/// @see SetInspectionRandom
	bool IsInspectionRandomOnly()const;
	/// @see SetInspectionRandom
	bool IsInspectionBehavioralOnly()const;
	/// @see SetInspectionRandomAndBehavioral
	bool IsInspectionRandomAndBehavioral()const;

	/// Set date and time measurements were taken.
	/// Default set to SDICOS::DcsDate::Today() and SDICOS::DcsTime::Now()
	void SetMeasurementsDateAndTime(const SDICOS::DcsDate &dsDate, const SDICOS::DcsTime &dsTime);
	/// @see SetMeasurementsDateAndTime
	DcsDate GetMeasurementsDate()const;
	/// @see SetMeasurementsDateAndTime
	DcsTime GetMeasurementsTime()const;
	
	/// Set Instance Number to identify this QR object.
	/// @param nInstanceNumber A number that identifies this image. Default value is 0.
	void SetInstanceNumber(const S_INT32 nInstanceNumber);
	/// @see SetInstanceNumber
	S_INT32 GetInstanceNumber()const;

	/// This structure represents a single QR measurement
	struct QRMeasurement
	{
		QRMeasurement();
		QRMeasurement(const QRMeasurement &qrm);
		QRMeasurement& operator=(const QRMeasurement &qrm);

		/// Comparison operator
		bool operator==(const QRMeasurement &measurement)const;
		/// Comparison operator
		bool operator!=(const QRMeasurement &measurement)const;

		/// The bounding polygon that contains the target material. A polygon of 2 points 
		/// is interpreted as opposite corners of a bounding box
		SDICOS::Array1D< SDICOS::Point3D<float> >	m_vBoundingPolygon;

		/// Signal-to-Noise ratio of the target material's frequency peak.
		/// Default is 0
		float	m_fSignalToNoiseRatio;

		/// Threshold to determine if target material is present. Values above the threshold indicate
		/// the target material's presence.
		/// Default is 0
		double	m_fSNRThreshold;

		/// Target material represented with the standard InChI (International Chemical Identifier) key
		SDICOS::DcsLongString	m_dsTargetMaterialInChIKey;
		/// Target material represented with the standard InChI (International Chemical Identifier) compound
		SDICOS::DcsLongString	m_dsTargetMaterialInChICompound;
	};

	/// Add a measurement
	void AddMeasurement(const QRMeasurement &measurement);
	/// Get the total number of measurements
	SDICOS::S_UINT32 GetNumberOfMeasurements()const;
	/// Retrieve a measurement
	/// @param nIndex Index of measurement to get
	/// @param measurement Place to store QR measurement data
	/// @return true/false
	bool GetMeasurement(const SDICOS::S_UINT32 nIndex, QRMeasurement &measurement)const;
	/// Replace or update a measurement
	/// @param measurement Place to store QR measurement data
	/// @param nIndex Index of measurement to set
	/// @return true/false
	bool SetMeasurement(const SDICOS::S_UINT32 nIndex, const QRMeasurement &measurement);

	/// Returns SOP Class UID
	virtual DcsUniqueIdentifier GetSopClassUID()const;

protected:

	/// Override to allocate a derived module-level API object.
	/// By default allocates QRModule.  This module is internally
	/// used for reading, writing, and networking.
	/// @return Dynamically allocated module-level API object
	virtual QRModule* AllocateModule()const;

	/// Override this function to set attributes in the SDICOS::QR object that are not set with QR
	/// WriteDerived_internal is called by the QR::Write() methods before attributes in the QR class are written.
	/// If the derived class wishes to further restrict values 
	/// @param qr QR object to set new values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors writing data
	virtual bool WriteDerived_internal(SDICOS::QRModule  &qr, ErrorLog &errorlog)const;

	/// Override this function to retrieve attributes from the SDICOS::QR object that are not retrieved by QR
	/// ReadDerived_internal is called by QR::Read() methods before attributes in the QR class are read.
	/// @param qr QR object to retrieve read values
	/// @param errorlog Error log
	/// @return true/false	false if there were errors reading data
	virtual bool ReadDerived_internal(const SDICOS::QRModule &qr, ErrorLog &errorlog);

	/// Do not allow reading multiple TDRs at once
	virtual bool Read(const DicosFileListing::SopInstance&, Array1D< std::pair<Filename, ErrorLog> > &, IMemoryManager *pMemMgr = S_NULL);

	/// Do not allow writing multiple TDRs at once.
	virtual bool Write(const Filename &, Array1D< std::pair<Filename, ErrorLog> > &, const DicosFile::TRANSFER_SYNTAX);

	class QRImpl;
	QRImpl	*m_pQRImpl;
};

}	//namespace SDICOS

#endif
