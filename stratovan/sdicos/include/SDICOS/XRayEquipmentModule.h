//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2022 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_XRAY_EQUIPMENT_H_
#define _STRATOVAN_DICOS_XRAY_EQUIPMENT_H_

#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"

namespace SDICOS
{
///
/// \class XRayEquipmentModule
/// \brief Implements X-Ray Equipment Module
/// SPECREF V03 Section 14.19, Table 125
///
class XRayEquipmentModule
{
public:
	/// Constructor
	XRayEquipmentModule();
	/// Copy constructor
	XRayEquipmentModule(const XRayEquipmentModule &xrayequipmentmodule);
	/// Destructor
	virtual ~XRayEquipmentModule();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	XRayEquipmentModule& operator=(const XRayEquipmentModule &xrayequipmentmodule);
	/// Comparison operator
	bool operator==(const XRayEquipmentModule &xrayequipmentmodule)const;
	/// Comparison operator
	bool operator!=(const XRayEquipmentModule &xrayequipmentmodule)const;

	/// Type of G0 enumerations
	typedef enum
	{
		enumUnknownG0, ///< Unknown enumeration

		// X-RAY ANODE is an invalid Code String and is currently unsupported
		// enumXrayAnodeG0, ///< "X-RAY ANODE"

		enumMaskG0, ///< "MASK"
		enumGratingG0, ///< "GRATING"

	}TYPE_G0;

	/// Type of G1 enumerations
	typedef enum
	{
		enumUnknownG1, ///< Unknown enumeration

		enumGratingG1, ///< "GRATING"
		enumOtherG1 ///< "OTHER"

	}TYPE_G1;

	/// Type of G2 enumerations
	typedef enum
	{
		enumUnknownG2, ///< Unknown enumeration

		enumGratingG2, ///< "GRATING"
		enumOtherG2 ///< "OTHER"

	}TYPE_G2;

	/// Reconstruction Algorithm for Phase and Dark Image enumerations
	typedef enum
	{
		enumUnknownImage, ///< Unknown enumeration

		enumFFT, ///< "FFT"
		enumModifiedFFT, ///< "MODIFIED FFT"
		enumOtherImage, ///< "OTHER"

	}RECON_IMAGE;

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

	/// Mask Characteristics : Tag (4300, 0906), VR = ST [optional]
	/// Describe how the CAI mask was designed. For example: random binary matrix, 
	/// sinusoid in x (horizontal), and a quadratic in y (vertical), or Hadamard matrix
	bool SetMaskCharacteristics(const DcsShortText &nMaskCharacteristics);
	/// @see SetMaskCharacteristics
	DcsShortText GetMaskCharacteristics()const;
	/// Returns true if value is set
	bool HasMaskCharacteristics()const;
	/// Delete data
	void DeleteMaskCharacteristics();

	/// Set Type of G0 : Tag (4300, 0904), VR = CS [optional]
	bool SetTypeG0(const TYPE_G0 nTypeG0);
	/// @see SetTypeG0
	TYPE_G0 GetTypeG0()const;
	/// @see SetTypeG0
	DcsString GetTypeG0AsString()const;
	/// Returns true if value is set
	bool HasTypeG0()const;
	/// Delete data
	void DeleteTypeG0();

	/// Set Type of G1 : Tag (4300, 0910), VR = CS [optional]
	bool SetTypeG1(const TYPE_G1 nTypeG1);
	/// @see SetTypeG1
	TYPE_G1 GetTypeG1()const;
	/// @see SetTypeG1
	DcsString GetTypeG1AsString()const;
	/// Returns true if value is set
	bool HasTypeG1()const;
	/// Delete data
	void DeleteTypeG1();

	/// Set Type of G2 : Tag (4300, 0914), VR = CS [optional]
	bool SetTypeG2(const TYPE_G2 nTypeG2);
	/// @see SetTypeG2
	TYPE_G2 GetTypeG2()const;
	/// @see SetTypeG2
	DcsString GetTypeG2AsString()const;
	/// Returns true if value is set
	bool HasTypeG2()const;
	/// Delete data
	void DeleteTypeG2();

	/// Reconstruction Algorithm for Phase Image : Tag (4300, 0938), VR = CS [optional]
	/// Set the type of algorithm used for reconstruction of the phase image
	bool SetReconAlgorithmPhaseImage(const RECON_IMAGE nPhaseImage);
	/// @see SetReconAlgorithmPhaseImage
	RECON_IMAGE GetReconAlgorithmPhaseImage()const;
	/// @see SetReconAlgorithmPhaseImage
	DcsString GetReconAlgorithmPhaseImageAsString()const;
	/// Returns true if value is set
	bool HasReconAlgorithmPhaseImage()const;
	/// Delete data
	void DeleteReconAlgorithmPhaseImage();

