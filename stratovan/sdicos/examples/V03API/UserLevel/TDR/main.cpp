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

void ParentClassChanges()
{
	SDICOS::TDR tdr;

	/*
	* Updates to IODCommon parent class
	*/
	{
		SDICOS::IODCommon& iodcommon = tdr;

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
	* Frame of Reference
	*/
	{
		/*
		*
		* Frame of Reference attributes now are inherited from SDICOS::FrameOfReferenceUser instead of being direct members of SDICOS::TDR
		*
		* SDICOS::FrameOfReferenceUser::GetFrameOfReferenceUID now returns const SDICOS::DcsUniqueIdentifier instead of const DcsString&
		*/
		{
			// Previous:
			// const DcsString& SDICOS::TDR::GetFrameOfReferenceUID() const;
			// Updated:
			// const DcsUniqueIdentifier SDICOS::FrameOfReferenceUser::GetFrameOfReferenceUID() const;
			tdr.GetFrameOfReferenceUID();
		}
	}
}

void BaggageAPIUpdates()
{
	SDICOS::TDR tdr;
    
	tdr.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBaggage);
	tdr.SetTDRType(SDICOS::TDRTypes::ThreatDetectionReport::enumMachine);

	SDICOS::S_UINT16 nBaggagePTOIdentifier(6357);

    /*
     *  Updates to TDR
     */
	SDICOS::IODCommon::enumXRAY;
    
    /*  Each of the following functions has had a new parameter added to their function signature.
     *  The data each of these functions accesses has moved to within BaggageSpecificTDR's PTORepresentationSequence;
     *  the index for which item in the sequence is now required to access the specific item to read/write values to.
	 *  This index does NOT have a default value. Instances of nRepresentation within function signatures in UserTDR.h
	 *  or SDICOS::TDR's members will no longer default to 0.
     *
     *  /// Set details specific to a Baggage Threat Detection Report
	 *  /// The Object Of Inspection (OOI) Type must be set to enumBaggage and the PTO ThreatType set to enumThreatTypeBaggage.
	 *  /// See SDICOS::IODCommon::SetOOIType() in SdcsTemplateBase.h.
	 *  bool SetBaggagePTODetails(const S_UINT16 PTOIdentifier, const float PTOMassInGrams, const float PTODensityInGramsPerCC, const S_UINT16 nRepresentation);
	 *  bool GetBaggagePTODetails(const S_UINT16 PTOIdentifier, float& PTOMass, float& PTODensity, const S_UINT16 nRepresentation) const;
     *
	 *  /// The PTO's Mass in grams
	 *  bool SetBaggagePTOMassInGrams(const S_UINT16 PTOIdentifier, const float fMassInGrams, const S_UINT16 nRepresentation);
	 *  float GetBaggagePTOMassInGrams(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool HasBaggagePTOMassInGrams(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool DeleteBaggagePTOMassInGrams(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
     *
	 *  /// The PTO's Density in grams CC
	 *  bool SetBaggagePTODensityInGramsPerCC(const S_UINT16 PTOIdentifier, const float fDensityInGramsPerCC, const S_UINT16 nRepresentation);
	 *  float GetBaggagePTODensityInGramsPerCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool HasBaggagePTODensityInGramsPerCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool DeleteBaggagePTODensityInGramsPerCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
     *
	 *  /// The PTO's volume in CC's
	 *  bool SetBaggagePTOVolumeInCC(const S_UINT16 PTOIdentifier, const float fVolumeInCC, const S_UINT16 nRepresentation);
	 *  float GetBaggagePTOVolumeInCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool HasBaggagePTOVolumeInCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool DeleteBaggagePTOVolumeInCC(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
     *
	 *  /// Set the Z-effective value for a baggage PTO
	 *  bool SetBaggageZeffective(const S_UINT16 PTOIdentifier, const float fZeffective, const S_UINT16 nRepresentation);
	 *  bool GetBaggageZeffective(const S_UINT16 PTOIdentifier, float &fZeffective, const S_UINT16 nRepresentation)const;
	 *  bool HasBaggageZeffective(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool DeleteBaggageZeffective(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
     *
	 *  /// An alternative to Z Effective, Zeff is based on the calculated x-ray 
	 *  /// properties of a compound. Zeff is designed to closely match the actual 
	 *  /// x-ray absorption of each material over the spectral region of interest. 
	 *  /// Zeff removes the arbitrariness and lack of optimization entailed in using Z Effective
	 *  bool SetBaggageZeffAlternative(const S_UINT16 PTOIdentifier, const float fVal, const S_UINT16 nRepresentation);
	 *  float GetBaggageZeffAlternative(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool HasBaggageZeffAlternative(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool DeleteBaggageZeffAlternative(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
     *
	 *  /// The electron density per unit volume [Mole of electrons per cm^3]
	 *  bool SetBaggageRho(const S_UINT16 PTOIdentifier, const float fVal, const S_UINT16 nRepresentation);
	 *  float GetBaggageRho(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool HasBaggageRho(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool DeleteBaggageRho(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
     */
    // Old Call:
    // tdr.SetBaggageRho(nBaggagePTOIdentifier, 1.0f);
    // New Call:
    tdr.SetBaggageRho(nBaggagePTOIdentifier, 1.0f, 0);

	/*  Each of the following functions no longer uses 0 as a default value for the parameter nRepresentation.
	 *  This index must be specified explicitly in all functions which take this as a parameter now. Providing
	 *  a 0 as the parameter has the same effect as the previous default parameter.
	 *
	 *	bool SetThreatBoundingPolygon(const S_UINT16 PTOIdentifier, const BoundingPolygon& controlPoints, const S_UINT16 nRepresentation);
	 *	bool GetThreatBoundingPolygon(const S_UINT16 PTOIdentifier, BoundingPolygon& controlPoints, const S_UINT16 nRepresentation)const;
	 *
	 *	bool AddReferencedInstance(const S_UINT16 PTOIdentifier,
	 *		const DcsUniqueIdentifier& referencedSopClassUID,
	 *		const DcsUniqueIdentifier& referencedSopInstanceUID,
	 *		const S_UINT16 nRepresentation);
	 *	bool GetReferencedInstances(const S_UINT16 PTOIdentifier,
	 *		Array1D<SDICOS::SopInstanceReference>& referencedInstances,
	 *		const S_UINT16 nRepresentation) const;
	 *
	 *  bool SetBaggagePTOLocationDescription(const S_UINT16 PTOIdentifier, const DcsShortText &dsDescription, const S_UINT16 nRepresentation);
	 *  DcsString GetBaggagePTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool HasBaggagePTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *  bool DeleteBaggagePTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
	 * 
	 * 	bool SetPersonPTOLocationDescription(const S_UINT16 PTOIdentifier, const DcsShortText& PTOLocation, const S_UINT16 nRepresentation);
	 *	bool GetPersonPTOLocationDescription(const S_UINT16 PTOIdentifier, DcsShortText& PTOLocation, const S_UINT16 nRepresentation) const;
	 *	DcsString GetPersonPTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation) const;
	 *	bool HasPersonPTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *	bool DeletePersonPTOLocationDescription(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
	 *
	 *	bool SetPersonPTOCenter(const S_UINT16 PTOIdentifier, const Point3D<float>& ptCenter, const S_UINT16 nRepresentation);
	 *	Point3D<float> GetPersonPTOCenter(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *	bool HasPersonPTOCenter(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *	bool DeletePersonPTOCenter(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
	 *
	 *	bool SetPersonPTODetails(
	 *		const S_UINT16 PTOIdentifier,
	 *		const DcsShortText& PTOLocation,
	 *		const Point3D<float>& PTOCenter, 
	 *		const S_UINT16 nRepresentation
	 *	);
	 *	bool GetPersonPTODetails(const S_UINT16 PTOIdentifier,
	 *		DcsShortText& PTOLocation,
	 *		Point3D<float>& PTOCenter,
	 *		const S_UINT16 nRepresentation) const;
	 *
	 *	bool AddPersonAnomalyIndicator(const S_UINT16 PTOIdentifier, const Point3D<float>& anomalyLocation, const S_UINT16 nRepresentation);
	 *	bool AddPersonAnomalyIndicator(const S_UINT16 PTOIdentifier, const Point3DArray& anomalyLocations, const S_UINT16 nRepresentation);
	 *	bool GetPersonAnomalyIndicators(const S_UINT16 PTOIdentifier, Point3DArray& anomalyLocations, const S_UINT16 nRepresentation) const;
	 *	bool HasPersonAnomalyIndicators(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *	bool DeletePersonAnomalyIndicators(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
	 *
	 *	bool SetPersonPTORegionSequence(const S_UINT16 PTOIdentifier, const Array1D<AitBodyZones> &vAitBodyZones, const S_UINT16 nRepresentation);
	 *	bool GetPersonPTORegionSequence(const S_UINT16 PTOIdentifier, Array1D<AitBodyZones> &vAitBodyZones, const S_UINT16 nRepresentation) const;
	 *	bool HasPersonPTORegionSequence(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation)const;
	 *	bool DeletePersonPTORegionSequence(const S_UINT16 PTOIdentifier, const S_UINT16 nRepresentation);
	 */
    // Old Call:
	// These took the form of tdr.MemberFunction(PTOIdentifer, value, OPTIONAL_INDEX)
	// tdr.SetBaggagePTOLocationDescription(nBaggagePTOIdentifier, "description");
    // New Call:
	// These take the form of tdr.MemberFunction(PTOIdentifier, value, REQUIRED_INDEX)
	tdr.SetBaggagePTOLocationDescription(nBaggagePTOIdentifier, "description", 0);

	/*  The SetThreatRegionOfInterest function no longer uses any default values, meaning the parameters
	 *  ptoMask and nRepresentation no longer have default values.
	 *  The old default value for ptoMask was SDICOS::Bitmap(), which indicated the entire region
	 *  is defined as the PTO, can be passed in as a parameter to achieve the same result. 
	 *  nRepresentation used to default to index value 0, which can be passed in as a parameter to 
	 *  achieve the same result.
	 *
	 *	bool SetThreatRegionOfInterest(
	 *		const S_UINT16 PTOIdentifier,
	 *		const Point3D<float>& ptoBase,
	 *		const Point3D<float>& ptoExtents,
	 *		const Bitmap& ptoMask,
	 *		const S_UINT16 nRepresentation
	 *	);
	 *	bool GetThreatRegionOfInterest(const S_UINT16 PTOIdentifier,
	 *		Point3D<float>& PTOBase,
	 *		Point3D<float>& PTOExtents,
	 *		Bitmap& bitmap,
	 *		const S_UINT16 nRepresentation
	 *	) const;
	 */
    // Old Call:
	// tdr.SetThreatRegionOfInterest(nBaggagePTOIdentifier, SDICOS::Point3D<float>(10.0f, 10.0f, 10.0f), SDICOS::Point3D<float>(10.0f, 10.0f, 10.0f));
    // New Call:
	tdr.SetThreatRegionOfInterest(nBaggagePTOIdentifier, SDICOS::Point3D<float>(10.0f, 10.0f, 10.0f), SDICOS::Point3D<float>(10.0f, 10.0f, 10.0f), SDICOS::Bitmap(), 0);
}

