//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2019 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_COMMUNICATIONS_CLIENT_MANAGER_H_
#define _STRATOVAN_DICOS_COMMUNICATIONS_CLIENT_MANAGER_H_

#include "SDICOS/Client.h"

namespace SDICOS
{

class AIT2D;
class AIT3D;
class CT;
class DX;
class QR;
class TDR;

namespace Network
{
	
/// \class DcsClientManager
/// \brief	Handles sending DICOS files to all managed clients. This class maintains a buffer to reduce allocation/deallocation times
///			incurred by sending the same file to multiple targets. The user can provide and reclaim this buffer.
class DcsClientManager
{
public:
	DcsClientManager();
	virtual ~DcsClientManager();

	/// Provide a preallocated buffer for internal use. This object gains ownership of the buffer.
	/// Buffer may increase in size if too small, but is never decreased. Call RemoveBuffer() to remove the buffer 
	/// from this object and take ownership over it.
	/// @param mbMessage User provided buffer for the internal C-Store message
	/// @return Returns true if buffer is set. Returns false if currently sending data and buffer is not set.
	/// @see RemoveBuffer
	bool SetBuffer(MemoryBuffer &mbMessage);
	/// Remove the buffer provided in SetBuffer() or the buffer internally allocated and gain ownership over it.
	/// Calling this function and then Store() will cause the internal buffer to reallocate.
	/// @see SetBuffer
	bool RemoveBuffer(MemoryBuffer &mbMessage);

	/// Manage multiple clients. Makes internal copies of clients. All clients must not be connected to DICOS servers and 
	/// must already be valid. Does not copy SSL settings; use DcsClientManager::SetSslCertificate.
	/// Use this object to manage server connection and DICOS sessions
	bool ManageClients(const std::vector<DcsClient*> &vpClient, ErrorLog &errorlog);
	/// Add a client to manage. Makes internal copy of client. Client must not be connected to DICOS servers and 
	/// must already be valid.
	/// Use this object to manage server connection and DICOS sessions
	bool ManageClient(const DcsClient &client, ErrorLog &errorlog);
	/// Remove all clients
	bool RemoveAllClients();
	/// Returns number of clients
	S_UINT32 GetNumClients()const;
	/// Returns pointer to client
	const DcsClient* GetClient(const S_UINT32 nClient)const;

	/// Calls PrioritizeDataCompression() on all managed DcsClients
	/// @see SDICOS::Network::DcsClient::PrioritizeDataCompression
	void PrioritizeDataCompression(const bool bPrioritize);

	/// Returns true if all clients are prioritizing compression
	/// @see PrioritizeDataCompression
	bool AreAllPrioritizingDataCompression()const;

	/// Disable data compression for all managed DcsClients.
	void DisableDataCompression();

	/// @see PrioritizeDataCompression
	/// @see DisableDataCompression
	bool IsDataCompressionDisabled()const;

	/// Set port and IP address of target device.
	/// Returns false if client is currently connected to a server.
	/// @param nClient DcsClient object index
	/// @param nPort Port to set
	/// @param dsIP IP to set
	bool SetServerPortandIP(const S_UINT32 nClient, const S_INT32 nPort, const DcsString &dsIP);
	/// @param nClient DcsClient object index
	/// @see SetPortandIP
	S_INT32 GetPort(const S_UINT32 nClient)const;
	/// @param nClient DcsClient object index
	/// @see SetPortandIP
	DcsString GetServerIP(const S_UINT32 nClient)const;

	/// Set the IP address of the client. Call this function if your device uses multiple IP addresses.
	/// Returns false if client is currently connected to a server.
	/// @param nClient DcsClient object index
	/// @param dsIP IP to set 
	bool SetClientIP(const S_UINT32 nClient, const DcsString &dsIP);
	/// @param nClient DcsClient object index
	/// @see SetClientIP
	DcsString GetClientIP(const S_UINT32 nClient)const;

	/// Set timeout for receiving and sending data. Default is 1000 ms.
	/// @param nClient DcsClient object index
	/// @param nTimeoutMilliseconds Time in milliseconds to set the timeout to
	bool SetReadTimeoutInMilliseconds(const S_UINT32 nClient, const S_UINT32 nTimeoutMilliseconds = 1000);
	/// @param nClient DcsClient object index
	/// @see SetReadTimeoutInMilliseconds
	S_UINT32 GetReadTimeoutInMilliseconds(const S_UINT32 nClient)const;

