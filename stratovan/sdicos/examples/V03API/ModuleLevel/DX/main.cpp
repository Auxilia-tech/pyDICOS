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

int CommonModuleUpdates()
{
	SDICOS::DXModule moduleAPI;

	/*
	* General Equipment Module API Updates
	*/
	{
		SDICOS::GeneralEquipmentModule& genEquip = moduleAPI.GetGeneralEquipment();

		/*
		* "Hold Mode" (0060, 7022) changed VR from SH to CS
		* Defined terms:
		*	YES
		*	NO
		*
		* Updated API:
		*	- SDICOS::GeneralEquipmentModule::SetHoldMode(const HOLD_MODE)
		*	- SDICOS::GeneralEquipmentModule::HOLD_MODE SDICOS::GeneralEquipmentModule::GetHoldMode()
		*	- SDICOS::GeneralEquipmentModule::GetHoldModeAsString()
		*
		* Previous API:
		*	- SDICOS::GeneralEquipmentModule::SetHoldMode(const DcsShortString&)
		*	- SDICOS::DcsString SDICOS::GeneralEquipmentModule::GetHoldMode()
		*/
		genEquip.SetHoldMode(SDICOS::GeneralEquipmentModule::enumHoldMode_Yes);
		genEquip.SetHoldMode(SDICOS::GeneralEquipmentModule::enumHoldMode_No);
	}


	/*
	* General Scan Module API Updates
	*/
	{
		SDICOS::GeneralScanModule& genScan = moduleAPI.GetGeneralScan();

		/*
		* "Referenced Scan Sequence" (0008, 1110) changed from optional to required if "Modality" (0008,0060) is TDR
		*
		* See:
		*	- SDICOS::GeneralScanModule::SetReferencedScans()
		*	- SDICOS::GeneralScanModule::GetReferencedScans()
		*	- SDICOS::GeneralScanModule::HasReferencedScans()
		*	- SDICOS::GeneralScanModule::DeleteReferencedScans()
		*/
		genScan.GetReferencedScans();

		/*
		* "Number of Views" (6100, 0028) has moved from General Series to General Scan
		*
		* Updated API:
		*	- SDICOS::GeneralScanModule::SetNumberOfViews()
		*	- SDICOS::GeneralScanModule::GetNumberOfViews()
		*	- SDICOS::GeneralScanModule::HasNumberOfViews()
		*	- SDICOS::GeneralScanModule::DeleteNumberOfViews()
		*
		* Previous API:
		*	- SDICOS::GeneralSeriesModule::SetSeriesNumberOfViews()
		*	- SDICOS::GeneralSeriesModule::GetSeriesNumberOfViews()
		*	- SDICOS::GeneralSeriesModule::HasSeriesNumberOfViews()
		*	- SDICOS::GeneralSeriesModule::DeleteSeriesNumberOfViews()
		*/
		genScan.SetNumberOfViews(1);

		/*
		* "Number of Energies" (6100, 0032) has moved from General Series to General Scan
		*
		* Updated API:
		*	- SDICOS::GeneralScanModule::SetNumberOfEnergies()
		*	- SDICOS::GeneralScanModule::GetNumberOfEnergies()
		*	- SDICOS::GeneralScanModule::HasNumberOfEnergies()
		*	- SDICOS::GeneralScanModule::DeleteNumberOfEnergies()
		*
		* Previous API:
		*	- SDICOS::GeneralSeriesModule::SetSeriesNumberOfEnergies()
		*	- SDICOS::GeneralSeriesModule::GetSeriesNumberOfEnergies()
		*	- SDICOS::GeneralSeriesModule::HasSeriesNumberOfEnergies()
		*	- SDICOS::GeneralSeriesModule::DeleteSeriesNumberOfEnergies()
		*/
		genScan.SetNumberOfEnergies(1);
	}

	/*
	* General Series API Updates
	*/
	{
		SDICOS::GeneralSeriesModule& series = moduleAPI.GetSeries();

		/*
		* Series Number VR changed from SL to IS
		*/
		{
			SDICOS::DcsInteger dcsInteger(100); //DcsInteger can be initialized with an S_INT32 parameter

			//SetSeriesNumber() takes SDICOS::DcsInteger instead of SDICOS::S_INT32
			series.SetSeriesNumber(dcsInteger);

			//GetSeriesNumber() returns DcsInteger instead of S_INT32 
			SDICOS::DcsInteger dcsGet = series.GetSeriesNumber();
		}

		/*
		* "Phantom Type" renamed to "Test Article"
		*
		* The following enumeration has been removed:
		*	enumNIST
		*
		* and replaced with the enumerations:
		*	enumNIST_FAT
		*	enumNIST_SAT
		*
		* A new enum has been included:
		*	enumGIQ
		*/
		{
			SDICOS::GeneralSeriesModule::enumNIST_FAT;
			SDICOS::GeneralSeriesModule::enumNIST_SAT;
			SDICOS::GeneralSeriesModule::enumGIQ;
		}
	}

	/*
	* TIP Image Module Updates
	*/
	{
		moduleAPI.AllocateTipImage();
		SDICOS::TipImage* tipImage = moduleAPI.GetTipImage();

		/*
		* Tip Image Type changes:
		* "PROJECTION" changed to "FTI" enumProjection->enumFTI
		* "COMPOSITE" changed to "CTI" enumComposite->enumCTI
		*/
		{
			//old calls
			//tipImage.SetTipImageType(SDICOS::TipImage::enumProjection);
			//tipImage.SetTipImageType(SDICOS::TipImage::enumComposite);

			//new calls
			tipImage->SetTipImageType(SDICOS::TipImage::enumFTI);
			tipImage->SetTipImageType(SDICOS::TipImage::enumCTI);
		}
	}

	return 0;
}

