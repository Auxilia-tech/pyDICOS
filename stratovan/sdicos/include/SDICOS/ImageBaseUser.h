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
#ifndef _SDCS_USER_IMAGE_BASE_H
#define _SDCS_USER_IMAGE_BASE_H

#include "SDICOS/ImageBase.h"
#include "SDICOS/ErrorLog.h"

namespace SDICOS
{
	class ErrorLog;

	/// \class UserImageBase
	/// \brief User Level API interface to ImageCommon
	class ImageCommonUser
	{
	public:
		/// Constructor
		ImageCommonUser();
		/// Copy constructor
		ImageCommonUser(const ImageCommonUser& sc);
		/// Destructor
		virtual ~ImageCommonUser();

		/// Copy operator
		ImageCommonUser& operator=(const ImageCommonUser& sc);
		/// Comparison operator
		bool operator==(const ImageCommonUser& sc)const;
		/// Comparison operator
		bool operator!=(const ImageCommonUser& sc)const;

		/// Coordinate system
		/// Default set to ImageCommon::enumLHS
		bool SetCoordinateSystem(const ImageCommon::IMAGE_COORDINATE_SYSTEM nSystem);
		/// @see SetCoordinateSystem
		ImageCommon::IMAGE_COORDINATE_SYSTEM GetCoordinateSystem()const;

		/// Image origin
		/// Default set to ImageCommon::enumMachine
		bool SetImageOrigin(const ImageCommon::IMAGE_ORIGIN nOrigin);
		/// @see SetImageOrigin
		ImageCommon::IMAGE_ORIGIN GetImageOrigin()const;

		/// Reset to default values
		virtual void FreeMemory();

		/// Read values from parameters
		virtual bool Read(const ImageCommon&, ErrorLog& errorlog);
		/// Write values to parameters
		virtual bool Write(ImageCommon&, ErrorLog& errorlog)const;


	private:
		class ImageCommonUserImpl;
		ImageCommonUserImpl* m_pUserImageCommonImpl;
	};
}

#endif
