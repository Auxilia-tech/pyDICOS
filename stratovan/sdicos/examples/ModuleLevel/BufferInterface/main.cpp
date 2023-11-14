//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2018 Stratovan Corporation. All Rights Reserved.
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

void InitCT(SDICOS::CTModule &ct); //Function to initialize a CT object
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

	SDICOS::CTModule ct; //The DICOS modality to write into the buffer. Works with any of the modalities (AIT2D, AIT3D, DX, CT, QR, TDR)
	SDICOS::ErrorLog errorlog; //Track errors when writing

	//
	// ... CT is initialized with data ...
	//
	InitCT(ct);

	bool bRetVal(true);

	//Write CT to buffer. Writing can fail if the buffer is too small.
	if (!ct.Write(memfile, SDICOS::DicosFile::enumLittleEndianExplicit, errorlog))
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

	SDICOS::CTModule ct; //The DICOS modality to read from the buffer. Works with any of the modalities (AIT2D, AIT3D, DX, CT, QR, TDR)
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
	SDICOS::CTModule ct; //The modality to write. Works with any of the modalities (AIT2D, AIT3D, DX, CT, QR, TDR)
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
	if (!ct.Write(memfile, SDICOS::DicosFile::enumLittleEndianExplicit, errorlog))
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

	SDICOS::CTModule ct; //The modality to read. Works with any of the modalities (AIT2D, AIT3D, DX, CT, QR, TDR)
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
	SDICOS::CTModule ct;
	SDICOS::ErrorLog errorlog;

	InitCT(ct);

	if (ct.Write(memfile, SDICOS::DicosFile::enumLittleEndianExplicit, errorlog))
	{
		return memfile.Length();
	}

	std::cout << errorlog << std::endl;
	return 0;
}

