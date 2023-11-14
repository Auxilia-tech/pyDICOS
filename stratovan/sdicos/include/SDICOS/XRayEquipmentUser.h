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

#ifndef _STRATOVAN_DICOS_USER_XRAY_EQUIPMENT_H_
#define _STRATOVAN_DICOS_USER_XRAY_EQUIPMENT_H_

#include "SDICOS/String.h"
#include "SDICOS/Attribute.h"
#include "SDICOS/XRayEquipmentModule.h"

namespace SDICOS
{
///
/// \class XRayEquipmentUser
///
class XRayEquipmentUser
{
public:
	/// Constructor
	XRayEquipmentUser();
	/// Copy constructor
	XRayEquipmentUser(const XRayEquipmentUser &xc);
	/// Destructor
	virtual ~XRayEquipmentUser();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy constructor
	XRayEquipmentUser& operator=(const XRayEquipmentUser &xc);
	/// Comparison operator
	bool operator==(const XRayEquipmentUser &xc)const;
	/// Comparison operator
	bool operator!=(const XRayEquipmentUser &xc)const;

	/// Read values from parameters
	virtual bool Read(const XRayEquipmentModule &xrm, ErrorLog& errorlog);
	/// Write values to parameters
	virtual bool Write(XRayEquipmentModule &xrm, ErrorLog& errorlog)const;

	/// Mask Characteristics that describe how the CAI mask was designed
	bool SetMaskCharacteristics(const DcsShortText &nMaskCharacteristics);
	/// @see SetMaskCharacteristics
	DcsShortText GetMaskCharacteristics()const;
	/// Returns true if value is set
	bool HasMaskCharacteristics()const;
	/// Delete data
	void DeleteMaskCharacteristics();

	/// Type of G0, defined terms are GRATING, OTHER
	bool SetTypeG0(const XRayEquipmentModule::TYPE_G0 nTypeG0);
	/// @see SetTypeG0
	XRayEquipmentModule::TYPE_G0 GetTypeG0()const;
	/// @see SetTypeG0
	DcsString GetTypeG0AsString()const;
	/// Returns true if value is set
	bool HasTypeG0()const;
	/// Delete data
	void DeleteTypeG0();

	/// Type of G1, defined terms are GRATING, OTHER
	bool SetTypeG1(const XRayEquipmentModule::TYPE_G1 nTypeG1);
	/// @see SetTypeG1
	XRayEquipmentModule::TYPE_G1 GetTypeG1()const;
	/// @see SetTypeG1
	DcsString GetTypeG1AsString()const;
	/// Returns true if value is set
	bool HasTypeG1()const;
	/// Delete data
	void DeleteTypeG1();

	/// Type of G2, defined terms are GRATING, OTHER
	bool SetTypeG2(const XRayEquipmentModule::TYPE_G2 nTypeG2);
	/// @see SetTypeG2
	XRayEquipmentModule::TYPE_G2 GetTypeG2()const;
	/// @see SetTypeG2
	DcsString GetTypeG2AsString()const;
	/// Returns true if value is set
	bool HasTypeG2()const;
	/// Delete data
	void DeleteTypeG2();

	/// The type of algorithm used for reconstruction of the phase image. Enumerated values are FFT, MODIFIED FFT, OTHER
	bool SetReconAlgorithmPhaseImage(const XRayEquipmentModule::RECON_IMAGE nPhaseImage);
	/// @see SetReconAlgorithmPhaseImage
	XRayEquipmentModule::RECON_IMAGE GetReconAlgorithmPhaseImage()const;
	/// @see SetReconAlgorithmPhaseImage
	DcsString GetReconAlgorithmPhaseImageAsString()const;
	/// Returns true if value is set
	bool HasReconAlgorithmPhaseImage()const;
	/// Delete data
	void DeleteReconAlgorithmPhaseImage();

	/// The type of algorithm used for reconstruction of the dark image. Enumerated values are FFT, MODIFIED FFT, OTHER
	bool SetReconAlgorithmDarkImage(const XRayEquipmentModule::RECON_IMAGE nDarkImage);
	/// @see SetReconAlgorithmDarkImage
	XRayEquipmentModule::RECON_IMAGE GetReconAlgorithmDarkImage()const;
	/// @see SetReconAlgorithmDarkImage
	DcsString GetReconAlgorithmDarkImageAsString()const;
	/// Returns true if value is set
	bool HasReconAlgorithmDarkImage()const;
	/// Delete data
	void DeleteReconAlgorithmDarkImage();

	/// This is the energy for which the gratings were designed for
	bool SetEffectiveEnergy(const float nEffectiveEnergy);
	/// @see SetEffectiveEnergy
	float GetEffectiveEnergy()const;

	/// Distance from the output of the X-Ray source to the G0 grating in centimeters
	bool SetDistanceFromG0ToSourceInCentimeters(const float nDistanceG0XR);
	/// @see SetDistanceFromG0ToSourceInCentimeters
	float GetDistanceFromG0ToSourceInCentimeters()const;
	/// Returns true if value is set
	bool HasDistanceFromG0ToSource()const;
	/// Delete data
	void DeleteDistanceFromG0ToSource();

