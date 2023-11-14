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

void InitQR(SDICOS::QR &qr); //Data initializer for the example

//Declare a custom Module-Level API class for use by the User-Level API.
//This class overrides functions to read, write, update, and validate data to include the private data.
class CustomQRModule : public SDICOS::QRModule
{
public:
	///////////////////////////
	//Provide constructors, destructor, copy, compare, and de-allocate functions
	CustomQRModule();
	CustomQRModule(const CustomQRModule &qr);
	virtual ~CustomQRModule();

	virtual void FreeMemory();

	CustomQRModule& operator=(const CustomQRModule &qr);

	bool operator==(const CustomQRModule &qr)const;
	bool operator!=(const CustomQRModule &qr)const;
	///////////////////////////

	//Initialize this class with values extracted from AttributeManager
	//This function must be overridden to retrieve data
	virtual bool SetAttributes(const SDICOS::AttributeManager &attribManager, SDICOS::ErrorLog &errorlog);

	//Define a static allocator function for this class.
	//This will be used to tell DicosLoader and DcsServer to internally allocate this class
	static QRModule* AllocateCustom() { return new QRModule; }
protected:
	//Save values in AttributeManager
	//This function must be overridden to save data
	virtual bool GetAttributes(SDICOS::AttributeManager &attribManager, SDICOS::ErrorLog &errorlog)const;

	//Update this class's data if the data is present in AttributeManager
	//This function does not need to be overridden
	virtual bool UpdateAttributes(const SDICOS::AttributeManager &attribManager, SDICOS::ErrorLog &errorlog);

	//Validate this class
	//This function must be overridden to validate data
	virtual bool IsValid(const SDICOS::AttributeManager &attribManager, SDICOS::ErrorLog &errorlog)const;

	//Initialize the private data tags
	void InitTags();
public:
	//The private data as attributes
	SDICOS::AttributeString m_attPrivateText;
	SDICOS::AttributeFloat	m_attPrivateValue;
};

//Declare a custom User-Level API class
//This class overrides functions to read, write, update, and validate data to include the private data.
class CustomQR : public SDICOS::QR
{
public:
	///////////////////////////
	//Provide constructor, destructor, copy, compare, de-allocate functions
	CustomQR();
	CustomQR(const CustomQR &qr);
	virtual ~CustomQR();

	CustomQR& operator=(const CustomQR &qr);

	virtual void FreeMemory();

	//Custom default initializer
	void DefaultInit();

	bool operator==(const CustomQR &qr)const;
	bool operator!=(const CustomQR &qr)const;
	///////////////////////////

	//Define a static allocator function for this class.
	//This will be used to tell DicosLoader and DcsServer to internally allocate this class
	static QR* AllocateCustom() { return new CustomQR; }
protected:

	//Override the allocate function so internal SDICOS::QR functions allocate the
	//our custom Module-Level API class
	virtual SDICOS::QRModule* AllocateModule()const { return new CustomQRModule; }

	//Save data to QRModule
	virtual bool WriteDerived_internal(SDICOS::QRModule &qr, SDICOS::ErrorLog &errorlog)const;

	//Load data from QRModule
	virtual bool ReadDerived_internal(const SDICOS::QRModule &qr, SDICOS::ErrorLog &errorlog);

public:
	//The private data
	std::string m_strPrivateText;
	float		m_fPrivateValue;
};

