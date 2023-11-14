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
#ifndef _STRATOVAN_DICOS_SDCS_PLANE_POSITION_H_
#define _STRATOVAN_DICOS_SDCS_PLANE_POSITION_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class PlanePosition
/// \brief Implements Plane Position, a required single item sequence (0020, 9113)
/// SPECREF V03 Section 14.14.3, Table 113
///
class PlanePosition
{
public:
	/// Constructor
	PlanePosition();
	/// Copy constructor
	PlanePosition(const PlanePosition &planeposition);
	/// Destructor
	virtual ~PlanePosition();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	PlanePosition& operator=(const PlanePosition &planeposition);
	/// Comparison operator
	bool operator==(const PlanePosition &planeposition)const;
	/// Comparison operator
	bool operator!=(const PlanePosition &planeposition)const;

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

	/// Set Position representing the first pixel's/voxel's position (top left) of the frame (center of voxel/pixel) in millimeters : Tag (0020, 0032), VR = DS, VM = 3 [required if Frame Type's, (0008, 9007), first value is "ORIGINAL" and Volumetric Properties, (0008, 9206), is not "DISTORTED"]
	bool SetPositionInMM(const float fX, const float fY, const float fZ = 0.0f);
	//		c) VM = 3 : Stored as single string "X\Y\Z"
	/// @see SetPositionInMM
	bool GetPosition(float &fX, float &fY, float &fZ)const;
	/// @see SetPositionInMM
	bool GetPositionAsString(DcsString &strX, DcsString &strY, DcsString &strZ)const;

protected:
	class ImplPlanePosition;
	ImplPlanePosition	*m_pImplPlanePosition; ///< Internal implementation
};

}//namespace SDICOS

#endif