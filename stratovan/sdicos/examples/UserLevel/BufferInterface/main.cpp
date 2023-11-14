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
#include "SDICOS/DICOS.h"
#include <iostream>

void InitCT(SDICOS::CT &ct); //Function to initialize a CT object
SDICOS::S_UINT64 InitCT(unsigned char *pBuffer, const SDICOS::S_UINT64 nBufferCapacity); //Function to initialize a CT object
SDICOS::S_UINT64 InitCT(SDICOS::MemoryFile &memfile); //Function to initialize a CT object

bool WriteToProvidedBuffer()
{
	//This example covers how to write to a pre-allocated buffer

	unsigned char *pMyBuffer(S_NULL); //The buffer to write DICOS data into
	const SDICOS::S_UINT64 nMyBufferCapacityInBytes(10000); //Buffer capacity in bytes
	SDICOS::S_UINT64 nDICOSDataSizeInBytes(0); //The size of the DICOS data within the buffer

	pMyBuffer = new unsigned char[nMyBufferCapacityInBytes]; //Pre-allocate buffer

	SDICOS::MemoryFile memfile; //The interface for reading and writing data from and to a buffer
	
	//Tell the interface it will be used for writing
	//The passed in text can be anything
	memfile.OpenWriting("Writing DICOS Data");

	//Tell the MemoryFile object that it does not own the buffer. This prevents
	//the MemoryFile from reallocating the buffer if writing requires more space 
	//and deleting the buffer when the MemoryFile is closed.
	memfile.SetMemoryPolicy(SDICOS::MemoryBuffer::enumPolicy_DoesNotOwnData);

	//Connect the interface to the buffer and provide its capacity
	memfile.SetBuffer(pMyBuffer, nMyBufferCapacityInBytes);

	//Set the used buffer size to zero bytes
	memfile.ChangeSize(0);

	//This functions returns the buffer's capacity: nMyBufferCapacityInBytes bytes
	memfile.GetAllocatedBufferSize();

	//This function returns the size of the buffer used: 0 bytes
	memfile.Length();

	SDICOS::CT ct; //The DICOS modality to write into the buffer. Works with any of the modalities (AIT2D, AIT3D, DX, CT, QR, TDR)
	SDICOS::ErrorLog errorlog; //Track errors when writing

	//
	// ... CT is initialized with data ...
	//
	InitCT(ct);

	bool bRetVal(true);

	//Write CT to buffer. Writing can fail if the buffer is too small.
	if (!ct.Write(memfile, errorlog))
	{
		//Print error log if writing failed
		std::cout << errorlog << std::endl;
		bRetVal = false;
	}
	else
	{
		//Print out the size of the DICOS data within the buffer object
		nDICOSDataSizeInBytes = memfile.Length();
		std::cout << "DICOS data: " << nDICOSDataSizeInBytes << " bytes" << std::endl;
	}

	//Closing the MemoryFile disconnects it from the buffer if it does not own the buffer; otherwise,
	//it deletes the buffer
	memfile.Close();

	delete[] pMyBuffer; //Deallocate memory
	return bRetVal;
}
///EndWriteToProvidedBuffer

bool ReadFromProvidedBuffer()
{
	//This example covers how to read from a provided buffer that contains
	//DICOS data.  The buffer, pMyBuffer, is assumed to have been filled with
	//DICOS data and has a capacity defined by nMyBufferSizeInBytes. The DICOS
	//data occupies a size of nMyDICOSDataSizeInBytes in that buffer.

	unsigned char *pMyBuffer(S_NULL); //The user provided buffer
	const SDICOS::S_UINT64 nMyBufferCapacityInBytes(10000); //The buffer is allocated to his capacity
	SDICOS::S_UINT64 nMyDICOSDataSizeInBytes(0);//DICOS data uses this amount of the buffer

	//
	// ... Buffer is filled with DICOS data ...
	//
	pMyBuffer = new unsigned char[nMyBufferCapacityInBytes];
	nMyDICOSDataSizeInBytes = InitCT(pMyBuffer, nMyBufferCapacityInBytes); //Size of DICOS data within buffer

	SDICOS::MemoryFile memfile; //The interface for reading and writing data from and to a buffer

	//Tell the interface it will be used for reading
	//The passed in text can be anything
	memfile.OpenReading("Reading DICOS DATA");

	//Set the buffer to read from and indicate the size of the DICOS data, not the size of the buffer
	memfile.SetBuffer(pMyBuffer, nMyDICOSDataSizeInBytes);

	//Tell the MemoryFile object that it does not own the buffer. This prevents
	//the MemoryFile from deleting the buffer when closed
	memfile.SetMemoryPolicy(SDICOS::MemoryBuffer::enumPolicy_DoesNotOwnData);

	SDICOS::CT ct; //The DICOS modality to read from the buffer. Works with any of the modalities (AIT2D, AIT3D, DX, CT, QR, TDR)
	SDICOS::ErrorLog errorlog; //Tracks errors when reading

	bool bRetVal(true);

	//Read from the buffer
	if (!ct.Read(memfile, errorlog))
	{
		//Print error log if reading failed
		std::cout << errorlog << std::endl;
		bRetVal = false;
	}

	//Closing the MemoryFile disconnects it from the buffer if it does not own the buffer; otherwise,
	//it deletes the buffer
	memfile.Close();

	delete[] pMyBuffer; //Delete buffer
	return bRetVal;
}
///EndReadFromProvidedBuffer