void AssessmentUpdates()
{
	SDICOS::TDR tdr;

	/*
	*	Threat Category Updates
	*/
	{
		SDICOS::S_UINT16 PTOIdentifier(1234);
		SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::ASSESSMENT_FLAG assessmentFlag(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoThreat);
		SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::ABILITY_ASSESSMENT abilityAssessment(SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumNoInterference);
		SDICOS::DcsLongText threatDescription("Threat Description");
		float assessmentProbability(-1.0f);
	
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

		//Old Calls:
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enum3DPrintedThreat, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumAmmunition, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumBatteries, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumBlunts, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumEmergingThreat1, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumEmergingThreat2, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumEmergingThreat3, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumEmergingThreat4, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumGrenade, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumSharps, abilityAssessment, threatDescription, assessmentProbability);
		// tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumWeapons, abilityAssessment, threatDescription, assessmentProbability);

		//New Call:
		tdr.SetPTOAssessment(PTOIdentifier, assessmentFlag, SDICOS::TDRTypes::AssessmentSequence::AssessmentItem::enumOther, abilityAssessment, threatDescription, assessmentProbability);
	}
}

int main()
{
	//Changes common to many modalities
	ParentClassChanges();

	//New functionality within User TDR
	BaggageAPIUpdates();

	//Updates to Assessment functionality within User TDR
	AssessmentUpdates();

	return 0;
}