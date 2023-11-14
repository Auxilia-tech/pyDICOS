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
//
// This example configures a server to require all clients to present a valid user name and passcode
//
#include "SDICOS/DICOS.h" //Header for DICOS
#include <iostream>

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
class DataProcessing : public SDICOS::Network::IReceiveCallback
{
public:

protected:
	virtual void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata);

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog);

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog);
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog);
};

//
//	Derive from the client authentication interface.  This interface allows authenticating incoming client's
//	application name, user name, and passcode.  Returning false from the derived functions prevents
//	clients from sending data to the DICOS server.
//
class AuthenticationCallback : public SDICOS::Network::IClientAuthenticationCallback
{
protected:
	virtual bool OnAuthenticateUserNameAndPasscode(const SDICOS::Utils::AuthenticationData &ad)const;
};

int main()
{
	DataProcessing				datacallback;			//Data processing callback interface
	AuthenticationCallback		authenticationcallback;	//Authentication callback object
	SDICOS::Network::DcsServer	server;					//DICOS server

	// Set the port to listen on for incoming connections
	server.SetPort(1000);

	// Set the name of this application. Must be no longer than 16 letters.
	server.SetApplicationName("ServerExample");
	
	// Configure server to only allow clients with specific user name and passcode combinations.
	// The allowed application names and passcodes are defined in the derived 
	// function ApplicationNameauthenticationCallback::OnAuthenticateUserNameAndPasscode()
	server.RequireUserNameAndPasscodeFromClient();

	///////////////////////////////////////////////////////////////
	// Two functions for configuring if compression is allowed to be sent from clients.
	// Although both are used below for demonstration purposes, choose one of them.
	// By default, the server prioritizes data compression.

	//Refuse connection if client can only send compressed data
	server.DisableDataCompression();

	//True = Prefer clients to send compressed data.
	//False = Prefer clients to send uncompressed data, but still accept compressed data.
	server.PrioritizeDataCompression(false);
	///////////////////////////////////////////////////////////////

	// Start the server using the specified callback interface using default preferred API to User-Level.
	// This is a non-blocking function call. This function starts a separate thread for connection processing.
	// The first parameter is the callback interface that is used by the server to send the user data 
	// as received by the server. All connections share the same callback interface; therefore, the 
	// function must exit in order to receive more data. The callback interface can be changed
	// after StartListening() has been called by calling UpdateCallback() and passing in the new
	// interface.
	// The second parameter sets the callback interface for authenticating client's application names, user names,
	// and passcodes.
	// The third parameter, default SDICOS::Network::DcsServer::enumMethodUserAPI, sets the preferred API
	// to use in the callback interface. If the preferred API cannot be used, then the Tag-Level API is called.
	// The preferred API can be changed after StartListening() has been called by calling UpdateCallback() and
	// passing in an SDICOS::Network::DcsServer::RETRIEVE_METHOD enumeration.
	if(!server.StartListening(datacallback, &authenticationcallback))
	{
		std::cout<<"Failed to start DICOS server. IP:Port: " << server.GetIP() << ":" << server.GetPort() << std::endl;
		return 1;
	}

	// Print message for manually stopping the server
	std::cout<<"\nPress enter to stop server";
	std::cin.get(); //Pause here until user presses the 'Enter' key

	// Stop the server
	server.StopListening();

	return 0;
}

bool AuthenticationCallback::OnAuthenticateUserNameAndPasscode(const SDICOS::Utils::AuthenticationData &ad)const
{
	return	(ad.m_dsUserName == SDICOS::DcsString("UserA") && ad.m_dsPasscode == SDICOS::DcsString("Pass0A")) ||
			(ad.m_dsUserName == SDICOS::DcsString("UserB") && ad.m_dsPasscode == SDICOS::DcsString("Pass0B")) ||
			(ad.m_dsUserName == SDICOS::DcsString("UserC") && ad.m_dsPasscode == SDICOS::DcsString("Pass0C"));

}

// [User-Level API] Process all CT modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'ct->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'ct.TakeOwnership()'
	// -Gain ownership of Tag-Level API with original data using the function 'ct.TakeOwnershipOriginal()'

	//Gain ownership of data for processing later using the function 'ct.TakeOwnership()'
	//If ownership is not taken with this function, the data is deleted when the function exits.
	SDICOS::CT *pCT = S_NULL;
	ct.TakeOwnership(pCT);
	DELETE_POINTER(pCT);

	//Gain ownership of original Tag-Level API data for processing later using the function 'ct.TakeOwnershipOriginal()'
	//If ownership is not taken with this function, the data is deleted when the function exits.
	SDICOS::AttributeManager *pmanagerOriginal = S_NULL;
	ct.TakeOwnershipOriginal(pmanagerOriginal);
	DELETE_POINTER(pmanagerOriginal);

	//Print connection information
	std::cout<<ct.GetClientIP().Get()<<std::endl;	//Client IP address that sent the data
	std::cout<<ct.GetServerIP().Get()<<std::endl;	//Server IP address that received the data
	std::cout<<ct.GetServerPort()<<std::endl;		//Server port number
}

// [User-Level API] Process all DX modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'dx->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'dx.TakeOwnership()'
	// -Gain ownership of Tag-Level API with original data using the function 'dx.TakeOwnershipOriginal()'
}

// [User-Level API] Process all AIT 2D modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'ait->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'ait.TakeOwnership()'
}

// [User-Level API] Process all AIT 3D modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'ait->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'ait.TakeOwnership()'
	// -Gain ownership of Tag-Level API with original data using the function 'ait.TakeOwnershipOriginal()'
}

// [User-Level API] Process all TDR modalities received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'tdr->Write()'
	// -Access data through several of the 'get' functions
	// -Gain ownership of data for processing later using the function 'tdr.TakeOwnership()'
	// -Gain ownership of Tag-Level API with original data using the function 'ait.TakeOwnershipOriginal()'
}

// This function is only called when an error occurred during the DICOS network session
// that prevented any modalities from being processed. Overriding this function is required by any derived class.
void DataProcessing::OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata)
{
	//Check the error log for errors and warnings with 'errorlog.GetErrorLog()'
	//or write error log to file 'errorlog.WriteLog()'
	//or print out the error
	std::cout<<errorlog<<std::endl;
}

// [Tag-Level API] Process DICOS data at received by the server
void DataProcessing::OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog)
{
	// The following are a few examples of what to do with the data:
	// -Write to a file using the function 'manager->Write()'
	// -Access data using the 'manager->FindAttribute()' functions
}
