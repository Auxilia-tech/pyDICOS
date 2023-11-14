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
#include "SDICOS/DICOS.h"

bool InitTDR(SDICOS::TDRModule &tdr);

int CommonModuleUpdates()
{
    SDICOS::TDRModule moduleAPI;

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
        *   - SDICOS::GeneralScanModule::SetReferencedScans()
        *   - SDICOS::GeneralScanModule::GetReferencedScans()
        *   - SDICOS::GeneralScanModule::HasReferencedScans()
        *   - SDICOS::GeneralScanModule::DeleteReferencedScans()
        */
        genScan.GetReferencedScans();

        /*
        * "Number of Views" (6100, 0028) has moved from General Series to General Scan
        * 
        * Updated API:
        *   - SDICOS::GeneralScanModule::SetNumberOfViews()
        *   - SDICOS::GeneralScanModule::GetNumberOfViews()
        *   - SDICOS::GeneralScanModule::HasNumberOfViews()
        *   - SDICOS::GeneralScanModule::DeleteNumberOfViews()
        * 
        * Previous API:
        *   - SDICOS::GeneralSeriesModule::SetSeriesNumberOfViews()
        *   - SDICOS::GeneralSeriesModule::GetSeriesNumberOfViews()
        *   - SDICOS::GeneralSeriesModule::HasSeriesNumberOfViews()
        *   - SDICOS::GeneralSeriesModule::DeleteSeriesNumberOfViews()
        */
        genScan.SetNumberOfViews(1);

        /*
        * "Number of Energies" (6100, 0032) has moved from General Series to General Scan
        * 
        * Updated API:
        *   - SDICOS::GeneralScanModule::SetNumberOfEnergies()
        *   - SDICOS::GeneralScanModule::GetNumberOfEnergies()
        *   - SDICOS::GeneralScanModule::HasNumberOfEnergies()
        *   - SDICOS::GeneralScanModule::DeleteNumberOfEnergies()
        * 
        * Previous API:
        *   - SDICOS::GeneralSeriesModule::SetSeriesNumberOfEnergies()
        *   - SDICOS::GeneralSeriesModule::GetSeriesNumberOfEnergies()
        *   - SDICOS::GeneralSeriesModule::HasSeriesNumberOfEnergies()
        *   - SDICOS::GeneralSeriesModule::DeleteSeriesNumberOfEnergies()
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
        *   enumNIST
        *
        * and replaced with the enumerations:
        *   enumNIST_FAT
        *   enumNIST_SAT
        *
        * A new enum has been included:
        *   enumGIQ
        */
        {
            SDICOS::GeneralSeriesModule::enumNIST_FAT;
            SDICOS::GeneralSeriesModule::enumNIST_SAT;
            SDICOS::GeneralSeriesModule::enumGIQ;
        }
    }

	/*
	* Frame of Reference
	*/
	{
		SDICOS::FrameOfReference& frameOfReference = moduleAPI.GetFrameOfReference();

		/*
		* Frame of Reference changes:
		* SDICOS::FrameOfReference::GetFrameOfReferenceUID now returns const SDICOS::DcsUniqueIdentifier instead of const DcsString&
		*/
		{
			// Previous:
			// const DcsString& SDICOS::FrameOfReference::GetFrameOfReferenceUID() const;
			// Updated:
			// const DcsUniqueIdentifier SDICOS::FrameOfReference::GetFrameOfReferenceUID() const;
			frameOfReference.GetFrameOfReferenceUID();
		}
	}

    return 0;
}

