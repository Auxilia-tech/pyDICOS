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
// This example shows how to utilize the User-Level API to receive and process a DICOS object over the network
// check that it is valid and save the error report to a file. The location where logs are placed
// must be specified on the command line.
//
// To run the example first start the DICOS Server with an ip address and port and then
// run a DICOS Client Application that is initialized to send data to the server in this example.
//
// 
//

#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "SDICOS/DICOS.h"

#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
#endif

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS
#endif

namespace ConformanceTesting
{

/**
 * \class DICOSCallbackHandler
 * 
 * The DICOSCallbackHandler class implements the SDICOS::Network::IReceiveCallback interface methods to
 * process DICOS files received from a DICOS Server. The callback handler is registered with the DcsServer object 
 * by calling SDICOS::DcsServer::StartListening() along with a flag indicating indicating which 
 * API level, (User, Module or Tag) should be called when DICOS files are received.
 * 
 * <b>IMPORTANT IMPLEMENTATION DETAILS</b>:
 *	
 *	The DcsServer uses a separate thread to dispatch received DICOS files to the SDICOS::Network::IReceiveCallback handler.
 *	This thread blocks on these callbacks so the callback implementations must be fast and deterministic.
 *	In general, when used in conjunction with a DcsServer the implementation of methods in SDICOS::Network::IReceiveCallback should take ownership
 *	of the DICOS data, pass it to a processing thread and return.
 * 
 * This example handler implements the callbacks for the User-Level, Module-Level API, Tag-Level API and error handler.
 * 
 * User Level API Callbacks:
 *		- void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QR> &tdr, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
 *
 * Module-Level API Callbacks:
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CTModule> &ct, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2DModule> &ait, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3DModule> &ait, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DXModule> &dx, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QRModule> &qr, const SDICOS::ErrorLog &errorlog)
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDRModule> &tdr, const SDICOS::ErrorLog &errorlog)
 *	
 * Tag-Level API Callback. This is a pure virtual method and must be implemented.
 *		- virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog) 
 * 
 * Error Handler Callback. This is a pure virtual method and must be implemented.
 *		- virtual void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata)
 *
 */
class DICOSCallbackHandler : public SDICOS::Network::IReceiveCallback
{
public:

