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
#ifndef _STRATOVAN_DICOS_DX_POSITIONING_H_
#define _STRATOVAN_DICOS_DX_POSITIONING_H_

#include "SDICOS/DetectorGeometry.h"

namespace SDICOS
{
namespace DXTypes
{

///
/// \class DXPositioning
/// \brief Implements DX/X-Ray Positioning
/// SPECREF V03 Section 8.2.2.4, Table 37
///
class DXPositioning
{
public:
	/// Constructor
	DXPositioning();
	/// Copy constructor
	DXPositioning(const DXPositioning &pos);
	/// Destructor
	virtual ~DXPositioning();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	DXPositioning& operator=(const DXPositioning &pos);
	/// Comparison operator
	bool operator==(const DXPositioning &pos)const;
	/// Comparison operator
	bool operator!=(const DXPositioning &pos)const;

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

	/// Belt Speed in mm/sec : Tag (0018, 9309), VR = FD [required]
	bool SetBeltSpeed(const double fBeltSpeed);
	/// @see SetBeltSpeed
	double GetBeltSpeed()const;

	/// Belt Height in mm relative to the coordinate system's origin : Tag (4010, 1062), VR = FL [required]
	bool SetBeltHeight(const float fBeltHeight);
	/// @see SetBeltHeight
	float GetBeltHeight()const;

	/// Detector Geometry Sequence : Tag (4010, 0004), VR = SQ [optional]
	bool SetDetectorGeometrySequence(const DetectorGeometry &dg);
	/// @see SetDetectorGeometrySequence
	bool GetDetectorGeometrySequence(DetectorGeometry &dg)const;
	/// @see SetDetectorGeometrySequence
	DetectorGeometry& GetDetectorGeometrySequence();
	/// @see SetDetectorGeometrySequence
	const DetectorGeometry& GetDetectorGeometrySequence()const;
	/// Determine if the Detector Geometry Sequence is set
	/// @return true if the sequence is set
	bool HasDetectorGeometrySequence()const;
	/// Delete the Detector Geometry Sequence and its internals
	void DeleteDetectorGeometrySequence();

protected:
	class ImplDXPositioning;
	ImplDXPositioning	*m_pImplDXPositioning; ///< Internal implementation
};

}//namespace DXTypes
}//namespace SDICOS

#endif
