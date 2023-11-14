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
#ifndef _STRATOVAN_DICOS_PIXEL_MEASUREMENTS_USER_H_
#define _STRATOVAN_DICOS_PIXEL_MEASUREMENTS_USER_H_

#include "SDICOS/Attribute.h"
#include "SDICOS/PixelMeasurement.h"

namespace SDICOS
{
	///
	/// \class PixelMeasurementUser
	/// \brief Implements Pixel Measurement User Level API
	///
	class PixelMeasurementUser
	{
	public:
		/// Constructor
		PixelMeasurementUser();
		/// Copy constructor
		PixelMeasurementUser(const PixelMeasurementUser& pixelmeasurement);
		/// Destructor
		virtual ~PixelMeasurementUser();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		PixelMeasurementUser& operator=(const PixelMeasurementUser& pixelmeasurement);
		/// Comparison operator
		bool operator==(const PixelMeasurementUser& pixelmeasurement)const;
		/// Comparison operator
		bool operator!=(const PixelMeasurementUser& pixelmeasurement)const;

		/// Initialize from PixelMeasurement Module
		/// @param pm PixelMeasurent
		/// @param el ErrorLog
		/// @return true/false
		bool Read(const PixelMeasurement& pm, ErrorLog& el);

		/// Write to PixelMeasurement
		/// @param pm PixelMeasurement
		/// @param el ErrorLog
		/// @return true/false
		bool Write(PixelMeasurement& pm, ErrorLog& el) const;

		/// Set Pixel Spacing in millimeters (Distance between pixel centers) : Tag (0028, 0030), VR = DS [required if Volumetric Properties, tag (0008, 9206), is not "DISTORTED" or "SAMPLED"]
		/// @param fSpacingRow Row spacing in millimeters
		/// @param fSpacingColumn Column spacing in millimeters
		bool SetPixelSpacingInMM(const float fSpacingRow, const float fSpacingColumn);
		//		a) Param 1, Distance between pixel center of rows in mm
		//		b) Param 2, Distance between pixel center of columns in mm
		//		c) Param 1-2 : Tag (0028, 0030)
		//			i) Stored in single tag : "RowSpacing\ColumnSpacing"

		/// @see SetPixelSpacingInMM
		float GetRowSpacing()const;
		/// @see SetPixelSpacingInMM
		DcsString GetRowSpacingAsString()const;
		/// @see SetPixelSpacingInMM
		float GetColumnSpacing()const;
		/// @see SetPixelSpacingInMM
		DcsString GetColumnSpacingAsString()const;

		/// Set Slice Thickness in millimeters : Tag (0018, 0050), VR = DS [required if Volumetric Properties, tag (0008, 9206), is "VOLUME" or "SAMPLED"]
		bool SetSliceThicknessInMM(const float fSliceThickness);
		/// @see SetSliceThicknessInMM
		float GetSliceThickness()const;
		/// @see SetSliceThicknessInMM
		DcsString GetSliceThicknessAsString()const;

	protected:
		class PixelMeasurementUserImpl;
		PixelMeasurementUserImpl* m_pPixelMeasurementUserImpl;
	};

}//namespace SDICOS

#endif
