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
#ifndef _STRATOVAN_DICOS_DX_DETECTOR_H_
#define _STRATOVAN_DICOS_DX_DETECTOR_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{
namespace DXTypes
{

///
/// \class DXDetector
/// \brief Implements DX/X-Ray Detector Module
/// SPECREF V03 Section 8.2.2.3, Table 36
///
class DXDetector
{
public:
	/// Constructor
	DXDetector();
	/// Copy constructor
	DXDetector(const DXDetector &dxd);
	/// Destructor
	virtual ~DXDetector();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	DXDetector& operator=(const DXDetector &dxd);
	/// Comparison operator
	bool operator==(const DXDetector &dxd)const;
	/// Comparison operator
	bool operator!=(const DXDetector &dxd)const;

	/// Detector type enumerations
	typedef enum
	{
		enumUnknownDetectorType, ///< Does not match defined terms

		enumDirect,			///< "DIRECT" - X-Ray Photoconductor
		enumScintillator,	///< "SCINTILLATOR" - Phosphor Used
		enumOther,			///< "OTHER"

	}DETECTOR_TYPE;

	/// Detector configuration enumerations
	typedef enum
	{
		enumUnknownDetectorConfiguration, ///< Does not match defined terms

		enumUnknown,		///< "UNKNOWN"
		enumSandwich,		///< "SANDWICH"
		enumSideBySide,		///< "SIDE BY SIDE"
		enumCheckerboard,	///< "CHECKERBOARD"
		enumMonoEnergetic,	///< "MONOENERGETIC"

	}DETECTOR_CONFIGURATION;

	/// Energy detector type enumerations
	typedef enum
	{
		enumUnknownEnergyDetectorType, ///< Does not match defined terms

		enumIntegrating,	///< "INTEGRATING"
		enumPhotonCounting,	///< "PHOTON_COUNTING"

	}ENERGY_DETECTOR_TYPE;

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

	/// Detector Type : Tag (0018, 7004), VR = CS [required (type 2), can be NULL]
	bool SetDetectorType(const DETECTOR_TYPE nType);
	/// @see SetDetectorType
	DETECTOR_TYPE GetDetectorType()const;
	/// @see SetDetectorType
	DcsString GetDetectorTypeAsString()const;
	///@return true/false If Detector Type is not NULL
	bool HasDetectorType()const;
	/// Delete Detector Type
	void DeleteDetectorType();

	/// Detector Configuration : Tag (0018, 7005), VR = CS [optional]
	bool SetDetectorConfiguration(const DETECTOR_CONFIGURATION nConfig);
	/// @see SetDetectorConfiguration
	DETECTOR_CONFIGURATION GetDetectorConfiguration()const;
	/// @see SetDetectorConfiguration
	DcsString GetDetectorConfigurationAsString()const;
	///@return true/false If Detector Configuration is present
	bool HasDetectorConfiguration()const;
	/// Delete Detector Configuration
	void DeleteDetectorConfiguration();

	/// Detector Description : Tag (0018, 7006), VR = LT [optional]
	bool SetDetectorDescription(const DcsLongText &strDescription);
	/// @see SetDetectorDescription
	DcsString GetDetectorDescription()const;
	/// Delete Detector Description
	void DeleteDetectorDescription();

	/// Detector Mode : Tag (0018, 7008), VR = LT [optional]
	bool SetDetectorMode(const DcsLongText &strMode);
	/// @see SetDetectorMode
	DcsString GetDetectorMode()const;
	/// Delete Detector Mode
	void DeleteDetectorMode();

	/// Detector ID : Tag (0018, 700A), VR = SH [optional]
	bool SetDetectorID(const DcsShortString &strID);
	/// @see SetDetectorID
	DcsString GetDetectorID()const;
	/// Delete Detector ID
	void DeleteDetectorID();

	/// Date of Last Detector Calibration : Tag (0018, 700C), VR = DA [optional]
	bool SetDateOfLastDetectorCalibration(const DcsDate &strDate);
	/// @see SetDateOfLastDetectorCalibration
	DcsDate GetDateOfLastDetectorCalibration()const;
	/// Delete Date of Last Detector Calibration
	void DeleteDateOfLastDetectorCalibration();

	/// Time of Last Detector Calibration : Tag (0018, 700E), VR = TM [optional]
	bool SetTimeOfLastDetectorCalibration(const DcsTime &strTime);
	/// @see GetTimeOfLastDetectorCalibration
	DcsTime GetTimeOfLastDetectorCalibration()const;
	/// Delete Time of Last Detector Calibration
	void DeleteTimeOfLastDetectorCalibration();

