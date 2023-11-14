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
#ifndef _STRATOVAN_DICOS_OVERLAY_PLANE_MODULE_H_
#define _STRATOVAN_DICOS_OVERLAY_PLANE_MODULE_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{

///
/// \class OverlayPlaneModule
/// \brief Implements Overlay Plane Module
/// SPECREF V03 Section 14.2.4, Table 89
///
/// Tag Group Range: (6000, ...) to (601E, ...), even numbers only
/// Required internal static counter to increment the tag group number
///
class OverlayPlaneModule
{
public:
	/// Constructor
	OverlayPlaneModule();
	/// Copy constructor
	OverlayPlaneModule(const OverlayPlaneModule &opm);
	/// Destructor
	virtual ~OverlayPlaneModule();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	OverlayPlaneModule& operator=(const OverlayPlaneModule &opm);
	/// Comparison operator
	bool operator==(const OverlayPlaneModule &opm)const;
	/// Comparison operator
	bool operator!=(const OverlayPlaneModule &opm)const;

	///
	/// \class Plane
	/// \brief Implements a single overlay plane
	///
	class Plane
	{
	public:
		/// Constructor
		/// @param nGroup Tag's group number
		Plane(const S_UINT16 nGroup);
		/// Copy constructor
		Plane(const Plane &plane);
		/// Destructor
		~Plane();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		Plane& operator=(const Plane &plane);
		/// Comparison operator
		bool operator==(const Plane &plane)const;
		/// Comparison operator
		bool operator!=(const Plane &plane)const;

		/// Overlay type enumerations
		typedef enum
		{
			enumUnknownOverlayType,	///< Unknown enumeration

			enumGraphics,	///< "G"
			enumROI,		///< "R"

		}OVERLAY_TYPE;

		/// Overlay subtype enumerations
		typedef enum
		{
			enumUnknownOverlaySubtype,	///< Unknown enumeration

			enumUser,		///< "USER"
			enumAutomated,	///< "AUTOMATED"

		}OVERLAY_SUBTYPE;

		/// Set attributes using as defined by the OverlayPlane object
		bool SetAttributes(const AttributeManager::OverlayPlane &plane, ErrorLog &errorlog);
		/// Copy the attributes into the attribute manager
		bool GetAttributes(AttributeManager &manager, ErrorLog &errorlog)const;
		/// Update the attribute manager with the plane's current values
		bool UpdateAttributes(const AttributeManager::OverlayPlane &plane, ErrorLog &errorlog);
		/// Validate all attributes
		bool IsValid(ErrorLog &errorlog);

		/// Overlay Type : Tag (60xx, 0040), VR = CS [required]
		bool SetOverlayType(const OVERLAY_TYPE nType);
		/// @see SetOverlayType
		OVERLAY_TYPE GetOverlayType()const;
		/// @see SetOverlayType
		DcsString GetOverlayTypeAsString()const;

		/// Overlay Origin : Tag (60xx, 0050), VM = 2, VR = SS [required]
		bool SetOrigin(const S_INT16 nRow, const S_INT16 nColumn);
		/// @see SetOrigin
		bool GetOrigin(S_INT16 &nRow, S_INT16 &nColumn)const;

		///
		/// Overlay Bits Allocated : Tag (60xx, 0100), VR = US [required]
		/// Value set to "1"
		///
		S_UINT16 GetBitsAllocated()const;

		///
		/// Overlay Bit Position : Tag (60xx, 0102), VR = US [required]
		/// Value set to "0"
		///
		S_UINT16 GetBitPosition()const;

