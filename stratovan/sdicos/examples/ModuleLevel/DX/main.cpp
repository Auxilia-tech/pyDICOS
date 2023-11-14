//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2014 Stratovan Corporation. All Rights Reserved.
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
#include <cstdlib>

#include "SDICOS/DICOS.h"

using namespace SDICOS;

/*
 * The XRay Equipment object is the module-level API object that represent the
 * XRay Equipment in the DICOS Specification Section 14.
 *
 * #include "SDICOS/XRayEquipmentModule.h"
 *
 * All objects in the Stratovan DICOS Toolkit are declared in the SDICOS namespace.
 */
bool CreateXRayEquipment(SDICOS::XRayEquipmentModule& xr)
{
	/*
	 *	High and low-level API methods generally return true/false to indicate
	 *	success and failure.
	 */
	bool bRes(true);

	/*
	 * XRay Equipment has one required Floating Point Single attribute.
	 */
	float energy = 0;
	bRes = bRes && xr.SetEffectiveEnergy(energy);

	/*
	 * XRay Equipment has one optional Short Text attribute.
	 */
	DcsShortText st = "Short Text Test.";
	bRes = bRes && xr.SetMaskCharacteristics(st);

	/*
	 * XRay Equipment has five optional Code String attributes.
	 * These attributes are represented by enums.
	 */

	 // Type of G0
	bRes = bRes && xr.SetTypeG0(XRayEquipmentModule::enumGratingG0);
	bRes = bRes && xr.SetTypeG0(XRayEquipmentModule::enumMaskG0);

	// Type of G1
	bRes = bRes && xr.SetTypeG1(XRayEquipmentModule::enumGratingG1);
	bRes = bRes && xr.SetTypeG1(XRayEquipmentModule::enumOtherG1);

	// Type of G2
	bRes = bRes && xr.SetTypeG2(XRayEquipmentModule::enumGratingG2);
	bRes = bRes && xr.SetTypeG2(XRayEquipmentModule::enumOtherG2);

	// Reconstruction Algorithm for Phase Image
	bRes = bRes && xr.SetReconAlgorithmPhaseImage(XRayEquipmentModule::enumFFT);
	bRes = bRes && xr.SetReconAlgorithmPhaseImage(XRayEquipmentModule::enumModifiedFFT);
	bRes = bRes && xr.SetReconAlgorithmPhaseImage(XRayEquipmentModule::enumOtherImage);

	// Reconstruction Algorithm for Dark Image
	bRes = bRes && xr.SetReconAlgorithmDarkImage(XRayEquipmentModule::enumFFT);
	bRes = bRes && xr.SetReconAlgorithmDarkImage(XRayEquipmentModule::enumModifiedFFT);
	bRes = bRes && xr.SetReconAlgorithmDarkImage(XRayEquipmentModule::enumOtherImage);

	/*
	 * XRay Equipment has thirteen optional Floating Point Single attributes.
	 */

	// Distance from X-Ray source output to the G0 grating in CM.
	bRes = bRes && xr.SetDistanceFromG0ToSourceInCentimeters(0.0f); 
	bRes = bRes && xr.SetDistanceFromG1ToSourceInCentimeters(1.0f);
	bRes = bRes && xr.SetG0AbsorptionPeriod(3.0f);
	bRes = bRes && xr.SetG1PhasePeriod(4.0f);
	bRes = bRes && xr.SetG2AnalyzerPeriod(5.0f);
	bRes = bRes && xr.SetVisibility(6.0f);
	bRes = bRes && xr.SetAbsorptionXRDetectorSize(7.0f, 9.0f);
	bRes = bRes && xr.SetAbsorptionReconstructionVoxelSize(9.0f, 10.0f);
	bRes = bRes && xr.SetPhaseXRDetectorSize(11.0f, 12.0f);
	bRes = bRes && xr.SetPhaseReconstructionVoxelSize(13.0f, 14.0f, 15.0f);
	bRes = bRes && xr.SetDarkXRDetectorSize(16.0f, 17.0f);
	bRes = bRes && xr.SetDarkReconstructionVoxelSize(18.0f, 19.0f, 20.0f);

	return bRes;
}