	/// Distance from the output of the X-Ray source to the G1 grating in centimeters
	bool SetDistanceFromG1ToSourceInCentimeters(const float nDistanceG1XR);
	/// @see SetDistanceFromG1ToSourceInCentimeters
	float GetDistanceFromG1ToSourceInCentimeters()const;
	/// Returns true if value is set
	bool HasDistanceFromG1ToSource()const;
	/// Delete data
	void DeleteDistanceFromG1ToSource();

	/// Distance G2 XR is temporarily disabled
	/*
	/// Distance from the output of the X-Ray source to the G2 grating in centimeters
	bool SetDistanceFromG2ToSourceInCentimeters(const float nDistanceG2XR);
	/// @see SetDistanceFromG2ToSourceInCentimeters
	float GetDistanceG2ToSourceInCentimeters()const;
	/// Returns true if value is set
	bool HasDistanceFromG2ToSource()const;
	/// Delete data
	void DeleteDistanceFromG2ToSource();
	*/

	/// The pitch or period of the G0 grating
	bool SetG0AbsorptionPeriod(const float nG0Absorption);
	/// @see SetG0AbsorptionPeriod
	float GetG0AbsorptionPeriod()const;
	/// Returns true if value is set
	bool HasG0AbsorptionPeriod()const;
	/// Delete data
	void DeleteG0AbsorptionPeriod();

	/// The period of the G1 grating
	bool SetG1PhasePeriod(const float nG1Phase);
	/// @see SetG1PhasePeriod
	float GetG1PhasePeriod()const;
	/// Returns true if value is set
	bool HasG1PhasePeriod()const;
	/// Delete data
	void DeleteG1PhasePeriod();

	/// The period of the G2 grating
	bool SetG2AnalyzerPeriod(const float nG2Analyzer);
	/// @see SetG2AnalyzerPeriod
	float GetG2AnalyzerPeriod()const;
	/// Returns true if value is set
	bool HasG2AnalyzerPeriod()const;
	/// Delete data
	void DeleteG2AnalyzerPeriod();

	/// The resulting visibility of the phase and dark image
	bool SetVisibility(const float nVisibility);
	/// @see SetVisibility
	float GetVisibility()const;
	/// Returns true if value is set
	bool HasVisibility()const;
	/// Delete data
	void DeleteVisibility();

	/// The resulting size of the X-Ray detectors which are combined to provide the absorption pixel size (x, y)
	bool SetAbsorptionXRDetectorSize(const float nSizeX, const float nSizeY);
	/// @see SetAbsorptionXRDetectorSize
	float GetAbsorptionXRDetectorSizeX()const;
	/// @see SetAbsorptionXRDetectorSize
	float GetAbsorptionXRDetectorSizeY()const;
	/// Returns true if value is set
	bool HasAbsorptionXRDetectorSize()const;
	/// Delete data
	void DeleteAbsorptionXRDetectorSize();

	/// The resulting size of the X-Ray detectors which are combined to provide the absorption voxel size (x, y)
	bool SetAbsorptionReconstructionVoxelSize(const float nSizeX, const float nSizeY);
	/// @see SetAbsorptionReconstructionVoxelSize
	float GetAbsorptionReconstructionVoxelSizeX()const;
	/// @see SetAbsorptionReconstructionVoxelSize
	float GetAbsorptionReconstructionVoxelSizeY()const;
	/// Returns true if value is set
	bool HasAbsorptionReconstructionVoxelSize()const;
	/// Delete data
	void DeleteAbsorptionReconstructionVoxelSize();

	/// The resulting size of the X-Ray detectors which are combined to provide the phase pixel size (x, y)
	bool SetPhaseXRDetectorSize(const float nSizeX, const float nSizeY);
	/// @see SetPhaseXRDetectorSize
	float GetPhaseXRDetectorSizeX()const;
	/// @see SetPhaseXRDetectorSize
	float GetPhaseXRDetectorSizeY()const;
	/// Returns true if value is set
	bool HasPhaseXRDetectorSize()const;
	/// Delete data
	void DeletePhaseXRDetectorSize();

	/// The resulting size of the X-Ray detectors which are combined to provide the phase voxel size, (x, y, z)
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

	/// The resulting size of the X-Ray detectors which are combined to provide the dark image pixel size (x, y)
	bool SetDarkXRDetectorSize(const float nSizeX, const float nSizeY);
	/// @see SetDarkXRDetectorSize
	float GetDarkXRDetectorSizeX()const;
	/// @see SetDarkXRDetectorSize
	float GetDarkXRDetectorSizeY()const;
	/// Returns true if value is set
	bool HasDarkXRDetectorSize()const;
	/// Delete data
	void DeleteDarkXRDetectorSize();

	/// The resulting size of the X-Ray detectors which are combined to provide the dark image voxel size, (x, y, z)
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
	class XRayEquipmentUserImpl;
	XRayEquipmentUserImpl	*m_pXRayEquipmentUserImpl;

	const XRayEquipmentUserImpl* GetImpl() const;
	XRayEquipmentUserImpl* GetImpl();
};

}//namespace SDICOS

#endif /* _STRATOVAN_DICOS_USER_XRAY_EQUIPMENT_H_ */
