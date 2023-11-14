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
#ifndef _STRATOVAN_DICOS_CT_XRAY_DETAILS_H_
#define _STRATOVAN_DICOS_CT_XRAY_DETAILS_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

namespace CTTypes
{

///
/// \class CTXRayDetails
/// \brief Implements CT X-Ray Details Sequence Macro, a required single item sequence (0018, 9325)
/// SPECREF V03 Section 7.4.3.2, Table 23
///
class CTXRayDetails
{
public:
	/// Constructor
	CTXRayDetails();
	/// Copy constructor
	CTXRayDetails(const CTXRayDetails &xrd);
	/// Destructor
	virtual ~CTXRayDetails();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	CTXRayDetails& operator=(const CTXRayDetails &xrd);
	/// Comparison operator
	bool operator==(const CTXRayDetails &xrd)const;
	/// Comparison operator
	bool operator!=(const CTXRayDetails &xrd)const;

	/// Filter Type enumerations
	typedef enum
	{
		enumUnknownFilterType, ///< Unknown enumeration

		enumWedge,		///< "WEDGE"
		enumButterfly,	///< "BUTTERFLY"
		enumMultiple,	///< "MULTIPLE"
		enumFlat,		///< "FLAT"
		enumShaped,		///< "SHAPED"
		enumNone,		///< "NONE"

	}FILTER_TYPE;

	/// Filter Material enumerations
	typedef enum
	{
		enumUnknownFilterMaterial, ///< Unknown enumeration

		enumMolybdenum,	///< "MOLYBDENUM"
		enumAluminum,	///< "ALUMINUM"
		enumCopper,		///< "COPPER"
		enumRhodium,	///< "RHODIUM"
		enumNiobium,	///< "NIOBIUM"
		enumEuropium,	///< "EUROPIUM"
		enumLead,		///< "LEAD"
		enumMixed,		///< "MIXED"

	}FILTER_MATERIAL;

	///
	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// KVP, Peak kilovoltage : Tag (0018, 0060), VR = DS [required if "Frame Type", tag (0008, 9007), is "ORIGINAL"]
	bool SetKVP(const float fKVP);
	/// @see SetKVP
	float GetKVP()const;
	/// @see SetKVP
	DcsString GetKVPAsString()const;
	/// Delete KVP
	void DeleteKVP();

	/// Focal Spot Size in millimeters : Tag (0018, 1190), VR = DS [required if "Frame Type", tag (0008, 9007), is "ORIGINAL"]
	bool SetFocalSpotSizeInMM(const float fNominalDimension);
	/// @see SetFocalSpotSizeInMM
	float GetFocalSpotSize()const;
	/// @see SetFocalSpotSizeInMM
	DcsString GetFocalSpotAsStringSize()const;
	/// Delete Focal Spot Size
	void DeleteFocalSpotSize();
	/// Returns true if only one focal spot size is defined
	bool HasSingleFocalSpotSize()const;

	/// Focal Spot Size in millimeters (two values) : Tag (0018, 1190), VR = DS [required if "Frame Type", tag (0008, 9007), is "ORIGINAL"]
	bool SetFocalSpotSizeInMM(const float fSmallSize, const float fLargeSize);
	//		i) Stored as single string in same tag, "Small\Large"
	/// @see SetFocalSpotSizeInMM
	bool GetFocalSpotSize(float &fSmallSize, float &fLargeSize)const;
	/// @see SetFocalSpotSizeInMM
	bool GetFocalSpotSize(DcsString &strSmallSize, DcsString &strLargeSize)const;
	/// Returns true if two focal spot sizes are defined
	bool HasTwoFocalSpotSizes()const;

	/// Filter Type : Tag (0018, 1160), VR = SH [required if "Frame Type", tag (0008, 9007), is "ORIGINAL"]
	bool SetFilterType(const FILTER_TYPE nFilterType);
	/// @see SetFilterType
	FILTER_TYPE GetFilterType()const;
	/// @see SetFilterType
	DcsString GetFilterTypeAsString()const;
	/// Delete Filter Type
	void DeleteFilterType();

	/// Filter Material (single item) : Tag (0018, 7050), VR = CS [required if "Frame Type", tag (0008, 9007), is "ORIGINAL" and "Filter Type" is not "NONE"]
	bool SetFilterMaterial(const FILTER_MATERIAL nFilterMaterial);
	/// Filter Material (multiple items) : Tag (0018, 7050), VR = CS [required if "Frame Type", tag (0008, 9007), is "ORIGINAL" and "Filter Type" is not "NONE"]
	bool SetFilterMaterial(const Array1D<FILTER_MATERIAL> &arrayFilterMaterial);
	/// @see SetFilterMaterial
	bool GetFilterMaterial(Array1D<CTXRayDetails::FILTER_MATERIAL> &arrayFilterMaterial)const;
	/// @see SetFilterMaterial
	const Array1D<DcsString>& GetFilterMaterial()const;
	/// Delete Filter Material
	void DeleteFilterMaterial();

protected:
	class ImplCTXRayDetails;
	ImplCTXRayDetails	*m_pImplCTXRayDetails; ///< Internal implementation
};

}//namespace CTTypes

}//namespace SDICOS

#endif