int main()
{
	CustomQR customQR; //Our custom User-Level API QR class

	//Set values for the private data
	customQR.m_fPrivateValue = 1.2f;
	customQR.m_strPrivateText = "Sampled Sample Text";

	InitQR(customQR); //Initialize base class data

	SDICOS::MemoryFile memfile; //Buffer to write data into
	SDICOS::ErrorLog errorlog; //Error log

	memfile.OpenReadingWriting("QR Memoryfile"); //Setup buffer to be written into

	//Write the QR data to the memory buffer
	if (!customQR.Write(memfile, errorlog, SDICOS::DicosFile::enumLittleEndianExplicit))
	{
		std::cout << errorlog << std::endl;
		return 1;
	}

	memfile.SeekFront(); //Move to front of buffer

	/*
		Read data into a new CustomQR object and compare with the original object
	*/
	{
		CustomQR customQRRead; //Custom QR used for reading

		//Read the data
		if (!customQRRead.Read(memfile, errorlog))
		{
			std::cout << errorlog << std::endl;
			return 2;
		}

		//Private tags are marked as warnings in the errorlog
		std::cout << errorlog << std::endl;

		//Compare both objects
		if (customQR != customQRRead)
		{
			std::cout << "Data does not match!" << std::endl;
			return 3;
		}
	}

	/*
		The APIAllocators class provides a set of function pointers to allocate
		custom classes.
	*/

	SDICOS::Utils::APIAllocators apiAllocators; //Set of custom allocator function pointers

	//Assign the custom allocator for each custom class
	apiAllocators.m_pfnAllocateModuleQR = &CustomQRModule::AllocateCustom; //Module-Level API
	apiAllocators.m_pfnAllocateUserQR = &CustomQR::AllocateCustom;	//User-Level API

	/*
		DicosLoader and DicosServer can use the allocator object
		to ensure the correct class is allocated and passed to
		the callback functions.
	*/

	SDICOS::DicosLoader dcsLoader;
	dcsLoader.SetCustomAllocators(apiAllocators);

	SDICOS::Network::DcsServer dcsServer;
	dcsServer.SetCustomAllocators(apiAllocators);

	/*
		To use the default classes instead of the custom classes,
		set the function pointer for that function pointer to S_NULL.
	*/
	{
		apiAllocators.m_pfnAllocateUserQR = S_NULL; //Only restores the Module-Level API to default
	}

	//Update users of the allocator functions
	dcsLoader.SetCustomAllocators(apiAllocators);
	dcsServer.SetCustomAllocators(apiAllocators);

	/*
		To reset all the allocators to use the default classes,
		call SDICOS::Utils::APIAllocators::FreeMemory();
	*/
	{
		apiAllocators.FreeMemory();
	}

	//Update users of the allocator functions
	dcsLoader.SetCustomAllocators(apiAllocators);
	dcsServer.SetCustomAllocators(apiAllocators);

	return 0;
}

/////////////////////////////////////////////
//CustomQRModule

CustomQRModule::CustomQRModule()
{
	InitTags();
}

CustomQRModule::CustomQRModule(const CustomQRModule &qr)
	: SDICOS::QRModule(qr),
	m_attPrivateValue(qr.m_attPrivateValue),
	m_attPrivateText(qr.m_attPrivateText)
{}

CustomQRModule::~CustomQRModule()
{
	FreeMemory();
}

void CustomQRModule::InitTags()
{
	//Private data must be stored using odd valued Group numbers.
	//A tag is defined as (Group, Element).
	const SDICOS::S_UINT16 nPrivateGroup(0x1111);

	m_attPrivateText.SetTag(nPrivateGroup, 0x0000); //Tag for text
	m_attPrivateValue.SetTag(nPrivateGroup, 0x0001);//Tag for float value
}

void CustomQRModule::FreeMemory()
{
	SDICOS::QRModule::FreeMemory();

	//Deallocate data. Does not reset tag value.
	m_attPrivateValue.FreeMemory();
	m_attPrivateText.FreeMemory();

	std::cout << m_attPrivateText.GetTag().GetGroup() << ", " << m_attPrivateText.GetTag().GetElement() << std::endl;
}

CustomQRModule& CustomQRModule::operator=(const CustomQRModule &qr)
{
	SDICOS::QRModule::operator=(qr);

	m_attPrivateText = qr.m_attPrivateText;
	m_attPrivateValue = qr.m_attPrivateValue;

	return *this;
}

bool CustomQRModule::operator==(const CustomQRModule &qr)const
{
	return SDICOS::QRModule::operator==(qr) &&
		m_attPrivateText == qr.m_attPrivateText &&
		m_attPrivateValue == qr.m_attPrivateValue;
}

bool CustomQRModule::operator!=(const CustomQRModule &qr)const
{
	return !operator==(qr);
}

bool CustomQRModule::SetAttributes(const SDICOS::AttributeManager &attribManager, SDICOS::ErrorLog &errorlog)
{
	//Call base class function
	if (!SDICOS::QRModule::SetAttributes(attribManager, errorlog))
		return false;

	/*
		Retrieve the data from the AttributeManager
	*/
	{
		if (!attribManager.FindAttribute(m_attPrivateValue.GetTag(), m_attPrivateValue))
			std::cout << "Could not find Private Value" << std::endl;

		if (!attribManager.FindAttribute(m_attPrivateText.GetTag(), m_attPrivateText))
			std::cout << "Could not find Private Text" << std::endl;
	}

	return true;
}

