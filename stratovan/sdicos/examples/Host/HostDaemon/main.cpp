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
// This example shows how to utilize the User-Level API to receive and process DICOS objects over the network.
// A daemon process is created that instantiates a SDICOS.Network.DcsServer object which starts listening
// for connections from SDICOS.Network.DcsClient objects.
// The accompanying SimpleClient executable can be used to send a DICOS file to the DICOS Server.
// 
// To run the example first start the DICOS Server with an ip address and port and then
// run SimpleClient with the same ip address and port. If the transfer is successful, log 
// messages should appear somewhere in /var/log depending upon how the system logging is setup.
//
// The log messages on a successful transfer should look like:
// HostDaemonExample[1705]: received dicos data via User-API CT. Id 1357197849.30379.8598.66202.21690000.Errors
//
// The server saves the tag listings to log files based on modality and date.
// 
#include <string>
#include <sstream>

#include "SDICOS/DICOS.h"	//DICOS include header

#ifndef WIN32
	#include <unistd.h>
	#include <syslog.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/stat.h>
	#include <sys/types.h>
#endif

#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
#endif

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS
#endif

namespace HostDaemonExample
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
	DICOSCallbackHandler() : IReceiveCallback()
	{
#ifdef WIN32
		m_LogFolder = "C:\\temp";
#else
		m_LogFolder = "/var/log/DICOSServer";
#endif
		if(!SDICOS::FolderExists(m_LogFolder)) {
			bool b = SDICOS::CreateFolder(m_LogFolder,true);
			if(b) {
				LogReceiveDicosFile("Constructing DICOSCallbackHandler", "Unable to open log folder /var/log/DICOSDaemon");
			}
		}
	}
		
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CT> &ct, const SDICOS::ErrorLog &errorlog)
	{
		// Write a text file with the tags and attribute values
		this->WriteTagListing("CT", ct);

		// Handle CT Object using the User-API
		//
		// The DcsServer thread that dispatches DICOS Data to callback methods blocks until the callback returns.
		// Non-trivial callback implementations should take ownership of the data, pass it to a processing thread
		// and return control to the DcsServer.
		
		// Take ownership of DICOS Data and pass it to a thread for processing. The caller is now responsible for deleting it.
		SDICOS::CT* pCTData(NULL);
		ct.TakeOwnership(pCTData);

		// ct is now invalidate and cannot be used
				
		if(pCTData) {
			// Simple example of logging information when a DICOS file is received.
			this->LogReceiveDicosFile("User-API CT", pCTData->GetSopInstanceUID(), errorlog);

			// Pass the data to a processing thread and return
			this->ProcessCTDataOnAnotherThread(pCTData);
			
		} else {
			this->LogReceiveDicosFile("User-API CT", "Unable to take ownership of DICOS data.", errorlog);
		}
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DX> &dx, const SDICOS::ErrorLog &errorlog)
	{
		// Handle DX object using User API
		this->LogReceiveDicosFile("User-API DX", dx->GetSopInstanceUID(), errorlog);
		this->WriteTagListing("DX",dx);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2D> &ait, const SDICOS::ErrorLog &errorlog)
	{
		// Handle AIT2D object using User API
		this->LogReceiveDicosFile("User-API AIT2D",ait->GetSopInstanceUID(), errorlog);
		this->WriteTagListing("AIT2D",ait);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3D> &ait, const SDICOS::ErrorLog &errorlog)
	{
		// Handle ATI3D object using User API
		this->LogReceiveDicosFile("User-API AIT3D", ait->GetSopInstanceUID(), errorlog);
		this->WriteTagListing("AIT3D",ait);
	}
	
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDR> &tdr, const SDICOS::ErrorLog &errorlog)
	{
		// Handle TDR object using the User API
		this->LogReceiveDicosFile("User-API TDR", tdr->GetSopInstanceUID(), errorlog);
		this->WriteTagListing("TDR",tdr);
	}
	
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::CTModule> &ct, const SDICOS::ErrorLog &errorlog)
	{
		// Handle CTModule object using Module-Level API.
		this->LogReceiveDicosFile("Module-API CT", ct->GetSopCommon().GetSopInstanceUID(), errorlog);
		this->WriteTagListing("CTModule",ct);
	}
	
	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT2DModule> &ait, const SDICOS::ErrorLog &errorlog)
	{
		// Handle AIT2DModule object using Module-Level API.
		this->LogReceiveDicosFile("Module-API AIT2D",ait->GetSopCommon().GetSopInstanceUID(), errorlog);
		this->WriteTagListing("AIT2DModule",ait);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::AIT3DModule> &ait, const SDICOS::ErrorLog &errorlog)
	{
		// Handle AIT3DModule object using Module-Level API.
		this->LogReceiveDicosFile("Module-API AIT3D", ait->GetSopCommon().GetSopInstanceUID(), errorlog);
		this->WriteTagListing("AIT3DModule",ait);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::DXModule> &dx, const SDICOS::ErrorLog &errorlog)
	{
		// Handle DXModule objects using Module-Level API.
		this->LogReceiveDicosFile("Module-API DX", dx->GetSopCommon().GetSopInstanceUID(), errorlog);
		this->WriteTagListing("DXModule",dx);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::QRModule> &qr, const SDICOS::ErrorLog &errorlog)
	{
		// Handle QRModule objects using the Module-Level API.
		this->LogReceiveDicosFile("Module-API QR",qr->GetSopCommon().GetSopInstanceUID(), errorlog);
		this->WriteTagListing("QRModule",qr);
	}

	virtual void OnReceiveDicosFile(SDICOS::Utils::DicosData<SDICOS::TDRModule> &tdr, const SDICOS::ErrorLog &errorlog)
	{
		// Handle TDRModule objects using the Module-Level API.
		this->LogReceiveDicosFile("Module-API TDR",tdr->GetSopCommon().GetSopInstanceUID(), errorlog);
		this->WriteTagListing("TDRModule",tdr);
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
		this->WriteTagListing("AM", manager);
	}

	//
	// Handle Error conditions and save error log to a text file.
	//
	virtual void OnReceiveDicosFileError(const SDICOS::ErrorLog &errorlog, const SDICOS::Utils::SessionData &sessiondata)
	{
		// Handle errors retrieving Dicos Files
		// This method is a pure virtual method and must be overridden.

		// Organize files into folders by date received
		SDICOS::DcsDate today = SDICOS::DcsDate::Today();
		std::string finalLogFolder;
		SDICOS::Format(finalLogFolder, "%s/EL_%s", m_LogFolder.c_str(), today.DcsString::Get());
			
		SDICOS::DcsTime t(SDICOS::DcsTime::Now());
		std::string filename;
		SDICOS::Format(filename, "EL_%s.el", t.DcsString::Get());

		SDICOS::Filename finalLogFilename(SDICOS::Folder(finalLogFolder),filename);
		SDICOS::DcsString logMessage;	
		if(errorlog.WriteLog(finalLogFilename))
		{
			SDICOS::Format(logMessage, "Saved Error Log to %s", finalLogFilename.GetFullPath().c_str());
		}
		else {
			SDICOS::Format(logMessage, "Failed to save Error Log to %s", finalLogFilename.GetFullPath().c_str());
		}
		LogReceiveDicosFile("OnReceiveDicosFileError", logMessage.Get());

		std::stringbuf buffer;
		std::ostream os(&buffer);
		os << finalLogFilename.GetFullPath() << " Errors Logged " << errorlog.NumErrors() << " Warnings Logged " << errorlog.NumWarnings() << "\n";
		if(errorlog.NumErrors() > 0 || errorlog.NumWarnings() > 0) {
			os << errorlog;
		}
		this->LogReceiveDicosFile("File Error", buffer.str().c_str());
	}

	//
	// Sample method to save tag listing of received data
	//
	template<typename DICOS_DATA_TYPE>
	bool WriteTagListing(const char * modality, SDICOS::Utils::DicosData<DICOS_DATA_TYPE>& data)
	{
		// Organize by modality and date received
		bool bRes(true);
		SDICOS::DcsDate today = SDICOS::DcsDate::Today();
		std::string s;
		SDICOS::Format(s, "%s/%s_%s", m_LogFolder.c_str(), modality, today.DcsString::Get());
		SDICOS::Folder finalLogFolder(s);

		if(!SDICOS::FolderExists(finalLogFolder) && !SDICOS::CreateFolder(finalLogFolder,true))
		{
			this->LogReceiveDicosFile("WriteTagListing failed", finalLogFolder.GetFullFolder().c_str());
			return false;
		}

		std::string outputFile;
		for(SDICOS::S_UINT32 i(0); i < data.GetNumOriginalData(); ++i)
		{
			//
			// If there is no filename, use the date and the time the file was received along with the IP address and port
			// 
			std::string originalFilename = data.GetOriginalDataFilename(i).GetNameAndExtension();
			if(0 == originalFilename.size())
			{
				SDICOS::DcsTime t(SDICOS::DcsTime::Now());
				SDICOS::Format(outputFile, "%s-%s:%d(%d).txt",t.DcsString::Get(), data.GetClientIP().Get(), data.GetServerPort(),i);
			}
			else
			{
				std::string originalFilename = data.GetOriginalDataFilename(i).GetName();
				SDICOS::Format(outputFile, "%s(%d).txt", originalFilename.c_str(),i);
			}
			
			//
			// Write the tag listing and values
			//
			SDICOS::Filename logFile(finalLogFolder, outputFile);
			const SDICOS::AttributeManager* pAttrManager = data.GetOriginalData(i);
			if(pAttrManager->WriteToFileAsText(logFile,true,SDICOS::AttributeManager::enumAll))
			{
				LogReceiveDicosFile("WriteTagListing succeeded", logFile.GetFullPath().c_str());
			}
			else {
				LogReceiveDicosFile("WriteTagListing failed", logFile.GetFullPath().c_str());
				bRes = false;
			}
		}
		return bRes;
	}

	void LogReceiveDicosFile(const char * source, const SDICOS::DcsString& message, const SDICOS::ErrorLog& el)
	{
#ifndef WIN32
		openlog("HostDaemonExample", LOG_CONS|LOG_PID, LOG_DAEMON);
				
		if(el.NumErrors() > 0) {
			std::stringbuf buffer;
			std::ostream os(&buffer);
			os << el<< "\n";
			syslog(LOG_NOTICE|LOG_DAEMON, "received dicos data Source: %s. Message: %s Errors: %s", source, message.Get(), buffer.str().c_str());
		}
		else {
			syslog(LOG_NOTICE|LOG_DAEMON, "received dicos data Source: %s. Message: %s No Errors.", source, message.Get());
		}
		closelog();
#else
		if(el.NumErrors() > 0) {
			std::stringbuf buffer;
			std::ostream os(&buffer);
			os << el<< "\n";
			std::cerr << "received dicos data Source: " << source << " Message: " << message.Get() << " Errors: " << buffer.str().c_str() << std::endl;
		}
		else {
			std::cerr << "received dicos data Source: " << source << " Message: " << message.Get() << " No Errors" << std::endl;
		}
#endif
	}

	void LogReceiveDicosFile(const char * source, const char * message)
	{
#ifndef WIN32
		openlog("HostDaemonExample", LOG_CONS|LOG_PID, LOG_DAEMON);
		syslog(LOG_NOTICE|LOG_DAEMON, "received dicos data Source: %s. Message: %s", source, message);
		closelog();
#else
		std::cerr << "received dicos data Source: " << source << " Message: " << message << std::endl;
#endif
	}