bool WriteToBuffer()
{
	SDICOS::CT ct; //The modality to write. Works with any of the modalities (AIT2D, AIT3D, DX, CT, QR, TDR)
	SDICOS::ErrorLog errorlog;//Track errors when writing

	//
	// ... CT has been initialized with data ...
	//
	InitCT(ct);

	SDICOS::MemoryFile memfile; //The interface for reading and writing data from and to a buffer

	//Open the memory file for writing
	memfile.OpenWriting("Write");

	//Write to the MemoryFile. The MemoryFile allocates a buffer to fit the written DICOS data.
	//If writing requires a larger capacity, the buffer is reallocated to a larger size
	if (!ct.Write(memfile, errorlog))
	{
		std::cout << errorlog << std::endl;
		return false;
	}

	//Print the size of the DICOS data in the memory file
	std::cout << "DICOS Data Size: " << memfile.Length() << " bytes" << std::endl;

	//Print the allocated buffer size
	std::cout << "Buffer Capacity: " << memfile.GetAllocatedBufferSize() << " bytes" << std::endl;

	//Get the buffer object. The MemoryFile owns the data and will delete it when closed.
	memfile.GetBuffer();

	//To recycle the MemoryFile for writing again without deallocating the 
	//buffer, call ChangeSize() and pass in zero bytes. This retains the allocated
	//buffer, but sets the used size to zero bytes
	memfile.ChangeSize(0);

	//Print MemoryFile info
	std::cout << "Used Buffer Size: " << memfile.Length() << " bytes" << std::endl;
	std::cout << "Buffer Capacity: " << memfile.GetAllocatedBufferSize() << " bytes" << std::endl;

	//Close the MemoryFile, which deletes the buffer
	memfile.Close();
	return true;
}
///EndWriteToBuffer

bool ReadFromBuffer()
{
	SDICOS::MemoryFile memfile; //The interface for reading and writing data from and to a buffer

	//Open the MemoryFile to read and write
	memfile.OpenReadingWriting("Read and Write");

	//
	// ... DICOS data has been written to the MemoryFile ...
	//
	InitCT(memfile);

	//Move to the front of the buffer to start reading
	memfile.SeekFront();

	SDICOS::CT ct; //The modality to read. Works with any of the modalities (AIT2D, AIT3D, DX, CT, QR, TDR)
	SDICOS::ErrorLog errorlog;//Track errors when reading

	bool bRetVal(true);

	//Read from the MemoryFile
	if (!ct.Read(memfile, errorlog))
	{
		std::cout << errorlog << std::endl;
		bRetVal = false;
	}

	//Close the MemoryFile
	memfile.Close();
	return bRetVal;
}
///EndReadFromBuffer

void FileAndBuffer()
{
	// This example show how to read a file into a buffer and 
	// how to write to a file from a buffer

	SDICOS::MemoryFile memfile; //The buffer used to read into then write from

	///////////////////////////////////
	//Read from a file into a buffer
	{
		SDICOS::File file; //File interface class
		SDICOS::Filename filenameSrc("MyFile.dat"); //The file to read. Enter a valid file name.

		//Open the file for reading. Returns false if the file is 
		//not found or could not be opened
		if (!file.OpenReading(filenameSrc))
			return;

		//Initialize the buffer for reading and writing data
		memfile.OpenReadingWriting("");

		//Read the entire file into the buffer
		if (!memfile.ReadFrom(file, file.Length()))
			return;

		//Close the file
		file.Close();

		//Move the file pointer to the front of the buffer so 
		//reads will begin at the front of the buffer
		memfile.SeekFront();

		//Closing the buffer will delete the data
		//memfile.Close();
	}

	///////////////////////////////
	//Write from a buffer to file
	{
		SDICOS::File file; //File interface class
		SDICOS::Filename filenameDst("MyOutput.dat"); //The file to write out. Enter a valid file name.

		//Open the file for writing. Returns false if the file could not be created.
		if (!file.OpenWriting(filenameDst))
			return;

		//Write the buffer to file
		if (!file.Write(memfile.GetBuffer(), memfile.Length(), "Buffer"))
			return;

		//Closing the buffer delete the data
		memfile.Close();

		//Close the file
		file.Close();
	}
}
///EndFileAndBuffer

