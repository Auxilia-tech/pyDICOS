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
#ifndef _STRATOVAN_DICOS_SDCS_PLANE_POSITION_USER_H_
#define _STRATOVAN_DICOS_SDCS_PLANE_POSITION_USER_H_

#include "SDICOS/Attribute.h"
#include "SDICOS/PlanePosition.h"

namespace SDICOS
{
	///
	/// \class PlanePositionUser
	/// \brief Implements Plane Position User Level API
	///
	class PlanePositionUser
	{
	public:
		/// Constructor
		PlanePositionUser();
		/// Copy constructor
		PlanePositionUser(const PlanePositionUser& planeposition);
		/// Destructor
		virtual ~PlanePositionUser();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		PlanePositionUser& operator=(const PlanePositionUser& planeposition);
		/// Comparison operator
		bool operator==(const PlanePositionUser& planeposition)const;
		/// Comparison operator
		bool operator!=(const PlanePositionUser& planeposition)const;

		/// Initialize from PlanePosition Module
		/// @param pp PlanePosition
		/// @param el ErrorLog
		/// @return true/false
		bool Read(const PlanePosition& pp, ErrorLog& el);

		/// Write to PlanePosition
		/// @param pp PlanePosition
		/// @param el ErrorLog
		/// @return true/false
		bool Write(PlanePosition& pp, ErrorLog& el) const;

		/// Set Position representing the first pixel's/voxel's position (top left) of the frame (center of voxel/pixel) in millimeters : Tag (0020, 0032), VR = DS, VM = 3 [required if Frame Type's, (0008, 9007), first value is "ORIGINAL" and Volumetric Properties, (0008, 9206), is not "DISTORTED"]
		bool SetPositionInMM(const float fX, const float fY, const float fZ = 0.0f);
		//		c) VM = 3 : Stored as single string "X\Y\Z"
		/// @see SetPositionInMM
		bool GetPosition(float& fX, float& fY, float& fZ)const;
		/// @see SetPositionInMM
		bool GetPositionAsString(DcsString& strX, DcsString& strY, DcsString& strZ)const;

	protected:
		class PlanePositionUserImpl;
		PlanePositionUserImpl* m_pPlanePositionUserImpl;
	};

}//namespace SDICOS

#endif