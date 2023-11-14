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
#ifndef _STRATOVAN_DICOS_DX_POSITIONING_USER_H_
#define _STRATOVAN_DICOS_DX_POSITIONING_USER_H_

#include "SDICOS/DXPositioning.h"
#include "SDICOS/DetectorGeometry.h"

namespace SDICOS
{
	class DXPositioningUser
	{
	public:
		DXPositioningUser();
		DXPositioningUser(const DXPositioningUser& rhs);
		virtual ~DXPositioningUser();

		DXPositioningUser& operator=(const DXPositioningUser& rhs);
		bool operator==(const DXPositioningUser& rhs) const;
		bool operator!=(const DXPositioningUser& rhs) const;

		/// DXPositioningUser has been set to valid values
		/// @return true/false
		bool IsValid() const;

		void FreeMemory();

		/// Read DXDetectorUser from the DXTypes::DXDetector object
		/// @param dxDetector Object to read from
		/// @param el Error Log
		/// @return true/false
		bool Read(const DXTypes::DXPositioning& dxDetector, ErrorLog& el);

		/// Write DXDetectorUser 
		/// @param dxDetector Object to write into
		/// @param el Error log
		/// @return true/false
		bool Write(DXTypes::DXPositioning& dxDetector, ErrorLog& el) const;

		/// Belt Speed in mm/sec : Tag (0018, 9309), VR = FD [required]
		bool SetBeltSpeed(const double fBeltSpeed);
		/// @see SetBeltSpeed
		double GetBeltSpeed()const;

		/// Belt Height in mm relative to the coordinate system's origin : Tag (4010, 1062), VR = FL [required]
		bool SetBeltHeight(const float fBeltHeight);
		/// @see SetBeltHeight
		float GetBeltHeight()const;

		/// Detector Geometry Sequence : Tag (4010, 0004), VR = SQ [optional]
		bool SetDetectorGeometrySequence(const DXTypes::DetectorGeometry& dg);
		/// @see SetDetectorGeometrySequence
		bool GetDetectorGeometrySequence(DXTypes::DetectorGeometry& dg)const;
		/// @see SetDetectorGeometrySequence
		DXTypes::DetectorGeometry& GetDetectorGeometrySequence();
		/// @see SetDetectorGeometrySequence
		const DXTypes::DetectorGeometry& GetDetectorGeometrySequence()const;
		/// Determine if the Detector Geometry Sequence is set
		/// @return true if the sequence is set
		bool HasDetectorGeometrySequence()const;
		/// Delete the Detector Geometry Sequence and its internals
		void DeleteDetectorGeometrySequence();

	private:
		class DXPositioningUserImpl;
		DXPositioningUserImpl* m_pDXPositioningUserImpl;
	};
}

#endif