	/// Detector Calibration Data : Tag (4010, 106C), VR = OB [optional]
	bool SetDetectorCalibrationData(const Array1D<S_UINT8> &arrayData);
	/// @see SetDetectorCalibrationData
	bool GetDetectorCalibrationData(Array1D<S_UINT8> &arrayData)const;
	/// @see SetDetectorCalibrationData
	Array1D<S_UINT8>& GetDetectorCalibrationData();
	/// @see SetDetectorCalibrationData
	const Array1D<S_UINT8>& GetDetectorCalibrationData()const;
	/// Delete Detector Calibration Data
	void DeleteDetectorCalibrationData();

	/// Exposures on Detector Since Last Calibration : Tag (0018, 7010), VR = IS [optional]
	bool SetExposuresOnDetectorSinceLastCalibration(const S_INT32 nNumExposures);
	/// @see SetExposuresOnDetectorSinceLastCalibration
	S_INT32 GetExposuresOnDetectorSinceLastCalibration()const;
	/// @see SetExposuresOnDetectorSinceLastCalibration
	DcsString GetExposuresOnDetectorSinceLastCalibrationAsString()const;
	/// Delete Exposures on Detector Since Last Calibration
	void DeleteExposuresOnDetectorSinceLastCalibration();

	/// Exposures on Detector Since Manufactured : Tag (0018, 7011), VR = IS [optional]
	bool SetExposuresOnDetectorSinceManufactured(const S_INT32 nNumExposures);
	/// @see SetExposuresOnDetectorSinceManufactured
	S_INT32 GetExposuresOnDetectorSinceManufactured()const;
	/// @see SetExposuresOnDetectorSinceManufactured
	DcsString GetExposuresOnDetectorSinceManufacturedAsString()const;
	/// Delete Exposures on Detector Since Manufactured
	void DeleteExposuresOnDetectorSinceManufactured();

	/// Detector Time Since Last Exposure in seconds : Tag (0018, 7012), VR = DS [optional]
	bool SetDetectorTimeSinceLastExposure(const float fTime);
	/// @see SetDetectorTimeSinceLastExposure
	float GetDetectorTimeSinceLastExposure()const;
	/// @see SetDetectorTimeSinceLastExposure
	DcsString GetDetectorTimeSinceLastExposureAsString()const;
	/// Delete Detector Time Since Last Exposure
	void DeleteDetectorTimeSinceLastExposure();

	/// Detector Binning. Number of detectors used to generate a single pixel. : Tag (0018, 701A), VR = DS [optional]
	bool SetDetectorBinning(const float fNumberOfRowDetectors, const float fNumberOfColumnDetectors);
	/// @see SetDetectorBinning
	bool GetDetectorBinning(float &fNumberOfRowDetectors, float &fNumberOfColumnDetectors)const;
	/// @see SetDetectorBinning
	bool GetDetectorBinning(DcsString &strNumberOfRowDetectors, DcsString &strNumberOfColumnDetectors)const;
	/// Delete Detector Binning
	void DeleteDetectorBinning();

	/// Detector Manufacturer Name : Tag (0018, 702A), VR = LO [optional]
	bool SetDetectorManufacturerName(const DcsLongString &strName);
	/// @see SetDetectorManufacturerName
	DcsString GetDetectorManufacturerName()const;
	/// Delete Detector Manufacturer Name
	void DeleteDetectorManufacturerName();

	/// Detector Manufacturer's Model Name : Tag (0018, 702B), VR = LO [optional]
	bool SetDetectorManufacturerModelName(const DcsLongString &strName);
	/// @see SetDetectorManufacturerModelName
	DcsString GetDetectorManufacturerModelName()const;
	/// Delete Detector Manufacturer's Model Name
	void DeleteDetectorManufacturerModelName();

	/// Detector Conditions Nominal Flag : Tag (0018, 7000), VR = CS [optional]
	/// @param bUsingNominalFlag true = "YES", false = "NO". true: Machine operating within nominal tolerances.
	bool SetDetectorConditionsNominalFlag(const bool bUsingNominalFlag);
	/// Returns true if Detector Conditions Nominal Flag is "YES"
	bool GetDetectorConditionsNominalFlag()const;
	/// @see SetDetectorConditionsNominalFlag
	DcsString GetDetectorConditionsNominalFlagAsString()const;
	/// Delete Detector Conditions Nominal Flag
	void DeleteDetectorConditionsNominalFlag();

	/// Detector Temperature in Celsius : Tag (0018, 7001), VR = DS [optional]
	bool SetDetectorTemperatureCelsius(const float fTemperature);
	/// @see SetDetectorTemperatureCelsius
	float GetDetectorTemperature()const;
	/// @see SetDetectorTemperatureCelsius
	DcsString GetDetectorTemperatureAsString()const;
	/// Delete Detector Temperature
	void DeleteDetectorTemperature();