	/// Reconstruction Algorithm for Dark Image : Tag (4300, 0940), VR = CS [optional]
	/// Set the type of algorithm used for reconstruction of the dark image
	bool SetReconAlgorithmDarkImage(const RECON_IMAGE nDarkImage);
	/// @see SetReconAlgorithmDarkImage
	RECON_IMAGE GetReconAlgorithmDarkImage()const;
	/// @see SetReconAlgorithmDarkImage
	DcsString GetReconAlgorithmDarkImageAsString()const;
	/// Returns true if value is set
	bool HasReconAlgorithmDarkImage()const;
	/// Delete data
	void DeleteReconAlgorithmDarkImage();

	/// Effective Energy : Tag (4300, 0902), VR = FL [required]
	/// Set the energy for which the gratings were designed for
	bool SetEffectiveEnergy(const float nEffectiveEnergy);
	/// @see SetEffectiveEnergy
	float GetEffectiveEnergy()const;

	/// Set Distance in centimeters from G0 to X-Ray Source : Tag (4300, 0908), VR = FL [optional]
	bool SetDistanceFromG0ToSourceInCentimeters(const float nDistanceG0XR);
	/// @see SetDistanceFromG0ToSourceInCentimeters
	float GetDistanceFromG0ToSourceInCentimeters()const;
	/// Returns true if value is set
	bool HasDistanceFromG0ToSource()const;
	/// Delete data
	void DeleteDistanceFromG0ToSource();

	/// Set Distance in centimeters from G1 to X-Ray Source : Tag (4300, 0912), VR = FL [optional]
	bool SetDistanceFromG1ToSourceInCentimeters(const float nDistanceG1XR);
	/// @see SetDistanceFromG1ToSourceInCentimeters
	float GetDistanceFromG1ToSourceInCentimeters()const;
	/// Returns true if value is set
	bool HasDistanceFromG1ToSource()const;
	/// Delete data
	void DeleteDistanceFromG1ToSource();

	/// Distance in centimeters from G2 to X-Ray Source is disabled due to invalid VR
	/*
	/// Set Distance in centimeters from G2 to X-Ray Source : Tag (4300, 0916), VR = CS [optional]
	bool SetDistanceFromG2ToSourceInCentimeters(const float nDistanceG2XR);
	/// @see SetDistanceFromG2ToSourceInCentimeters
	float GetDistanceG2ToSourceInCentimeters()const;
	/// Returns true if value is set
	bool HasDistanceFromG2ToSource()const;
	/// Delete data
	void DeleteDistanceFromG2ToSource();
	*/

	/// G0 Absorption Period : Tag (4300, 0918), VR = FL [optional]
	/// Set the pitch or period of the G0 grating
	bool SetG0AbsorptionPeriod(const float nG0Absorption);
	/// @see SetG0AbsorptionPeriod
	float GetG0AbsorptionPeriod()const;
	/// Returns true if value is set
	bool HasG0AbsorptionPeriod()const;
	/// Delete data
	void DeleteG0AbsorptionPeriod();

	/// G1 Phase Period : Tag (4300, 0920), VR = FL [optional]
	/// Set the period of the G1 grating
	bool SetG1PhasePeriod(const float nG1Phase);
	/// @see SetG1PhasePeriod
	float GetG1PhasePeriod()const;
	/// Returns true if value is set
	bool HasG1PhasePeriod()const;
	/// Delete data
	void DeleteG1PhasePeriod();

	/// G2 Analyzer Period : Tag (4300, 0922), VR = FL [optional]
	/// Set the period of the G2 grating
	bool SetG2AnalyzerPeriod(const float nG2Analyzer);
	/// @see SetG2AnalyzerPeriod
	float GetG2AnalyzerPeriod()const;
	/// Returns true if value is set
	bool HasG2AnalyzerPeriod()const;
	/// Delete data
	void DeleteG2AnalyzerPeriod();

	/// Visibility : Tag (4300, 0924), VR = FL [optional]
	/// Set the resulting visibility of the phase and dark image
	bool SetVisibility(const float nVisibility);
	/// @see SetVisibility
	float GetVisibility()const;
	/// Returns true if value is set
	bool HasVisibility()const;
	/// Delete data
	void DeleteVisibility();