	/// Set timeout for receiving and sending data. Default is 1000 ms.
	/// @param nClient DcsClient object index
	/// @param nTimeoutMilliseconds Time in milliseconds to set the timeout to
	bool SetWriteTimeoutInMilliseconds(const S_UINT32 nClient, const S_UINT32 nTimeoutMilliseconds = 1000);
	/// @param nClient DcsClient object index
	/// @see SetWriteTimeoutInMilliseconds
	S_UINT32 GetWriteTimeoutInMilliseconds(const S_UINT32 nClient)const;

	/// Enables SSL connection with the provided certificate. Call before connecting to a server.
	/// @param nClient DcsClient object index
	/// @param dsFilenamePFX Name of the PFX file
	/// @param dsPassword Password for the PFX file
	/// @param dsCN Common Name for the certificate
	/// @param &errorlog Error log
	/// @return true/false false if setting the certificate failed
	bool SetSslCertificate(const S_UINT32 nClient, const DcsString &dsFilenamePFX, const DcsString &dsPassword, const DcsString &dsCN, ErrorLog &errorlog);

	/// Enable SSL connection with the provided public key certificate. Call before connecting to a server.
	/// Loads a certificate from a.cer, .crt, .p7b, or .pem file.
	/// This method accepts certificates from files in any of the following formats:
	///   1. DER encoded binary X.509 (.CER)
	///   2. Base - 64 encoded X.509 (.CER)
	///   3. Cryptographic Message Syntax Standard - PKCS #7 Certificates(.P7B)
	///   4. PEM format
	/// @param nClient DcsClient object index
	/// @param dsFilenameCert The file with the server's public key for SSL connections to a DICOS Server
	/// @param errorlog Error log
	/// @return true/false;
	bool SetSslCertificate(const S_UINT32 nClient, const DcsString &dsFilenameCert, ErrorLog& errorlog);

	/// Enable or disable automatic SSL connections with or without a client certificate
	/// for the next time the client tries to establish a connection to a server.
	/// If set to false, a non SSL connection will be use even if a valid certificate is set
	/// by a call to SetSslCertificate(...)
	/// Note that IsUsingSsl() may return false until an actual Ssl connection is made by the socket.
	/// @param nClient DcsClient object index
	/// @param bEnableSsl true/false Enable or disable Ssl the next time the client tries to connect to a server
	void EnableSsl(const S_UINT32 nClient, const bool bEnableSsl);

	/// Returns true if using an SSL connection; otherwise, returns false
	/// @param nClient DcsClient object index
	/// @see SetSslCertificate
	bool IsUsingSsl(const S_UINT32 nClient)const;

	/// Set the name of the application sending data. Must be 16 or less characters
	/// This is a requirement for the DICOM protocol that can be used by the server for verification.
	/// @param nClient DcsClient object index
	/// @param aeSrc Name of source application that is sending DICOS files.
	/// @return true/false false if aeSrc is not a valid DcsApplicationEntity string.
	bool SetSourceApplication(const S_UINT32 nClient, const DcsApplicationEntity &aeSrc);
	/// @param nClient DcsClient object index
	/// @see SetSourceApplication
	DcsApplicationEntity GetSourceApplication(const S_UINT32 nClient)const;

	/// Set the name of the application receiving data. Must be 16 or less characters.
	/// This value will take effect in the next DICOS session and not in a current open DICOS session.
	/// This is a requirement for the DICOM protocol that can be used by clients to verify the server.
	/// @param nClient DcsClient object index
	/// @param aeDst Name of destination application that is receiving DICOS files.
	/// @return true/false false if aeDst is not a valid DcsApplicationEntity string.
	bool SetDestinationApplication(const S_UINT32 nClient, const DcsApplicationEntity &aeDst);
	/// @param nClient DcsClient object index
	/// @see SetDestinationApplication
	DcsApplicationEntity GetDestinationApplication(const S_UINT32 nClient)const;