void ThreatSequenceUpdates()
{
    SDICOS::TDRModule moduleAPI;
    //Initialize moduleAPI with required values
    if(!InitTDR(moduleAPI))
        return;

    /*
     *  Updates to Threat Sequence
     */
    {
        SDICOS::TDRTypes::ThreatSequence &threatSequence = moduleAPI.GetThreatSequence();

        SDICOS::Array1D<SDICOS::TDRTypes::ThreatSequence::ThreatItem> &vThreatItems = threatSequence.GetPotentialThreatObject();

        /*
         *  Updates to Baggage Specific TDR
         */
        {
            SDICOS::TDRTypes::BaggageSpecificTDR &bstdr = vThreatItems[0].GetBaggageTDR();
            SDICOS::Array1D<SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem> &repSeqItems = bstdr.GetPTORepresentationSequenceItems();

            repSeqItems.SetSize(1);
            SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem myRepSeqItem = repSeqItems[0];

            /*
             *  Updates to PTO Representation Sequence Item
             */

            /* Mass of PTO in grams
             *
             * Moved from SDICOS::TDRTypes::BaggageSpecificTDR to SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem.
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetMass(const float fMass);
             *      - float GetMass() const;
             *      - bool HasMass() const;
             *      - void DeleteMass();
             */

            // Old Call:
            // bstdr.SetMass(1.0f);
            // New Call:
            myRepSeqItem.SetMass(1.0f);

            /* Density of PTO in grams/cc
             *
             * Moved from SDICOS::TDRTypes::BaggageSpecificTDR to SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetDensity(const float fDensity);
             *      - float GetDensity() const;
             *      - bool HasDensity() const;
             *      - void DeleteDensity();
             */

            // Old Call:
            // bstdr.SetDensity(1.0f);
            // New Call:
            myRepSeqItem.SetDensity(1.0f);

            /* Z Effective
             *
             * Moved from SDICOS::TDRTypes::BaggageSpecificTDR to SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetZEffective(const float fZEffective);
             *      - float GetZEffective() const;
             *      - bool HasZEffective() const;
             *      - void DeleteZEffective();
             */

            // Old Call:
            // bstdr.SetZeffective(1.0f);
            // New Call:
            myRepSeqItem.SetZEffective(1.0f);

            /* Volume of PTO
             *
             * Moved from SDICOS::TDRTypes::BaggageSpecificTDR to SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetVolume(const float fVolume);
             *      - float GetVolume() const;
             *      - bool HasVolume() const;
             *      - void DeleteVolume();
             */

            // Old Call:
            // bstdr.SetVolume(1.0f);
            // New Call:
            myRepSeqItem.SetVolume(1.0f);

            /* Rho
             *
             * Moved from SDICOS::TDRTypes::BaggageSpecificTDR to SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetRho(const float fVal);
             *      - float GetRho() const;
             *      - bool HasRho() const;
             *      - void DeleteRho();
             */

            // Old Call:
            // bstdr.SetRho(1.0f);
            // New Call:
            myRepSeqItem.SetRho(1.0f);

            /* Zeff Alternative
             *
             * Moved from SDICOS::TDRTypes::BaggageSpecificTDR to SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetZeffAlternative(const float fVal);
             *      - float GetZeffAlternative() const;
             *      - bool HasZeffAlternative() const;
             *      - void DeleteZeffAlternative();
             */

            // Old Call:
            // bstdr.SetZeffAlternative(1.0f);
            // New Call:
            myRepSeqItem.SetZeffAlternative(1.0f);
        }
    }

    /*
    *   Updates to AssessmentSequence
    */
    {
        /*
        *   Updates to Threat Category
        */
        {
	        SDICOS::TDRTypes::ThreatSequence &ts = moduleAPI.GetThreatSequence();
            SDICOS::TDRTypes::ThreatSequence::ThreatItem threatItem = ts.GetPotentialThreatObject()[0];

            /*
            *   DICOS V03 removed the following values from Threat Category.  Can use OTHER in their place
            *   3D PRINTED PI
            *   AMMUNITION PI
            *   BATTERIES PI
            *   BLUNTS PI
            *   EMERGING 1
            *   EMERGING 2
            *   EMERGING 3
            *   EMERGING 4
            *   GRENADE PI
            *   SHARPS PI
            *   WEAPONS PI
            */

            // Old Calls:
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enum3DPrintedThreat);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumAmmunition);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumBatteries);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumBlunts);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumEmergingThreat1);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumEmergingThreat2);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumEmergingThreat3);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumEmergingThreat4);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumGrenade);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumSharps);
            // threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumWeapons); 

            // New Call:
            threatItem.GetAssessment().GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumOther);
        }
    }
}

