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
#ifndef _STRATOVAN_DICOS_COMMUNICATIONS_CLIENT_H_
#define _STRATOVAN_DICOS_COMMUNICATIONS_CLIENT_H_

#include "SDICOS/Types.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/ModuleCT.h"
#include "SDICOS/ModuleAIT2D.h"
#include "SDICOS/ModuleAIT3D.h"
#include "SDICOS/ModuleDX.h"
#include "SDICOS/ModuleQR.h"
#include "SDICOS/ModuleTDR.h"
#include "SDICOS/IReceiveCallback.h"
#include "SDICOS/IClient.h"

namespace SDICOS
{
namespace Network
{

/// \class DcsClient
/// \brief DICOS client for sending data using the DICOM protocol over a TCP/IP connection
class DcsClient : public IClient
{
public:
	/// Constructor
	DcsClient();
	/// Copy constructor
	DcsClient(const DcsClient &client);
	/// Destructor
	virtual ~DcsClient();

	/// Copy operator
	DcsClient& operator=(const DcsClient &client);

	/// Reset to default values
	/// @return Returns false if a connection is still open. Returns true otherwise.
	virtual bool FreeMemory();

	/// Set port and IP address of target device.
	/// Returns false if client is currently connected to a server.
	bool SetServerPortandIP(const S_INT32 nPort, const DcsString &dsIP);
	/// @see SetPortandIP
	S_INT32 GetPort()const;
	/// @see SetPortandIP
	const DcsString& GetServerIP()const;

	/// Set the IP address of the client. Call this function if your device uses multiple IP addresses.
	/// Returns false if client is currently connected to a server.
	bool SetClientIP(const DcsString &dsIP);
	/// @see SetClientIP
	DcsString GetClientIP()const;

	/// Set timeout for receiving and sending data. Default is 1000 ms.
	bool SetReadTimeoutInMilliseconds(const S_UINT32 nTimeoutMilliseconds = 1000);
	/// @see SetReadTimeoutInMilliseconds
	S_UINT32 GetReadTimeoutInMilliseconds()const;

	/// Set timeout for receiving and sending data. Default is 1000 ms.
	bool SetWriteTimeoutInMilliseconds(const S_UINT32 nTimeoutMilliseconds = 1000);
	/// @see SetWriteTimeoutInMilliseconds
	S_UINT32 GetWriteTimeoutInMilliseconds()const;

	/// Enables SSL connection with the provided certificate. Call before connecting to a server.
	/// @param dsFilenamePFX Name of the PFX file
	/// @param dsPassword Password for the PFX file
	/// @param dsCN Common Name for the certificate
	/// @param &errorlog Error log
	/// @return true/false false if setting the certificate failed
	bool SetSslCertificate(const DcsString &dsFilenamePFX, const DcsString &dsPassword, const DcsString &dsCN, ErrorLog &errorlog);

	/// Enable SSL connection with the provided public key certificate. Call before connecting to a server.
	/// Loads a certificate from a.cer, .crt, .p7b, or .pem file.
	/// This method accepts certificates from files in any of the following formats:
	///   1. DER encoded binary X.509 (.CER)
	///   2. Base - 64 encoded X.509 (.CER)
	///   3. Cryptographic Message Syntax Standard - PKCS #7 Certificates(.P7B)
	///   4. PEM format
	/// @param dsFilenameCert The file with the server's public key for SSL connections to a DICOS Server
	/// @param errorlog Error log
	/// @return true/false;
	bool SetSslCertificate(const DcsString &dsFilenameCert, ErrorLog& errorlog);

	/// Enable or disable automatic SSL connections with or without a client certificate
	/// for the next time the client tries to establish a connection to a server.
	/// If set to false, a non SSL connection will be use even if a valid certificate is set
	/// by a call to SetSslCertificate(...)
	/// Note that IsUsingSsl() may return false until an actual Ssl connection is made by the socket.
	/// @param bEnableSsl true/false Enable or disable Ssl the next time the client tries to connect to a server
	void EnableSsl(const bool bEnableSsl);

	/// Returns true if using an SSL connection; otherwise, returns false
	/// @see SetSslCertificate
	bool IsUsingSsl()const;

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

	/// Set the name of the application sending data. Must be 16 or less characters
	/// This is a requirement for the DICOM protocol that can be used by the server for verification.
	/// @param aeSrc Name of source application that is sending DICOS files.
	/// @return true/false false if aeSrc is not a valid DcsApplicationEntity string.
	bool SetSourceApplication(const DcsApplicationEntity &aeSrc);
	/// @see SetSourceApplication
	const DcsApplicationEntity& GetSourceApplication()const;

	/// Set the name of the application receiving data. Must be 16 or less characters.
	/// This value will take effect in the next DICOS session and not in a current open DICOS session.
	/// This is a requirement for the DICOM protocol that can be used by clients to verify the server.
	/// @param aeDst Name of destination application that is receiving DICOS files.
	/// @return true/false false if aeDst is not a valid DcsApplicationEntity string.
	bool SetDestinationApplication(const DcsApplicationEntity &aeDst);
	/// @see SetDestinationApplication
	const DcsApplicationEntity& GetDestinationApplication()const;