int main()
{
	bool bRetVal(true);

	//////////////////////////////
	//These two examples show how to read from and write to
	//a user provided buffer

	bRetVal = WriteToProvidedBuffer() && bRetVal; //Write example
	bRetVal = ReadFromProvidedBuffer() && bRetVal; //Read example

	//////////////////////////////

	//////////////////////////////
	//These two examples show how to read from and write to
	//a MemoryFile object

	bRetVal = WriteToBuffer() && bRetVal; //Write example
	bRetVal = ReadFromBuffer() && bRetVal; //Read example

	//////////////////////////////

	// This example show how to read a file into a buffer and 
	// how to write to a file from a buffer
	FileAndBuffer();

	return bRetVal ? 0 : 1;
}

////////////////////////////////////////////////////////
// Utility functions to initialize data for example functions

SDICOS::S_UINT64 InitCT(unsigned char *pBuffer, const SDICOS::S_UINT64 nBufferCapacity)
{
	SDICOS::MemoryFile memfile;

	memfile.OpenReadingWriting("");
	memfile.SetMemoryPolicy(SDICOS::MemoryBuffer::enumPolicy_DoesNotOwnData);
	memfile.SetBuffer(pBuffer, nBufferCapacity);
	memfile.ChangeSize(0);

	return InitCT(memfile);
}

SDICOS::S_UINT64 InitCT(SDICOS::MemoryFile &memfile)
{
	SDICOS::CT ct;
	SDICOS::ErrorLog errorlog;
	
	InitCT(ct);

	if (ct.Write(memfile, errorlog, SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		return memfile.Length();
	}

	std::cout << errorlog << std::endl;
	return 0;
}

void InitCT(SDICOS::CT &ct)
{
	const SDICOS::DcsDate strDate(SDICOS::DcsDate::Today());	//Constant for today's date
	const SDICOS::DcsTime strTime(SDICOS::DcsTime::Now());		//Constant for current time

	ct.SetOOIID("10");	//Object of Inspection ID
	ct.GenerateSopInstanceUID();		//Obtain an SOP Instance UID
	ct.GenerateScanInstanceUID();		//Obtain an SOP Scan Instance UID
	ct.GenerateSeriesInstanceUID();		//Obtain an SOP Series Instance UID

	ct.SetImageAcquisitionDateAndTime(strDate, strTime);	//Date and time of volume acquisition
	ct.SetBurnedInAnnotation(false);									//No burned-in annotations

																		//Low values in volume data correspond to low intensity values
	ct.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);

	ct.SetImageType(SDICOS::CTTypes::CTImage::enumPhotoelectric); //Photoelectric acquisition
	ct.SetImageAcquisitionDuration(5000);		//Time taken for acquisition
	ct.SetContentDateAndTime(strDate, strTime);	//Date and time of content acquisition
	ct.SetOOIIDAssigningAuthority("OOI ID Assigning Authority");	//Name of OOI ID assigning authority
	ct.SetOOIIDType(SDICOS::ObjectOfInspectionModule::IdInfo::enumRFID); //OOI ID corresponds to an RFID
	ct.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage); //OOI is baggage
	ct.SetScanID("Scan ID"); //Scan ID
	ct.SetScanStartDateAndTime(strDate, strTime); //Date and time scan started
	ct.SetScanType(SDICOS::GeneralScanModule::enumOperational); //Operational scan
	ct.SetSeriesDateAndTime(strDate, strTime);	//Date and time of series creation
	ct.SetSeriesAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful); //Acquisition was successfully captured
	ct.SetDeviceCalibrationDateAndTime(strDate, strTime); //Date and time of device calibration
	ct.SetDeviceSerialNumber("123456987");	//Device serial number
	ct.SetMachineAddress("Machine Address"); //Machine address (Physical address)
	ct.SetMachineLocation("Machine Location");//Machine location (Location on site)
	ct.SetMachineID("Machine ID"); //Machine ID
	ct.SetDeviceManufacturer("Device Manufacturer"); //Device manufacturer
	ct.SetDeviceManufacturerModelName("Device Manufacturer Model Name");	//Model name
	ct.SetDeviceSoftwareVersion("Device Software Version"); //Device's software version
	ct.SetSopInstanceCreationDateAndTime(strDate, strTime); //Date and time of SOP instance creation

	ct.SetNumberOfSections(1);	//Create a single section
	SDICOS::Section *psection = ct.GetSectionByIndex(0);	//Get a reference to the section

	psection->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumAluminum); //Aluminum filter
	psection->SetFocalSpotSizeInMM(10); //10mm nominal focal spot size
	psection->SetKVP(7000); // 7000 Peak Kilo Voltage

	psection->GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit, 5, 5, 5);
	psection->GetPixelData().GetUnsigned16()->Zero(0);	//Initialize all values to 0
}