void InitCT(SDICOS::CTModule &ct)
{
	SDICOS::DcsDateTime dateTime;
	SDICOS::DcsDate date;
	SDICOS::DcsTime time;
	SDICOS::Point3D<float> ptOrigin(1.0f, 2.0f, 3.0f);
	SDICOS::Point3D<float> ptSpacing(0.1f, 0.1f, 0.5f);
	SDICOS::Array3DLarge<float> vnVolume;

	const SDICOS::S_UINT32 width(5), height(5), depth(5);
	vnVolume.SetSize(width, height, depth);
	vnVolume.Zero(0);

	date.SetToday();
	time.SetNow();
	dateTime.Set(date, time);

	SDICOS::CTTypes::CTImage &image = ct.GetCTImage();

	SDICOS::CTTypes::CTSeries &series = ct.GetSeries();
	series.SetAcquisitionStatus(SDICOS::GeneralSeriesModule::enumSuccessful);
	series.SetDateAndTime(date, time);

	//
	// Set the Unique ID of the Scan for the CTSeries.
	//
	SDICOS::DcsUniqueIdentifier instanceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370732.880");
	series.SetInstanceUID(instanceUID);

	image.SetPixelData(vnVolume);
	image.SetAcquisitionDateAndTime(dateTime);
	image.SetBurnedInAnnotation(false);

	/*
	* See the documentation for SDICOS::ImagePixelMacro::PHOTOMETRIC_INTERPRETATION
	*/
	image.SetPhotometricInterpretation(SDICOS::ImagePixelMacro::enumMonochrome2);

	/*
	* The CT Image Type attribute contains 4 values.
	*/
	image.SetImageTypeCT(SDICOS::CTTypes::CTImage::enumOriginal,
		SDICOS::CTTypes::CTImage::enumPhotoelectric,
		SDICOS::CTTypes::CTImage::enumVolume,
		SDICOS::CTTypes::CTImage::enumNone);
	image.SetAcquisitionDuration(30);
	image.SetImageOrigin(SDICOS::ImageCommon::enumMachine);
	image.SetCoordinateSystem(SDICOS::ImageCommon::enumLHS);

	SDICOS::CommonImageDescription * commonImageDescription = image.GetCommonImageDescription();
	commonImageDescription->SetPixelPresentation(SDICOS::CommonImageDescription::enumPP_Monochrome);
	commonImageDescription->SetVolumeBasedCalculationTechnique(SDICOS::CommonImageDescription::enumVC_None);
	commonImageDescription->SetVolumetricProperties(SDICOS::CommonImageDescription::enumVP_Volume);

	/*
	* The CTTypes::CTMultiframeFunctionalGroups class is the CT Specific implementation of the MultiframeFunctionalGroups (Table 109) module
	* with the CT Specific Multiframe Functional Groups in Table 15
	*/
	SDICOS::CTTypes::CTMultiframeFunctionalGroups& multiframeFunctionalGroups = ct.GetMultiframeFunctionalGroups();
	multiframeFunctionalGroups.SetNumberOfFrames(vnVolume.GetDepth());
	multiframeFunctionalGroups.SetContentDateAndTime(date, time);
	multiframeFunctionalGroups.SetInstanceNumber(1001);

	/*
	* Shared Functional Groups are values that are identical between all frames
	*/
	multiframeFunctionalGroups.AllocateSharedFunctionalGroups();
	SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros *pmfg = multiframeFunctionalGroups.GetSharedFunctionalGroups();

	//
	// Modules that are marked as 'U' or User optional need to be explicitly allocated
	// by the user to indicate that their attributes are being used.
	//
	pmfg->AllocatePixelMeasurement();
	pmfg->AllocatePlaneOrientation();
	pmfg->AllocatePixelValueTransformation();
	pmfg->AllocateImageFrameType();
	pmfg->AllocateXRayDetails();
	pmfg->AllocatePixelMeasurement();

	/*
	* Set Pixel spacing in MM for X and Y directions.
	* Pixel spacing in the distance in MM between pixel centers.
	*/
	SDICOS::PixelMeasurement *pixelMeasurement = pmfg->GetPixelMeasurement();
	pixelMeasurement->SetPixelSpacingInMM(ptSpacing.x, ptSpacing.y);

	/*
	* Set slice thickness in MM (Z direction)
	*/
	pixelMeasurement->SetSliceThicknessInMM(1.0f);

	/*
	* Set plane orientation using cosines to define frame vectors.
	*/
	SDICOS::PlaneOrientation * planeOrientation = pmfg->GetPlaneOrientation();
	planeOrientation->SetImageOrientation(1, 0, 0, 0, 1, 0);

	/*
	* Set plane per frame positions along the z-axis.
	*/
	SDICOS::Array1D<SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros> &vPerFrame = ct.GetMultiframeFunctionalGroups().GetPerFrameFunctionalGroups();

	vPerFrame.SetSize(vnVolume.GetDepth());

	for (SDICOS::S_UINT32 nFrame(0); nFrame < vPerFrame.GetSize(); ++nFrame)
	{
		SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros &mfgm = vPerFrame[nFrame];
		mfgm.AllocatePlanePosition();
		mfgm.GetPlanePosition()->SetPositionInMM(ptOrigin.x, ptOrigin.y, ptOrigin.z + ptSpacing.z * float(nFrame));
	}

	/*
	* The PixelValueTransformation specifies a linear transform applied to the
	* stored values to produce values in the output units.
	*/
	SDICOS::CTTypes::CTPixelValueTransformation * pixelValueTransform = pmfg->GetPixelValueTransformation();
	pixelValueTransform && pixelValueTransform->SetRescaleIntercept(-1000);
	pixelValueTransform && pixelValueTransform->SetRescaleSlope(1);

	/*
	* String value indicating what the output units are after applying pixel transformation
	*/
	pixelValueTransform && pixelValueTransform->SetRescaleType("HU");

	/*
	* Same as as call to ct.GetCTImage().SetImageTypeCT()
	*/
	SDICOS::CTTypes::CTImageFrameType * imageFrameType = pmfg->GetImageFrameType();
	imageFrameType && imageFrameType->SetFrameType(SDICOS::CTTypes::CTImage::enumOriginal,
		SDICOS::CTTypes::CTImage::enumPhotoelectric,
		SDICOS::CTTypes::CTImage::enumVolume,
		SDICOS::CTTypes::CTImage::enumNone);

	/*
	* The CommonImageDescription data is shared between the CTImage and CTMultiframeFunctionalGroupMacros
	*/
	if (imageFrameType)
	{
		SDICOS::CommonImageDescription& description = imageFrameType->GetCommonImageDescription();
		description = *(ct.GetCTImage().GetCommonImageDescription());
	}

	/*
	* The CTXRayDetails module is required if the first value in the CT Image Type attribute is ORIGINAL or MIXED.
	* See CTImage::SetImageTypeCT which is set above by calling SetImageTypeCT
	*/
	SDICOS::CTTypes::CTXRayDetails * xRayDetails = pmfg->GetXRayDetails();
	xRayDetails->SetFilterMaterial(SDICOS::CTTypes::CTXRayDetails::enumLead);
	xRayDetails->SetFilterType(SDICOS::CTTypes::CTXRayDetails::enumNone);
	xRayDetails->SetFocalSpotSizeInMM(0);
	xRayDetails->SetKVP(0);

	/*
	* The SDICOS::FrameOfReference class represents the Frame of Reference (Table 107)
	* The Frame of Reference UID uniquely identifies a frame of reference for a series and
	* is a grouping to indicate that multiple series in a scan have the same frame of reference.
	*/
	SDICOS::DcsUniqueIdentifier frameOfReferenceUID;

	// Generate a randomized unique identifier
	frameOfReferenceUID.SetGUID();

	SDICOS::FrameOfReference& frame = ct.GetFrameOfReference();
	frame.SetFrameOfReferenceUID(frameOfReferenceUID);

	/*
	* The ObjectOfInspectionModule class represents Object Of Inspection Module (OOI) (Section 4.1, Table 10)
	*/
	SDICOS::ObjectOfInspectionModule& ooi = ct.GetObjectOfInspection();
	SDICOS::ObjectOfInspectionModule::IdInfo& idInfo = ooi.GetID();
	idInfo.SetID("TSS4.000314");
	idInfo.SetIdAssigningAuthority("Issuer-001");
	idInfo.SetIdType(SDICOS::ObjectOfInspectionModule::IdInfo::enumText);
	ooi.SetType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);

	/*
	* The GeneralScanModule class represents the General Scan Module (Section 5 Table 12)
	*/
	SDICOS::GeneralScanModule& generalScan = ct.GetGeneralScan();
	generalScan.SetScanID("TSS4.314");

	// Create unique identifier using static class method
	generalScan.SetScanInstanceUID(SDICOS::DcsUniqueIdentifier::CreateGUID());
	generalScan.SetStartDateAndTime(date, time);
	generalScan.SetType(SDICOS::GeneralScanModule::enumOperational);
	generalScan.SetDescription("MY SCAN DESCRIPTION");

	/*
	* The GeneralEquipmentModule class represent the General Equipment Module (Table 70)
	* Required information about the machine the scan was captured on.
	*/
	SDICOS::GeneralEquipmentModule& generalEquipment = ct.GetGeneralEquipment();
	generalEquipment.SetCalibrationDateAndTime(date, time);
	generalEquipment.SetDeviceSerialNumber("001");
	generalEquipment.SetMachineAddress("Ave");
	generalEquipment.SetMachineID("007");
	generalEquipment.SetMachineLocation("Check Point 1");
	generalEquipment.SetManufacturer("Stratovan");
	generalEquipment.SetManufacturerModelName("HAL");
	generalEquipment.SetSoftwareVersion("3.14");

	/*
	* The SOPCommonModule class represents the SOP Common Module (Table 82)
	* which defines attributes for identifying associated Service Object Pair (SOP) instances
	*/
	SDICOS::SopCommonModule& sopCommon = ct.GetSopCommon();
	sopCommon.SetSopInstanceCreationDateAndTime(date, time);

	SDICOS::DcsUniqueIdentifier sopInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.881");
	sopCommon.SetSopInstanceUID(sopInstanceUID);
}