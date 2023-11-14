//////////////////////////////////////////////////////////////////////////////
/// Stratovan Corporation Copyright and Disclaimer Notice:
///
/// Copyright (c) 2014 Stratovan Corporation. All Rights Reserved.
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
#ifndef _STRATOVAN_DICOS_BAGGAGE_SPECIFIC_TDR_H_
#define _STRATOVAN_DICOS_BAGGAGE_SPECIFIC_TDR_H_

#include "SDICOS/CommonSpecificTDR.h"
#include "SDICOS/String.h"

namespace SDICOS
{
namespace TDRTypes
{

///
/// \class BaggageSpecificTDR
/// Represents Baggage-Specific TDR Details Macro
/// SPECREF V03 Section 12.5.1, Table 71
/// 
class BaggageSpecificTDR
{
public:
	/// Default Constructor
	BaggageSpecificTDR();
	
	/// Copy Constructor
	BaggageSpecificTDR(const BaggageSpecificTDR &btdr);
	
	/// Destructor
	virtual ~BaggageSpecificTDR();

	/// Release allocated resources
	virtual void FreeMemory();

	/// Assignment operator
	BaggageSpecificTDR& operator=(const BaggageSpecificTDR &btdr);
	
	/// Equality comparison operator
	bool operator==(const BaggageSpecificTDR &btdr) const;
	
	/// Inequality comparison operator
	bool operator!=(const BaggageSpecificTDR &btdr) const;

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false is returned if attributes were specified or if some were invalid.
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;


	///
	/// \class PTORepresentationSequenceItem
	/// Represents an item in PTO Representation Sequence
	/// 
	class PTORepresentationSequenceItem : public CommonSpecificTDR
	{
	public:
		/// Default Constructor
		PTORepresentationSequenceItem();

		/// Copy Constructor
		PTORepresentationSequenceItem(const PTORepresentationSequenceItem &item);

		/// Destructor
		virtual ~PTORepresentationSequenceItem();

		/// Release allocated resources
		virtual void FreeMemory();

		/// Assignment operator
		PTORepresentationSequenceItem& operator=(const PTORepresentationSequenceItem &item);

		/// Equality comparison operator
		bool operator==(const PTORepresentationSequenceItem &item) const;

		/// Inequality comparison operator
		bool operator!=(const PTORepresentationSequenceItem &item) const;

		/// Initialize the class attributes from the given AttributeManager
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not fetched
		///							or if some were invalid.
		virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Copy the attributes from the module into the given AttributeManager
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not uploaded.
		virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Attempt to set all required and optional attributes from the given AttributeManager
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false is returned if attributes were specified or if some were invalid.
		virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Determine if all needed attributes (required and conditionally required) are set
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Bounding box resolution enumerations
		/// @see SetBoundingBoxResolution
		typedef enum
		{
			enumBBR_Summation,						///< "SUMMATION"
			enumBBR_LargestBoundingBox,				///< "LARGEST BB"   /* BB = Bounding Box */
			enumBBR_HighestAssessmentProbability,	///< "HIGHEST AP"   /* AP = Assessment Probability */
			enumBBR_Other,							///< "OTHER"

			enumUnknownBoundingBoxResolution		///<				/* Represents an Unknown Bounding Box Resolution */
		} BOUNDING_BOX_RESOLUTION;

		/// ROI Resolution enumerations
		/// @see SetROIResolution
		typedef enum
		{
			enumROI_Summation,						///< "SUMMATION"
			enumROI_LargestBoundingBox,				///< "LARGEST BB"   /* BB = Bounding Box */
			enumROI_HighestAssessmentProbability,	///< "HIGHEST AP"   /* AP = Assessment Probability */
			enumROI_Other,							///< "OTHER"

			enumUnknownROIResolution				///<				/* Represents an Unknown ROI Resolution */
		} ROI_RESOLUTION;

		/// Bounding Box Resolution : Tag (4010, 1147) VR = CS [optional]
		/// Enumeration describing possible bounding box resolution methods to avoid multiple bounding boxes on the same PTO
		/// @param nBoundingBox Specifies which bounding box resolution method was used
		/// @return true/false false if unable to set a valid value
		bool SetBoundingBoxResolution(const BOUNDING_BOX_RESOLUTION nBoundingBox);

