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
#ifndef _STRATOVAN_DICOS_DX_XRAY_FILTRATION_USER_H_
#define _STRATOVAN_DICOS_DX_XRAY_FILTRATION_USER_H_

#include "SDICOS/Attribute.h"
#include "SDICOS/XRayFiltration.h"

namespace SDICOS
{
	using namespace DXTypes;

	///
	/// \class XRayFiltrationUser
	/// \brief Implements X-Ray Filtration for User Level API
	///
	class XRayFiltrationUser
	{
	public:
		/// Constructor
		XRayFiltrationUser();
		/// Copy constructor
		XRayFiltrationUser(const XRayFiltrationUser& xrf);
		/// Destructor
		virtual ~XRayFiltrationUser();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		XRayFiltrationUser& operator=(const XRayFiltrationUser& xrf);
		/// Comparison operator
		bool operator==(const XRayFiltrationUser& xrf)const;
		/// Comparison operator
		bool operator!=(const XRayFiltrationUser& xrf)const;

		/// XRayFiltrationUser has been set to valid values
		/// @return true/false
		bool IsValid() const;

		/// Read values from parameters
		virtual bool Read(const XRayFiltration& rhs, ErrorLog& errorlog);
		/// Write values to parameters
		virtual bool Write(XRayFiltration& lhs, ErrorLog& errorlog)const;

		/// Filter Type : Tag (0018, 1160), VR = SH [optional]
		bool SetFilterType(const XRayFiltration::FILTER_TYPE nType);
		/// @see SetFilterType
		XRayFiltration::FILTER_TYPE GetFilterType()const;
		/// @see SetFilterType
		DcsString GetFilterTypeAsString()const;
		/// Delete Filter Type
		void DeleteFilterType();

		/// Filter Material : Tag (0018, 7050), VR = CS [optional]
		bool SetFilterMaterial(const Array1D<XRayFiltration::FILTER_MATERIAL>& arrayMaterial);
		/// Filter Material : Tag (0018, 7050), VR = CS [optional]
		bool SetFilterMaterial(const XRayFiltration::FILTER_MATERIAL& nMaterial);
		/// @see SetFilterMaterial
		bool GetFilterMaterial(Array1D<XRayFiltration::FILTER_MATERIAL>& arrayMaterial)const;
		/// @see SetFilterMaterial
		bool GetFilterMaterial(Array1D<DcsString>& arrayMaterial)const;
		/// @see SetFilterMaterial
		bool GetFilterMaterial(XRayFiltration::FILTER_MATERIAL& nMaterial)const;
		/// @see SetFilterMaterial
		bool GetFilterMaterial(DcsString& strMaterial)const;
		/// Delete Filter Material
		void DeleteFilterMaterial();

		/// Filter Thickness Minimum in mm : Tag (0018, 7052), VR = DS [optional]
		bool SetFilterMinimumThicknessMM(const Array1D<float>& arrayThickness);
		/// Filter Thickness Minimum in mm : Tag (0018, 7052), VR = DS [optional]
		bool SetFilterMinimumThicknessMM(const float fThickness);
		/// @see SetFilterMinimumThicknessMM
		bool GetFilterMinimumThickness(Array1D<float>& arrayThickness)const;
		/// @see SetFilterMinimumThicknessMM
		bool GetFilterMinimumThickness(float& fThickness)const;
		/// Delete Filter Thickness Minimum
		void DeleteFilterMinimumThickness();

		/// Filter Thickness Maximum in mm : Tag (0018, 7054), VR = DS [optional]
		bool SetFilterMaximumThicknessMM(const Array1D<float>& arrayThickness);
		/// Filter Thickness Maximum in mm : Tag (0018, 7054), VR = DS [optional]
		bool SetFilterMaximumThicknessMM(const float fThickness);
		/// @see SetFilterMaximumThicknessMM
		bool GetFilterMaximumThickness(Array1D<float>& arrayThickness)const;
		/// @see SetFilterMaximumThicknessMM
		bool GetFilterMaximumThickness(float& fThickness)const;
		/// @see SetFilterMaximumThicknessMM
		void DeleteFilterMaximumThickness();

	protected:
		class ImplXRayFiltration;
		ImplXRayFiltration* m_pImplXRayFiltration; ///< Internal implementation
	};

}//namespace SDICOS

#endif