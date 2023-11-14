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

void NewBaseClassTags()
{
	SDICOS::DXModule dx;

	//OOI Owner Module
	{
		dx.AllocateObjectOfInspectionOwner();
		SDICOS::ObjectOfInspectionOwnerModule *pOOIOwner = dx.GetObjectOfInspectionOwner();

		//OOI Owner Risk Score - A new optional tag to set a OOI Owner's risk score
		{
			SDICOS::S_INT16 nRiskScore(5);

			//Set the risk score
			pOOIOwner->SetOwnerRiskScore(nRiskScore);

			//Get the risk score
			nRiskScore = pOOIOwner->GetOwnerRiskScore();

			//Remove the Risk Score
			pOOIOwner->DeleteOwnerRiskScore();

			//Check if a risk score is present in ObjectOfInspectionOwnerModule. This is primarily
			//used after loading a DICOS file or receiving a DICOS file from a network transfer.
			if (pOOIOwner->HasOwnerRiskScore())
			{
				//Tag is present
				nRiskScore = pOOIOwner->GetOwnerRiskScore();
			}
			else
			{
				//Tag is not present
			}
		}
	}

	//X-Ray Equipment Module
	{
		/*  X-Ray Equipment Module
		 *
		 *  Describes the attributes related to the device's grating and detectors during the acquisition of an X-Ray image
		 *
		 *  See within SDICOS::DXModule:
		 *      - bool SetXRayEquipment(const XRayEquipmentModule &xRayEquipment);
		 *      - bool GetXRayEquipment(XRayEquipmentModule &xRayEquipment)const;
		 *      - XRayEquipmentModule& GetXRayEquipment();
		 *      - const XRayEquipmentModule& GetXRayEquipment()const;
		 */
		SDICOS::XRayEquipmentModule& xRayEquipment = dx.GetXRayEquipment();


		// Members of X-Ray Equipment Module:


		/*  Mask Characteristics : Tag (4300, 0906), VR = ST [optional]
		 *
		 *  Describes how the CAI mask was designed
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetMaskCharacteristics(const DcsShortText &nMaskCharacteristics);
		 *      - DcsShortText GetMaskCharacteristics()const;
		 *      - bool HasMaskCharacteristics()const;
		 *      - void DeleteMaskCharacteristics();
		 */
		xRayEquipment.GetMaskCharacteristics();

		/*  Type of G0 : Tag (4300, 0904), VR = CS [optional]
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetTypeG0(const TYPE_G nTypeG0);
		 *      - TYPE_G GetTypeG0()const;
		 *      - DcsString GetTypeG0AsString()const;
		 *      - bool HasTypeG0()const;
		 *      - void DeleteTypeG0();
		 */
		xRayEquipment.GetTypeG0();
		// Valid Values:
		SDICOS::XRayEquipmentModule::enumGratingG0;
		SDICOS::XRayEquipmentModule::enumMaskG0;

		/*  Type of G1 : Tag (4300, 0910), VR = CS [optional]
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetTypeG1(const TYPE_G nTypeG1);
		 *      - TYPE_G GetTypeG1()const;
		 *      - DcsString GetTypeG1AsString()const;
		 *      - bool HasTypeG1()const;
		 *      - void DeleteTypeG1();
		 */
		xRayEquipment.GetTypeG1();
		// Valid Values:
		SDICOS::XRayEquipmentModule::enumGratingG1;
		SDICOS::XRayEquipmentModule::enumOtherG1;

		/*  Type of G2 : Tag (4300, 0914), VR = CS [optional]
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetTypeG2(const TYPE_G nTypeG2);
		 *      - TYPE_G GetTypeG2()const;
		 *      - DcsString GetTypeG2AsString()const;
		 *      - bool HasTypeG2()const;
		 *      - void DeleteTypeG2();
		 */
		xRayEquipment.GetTypeG2();
		// Valid Values:
		SDICOS::XRayEquipmentModule::enumGratingG2;
		SDICOS::XRayEquipmentModule::enumOtherG2;

		/*  Reconstruction Algorithm for Phase Image : Tag (4300, 0938), VR = CS [optional]
		 *
		 *  Type of algorithm used for reconstruction of the phase image
		 * 
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetReconAlgorithmPhaseImage(const RECON_IMAGE nPhaseImage);
		 *      - RECON_IMAGE GetReconAlgorithmPhaseImage()const;
		 *      - DcsString GetReconAlgorithmPhaseImageAsString()const;
		 *      - bool HasReconAlgorithmPhaseImage()const;
		 *      - void DeleteReconAlgorithmPhaseImage();
		 */
		xRayEquipment.GetReconAlgorithmPhaseImage();
		// Valid Values:
		SDICOS::XRayEquipmentModule::enumFFT;
		SDICOS::XRayEquipmentModule::enumModifiedFFT;
		SDICOS::XRayEquipmentModule::enumOtherImage;
		
		/*  Reconstruction Algorithm for Dark Image : Tag (4300, 0940), VR = CS [optional]
		 *
		 *  Type of algorithm used for reconstruction of the dark image
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetReconAlgorithmDarkImage(const RECON_IMAGE nDarkImage);
		 *      - RECON_IMAGE GetReconAlgorithmDarkImage()const;
		 *      - DcsString GetReconAlgorithmDarkImageAsString()const;
		 *      - bool HasReconAlgorithmDarkImage()const;
		 *      - void DeleteReconAlgorithmDarkImage();
		 */
		xRayEquipment.GetReconAlgorithmDarkImage();
		// Valid Values:
		SDICOS::XRayEquipmentModule::enumFFT;
		SDICOS::XRayEquipmentModule::enumModifiedFFT;
		SDICOS::XRayEquipmentModule::enumOtherImage;

		/*  Effective Energy : Tag (4300, 0902), VR = FL [required]
		 *
		 *  The energy for which the gratings were designed for
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetEffectiveEnergy(const float nEffectiveEnergy);
		 *      - float GetEffectiveEnergy()const;
		 */
		xRayEquipment.GetEffectiveEnergy();

		/*  Distance G0 from X-Ray Source : Tag (4300, 0908), VR = FL [optional]
		 *
		 *  Distance from the output of the X-Ray source to the G0 grating (in cm)
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetDistanceFromG0ToSourceInCentimeters(const float nDistanceG0XR);
		 *      - float GetDistanceFromG0ToSourceInCentimeters()const;
		 *      - bool HasDistanceFromG0ToSourceInCentimeters()const;
		 *      - void DeleteDistanceFromG0ToSourceInCentimeters();
		 */
		xRayEquipment.GetDistanceFromG0ToSourceInCentimeters();

		/*  Distance G1 from X-Ray Source : Tag (4300, 0912), VR = FL [optional]
		 *
		 *  Distance from the output of the X-Ray source to the G1 grating (in cm)
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetDistanceFromG1ToSourceInCentimeters(const float nDistanceG1XR);
		 *      - float GetDistanceFromG1ToSourceInCentimeters()const;
		 *      - bool HasDistanceFromG1ToSourceInCentimeters()const;
		 *      - void DeleteDistanceFromG1ToSourceInCentimeters();
		 */
		xRayEquipment.GetDistanceFromG1ToSourceInCentimeters();

		/*  G0 Absorption Period : Tag (4300, 0918), VR = FL [optional]
		 *
		 *  The pitch or period of the G0 grating
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetG0AbsorptionPeriod(const float nG0Absorption);
		 *      - float GetG0AbsorptionPeriod()const;
		 *      - bool HasG0AbsorptionPeriod()const;
		 *      - void DeleteG0AbsorptionPeriod();
		 */
		xRayEquipment.GetG0AbsorptionPeriod();

		/*  G1 Phase Period : Tag (4300, 0920), VR = FL [optional]
		 *
		 *  The period of the G1 grating
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetG1PhasePeriod(const float nG1Phase);
		 *      - float GetG1PhasePeriod()const;
		 *      - bool HasG1PhasePeriod()const;
		 *      - void DeleteG1PhasePeriod();
		 */
		xRayEquipment.GetG1PhasePeriod();

		/*  G2 Analyzer Period : Tag (4300, 0922), VR = FL [optional]
		 *
		 *  The period of the G1 grating
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetG2AnalyzerPeriod(const float nG2Analyzer);
		 *      - float GetG2AnalyzerPeriod()const;
		 *      - bool HasG2AnalyzerPeriod()const;
		 *      - void DeleteG2AnalyzerPeriod();
		 */
		xRayEquipment.GetG2AnalyzerPeriod();

		/*  Visibility : Tag (4300, 0924), VR = FL [optional]
		 *
		 *  The resulting visibility of the phase and dark image
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetVisibility(const float nVisibility);
		 *      - float GetVisibility()const;
		 *      - bool HasVisibility()const;
		 *      - void DeleteVisibility();
		 */
		xRayEquipment.GetVisibility();

		/*  Absorption X-Ray Detector Size : Tag (4300, 0926), VR = FL [optional]
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetAbsorptionXRDetectorSize(const float nSizeX, const float nSizeY);
		 *      - float GetAbsorptionXRDetectorSizeX()const;
		 *      - float GetAbsorptionXRDetectorSizeY()const;
		 *      - bool HasAbsorptionXRDetectorSize()const;
		 *      - void DeleteAbsorptionXRDetectorSize();
		 */
		xRayEquipment.GetAbsorptionXRDetectorSizeX();
		xRayEquipment.GetAbsorptionXRDetectorSizeY();

		/*  Absorption Reconstruction Voxel Size : Tag (4300, 0928), VR = FL [optional]
		 *
		 *  The resulting size of the X-Ray detectors which are combined to provide the absorption pixel/voxel size (x, y)
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetAbsorptionReconstructionVoxelSize(const float nSizeX, const float nSizeY);
		 *      - float GetAbsorptionReconstructionVoxelSizeX()const;
		 *      - float GetAbsorptionReconstructionVoxelSizeY()const;
		 *      - bool HasAbsorptionReconstructionVoxelSize()const;
		 *      - void DeleteAbsorptionReconstructionVoxelSize();
		 */
		xRayEquipment.GetAbsorptionReconstructionVoxelSizeX();
		xRayEquipment.GetAbsorptionReconstructionVoxelSizeY();

		/*  Phase X-Ray Detector Size : Tag (4300, 0930), VR = FL [optional]
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetPhaseXRDetectorSize(const float nSizeX, const float nSizeY);
		 *      - float GetPhaseXRDetectorSizeX()const;
		 *      - float GetPhaseXRDetectorSizeY()const;
		 *      - bool HasPhaseXRDetectorSize()const;
		 *      - void DeletePhaseXRDetectorSize();
		 */
		xRayEquipment.GetPhaseXRDetectorSizeX();
		xRayEquipment.GetPhaseXRDetectorSizeY();

		/*  Phase Reconstruction Voxel Size : Tag (4300, 0932), VR = FL [optional]
		 *
		 *  The resulting size of the X-Ray detectors which are combined to provide the phase pixel/voxel size (x, y)
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetPhaseReconstructionVoxelSize(const float nSizeX, const float nSizeY, const float nSizeZ);
		 *      - float GetPhaseReconstructionVoxelSizeX()const;
		 *      - float GetPhaseReconstructionVoxelSizeY()const;
		 *      - float GetPhaseReconstructionVoxelSizeZ()const;
		 *      - bool HasPhaseReconstructionVoxelSize()const;
		 *      - void DeletePhaseReconstructionVoxelSize();
		 */
		xRayEquipment.GetPhaseReconstructionVoxelSizeX();
		xRayEquipment.GetPhaseReconstructionVoxelSizeY();
		xRayEquipment.GetPhaseReconstructionVoxelSizeZ();

		/*  Dark XR Detector Size : Tag (4300, 0934), VR = FL [optional]
		 *
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetDarkXRDetectorSize(const float nSizeX, const float nSizeY);
		 *      - float GetDarkXRDetectorSizeX()const;
		 *      - float GetDarkXRDetectorSizeY()const;
		 *      - bool HasDarkXRDetectorSize()const;
		 *      - void DeleteDarkXRDetectorSize();
		 */
		xRayEquipment.GetDarkXRDetectorSizeX();
		xRayEquipment.GetDarkXRDetectorSizeY();

		/*  Dark Reconstruction Voxel Size : Tag (4300, 0936), VR = FL [optional]
		 *
		 *  The resulting size of the X-Ray detectors which are combined to provide the dark image voxel size, (x, y, z)
		 * 
		 *  See within SDICOS::XRayEquipmentModule:
		 *      - bool SetDarkReconstructionVoxelSize(const float nSizeX, const float nSizeY, const float nSizeZ);
		 *      - float GetDarkReconstructionVoxelSizeX()const;
		 *      - float GetDarkReconstructionVoxelSizeY()const;
		 *      - float GetDarkReconstructionVoxelSizeZ()const;
		 *      - bool HasDarkReconstructionVoxelSize()const;
		 *      - void DeleteDarkReconstructionVoxelSize();
		 */
		xRayEquipment.GetDarkReconstructionVoxelSizeX();
		xRayEquipment.GetDarkReconstructionVoxelSizeY();
		xRayEquipment.GetDarkReconstructionVoxelSizeZ();
	}
}
/// End NewBaseClassTags

