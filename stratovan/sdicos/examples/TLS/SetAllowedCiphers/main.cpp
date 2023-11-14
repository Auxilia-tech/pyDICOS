//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2021 Stratovan Corporation. All Rights Reserved.
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
#include <iostream>

#include "SDICOS/FileSystem.h"
#include "SDICOS/ToolsLight.h"
#include "SDICOS/Host.h"
#include "SDICOS/Client.h"
#include "SDICOS/Attribute.h"

//
// This class derives from the callback interface class. Override callback functions to process DICOS 
// data received by the DICOS server. The overridden functions should at least correspond to the API preference
// selected by the server. The function 'OnReceiveDicosFileError()', which receives errors that occurred 
// during the transmission, and 'OnReceiveDicosFile(DicosData<AttributeManager> &, const ErrorLog &)', which is called
// if DcsServer::PreferTagAPI() is called or if an unknown modality is received, must always be overridden.
//
// Example:
//		A call to DcsServer::PreferUserAPI() should have all the user-level API callback functions overridden in the
//		callback interface class. Only the functions using the expected modalities should be overridden.
//		Functions to override:
//			-OnReceiveDicosFile(DicosData<SDICOS::CT> &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::DX> &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::AIT2D> &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::AIT3D> &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::QR> &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::TDR> &, const ErrorLog &)
//
// Example:
//		A call to DcsServer::PreferModuleAPI() should have all the module-level API callback functions overridden in the
//		callback interface class. Only the functions using the expected modalities should be overridden.
//		Functions to override: 
//			-OnReceiveDicosFile(DicosData<SDICOS::CTModule> &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::DXModule>  &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::AIT2DModule> &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::AIT3DModule> &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::QRModule> &, const ErrorLog &)
//			-OnReceiveDicosFile(DicosData<SDICOS::TDRModule> &, const ErrorLog &)
//
class ExampleServer : public SDICOS::Network::IReceiveCallback
{
public:
	ExampleServer() {}

	/// Start the server and begin listening for TSL connections
	bool StartListeningWithSSL();

	/// Get the port used by the DICOS server
	static int GetServerPort();

	/// Get the DICOS server's application name
	static SDICOS::DcsApplicationEntity GetServerApplicationName();
	
	/// [Error] Override for callback function when errors occur and client session completes
	virtual void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata)
	{
		std::cerr << "OnReceiveDicosFileError " << errorlog << std::endl;
	}

	/// [Tag-Level API or Unknown Data] Override for callback function when data is received.
	/// This function is also called if the preferred API cannot be used due to an unknown SOP class UID found in the DICOS data.
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog)
	{
		std::cerr << "OnReceiveDicosFile(AttributeManager) " << errorlog << " SSL=" << m_DcsServer.IsUsingSsl() << std::endl;
	}
	
	/// [Tag-Level API or Unknown Data] Override for callback function when data is received.
	/// This function is also called if the preferred API cannot be used due to an unknown SOP class UID found in the DICOS data.
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
	{
		std::cerr << "OnReceiveDicosFile(SDICOS::CT) " << errorlog << " SSL=" << m_DcsServer.IsUsingSsl() << std::endl;
	}
	
	/// Called after receiving a C-Echo
	virtual void OnReceiveDicosEcho(const SDICOS::Utils::SessionData &sessiondata, const SDICOS::ErrorLog &errorlog)
	{
		std::cerr << __FUNCTION__ << " " << sessiondata << " SSL=" << m_DcsServer.IsUsingSsl() << " ErrorLog=" << errorlog << std::endl;
	}

	/// Called when DICOS session starts
	virtual void OnBeginSession(const SDICOS::Utils::SessionData &sessiondata)
	{
		std::cerr << __FUNCTION__ << " " << sessiondata << " SSL=" << m_DcsServer.IsUsingSsl() << std::endl;
	}

	/// Called when DICOS session ends
	void OnEndSession(const SDICOS::Utils::SessionData &sessiondata)
	{
		std::cerr << __FUNCTION__ << " " << sessiondata << " SSL=" << m_DcsServer.IsUsingSsl() << std::endl;
	}

	/// Called when a TCP/IP connection is established
	void OnConnected(const SDICOS::Utils::SessionData &sessiondata)
	{
		std::cerr << __FUNCTION__ << " " << sessiondata << " SSL=" << m_DcsServer.IsUsingSsl() << std::endl;
	}

	/// Called when a TCP/IP connection is terminated
	void OnDisconnected(const SDICOS::Utils::SessionData &sessiondata)
	{
		std::cerr << __FUNCTION__ << " " << sessiondata << " SSL=" << m_DcsServer.IsUsingSsl() << std::endl;
	}
	
	SDICOS::DcsString m_certFile;
	SDICOS::DcsString m_certPassword;

	/*
		Server and Client certificates' Common Name must match.
	*/
	SDICOS::DcsString m_certCommonName;

	SDICOS::DcsString m_dsSslAllowedCiphers;

	SDICOS::Network::DcsServer m_DcsServer;
};

