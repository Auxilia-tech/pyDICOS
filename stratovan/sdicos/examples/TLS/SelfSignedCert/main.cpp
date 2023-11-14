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

#define DICOS_SERVER_PORT	7890

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

	bool Start();
	
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

	SDICOS::Network::DcsServer m_DcsServer;
};

bool ExampleServer::Start()
{
	/*
		Setup required DICOS Server parameters
	*/
	m_DcsServer.SetIP("127.0.0.1");
	m_DcsServer.SetPort(DICOS_SERVER_PORT);
	m_DcsServer.SetApplicationName(SDICOS::DcsApplicationEntity("SERVER"));
	
	SDICOS::ErrorLog errorLog;

	if(false == m_DcsServer.SetSslCertificate(m_certFile, m_certPassword, m_certCommonName, errorLog))
	{
		std::cerr << "Failed to set DcsServer certificate " << errorLog << std::endl;
		return false;
	}
	else{
		std::cerr << "Set DcsServer certificate SSL=" << m_DcsServer.IsUsingSsl() << std::endl;
	}
	
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

class ExampleClient
{
public:
	ExampleClient()
	{	
	}

	bool Start();
	bool TestConnection();
	bool SendEcho();
	bool SendDicosFile(const SDICOS::Filename& dicosFile);

	/*
		Server and Client certificates' Common Name must match.
	*/
	SDICOS::DcsString m_certFile;
	SDICOS::DcsString m_certPassword;
	SDICOS::DcsString m_certCommonName;
	SDICOS::Network::DcsClient m_DcsClient;
};

bool ExampleClient::Start()
{
	/*
		Setup required DICOS Client parameters
	*/
	m_DcsClient.SetSourceApplication(SDICOS::DcsApplicationEntity("CLIENT"));
	m_DcsClient.SetDestinationApplication(SDICOS::DcsApplicationEntity("SERVER"));
	
	if(false == m_DcsClient.SetServerPortandIP(SDICOS::S_INT32(DICOS_SERVER_PORT), SDICOS::DcsString("127.0.0.1")))
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
}

bool ExampleClient::SendEcho()
{
	if(m_DcsClient.Echo())
	{
		std::cerr << "Sent Echo to DcsServer UsingSSL=" << m_DcsClient.IsUsingSsl() << std::endl;
		return true;
	}
	else
	{
		std::cerr << "Unable to send Echo to DcsServer UsingSSL=" << m_DcsClient.IsUsingSsl() << " ErrorLog=" << m_DcsClient.GetErrorLog() << std::endl;
		return false;
	}		
}

bool ExampleClient::TestConnection()
{
	if(false == m_DcsClient.ConnectToServer())
	{
		std::cerr << "Unable to connect to DcsServer UsingSsl=" << m_DcsClient.IsUsingSsl() << std::endl;
		return false;
	}
	else
	{
		std::cerr << "Connected to DcsServer Connected=" << m_DcsClient.IsConnectedToServer() << " SSL=" << m_DcsClient.IsUsingSsl() << std::endl;
	}
	
	if(false == m_DcsClient.StartDicosSession(SDICOS::Network::DcsClient::enumSopCT | SDICOS::Network::DcsClient::enumSopAIT2DTDR))
	{
		std::cerr << "Unable to start DICOS session with DcsServer " 
		<< m_DcsClient.IsConnectedToServer() 
		<< " " << m_DcsClient.IsValid() 
		<< " " << m_DcsClient.GetErrorLog() << std::endl;
		return false;
	}
	else
	{
		std::cerr << "Started DICOS session with DcsServer Connected=" << m_DcsClient.IsConnectedToServer() 
		<< " SessionInProgress=" << m_DcsClient.IsSessionInProgress()
		<< " SSL=" << m_DcsClient.IsUsingSsl() << std::endl;
		m_DcsClient.StopDicosSession();
	}
	
	m_DcsClient.DisconnectFromServer();
	return true;
}

bool ExampleClient::SendDicosFile(const SDICOS::Filename& dicosFile)
{
	SDICOS::ErrorLog errorlog;
	SDICOS::AttributeManager am;
	if(false == am.Read(dicosFile, errorlog))
	{
		std::cerr << "Unable to read DICOS file " << dicosFile << " " << errorlog << std::endl;
		return false;
	}
	else
	{
		std::cerr << "Loaded DICOS file " << dicosFile << " into AttributeManager" << std::endl;
		
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

int main(int argc, char* argv[])
{
	/*
		Setup DICOS Server and Client TLS data
		Server requires the Client to have the same Common Name
	*/
	ExampleServer server;
	server.m_certFile = SDICOS::DcsString("dicos_server.pfx");

	// The password set when creating the PFX file
	server.m_certPassword = SDICOS::DcsString("dicos");
	server.m_certCommonName = SDICOS::DcsString("dcs");

	ExampleClient client;
	client.m_certFile = SDICOS::DcsString("dicos_client.pfx");

	// The password set when creating the PFX file
	client.m_certPassword = SDICOS::DcsString("dicos");

	// Server requires the Client to have the same Common Name
	client.m_certCommonName = SDICOS::DcsString("dcs");

	/*
		Initialize DcsServer and DcsClient
	*/
	if(false == server.Start() || 
		false == client.Start())
		return 1;
	
	SDICOS::SleepTime(1000);

	/*
		Test sending CEcho to the server
	*/
	if(false == client.SendEcho())
		return 1;

	SDICOS::SleepTime(1000);

	/*
		Test setting up a Dicos Connection and Dicos Session with the server
	*/
	if(false == client.TestConnection())
		return 1;

	SDICOS::SleepTime(1000);

	// Set to a valid DICOS file
	SDICOS::Filename testDicosFile("testDicosFile.dcs");

	/*
		Test sending a Dicos file to the server
	*/
	if(false == client.SendDicosFile(testDicosFile))
		return 1;

	return 0;
}