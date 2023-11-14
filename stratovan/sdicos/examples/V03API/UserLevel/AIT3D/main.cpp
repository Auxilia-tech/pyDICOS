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

void ParentClassChanges()
{
	SDICOS::AIT3D ait;

	/*
	* Updates to IODCommon parent class
	*/
	{
		SDICOS::IODCommon& iodcommon = ait;

		/*
		* Enumeration changed from SDICOS::IODCommon::enumDX to SDICOS::IODCommon::enumXRAY
		*/
		SDICOS::IODCommon::enumXRAY;

		/*
		* "Hold Mode" changed VR from SH to CS
		* Defined terms:
		*	YES
		*	NO
		*
		* Updated API:
		*	- SDICOS::IODCommon::SetHoldMode(const SDICOS::GeneralEquipmentModule::HOLD_MODE)
		*	- SDICOS::GeneralEquipmentModule::HOLD_MODE SDICOS::GeneralEquipmentModule::GetHoldMode()
		*
		* Previous API:
		*	- SDICOS::IODCommon::SetHoldMode(const DcsShortString&)
		*	- SDICOS::DcsString SDICOS::IODCommon::GetHoldMode()
		*/
		iodcommon.SetHoldMode(SDICOS::GeneralEquipmentModule::enumHoldMode_Yes);
		iodcommon.SetHoldMode(SDICOS::GeneralEquipmentModule::enumHoldMode_No);

		/*
		* "Number of Views" moved from SDICOS::ScanCommon to SDICOS::IODCommon
		*
		* Updated API:
		*	- SDICOS::IODCommon::SetNumberOfViews()
		*	- SDICOS::IODCommon::GetNumberOfViews()
		*	- SDICOS::IODCommon::HasNumberOfViews()
		*	- SDICOS::IODCommon::DeleteNumberOfViews()
		*
		* Previous API:
		*	- SDICOS::ScanCommon::SetSeriesNumberOfViews()
		*	- SDICOS::ScanCommon::GetSeriesNumberOfViews()
		*	- SDICOS::ScanCommon::HasSeriesNumberOfViews()
		*	- SDICOS::ScanCommon::DeleteSeriesNumberOfViews()
		*/
		iodcommon.SetNumberOfViews(2);

		/*
		* "Number of Energies" moved from SDICOS::ScanCommon to SDICOS::IODCommon
		*
		* Updated API:
		*	- SDICOS::IODCommon::SetNumberOfEnergies()
		*	- SDICOS::IODCommon::GetNumberOfEnergies()
		*	- SDICOS::IODCommon::HasNumberOfEnergies()
		*	- SDICOS::IODCommon::DeleteNumberOfEnergies()
		*
		* Previous API:
- 		*	- SDICOS::ScanCommon::SetSeriesNumberOfEnergies()
		*	- SDICOS::ScanCommon::GetSeriesNumberOfEnergies()
		*	- SDICOS::ScanCommon::HasSeriesNumberOfEnergies()
		*	- SDICOS::ScanCommon::DeleteSeriesNumberOfEnergies()
		*/
		iodcommon.SetNumberOfEnergies(1);

		/*
		* "Series View" moved from SDICOS::ScanCommon to SDICOS::IODCommon
		*
		* Updated API:
		*	- SDICOS::IODCommon::SetSeriesView()
		*	- SDICOS::IODCommon::GetSeriesView()
		*	- SDICOS::IODCommon::HasSeriesView()
		*	- SDICOS::IODCommon::DeleteSeriesView()
		*
		* Previous API:
		*	- SDICOS::ScanCommon::SetSeriesView()
		*	- SDICOS::ScanCommon::GetSeriesView()
		*	- SDICOS::ScanCommon::HasSeriesView()
		*	- SDICOS::ScanCommon::DeleteSeriesView()
		*/
		iodcommon.SetSeriesView(0);

		/*
		* "Series View Description" moved from SDICOS::ScanCommon to SDICOS::IODCommon
		*
		* Updated API:
		*	- SDICOS::IODCommon::SetSeriesViewDescription()
		*	- SDICOS::IODCommon::GetSeriesViewDescription()
		*	- SDICOS::IODCommon::HasSeriesViewDescription()
		*	- SDICOS::IODCommon::DeleteSeriesViewDescription()
		*
		* Previous API:
		*	- SDICOS::ScanCommon::SetSeriesViewDescription()
		*	- SDICOS::ScanCommon::GetSeriesViewDescription()
		*	- SDICOS::ScanCommon::HasSeriesViewDescription()
		*	- SDICOS::ScanCommon::DeleteSeriesViewDescription()
		*/
		iodcommon.SetSeriesViewDescription("View Description");

		/*
		* "Series Energy" moved from SDICOS::ScanCommon to SDICOS::IODCommon
		*
		* Updated API:
		*	- SDICOS::IODCommon::SetSeriesEnergy()
		*	- SDICOS::IODCommon::GetSeriesEnergy()
		*	- SDICOS::IODCommon::HasSeriesEnergy()
		*	- SDICOS::IODCommon::DeleteSeriesEnergy()
		*
		* Previous API:
		*	- SDICOS::ScanCommon::SetSeriesEnergy()
		*	- SDICOS::ScanCommon::GetSeriesEnergy()
		*	- SDICOS::ScanCommon::HasSeriesEnergy()
		*	- SDICOS::ScanCommon::DeleteSeriesEnergy()
		*/
		iodcommon.SetSeriesEnergy(2);

		/*
		* "Series Energy Description" moved from SDICOS::ScanCommon to SDICOS::IODCommon
		*
		* Updated API:
		*	- SDICOS::IODCommon::SetSeriesEnergyDescription()
		*	- SDICOS::IODCommon::GetSeriesEnergyDescription()
		*	- SDICOS::IODCommon::HasSeriesEnergyDescription()
		*	- SDICOS::IODCommon::DeleteSeriesEnergyDescription()
		*
		* Previous API:
		*	- SDICOS::ScanCommon::SetSeriesEnergyDescription()
		*	- SDICOS::ScanCommon::GetSeriesEnergyDescription()
		*	- SDICOS::ScanCommon::HasSeriesEnergyDescription()
		*	- SDICOS::ScanCommon::DeleteSeriesEnergyDescription()
		*/
		iodcommon.SetSeriesEnergyDescription("Energy Description");

		/*
		* Referenced scans at the User-Level API will now store references under the "Referenced Scan Sequence"
		* defined in the "General Scan Module" instead of the "Common Instance Reference Module".
		*/
		{
			/*
			* AddReferencedSopInstance() removed the parameter for Series Instance UID
			*/
			{
				SDICOS::DcsUniqueIdentifier dcsSeriesInstanceUID;
				SDICOS::DcsUniqueIdentifier dcsSopInstanceUID;
				SDICOS::DcsUniqueIdentifier dcsSopClassUID;

				//Old Call: 
				//iodcommon.AddReferencedSopInstance(dcsSeriesInstanceUID, dcsSopInstanceUID, dcsSopClassUID);

				//New Call:
				iodcommon.AddReferencedSopInstance(dcsSopInstanceUID, dcsSopClassUID);
			}

			/*
			*	SDICOS::IODCommon::GetReferencedSeriesInstances() is removed since Referenced Scan Sequence only stores SOP Instance UID and SOP Class UID
			*/

		}
	}

	/*
	* Updates to ScanCommon parent class
	*/
	{
		SDICOS::ScanCommon& scanCommon = ait;
		
		/*
		* Changes to TipImageType
		* "PROJECTION" changed to "FTI"
		* "COMPOSITE" changed to "CTI"
		*
		* Updated API:
		*	- SDICOS::ScanCommon::SetTipImageFTI()
		*	- SDICOS::ScanCommon::IsTipImageFTI()
		*	- SDICOS::ScanCommon::SetTipImageCTI()
		*	- SDICOS::ScanCommon::IsTipImageCTI()
		*
		* Previous API:
		*	- SDICOS::ScanCommon::SetTipImageProjection()
		*	- SDICOS::ScanCommon::IsTipImageProjection()
		*	- SDICOS::ScanCommon::SetTipImageComposite()
		*	- SDICOS::ScanCommon::IsTipImageComposite()
		*/
		scanCommon.SetTipImageFTI();
		scanCommon.SetTipImageCTI();
	}

	/*
	* Updates to AIT3D class
	*/
	{
		/*
		* Image Type Value 2 (Image Characteristics) can now be non-NULL.  If it is not NULL valid values are:
		* "CNT_AMP" for Content Amplitude and "CNT_CPX_AMP" for Content Complex Amplitude
		* SetImageType now accepts four arguments to accommodate the value for Image Characteristics
		* Added GetImageCharacteristicss
		*/
		SDICOS::AIT3DTypes::AIT3DImage::AIT3D_PIXEL_DATA_CHARACTERISTICS nPixelDataCharacteristics(SDICOS::AIT3DTypes::AIT3DImage::enumDerived);
		SDICOS::AITImageType::AIT_IMAGE_CHARACTERISTICS nImageCharacteristics(SDICOS::AITImageType::enumNoImageCharacteristic);
		SDICOS::AIT3DTypes::AIT3DImage::IMAGE_FLAVOR nImageFlavor(SDICOS::AIT3DTypes::AIT3DImage::enumProjection);
		SDICOS::AIT3DTypes::AIT3DImage::DERIVED_PIXEL_CONTRAST nDerivedPixelContrast(SDICOS::AIT3DTypes::AIT3DImage::enumMixedContrast);

		//Old Call:
		//ait.SetImageType(nPixelDataCharacteristics, nImageFlavor, nDerivedPixelContrast);

		//New Call:
		ait.SetImageType(nPixelDataCharacteristics, nImageCharacteristics, nImageFlavor, nDerivedPixelContrast);

		//Get Image Characteristics
		nImageCharacteristics = ait.GetImageCharacteristics();


		/*
		* Frame of Reference
		* changes:
		*
		* Frame of Reference attributes now are inherited from SDICOS::FrameOfReferenceUser instead of being direct members of AIT3D
		*
		* SDICOS::FrameOfReferenceUser::GetFrameOfReferenceUID now returns const SDICOS::DcsUniqueIdentifier instead of const DcsString&
		*/
		{
			// Previous:
			// const DcsString& SDICOS::AIT3D::GetFrameOfReferenceUID() const;
			// Updated:
			// const DcsUniqueIdentifier SDICOS::FrameOfReferenceUser::GetFrameOfReferenceUID() const;
			ait.GetFrameOfReferenceUID();
		}
	}
}

int main()
{
	ParentClassChanges(); //Changes common to multiple modalities

	return 0;
}