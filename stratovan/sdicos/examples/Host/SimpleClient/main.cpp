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
// This example shows how to utilize the User-Level API in order to send a 
// CT object over the network.
//
// The accompanying HostDaemon executable can be used to create a DICOS Server that 
// listens for and accepts connections from DICOS client.
// 
// To run the example first start the DICOS Server with an ip address and port and then
// run SimpleClient with the same ip address and port. If the transfer is successful, log 
// messages should appear somewhere in /var/log depending upon how the system logging is setup.
//
// The log messages on a successful transfer should look like:
// HostDaemonExample[1705]: received dicos data via User-API CT. Id 1357197849.30379.8598.66202.21690000.Errors
//
#include "SDICOS/DICOS.h" // DICOS include header
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
#endif

/**
 * Initialize a CT object with valid data.
 * @param ct
 */
void InitCT(SDICOS::CT &ct);

void PrintUsage();

int main(int argc, char * argv[])
{
	for(int i = 0; i < argc; ++i) 
	{
		if(0 == strcmp("-help", argv[i]) || 
		  (0 == strcmp("--help", argv[i])) ||
		  (0 == strcmp("/H", argv[i]))
		) 
		{
			PrintUsage();
			exit(EXIT_SUCCESS);
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
		
	if(port <= 0) {
		std::cerr << "Port for listening cannot be <= 0" << std::endl;
		++numErrors;
	}
		
	if(numErrors) 
	{
		PrintUsage();
		return EXIT_FAILURE;
	}

	// This example uses the User-Level API CT object to send data to the DICOS Server.
	SDICOS::CT ct;
	SDICOS::ErrorLog errorlog;

	// Initialize the CT object
	InitCT(ct);

	// Send the CT object over the network to a server
	// The SendOverNetwork method in the SDICOS::CT class and other User-Level API classes
	// takes care of establishing the connection, sending the DICOS data, and closing the connection
	if(!ct.SendOverNetwork(	port,			// Port
							ip,				// IP Address
							"SrcApp",		// Source Application Name. Name of application using calling this function.
							"ExampleHost",	// Destination Application Name. Name of application accepting the client's connection.
							errorlog))		// Error log
	{
		//Print error log if the transmission fails
		std::cout<<"Failed to send data across network:"<<std::endl;
		std::cout<<errorlog<<std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Send CT file succeeded." << std::endl;
		
	//
	// Alternatively the Client implementation can create a DcsClient object
	// and keep the connection open for sending multiple DICOS files
	// This model can used for a persistent client application that generates DICOS files.
	// 
	SDICOS::Network::DcsClient client;

	bool bRes(true);	// client methods return true/false to indicate success and failure
		
	bRes = client.SetServerPortandIP(port,ip) && bRes;
	bRes = client.SetSourceApplication("SrcApp") && bRes;
	bRes = client.SetDestinationApplication("ExampleHost") && bRes;
	
	// For a client machine with multiple IP address, e.g. > 1 network card, this method is used to indicate which IP address to use for sending
	//bRes = client.SetClientIP() && bRes;
		
	if(!bRes) 
	{
		// print error message
		return EXIT_FAILURE;
	}

	//Connect to host
	if(!client.ConnectToServer())
	{
		// handler error
		return EXIT_FAILURE;
	}

	// Send multiple CT files before closing connection
	ct.SetSopInstanceUID(SDICOS::DcsUniqueIdentifier::CreateGUID());
	bRes = ct.SendOverNetwork(client, errorlog) && bRes;

	if(!bRes) 
	{
		// Handle failure
		return EXIT_FAILURE;
	}

	ct.SetSopInstanceUID(SDICOS::DcsUniqueIdentifier::CreateGUID());
	bRes = ct.SendOverNetwork(client,errorlog) && bRes;

	if(!bRes) {
		// Handle failure
		return EXIT_FAILURE;
	}

	client.DisconnectFromServer();

	return EXIT_SUCCESS;
}

// Initialize a CT object with User-Level API
void InitCT(SDICOS::CT &ct)
{
	const SDICOS::DcsDate strDate(SDICOS::DcsDate::Today()); 
	const SDICOS::DcsTime strTime(SDICOS::DcsTime::Now());
	SDICOS::Vector3D<float> vecRowOrientation;
	SDICOS::Vector3D<float> vecColumnOrientation;

	ct.FreeMemory();

	vecRowOrientation.Set(1,0,0);
	vecColumnOrientation.Set(0,1,0);

	ct.SetFrameOfReferenceUID("4.4.6.6.0.0.8.8.7");
	ct.SetImageAcquisitionDateAndTime(strDate, strTime);
	ct.SetBurnedInAnnotation(false);
	ct.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);
	ct.SetImageType(SDICOS::CTTypes::CTImage::enumPhotoelectric);
	ct.SetImageAcquisitionDuration(5000);
	ct.SetContentDateAndTime(strDate, strTime);
	ct.SetOOIID("10");
	ct.SetOOIIDAssigningAuthority("OOI ID Assigning Authority");
	ct.SetOOIIDType(SDICOS::ObjectOfInspectionModule::IdInfo::enumRFID);
	ct.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);
	ct.SetScanID("Scan ID");
	ct.GenerateScanInstanceUID();
	ct.SetScanStartDateAndTime(strDate, strTime);
	ct.SetScanType(SDICOS::GeneralScanModule::enumOperational);
	ct.GenerateSeriesInstanceUID();
	ct.SetSeriesDateAndTime(strDate, strTime);
	ct.SetSeriesAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful);
	ct.SetDeviceCalibrationDateAndTime(strDate, strTime);
	ct.SetDeviceSerialNumber("123456987");
	ct.SetMachineAddress("Machine Address");
	ct.SetMachineLocation("Machine Location");
	ct.SetMachineID("Machine ID");
	ct.SetDeviceManufacturer("Device Manufacturer");
	ct.SetDeviceManufacturerModelName("Device Manufacturer Model Name");
	ct.SetDeviceSoftwareVersion("Device Software Version");
	ct.SetSopInstanceCreationDateAndTime(strDate, strTime);
	ct.GenerateSopInstanceUID();

	SDICOS::Section *psection = S_NULL;

	ct.SetNumberOfSections(1);
	psection = ct.GetSectionByIndex(0);

	psection->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumAluminum);
	psection->SetFocalSpotSizeInMM(10);
	psection->SetKVP(7000);
	psection->SetPlaneOrientation(vecRowOrientation, vecColumnOrientation);
	psection->SetPositionInMM(0,0,2000);
	psection->SetSpacingInMM(1,1,1);
	psection->GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, 32, 32, 32);
	psection->GetPixelData().GetUnsigned16()->Zero(20);
}

void PrintUsage()
{
	printf("The SimpleClient example send a DICOS file to a DcsHost.\n");
	printf("options: [-ip,-port]\n");
	printf("-ip IP. IP Address to listen on for connections. -ip 123.123.123.123\n");
	printf("-port Port. Port to listen on for connections. -port 1234\n");
	printf("Example: SimpleClient -ip 123.234.345.456 -port 2000\n");
}