	/// Detector Sensitivity : Tag (0018, 6000), VR = DS [optional]
	bool SetDetectorSensitivity(const float fSensitivity);
	/// @see SetDetectorSensitivity
	float GetDetectorSensitivity()const;
	/// @see SetDetectorSensitivity
	DcsString GetDetectorSensitivityAsString()const;
	/// Delete Detector Sensitivity
	void DeleteDetectorSensitivity();

	/// Detector Element Physical Size in mm : Tag (0018, 7020), VR = DS [optional]
	bool SetDetectorElementPhysicalSizeMM(const float fRowSize, const float fColumnSize);
	/// @see SetDetectorElementPhysicalSizeMM
	bool GetDetectorElementPhysicalSize(float &fRowSize, float &fColumnSize)const;
	/// @see SetDetectorElementPhysicalSizeMM
	bool GetDetectorElementPhysicalSize(DcsString &strRowSize, DcsString &strColumnSize)const;
	/// Delete Detector Element Physical Size
	void DeleteDetectorElementPhysicalSize();

	/// Detector Element Spacing in mm : Tag (0018, 7022), VR = DS [optional]
	bool SetDetectorElementSpacingMM(const float fRowSpacing, const float fColumnSpacing);
	/// @see SetDetectorElementSpacingMM
	bool GetDetectorElementSpacing(float &fRowSpacing, float &fColumnSpacing)const;
	/// @see SetDetectorElementSpacingMM
	bool GetDetectorElementSpacing(DcsString &strRowSpacing, DcsString &strColumnSpacing)const;
	/// Delete Detector Element Spacing
	void DeleteDetectorElementSpacing();

	/// Low Energy Detectors : Tag (4010, 0001), VR = CS [optional]
	bool SetLowEnergyDetector(const ENERGY_DETECTOR_TYPE nType);
	/// @see SetLowEnergyDetectors
	ENERGY_DETECTOR_TYPE GetLowEnergyDetector()const;
	/// @see SetLowEnergyDetectors
	DcsString GetLowEnergyDetectorAsString()const;
	/// Delete Low Energy Detectors
	void DeleteLowEnergyDetector();

	/// High Energy Detectors : Tag (4010, 0002), VR = CS [optional]
	bool SetHighEnergyDetector(const ENERGY_DETECTOR_TYPE nType);
	/// @see SetHighEnergyDetectors
	ENERGY_DETECTOR_TYPE GetHighEnergyDetector()const;
	/// @see SetHighEnergyDetectors
	DcsString GetHighEnergyDetectorAsString()const;
	/// Delete High Energy Detectors
	void DeleteHighEnergyDetector();

	/// The bin number within the energy histogram used to reconstruct the image
	/// Tag (4010, 0003), VR = SL [optional]
	bool SetBinNumber(const S_INT32 nNum);
	/// @see SetBinNumber
	S_INT32 GetBinNumber()const;
	/// @see SetBinNumber
	bool HasBinNumber()const;
	/// Delete data
	void DeleteBinNumber();

	/// The higher energy of the energy histogram bins used to reconstruct the high energy image
	/// Tag (4010, 0007), VR = SL [optional]
	bool SetHigherEnergy(const S_INT32 nVal);
	/// @see SetHigherEnergy
	S_INT32 GetHigherEnergy()const;
	/// @see SetHigherEnergy
	bool HasHigherEnergy()const;
	/// Delete data
	void DeleteHigherEnergy();

	/// The lower energy of the energy histogram bins used to reconstruct the low energy image
	/// Tag (4010, 0005), VR = SL [optional]
	bool SetLowerEnergy(const S_INT32 nVal);
	/// @see SetLowerEnergy
	S_INT32 GetLowerEnergy()const;
	/// @see SetLowerEnergy
	bool HasLowerEnergy()const;
	/// Delete data
	void DeleteLowerEnergy();

	/// The energy bin width used to place to produce the energy histogram
	/// Tag (4010, 0006), VR = SL [optional]
	bool SetEnergyResolution(const S_INT32 nVal);
	/// @see SetEnergyResolution
	S_INT32 GetEnergyResolution()const;
	/// @see SetEnergyResolution
	bool HasEnergyResolution()const;
	/// Delete data
	void DeleteEnergyResolution();

protected:
	class ImplDXDetector;
	ImplDXDetector	*m_pImplDXDetector; ///< Internal implementation
};

}//namespace DXTypes
}//namespace SDICOS

#endif