		/// @see SetBoundingBoxResolution
		/// @return returns enumUnknownBoundingBoxResolution if not set
		BOUNDING_BOX_RESOLUTION GetBoundingBoxResolution() const;

		/// @see SetBoundingBoxResolution
		/// @return returns empty string if not set
		DcsString GetBoundingBoxResolutionAsString() const;

		/// @return true if data is present
		bool HasBoundingBoxResolution() const;

		/// Delete bounding box enum so that it is not written to the DICOS file
		void DeleteBoundingBoxResolution();

		/// Aggregated Method For Bounding Box : Tag (4010, 1149) VR = LT
		/// [Required if the Bounding Box Resolution (4010, 1147) is set to OTHER]
		/// Text description on how the bounding box resolution was performed from the TDRs
		/// @param strDescription Describes the bounding box resolution method performed from the different TDRs
		/// @return true/false false if given empty string as input
		bool SetAggregatedMethodForBoundingBox(const DcsLongText& strDescription);

		/// @see SetAggregatedMethodForBoundingBox
		/// @return returns empty string if not accessible
		DcsLongText GetAggregatedMethodForBoundingBox() const;

		/// @return true if data is present
		bool HasAggregatedMethodForBoundingBox() const;

		/// Delete description so that it is not written to the DICOS file
		void DeleteAggregatedMethodForBoundingBox();

		/// ROI Resolution : Tag (4010, 1247) VR = CS
		/// [Required if the Bounding Box Resolution (4010, 1147) is present]
		/// Enumeration describing possible ROI resolution methods to avoid multiple ROIs on the same PTO
		/// @param nROIResolution Specifies which ROI resolution method was used
		/// @return true/false false if unable to set a valid value
		bool SetROIResolution(const ROI_RESOLUTION nROIResolution);

		/// @see SetROIResolution
		/// @return returns enumUnknownROIResolution if not set
		ROI_RESOLUTION GetROIResolution() const;

		/// @see SetROIResolution
		/// @return returns empty string if not set
		DcsString GetROIResolutionAsString() const;

		/// @return true if data is present
		bool HasROIResolution() const;

		/// Delete mass so that it is not written to the DICOS file
		void DeleteROIResolution();

		/// Aggregated Method of ROI Resolution : Tag (4010, 1249) VR = LT
		/// [Required if the ROI Resolution (4010, 1247) is set to OTHER]
		/// Text description on how the ROI resolution was performed from the TDRs
		/// @param strDescription Describes the bounding box resolution method performed from the different TDRs
		/// @return true/false false if input is the empty string
		bool SetAggregatedMethodOfROIResolution(const DcsLongText& strDescription);

		/// @see SetAggregatedMethodOfROIResolution
		/// @return returns the empty string if not set
		DcsLongText GetAggregatedMethodOfROIResolution() const;

		/// @return true if data is present
		bool HasAggregatedMethodOfROIResolution() const;

		/// Delete description so that it is not written to the DICOS file
		void DeleteAggregatedMethodOfROIResolution();

		/// Set Center of Mass : Tag (4010, 101B)
		///	a) Param 1-3, Center of PTO : Tag (4010. 101B), VR = FL [optional]
		///		i) Values stored sequentially as XYZ
		///		ii) Values in image space (i.e. Z indicates frame number)
		///		iii) 2D images: Z = 0
		///	@param fX	Center of Mass X
		///	@param fY	Center of Mass Y
		///	@param fZ	Center of Mass Z
		/// @return true/false
		bool SetCenterOfMass(const float fX, const float fY, const float fZ);
	
		/// @see SetCenterOfMass
		bool GetCenterOfMass(float &fX, float &fY, float &fZ) const;

		/// Returns true if data is set
		bool HasCenterOfMass() const;
	
		/// Delete Center of Mass so that it is not saved to the DICOS file
		void DeleteCenterOfMass();