		/// Overlay Data : Tag (60xx, 3000), VR = OB [required]
		/// @param nRows Overlay Rows : Tag (60xx, 0010), VR = US [required]
		/// @param nColumns Overlay Columns : Tag (60xx, 0011), VR = US [required]
		bool SetOverlayData(const S_UINT16 nRows, const S_UINT16 nColumns);
		/// Set or clear an overlay pixel at a given coordinate
		/// @param nRow Row index
		/// @param nColumn Column index
		/// @param bSet true: Set the overlay's pixel (Sets bit to 1). false: Clear the overlay's pixel (Sets bit to 0).
		/// @return true: Pixel was set/cleared.  false: Pixel was no set/cleared.
		bool SetOverlayPixel(const S_UINT16 nRow, const S_UINT16 nColumn, bool bSet);
		/// @see SetOverlayPixel
		bool IsOverylayPixelSet(const S_UINT16 nRow, const S_UINT16 nColumn)const;
		/// @see SetOverlayPixel
		bool IsOverylayPixelClear(const S_UINT16 nRow, const S_UINT16 nColumn)const;
		
		/// @see SetOverlayData
		S_UINT16 GetNumberOfRows()const;
		/// @see SetOverlayData
		S_UINT16 GetNumberOfColumns()const;

		/// Overlay Description : Tag (60xx, 0022), VR = LO [optional]
		bool SetOverlayDescription(const DcsLongString &strDescription);
		/// @see SetOverlayDescription
		DcsString GetOverlayDescription()const;

		/// Overlay Subtype : Tag (60xx, 0045), VR = LO [optional]
		bool SetSubtype(const OVERLAY_SUBTYPE nType);
		/// @see SetSubtype
		OVERLAY_SUBTYPE GetSubtype()const;
		/// @see SetSubtype
		DcsString GetSubtypeAsString()const;
		
		/// Overlay Label : Tag (60xx, 1500), VR = LO [optional]
		bool SetLabel(const DcsLongString &strLabel);
		/// @see SetLabel
		DcsString GetLabel()const;

		/// ROI Area : Tag (60xx, 1301), VR = IS [required if "Overlay Type" is "R"]
		bool SetRegionOfInterestArea(const S_INT32 nArea);
		/// @see SetRegionOfInterestArea
		S_INT32 GetRegionOfInterestArea()const;
		/// @see SetRegionOfInterestArea
		DcsString GetRegionOfInterestAreaAsString()const;

		/// ROI Mean : Tag (60xx, 1302), VR = DS [required if "Overlay Type" is "R"]
		bool SetRegionOfInterestMean(const float fMean);
		/// @see SetRegionOfInterestMean
		float GetRegionOfInterestMean()const;
		/// @see SetRegionOfInterestMean
		DcsString GetRegionOfInterestMeanAsString()const;

		/// ROI Standard Deviation : Tag (60xx, 1303), VR = DS [required if "Overlay Type" is "R"]
		bool SetRegionOfInterestStandardDeviation(const float fStandardDeviation);
		/// @see SetRegionOfInterestStandardDeviation
		float GetRegionOfInterestStandardDeviation()const;
		/// @see SetRegionOfInterestStandardDeviation
		DcsString GetRegionOfInterestStandardDeviationAsString()const;

	protected:
		class ImplPlane;
		ImplPlane *m_pImplPlane; ///< Internal implementation

		/// Disabled
		Plane();
	};

	///
	/// Initialize the class attributes from the given AttributeManager.
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager.
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager.
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	/// 
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// Returns number of planes
	S_UINT16 GetNumberOfPlanes()const;

	/// Add up to 16 planes
	/// @return Returns plane added
	OverlayPlaneModule::Plane* AddPlane();
	/// Delete a plane
	void DeletePlane(const S_UINT16 nIndex);
	/// Get a plane
	Plane* operator[](const S_UINT16 nIndex);
	/// Get a plane
	const Plane* operator[](const S_UINT16 nIndex)const;

protected:
	class ImplOverlayPlaneModule;
	ImplOverlayPlaneModule	*m_pImplOverlayPlaneModule; ///< Holds array of Plane pointers, each correspond to a group ID
};

}//namespace SDICOS

#endif