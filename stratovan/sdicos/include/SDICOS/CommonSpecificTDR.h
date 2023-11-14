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
#ifndef _STRATOVAN_DICOS_COMMON_SPECIFIC_TDR_H_
#define _STRATOVAN_DICOS_COMMON_SPECIFIC_TDR_H_

#include "SDICOS/SopInstanceReference.h"
#include "SDICOS/Point3D.h"
#include "SDICOS/Bitmap.h"

namespace SDICOS
{
namespace TDRTypes
{

///
/// \class CommonSpecificTDR
/// Common attributes for Baggage-Specific TDR Details Macro and Person-Specific TDR Details Macro Attributes
/// SPECREF V03 Section 12.5.1, Table 71
/// SPECREF V03 Section 12.5.2, Table 72
///
class CommonSpecificTDR
{
protected:
	class ImplCommonSpecificTDR;
public:
	
	/// ConstructorC
	CommonSpecificTDR();
	
	/// Copy Constructor
	CommonSpecificTDR(const CommonSpecificTDR &common);
	
	/// Destructor
	virtual ~CommonSpecificTDR();

	/// Reset to default state
	virtual void FreeMemory();

	/// Assignment operator
	CommonSpecificTDR& operator=(const CommonSpecificTDR &common);
	
	/// equality comparison operator
	bool operator==(const CommonSpecificTDR &common)const;
	
	/// inequality comparison operator
	bool operator!=(const CommonSpecificTDR &common)const;

	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false is returned if attributes were specified or if some were invalid.
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

	///
	/// \class ThreatROI 
	/// Implements the Threat ROI Voxel Sequence (Single Item Sequence), Tag (4010, 1001)
	/// and the attributes contained within its single item.
	///
	class ThreatROI
	{
		friend class CommonSpecificTDR::ImplCommonSpecificTDR;
	public:
		/// Default Constructor
		ThreatROI();
		
		/// Copy Constructor
		ThreatROI(const ThreatROI &troi);
		
		/// Destructor
		virtual ~ThreatROI();

		/// Delete allocated memory
		virtual void FreeMemory();

		/// Assignment operator
		ThreatROI& operator=(const ThreatROI &troi);
		
		/// equality comparison operator
		bool operator==(const ThreatROI &troi)const;
		
		/// inequality comparison operator
		bool operator!=(const ThreatROI &troi)const;

		/// Initialize the class attributes from the given AttributeManager
		///
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not fetched
		///							or if some were invalid.
		bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Copy the attributes from the module into the given AttributeManager
		///
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if all required attributes were not uploaded.
		bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Attempt to set all required and optional attributes from the given AttributeManager
		///
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false is returned if attributes were specified or if some were invalid.
		bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		/// Determine if all needed attributes (required and conditionally required) are set
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;

		/// Set Threat ROI Base in image space: Tag (4010, 1004), VR = FL [required]
		///	Threat ROI Base, (minX, minY, minZ) corner
		///		i) Values stored sequentially as XYZ
		///		ii)	2D images: Z = 0
		/// @param fMinX Starting corner X
		/// @param fMinY Starting corner Y
		/// @param fMinZ Starting corner Z
		/// @return true/false
		bool SetThreatRoiBase(const float fMinX, const float fMinY, const float fMinZ);

		/// @see SetThreatRoiBase
		bool GetThreatRoiBase(float &fMinX, float &fMinY, float &fMinZ)const;
	
		/// Threat ROI Extents in image space : Tag (4010, 1005), VR = FL [required]
		///		i) Values stored sequentially as WHD
		///		ii)	2D images: D = 0
		///		iii) Width and Height must be greater than zero
		/// @param fWidth Threat Extent width
		/// @param fHeight Threat Extent height
		/// @param fDepth Threat Extent depth
		/// @return true/false
		bool SetThreatRoiExtents(const float fWidth, const float fHeight, const float fDepth);

		/// @see SetThreatRoiExtents
		bool GetThreatRoiExtents(float& fWidth, float& fHeight, float& fDepth) const;

		/// Get the volume indicated by Threat Roi Extents
		float GetThreatRoiVolume() const;
		
		/// Set Threat ROI Bitmap : Tag (4010, 1006)
		///	@param threatROIBitmap Threat ROI Bitmap, "1" indicates PTO voxel, starting at (minX, minY, minZ) : Tag (4010, 1006), VR = OB [required (type 2), can be empty]
		///		i) If length is zero, all voxels in ROI default to "1".
		/// @return true/false
		bool SetThreatRoiBitmap(const SDICOS::Bitmap &threatROIBitmap);