void XRayPositioning()
{
	SDICOS::DXModule moduleAPI;

	/*
	 *  Additions to DX/X-Ray Positioning
	 */
	{
		moduleAPI.AllocatePositioning();
		SDICOS::DXTypes::DXPositioning* pPositioning = moduleAPI.GetPositioning();
		SDICOS::DXTypes::DetectorGeometry& geometrySequence = pPositioning->GetDetectorGeometrySequence();
		
		SDICOS::Array1D<SDICOS::DXTypes::DetectorGeometry::GeometryItem>& vGeometryItems = geometrySequence.GetSequence();
		vGeometryItems.SetSize(1);
		SDICOS::DXTypes::DetectorGeometry::GeometryItem& geometryItem = pPositioning->GetDetectorGeometrySequence().GetSequence()[0];

		/* Detector Geometry Sequence [optional]
		 *
		 * This attribute has changed from required to optional
		 * Contains a sequence of detector positioning module attributes
		 *
		 * See within SDICOS::DXTypes::DetectorGeometry:
		 *
		 *     Pre-existing:
		 *      - bool SetDetectorGeometrySequence(const DetectorGeometry &dg);
		 *      - bool GetDetectorGeometrySequence(DetectorGeometry &dg)const;
		 *      - DetectorGeometry& GetDetectorGeometrySequence();
		 *      - const DetectorGeometry& GetDetectorGeometrySequence()const;
		 *     New:
		 *      - bool HasDetectorGeometrySequence()const;
		 *      - void DeleteDetectorGeometrySequence();
		 */
		pPositioning->HasDetectorGeometrySequence();

		/* Distance Source to Detector [optional]
		 *
		 * This attribute has changed from required to optional
		 * Specifies the distance in mm from source to detector center
		 *
		 * See within SDICOS::DXTypes::DetectorGeometry::GeometryItem:
		 *
		 *     Pre-existing:
		 *      - bool SetDistanceToDetectorMM(const float fDistanceToDetector);
		 *      - float GetDistanceToDetector()const;
		 *      - DcsString GetDistanceToDetectorAsString()const;
		 *     New:
		 *      - bool HasDistanceToDetector()const;
		 *      - void DeleteDistanceToDetector();
		 */
		geometryItem.HasDistanceToDetector();

		/* Source Orientation [optional]
		 *
		 * This attribute has changed from required to optional
		 * Specifies directional cosines of the X-Ray beam in the coordinate system in degrees relative to gravity (0 degrees)
		 *
		 * See within SDICOS::DXTypes::DetectorGeometry::GeometryItem:
		 *
		 *     Pre-existing:
		 *      - bool SetSourceOrientation(const float fDirectionalCosineX, const float fDirectionalCosineY, const float fDirectionalCosineZ);
		 *      - bool GetSourceOrientation(float &fDirectionalCosineX, float &fDirectionalCosineY, float &fDirectionalCosineZ)const;
		 *     New:
		 *      - bool HasSourceOrientation()const;
		 *      - void DeleteSourceOrientation();
		 */
		geometryItem.HasSourceOrientation();

		/* Source Position [optional]
		 *
		 * This attribute has changed from required to optional
		 * Specifies the (x,y,z) position coordinates of the X-Ray source in mm relative to the origin of the coordinate system
		 *
		 * See within SDICOS::DXTypes::DetectorGeometry::GeometryItem:
		 *
		 *     Pre-existing:
		 *      - bool SetSourcePosition(const float fPositionX, const float fPositionY, const float fPositionZ);
		 *      - bool GetSourcePosition(float &fPositionX, float &fPositionY, float &fPositionZ)const;
		 *     New:
		 *      - bool HasSourcePosition()const;
		 *      - void DeleteSourcePosition();
		 */
		geometryItem.HasSourcePosition();

	}
}
/// End XRayPositioning