bool CustomQRModule::GetAttributes(SDICOS::AttributeManager &attribManager, SDICOS::ErrorLog &errorlog)const
{
	//Call base class function
	if (!SDICOS::QRModule::GetAttributes(attribManager, errorlog))
		return false;

	/*
		Save the private data to the AttributeManager as references instead of copies.
	*/
	{
		CustomQRModule *pThis = const_cast<CustomQRModule*>(this);

		attribManager.SetReference(pThis->m_attPrivateText);
		attribManager.SetReference(pThis->m_attPrivateValue);
	}

	return true;
}

bool CustomQRModule::UpdateAttributes(const SDICOS::AttributeManager &attribManager, SDICOS::ErrorLog &errorlog)
{
	//Call base class function
	if (!SDICOS::QRModule::UpdateAttributes(attribManager, errorlog))
		return false;

	/*
		Update values if they are present within the AttributeManager
	*/
	{
		if (attribManager.HasAttribute(m_attPrivateValue.GetTag()))
			attribManager.FindAttribute(m_attPrivateValue.GetTag(), m_attPrivateValue);

		if (attribManager.HasAttribute(m_attPrivateText.GetTag()))
			attribManager.FindAttribute(m_attPrivateText.GetTag(), m_attPrivateText);
	}

	return true;
}

bool CustomQRModule::IsValid(const SDICOS::AttributeManager &attribManager, SDICOS::ErrorLog &errorlog)const
{
	//Call base class function
	if (!SDICOS::QRModule::IsValid(attribManager, errorlog))
		return false;

	/*
		Check if the private data is valid
	*/
	{
		if (!m_attPrivateText.IsValid())
			return false;

		if (!m_attPrivateValue.IsValid())
			return false;
	}

	return true;
}

//CustomQRModule
/////////////////////////////////////////////

/////////////////////////////////////////////
//CustomQR
CustomQR::CustomQR()
	: SDICOS::QR()
{
	DefaultInit();
}

CustomQR::CustomQR(const CustomQR &qr)
	: SDICOS::QR(qr),
	m_fPrivateValue(qr.m_fPrivateValue),
	m_strPrivateText(qr.m_strPrivateText)
{}

CustomQR::~CustomQR()
{
	FreeMemory();
}

void CustomQR::DefaultInit()
{
	m_strPrivateText.clear();
	m_fPrivateValue = 0.0f;

	//////////////////////////////////////
	//Initialize SDICOS::QR values that may be common to all instances of QR

	SDICOS::DcsDate dsDate(SDICOS::DcsDate::Today());	//Current Date
	SDICOS::DcsTime dsTime(SDICOS::DcsTime::Now());		//Current Time

	GenerateSopInstanceUID();	//Generate an SOP Instance UID
	GenerateSeriesInstanceUID();	//Generate a Series Instance UID
	GenerateScanInstanceUID();	//Generate a Scan Instance UID

	SetMeasurementsDateAndTime(dsDate, dsTime);	//Date and time measurement was taken
	SetScanStartDateAndTime(dsDate, dsTime);		//Date and time scan was created
	SetSeriesDateAndTime(dsDate, dsTime);		//Date and time series was created
	SetSopInstanceCreationDateAndTime(dsDate, dsTime);	//Date and time SOP instance was created

	SetDeviceCalibrationDateAndTime(dsDate, dsTime); //Date and time device was calibrated
	SetDeviceManufacturer("manufacturer");	//Device manufacturer
	SetDeviceManufacturerModelName("model");	//Device model name
	SetDeviceSerialNumber("serial number");	//Device serial number
	SetDeviceSoftwareVersion("version");	//Device software version

	SetInspectionBehavioral();	//Set inspection criteria to behavioral
}

CustomQR& CustomQR::operator=(const CustomQR &qr)
{
	SDICOS::QR::operator=(qr);

	m_strPrivateText = qr.m_strPrivateText;
	m_fPrivateValue = qr.m_fPrivateValue;
	return *this;
}

