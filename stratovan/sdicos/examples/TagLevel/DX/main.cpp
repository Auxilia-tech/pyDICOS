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
// This example will perform the following tasks:
// -Use the Tag-Level API to create a DX DICOS file
// -Use the Tag-Level API to create a tag listing of the DX data
// -Copy the Tag-Level API to a Module-Level API structure
// -Delete attributes with the Tag-Level API and receive errors when 
//		initializing a Module-Level API structure 
//
#include "SDICOS/DICOS.h"
#include <iostream>

//Struct representing data for a DX gathered from a scanning device
//that exists in the workflow.  
struct DXData
{
	DXData();
	~DXData();

	//DX Image Module
	unsigned short	*m_pnImage;				//Image received from scanning device
	unsigned short	m_pnImageDims[2];		//Image dimensions
	unsigned short	m_nPixelRepresentation;	//Identify image data is signed or unsigned
	unsigned short	m_nSamplesPerPixel;		//Samples per pixel in image. Example: One sample per pixel is monochrome.

	unsigned short	m_nBitsAllocated;				//DICOS requirement: Bits allocated per sample for storing image data
	unsigned short	m_nBitsStored;					//DICOS requirement: Identify from the bits allocated, how many bits represent the image sample
	unsigned short	m_nHighBit;						//DICOS requirement: Bit alignment within th bits allocated of the stored bits

	std::string		m_strRescaleIntercept;			//DICOS requirement: Add this value to image data to offset the data back to the intended origin
	std::string		m_strRescaleSlope;				//DICOS requirement: Multiply image data by this value to scale it back to the intended size
	std::string		m_strRescaleType;				//DICOS requirement: Units that represent the image data after rescaling

	std::string		m_strPresentationIntentType;	//DICOS requirement: Identify if the data is intended for presentation or processing
	std::string		m_strImageTypePixelDataCharacteristics;	//DICOS requirement: Identifies the image data as original or derived
	std::string		m_strImageTypeImageCharacteristics;		//DICOS requirement: Image data is primary or secondary (Meaning of values is unclear from DICOS specification)

	std::string		m_strPhotometricInterpretation;		//Describes how the image data is interpreted. Example: Monochrome, RGB, etc.
	std::string		m_strPixelIntensityRelationship;	//Identify the image data as linear or logarithmic
	unsigned short	m_nPixelIntensitySign;				//Describe relationship between image value and intensity. Example: Low image value means low intensity.

	std::string		m_strPresentationLutShape;			//Value is always set to IDENTITY
	std::string		m_strLossyImageCompression;			//Indicate if image data suffers from lossy compression
	std::string		m_strInstanceNumber;				//DICOS requirement: Number to identify the image within the series
	std::string		m_strBurnedInAnnotation;			//Flag if image data has burned-in annotations

	//X-Ray Generation Module
	std::string	m_pstrRowPlaneOrientation[3];		//Image data's Y-axis orientation provided by scanning device
	std::string	m_pstrColumnPlaneOrientation[3];	//Image data's X-axis orientation provided by scanning device
	std::string	m_pstrImagePosition[3];				//Image's real world offset position provided by scanning device

	std::string	m_strKVP;							//Peak kilo-voltage used when scanning provided by scanning device
	std::string	m_strXRayTubeCurrent;				//Current used when scanning provided by scanning device

	//SOP Common Module
	std::string	m_strSopInstanceUID;	//DICOS requirement: Unique ID for this image data (UID Hierarchy: Scan > Series > SOP Instance)
	std::string	m_strDicosVersion;		//DICOS requirement: DICOS version

	//Object of Inspection Module
	std::string	m_strOOIType;						//Object of Inspection Type identifies the scanned object as baggage, person, etc.

	std::string	m_strAlgorithmRoutingCode;					//Code to be used by a threat algorithm
	std::string	m_strAlgorithmRoutingCodeMeaning;			//Meaning of threat algorithm code
	std::string	m_strAlgorithmRoutingCodeSchemeDesignator;	//Designator of the threat algorithm code

	//Object of Inspection Module - ID Info
	std::string	m_strObjectOfInspectionID;						//ID for object of inspection
	std::string	m_strObjectOfInspectionIDType;					//Describes if the ID is text, RFID, etc.
	std::string	m_strObjectOfInspectionIDAssigningAuthority;	//OOI ID provider