private:
	
	void ProcessCTDataOnAnotherThread(const SDICOS::CT* pCT)
	{
		// Stub method for processing CT Data
		
		// Callback handler is now responsible for deleting DICOS data
		delete pCT;
	}
		
	// Location on file system where files received logs are written
	std::string m_LogFolder;
};

} // namespace HostDaemonExample

void PrintUsage();

int main(int argc, char *argv[])
{
	for(int i = 0; i < argc; ++i) {if(0 == strcmp("-help", argv[i]) || 
		  (0 == strcmp("--help", argv[i])) ||
		  (0 == strcmp("/H", argv[i]))
		) {
			PrintUsage();
			exit(EXIT_SUCCESS);
		}
	}
	
	/* Parse command line args for port and IP address */
	const char * ip(NULL);
	SDICOS::S_INT32 port(0);
	for(int i = 0; i < argc; ++i) {
		if(0 == strcmp("-ip", argv[i])) {
			if(argc > (i+1)) {
				ip = argv[i+1];
			}
		} else if (0 == strcmp("-port", argv[i])) {
			if(argc > (i+1)) {
				port = atoi(argv[i+1]);
			}
		}
	}
		
	int numErrors = 0;
	if(NULL == ip) {
		std::cerr << "IP Address for listening must be specified." << std::endl;
		++numErrors;
	}
		
	if(port <= 0) {
		std::cerr << "Port for listening cannot be <= 0" << std::endl;
		++numErrors;
	}
		
	if(numErrors) {
		PrintUsage();
		return EXIT_FAILURE;
	}

	/*
		Unix specific code to fork a process and run as daemon.
	 */
#ifndef WIN32
	pid_t pid;

	/* Fork off the parent process */
	pid = fork();
	if (pid < 0) {
		std::cerr << "Failed to fork child process for daemon." << std::endl;
		openlog("DcsHostDaemon", LOG_CONS|LOG_PID, LOG_DAEMON);
		syslog(LOG_ERR|LOG_DAEMON, "Failed to fork child process for daemon. Exiting with code %d.", EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
		
		
	/* If we got a good PID, then we can exit the parent process. */
	if (pid > 0) {
		std::cerr << "Forked Child process and exiting parent process. PID " << pid << std::endl;
		openlog("DcsHostDaemon", LOG_CONS|LOG_PID, LOG_DAEMON);
		syslog(LOG_NOTICE|LOG_DAEMON, "Successfully forked child process for daemon. PID %d", pid);
		exit(EXIT_SUCCESS);
	}

	/*
		Change the file mode mask for logging.
	*/
	umask(0);

	pid_t sid = setsid();
	if(sid < 0) {
		openlog("DcsHostDaemon", LOG_CONS|LOG_PID, LOG_DAEMON);
		syslog(LOG_ERR|LOG_DAEMON, "Failed to create system idf for child process. Exiting with code %d.", EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}

	openlog("DcsHostDaemon", LOG_CONS|LOG_PID, LOG_DAEMON);
	syslog(LOG_NOTICE|LOG_DAEMON, "Successfully created sid for child process. SID %d", sid);
	std::cerr << "Created SID for child process " << sid << std::endl;
		
	
	/*
		Change working directory to /
	*/
	
	if ((chdir("/")) < 0) {
		/* Log any failure here */
		openlog("DcsHostDaemon", LOG_CONS|LOG_PID, LOG_DAEMON);
		syslog(LOG_ERR|LOG_DAEMON, "Failed to change directory to '/'. Exiting with code %d.", EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
		
	std::cerr << "Closing standard file descriptors for daemon process." << std::endl;
		
	/* Close out the standard file descriptors */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
#else
	// Place any windows code here necessary to create a service.
#endif
		
	SDICOS::Network::DcsServer server;
	HostDaemonExample::DICOSCallbackHandler handler;
		
	bool bRes(true);
		
	/// Server application name that Client connects to. Must by of type SDICOS.DcsApplicationEntity.
	/// This parameter corresponds to the Destination Application name property in the SDICOS.Network.DcsClient class
	/// and is parameter to the SendOverNetwork() method in the User-Level API objects. e.g. SDICOS.CT.
	bRes = server.SetApplicationName("ExampleHost") && bRes;
	bRes = server.SetIP(ip) && bRes;
	bRes = server.SetPort(port) && bRes;
		
	// The maximum number of milliseconds to wait on a socket read operation while no additional data is forthcoming.
	// The maximum number of milliseconds to wait for the socket to become writeable on a socket write operation. 
	// To wait indefinitely set value to 0. Default is 1000ms.
	bRes = server.SetReadTimeoutInMilliseconds(500) && bRes;
	bRes = server.SetWriteTimeoutInMilliseconds(500) && bRes;

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

	/// This call creates a thread that listens for connections and routes them to the User API callbacks
	
	/// Accept connections from all source application names to all destination application names.
	/// The Source Application Name and Destination Application Name are members of the SDICOS.Network.DcsClient class.
	/// They are also passed as parameters to the SendOverNetwork() call in the User-Level API objects. e.g. SDICOS.CT, SDICOS.AIT3D etc.
	server.IgnoreApplicationNames();
		
	// Start listening for DICOS data using the specified handler and calling the User-Level API methods.
	bRes = server.StartListening(handler, NULL, SDICOS::Network::DcsServer::enumMethodUserAPI);
		
	while(1) {
		// Put custom server code here
		SDICOS::SleepTime(10000);
	}

	return 0;
}

void PrintUsage()
{
	printf("The DcsHostDaemon listens for connections to a DcsHost on a specific port.\n");
	printf("options: [-ip,-port]\n");
	printf("-ip IP. IP Address to listen on for connections. -ip 123.123.123.123\n");
	printf("-port Port. Port to listen on for connections. -port 1234\n");
	printf("Example: HostDaemon -ip 123.234.345.456 -port 2000\n");
}