void CustomQR::FreeMemory()
{
	SDICOS::QR::FreeMemory();
	DefaultInit();
}

bool CustomQR::operator==(const CustomQR &qr)const
{
	return SDICOS::QR::operator==(qr) &&
		m_strPrivateText == qr.m_strPrivateText &&
		SDICOS::IsEqual(m_fPrivateValue, qr.m_fPrivateValue);
}

bool CustomQR::operator!=(const CustomQR &qr)const
{
	return !operator==(qr);
}

bool CustomQR::WriteDerived_internal(SDICOS::QRModule  &qr, SDICOS::ErrorLog &errorlog)const
{
	//Cast qr to CustomQRModule to access the private data
	CustomQRModule *pCustomQRModule = dynamic_cast<CustomQRModule*>(&qr);

	//Check if the cast passed
	if (!pCustomQRModule)
	{
		std::cout << "Failed to cast CustomQRModule" << std::endl;
		return false;
	}

	/*
		Save data to CustomQRModule
	*/
	{
		//Save float value
		pCustomQRModule->m_attPrivateValue.SetValue(m_fPrivateValue);

		//Save string as Long Text (VR = LT)
		pCustomQRModule->m_attPrivateText.SetValue(m_strPrivateText.c_str(), SDICOS::AttributeString::enumLongText);
	}

	return true;
}

bool CustomQR::ReadDerived_internal(const SDICOS::QRModule &qr, SDICOS::ErrorLog &errorlog)
{
	//Cast qr to CustomQRModule to access the private data
	const CustomQRModule *pCustomQRModule = dynamic_cast<const CustomQRModule*>(&qr);

	//Check if the cast passed
	if (!pCustomQRModule)
	{
		std::cout << "Failed to cast CustomQRModule" << std::endl;
		return false;
	}

	/*
		Get data from CustomQRModule
	*/
	{
		//Get the float value
		pCustomQRModule->m_attPrivateValue.GetValue(m_fPrivateValue);

		//Get the text value. Check if there is a value with SDICOS::AttributeString::GetVM().
		if (0 < pCustomQRModule->m_attPrivateText.GetVM())
		{
			//Get the value by reference using the a SDICOS::AttributeString::operator[], which
			//returns an SDICOS::DcsString reference. SDICOS::DcsString::Get() returns the char*
			//to the data.
			m_strPrivateText = pCustomQRModule->m_attPrivateText[0].Get();
		}
	}

	return true;
}

//CustomQR
/////////////////////////////////////////////

//Initializing function
void InitQR(SDICOS::QR &qr)
{
	qr.SetItineraryID("itinerary ID");							//Itinerary ID
	qr.SetItineraryIDAssigningAuthority("Itinerary assigner");	//Authority that assigned the itinerary ID
	qr.SetItineraryIDType(SDICOS::ItineraryModule::enumAgent);	//Itinerary ID Type set to agent

	qr.SetOOIID("OOI ID");							//Object of Inspection ID
	qr.SetOOIIDAssigningAuthority("OOID Assigner"); //Authority that assigned the OOI ID
	qr.SetOOIMassInGrams(100);						//OOI mass in grams
	qr.SetOOISizeInMeters(1000, 1000, 1000);		//OOI dimensions in meters
	qr.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);	//OOI type set to baggage
	qr.SetOOITypeDescriptor("description");			//OOI type description

	SDICOS::QR::QRMeasurement measurement;	//QR measurement data

	measurement.m_dsTargetMaterialInChICompound = "InChI=1S/C6H6/c1-2-4-6-5-3-1/h1-6H";	//InChI compound
	measurement.m_dsTargetMaterialInChIKey = "UHOVQNZJYSORNB-UHFFFAOYSA-N";				//InChI key
	measurement.m_fSignalToNoiseRatio = 33.0f;	//Signal-to-Noise (SNR) ratio
	measurement.m_fSNRThreshold = 12;			//SNR threshold

												//Bounding polygon in real world coordinates
												//Providing two points defines the opposite corners of the bounding box
	measurement.m_vBoundingPolygon.SetSize(2);
	measurement.m_vBoundingPolygon[0].Set(0, 0, 0);
	measurement.m_vBoundingPolygon[1].Set(10, 20, 30);

	qr.AddMeasurement(measurement);	//Add the measurement
}