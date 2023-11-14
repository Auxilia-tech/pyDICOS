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
#ifndef _STRATOVAN_DICOS_AIT_PLANE_ORIENTATION_USER_H_
#define _STRATOVAN_DICOS_AIT_PLANE_ORIENTATION_USER_H_

#include "SDICOS/PlaneOrientationUser.h"
#include "SDICOS/PlaneOrientationAIT.h"
#include "SDICOS/Vector3D.h"

namespace SDICOS
{

	///
	/// \class AitPlaneOrientationUser
	/// \brief Implements AIT Plane Orientation User Level API
	///
	class AitPlaneOrientationUser
	{
	public:
		/// Constructor
		AitPlaneOrientationUser();
		/// Copy constructor
		AitPlaneOrientationUser(const AitPlaneOrientationUser& apo);
		/// Destructor
		~AitPlaneOrientationUser();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		AitPlaneOrientationUser& operator=(const AitPlaneOrientationUser& apo);
		/// Comparison operator
		bool operator==(const AitPlaneOrientationUser& apo)const;
		/// Comparison operator
		bool operator!=(const AitPlaneOrientationUser& apo)const;

		/// Read from AitPlaneOrientationUser Module
		bool Read(const AitPlaneOrientation& rhs, ErrorLog& el);

		/// Write to AitPlaneOrientationUser Module
		bool Write(AitPlaneOrientation& lhs, ErrorLog& el) const;

		///
		/// Set Image Orientation using direction cosines for first row and first column : Tag (0020, 0037), VR = DS [required if Frame Type's, (0008, 9007), first value is "ORIGINAL" and Volumetric Properties, (0008, 9206), is not "DISTORTED"]
		/// The coordinate system for CT and DX: 
		///		The positive Z-axis is the opposite of the scan direction.  
		///		The positive Y-axis points towards the ground.
		///		Facing the scan direction, the positive X-axis points to the right.  
		///	The coordinate system for AIT3D:
		///		The positive Z-axis points up.
		///		The positive Y-axis points to the front of the scanned person.
		///		The positive X-axis points to the left of the scanned person.
		///
		bool SetImageOrientation(const float fRowCosineX, const float fRowCosineY, const float fRowCosineZ,
			const float fColumnCosineX, const float fColumnCosineY, const float fColumnCosineZ);

		/// @see SetImageOrientation
		bool GetImageOrientation(float& fRowCosineX, float& fRowCosineY, float& fRowCosineZ,
			float& fColumnCosineX, float& fColumnCosineY, float& fColumnCosineZ)const;

		/// @see SetImageOrientation
		bool GetImageOrientationAsString(DcsString& strRowCosineX, DcsString& strRowCosineY, DcsString& strRowCosineZ,
			DcsString& strColumnCosineX, DcsString& strColumnCosineY, DcsString& strColumnCosineZ)const;

		/// @see SetImageOrientation
		bool GetImageOrientation(Vector3D<float>& rowOrientation, Vector3D<float>& columnOrientation)const;

		///
		/// PRCS (Person Reference Coordinate System) to RCS (Reference Coordinate System) Orientation
		///	Tag (4010, 107E), VM = 6, VR = DS [optional]
		/// Both PRCS and RCS follow positive Y-axis crossed with positive X-axis is positive Z-axis
		/// X-axis is given by fXx, fYx, and fZx.  The Y-axis is given by fXy, fYy, and fZy.
		///
		bool SetPrcsToRcsOrientation(const float fXx, const float fYx, const float fZx,
			const float fXy, const float fYy, const float fZy);
		/// @see SetPrcsToRcsOrientation
		bool GetPrcsToRcsOrientation(float& fXx, float& fYx, float& fZx,
			float& fXy, float& fYy, float& fZy)const;

		/// @see SetPrcsToRcsOrientation
		bool GetPrcsToRcsOrientation(DcsString& strXx, DcsString& strYx, DcsString& strZx,
			DcsString& strXy, DcsString& strYy, DcsString& strZy)const;

		/// @see SetPrcsToRcsOrientation
		bool GetPrcsToRcsOrientation(Vector3D<float>& XAxis, Vector3D<float>& YAxis)const;
	protected:
		class AitPlaneOrientationUserImpl;
		AitPlaneOrientationUserImpl* m_pAitPlaneOrientationUserImpl;
	};

}//namespace SDICOS

#endif
