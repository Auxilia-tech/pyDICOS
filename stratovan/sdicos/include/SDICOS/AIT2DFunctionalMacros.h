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
#ifndef _STRATOVAN_DICOS_AIT_2D_FUNCTIONAL_MACROS_H_
#define _STRATOVAN_DICOS_AIT_2D_FUNCTIONAL_MACROS_H_

#include "SDICOS/PixelMeasurement.h"
#include "SDICOS/RealWorldValueMapping.h"
#include "SDICOS/PlaneOrientationAIT.h"
#include "SDICOS/PlanePosition.h"

namespace SDICOS
{
namespace AIT2DTypes
{

///
/// \class AIT2DFunctionalMacros
/// Implementation of 2D AIT Functional Macros used in 2D AIT IOD Modules
/// SPECREF V03 Section 9.2.3.3, Table 44
///
class AIT2DFunctionalMacros
{
public:
	/// Constructor
	AIT2DFunctionalMacros();
	
	/// Copy Constructor
	AIT2DFunctionalMacros(const AIT2DFunctionalMacros &macros);
	
	/// Destructor
	~AIT2DFunctionalMacros();

	/// Delete allocated resources
	void FreeMemory();

	/// Assignment operator
	AIT2DFunctionalMacros& operator=(const AIT2DFunctionalMacros &macros);
	
	/// equality comparison operator
	bool operator==(const AIT2DFunctionalMacros &macros)const;
	
	/// Inequality comparison operator
	bool operator!=(const AIT2DFunctionalMacros &macros)const;
	
	/// Initialize the class attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not fetched
	///							or if some were invalid.
	bool SetAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Copy the attributes from the module into the given AttributeManager
	/// @param attribManager	AttributeManager to store the module's attributes
	/// @param errorlog			Report missing required attributes
	/// @return true/false		false is returned if all required attributes were not uploaded.
	bool GetAttributes(AttributeManager &attribManager, ErrorLog &errorlog) const;

	/// Attempt to set all required and optional attributes from the given AttributeManager
	/// @param attribManager	Attribute Manager that contains the module's attributes
	/// @param errorlog			Report found attributes where IsValid() returns false
	/// @return true/false		false is returned if attributes were specified or if some were invalid.
	bool UpdateAttributes(const AttributeManager &attribManager, ErrorLog &errorlog);

	/// Determine if all needed attributes (required and conditionally required) are set
	/// @param attribManager	AttributeManager used to check dependencies
	/// @param errorlog			ErrorLog used to report errors
	/// @return true/false
	bool IsValid(const AttributeManager &attribManager, ErrorLog &errorlog) const;
	
	/// Set Pixel Measurement [required]
	bool SetPixelMeasurement(const PixelMeasurement &pixelmeasurement);
	
	/// @see SetPixelMeasurement
	bool GetPixelMeasurement(PixelMeasurement &pixelmeasurement)const;
	
	/// @see SetPixelMeasurement
	PixelMeasurement& GetPixelMeasurement();
	
	/// @see SetPixelMeasurement
	const PixelMeasurement& GetPixelMeasurement() const;
	
	/// Set Plane Position [required]
	bool SetPlanePosition(const PlanePosition &planeposition);
	
	/// @see SetPlanePosition
	bool GetPlanePosition(PlanePosition &planeposition)const;
	
	/// @see SetPlanePosition
	PlanePosition& GetPlanePosition();
	
	/// @see SetPlanePosition
	const PlanePosition& GetPlanePosition() const;
	
	/// Set AIT Plane Orientation [required]
	bool SetAitPlaneOrientation(const AitPlaneOrientation &aitplaneorientation);
	
	/// @see SetAitPlaneOrientation
	bool GetAitPlaneOrientation(AitPlaneOrientation &aitplaneorientation)const;
	
	/// @see SetAitPlaneOrientation
	AitPlaneOrientation& GetAitPlaneOrientation();
	
	/// @see SetAitPlaneOrientation
	const AitPlaneOrientation& GetAitPlaneOrientation() const;
	
	/// Set Real World Value Mapping [optional]
	bool SetRealWorldValueMapping(const RealWorldValueMappingSequence &realworldvaluemappingsequence);
	
	/// @see SetRealWorldValueMapping
	bool GetRealWorldValueMapping(RealWorldValueMappingSequence &realworldvaluemappingsequence)const;

	/// @see SetRealWorldValueMapping
	RealWorldValueMappingSequence& GetRealWorldValueMapping();
	
	/// @see SetRealWorldValueMapping
	const RealWorldValueMappingSequence& GetRealWorldValueMapping() const;
	
	/// Delete attribute so that it is not written to the DICOS file
	void DeleteRealWorldValueMapping();
	
	/// Check if the Real World Value Mapping Sequence has been set
	bool IsRealWorldValueMappingSet() const;
protected:
	class ImplAIT2DFunctionalMacros;
	ImplAIT2DFunctionalMacros	*m_pImplAIT2DFunctionalMacros; ///< Internal implementation
	
	ImplAIT2DFunctionalMacros* GetImpl();
	const ImplAIT2DFunctionalMacros* GetImpl() const;
};

}//namespace AIT2DTypes
}//namespace SDICOS

#endif