bool CreateDX()
{	
	/*
	 * The DXModule object is the module-level API object that represent the
	 * Digital X-Ray (CT) Information Object Definition (IOD) in the DICOS Specification Section 8.
	 * 
	 * #include "SDICOS/ModuleDX.h"
	 *
	 * All objects in the Stratovan DICOS Toolkit are declared in the SDICOS namespace.
	 * The SDICOS::DXTypes namespace contains classes used to implement the DICOS modles in the DX IOD.
	 */
	SDICOS::DXModule dx;

	//
	// DX Data is stored as a buffer of unsigned shorts
	//
	// In this example, the DX data is stored as a 3D array which 
	// is implemented as a 1-D array of 2-D arrays so (X,Y) slices and contiguous blocks of memory.
	//
	Array3DLarge<unsigned short> vnVolume;
	
	// The DX Image only has 1 slice.
	SDICOS::S_UINT32 width(128),height(128),depth(1);
	vnVolume.SetSize(width,height,depth);

	// Buffer for volume slice that contains user data
	SDICOS::S_UINT16 * sourceSlice = new SDICOS::S_UINT16[width*height];

	//Initialize with dummy data
	memset(sourceSlice, 0, width*height*sizeof(SDICOS::S_UINT16));

	for(SDICOS::S_UINT32 z = 0; z < depth; ++z)
	{
		// 3D array is an array of 2D slices
		// Access raw data for the slice
		SDICOS::S_UINT16 * xyPlane = vnVolume[z].GetBuffer();
		
		// Set data for each element individually
		for(SDICOS::S_UINT32 i = 0; i < (width*height); ++i)
			xyPlane[i] = z;
		
		// Alternatively set slice data using memcpy
		memcpy(xyPlane, sourceSlice, width*height*sizeof(SDICOS::S_UINT16));
	}
	
	delete [] sourceSlice;
	
	/*
	 * Origin and Spacing are stored in the SDICOS::CTTypes::CTMultiframeFunctionalGroupMacros
	 */
	Point3D<float> ptOrigin;
	Point3D<float> ptSpacing;

	/// Indicate that this DX file is intended for viewing.
	/// Per the DICOS Specification Section
	///		A series of images intended for viewing by an observer, after application of any grayscale 
	///		transformations specified in the image object such as VOI LUT, shall have an Enumerated Value
	///		of "FOR PRESENTATION"
	///
	/// Sets DICOS SOP Class UID (0008, 0016) to "For Presentation" and 
	/// Presentation Intent Type (0008, 0068) to "FOR PRESENTATION"
	dx.SetForPresentation();

	/*
	 *	High and low-level API methods generally return true/false to indicate
	 *	success and failure.
	 */
	bool bRes(true);
	
	/*
	 * DcsdDateTime object takes data as "YYYYMMDD" and time as "HHMMSS"
	 */
	SDICOS::DcsDateTime dateTime;
	SDICOS::DcsDate date;
	SDICOS::DcsTime time;
	date.SetToday();
	time.SetNow();
	dateTime.Set(date,time);
	
	/*
	 * The DX Series class hold data for the Series Information Entity in the DX IOD.
	 * It includes Attributes for the DX Series Module nand the"General Series" module
	 * 
	 * #include "SDICOS/GeneralSeriesModule.h"
	 * #include "SDICOS/DXSeries.h"
	 */
	SDICOS::DXTypes::DXSeries& series = dx.GetSeries();
	bRes = bRes && series.SetAcquisitionStatus(DXTypes::DXSeries::enumSuccessful);
	bRes = bRes && series.SetDateAndTime(date,time);
	
	//
	// Set the Unique ID of the Scan for the DX Series
	// Create a unique identifier from a user defined string.
	//
	SDICOS::DcsUniqueIdentifier instanceUID("1.2.276.0.7230010.3.1.3.4126100761.8984.1407370732.884");
	bRes = bRes && series.SetInstanceUID(instanceUID);

	/*
	 * The DX Image class represents the DX Image Module
	 * 
	 * See "SDICOS/DXImage.h"
	 * 
	 * Currently the data is copied from the given array into the
	 * CTImage module.
	 */
	SDICOS::DXTypes::DXImage& image = dx.GetImage();
	bRes = bRes && image.SetBurnedInAnnotation(true);
	bRes = bRes && image.SetContentTimeAndDate(date,time);
	
	/*
	 * DX Image type has two mandatory values.
	 */
	bRes = bRes && image.SetImageType(	DXTypes::DXImage::enumOriginal,
										DXTypes::DXImage::enumIntensity);
	
	/*
	 * Instance Number, is in the General Image Module
	 */
	bRes = bRes && image.SetInstanceNumber(1);
	bRes = bRes && image.SetPhotometricInterpretation(DXTypes::DXImage::enumMonochrome2);
	
	// Select slice 0 for this DX Image
	bRes = bRes && image.SetPixelData(vnVolume[0]);
	bRes = bRes && image.SetPixelIntensityRelationship(DXTypes::DXImage::enumLinear);
	bRes = bRes && image.SetPixelIntensitySign(DXTypes::DXImage::enumLowValueLowIntensity);
	bRes = bRes && image.SetRescaleType("HU");
	bRes = bRes && image.SetPresentationLutShape(GeneralImageModule::enumIdentity);

	//
	// VOI Lut object is required because the DX object is for presentation
	// Presentation Type is "FOR PRESENTATION"
	//
	SDICOS::VoiLut& voiLut = image.GetVoiLut();
	bRes = bRes && voiLut.SetWindowCenterAndWidth(2048, 4096);

	/*
	 * Note:
	 *	The DXTypes::DXPositioning class that represents the DX Position Module 
	 *	is type 'U' User Optional and is not used in this example.
	 * 
	 * The DXTypes::DXDetector class that represents the DX Detector Module
	 * is required but all attributes are Type 2 (Required but can be NULL) or Type 3 (Optional)
	 * so none of the attributes are explicitly set.
	 */
	
	/*
	 * The XRayGeneration class represents X-Ray Generation module
	 * Required information for how x-rays were generated during the x-ray image acquisition process.
	 */
	SDICOS::DXTypes::XRayGeneration& xRayGeneration = dx.GetXRayGeneration();
	
	bRes = bRes && xRayGeneration.SetImageOrientation(1,0,0, 0,1,0);
	bRes = bRes && xRayGeneration.SetImagePosition(ptOrigin.x,ptOrigin.y,ptOrigin.z);
	bRes = bRes && xRayGeneration.SetKVP(0);
	bRes = bRes && xRayGeneration.SetXRayTubeCurrent(0);

	/*
	 * The ObjectOfInspectionModule class represents Object Of Inspection Module (OOI) 
	 */
	SDICOS::ObjectOfInspectionModule& objectOfInspection = dx.GetObjectOfInspection();
	SDICOS::ObjectOfInspectionModule::IdInfo& idInfo = objectOfInspection.GetID();
	
	bRes = bRes && idInfo.SetID("TSS4.000314");
	bRes = bRes && idInfo.SetIdAssigningAuthority("TSA");
	bRes = bRes && idInfo.SetIdType(ObjectOfInspectionModule::IdInfo::enumText);
	bRes = bRes && objectOfInspection.SetType(ObjectOfInspectionModule::enumTypeBaggage);

	/*
	 * The GeneralScanModule class represents the General Scan Module
	 */
	SDICOS::GeneralScanModule& generalScan = dx.GetGeneralScan();
	bRes = bRes && generalScan.SetScanID("TSS4.314");
	
	// Create a randomized unique identifier
	SDICOS::DcsUniqueIdentifier scanInstanceUID = SDICOS::DcsUniqueIdentifier::CreateGUID();
	bRes = bRes && generalScan.SetScanInstanceUID(scanInstanceUID);
	
	bRes = bRes && generalScan.SetStartDateAndTime(date,time);
	bRes = bRes && generalScan.SetType(GeneralScanModule::enumOperational);

	/*
	 * The GeneralEquipmentModule class represent the General Equipment Module
	 * Required information about the machine the scan was captured on.
	 */
	SDICOS::GeneralEquipmentModule& generalEquipment = dx.GetGeneralEquipment();
	bRes = bRes && generalEquipment.SetCalibrationDateAndTime("20140130", "130532.435");
	bRes = bRes && generalEquipment.SetDeviceSerialNumber("007");
	bRes = bRes && generalEquipment.SetMachineAddress("Davis, CA");
	bRes = bRes && generalEquipment.SetMachineID("Enigma");
	bRes = bRes && generalEquipment.SetMachineLocation("Dungeon");
	bRes = bRes && generalEquipment.SetManufacturer("Stratovan");
	bRes = bRes && generalEquipment.SetManufacturerModelName("Foo Bar");
	bRes = bRes && generalEquipment.SetSoftwareVersion("2.718");

	/*
		XRayEquipmentModule represents the X-Ray Equipment Module 
		Attribute related to the device's grating and detectors dusing X-Ray Image acquisition.
	*/
	SDICOS::XRayEquipmentModule& XRayEquipment = dx.GetXRayEquipment();
	bRes = bRes && CreateXRayEquipment(XRayEquipment);

	/*
	 * The SOPCommonModule class represents the SOP Common Module
	 * which defines attributes for identifying associated Service Object Pair (SOP) instances
	 */
	SDICOS::SopCommonModule& sopCommon = dx.GetSopCommon();
	bRes = bRes && sopCommon.SetSopInstanceCreationDateAndTime(date,time);
	
	SDICOS::DcsUniqueIdentifier sopInstanceUID;
	sopInstanceUID.SetGUID();
	bRes = bRes && sopCommon.SetSopInstanceUID(sopInstanceUID);
	
	/*
	 * The CommonInstanceReferenceModule class represents the Common Instance Reference Module
	 * which describes the relationships between SOP Instances referenced between modules in the same instance.
	 * In this example, we have one scan with one series.
	 */
	SDICOS::CommonInstanceReferenceModule& commonInstance = dx.GetCommonInstanceReference();
	commonInstance.AllocateReferencedSeries();
	
	SDICOS::ReferencedSeriesSequence * refSeriesSeq = commonInstance.GetReferencedSeries();
	bRes = bRes && (S_NULL != refSeriesSeq);
	bRes = bRes && refSeriesSeq->GetReferencedSeries().SetSize(1);
	
	if(refSeriesSeq)
	{
		/*
		 * Note that this series instance UID matches the one set above on the DX object
		 * with the call to dx.GetSeries().SetInstanceUID(...)
		 */
		SDICOS::Array1D<SDICOS::ReferencedSeriesSequence::ReferencedSeries> & referencedSeries = refSeriesSeq->GetReferencedSeries();

		bRes = bRes && referencedSeries[0].SetSeriesInstanceUID(instanceUID);
		
		SDICOS::Array1D<SDICOS::SopInstanceReference>& referencedInstances = referencedSeries[0].GetReferencedInstances();
		bRes = bRes && referencedInstances.SetSize(1);
		bRes = bRes && referencedInstances[0].SetClassUID(SOPClassUID::GetDXPresentation());
		
		// Specify UID with user defined string
		bRes = bRes && referencedInstances[0].SetInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.885");
	}
	
	const Filename filename("DXspimage.dcs");

	// Alternatively a Filename can be specified with a folder and name
#if 0
	Folder folder("C:\temp");
	Filename(folder,"DXspimage.dcs");
#endif
	
	/*
	 * The ErrorLog class stores warning and errors from the validation process
	 */
	ErrorLog errorlog;
	
	/*
	 * Writing the DX file validates the DX object and reports errors in the
	 * supplied ErrorLog.
	 */
	if(!dx.Write(filename, DicosFile::enumLittleEndianExplicit, errorlog)) 
	{
		errorlog.WriteLog("DXErrorLog.txt");
		std::cerr << "Failed to write DX DICOS File " << filename << " Writing errors to DXErrorLog.txt" << std::endl;
		std::cerr << errorlog << std::endl;
		bRes = false;
	} 
	else 
	{
		std::cout << "Write DX DICOS File " << filename << std::endl;
	}

	/*
	 * Reading the DICOS file 
	 */
	AttributeManager manager;
	errorlog.FreeMemory();
	if(DicosFile::Read(filename, errorlog, manager)) 
	{
		manager.WriteToFileAsText("DXspimageListings.txt");
		std::cout << "Write Attribute Listing to DXspimageListings.txt" << std::endl;
	} 
	else 
	{
		std::cerr << "Failed to read as DICOS file " << filename << std::endl;
		std::cerr << errorlog << std::endl;
		bRes = false;
	}
	

	SDICOS::DXModule dxRead;
	ErrorLog errorlogRead;
	
	if(!dxRead.Read(filename, errorlogRead)) 
	{
		std::cerr << "Failed to read as DX object " << filename << std::endl;
		std::cerr << errorlogRead << std::endl;
		bRes = false;
	} 
	else 
	{
		std::cout << "ReadDX from " << filename << std::endl;
		bRes = bRes && dx == dxRead;
		if(bRes) 
		{
			std::cout << "Verified written and read DX files are equivalent" << std::endl;
		} 
		else 
		{
			std::cerr << "Failed to verify that written and read DX files are equivalent" << std::endl;
		}
	}

	return bRes;
}

int main()
{
	return (CreateDX() ? 0 : 1);
}
