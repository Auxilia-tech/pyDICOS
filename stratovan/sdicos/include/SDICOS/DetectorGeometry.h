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
#ifndef _STRATOVAN_DICOS_DETECTOR_GEOMETRY_H_
#define _STRATOVAN_DICOS_DETECTOR_GEOMETRY_H_

#include "SDICOS/Attribute.h"

namespace SDICOS
{
namespace DXTypes
{

///
/// \class DetectorGeometry
/// \brief Implements Detector Geometry Sequence, an optional sequence (4010, 0004), in DX/X-Ray Positioning
/// SPECREF V03 Section 8.2.2.4, Table 37
///
class DetectorGeometry
{
public:
	/// Constructor
	DetectorGeometry();
	/// Copy constructor
	DetectorGeometry(const DetectorGeometry &dg);
	/// Destructor
	~DetectorGeometry();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	DetectorGeometry& operator=(const DetectorGeometry &dg);
	/// Comparison operator
	bool operator==(const DetectorGeometry &dg)const;
	/// Comparison operator
	bool operator!=(const DetectorGeometry &dg)const;

	///
	/// \class GeometryItem
	/// \brief Implements an item in Detector Geometry Sequence
	///
	class GeometryItem
	{
	public:
		/// Constructor
		GeometryItem();
		/// Copy constructor
		GeometryItem(const GeometryItem &item);
		/// Destructor
		~GeometryItem();

		/// Reset to default values
		void FreeMemory();

		/// Copy operator
		GeometryItem& operator=(const GeometryItem &item);
		/// Comparison operator
		bool operator==(const GeometryItem &item)const;
		/// Comparison operator
		bool operator!=(const GeometryItem &item)const;

		///
		/// Initialize the class attributes from the given AttributeManager
		///
		/// @param attribManager 	Attribute Manager that contains the module's attributes
		/// @param errorlog 	 	Report missing required attributes
		/// @return true/false		false is returned if any required attribute is missing or invalid
		///
		bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		///
		/// Copy the attributes from the module into the given AttributeManager
		///
		/// @param attribManager 	AttributeManager to store the module's attributes
		/// @param errorlog		 	Report missing required attributes
		/// @return true/false		false is returned if any required attribute is not present.
		///
		bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

		///
		/// Set all required and optional attributes from the given AttributeManager
		///
		/// @param attribManager	Attribute Manager that contains the module's attributes
		/// @param errorlog			Report found attributes where IsValid() returns false
		/// @return true/false		false if IsValid() returned false
		///
		bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

		///
		/// Determine if all needed attributes (required and conditionally required) are set.
		///
		/// @param attribManager	AttributeManager used to check dependencies
		/// @param errorlog			ErrorLog used to report errors
		/// @return true/false
		///
		bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

		/// Distance Source To Detector in mm : Tag (0018, 1110), VR = DS [optional]
		bool SetDistanceToDetectorMM(const float fDistanceToDetector);
		/// @see SetDistanceToDetectorMM
		float GetDistanceToDetector()const;
		/// @see SetDistanceToDetectorMM
		DcsString GetDistanceToDetectorAsString()const;
		/// @see SetDistanceToDetectorMM
		/// @return true if distance to detector is set
		bool HasDistanceToDetector()const;
		/// @see SetDistanceToDetectorMM
		/// Delete distance to detector
		void DeleteDistanceToDetector();
		
		/// Source Orientation : Tag (4010, 1060), VM = 3, VR = FL [optional]
		bool SetSourceOrientation(	const float fDirectionalCosineX,
									const float fDirectionalCosineY,
									const float fDirectionalCosineZ);

		/// @see SetSourceOrientation
		bool GetSourceOrientation(	float &fDirectionalCosineX, 
									float &fDirectionalCosineY, 
									float &fDirectionalCosineZ)const;

		/// @see SetOrientation
		/// @return true if orientation is set
		bool HasSourceOrientation()const;

		/// @see SetOrientation
		/// Delete orientation
		void DeleteSourceOrientation();

		/// Source Position : Tag (4010, 1061), VM = 3, VR = FL [optional]
		bool SetSourcePosition(	const float fPositionX, 
								const float fPositionY, 
								const float fPositionZ);
		/// @see SetSourcePosition
		bool GetSourcePosition(	float &fPositionX, 
								float &fPositionY, 
								float &fPositionZ)const;

		/// @see SetSourcePosition
		/// @return true if source position is set
		bool HasSourcePosition()const;

		/// @see SetSourcePosition
		/// Delete source position
		void DeleteSourcePosition();

	protected:
		class ImplGeometryItem;
		ImplGeometryItem	*m_pImplGeometryItem; ///< Internal implementation
	};

	///
	/// Initialize the class attributes from the given AttributeManager
	///
	/// @param attribManager 	Attribute Manager that contains the module's attributes
	/// @param errorlog 	 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is missing or invalid
	///
	virtual bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Copy the attributes from the module into the given AttributeManager
	///
	/// @param attribManager 	AttributeManager to store the module's attributes
	/// @param errorlog		 	Report missing required attributes
	/// @return true/false		false is returned if any required attribute is not present.
	///
	virtual bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog)const;

	///
	/// Set all required and optional attributes from the given AttributeManager
	///
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false if IsValid() returned false
	///
	virtual bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	///
	/// Determine if all needed attributes (required and conditionally required) are set.
	///
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	///
	virtual bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog)const;

	/// Detector Geometry Sequence : Tag (4010, 0004), VR = SQ [optional]
	bool SetSequence(const Array1D<GeometryItem> &arrayDetectorGeometry);
	/// @see SetSequence
	bool GetSequence(Array1D<GeometryItem> &arrayDetectorGeometry)const;
	/// @see SetSequence
	Array1D<GeometryItem>& GetSequence();
	/// @see SetSequence
	const Array1D<GeometryItem>& GetSequence()const;

protected:
	class ImplDetectorGeometry;
	ImplDetectorGeometry	*m_pImplDetectorGeometry; ///< Internal implementation
};

}//namespace DXTypes
}//namespace SDICOS

#endif