	/// Set user name. Must be a non-empty string.
	/// This value will take effect in the next DICOS session and not in a current open DICOS session.
	/// @param nClient DcsClient object index
	/// @param dsUserName Name of user sending DICOS files
	/// @return true/false false if dsUserName is empty
	bool SetUserName(const S_UINT32 nClient, const DcsString &dsUserName);
	/// Set passcode and user name. Both must be a non-empty strings.
	/// This value will take effect in the next DICOS session and not in a current open DICOS session.
	/// @param nClient DcsClient object index
	/// @param dsPasscode Password to authenticate the user sending DICOS files with the Server
	/// @param dsUserName Name of the user sending DICOS files
	/// @return true/false false if dsUserName is empty
	bool SetPasscodeAndUserName(const S_UINT32 nClient, const DcsString &dsPasscode, const DcsString &dsUserName);
	/// Delete passcode and user name
	/// @param nClient DcsClient object index
	void DeletePasscodeAndUserName(const S_UINT32 nClient);

	/// Establishes a TCP/IP connection with a DICOS server for each client. Skips clients already connected to servers.
	/// All clients should be initialized before calling ConnectToServers.
	/// @return Returns number of clients that successfully connected
	/// @see IsConnectedToServer
	S_UINT32 ConnectToServers(ErrorLog &errorlog);
	/// Disconnects the TCP/IP connection from all DICOS servers. If a session is in progress, this will wait until it is completed before disconnecting.
	/// This must be called before starting a new DICOS session after calling StopDicosSession().
	/// @see StopDicosSessions
	void DisconnectFromServers();
	/// Returns true if all clients are connected with DICOS servers
	bool AreAllConnectedToServers()const;
	/// Returns number of clients with active connections to their server
	S_UINT32 GetNumClientsConnectedToServers()const;
	/// Returns true if a client is connected with a DICOS server
	bool IsConnectedToServer(const S_UINT32 nClient)const;

	/// Starts a DICOS session on an established TCP/IP connection. Call after ConnectToServer().
	/// Skips clients not connected to servers and clients with currently active DICOS sessions.
	/// Once the session is complete, call StopDicosSession.
	/// @param nSopClassUIDs DcsClient::SOPCLASSUID enumerations to enable. Example: To enable echo, CT, and TDR call set this parameter to (enumSopEcho | enumSopCT | enumSopTDR)
	/// @param errorlog Errorlog to store session errors
	/// @return Returns number of clients that successfully started a DICOS session
	S_UINT32 StartDicosSessions(const S_UINT32 &nSopClassUIDs, ErrorLog &errorlog);
	/// End a DICOS sessions
	/// @see DisconnectFromServers
	void StopDicosSessions();
	/// Returns true if all clients DICOS sessions are in progress
	bool AreAllSessionsInProgress()const;
	/// Returns number of clients with active DICOS sessions
	S_UINT32 GetNumClientsWithSessionsInProgress()const;
	/// Returns true if a DICOS session is in progress
	bool IsSessionInProgress(const S_UINT32 nClient)const;

	/// Perform a C-Echo operation on all clients.
	/// If a connection or session is already in progress before this function is called, then that state is maintained 
	/// when this function exits.
	/// Timing metrics available in GetTimingMetrics
	/// @see GetTimingMetrics
	/// @return Returns false if IsValid() fails. Returns true if echo completed successfully.
	S_UINT32 Echo(ErrorLog &errorlog);

	/// \class ClientMetrics
	/// \brief Stores metrics info for calls to Store()
	class ClientMetrics
	{
	public:
		/// Constructor
		ClientMetrics();

		SDICOS::Utils::TimeStamp m_dtStart;///< Time stamp when event started
		S_UINT32	m_nDurationMilliSec;///< Amount of time in milliseconds taken to send the data
		DcsString	m_dsIpAndPort;///< "IP:Port" of receiving device
	};

	///////////////////////////////////////////////////////////
	//  Tag-Level API Store function

	/// Perform a C-Store operation for each managed client. All clients must already have DICOS sessions in progress.
	/// Timing metrics available in GetTimingMetrics
	/// @see GetTimingMetrics
	/// @param manager Attribute manager to store
	/// @param errorlog Errorlog to store c-store errors
	/// @return Number of clients that successfully sent data
	S_INT32 Store(AttributeManager &manager, ErrorLog &errorlog);