	/// Absorption X-Ray Detector Size : Tag (4300, 0926), VR = FL [optional]
	/// Set the resulting size of the X-Ray detectors which are combined to provide the absorption pixel size
	bool SetAbsorptionXRDetectorSize(const float nSizeX, const float nSizeY);
	/// @see SetAbsorptionXRDetectorSize
	float GetAbsorptionXRDetectorSizeX()const;
	/// @see SetAbsorptionXRDetectorSize
	float GetAbsorptionXRDetectorSizeY()const;
	/// Returns true if value is set
	bool HasAbsorptionXRDetectorSize()const;
	/// Delete data
	void DeleteAbsorptionXRDetectorSize();

	/// Absorption Reconstruction Voxel Size : Tag (4300, 0928), VR = FL [optional]
	/// Set the resulting size of the X-Ray detectors which are combined to provide the absorption voxel size
	bool SetAbsorptionReconstructionVoxelSize(const float nSizeX, const float nSizeY);
	/// @see SetAbsorptionReconstructionVoxelSize
	float GetAbsorptionReconstructionVoxelSizeX()const;
	/// @see SetAbsorptionReconstructionVoxelSize
	float GetAbsorptionReconstructionVoxelSizeY()const;
	/// Returns true if value is set
	bool HasAbsorptionReconstructionVoxelSize()const;
	/// Delete data
	void DeleteAbsorptionReconstructionVoxelSize();

	/// Phase X-Ray Detector Size : Tag (4300, 0930), VR = FL [optional]
	/// Set the resulting size of the X-Ray detectors which are combined to provide the phase pixel size
	bool SetPhaseXRDetectorSize(const float nSizeX, const float nSizeY);
	/// @see SetPhaseXRDetectorSize
	float GetPhaseXRDetectorSizeX()const;
	/// @see SetPhaseXRDetectorSize
	float GetPhaseXRDetectorSizeY()const;
	/// Returns true if value is set
	bool HasPhaseXRDetectorSize()const;
	/// Delete data
	void DeletePhaseXRDetectorSize();

	/// Phase Reconstruction Voxel Size : Tag (4300, 0932), VR = FL [optional]
	/// Set the resulting size of the X-Ray detectors which are combined to provide the phase voxel size
	bool SetPhaseReconstructionVoxelSize(const float nSizeX, const float nSizeY, const float nSizeZ);
	/// @see SetPhaseReconstructionVoxelSize
	float GetPhaseReconstructionVoxelSizeX()const;
	/// @see SetPhaseReconstructionVoxelSize
	float GetPhaseReconstructionVoxelSizeY()const;
	/// @see SetPhaseReconstructionVoxelSize
	float GetPhaseReconstructionVoxelSizeZ()const;
	/// Returns true if value is set
	bool HasPhaseReconstructionVoxelSize()const;
	/// Delete data
	void DeletePhaseReconstructionVoxelSize();

	/// Dark Image X-Ray Detector Size : Tag (4300, 0934), VR = FL [optional]
	/// Set the resulting size of the X-Ray detectors which are combined to provide the dark image pixel size
	bool SetDarkXRDetectorSize(const float nSizeX, const float nSizeY);
	/// @see SetDarkXRDetectorSize
	float GetDarkXRDetectorSizeX()const;
	/// @see SetDarkXRDetectorSize
	float GetDarkXRDetectorSizeY()const;
	/// Returns true if value is set
	bool HasDarkXRDetectorSize()const;
	/// Delete data
	void DeleteDarkXRDetectorSize();

	/// Dark Image Reconstruction Voxel Size : Tag (4300, 0936), VR = FL [optional]
	/// Set the resulting size of the X-Ray detectors which are combined to provide the dark image voxel size
	bool SetDarkReconstructionVoxelSize(const float nSizeX, const float nSizeY, const float nSizeZ);
	/// @see SetDarkReconstructionVoxelSize
	float GetDarkReconstructionVoxelSizeX()const;
	/// @see SetDarkReconstructionVoxelSize
	float GetDarkReconstructionVoxelSizeY()const;
	/// @see SetDarkReconstructionVoxelSize
	float GetDarkReconstructionVoxelSizeZ()const;
	/// Returns true if value is set
	bool HasDarkReconstructionVoxelSize()const;
	/// Delete data
	void DeleteDarkReconstructionVoxelSize();

protected:
	class ImplXR;
	ImplXR	*m_pImplXR; ///< Internal implementation
};

}//namespace SDICOS

#endif
