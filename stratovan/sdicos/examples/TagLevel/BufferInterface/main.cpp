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

void InitAttributeManager(SDICOS::AttributeManager &manager); //Function to initialize the AttributeManager
SDICOS::S_UINT64 InitAttributeManager(unsigned char *pBuffer, const SDICOS::S_UINT64 nBufferCapacity); //Function to initialize the AttributeManager
SDICOS::S_UINT64 InitAttributeManager(SDICOS::MemoryFile &memfile); //Function to initialize the AttributeManager

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

	SDICOS::AttributeManager manager; //Attribute manager to write
	SDICOS::ErrorLog errorlog; //Track errors when writing

	//
	// ... Attribute manager is initialized with data ...
	//
	InitAttributeManager(manager);

	bool bRetVal(true);

	//Write attribute manager to buffer. Writing can fail if the buffer is too small.
	if (!SDICOS::DicosFile::Write(memfile, errorlog, manager, SDICOS::DicosFile::enumLittleEndianExplicit))
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
	nMyDICOSDataSizeInBytes = InitAttributeManager(pMyBuffer, nMyBufferCapacityInBytes); //Size of DICOS data within buffer

	SDICOS::MemoryFile memfile; //The interface for reading and writing data from and to a buffer

	//Tell the interface it will be used for reading
	//The passed in text can be anything
	memfile.OpenReading("Reading DICOS DATA");

	//Set the buffer to read from and indicate the size of the DICOS data, not the size of the buffer
	memfile.SetBuffer(pMyBuffer, nMyDICOSDataSizeInBytes);

	//Tell the MemoryFile object that it does not own the buffer. This prevents
	//the MemoryFile from deleting the buffer when closed
	memfile.SetMemoryPolicy(SDICOS::MemoryBuffer::enumPolicy_DoesNotOwnData);

	SDICOS::AttributeManager manager; //Attribute manager to read 
	SDICOS::ErrorLog errorlog; //Tracks errors when reading

	bool bRetVal(true);

	//Read from the buffer
	if (!SDICOS::DicosFile::Read(memfile, errorlog, manager))
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
	SDICOS::AttributeManager manager; //Attribute manager to write
	SDICOS::ErrorLog errorlog;//Track errors when writing

	//
	// ... Attribute manager has been initialized with data ...
	//
	InitAttributeManager(manager);

	SDICOS::MemoryFile memfile; //The interface for reading and writing data from and to a buffer

	//Open the memory file for writing
	memfile.OpenWriting("Write");

	//Write to the MemoryFile. The MemoryFile allocates a buffer to fit the written DICOS data.
	//If writing requires a larger capacity, the buffer is reallocated to a larger size
	if (!SDICOS::DicosFile::Write(memfile, errorlog, manager, SDICOS::DicosFile::enumLittleEndianExplicit))
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
	InitAttributeManager(memfile);

	//Move to the front of the buffer to start reading
	memfile.SeekFront();

	SDICOS::AttributeManager manager; //The modality to read. Works with any of the modalities (AIT2D, AIT3D, DX, CT, QR, TDR)
	SDICOS::ErrorLog errorlog;//Track errors when reading

	bool bRetVal(true);

	//Read from the MemoryFile
	if (!SDICOS::DicosFile::Read(memfile, errorlog, manager))
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

SDICOS::S_UINT64 InitAttributeManager(unsigned char *pBuffer, const SDICOS::S_UINT64 nBufferCapacity)
{
	SDICOS::MemoryFile memfile;

	memfile.OpenReadingWriting("");
	memfile.SetMemoryPolicy(SDICOS::MemoryBuffer::enumPolicy_DoesNotOwnData);
	memfile.SetBuffer(pBuffer, nBufferCapacity);
	memfile.ChangeSize(0);

	return InitAttributeManager(memfile);
}

SDICOS::S_UINT64 InitAttributeManager(SDICOS::MemoryFile &memfile)
{
	SDICOS::AttributeManager manager;
	SDICOS::ErrorLog errorlog;

	InitAttributeManager(manager);

	if (SDICOS::DicosFile::Write(memfile, errorlog, manager, SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		return memfile.Length();
	}

	std::cout << errorlog << std::endl;
	return 0;
}

void InitAttributeManager(SDICOS::AttributeManager &manager)
{
	SDICOS::AttributeString attStr;
	SDICOS::AttributeFloat attFL;

	attStr.SetTag(0x0008, 0x0016);
	attStr.SetValue("1.1", SDICOS::AttributeString::enumUniqueIdentifier);
	manager.SetAttribute(attStr);

	attStr.SetTag(0x0008, 0x0018);
	attStr.SetValue("1.2", SDICOS::AttributeString::enumUniqueIdentifier);
	manager.SetAttribute(attStr);

	attStr.SetTag(0x4010, 0x103A);
	attStr.SetValue("V03", SDICOS::AttributeString::enumCodeString);
	manager.SetAttribute(attStr);

	attFL.SetTag(0x0100, 0x0001);
	attFL.SetValue(10.0f);
	manager.SetAttribute(attFL);

	attStr.SetTag(0x0200, 0x0010);
	attStr.SetValue("STRING", SDICOS::AttributeString::enumCodeString);
	manager.SetAttribute(attStr);
}