void XRayDetector()
{
	SDICOS::DXModule dx;
	SDICOS::DXTypes::DXDetector &det = dx.GetDetector();

	/*
	* Detector Type has one new enumeration:
	*/
	{
		det.SetDetectorType(SDICOS::DXTypes::DXDetector::enumOther); // "OTHER"

		//Check if Detector Type is present and valid
		bool bRet = det.HasDetectorType();
	}

	/*
	* Detector Configuration has new enumerations:
	*/
	{
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumUnknown);			// "UNKNOWN"
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumSandwich);		// "SANDWICH"
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumSideBySide);		// "SIDE BY SIDE"
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumCheckerboard);	// "CHECKERBOARD"
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumMonoEnergetic);	// "MONOENERGETIC"

		//Check if Detector Configuration is present
		bool bRet = det.HasDetectorConfiguration();
	}
}
/// End XRayDetector

void TipImageFeatures()
{
	SDICOS::DXModule dx;
	dx.AllocateTipImage();
	SDICOS::TipImage* tipImage = dx.GetTipImage();

	/*
	* TIP Library Name - a new optional tag to set the TIP library name
	*/
	{
		//Set the library name
		tipImage->SetTipLibraryName("EXAMPLE LIBRARY NAME");
		
		//Check if the library name is set, if it is get it
		if(tipImage->HasTipLibraryName())
		{
			SDICOS::DcsShortText strLibraryName;
			strLibraryName = tipImage->GetTipLibraryName();	
		}

		//Delete the library name
		tipImage->DeleteTipLibraryName();
	}

	/*
	* TIP Image Identifier - a new optional tag to set the TIP Image Identifier
	*/
	{
		//Set the image identifier
		tipImage->SetTipImageIdentifier("EXAMPLE IMAGE IDENTIFIER");
		
		//Check if the image identifier is set, if it is get it
		if(tipImage->HasTipImageIdentifier())
		{
			SDICOS::DcsShortText strImageIdentifier;
			strImageIdentifier = tipImage->GetTipImageIdentifier();	
		}

		//Delete the library name
		tipImage->DeleteTipImageIdentifier();
	}

	/*
	* TIP Library Date - a new optional tag to set the TIP Library Date
	*/
	{
		SDICOS::DcsDateTime dtLibraryDate;
		dtLibraryDate.SetNow();

		//Set the library date
		tipImage->SetTipLibraryDate(dtLibraryDate);

		//Check if the library date is set, if it is get it
		if(tipImage->HasTipLibraryDate())
		{
			dtLibraryDate = tipImage->GetTipLibraryDate();
		}

		//Delete the library date
		tipImage->DeleteTipLibraryDate();
	}
}

int main()
{
	//New functions for setting SOP Common values
	NewBaseClassTags();

	//New features for X-Ray Positioning
	XRayPositioning();

	//New features for X-Ray Detector
	XRayDetector();

	//New functions for SDICOS::TipImage
	TipImageFeatures();

	return 0;
}