		/// Mass of PTO in grams : Tag (4010, 1017) VR = FL
		/// [Required if the Modality (0008, 0060) of the Referenced Instance Sequence (0008, 114A) object in
		/// the "PTO Representation Sequence" (4010, 1037) is "CT" and "TDR Type" is "MACHINE"]
		/// @return true/false false if fMass < 0.0f
		bool SetMass(const float fMass);

		/// @see SetMass
		/// @return returns 0.0f if not set
		float GetMass() const;

		/// Returns true if data is present
		bool HasMass() const;

		/// Delete mass so that it is not written to the DICOS file
		void DeleteMass();

		/// Density of PTO in grams/cc : Tag (4010, 1018), VR = FL
		/// [Required if the Modality (0008, 0060) of the Referenced Instance Sequence (0008, 114A) object in
		/// the "PTO Representation Sequence" (4010, 1037) is "CT" and "TDR Type" is "MACHINE"]
		/// @return true/false false if density < 0.0f
		bool SetDensity(const float fDensity);

		/// @see SetDensity
		/// @return returns 0.0f if not set
		float GetDensity() const;

		/// Returns true if data is present
		bool HasDensity() const;

		/// Delete density so that it is not saved to the DICOS file
		void DeleteDensity();

		/// Set Z Effective : Tag (4010, 1019)
		///	@param fZEffective Z Effective : Tag (4010, 1019), VR = FL [optional]
		/// @return true/false
		bool SetZEffective(const float fZEffective);

		/// @see SetZEffective
		float GetZEffective() const;

		/// Returns true if data is present
		bool HasZEffective() const;

		/// Delete ZEffective so that it is not written to the DICOS file
		void DeleteZEffective();

		/// Set Volume of PTO : Tag (4010, 1023)
		///	@param fVolume Volume of PTO in cc : Tag (4010, 1023), VR = FL [optional]
		/// @return true/false
		bool SetVolume(const float fVolume);

		/// @see SetVolume
		float GetVolume() const;

		/// Returns true if data is present
		bool HasVolume() const;

		/// Delete volume so that it is not written to the DICOS file
		void DeleteVolume();

		/// Set Rho : Tag (6000, 8000), VR = FL [optional]
		/// The electron density per unit volume [Mole of electrons per cm^3]
		/// @return true/false
		bool SetRho(const float fVal);

		/// @see SetRho
		float GetRho() const;

		/// Returns true if data is present
		bool HasRho() const;

		/// Delete data
		void DeleteRho();

		/// Set Zeff Alternative : Tag (6000, 8002), VR = FL [optional]
		/// An alternative to Z Effective, Zeff is based on the calculated x-ray
		/// properties of a compound. Zeff is designed to closely match the actual
		/// x-ray absorption of each material over the spectral region of interest.
		/// Zeff removes the arbitrariness and lack of optimization entailed in using Z Effective
		/// @return true/false
		bool SetZeffAlternative(const float fVal);

		/// @see SetZeffAlternative
		float GetZeffAlternative() const;

		/// Returns true if data is present
		bool HasZeffAlternative() const;

		/// Delete data
		void DeleteZeffAlternative();

	private:
		class SequenceItemImpl;
		SequenceItemImpl *m_pSequenceItemImpl;
	};

	/// Returns PTO Representation Sequence items : Tag (4010, 1037), VR = SQ, VM = 1...n [Required if TDR Type is MACHINE]
	Array1D<PTORepresentationSequenceItem>& GetPTORepresentationSequenceItems();
	/// Returns PTO Representation Sequence items : Tag (4010, 1037), VR = SQ, VM = 1...n [Required if TDR Type is MACHINE]
	const Array1D<PTORepresentationSequenceItem>& GetPTORepresentationSequenceItems() const;
	/// Delete all items
	void DeletePTORepresentationSequenceItems();


protected:
	class ImplBaggageSpecificTDR;
	ImplBaggageSpecificTDR	*m_pImplBaggageSpecificTDR; ///< Internal implementation
	
	ImplBaggageSpecificTDR* GetImpl();
	const ImplBaggageSpecificTDR* GetImpl()const;
};

}//namespace TDRTypes
}//namespace SDICOS

#endif
