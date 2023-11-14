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
#ifndef _STRATOVAN_DICOS_COMMUNICATIONS_HOST_H_
#define _STRATOVAN_DICOS_COMMUNICATIONS_HOST_H_

#include "SDICOS/ErrorLog.h"
#include "SDICOS/Utils.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/ModuleCT.h"
#include "SDICOS/ModuleAIT2D.h"
#include "SDICOS/ModuleAIT3D.h"
#include "SDICOS/ModuleDX.h"
#include "SDICOS/ModuleQR.h"
#include "SDICOS/ModuleTDR.h"
#include "SDICOS/UserCT.h"
#include "SDICOS/UserDX.h"
#include "SDICOS/UserAIT2D.h"
#include "SDICOS/UserAIT3D.h"
#include "SDICOS/UserQR.h"
#include "SDICOS/UserTDR.h"
#include "SDICOS/IReceiveCallback.h"
#include "SDICOS/IHost.h"
#include "SDICOS/IClientAuthentication.h"

namespace SDICOS
{
namespace Network
{

/// \class DcsServer
/// \brief The DICOS server uses the DICOM protocol for receiving data over a TCP/IP connection
class DcsServer : public IDcsServer
{
public:
	/// Constructor
	DcsServer();
	/// Destructor
	virtual ~DcsServer();

	/// Reset to default values
	virtual void FreeMemory();

	/// Set timeout for receiving and sending data. Default is 1000 ms.
	bool SetReadTimeoutInMilliseconds(const S_UINT32 nTimeoutMilliseconds = 1000);
	/// @see SetReadTimeoutInMilliseconds
	S_UINT32 GetReadTimeoutInMilliseconds()const;

	/// Set timeout for receiving and sending data. Default is 1000 ms.
	bool SetWriteTimeoutInMilliseconds(const S_UINT32 nTimeoutMilliseconds = 1000);
	/// @see SetWriteTimeoutInMilliseconds
	S_UINT32 GetWriteTimeoutInMilliseconds()const;

	/// Set the server's IP address. Call this function if your device uses multiple IP addresses.
	/// Function can only be called when server is not listening.
	bool SetIP(const DcsString &ds);
	/// Returns the server's IP address
	DcsString GetIP()const;

	/// Set listening port.
	/// Function can only be called when server is not listening.
	bool SetPort(const S_INT32 nPort);
	/// @see SetPort
	S_INT32 GetPort()const;

	/// Set application name (i.e. Name of the application calling this function).
	/// This is a requirement for the DICOM protocol that can be used by clients connecting
	/// to this server for verification.
	/// Must be 16 or less characters
	bool SetApplicationName(const DcsApplicationEntity &ae);
	/// @see SetApplicationName
	DcsApplicationEntity GetApplicationName()const;

	/// Require verification of clients' application names
	void RequireApplicationNames();
	/// Allow connections from clients with any application name. 
	///	This is the default.
	bool IgnoreApplicationNames();
	/// Returns true if host accepts connections from the specified application
	bool IsConnectionFromApplicationEnabled(const DcsApplicationEntity &ae);

	/// Enable SSL connection with the provided certificate. Call before listening for connections.
	/// If the PFX file contains multiple certificates, only the first one will be used.
	/// @param dsFilenamePFX Name of the PFX file
	/// @param dsPassword Password for the PFX file
	/// @param &errorlog Error log
	/// @return true/false false if setting the certificate failed
	bool SetSslCertificate(const DcsString &dsFilenamePFX, const DcsString &dsPassword, ErrorLog &errorlog);

	/// Enable SSL connection with the provided certificate. Call before listening for connections.
	/// The certificate matching the common name dsCN will be loaded from the PFX file.
	/// This function should be used if the PFX file contains more than one certificate.
	/// @param dsFilenamePFX Name of the PFX file
	/// @param dsPassword Password for the PFX file
	/// @param dsCN Common Name for the certificate
	/// @param &errorlog Error log
	/// @return true/false false if setting the certificate failed
	bool SetSslCertificate(const DcsString &dsFilenamePFX, const DcsString &dsPassword, const DcsString &dsCN, ErrorLog &errorlog);

	/// Returns true if using an SSL connection; otherwise, returns false
	/// @see SetSslCertificate
	bool IsUsingSsl()const;

	/// Require incoming client connections to present a valid certificate.
	/// They are required by default.
	/// Must be called before SetSslCertificate() to take effect.
	void SetTLSClientCertificateRequired(bool bRequired);
	bool IsTLSClientCertificateRequired()const;

	/// Set the ciphers allowed for TLS connections
	/// The string is a comma delmited list of ciphers that are acceptable
	/// e.g., "TLS_AES_256_GCM_SHA384,TLS_CHACHA20_POLY1305_SHA256,TLS_AES_128_GCM_SHA256"
	/// @param dsAllowedCiphers A comma delimited list of ciphers to be used
	void SetSslAllowedCiphers(const DcsString & dsAllowedCiphers);

	/// Get the list of allowed ciphers for TLS connections
	/// @see SetSslAllowedCiphers
	DcsString GetSslAllowedCiphers()const;

	/// Get the currently used cipher for TLS connections
	/// @see SetSslAllowedCiphers
	DcsString GetTlsCipherSuite()const;

	/// Requires all clients to present no user name or passcode. This is the default setting.
	bool AllowAllCients();
	/// Requires all clients to present a valid user name
	bool RequireUserNameFromClient();
	/// Requires all clients to present a valid user name and passcode
	bool RequireUserNameAndPasscodeFromClient();