	//General Scan Module
	std::string	m_strScanID;			//A human readable ID for the scan
	std::string	m_strScanInstanceUID;	//DICOS requirement: Unique ID for the scan (UID Hierarchy: Scan > Series > SOP Instance)
	std::string	m_strScanType;			//Indicate if the device is operational or non-operational (Meaning of values is unclear from DICOS specification)

	//DX Series Module
	std::string	m_strSeriesInstanceUID;			//DICOS requirement: Unique ID for the series (UID Hierarchy: Scan > Series > SOP Instance)
	std::string	m_strSeriesAcquisitionStatus;	//Identify the acquisition status such as successful, jam, incomplete, etc.
	std::string	m_strModality;					//Data modality. Example: AIT, CT, etc.

	//General Equipment Module
	std::string	m_strDeviceSerialNumber;			//Device's serial number
	std::string	m_strMachineAddress;				//Physical address where the device is located
	std::string	m_strMachineLocation;				//Location within the physical address where the device is located
	std::string	m_strMachineID;						//Human readable ID for the device
	std::string	m_strDeviceManufacturer;			//Device manufacturer
	std::string	m_strDeviceManufacturerModelName;	//Device model name
	std::string	m_strDeviceSoftwareVersion;			//Device's software version
};

SDICOS::Folder GetOutputFolder();