	/// Set user name. Must be a non-empty string.
	/// This value will take effect in the next DICOS session and not in a current open DICOS session.
	/// @param dsUserName Name of user sending DICOS files
	/// @return true/false false if dsUserName is empty
	bool SetUserName(const DcsString &dsUserName);
	/// Set passcode and user name. Both must be a non-empty strings.
	/// This value will take effect in the next DICOS session and not in a current open DICOS session.
	/// @param dsPasscode Password to authenticate the user sending DICOS files with the Server
	/// @param dsUserName Name of the user sending DICOS files
	/// @return true/false false if dsUserName is empty
	bool SetPasscodeAndUserName(const DcsString &dsPasscode, const DcsString &dsUserName);
	/// Delete passcode and user name
	void DeletePasscodeAndUserName();

	/// Set a restricted size for data PDU's. Set to zero for unrestricted size.
	/// Default is unrestricted. Value can only be set when no DICOS session is in progress.
	/// @param nMaxSize Maximum size in bytes for a data PDU. Must be greater than or equal to 1000.
	/// @return true/false false if nMaxSize < 1000
	bool RestrictSizeOfPDU(const S_UINT32 nMaxSize);
	/// Sets data PDU size to unrestricted. Value can only be set when no DICOS session is in progress.
	bool SetUnrestrictedSizeForPDU();

	/// Set parameter to true to prioritize using compression transfer syntaxes for data
	/// transfers between the client and server. Otherwise, set the parameter to false
	/// to prioritize uncompressed data transfers between the client and server.
	/// Defaults to prioritze compression.
	void PrioritizeDataCompression(const bool bPrioritize);

	/// @see PrioritizeDataCompression
	bool IsPrioritizingDataCompression()const;

	/// Disable data compression transfer syntax.
	void DisableDataCompression();

	/// @see PrioritizeDataCompression
	/// @see DisableDataCompression
	bool IsDataCompressionDisabled()const;

	/// Perform a C-Echo operation. This function internally connects, sends an echo, then disconnects from a DICOS server.
	/// If a connection or session is already in progress before this function is called, then that state is maintained 
	/// when this function exits.
	/// @return Returns false if IsValid() fails. Returns true if echo completed successfully.
	bool Echo();
	
	/// Perform a C-Store operation. This function internally connects, sends data, then disconnects from a DICOS server.
	/// If a connection or session is already in progress before this function is called, then that state is maintained 
	/// when this function exits.
	/// @param manager Attribute manager to store
	/// @return true/false 
	bool Store(AttributeManager& manager);
	
	/// Perform a C-Store operation. This function internally connects, sends data, then disconnects from a DICOS server.
	/// If a connection or session is already in progress before this function is called, then that state is maintained 
	/// when this function exits.
	/// @param ct CT object to store
	/// @param errorlog Error log
	/// @return true/false 
	bool Store(CTModule& ct, ErrorLog &errorlog);
	
	/// Perform a C-Store operation. This function internally connects, sends data, then disconnects from a DICOS server.
	/// If a connection or session is already in progress before this function is called, then that state is maintained 
	/// when this function exits.
	/// @param ait2d AIT2D object to store
	/// @param errorlog Error log
	/// @return true/false 
	bool Store(AIT2DModule& ait2d, ErrorLog &errorlog);
	
	/// Perform a C-Store operation. This function internally connects, sends data, then disconnects from a DICOS server.
	/// If a connection or session is already in progress before this function is called, then that state is maintained 
	/// when this function exits.
	/// @param ait3d AIT3D object to store
	/// @param errorlog Error log
	/// @return true/false 
	bool Store(AIT3DModule& ait3d, ErrorLog &errorlog);
	
	/// Perform a C-Store operation. This function internally connects, sends data, then disconnects from a DICOS server.
	/// If a connection or session is already in progress before this function is called, then that state is maintained 
	/// when this function exits.
	/// @param dx DX object to store
	/// @param errorlog Error log
	/// @return true/false 
	bool Store(DXModule& dx, ErrorLog &errorlog);
	
	/// Perform a C-Store operation. This function internally connects, sends data, then disconnects from a DICOS server.
	/// If a connection or session is already in progress before this function is called, then that state is maintained 
	/// when this function exits.
	/// @param qr QR object to store
	/// @param errorlog Error log
	/// @return true/false 
	bool Store(QRModule& qr, ErrorLog &errorlog);
	
	/// Perform a C-Store operation. This function internally connects, sends data, then disconnects from a DICOS server.
	/// If a connection or session is already in progress before this function is called, then that state is maintained 
	/// when this function exits.
	/// @param tdr TDR object to store
	/// @param errorlog Error log
	/// @return true/false 
	bool Store(TDRModule& tdr, ErrorLog &errorlog);

	/// Returns operation result
	RESULT GetResult()const;

