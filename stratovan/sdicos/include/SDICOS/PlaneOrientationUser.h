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
#ifndef _STRATOVAN_DICOS_PLANE_ORIENTATION_USER_H_
#define _STRATOVAN_DICOS_PLANE_ORIENTATION_USER_H_

#include "SDICOS/Attribute.h"
#include "SDICOS/Vector3D.h"
#include "SDICOS/PlaneOrientation.h"

namespace SDICOS
{

	///
	/// \class PlaneOrientationUser
	/// \brief Implements Plane Orientation User Level API
	///
	class PlaneOrientationUser
	{
	public:
		/// Constructor
		PlaneOrientationUser();
		/// Copy constructor
		PlaneOrientationUser(const PlaneOrientationUser& planeorientation);
		/// Destructor
		virtual ~PlaneOrientationUser();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		PlaneOrientationUser& operator=(const PlaneOrientationUser& planeorientation);
		/// Comparison operator
		bool operator==(const PlaneOrientationUser& planeorientation)const;
		/// Comparison operator
		bool operator!=(const PlaneOrientationUser& planeorientation)const;

		/// Read from PlaneOrientation Module
		bool Read(const PlaneOrientation& rhs, ErrorLog& el);

		/// Write to PlaneOrientation Module
		bool Write(PlaneOrientation& lhs, ErrorLog& el) const;

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

	protected:
		class ImplPlaneOrientation;
		ImplPlaneOrientation* m_pImplPlaneOrientation; ///< Internal implementation
	};

}//namespace SDICOS

#endif