		/// @see SetThreatRoiBitmap
		bool GetThreatRoiBitmap(SDICOS::Bitmap &threatROIBitmap)const;

		Bitmap& GetThreatRoiBitmap();
		const Bitmap& GetThreatRoiBitmap() const;
		
		/// Determine if the Bitmap has valid data or not
		bool Empty() const;

		/// Returns true if ROI Base or ROI Extents
		bool AreAnyRequiredAttributesSet()const;
		
	protected:
		class ImplThreatROI;
		ImplThreatROI	*m_pImplThreatROI; ///< Internal implementation
		
		ImplThreatROI* GetImpl();
		const ImplThreatROI* GetImpl() const;
	};

	/// Set Referenced Instance Sequence : Tag (0008, 114A), VR = SQ [required]
	///	@param arrayReference Referenced Instances
	/// @return true/false
	bool SetReferencedInstance(const Array1D<SopInstanceReference> &arrayReference);

	/// @see SetReferencedInstance
	bool GetReferencedInstance(Array1D<SopInstanceReference> &arrayReference)const;

	/// @see SetReferencedInstance
	Array1D<SopInstanceReference>& GetReferencedInstance();

	/// @see SetReferencedInstance
	const Array1D<SopInstanceReference>& GetReferencedInstance()const;
	
	typedef Array1D< Point3D<float> > BoundingPolygon;
	
	/// Set Bounding Polygon : Tag (4010, 101D)
	///	@param arrayBoundingPolygon Array of 3D Points : Tag (4010, 101D), VR = FL [optional]
	///		i) Values stored sequentially as XYZ
	///		ii)	2D images: Z = 0
	///		iii) Must have at least 2 points
	/// @return true/false
	bool SetBoundingPolygon(const Array1D< Point3D<float> > &arrayBoundingPolygon);
	
	/// @see SetBoundingPolygon
	bool GetBoundingPolygon(Array1D< Point3D<float> > &arrayBoundingPolygon)const;

	/// @see SetBoundingPolygon
	Array1D< Point3D<float> >& GetBoundingPolygon();
	/// @see SetBoundingPolygon
	const Array1D< Point3D<float> >& GetBoundingPolygon()const;
	
	/// Remove bounding polygon so that it is not written to the DICOS file
	void DeleteBoundingPolygon();
	
	/// Set Threat ROI Voxel Sequence (Single Item Sequence) : Tag (4010, 1001), VR = SQ 
	/// [If OOI Type (4010, 1042) = "BAGGAGE": Required if "TDR Type", tag (4010, 1027), is "MACHINE"]
	/// [If OOI Type (4010, 1042) = "PERSON": Optional]
	///	@param threatroi Threat ROI
	/// @return true/false
	bool SetThreatROI(const ThreatROI &threatroi);

	/// @see SetThreatROI
	bool GetThreatROI(ThreatROI &threatroi)const;
	
	/// @see SetThreatROI
	ThreatROI& GetThreatROI();
	
	/// @see SetThreatROI
	const ThreatROI& GetThreatROI()const;
	
	/// Set PTO Location Description : Tag (4010, 1078)
	/// @param strDescription PTO Location Description : Tag (4010, 1078), VR = ST [optional]
	/// @return true/false
	bool SetLocationDescription(const DcsShortText &strDescription);

	/// @see SetLocationDescription
	DcsString GetLocationDescription()const;

	/// @see SetLocationDescription
	bool HasLocationDescription()const;
	
	/// Remove location description so that it is not written to the DICOS file
	void DeleteLocationDescription();
	
	/// Set Center of PTO : Tag (4010. 101C), VR = FL [optional]
	///		i) Values stored sequentially as XYZ
	///		ii) Values in image space (Z indicates frame number, Z = 1 for first frame)
	///		iii) 2D images: Z = 0
	///
	/// @return true/false
	bool SetCenter(const float fX, const float fY, const float fZ);

	/// @see GetCenter
	bool GetCenter(float &fX, float &fY, float &fZ)const;

	/// @see GetCenter
	bool HasCenter()const;
	
	/// Remove center attribute so that it is not written to the DICOS file
	void DeleteCenter();

protected:
	//class ImplCommonSpecificTDR;
	ImplCommonSpecificTDR	*m_pImplCommonSpecificTDR; ///< Internal implementation
	
	ImplCommonSpecificTDR* GetImpl();
	const ImplCommonSpecificTDR* GetImpl() const;
};

}//namespace TDRTypes
}//namespace SDICOS

#endif