// Init attributes for use in examples
bool InitTDR(SDICOS::TDRModule &tdr)
{
    bool bRes(true);

	// Utility method for setting the current date
	SDICOS::DcsDate date;
	date.SetToday();
	
	// Utility method for setting the current time
	SDICOS::DcsTime time;
	time.SetNow();
	
	// The DateTime object is a specific DICOS Value Representation (VR) that contains date and time
	SDICOS::DcsDateTime dateTime;
	dateTime.Set(date,time);
	//
	// unique identifier for the CT instance referenced by threat items
	//
	SDICOS::DcsUniqueIdentifier ctInstanceUID("1.2.276.0.7230010.3.1.4.4126100761.8984.1407370732.881");
	//
	// The Threat Sequence class represents the Threat Sequence Module (Table 62)
	//
	SDICOS::TDRTypes::ThreatSequence &ts = tdr.GetThreatSequence();
	
	//
	// The ThreatSequence contains information about Potential Threat Objects (PTOs).
	// The ThreatSequence::ThreatItem class stores the information for a specific PTO.
	// The ThreatSequence contains one or more ThreatItems.
	//
	SDICOS::Array1D<SDICOS::TDRTypes::ThreatSequence::ThreatItem>& threatObject = ts.GetPotentialThreatObject();
	
	// for this example there is 1 threats
	threatObject.SetSize(1);

	// Indicate that Item 0 is a piece of baggage
	threatObject[0].EnableBaggageTDR(true);
	bRes = bRes && threatObject[0].SetID(0);
	
	//
	// The AssessmentSequence class contains one or more threat assessments for this threat object
	// The Assessment Sequence is implemented as an array of AssessmentItem objects
	// In this example, two threat assessments are provided for a explosive precursor
	//
	SDICOS::TDRTypes::AssessmentSequence& objectAssessmentSequence = threatObject[0].GetAssessment();
	bRes = bRes && objectAssessmentSequence.GetAssessment().SetSize(2);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumExplosive);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetAbilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[0].SetAssessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetThreatCategory(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumOther);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetAbilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference);
	bRes = bRes && objectAssessmentSequence.GetAssessment()[1].SetAssessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumThreat);

	// Set baggage specific attributes
	{
		// The BaggageSpecificTDR object stores information specific to baggage threats
		SDICOS::TDRTypes::BaggageSpecificTDR& baggageTDR = threatObject[0].GetBaggageTDR();
		// One representation for the PTO (Single-Energy CT). 
		// Each representation can signify information for another view or energy level.
		baggageTDR.GetPTORepresentationSequenceItems().SetSize(1);
		SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem& seqItem = baggageTDR.GetPTORepresentationSequenceItems()[0];

		bRes = bRes && seqItem.SetMass(1321.2283935546875f);
		bRes = bRes && seqItem.SetDensity(1.0f);

		// Indicate the original scan or scans associated with this TDR.
		SDICOS::Array1D<SDICOS::SopInstanceReference> & referencedInstanceSequence = baggageTDR.GetPTORepresentationSequenceItems()[0].GetReferencedInstance();
		bRes = bRes && referencedInstanceSequence.SetSize(1);
		bRes = bRes && referencedInstanceSequence[0].SetClassUID(SDICOS::SOPClassUID::GetCT());
		bRes = bRes && referencedInstanceSequence[0].SetInstanceUID(ctInstanceUID);

		// Indicate the geometry of the threat Region Of Interest
		SDICOS::TDRTypes::CommonSpecificTDR::ThreatROI& threatRegionOfInterest = baggageTDR.GetPTORepresentationSequenceItems()[0].GetThreatROI();
		bRes = bRes && threatRegionOfInterest.SetThreatRoiBase(101.0f, 141.0f, 57.0f);
		bRes = bRes && threatRegionOfInterest.SetThreatRoiExtents(54.0f, 63.0f, 104.0f);
		bRes = bRes && threatRegionOfInterest.GetThreatRoiBitmap().SetDims(54, 63, 104);
	}

	// Set the Processing time for Item 0
	bRes = bRes && threatObject[0].SetProcessingStartTime(dateTime);
	bRes = bRes && threatObject[0].SetProcessingEndTime(dateTime);
	// Total Processing time is in milliseconds
	bRes = bRes && threatObject[0].SetTotalProcessingTime(0.0f);

    return bRes;
}

int main()
{
    // Updates common to all modalities
    CommonModuleUpdates();
    // Changed functionality within TDR Module
    ThreatSequenceUpdates();

    return 0;
}
