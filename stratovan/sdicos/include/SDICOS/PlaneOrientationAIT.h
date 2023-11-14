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
#ifndef _STRATOVAN_DICOS_AIT_PLANE_ORIENTATION_H_
#define _STRATOVAN_DICOS_AIT_PLANE_ORIENTATION_H_

#include "SDICOS/PlaneOrientation.h"
#include "SDICOS/Vector3D.h"

namespace SDICOS
{

///
/// \class AitPlaneOrientation
/// \brief Implements AIT Plane Orientation
/// SPECREF V03 Section 14.14.5, Table 115
///
class AitPlaneOrientation : public PlaneOrientation
{
public:
	/// Constructor
	AitPlaneOrientation();
	/// Copy constructor
	AitPlaneOrientation(const AitPlaneOrientation &apo);
	/// Destructor
	~AitPlaneOrientation();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	AitPlaneOrientation& operator=(const AitPlaneOrientation &apo);
	/// Comparison operator
	bool operator==(const AitPlaneOrientation &apo)const;
	/// Comparison operator
	bool operator!=(const AitPlaneOrientation &apo)const;

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

	///
	/// PRCS (Person Reference Coordinate System) to RCS (Reference Coordinate System) Orientation
	///	Tag (4010, 107E), VM = 6, VR = DS [optional]
	/// Both PRCS and RCS follow positive Y-axis crossed with positive X-axis is positive Z-axis
	/// X-axis is given by fXx, fYx, and fZx.  The Y-axis is given by fXy, fYy, and fZy.
	///
	bool SetPrcsToRcsOrientation(	const float fXx, const float fYx, const float fZx, 
									const float fXy, const float fYy, const float fZy);
	/// @see SetPrcsToRcsOrientation
	bool GetPrcsToRcsOrientation(	float &fXx, float &fYx, float &fZx, 
									float &fXy, float &fYy, float &fZy)const;

	/// @see SetPrcsToRcsOrientation
	bool GetPrcsToRcsOrientation(DcsString &strXx, DcsString &strYx, DcsString &strZx, 
										DcsString &strXy, DcsString &strYy, DcsString &strZy)const;

	/// @see SetPrcsToRcsOrientation
	bool GetPrcsToRcsOrientation(Vector3D<float>& XAxis, Vector3D<float>& YAxis)const;
protected:
	class ImplAitPlaneOrientation;
	ImplAitPlaneOrientation	*m_pImplAitPlaneOrientation; ///< Internal implementation
};

}//namespace SDICOS

#endif