	/// Get the client's error log
	const ErrorLog& GetErrorLog()const;

	/// Returns true if all values are set correctly.
	bool IsValid()const;

	/// Include an SOP class UID
	bool IncludeSopClassUID(const DcsUniqueIdentifier &uidSopClassUID);

	/// Resets allowed SOP class UID's to the defaults
	void ResetIncludedSopClassUIDs();

	/// Get list of supported SOP class UID's
	void GetListOfSupportedSopClassUIDs(Array1D<DcsUniqueIdentifier> &vSopClassUIDs)const;

	////////////////////////////////////////////////////////////////////////////////
	// The following connect/disconnect functions for establishing a single session
	// so that each call to Store() will be part of the same session.

	/// Enumeration flags for manual connections
	typedef enum
	{
		enumSopCT				= 1,	///< CT (8-64 bit, 32 bit float)
		enumSopAIT2D			= 1<<1,	///< AIT 2D (8-64 bit, 32 bit float)
		enumSopAIT3D			= 1<<2,	///< AIT 3D (8-64 bit, 32 bit float)
		enumSopDXProcessing		= 1<<3,	///< DX for processing (8-64 bit, 32 bit float)
		enumSopDXPresentation	= 1<<4,	///< DX for presentation (8-64 bit, 32 bit float)
		enumSopDX				= (enumSopDXProcessing | enumSopDXPresentation),	///< DX for processing and DX for presentation (8-64 bit, 32 bit float)
		enumSopQR				= 1<<5,	///< QR
		enumSopTDR				= 1<<6,	///< TDR

		enumSopEcho				= 1<<7,	///< C-Echo

		enumSopAIT2DTDR			= enumSopAIT2D | enumSopTDR,	///< AIT 2D and TDR
		enumSopAIT3DTDR			= enumSopAIT3D | enumSopTDR,	///< AIT 2D and TDR (8-64 bit, 32 bit float)
		enumSopCTTDR			= enumSopCT | enumSopTDR,		///< CT and TDR (8-64 bit, 32 bit float)
		enumSopDXTDR			= enumSopDX | enumSopTDR,		///< DX and TDR (8-64 bit, 32 bit float)
		enumSopQRTDR			= enumSopQR | enumSopTDR,		///< DX and TDR (8-64 bit, 32 bit float)

		enumSopAll				= enumSopCT | enumSopAIT2D | enumSopAIT3D | enumSopDX | enumSopQR | enumSopTDR | enumSopEcho,	///< All SOP class UID's
	}SOPCLASSUID;

	/// Establishes a TCP/IP connection with a DICOS server 
	/// @return Returns true if connected
	bool ConnectToServer();
	/// Disconnects the TCP/IP connection from a DICOS server. If a session is in progress, this will wait until it is completed before disconnecting.
	/// This must be called before starting a new DICOS session after calling StopDicosSession().
	/// @see StopDicosSession
	void DisconnectFromServer();
	/// Returns true if there is a connection with a DICOS server
	bool IsConnectedToServer()const;

	/// Starts a DICOS session on an established TCP/IP connection. Call after ConnectToServer().
	/// Once the session is complete, call StopDicosSession.
	/// @param nSopClassUIDs SOPCLASSUID enumerations to enable. Example: To enable echo, CT, and TDR call ConnectToServer(enumSopEcho | enumSopCT | enumSopTDR)
	/// @return Returns true if session has started. Returns false if not connected or IsValid() fails or if a session is already in progress.
	bool StartDicosSession(const S_UINT32 &nSopClassUIDs);
	/// End a DICOS session. Call DisconnectFromServer() after StopDicosSession().
	/// Returns true if the session has ended. Returns false if the session is processing a command that cannot be interrupted.
	/// @see DisconnectFromServer
	bool StopDicosSession();
	/// Returns true if a DICOS session is in progress
	bool IsSessionInProgress()const;

	/// Returns true if the currently established connection supports sending CT data
	bool CanSendCT()const;
	/// Returns true if the currently established connection supports sending AIT 2D data
	bool CanSendAIT2D()const;
	/// Returns true if the currently established connection supports sending AIT 3D data
	bool CanSendAIT3D()const;
	/// Returns true if the currently established connection supports sending DX for processing data
	bool CanSendDXProcessing()const;
	/// Returns true if the currently established connection supports sending DX for presentation data
	bool CanSendDXPresentation()const;
	/// Returns true if the currently established connection supports sending QR data
	bool CanSendQR()const;
	/// Returns true if the currently established connection supports sending TDR data
	bool CanSendTDR()const;
	/// Returns true if the currently established connection supports sending C-Echo commands
	bool CanSendEcho()const;

protected:

	friend class DcsClientManager;

	class DcsClientImpl;				///< Implementation forward declaration
	DcsClientImpl *m_pDcsClientImpl;	///< Implementation

	DcsClientImpl* GetImpl();
	const DcsClientImpl* GetImpl()const;
};

}//namespace Network
}//namespace SDICOS

#endif
