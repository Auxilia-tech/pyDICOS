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
// This example configures a client to have a user name and passcode
//
#include "SDICOS/DICOS.h" //Header for DICOS
#include <iostream>

int main()
{
	SDICOS::Network::DcsClient client; // DICOS client

	// Set the port and IP address of the server
	client.SetServerPortandIP(1000, "1.1.1.1");

	// Set the name of the client application. Must be no longer than 16 letters.
	client.SetSourceApplication("ClientExample");

	// Set the name of the client application. Must be no longer than 16 letters.
	client.SetDestinationApplication("server");

	// Set a user name and passcode for the client. User name and passcode can also be set
	// after DcsClient::ConnectToServer() has been called.
	client.SetPasscodeAndUserName("Passcode", "UserName");

	//Manually connect to the server. Establishes the TCP/IP connection.
	if(client.ConnectToServer())
		std::cout<<"Connected to server"<<std::endl;
	else
	{
		std::cout<<"Connecting to server failed"<<std::endl;

		// Print out the error log
		std::cout<<"Error log:"<<std::endl;
		std::cout<<client.GetErrorLog()<<std::endl;

		// Write the error log to file. Alternatively, string arrays can be retrieved
		// using errorlog.GetErrorLog()
		client.GetErrorLog().WriteLog(SDICOS::Filename("ErrorLog - Server Connection Failed.txt"));
		return 1;
	}

	//Manually start a DICOS session to only allow processing C-Echo commands.
	//An invalid user name and password combination can cause a DICOS session to not start.
	if(client.StartDicosSession(SDICOS::Network::DcsClient::enumSopEcho))
		std::cout<<"DICOS session started"<<std::endl;
	else
	{
		std::cout<<"DICOS session failed to start"<<std::endl;

		// Print out the error log
		std::cout<<"Error log:"<<std::endl;
		std::cout<<client.GetErrorLog()<<std::endl;

		// Write the error log to file. Alternatively, string arrays can be retrieved
		// using errorlog.GetErrorLog()
		client.GetErrorLog().WriteLog(SDICOS::Filename("ErrorLog - DICOS Session Start Failed.txt"));
		return 1;
	}

	// Send a C-Echo to the server. True is returned if the echo completed successfully.
	if(client.Echo())
		std::cout<<"Echo success"<<std::endl;
	else
	{
		std::cout<<"Echo failed"<<std::endl;

		// Print out the error log
		std::cout<<"Error log:"<<std::endl;
		std::cout<<client.GetErrorLog()<<std::endl;

		// Write the error log to file. Alternatively, string arrays can be retrieved
		// using errorlog.GetErrorLog()
		client.GetErrorLog().WriteLog(SDICOS::Filename("ErrorLog - Echo Failed.txt"));
	}

	//Manually stop the DICOS session
	client.StopDicosSession();

	//Manually disconnect from server.
	client.DisconnectFromServer();

	return 0;
}
