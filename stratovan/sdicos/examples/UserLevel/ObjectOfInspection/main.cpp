//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2015 Stratovan Corporation. All Rights Reserved.
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
#include "SDICOS/DICOS.h"	//DICOS include header

bool CreateWithObjectOfInspection();

int main()
{
	bool bRes = CreateWithObjectOfInspection();
	if(bRes)
		std::cout << "ObjectOfInspectionExample completed successfully set attributes" << std::endl;
	else
		std::cout << "ObjectOfInspectionExample failed to set all attributes" << std::endl;

	return (bRes ? 0 : 1);
}

/**
 * CreateWithObjectOfInspection shows how to use the Object of Inspection(OOI) API methods in IODCommon
 * to create a CT DICOS file with OOI information.
 * 
 * In this example all OOI attributes are set and optional attributes are indicated as such.
 */
bool CreateWithObjectOfInspection()
{
    bool bRes(true); // API methods return true/false to indicate success

    /// Create a CT Series for a cargo Object of Inspection (OOI)
    /// For more details on using the User-Level API object SDICOS::CT see 
    /// the CTExample and UserCTExample
    SDICOS::CT ct(
            SDICOS::ObjectOfInspectionModule::enumTypeCargo,
            SDICOS::CTTypes::CTImage::enumHighEnergy
    );

    /// Acquisition time in seconds
    ct.SetImageAcquisitionDuration(5.2);

    /// Add one section of volume data to the CT Series
    ///		Row and Column orientation vectors are (1,0,0) and (0,1,0)
    ///		CT Frame Type Pixel Data Characteristics value is set to ORIGINAL
    ///		CT Filter Type is set to NONE. CT Filter Material is not used.
    SDICOS::Section * pSection = ct.AddSection();
    pSection->GetPixelData().Allocate(SDICOS::Volume::enumUnsigned16Bit,128,64,100);

    pSection->SetFocalSpotSizeInMM(1.414f);			/// Used nominal size of the focal spot in MM.
    pSection->SetKVP(3.14f);							
    pSection->SetPositionInMM(10.0f, 20.0f, 15.0f);	/// Volume data location in MM
    pSection->SetSpacingInMM(1.0f, 2.0f, 10.0f);		/// Column spacing, row spacing and slice spacing.

    //	Clear the Volume data for the CT Series section
    SDICOS::Volume& volume = pSection->GetPixelData();
    volume.GetUnsigned16()->Zero(0xbeef);

    // Set object of inspection attributes available through the IODCommon base class

    // String identifier for the Object of Inspection
    SDICOS::DcsLongString OOIId("123-345-eager-34t342-avf32");
    bRes = ct.SetOOIID(OOIId) && bRes;
    
    // Name of system that created the OOIId
    SDICOS::DcsLongString OOIIdAssigningAuthority("Checkpoint Inspection Handler");
    bRes = ct.SetOOIIDAssigningAuthority((OOIIdAssigningAuthority)) && bRes;
    
    // What kind of id is being used
    bRes = ct.SetOOIIDType(SDICOS::ObjectOfInspectionModule::IdInfo::enumBarcode) && bRes;
    
    // OOI Type is set in the constructor, but can also be set through the API
    bRes = ct.SetOOIType(SDICOS::ObjectOfInspectionModule::enumTypeBioSample) && bRes;
    
    // For an OOIType SDICOS::ObjectofInspectionModule::enumPerson, gender is required
    // bRes = ct.SetGender(SDICOS::ObjectOfInspectionModule::enumGenderFemale) && bRes;
    
    // Optional Attribute: mass of object in grams must be > 0.
    bRes = !ct.SetOOIMassInGrams(-1) && bRes;
    bRes = ct.SetOOIMassInGrams(2200) && bRes;
    
    // Optional Attribute: Multiple OOI Identifiers can be used to identify the same object
    bRes = ct.AddAlternativeOOIId(
		"Alternative OOIId",
		"Alternative OOIId Issuer",
		SDICOS::ObjectOfInspectionModule::IdInfo::enumText
     ) && bRes;
    
	bRes = ct.AddAlternativeOOIId(
		"Alternative OOIId 1",
		"Alternative OOIId Issuer",
		SDICOS::ObjectOfInspectionModule::IdInfo::enumRFID
     ) && bRes;
				 
	// An alternative ID can be removed
	ct.DeleteAlternativeOOIId("Alternative OOIId");
	
    // Optional Attribute: The algorithm routing code is used to identify the threat detection algorithm
	// that should be used to inspect this OOI. Specific types of OOI can require special handling
	bRes = ct.SetAlgorithmRoutingCode("ALG_CODE", "ALG_SCHEME", "Algorithm Description") && bRes;
    
	// The Algorithm routing code can be removed
	ct.DeleteAlgorithmRoutingCode();
	
	// Optional Attribute: OOI Type Description is a longer, human-readable description
	bRes = ct.SetOOITypeDescriptor("Human readable description of OOI") && bRes;
		
	// The Type Descriptor can be removed
	ct.DeleteOOITypeDescriptor();
		
	// Optional Attribute: Dimensions of OOI in meters. Values my be > 0
	bRes = !ct.SetOOISizeInMeters(1.2f,0.3f,-1.0f) && bRes;
	bRes = ct.SetOOISizeInMeters(1.2f,0.2f,0.75f) && bRes;
		
	// Dimensions can be removed
	ct.DeleteOOISize();
		
    return bRes;
}
