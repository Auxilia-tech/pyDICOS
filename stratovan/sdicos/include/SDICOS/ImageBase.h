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
#ifndef _SDCS_IMAGE_BASE_H
#define _SDCS_IMAGE_BASE_H

#include "SDICOS/Attribute.h"
#include "SDICOS/ErrorLog.h"
#include "SDICOS/Tag.h"

namespace SDICOS
{
	///  
	/// \class ImageCommon
	/// \brief Base class containing attributes shared by CT, AIT2D, AIT3D, and DX/X-Ray Image Modules
	/// SPECREF V03 Section 7.4.2, Table 20
	/// SPECREF V03 Section 9.2.3.2, Table 42
	/// SPECREF V03 Section 9.3.3.2, Table 48
	/// SPECREF V03 Section 8.2.2.2, Table 35
	///
	class ImageCommon
	{
	public:
		/// Default constructor
		ImageCommon();

		/// Copy Constructor 
		ImageCommon(const ImageCommon &imageCommon);

		/// Destructor
		virtual ~ImageCommon();

		/// Free allocated resources
		virtual void FreeMemory();

		/// Assignment operator
		ImageCommon& operator=(const ImageCommon &imageCommon);

		/// Comparison operator
		bool operator==(const ImageCommon &imageCommon)const;

		/// Comparison operator
		bool operator!=(const ImageCommon &imageCommon)const;

		///
		/// Determine if all needed attributes (required and conditionally required) are set.
		///
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		///
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

		///
		/// Initialize the class attributes from the given AttributeManager
		///
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report missing required attributes
		/// @return true/false		false is returned if any required attribute is missing or invalid
		///
		virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		///
		/// Set all required and optional attributes from the given AttributeManager
		///
		/// @param attribManager	AttributeManager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false if IsValid() returns false
		///
		virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		///
		/// Copy the attributes from the module into the given AttributeManager
		///
		/// @param attribManager	AttributeManager to store the module's attributes
		/// @param errorlog			Report missing required attributes
		/// @return true/false		false is returned if any required attribute is not present
		virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

		/// Enumeration for Image Origin
		typedef enum
		{
			enumUnknownImageOrigin,

			enumMachine,   ///< "MACHINE"
			enumSynthetic, ///< "SYNTHETIC"
			enumAugmented, ///< "AUGMENTED"
		}IMAGE_ORIGIN;

		/// Enumeration for Coordinate System
		typedef enum
		{
			enumUnknownCoordinateSystem,

			enumLHS, ///< "LHS"
			enumRHS, ///< "RHS"
		}IMAGE_COORDINATE_SYSTEM;   

		///
		/// Set Image Origin : Tag (0008, 0118), VR = CS [required] 
		/// @param nOrigin  Value to set the origin to
		/// @return true/false
		///
		bool SetImageOrigin(IMAGE_ORIGIN nOrigin);
		/// @see SetImageOrigin
		IMAGE_ORIGIN GetImageOrigin()const;
		/// @see Set ImageOrigin 
		DcsCodeString GetImageOriginAsString()const;

		/// Check if an Image Origin value is valid
		/// @param nOrigin Value to check
		/// @return true if it is valid, false otherwise
		static bool IsImageOriginValid(IMAGE_ORIGIN nOrigin);
		/// @see IsImageOriginValid
		static bool IsImageOriginValid(DcsString strOrigin);
		/// If the string is a valid Image Origin, return the associated enum value
		/// @param strOrigin string to convert to Image Origin enum
		/// @return enum value of strOrigin if strOrigin is valid, enumUnknownImageOrigin otherwise
		static IMAGE_ORIGIN GetImageOriginAsEnum(DcsString strOrigin);

		///
		/// Set Coordinate System : Tag (0008, 2108), VR = CS [required]
		/// @param nSystem  Value to set the Coordinate system to
		/// @return true/false
		bool SetCoordinateSystem(IMAGE_COORDINATE_SYSTEM nSystem);
		/// @see SetCoordinateSystem
		IMAGE_COORDINATE_SYSTEM GetCoordinateSystem()const;
		/// @see SetCoordinateSystem 
		DcsCodeString GetCoordinateSystemAsString()const;

		/// Check if a Coordinate System value is valid
		/// @param nSystem Value to check
		/// @return true if it is valid, false otherwise
		static bool IsCoordinateSystemValid(IMAGE_COORDINATE_SYSTEM nSystem);
		/// @see IsCoordinateSystemValid
		static bool IsCoordinateSystemValid(DcsString strCoordinateSystem);
		/// If the input is a valid Coordinate System, return the associated enum value
		/// @param strCorodinateSystem string to convert to Image Coordinate System enum
		/// @return enum value of strCoordinateSystem if strCoordinateSystem is valid, enumUnknownCoordinateSystem otherwise
		static IMAGE_COORDINATE_SYSTEM GetCoordinateSystemAsEnum(DcsString strCorodinateSystem);

	protected:
		class ImplImageCommon;
		ImplImageCommon *m_pImplImageCommon; ///< Internal implementation
	};
} //namespace SDICOS

#endif //_SDCS_IMAGE_BASE_H
