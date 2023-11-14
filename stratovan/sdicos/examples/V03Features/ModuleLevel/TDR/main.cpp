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

void NewBaseClassTags()
{
    SDICOS::TDRModule tdr;

    //OOI Owner Module
    {
        tdr.AllocateObjectOfInspectionOwner();
        SDICOS::ObjectOfInspectionOwnerModule* pOOIOwner = tdr.GetObjectOfInspectionOwner();

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
}
///End NewBaseClassTags

void ThreatSequenceFeatures()
{
	SDICOS::TDRModule moduleAPI;

    /*
     *  Additions to Threat Sequence
     */
    {
        SDICOS::TDRTypes::ThreatSequence& threatSequence = moduleAPI.GetThreatSequence();

        SDICOS::Array1D<SDICOS::TDRTypes::ThreatSequence::ThreatItem>& vThreatItems = threatSequence.GetPotentialThreatObject();
        vThreatItems.SetSize(1);

        /*
        * Additions to Threat Sequence Items
        */
        {
            SDICOS::TDRTypes::ThreatSequence::ThreatItem& threatItem = vThreatItems[0];

            /*
            * Signal Generation Software Versions : Tag (0060, 7008) VM = 1 or more, VR = LO [optional]
            * Defines version of software that converts original sensor data and transforms data for presentation or analysis.
            * For 3D imaging devices this is the reconstruction software version used to generate the display 
            * image from the raw detector dataand for 2D screening devices it is the transformation software/algorithm.
            */
            {
                //Add a version
                threatItem.AddSignalGenerationSoftwareVersion("Version 41");

                //Get a reference to the array of software versions
                SDICOS::Array1D<SDICOS::DcsLongString>& vstrVersions = threatItem.GetSignalGenerationSoftwareVersion();

                //Check if Signal Generation Software Versions is present
                bool bIsPresent = threatItem.HasSignalGenerationSoftwareVersion();

                //Delete Signal Generation Software Versions
                threatItem.DeleteSignalGenerationSoftwareVersions();
            }

            /*
            * Dynamic Screening Flag : Tag (0060, 7010) VR = CS [optional]
            * Defines the inspection mode. 
            * Dynamic screening is an adaptive Risk Based Screening (RBS) security screening capability
            * that provides personalized screening by adjusting screening parameters based on what is known about
            * each passenger on the day of travel.It enables dynamic switching of automated detection algorithms for
            * the screening of passengersand their belongings(including accessible property and checked baggage)
            * based on passenger risk designations in a real-time fashion.
            * 
            * Valid terms for Dynamic Screening Flag:
            *   BHS
            *   STIP
            *   OTHER
            *   NONE
            */
            {
                //Set the Dynamic Screening Flag
                threatItem.SetDynamicScreeningFlag(SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumBHS);
                threatItem.SetDynamicScreeningFlag(SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumSTIP);
                threatItem.SetDynamicScreeningFlag(SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumOther);
                threatItem.SetDynamicScreeningFlag(SDICOS::TDRTypes::ThreatSequence::ThreatItem::enumNone);

                //Get the Dynamic Screening Flag as an enum
                SDICOS::TDRTypes::ThreatSequence::ThreatItem::DYNAMIC_SCREENING_FLAG nFlag = threatItem.GetDynamicScreeningFlagEnum();

                //Get the Dynamic Screening Flag as a string
                SDICOS::DcsString strDSF = threatItem.GetDynamicScreeningFlagString();

                //Check if the Dynamic Screening Flag is present
                bool bIsPresent = threatItem.HasDynamicScreeningFlag();

                //Delete the Dynamic Screening Flag
                threatItem.DeleteDynamicScreeningFlag();
            }
        }

        /*
         *  Additions to Baggage Specific TDR
         */
        {
            SDICOS::TDRTypes::BaggageSpecificTDR& bstdr = vThreatItems[0].GetBaggageTDR();
            SDICOS::Array1D<SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem>& vRepSeqItems = bstdr.GetPTORepresentationSequenceItems();
            vRepSeqItems.SetSize(1);
            SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem& ptoRep = vRepSeqItems[0];

            /*
             *  Additions to PTO Representation Sequence Item
             */

            /* BoundingBoxResolution : Tag (4010, 1147) VR = CS [optional]
             *
             * Specifies how multiple bounding boxes on the same PTO were resolved into one bounding box
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetBoundingBoxResolution(const BOUNDING_BOX_RESOLUTION enumBoundingBox);
             *      - BOUNDING_BOX_RESOLUTION GetBoundingBoxResolution() const;
             *      - DcsString GetBoundingBoxResolutionAsString() const;
             *      - bool HasBoundingBoxResolution() const;
             *      - void DeleteBoundingBoxResolution();
             *
             * Valid Values:
             */
            // Specifies method used summed the bounding boxes together
            ptoRep.SetBoundingBoxResolution(SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumBBR_Summation);
            // Specifies method used the largest bounding box
            ptoRep.SetBoundingBoxResolution(SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumBBR_LargestBoundingBox);
            // Specifies method used the box with the highest assessment probability
            ptoRep.SetBoundingBoxResolution(SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumBBR_HighestAssessmentProbability);
            // Specifies method used was none of the methods above
            // Attribute Aggregate Method for Bounding Box is required and specifies further description
            ptoRep.SetBoundingBoxResolution(SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumBBR_Other);

            /* Aggregated Method for Bounding Box: Tag (4010, 1149) VR = LT [Required if Bounding Box Resolution (4010, 1147) is OTHER]
             *
             * Provides a larger description for uncommon Bounding Box Resolution methods
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetAggregatedMethodForBoundingBox(const DcsLongText& strDescription);
             *      - DcsLongText GetAggregatedMethodForBoundingBox() const;
             *      - bool HasAggregatedMethodForBoundingBox() const;
             *      - void DeleteAggregatedMethodForBoundingBox();
             *
             */

            /* ROI Resolution: Tag (4010, 1247) VR = CS [Required if Bounding Box Resolution (4010, 1147) is set]
             *
             * Specifies how multiple regions of interest on the same PTO were resolved into one region of interest
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetROIResolution(const ROI_RESOLUTION enumROIResolution);
             *      - ROI_RESOLUTION GetROIResolution() const;
             *      - DcsString GetROIResolutionAsString() const;
             *      - bool HasROIResolution() const;
             *      - void DeleteROIResolution();
             *
             * Valid Values:
             */
            // Specifies method used summed the regions of interest together
            ptoRep.SetROIResolution(SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumROI_Summation);
            // Specifies method used the largest region of interest
            ptoRep.SetROIResolution(SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumROI_LargestBoundingBox);
            // Specifies method used the region of interest with the highest assessment probability
            ptoRep.SetROIResolution(SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumROI_HighestAssessmentProbability);
            // Specifies method used was none of the methods above
            // Attribute Aggregate Method Of ROI Resolution is required and specifies further description
            ptoRep.SetROIResolution(SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem::enumROI_Other);

            /* Aggregated Method of ROI Resolution: Tag (4010, 1249) VR = LT [Required if Bounding Box Resolution (4010, 1147) is OTHER]
             *
             * Provides a larger description for uncommon ROI Resolution methods
             *
             * See within SDICOS::TDRTypes::BaggageSpecificTDR::PTORepresentationSequenceItem:
             *      - bool SetAggregatedMethodOfROIResolution(const DcsLongText& strDescription);
             *      - DcsLongText GetAggregatedMethodOfROIResolution() const;
             *      - bool HasAggregatedMethodOfROIResolution() const;
             *      - void DeleteAggregatedMethodOfROIResolution();
             *
             */
            ptoRep.SetAggregatedMethodOfROIResolution("Description");
        }
    }
}

void AdditionalInspectionSelectionCriteriaFeatures()
{
    SDICOS::TDRModule moduleAPI;

    /*
     *  Additions to Additional Inspection Selection Criteria
     */
    {
        SDICOS::TDRTypes::AdditionalInspectionSelectionCriteria additionalCriteria = moduleAPI.GetAdditionalInspectionSelectionCriteria();

        /*  Additional Inspection Selection Criteria : Tag (4010, 106E) VR = CS [Required if Additional Screening is Performed (4010, 106D) is YES]
         *
         *  Pre-existing values:
         *       - RANDOM
         *       - BEHAVIORAL
         *       - ALL
         *  Newly added values:
         *       - OWNER_RISK
         *       - FLIGHT_RISK
         *       - THREAT_LEVEL
         */
        additionalCriteria.GetAdditionalInspectionSelectionCriteria();
        SDICOS::TDRTypes::AdditionalInspectionSelectionCriteria::enumOwnerRisk;
        SDICOS::TDRTypes::AdditionalInspectionSelectionCriteria::enumFlightRisk;
        SDICOS::TDRTypes::AdditionalInspectionSelectionCriteria::enumThreatLevel;
    }
}

int main()
{
	// New functions for setting SOP Common values
	NewBaseClassTags();

	// New functionality within Module TDR
	ThreatSequenceFeatures();

    // New Enum Values for Additional Inspection Selection Criteria
    AdditionalInspectionSelectionCriteriaFeatures();

	return 0;
}