	/// Return true if the user name and passcode combination are valid
	bool IsValidUserNameAndPasscode(const DcsString &dsUserName, const DcsString &dsPasscode)const;
	/// Returns true if the user name is valid
	bool IsValidUserName(const DcsString &dsUserName)const;

	/// Set parameter to true to prioritize using compression transfer syntaxes for data
	/// transfers between the client and server. Otherwise, set the parameter to false
	/// to prioritize uncompressed data transfers between the client and server.
	void PrioritizeDataCompression(const bool bPrioritize);

	/// @see PrioritizeDataCompression
	bool IsPrioritizingDataCompression()const;

	/// Disable data compression transfer syntax.
	void DisableDataCompression();

	/// @see PrioritizeDataCompression
	/// @see DisableDataCompression
	bool IsDataCompressionDisabled()const;

	/// (Non-blocking call) Start the server to process DICOS data received by incoming client connections. 
	/// The server will continue to listen until StopListening() is called.
	/// This method processes incoming connections on a separate thread. Each unique connection starts a DICOS
	/// session, which is processed in its own thread. Received DICOS data is placed in a processing queue that invokes
	/// the callback interface. The callback function must exit before the processing queue can send more DICOS data.
	/// NOTE: Calling StartListening(), StopListening(), StartListening() close enough together can 
	/// trigger 'Address Already in Use' errors.
	/// @param icallback Callback interface. If the preferred API is set to Module-Level or User-Level API, the original Tag-Level data  (excluding pixel data) can be retrieved with DicosData::GetOriginalData() or DicosData::TakeOwnershipOriginal()
	/// @param pIClientVerificationCallback Callback interface for verifying client's user name and/or passcodes. Used only if the server is configured to require user names and/or passcodes.
	/// @param nPreferAPI Preferred API for callback
	/// @param bProcessDataOnSessionEnd	If set to true and using enumMethodUserAPI, the server will accumulate the data sent by the client. Once the DICOS session ends, the data will be placed into User-Level API objects. For CT and AIT 3D, if data was sent slice by slice, each slice will be placed into a single User-Level API.
	/// @return true/false false if unable to bind to the port
	/// @see StopListening
	/// @see UpdateCallback(IReceiveCallback &icallback)
	/// @see UpdateCallback(const RETRIEVE_METHOD nPreferAPI)
	bool StartListening(IReceiveCallback &icallback,
						IClientAuthenticationCallback *pIClientVerificationCallback = S_NULL,
						const RETRIEVE_METHOD nPreferAPI = DcsServer::enumMethodUserAPI,
						const bool bProcessDataOnSessionEnd = false);

	/// Updates the callback interface after StartListening() has been called
	/// @param icallback Callback interface to use
	/// @see StartListening
	bool UpdateCallback(IReceiveCallback &icallback);
	/// Updates the preferred callback API after StartListening() has been called
	/// @see StartListening
	bool UpdateCallback(const RETRIEVE_METHOD nPreferAPI);

	/// (Blocking call) Stop listening to port. Terminates all DICOS connections.
	void StopListening();
	/// Returns true if processing a command or is listening
	bool IsBusy()const;
	/// Returns true if host is idle (not listening or busy)
	bool IsIdle()const;
	/// Returns true if host is currently accepting new connections
	bool IsActivelyAcceptingConnections()const;

	/// Wait for the server thread to complete. StartListening() causes the server to enter a loop while it waits for connections. WaitForThreadToComplete will wait for that loop to complete indicating that the server is shutting down.
	void WaitForThreadToComplete();

	/// Terminate a connection with a client device using an A-Abort
	/// @param dsIP IP of client device
	bool TerminateConnectionWithDevice(const DcsString &dsIP);

	/// Get list of currently connected client devices
	/// @param vClientIPs Array of connected client IP addresses
	void GetConnectedDevices(Array1D<DcsString> &vClientIPs)const;

	/// Get list of currently connected client devices with active DICOS sessions
	/// @param vClientIPs Array of connected client IP addresses
	void GetConnectedDevicesWithActiveDicosSessions(Array1D<DcsString> &vClientIPs)const;

	/// Include an SOP class UID
	bool IncludeSopClassUID(const DcsUniqueIdentifier &uidSopClassUID);

	/// Resets allowed SOP class UID's to the defaults
	void ResetIncludedSopClassUIDs();

	/// Get list of supported SOP class UID's
	void GetListOfSupportedSopClassUIDs(Array1D<DcsUniqueIdentifier> &vSopClassUIDs)const;

	/// Sets the server to use custom allocators for derived user-level and module-level API classes
	void SetCustomAllocators(const SDICOS::Utils::APIAllocators &apiAllocators);

	/// Provide a memory manager for allocating & deallocating memory for the pixel data.
	/// The DICOS library will internally use the memory manager's allocator for each slice. When the pixel
	/// data is to be deleted, the SDK will use the memory manager's deallocator for each slice.
	///
	/// Thread Safety: All allocation and deallocation calls originate from a single thread.
	///
	/// This value is not reset with FreeMemory()
	void SetMemoryManager(IMemoryManager *pMemMgr);
	/// @see SetMemoryManager
	bool HasMemoryManager()const;

	/// Return server's error log
	void GetErrorLog(DcsString &dsErrorLog)const;
protected:
	class DcsServerImpl;
	DcsServerImpl *m_pDcsServerImpl;
	
private:
	/// Disabled
	DcsServer(const DcsServer &host);
	/// Disabled
	DcsServer& operator=(const DcsServer &host);
};

}//namespace Network
}//namespace SDICOS

#endif