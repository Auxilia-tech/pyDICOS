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
// This example shows how to manually connect to a server, then send a C-Echo.
//
#include "SDICOS/DICOS.h" //Header for DICOS
#include <iostream>

int main()
{
	int retVal(0);
	SDICOS::Network::DcsClient client; // DICOS client

	// Set the port and IP address of the server
	client.SetServerPortandIP(1000, "1.1.1.1");

	// Set the name of the client application. Must be no longer than 16 letters.
	client.SetSourceApplication("ClientExample");

	// Set the name of the client application. Must be no longer than 16 letters.
	client.SetDestinationApplication("Server");

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
		client.GetErrorLog().WriteLog(SDICOS::Filename("ErrorLog-EchoExample.txt"));
		retVal = 1;
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
		retVal = 1;
	}

	//Manually disconnect from server. Alternatively, deleting the client object will automatically disconnect from the server.
	client.DisconnectFromServer();

	return retVal;
}
