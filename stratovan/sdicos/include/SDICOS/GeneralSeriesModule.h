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
#ifndef _STRATOVAN_DICOS_GENERAL_SERIES_MODULE_H_
#define _STRATOVAN_DICOS_GENERAL_SERIES_MODULE_H_

#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class GeneralSeriesModule
/// \brief Implements General Series Module
/// SPECREF V03 Section 6.1, Table 16
///
class GeneralSeriesModule
{
public:
	/// Constructor
	GeneralSeriesModule();
	/// Copy constructor
	GeneralSeriesModule(const GeneralSeriesModule &generalseriesmodule);
	/// Destructor
	virtual ~GeneralSeriesModule();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	GeneralSeriesModule& operator=(const GeneralSeriesModule &generalseriesmodule);
	/// Comparison operator
	bool operator==(const GeneralSeriesModule &generalseriesmodule)const;
	/// Comparison operator
	bool operator!=(const GeneralSeriesModule &generalseriesmodule)const;

	/// Modality enumerations
	typedef enum
	{
		enumUnknownModality, ///< Unknown enumeration
		
		enumCT,		///< "CT" 
		enumXRAY,	///< "XRAY" 
		enumTDR,	///< "TDR" 
		enumAIT,	///< "AIT" 
		enumAIT2D,	///< "AIT2D" 
		enumAIT3D,	///< "AIT3D" 
		enumQR,		///< "QR"
		enumHDAIT,	///< "HDAIT"
		enumWAIT,	///< "WAIT"
		enumETD,	///< "ETD" - Explosive Trace Detection
		enumDPC,	///< "DPC"
		enumXRD,	///< "XRD"

	}MODALITY;

	/// Acquisition Status enumerations
	typedef enum
	{
		enumUnknownAcquisitionStatus, ///< Unknown enumeration

		enumSuccessful,		///< "SUCCESSFUL" 
		enumJam,			///< "JAM"
		enumOversize,		///< "OVERSIZE"
		enumSlip,			///< "SLIP"
		enumIncomplete,		///< "INCOMPLETE"
		enumCut,			///< "CUT"
		enumMerged,			///< "MERGED"
		enumStitched,		///< "STITCHED"

	}ACQUISITION_STATUS;

	/// Test Article enumerations
	/// (Name changed from "Phantom Type" in V02A to "Test Article Type" in V03)
	typedef enum
	{
		enumUnknownTestArticleType,

		enumNIST_FAT,		///< "NIST_FAT"
		enumNIST_SAT,		///< "NIST_SAT"
		enumOTK,			///< "OTK"
		enumCTIQ,			///< "CTIQ"
		enumCalibration,	///< "CALIBRATION"
		enumGIQ,			///< "GIQ"

	}TEST_ARTICLE_TYPE;

	///
	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// Set Series Instance UID : Tag (0020, 000E), VR = UI [required]
	bool SetInstanceUID(const DcsUniqueIdentifier &strSeriesInstanceUID);
	/// @see SetInstanceUID
	DcsString GetInstanceUID()const;

	/// Series Date and Time
	/// @param strDate Date : Tag (0008, 0021), VR = DA [required]
	/// @param strTime Time : Tag (0008, 0031), VR = TM [required]
	bool SetDateAndTime(const DcsDate &strDate, const DcsTime &strTime);
	/// @see SetDateAndTime
	DcsDate GetDate()const;
	/// @see SetDateAndTime
	DcsTime GetTime()const;

	/// Set Modality : Tag (0008, 0060), VR = CS [required]
	virtual bool SetModality(const MODALITY nModality);
	/// @see SetModality
	MODALITY GetModality()const;
	/// @see SetModality
	DcsString GetModalityAsString()const;

	/// Set Acquisition Status : Tag (4010, 1044), VR = CS [required]
	bool SetAcquisitionStatus(const ACQUISITION_STATUS nAcquisitionStatus);
	/// @see SetAcquisitionStatus
	ACQUISITION_STATUS GetAcquisitionStatus()const;
	/// @see SetAcquisitionStatus
	DcsString GetAcquisitionStatusAsString()const;

	/// Set Description : Tag (0008, 103E), VR = LO [optional]
	bool SetDescription(const DcsLongString &strSeriesDescription);
	/// @see SetDescription
	DcsString GetDescription()const;
	/// Returns true if value is set
	bool HasDescription()const;
	/// Delete Description
	void DeleteDescription();

	/// Set Test Article : Tag (4010, 1046), VR = CS [optional]
	/// (Name changed from "Phantom Type" in V02A to "Test Article" in V03)
	bool SetTestArticleType(const TEST_ARTICLE_TYPE nPhantomType);
	/// @see SetTestArticleType
	TEST_ARTICLE_TYPE GetTestArticleType()const;
	/// @see SetTestArticleType
	DcsString GetTestArticleTypeAsString()const;
	/// Returns true if value is set
	bool HasTestArticleType()const;
	/// Delete Phantom Type
	void DeleteTestArticleType();

	/// A number that identifies this series and is unique within a scan : Tag (0020, 0011), VR = IS [optional]
	/// @see HasSeriesNumber
	/// @see DeleteSeriesNumber
	bool SetSeriesNumber(const DcsInteger &str);
	/// @see SetSeriesNumber
	/// @see HasSeriesNumber
	/// @see DeleteSeriesNumber
	DcsInteger GetSeriesNumber()const;
	/// Returns true if value is set
	bool HasSeriesNumber()const;
	/// Delete data
	void DeleteSeriesNumber();

	/// View identifier for this series when using multi-view image data : Tag (6100, 0024), VR = US [optional]
	bool SetSeriesView(const S_UINT16 &nView);
	/// @see SetSeriesView
	S_UINT16 GetSeriesView()const;
	/// Returns true if value is set
	bool HasSeriesView()const;
	/// Delete data
	void DeleteSeriesView();

	/// Series View Description : Tag (6100, 0026), VR = LO [optional]
	bool SetSeriesViewDescription(const DcsLongString &strDescription);
	/// @see SetSeriesViewDescription
	DcsString GetSeriesViewDescription()const;
	/// Returns true of value is set
	bool HasSeriesViewDescription()const;
	/// Delete data
	void DeleteSeriesViewDescription();

	/// Energy identifier for this series when using multi-energy image data : Tag (6100, 0030), VR = US [optional]
	bool SetSeriesEnergy(const S_UINT16 &nEnergy);
	/// @see SetSeriesEnergy
	S_UINT16 GetSeriesEnergy()const;
	/// Returns true if value is set
	bool HasSeriesEnergy()const;
	/// Delete data
	void DeleteSeriesEnergy();

	/// Series Energy Description : Tag (6100, 0031), VR = LO [optional]
	bool SetSeriesEnergyDescription(const DcsLongString &strDescription);
	/// @see SetSeriesEnergyDescription
	DcsString GetSeriesEnergyDescription()const;
	/// Returns true of value is set
	bool HasSeriesEnergyDescription()const;
	/// Delete data
	void DeleteSeriesEnergyDescription();

protected:
	class ImplGeneralSeries;
	ImplGeneralSeries	*m_pImplGeneralSeries; ///< Internal implementation
};

}//namespace SDICOS

#endif