	template<typename DICOS_MODULE_DATA_TYPE>
	bool ValidateDICOSModuleData(SDICOS::Utils::DicosData<DICOS_MODULE_DATA_TYPE>& dicosData, SDICOS::ErrorLog& errorLog)
	{
			DICOS_MODULE_DATA_TYPE* pData(0);
			dicosData.TakeOwnership(pData);
			bool bRes(false);
			if(pData)
			{
				bRes = pData->IsValid(errorLog);
			}
			return bRes;
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
	{
		// Handle CT Object using the User-API
		//
		// The DcsServer thread that dispatches DICOS Data to callback methods blocks until the callback returns.
		// Non-trivial callback implementations should take ownership of the data, pass it to a processing thread
		// and return control to the DcsServer.
		
		// Take ownership of DICOS Data and pass it to a thread for processing. The caller is now responsible for deleting it.
		SDICOS::CT* pCTData(NULL);
		ct.TakeOwnership(pCTData);

		// ct is now invalidated and cannot be used
				
		if(pCTData) 
		{
			SDICOS::ErrorLog errorLog;

			// Simple example of logging information when a DICOS file is received.
			this->LogReceiveDicosFile("User-API CT", pCTData->GetSopInstanceUID(), errorlog);

			// Pass the data to a processing thread and return
			this->ProcessCTDataOnAnotherThread(pCTData);
			
		} 
		else 
		{
			this->LogReceiveDicosFile("User-API CT", "Unable to take ownership of DICOS data.", errorlog);
		}
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
	{
		// Handle DX object using User API
		this->LogReceiveDicosFile("User-API DX", dx->GetSopInstanceUID(), errorlog);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
	{
		// Handle AIT2D object using User API
		this->LogReceiveDicosFile("User-API AIT2D",ait->GetSopInstanceUID(), errorlog);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog)
	{
		// Handle ATI3D object using User API
		this->LogReceiveDicosFile("User-API AIT3D", ait->GetSopInstanceUID(), errorlog);
	}
	
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
	{
		// Handle TDR object using the User API
		this->LogReceiveDicosFile("User-API TDR", tdr->GetSopInstanceUID(), errorlog);
	}
	
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CTModule> &ct, const SDICOS::ErrorLog &errorlog)
	{
		// Handle CTModule object using Module-Level API.
		this->LogReceiveDicosFile("Module-API CT", ct->GetSopCommon().GetSopInstanceUID(), errorlog);
	}
	
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2DModule> &ait, const SDICOS::ErrorLog &errorlog)
	{
		// Handle AIT2DModule object using Module-Level API.
		this->LogReceiveDicosFile("Module-API AIT2D",ait->GetSopCommon().GetSopInstanceUID(), errorlog);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3DModule> &ait, const SDICOS::ErrorLog &errorlog)
	{
		// Handle AIT3DModule object using Module-Level API.
		this->LogReceiveDicosFile("Module-API AIT3D", ait->GetSopCommon().GetSopInstanceUID(), errorlog);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DXModule> &dx, const SDICOS::ErrorLog &errorlog)
	{
		// Handle DXModule objects using Module-Level API.
		this->LogReceiveDicosFile("Module-API DX", dx->GetSopCommon().GetSopInstanceUID(), errorlog);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QRModule> &qr, const SDICOS::ErrorLog &errorlog)
	{
		// Handle QRModule objects using the Module-Level API.
		this->LogReceiveDicosFile("Module-API QR",qr->GetSopCommon().GetSopInstanceUID(), errorlog);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDRModule> &tdr, const SDICOS::ErrorLog &errorlog)
	{
		// Handle TDRModule objects using the Module-Level API.
		this->LogReceiveDicosFile("Module-API TDR",tdr->GetSopCommon().GetSopInstanceUID(), errorlog);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AttributeManager> &manager, const SDICOS::ErrorLog &errorlog)
	{
		// Catch all callback that handles DICOS data which does not fall into one of the expected callbacks
		// for the User API or Module API.
		// This method is a pure virtual method and must be overridden.

		std::stringbuf buffer;
		std::ostream os(&buffer);
				
		SDICOS::AttributeManager::TagList tl;
		manager->GetTagListing(tl,true);
		os << "Num Attributes" << tl.Length();
		os << "Transfer Syntax " << manager->GetTransferSyntax();
		os << "Errors " << errorlog;
		this->LogReceiveDicosFile("Tag-Level AttributeManager", buffer.str().c_str());
	}

	virtual void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata)
	{
		// Handle errors retrieving Dicos Files
		// This method is a pure virtual method and must be overridden.
		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << "Errors Logged " << errorlog.NumErrors() << " Warnings Logged " << errorlog.NumWarnings() << "\n";
		if(errorlog.NumErrors() > 0 || errorlog.NumWarnings() > 0) 
		{
			os << errorlog;
		}
		this->LogReceiveDicosFile("File Error", buffer.str().c_str());
	}

	void LogReceiveDicosFile(const char * source, const SDICOS::DcsString& message, const SDICOS::ErrorLog& el)
	{
		if(el.NumErrors() > 0) 
		{
			std::stringbuf buffer;
			std::ostream os(&buffer);
			os << el<< "\n";
			std::cerr << "received dicos data Source: " << source << " Message: " << message.Get() << " Errors: " << buffer.str().c_str() << std::endl;
		}
		else 
		{
			std::cerr << "received dicos data Source: " << source << " Message: " << message.Get() << " No Errors" << std::endl;
		}
	}

	void LogReceiveDicosFile(const char * source, const char * message)
	{
		std::cerr << "received dicos data Source: " << source << " Message: " << message << std::endl;
	}

private:
	
	void ProcessCTDataOnAnotherThread(const SDICOS::CT* pCT)
	{
		// Stub method for processing CT Data
			
		// Callback handler is now responsible for deleting DICOS data
		delete pCT;
	}
};

} // namespace ConformanceTesting