	///////////////////////////////////////////////////////////
	//  Module-Level API Store functions

	/// Perform a C-Store operation for each managed client. If a connection or session with all clients are already in 
	/// progress before this function is called, then that state is maintained when this function exits.
	/// @param ct CT object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(CTModule& ct, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. If a connection or session with all clients are already in 
	/// progress before this function is called, then that state is maintained when this function exits.
	/// @param ait2d AIT2D object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(AIT2DModule& ait2d, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. If a connection or session with all clients are already in 
	/// progress before this function is called, then that state is maintained when this function exits.
	/// @param ait3d AIT3D object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(AIT3DModule& ait3d, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. If a connection or session with all clients are already in 
	/// progress before this function is called, then that state is maintained when this function exits.
	/// @param dx DX object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(DXModule& dx, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. If a connection or session with all clients are already in 
	/// progress before this function is called, then that state is maintained when this function exits.
	/// @param qr QR object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(QRModule& qr, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. If a connection or session with all clients are already in 
	/// progress before this function is called, then that state is maintained when this function exits.
	/// @param tdr TDR object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(TDRModule& tdr, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	///////////////////////////////////////////////////////////
	//  User-Level API Store functions

	/// Perform a C-Store operation for each managed client. Call ConnectToServers() before calling this function. 
	/// Handles starting and stopping DICOS sessions if all clients have no sessions started. If not all clients 
	/// have active sessions, a session will start for those without active sessions and this function will not stop 
	/// any of the sessions. If all clients have active sessions, those session reamin active when this function exits.
	/// @param ct CT object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(CT& ct, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. Call ConnectToServers() before calling this function. 
	/// Handles starting and stopping DICOS sessions if all clients have no sessions started. If not all clients 
	/// have active sessions, a session will start for those without active sessions and this function will not stop 
	/// any of the sessions. If all clients have active sessions, those session reamin active when this function exits.
	/// @param ait2d AIT2D object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(AIT2D& ait2d, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. Call ConnectToServers() before calling this function. 
	/// Handles starting and stopping DICOS sessions if all clients have no sessions started. If not all clients 
	/// have active sessions, a session will start for those without active sessions and this function will not stop 
	/// any of the sessions. If all clients have active sessions, those session reamin active when this function exits.
	/// @param ait3d AIT3D object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(AIT3D& ait3d, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. Call ConnectToServers() before calling this function. 
	/// Handles starting and stopping DICOS sessions if all clients have no sessions started. If not all clients 
	/// have active sessions, a session will start for those without active sessions and this function will not stop 
	/// any of the sessions. If all clients have active sessions, those session reamin active when this function exits.
	/// @param dx DX object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(DX& dx, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. Call ConnectToServers() before calling this function. 
	/// Handles starting and stopping DICOS sessions if all clients have no sessions started. If not all clients 
	/// have active sessions, a session will start for those without active sessions and this function will not stop 
	/// any of the sessions. If all clients have active sessions, those session reamin active when this function exits.
	/// @param qr QR object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(QR& qr, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	/// Perform a C-Store operation for each managed client. Call ConnectToServers() before calling this function. 
	/// Handles starting and stopping DICOS sessions if all clients have no sessions started. If not all clients 
	/// have active sessions, a session will start for those without active sessions and this function will not stop 
	/// any of the sessions. If all clients have active sessions, those session reamin active when this function exits.
	/// @param tdr TDR object to store
	/// @param errorlog Error log
	/// @param vSendTimes The time in milliseconds to send data to the server "IP:Port"
	/// @return Number of clients that successfully sent data
	S_UINT32 Store(TDR& tdr, ErrorLog &errorlog, std::vector< ClientMetrics > &vSendTimes);

	///////////////////////////////////////////////////////////

	/// Get the timing metrics for the most recent call to Store()
	void GetTimingMetrics(std::vector<ClientMetrics> &vMetrics)const;
private:
	DcsClientManager(const DcsClientManager&);
	DcsClientManager& operator=(const DcsClientManager&);

	class Impl;
	Impl *m_pImpl; ///< Internal implementation
};

}//namespace Network
}//namespace SDICOS

#endif