bool ExampleServer::StartListeningWithSSL()
{
	/*
		Setup required DICOS Server parameters
	*/

	/// Set the server port and IP
	m_DcsServer.SetIP("127.0.0.1");
	m_DcsServer.SetPort(ExampleServer::GetServerPort());
	
	/// Set the application name.  The application name is a 16 character maximum name associated with the server
	/// Should be related to the application using the server
	m_DcsServer.SetApplicationName(ExampleServer::GetServerApplicationName());
  
	/// Set the server's list of allowed ciphers
	m_DcsServer.SetSslAllowedCiphers(m_dsSslAllowedCiphers);

    /// Set client certificates as optional
	/// This allows a TLS connection to be established between a server with verified certificates without the client to have certs
	/// This must be called before DcsServer::SetSslCertificate, otherwise the server will still expect client certificates
    m_DcsServer.SetTLSClientCertificateRequired(false);	
	
	SDICOS::ErrorLog errorLog;

	/// Set the DICOS server's SSL certificate
	if(false == m_DcsServer.SetSslCertificate(m_certFile, m_certPassword, m_certCommonName, errorLog))
	{
		std::cerr << "Failed to set DcsServer certificate " << errorLog << std::endl;
		return false;
	}
	else{
		std::cerr << "Set DcsServer certificate SSL=" << m_DcsServer.IsUsingSsl() << std::endl;
	}
	
	/// Start the server listening
	/// Takes *this as an argument to have access to all of the overridden IRecieveCallback functions
	if(m_DcsServer.StartListening((*this)))
	{
		std::cerr << "DcsServer Listening at "  << m_DcsServer.GetIP() << ":" << m_DcsServer.GetPort() << " UsingSsl=" << m_DcsServer.IsUsingSsl() << std::endl;
	}
	else
	{
		std::cerr << "Failed to start DcsServer at "  << m_DcsServer.GetIP() << ":" << m_DcsServer.GetPort() << " UsingSsl=" << m_DcsServer.IsUsingSsl() << std::endl;
		return false;
	}
	return true;
}

/// Get the DICOS server port
int ExampleServer::GetServerPort()
{
	return 7890;
}

/// Get the DICOS server Application Name
SDICOS::DcsApplicationEntity ExampleServer::GetServerApplicationName()
{
	return SDICOS::DcsApplicationEntity("SERVER");
}

/// Example client class, include a DcsClient object and some simple functions to drive it
class ExampleClient
{
public:
	ExampleClient()
	{	
	}

	/// Start the client and connect it to the server
	bool ConnectToServer();
	/// Send echo to the server
	bool SendEcho();
	/// Send DICOS file to the server
	bool SendDicosFile(const SDICOS::Filename& dicosFile);


	/*
		Server and Client certificates' Common Name must match.
	*/
	SDICOS::DcsString m_certFile;
	SDICOS::DcsString m_certPassword;
	SDICOS::DcsString m_certCommonName;
	SDICOS::Network::DcsClient m_DcsClient;
	SDICOS::DcsString m_dsSslAllowedCiphers;
};

bool ExampleClient::ConnectToServer()
{
	/*
		Setup required DICOS Client parameters
	*/
	m_DcsClient.SetSourceApplication(SDICOS::DcsApplicationEntity("CLIENT"));
	/// Destination application must be the same application name as the server's
	m_DcsClient.SetDestinationApplication(ExampleServer::GetServerApplicationName());

	/// Set the client's list of allowed ciphers
	m_DcsClient.SetSslAllowedCiphers(m_dsSslAllowedCiphers);
	
	/// Set the server port and IP for the client to connect to
	if(false == m_DcsClient.SetServerPortandIP(SDICOS::S_INT32(ExampleServer::GetServerPort()), SDICOS::DcsString("127.0.0.1")))
	{
		std::cerr << "Failed to set DcsClient's Server IP and Port" << std::endl;
		return false;
	}
	else
	{
		std::cerr << "Set DcsClient's Server IP and Port" << std::endl; 
	}
	
	SDICOS::ErrorLog errorLog;

	if(false == m_DcsClient.SetSslCertificate(m_certFile, m_certPassword, m_certCommonName, errorLog))
	{
		std::cerr << "Cannot Set DcsClient certificate " << errorLog << std::endl;
		return false;
	}
	else
	{
		m_DcsClient.EnableSsl(true);
		std::cerr << "Set DcsClient certificate SSL=" << m_DcsClient.IsUsingSsl() << std::endl;
	}
	
	std::cerr << "DcsClient Initialized IsValid=" << m_DcsClient.IsValid() << " UsingSsl=" << m_DcsClient.IsUsingSsl() << std::endl;	
	return true;

	std::cerr << "DcsClient Initialized IsValid=" << m_DcsClient.IsValid() << " UsingSsl=" << m_DcsClient.IsUsingSsl() << std::endl;	
	return true;
}

