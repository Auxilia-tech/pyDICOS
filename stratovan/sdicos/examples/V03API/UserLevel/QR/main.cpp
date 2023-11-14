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
	SDICOS::QR qr;

	/*
	* Updates to IODCommon parent class
	*/
	{
		SDICOS::IODCommon& iodcommon = qr;

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
		SDICOS::ScanCommon& scanCommon = qr;
		
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
}

void MethodRefactors()
{
	SDICOS::QR qr;

	/*
	* Renamed Methods from QR
	*/
	{
		SDICOS::DcsTime time;
		bool b = true;
		SDICOS::QR::QRMeasurement measurement;

		/*
		* GetMeasurmentsTime renamed to GetMeasurementsTime
		*/

		//Old Call: 
		//time = qr.GetMeasurmentsTime();

		//New Call:
		time = qr.GetMeasurementsTime();

		/*
		* GetMeasurment renamed to GetMeasurement
		*/

		//Old Call:
		//b = qr.GetMeasurment(0, measurement);

		//New Call:
		b = qr.GetMeasurement(0, measurement);

		/*
		* SetMeasurment renamed to SetMeasurement
		*/

		//Old Call:
		//b = qr.SetMeasurment(0, measurement);

		//New Call:
		b = qr.SetMeasurement(0, measurement);
	}
}

int main()
{
	MethodRefactors(); //Refactored methods
	ParentClassChanges(); //Changes common to multiple modalities

	return 0;
}