void PrintUsage();

int main(int argc, char *argv[])
{
	for(int i = 0; i < argc; ++i) 
	{
		if(	0 == strcmp("-help", argv[i]) || 
			(0 == strcmp("--help", argv[i])) ||
			(0 == strcmp("/H", argv[i]))) 
		{
			PrintUsage();
			return(EXIT_SUCCESS);
		}
	}
	
	/* Parse command line args for port and IP address */
	const char * ip(NULL);
	SDICOS::S_INT32 port(0);
	for(int i = 0; i < argc; ++i) 
	{
		if(0 == strcmp("-ip", argv[i])) 
		{
			if(argc > (i+1)) 
			{
				ip = argv[i+1];
			}
		} 
		else if (0 == strcmp("-port", argv[i])) 
		{
			if(argc > (i+1)) 
			{
				port = atoi(argv[i+1]);
			}
		}
	}
		
	int numErrors = 0;
	if(NULL == ip) 
	{
		std::cerr << "IP Address for listening must be specified." << std::endl;
		++numErrors;
	}
		
	if(port <= 0) 
	{
		std::cerr << "Port for listening cannot be <= 0" << std::endl;
		++numErrors;
	}
		
	if(numErrors) 
	{
		PrintUsage();
		return EXIT_FAILURE;
	}

	SDICOS::Network::DcsServer server;
	ConformanceTesting::DICOSCallbackHandler handler;
		
	bool bRes(true);
		
	/// Server application name that Client connects to. Must by of type SDICOS.DcsApplicationEntity.
	/// This parameter corresponds to the Destination Application name property in the SDICOS.Network.DcsClient class
	/// and is parameter to the SendOverNetwork() method in the User-Level API objects. e.g. SDICOS.CT.
	bRes = server.SetApplicationName("Conf") && bRes;
	bRes = server.SetIP(ip) && bRes;
	bRes = server.SetPort(port) && bRes;
		
	// The maximum number of milliseconds to wait on a socket read operation while no additional data is forthcoming.
	// The maximum number of milliseconds to wait for the socket to become writeable on a socket write operation. 
	// To wait indefinitely set value to 0. Default is 1000ms.
	bRes = server.SetReadTimeoutInMilliseconds(500) && bRes;
	bRes = server.SetWriteTimeoutInMilliseconds(500) && bRes;

	// Prefer clients to send uncompressed data, but still accept compressed data.
	server.PrioritizeDataCompression(false);
	
	/// Accept connections from all source application names to all destination application names.
	/// The Source Application Name and Destination Application Name are members of the SDICOS.Network.DcsClient class.
	/// They are also passed as parameters to the SendOverNetwork() call in the User-Level API objects. e.g. SDICOS.CT, SDICOS.AIT3D etc.
	server.IgnoreApplicationNames();

	server.AllowAllCients();

  // See SdcsConfig.h
	// SDICOS::Config::EnableDcm_337_WorkArounds();

    // This call creates a thread that listens for connections and routes them to the User API callbacks	
	// Start listening for DICOS data using the specified handler and calling the User-Level API methods.
	bRes = server.StartListening(handler, NULL, SDICOS::Network::DcsServer::enumMethodUserAPI);
		
	// To restrict access to a specific application name
	//server.EnableConnectionFromApplication("TestApp");
	/*
		For finer grain access by source application name call these methods:
			- server.EnableConnectionFromApplication()
			- server.DisableConnectionFromApplication()
	*/
		
	while(1) 
	{
		// Put custom server code here
		SDICOS::SleepTime(10);
	}

	return 0;
}

void PrintUsage()
{
	printf("The ConformanceTesting listens for connections to a DcsHost on a specific port.\n");
	printf("options: [-ip,-port,-logDir]\n");
	printf("-ip IP. IP Address to listen on for connections. -ip 123.123.123.123\n");
	printf("-port Port. Port to listen on for connections. -port 1234\n");
	printf("-logDir Folder where error logs and save files will be written\n");
	printf("Example: ConformanceTesting -ip 123.234.345.456 -port 2000\n");
}