bool ExampleClient::SendEcho()
{
	if(m_DcsClient.Echo())
	{
		std::cerr << "Sent Echo to DcsServer UsingSSL=" << m_DcsClient.IsUsingSsl() << std::endl;
		std::cerr << "TLS Cipher Suite Used=" << m_DcsClient.GetTlsCipherSuite() << std::endl;
		return true;
	}
	else
	{
		std::cerr << "Unable to send Echo to DcsServer UsingSSL=" << m_DcsClient.IsUsingSsl() << " ErrorLog=" << m_DcsClient.GetErrorLog() << std::endl;
		return false;
	}		
}

bool ExampleClient::SendDicosFile(const SDICOS::Filename& dicosFile)
{
	SDICOS::ErrorLog errorlog;
	SDICOS::AttributeManager am;
	/// Load DICOS file
	if(false == am.Read(dicosFile, errorlog))
	{
		std::cerr << "Unable to read DICOS file " << dicosFile << " " << errorlog << std::endl;
		return false;
	}
	else
	{
		std::cerr << "Loaded DICOS file " << dicosFile << " into AttributeManager" << std::endl;
		
		/// Send data to the server
		if(	m_DcsClient.Store(am))
		{
			std::cerr << "Sent DICOS file as Attribute Manager to server" << std::endl;
			return true;
		}
		else
		{
			std:: cerr << "Failed to send DICOS file to server " << dicosFile << " " << m_DcsClient.GetErrorLog() << std::endl;
			return false;
		}
	}
}

/// Set up a client and server with a list of allowed ciphers
/// The client sends the server the list of ciphers in order of preference and the server choses one that they have in common
/// If the client and server have no ciphers in common, the connection will be rejected.
int main()
{
	/*
		Setup DICOS Server and Client TLS data
		Server requires the Client to have the same Common Name
	*/
	ExampleServer server;
	server.m_certFile = SDICOS::DcsString("dicos_server.pfx");

	/// The password set when creating the PFX file
	server.m_certPassword = SDICOS::DcsString("dicos");
	server.m_certCommonName = SDICOS::DcsString("dcs");

	/// Set the server's allowed ciphers
	/// The allowed ciphers is a comma delimited list of ciphers in order of preference.
	/// If set to the empty string, any cipher that is supported will be allowed.
	/// The default list of ciphers for the client and server is "TLS_AES_256_GCM_SHA384,TLS_CHACHA20_POLY1305_SHA256,TLS_AES_128_GCM_SHA256"
	server.m_dsSslAllowedCiphers = SDICOS::DcsString("TLS_AES_256_GCM_SHA384,TLS_CHACHA20_POLY1305_SHA256,TLS_AES_128_GCM_SHA256");

	ExampleClient client;
	client.m_certFile = SDICOS::DcsString("dicos_client.pfx");

	// The password set when creating the PFX file
	client.m_certPassword = SDICOS::DcsString("dicos");

	// Server requires the Client to have the same Common Name
	client.m_certCommonName = SDICOS::DcsString("dcs");

	/// Set the client's allowed ciphers
	client.m_dsSslAllowedCiphers = SDICOS::DcsString("TLS_CHACHA20_POLY1305_SHA256,TLS_AES_128_GCM_SHA256");

	/*
		Initialize DcsServer and DcsClient
	*/

	/// Start the server and start listening with TLS enabled
	if(false == server.StartListeningWithSSL())
		return 1;
	
	/// Give the server thread time to start up and listen for a connection
	SDICOS::SleepTime(1000);

	if(false == client.ConnectToServer())
		return 1;
	
	/// Give the client thread time to start and set the server ip and port before attempting to send an echo
	SDICOS::SleepTime(1000);

	/*
		Test sending CEcho to the server
	*/
	if(false == client.SendEcho())
		return 1;

	/// Give the client thread time to send the echo
	SDICOS::SleepTime(1000);

	/// Set to a valid DICOS file
	SDICOS::Filename testDicosFile("testDicosFile.dcs");

	/*
		Test sending a Dicos file to the server
	*/
	if(false == client.SendDicosFile(testDicosFile))
		return 1;

	server.m_DcsServer.StopListening();
	return 0;
}