int BaseClassUpdate()
{
	SDICOS::DXModule dx;

	/*
	* Updates to SDICOS::DXTypes::DXSeries
	*/
	{
		SDICOS::DXTypes::DXSeries &series = dx.GetSeries();

		/*
		* V03 updated the modality string used for DX from "DX" to "XRAY"
		*/
		{
			//Modality string changed from "DX" to "XRAY"
			if (series.GetModalityAsString() == "XRAY")
			{
			}

			//Enumeration in SDICOS::GeneralSeriesModule changed from enumDX to enumXRAY
			if (SDICOS::GeneralSeriesModule::enumXRAY == series.GetModality())
			{
			}
		}

		/*
		* "Phantom Type" renamed to "Test Article Type"
		*/
		{
			/*
			* Enum renamed:
			*	- SDICOS::GeneralSeriesModule::PHANTOM_TYPE renamed to SDICOS::GeneralSeriesModule::TEST_ARTICLE_TYPE
			*	- SDICOS::GeneralSeriesModule::enumUnknownPhantomType renamed to SDICOS::GeneralSeriesModule::enumUnknownTestArticleType
			* 
			* APIs renamed:
			*	- SDICOS::GeneralSeriesModule::SetPhantomType() renamed to SetTestArticleType()
			*	- SDICOS::GeneralSeriesModule::GetPhantomType() renamed to GetTestArticleType()
			*	- SDICOS::GeneralSeriesModule::GetPhantomTypeAsString() renamed to GetTestArticleTypeAsString()
			*	- SDICOS::GeneralSeriesModule::HasPhantomType() renamed to HasTestArticleType()
			*	- SDICOS::GeneralSeriesModule::DeletePhantomType() renamed to DeleteTestArticleType()
			*/
		}
	}

	/*
	* DX Detector Updates
	*/
	{
		SDICOS::DXTypes::DXDetector& det = dx.GetDetector();

		/*
		* Detector Configuration has removed the below defined terms:
		*	- SDICOS::DXTypes::DXDetector::enumSlot;
		*	- SDICOS::DXTypes::DXDetector::enumArea;
		* 
		* The below new terms have been added:
		*/
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumUnknown);			// "UNKNOWN"
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumSandwich);		// "SANDWICH"
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumSideBySide);		// "SIDE BY SIDE"
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumCheckerboard);	// "CHECKERBOARD"
		det.SetDetectorConfiguration(SDICOS::DXTypes::DXDetector::enumMonoEnergetic);	// "MONOENERGETIC"

		/*
		* Bin Number has changed from 16-bit (VR = SS) to 32-bit (VR = SL)
		*/
		det.SetBinNumber(SDICOS::S_INT32(32));

		/*
		* The following attributes have changed VR from ST (string) to SL (32-bit signed int)
		*	- Higher Energy
		*	- Lower Energy
		*	- Energy Resolution
		*/
		det.SetHigherEnergy(SDICOS::S_INT32(100));
		det.SetLowerEnergy(SDICOS::S_INT32(10));
		det.SetEnergyResolution(SDICOS::S_INT32(1000));
	}

	return 0;
}

int main()
{
	//Updates common to many modalities
	CommonModuleUpdates();

	//Updates specific to DX
	BaseClassUpdate();

	return 0;
}