int main()
{
	SDICOS::AttributeManager	attributemanager;	//Tag-Level API
	SDICOS::Filename			filenameDX(GetOutputFolder(), "DXTagAPI.dcs");					//Output file name
	SDICOS::Filename			filenameList(GetOutputFolder(), "DXTagAPI_TagList.txt");	//Tag listing output file name
	DXData						dxdata;				//The data to make a DICOS file
	SDICOS::ErrorLog			errorlog;			//Error log
	const SDICOS::DcsDate		dsDate(SDICOS::DcsDate::Today());
	const SDICOS::DcsTime		dsTime(SDICOS::DcsTime::Now());
	SDICOS::DcsDate				dsDateCalibration;
	SDICOS::DcsTime				dsTimeCalibration;

	//Set calibration date and time
	dsDateCalibration.Set(1985, 5, 5);
	dsTimeCalibration.Set(4, 14, 13, 0);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SDICOS::AttributeManager::AttributePointer: A structure used to reference an attribute within the attribute manager

	SDICOS::Tag	tag;	//Attribute tag: (Group, Element) hex identifiers
	SDICOS::AttributeManager::AttributePointer<SDICOS::AttributeUnsignedInt16Bit>	attptrUS;	//VR: US - Unsigned Short
	SDICOS::AttributeManager::AttributePointer<SDICOS::AttributeSignedInt16Bit>		attptrSS;	//VR: SS - Signed Short
	SDICOS::AttributeManager::AttributePointer<SDICOS::AttributeSequence>			attptrSQ;	//VR: SQ - Sequences
	SDICOS::AttributeManager::AttributePointer<SDICOS::AttributePixelData>	attptrPixelData;	//Variable handles the pixel data, which can have
	//a VR of OB or OW
	SDICOS::AttributeManager::AttributePointer<SDICOS::AttributeString>	attptrStr;	//Variable handles all string VR's: 
																					//AE - Application Entity
																					//AS - Age
																					//CS - Code String
																					//DA - Date
																					//DS - Decimal String
																					//DT - Date Time
																					//IS - Integer String
																					//LO - Long String
																					//LT - Long Text
																					//PN - Person Name
																					//SH - Short String
																					//ST - Short Text
																					//TM - Time
																					//UI - Unique Identifier
																					//UT - Unlimited Text

	////////////////////////////////////////////////////////////////////////
	//Image Type - (0008, 0008) CS
	tag.Set(0x0008, 0x0008);

	//This call to 'FindAttribute' tells the attribute manager to allocate 
	//the attribute if it is not found and not to search parent sequences.
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 1;
	}

	attptrStr->SetSize(2, SDICOS::AttributeString::enumCodeString);				//Image Type is a Code String with a VM of 2
	(*attptrStr)[0] = dxdata.m_strImageTypePixelDataCharacteristics.c_str();	//First value - Pixel Data Characteristics
	(*attptrStr)[1] = dxdata.m_strImageTypeImageCharacteristics.c_str();		//Second value - Image Characteristics
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Instance Creation Date - (0008, 0012) DA 
	tag.Set(0x0008, 0x0012);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 2;
	}

	attptrStr->SetValue(dsDate);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Instance Creation Time - (0008, 0013) TM 
	tag.Set(0x0008, 0x0013);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 3;
	}

	attptrStr->SetValue(dsTime);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//SOP Class UID - (0008, 0016) UI 
	tag.Set(0x0008, 0x0016);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 4;
	}

	attptrStr->SetValue(SDICOS::SOPClassUID::GetDXProcessing(), SDICOS::AttributeString::enumUniqueIdentifier);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//SOP Instance UID - (0008, 0018) UI 
	tag.Set(0x0008, 0x0018);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 5;
	}

	attptrStr->SetValue(dxdata.m_strSopInstanceUID.c_str(), SDICOS::AttributeString::enumUniqueIdentifier);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Scan Date - (0008, 0020) DA 
	tag.Set(0x0008, 0x0020);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 6;
	}

	attptrStr->SetValue(dsDate);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Series Date (0008, 0021) DA 
	tag.Set(0x0008, 0x0021);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 7;
	}

	attptrStr->SetValue(dsDate);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Content Date - (0008, 0023) DA 
	tag.Set(0x0008, 0x0023);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 8;
	}

	attptrStr->SetValue(dsDate);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Scan Time - (0008, 0030) TM 
	tag.Set(0x0008, 0x0030);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 9;
	}

	attptrStr->SetValue(dsTime);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Series Time - (0008, 0031) TM 
	tag.Set(0x0008, 0x0031);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 10;
	}

	attptrStr->SetValue(dsTime);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Content Time - (0008, 0033) TM 
	tag.Set(0x0008, 0x0033);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 11;
	}

	attptrStr->SetValue(dsTime);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Modality - (0008, 0060) CS 
	tag.Set(0x0008, 0x0060);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 12;
	}

	attptrStr->SetValue(dxdata.m_strModality.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Presentation Intent Type - (0008, 0068) CS 
	tag.Set(0x0008, 0x0068);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 13;
	}

	attptrStr->SetValue(dxdata.m_strPresentationIntentType.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Device Manufacturer - (0008, 0070) LO 
	tag.Set(0x0008, 0x0070);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 14;
	}

	attptrStr->SetValue(dxdata.m_strDeviceManufacturer.c_str(), SDICOS::AttributeString::enumLongString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Machine Location - (0008, 0080) LO 
	tag.Set(0x0008, 0x0080);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 15;
	}

	attptrStr->SetValue(dxdata.m_strMachineLocation.c_str(), SDICOS::AttributeString::enumLongString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Machine Address - (0008, 0081) ST 
	tag.Set(0x0008, 0x0081);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 16;
	}

	attptrStr->SetValue(dxdata.m_strMachineAddress.c_str(), SDICOS::AttributeString::enumShortText);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Machine ID - (0008, 1010) SH 
	tag.Set(0x0008, 0x1010);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 17;
	}

	attptrStr->SetValue(dxdata.m_strMachineID.c_str(), SDICOS::AttributeString::enumShortString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Device Manufacturer Model Name - (0008, 1090) LO 
	tag.Set(0x0008, 0x1090);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 18;
	}

	attptrStr->SetValue(dxdata.m_strDeviceManufacturerModelName.c_str(), SDICOS::AttributeString::enumLongString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//OOI ID - (0010, 0020) LO 
	tag.Set(0x0010, 0x0020);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 19;
	}

	attptrStr->SetValue(dxdata.m_strObjectOfInspectionID.c_str(), SDICOS::AttributeString::enumLongString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//OOI ID Assigning Authority - (0010, 0021) LO 
	tag.Set(0x0010, 0x0021);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 20;
	}

	attptrStr->SetValue(dxdata.m_strObjectOfInspectionIDAssigningAuthority.c_str(), SDICOS::AttributeString::enumLongString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//OOI ID Type - (0010, 0022) CS 
	tag.Set(0x0010, 0x0022);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 21;
	}

	attptrStr->SetValue(dxdata.m_strObjectOfInspectionIDType.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Alternate ID's Sequence - (0010, 1002) SQ [Empty Sequence]
	tag.Set(0x0010, 0x1002);
	if(!attributemanager.FindAttribute(tag, attptrSQ, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 22;
	}
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//KVP - (0018, 0060) DS 
	tag.Set(0x0018, 0x0060);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 23;
	}

	attptrStr->SetValue(dxdata.m_strKVP.c_str(), SDICOS::AttributeString::enumDecimal);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Device Serial Number - (0018, 1000) LO 
	tag.Set(0x0018, 0x1000);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 24;
	}

	attptrStr->SetValue(dxdata.m_strDeviceSerialNumber.c_str(), SDICOS::AttributeString::enumLongString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Device Software Version - (0018, 1020) LO 
	tag.Set(0x0018, 0x1020);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 25;
	}

	attptrStr->SetValue(dxdata.m_strDeviceSoftwareVersion.c_str(), SDICOS::AttributeString::enumLongString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Calibration Date - (0018, 1200) DA 
	tag.Set(0x0018, 0x1200);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 26;
	}

	attptrStr->SetValue(dsDate);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Calibration Time - (0018, 1201) TM 
	tag.Set(0x0018, 0x1201);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 27;
	}

	attptrStr->SetValue(dsTime);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Detector Type - (0018, 7004) CS [NULL]
	tag.Set(0x0018, 0x7004);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 28;
	}

	attptrStr->SetSize(0, SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//X-Ray Tube Current - (0018, 8151) DS 
	tag.Set(0x0018, 0x8151);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 29;
	}

	attptrStr->SetValue(dxdata.m_strXRayTubeCurrent.c_str(), SDICOS::AttributeString::enumDecimal);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Scan Instance UID - (0020, 000D) UI 
	tag.Set(0x0020, 0x000D);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 30;
	}

	attptrStr->SetValue(dxdata.m_strScanInstanceUID.c_str(), SDICOS::AttributeString::enumUniqueIdentifier);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Series Instance UID - (0020, 000E) UI 
	tag.Set(0x0020, 0x000E);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 31;
	}

	attptrStr->SetValue(dxdata.m_strSeriesInstanceUID.c_str(), SDICOS::AttributeString::enumUniqueIdentifier);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Scan ID - (0020, 0010) SH 
	tag.Set(0x0020, 0x0010);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 32;
	}

	attptrStr->SetValue(dxdata.m_strScanID.c_str(), SDICOS::AttributeString::enumShortString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Instance Number - (0020, 0013) IS 
	tag.Set(0x0020, 0x0013);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 33;
	}

	attptrStr->SetValue(dxdata.m_strInstanceNumber.c_str(), SDICOS::AttributeString::enumInteger);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Image Position - (0020, 0032) DS 
	tag.Set(0x0020, 0x0032);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 34;
	}

	attptrStr->SetSize(3, SDICOS::AttributeString::enumDecimal);	//Image Position has a VM of 3
	(*attptrStr)[0] = dxdata.m_pstrImagePosition[0].c_str();
	(*attptrStr)[1] = dxdata.m_pstrImagePosition[1].c_str();
	(*attptrStr)[2] = dxdata.m_pstrImagePosition[2].c_str();
	///////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Image Orientation - (0020, 0037) DS 
	tag.Set(0x0020, 0x0037);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 35;
	}

	attptrStr->SetSize(6, SDICOS::AttributeString::enumDecimal);	//Image Orientation has a VM of 6
	(*attptrStr)[0] = dxdata.m_pstrRowPlaneOrientation[0].c_str();
	(*attptrStr)[1] = dxdata.m_pstrRowPlaneOrientation[1].c_str();
	(*attptrStr)[2] = dxdata.m_pstrRowPlaneOrientation[2].c_str();
	(*attptrStr)[3] = dxdata.m_pstrColumnPlaneOrientation[0].c_str();
	(*attptrStr)[4] = dxdata.m_pstrColumnPlaneOrientation[1].c_str();
	(*attptrStr)[5] = dxdata.m_pstrColumnPlaneOrientation[2].c_str();
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Samples per Pixel - (0028, 0002) US 
	tag.Set(0x0028, 0x0002);
	if(!attributemanager.FindAttribute(tag, attptrUS, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 36;
	}

	attptrUS->SetValue(dxdata.m_nSamplesPerPixel);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Photometric Interpretation - (0028, 0004) CS 
	tag.Set(0x0028, 0x0004);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 37;
	}

	attptrStr->SetValue(dxdata.m_strPhotometricInterpretation.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Rows - (0028, 0010) US 
	tag.Set(0x0028, 0x0010);
	if(!attributemanager.FindAttribute(tag, attptrUS, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 38;
	}

	attptrUS->SetValue(dxdata.m_pnImageDims[1]);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Columns - (0028, 0011) US 
	tag.Set(0x0028, 0x0011);
	if(!attributemanager.FindAttribute(tag, attptrUS, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 39;
	}

	attptrUS->SetValue(dxdata.m_pnImageDims[0]);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Bits Allocated - (0028, 0100) US 
	tag.Set(0x0028, 0x0100);
	if(!attributemanager.FindAttribute(tag, attptrUS, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 40;
	}

	attptrUS->SetValue(dxdata.m_nBitsAllocated);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Bits Stored - (0028, 0101) US 
	tag.Set(0x0028, 0x0101);
	if(!attributemanager.FindAttribute(tag, attptrUS, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 41;
	}

	attptrUS->SetValue(dxdata.m_nBitsStored);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//High Bit - (0028, 0102) US 
	tag.Set(0x0028, 0x0102);
	if(!attributemanager.FindAttribute(tag, attptrUS, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 42;
	}

	attptrUS->SetValue(dxdata.m_nHighBit);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Pixel Representation - (0028, 0103) US 
	tag.Set(0x0028, 0x0103);
	if(!attributemanager.FindAttribute(tag, attptrUS, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 43;
	}

	attptrUS->SetValue(dxdata.m_nPixelRepresentation);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Burned In Annotation - (0028, 0301) CS 
	tag.Set(0x0028, 0x0301);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 44;
	}

	attptrStr->SetValue(dxdata.m_strBurnedInAnnotation.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Pixel Intensity Relationship - (0028, 1040) CS 
	tag.Set(0x0028, 0x1040);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 45;
	}

	attptrStr->SetValue(dxdata.m_strPixelIntensityRelationship.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Pixel Intensity Sign - (0028, 1041) SS 
	tag.Set(0x0028, 0x1041);
	if(!attributemanager.FindAttribute(tag, attptrSS, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 46;
	}

	attptrSS->SetValue(dxdata.m_nPixelIntensitySign);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Rescale Intercept - (0028, 1052) DS 
	tag.Set(0x0028, 0x1052);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 47;
	}

	attptrStr->SetValue(dxdata.m_strRescaleIntercept.c_str(), SDICOS::AttributeString::enumDecimal);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Rescale Slope - (0028, 1053) DS 
	tag.Set(0x0028, 0x1053);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 48;
	}

	attptrStr->SetValue(dxdata.m_strRescaleSlope.c_str(), SDICOS::AttributeString::enumDecimal);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Rescale Type - (0028, 1054) LO 
	tag.Set(0x0028, 0x1054);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 49;
	}

	attptrStr->SetValue(dxdata.m_strRescaleType.c_str(), SDICOS::AttributeString::enumLongString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Lossy Image Compression - (0028, 2110) CS 
	tag.Set(0x0028, 0x2110);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 50;
	}

	attptrStr->SetValue(dxdata.m_strLossyImageCompression.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Acquisition Context Sequence - (0040, 0555) SQ [Empty Sequence]
	tag.Set(0x0040, 0x0555);
	if(!attributemanager.FindAttribute(tag, attptrSQ, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 51;
	}
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Presentation LUT Shape - (2050, 0020) CS 
	tag.Set(0x2050, 0x0020);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 52;
	}

	attptrStr->SetValue(dxdata.m_strPresentationLutShape.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Dicos Version - (4010, 103A) CS 
	tag.Set(0x4010, 0x103A);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 53;
	}

	attptrStr->SetValue(dxdata.m_strDicosVersion.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//OOI Type - (4010, 1042) CS 
	tag.Set(0x4010, 0x1042);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 54;
	}

	attptrStr->SetValue(dxdata.m_strOOIType.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Acquisition Status - (4010, 1044) CS 
	tag.Set(0x4010, 0x1044);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 55;
	}

	attptrStr->SetValue(dxdata.m_strSeriesAcquisitionStatus.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Scan Type - (4010, 1048) CS 
	tag.Set(0x4010, 0x1048);
	if(!attributemanager.FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 56;
	}

	attptrStr->SetValue(dxdata.m_strScanType.c_str(), SDICOS::AttributeString::enumCodeString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Algorithm Routing Code Sequence (Single Item Sequence) - (4010, 1064) SQ 
	tag.Set(0x4010, 0x1064);
	if(!attributemanager.FindAttribute(tag, attptrSQ, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 57;
	}

	attptrSQ->SetNumberOfItems(1, &attributemanager); //Allocate 1 sequence item

	//Add attributes to the sequence item using the the sequence item as an attribute manager

	//Code value - (0008, 0100) SH
	tag.Set(0x0008, 0x0100);
	if(!(*attptrSQ)[0].FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 58;
	}

	attptrStr->SetValue(dxdata.m_strAlgorithmRoutingCode.c_str(), SDICOS::AttributeString::enumShortString);

	//Code Meaning - Tag (0008, 0104) LO
	tag.Set(0x0008, 0x0104);
	if(!(*attptrSQ)[0].FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 59;
	}

	attptrStr->SetValue(dxdata.m_strAlgorithmRoutingCodeMeaning.c_str(), SDICOS::AttributeString::enumLongString);

	//Set Code Scheme Designator - (0008, 0102) SH
	tag.Set(0x0008, 0x0102);
	if(!(*attptrSQ)[0].FindAttribute(tag, attptrStr, true, false))
	{
		std::cout<<"Failed to allocate attribute "<<tag<<std::endl;
		return 59;
	}

	attptrStr->SetValue(dxdata.m_strAlgorithmRoutingCodeSchemeDesignator.c_str(), SDICOS::AttributeString::enumShortString);
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//Pixel data - (7FE0, 0010) OB/OW
	if(!attributemanager.GetPixelData(attptrPixelData, true))
	{
		std::cout<<"Failed to allocate pixel data"<<std::endl;
		return 60;
	}

	SDICOS::Array2D<SDICOS::S_UINT16> vImage;
	vImage.MoveData(dxdata.m_pnImage, dxdata.m_pnImageDims[0], dxdata.m_pnImageDims[1]);
	attptrPixelData->SetValue(vImage);
	dxdata.m_pnImage = NULL;

	////////////////////////////////////////////////////////////////////////

	//
	//
	//	All attributes set
	//
	//

	////////////////////////////////////////////////////////////////////////
	//Write DICOS file.  Print error log if it fails.
	if(SDICOS::DicosFile::Write(filenameDX, errorlog, attributemanager, SDICOS::DicosFile::enumLosslessJPEG))
	{
		std::cout<<"Created DX file: "<<filenameDX.GetFullPath()<<std::endl;
	}
	else
	{
		std::cout<<"Failed to create file.  Error log:\n"<<errorlog<<std::endl;
		return 61;
	}
	////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////
	//Write tag list
	if(attributemanager.WriteToFileAsText(filenameList))
	{
		std::cout<<"Create tag listing: "<<filenameList.GetFullPath()<<std::endl;
	}
	else
	{
		std::cout<<"Failed to create tag listing"<<std::endl;
		return 62;
	}
	////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////
	//Pass Tag-Level API into DX Module-Level API.
	//Print error log if initialization fails or if warnings are detected on success.
	SDICOS::DXModule dxmodule;

	errorlog.FreeMemory(); //Clear error log
	if(dxmodule.SetAttributes(attributemanager, errorlog))
	{
		std::cout<<"Initialized DX Module-Level API with Tag-Level API"<<std::endl;

		if(errorlog.HasWarnings())
		{
			std::cout<<"Encountered warnings. Error log:\n"<<errorlog<<std::endl;
		}
	}
	else
	{
		std::cout<<"Failed to initialize DX Module-Level API with Tag-Level API.\nError log:\n"<<errorlog<<std::endl;
		return 63;
	}
	////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////
	//Delete Attributes: Only requires tag

	std::cout<<"Removing required attributes Date of Last Caibration(0x0018,0x1200) and Time of Last Calibration(0x00180x1201) to test error log messages."<<std::endl;
		
	//Calibration Date - (0018, 1200) DA 
	attributemanager.DeleteAttribute(0x0018, 0x1200);

	//Calibration Time - (0018, 1201) TM 
	attributemanager.DeleteAttribute(0x0018, 0x1201);
	////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////
	//Pass Tag-Level API into DX Module-Level API with the missing required calibration attributes.
	//Print error log if initialization fails or if warnings are detected on success.

	dxmodule.FreeMemory();	//Clear DX module
	errorlog.FreeMemory();	//Clear error log
	if(dxmodule.SetAttributes(attributemanager, errorlog))
	{
		std::cout<<"Initialized DX Module-Level API with Tag-Level API"<<std::endl;

		if(errorlog.HasWarnings())
		{
			std::cout<<"Encountered warnings. Error log:\n"<<errorlog<<std::endl;
		}
	}
	else
	{
		std::cout<<"Failed to initialize DX Module-Level API with Tag-Level API.\nError log:\n"<<errorlog<<std::endl;

		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////

	return 0;
}

SDICOS::Folder GetOutputFolder()
{
#if WIN32
	return SDICOS::Folder(SDICOS::GetExecutableFolder().GetFullFolder() + "..\\..\\..\\");
#else
	return SDICOS::Folder(SDICOS::GetExecutableFolder().GetFullFolder());	
#endif
}

DXData::DXData()
{
	m_strSopInstanceUID = SDICOS::DcsUniqueIdentifier::CreateGUID().Get();
	m_strPresentationIntentType = "FOR PROCESSING";
	m_strImageTypePixelDataCharacteristics = "ORIGINAL";
	m_strImageTypeImageCharacteristics = "PRIMARY";
	m_strPhotometricInterpretation = "MONOCHROME2";
	m_strPixelIntensityRelationship = "LIN";
	m_strRescaleIntercept = "0";
	m_strRescaleSlope = "1";
	m_strRescaleType = "HU";
	m_strInstanceNumber = "1";
	m_strBurnedInAnnotation = "NO";
	m_strKVP = "5000";
	m_strXRayTubeCurrent = "111";
	m_strObjectOfInspectionID = "10";
	m_strObjectOfInspectionIDAssigningAuthority = "ID Assigning Authority";
	m_strObjectOfInspectionIDType = "RFID";
	m_strOOIType = "BAGGAGE";
	m_strScanID = "Scan ID";
	m_strScanInstanceUID = SDICOS::DcsGUID::GenerateAsString().Get();
	m_strScanType = "OPERATIONAL";
	m_strSeriesInstanceUID = SDICOS::DcsGUID::GenerateAsString().Get();
	m_strSeriesAcquisitionStatus = "SUCCESSFUL";
	m_strDeviceSerialNumber = "123456987";
	m_strMachineAddress = "Machine Address";
	m_strMachineLocation = "Machine Location";
	m_strMachineID = "Machine ID";
	m_strDeviceManufacturer = "Device Manufacturer";
	m_strDeviceManufacturerModelName = "Device Manufacturer Model Name";
	m_strDeviceSoftwareVersion = "Device Software Version";
	m_strPresentationLutShape = "IDENTITY";
	m_strLossyImageCompression = "00";
	m_nBitsAllocated = 16;
	m_nBitsStored = 16;
	m_nHighBit = 15;
	m_nPixelRepresentation = 0;
	m_nSamplesPerPixel = 1;
	m_nPixelIntensitySign = 1;
	m_strModality = "DX";
	m_strDicosVersion = "V02";
	m_strAlgorithmRoutingCode = "ALG13-9";
	m_strAlgorithmRoutingCodeMeaning = "Half R-to-Q Quarter Spin Detection";
	m_strAlgorithmRoutingCodeSchemeDesignator = "Designator55";

	m_pstrRowPlaneOrientation[0] = "0";
	m_pstrRowPlaneOrientation[1] = "1";
	m_pstrRowPlaneOrientation[2] = "0";

	m_pstrColumnPlaneOrientation[0] = "1";
	m_pstrColumnPlaneOrientation[1] = "0";
	m_pstrColumnPlaneOrientation[2] = "0";

	m_pstrImagePosition[0] = m_pstrImagePosition[1] = m_pstrImagePosition[2] = "0";

	m_pnImageDims[0] = 200;
	m_pnImageDims[1] = 400;

	try
	{
		m_pnImage = new unsigned short[m_pnImageDims[0] * m_pnImageDims[1]];
		memset(m_pnImage, 800, sizeof(unsigned short) * m_pnImageDims[0] * m_pnImageDims[1]);
	}
	catch(...)
	{
		m_pnImage = NULL;
	}
}

DXData::~DXData()
{
	if(NULL != m_pnImage)
		delete [] m_pnImage;
}
