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
#ifndef _STRATOVAN_DICOS_DX_XRAY_FILTRATION_H_
#define _STRATOVAN_DICOS_DX_XRAY_FILTRATION_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{
namespace DXTypes
{

///
/// \class XRayFiltration
/// \brief Implements X-Ray Filtration
/// SPECREF V03 Section 8.2.2.6, Table 39
///
class XRayFiltration
{
public:
	/// Constructor
	XRayFiltration();
	/// Copy constructor
	XRayFiltration(const XRayFiltration &xrf);
	/// Destructor
	virtual ~XRayFiltration();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	XRayFiltration& operator=(const XRayFiltration &xrf);
	/// Comparison operator
	bool operator==(const XRayFiltration &xrf)const;
	/// Comparison operator
	bool operator!=(const XRayFiltration &xrf)const;

	/// Filter type enumerations
	typedef enum
	{
		enumUnknownFilterType,	///< Unknown enumeration

		enumStrip,		///< "STRIP"
		enumWedge,		///< "WEDGE"
		enumButterfly,	///< "BUTTERFLY"
		enumMultiple,	///< "MULTIPLE"
		enumNone,		///< "NONE"

	}FILTER_TYPE;

	/// Filter material enumerations
	typedef enum
	{
		enumUnknownFilterMaterial,	///< Unknown enumeration

		enumMolybdenum,		///< "MOLYBDENUM"
		enumAluminum,		///< "ALUMINUM"
		enumCopper,			///< "COPPER"
		enumRhodium,		///< "RHODIUM"
		enumNiobium,		///< "NIOBIUM"
		enumEuropium,		///< "EUROPIUM"
		enumLead,			///< "LEAD"

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

	/// Filter Type : Tag (0018, 1160), VR = SH [optional]
	bool SetFilterType(const FILTER_TYPE nType);
	/// @see SetFilterType
	FILTER_TYPE GetFilterType()const;
	/// @see SetFilterType
	DcsString GetFilterTypeAsString()const;
	/// Delete Filter Type
	void DeleteFilterType();

	/// Filter Material : Tag (0018, 7050), VR = CS [optional]
	bool SetFilterMaterial(const Array1D<FILTER_MATERIAL> &arrayMaterial);
	/// Filter Material : Tag (0018, 7050), VR = CS [optional]
	bool SetFilterMaterial(const FILTER_MATERIAL &nMaterial);
	/// @see SetFilterMaterial
	bool GetFilterMaterial(Array1D<FILTER_MATERIAL> &arrayMaterial)const;
	/// @see SetFilterMaterial
	bool GetFilterMaterial(Array1D<DcsString> &arrayMaterial)const;
	/// @see SetFilterMaterial
	bool GetFilterMaterial(FILTER_MATERIAL &nMaterial)const;
	/// @see SetFilterMaterial
	bool GetFilterMaterial(DcsString &strMaterial)const;
	/// Delete Filter Material
	void DeleteFilterMaterial();

	/// Filter Thickness Minimum in mm : Tag (0018, 7052), VR = DS [optional]
	bool SetFilterMinimumThicknessMM(const Array1D<float> &arrayThickness);
	/// Filter Thickness Minimum in mm : Tag (0018, 7052), VR = DS [optional]
	bool SetFilterMinimumThicknessMM(const float fThickness);
	/// @see SetFilterMinimumThicknessMM
	bool GetFilterMinimumThickness(Array1D<float> &arrayThickness)const;
	/// @see SetFilterMinimumThicknessMM
	bool GetFilterMinimumThickness(Array1D<DcsString> &arrayThickness)const;
	/// @see SetFilterMinimumThicknessMM
	bool GetFilterMinimumThickness(float &fThickness)const;
	/// @see SetFilterMinimumThicknessMM
	bool GetFilterMinimumThickness(DcsString &strThickness)const;
	/// Delete Filter Thickness Minimum
	void DeleteFilterMinimumThickness();

	/// Filter Thickness Maximum in mm : Tag (0018, 7054), VR = DS [optional]
	bool SetFilterMaximumThicknessMM(const Array1D<float> &arrayThickness);
	/// Filter Thickness Maximum in mm : Tag (0018, 7054), VR = DS [optional]
	bool SetFilterMaximumThicknessMM(const float fThickness);
	/// @see SetFilterMaximumThicknessMM
	bool GetFilterMaximumThickness(Array1D<float> &arrayThickness)const;
	/// @see SetFilterMaximumThicknessMM
	bool GetFilterMaximumThickness(Array1D<DcsString> &arrayThickness)const;
	/// @see SetFilterMaximumThicknessMM
	bool GetFilterMaximumThickness(float &fThickness)const;
	/// @see SetFilterMaximumThicknessMM
	bool GetFilterMaximumThickness(DcsString &strThickness)const;
	/// Delete Filter Thickness Maximum
	void DeleteFilterMaximumThickness();

protected:
	class ImplXRayFiltration;
	ImplXRayFiltration	*m_pImplXRayFiltration; ///< Internal implementation
};

}//namespace DXTypes
}//namespace SDICOS

#endif