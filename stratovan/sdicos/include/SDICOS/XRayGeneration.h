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
#ifndef _STRATOVAN_DICOS_DX_XRAY_GENERATION_H_
#define _STRATOVAN_DICOS_DX_XRAY_GENERATION_H_

#include "SDICOS/Attribute.h"
#include "SDICOS/Vector3D.h"

namespace SDICOS
{
namespace DXTypes
{

///
/// \class XRayGeneration
/// \brief Implements X-Ray Generation
/// SPECREF V03 Section 8.2.2.5, Table 38
///
class XRayGeneration
{
public:
	/// Constructor
	XRayGeneration();
	/// Copy constructor
	XRayGeneration(const XRayGeneration &xrgen);
	/// Destructor
	virtual ~XRayGeneration();

	/// Reset to default values
	void FreeMemory();

	/// Copy operator
	XRayGeneration& operator=(const XRayGeneration &xrgen);
	/// Comparison operator
	bool operator==(const XRayGeneration &xrgen)const;
	/// Comparison operator
	bool operator!=(const XRayGeneration &xrgen)const;

	/// Exposure Control Mode enumerations
	typedef enum
	{
		enumUnknownExposureControlMode,	///< Unknown enumeration

		enumManual,		///< "MANUAL"
		enumAutomatic,	///< "AUTOMATIC"

	}EXPOSURE_CONTROL_MODE;

	/// Exposure Status enumerations
	typedef enum
	{
		enumUnknownExposureStatus,	///< Unknown enumeration

		enumNormal,		///< "NORMAL"
		enumAborted,	///< "ABORTED"

	}EXPOSURE_STATUS;

	/// Anode Target Material enumerations
	typedef enum
	{
		enumUnknownAnodeTargetMaterial,	///< Unknown enumeration

		enumTungsten,		///< "TUNGSTEN"
		enumMolybdenum,		///< "MOLYBDENUM"
		enumRhodium,		///< "RHODIUM"

	}ANODE_TARGET_MATERIAL;

	/// Rectification Type enumerations
	typedef enum
	{
		enumUnknownRectificationType,	///< Unknown enumeration

		enumSinglePhase,	///< "SINGLE PHASE"
		enumThreePhase,		///< "THREE PHASE"
		enumConstPotential,	///< "CONST POTENTIAL"

	}RECTIFICATION_TYPE;

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

	/// KVP : Tag (0018, 0060), VR = DS [required]
	bool SetKVP(const float fKVP);
	/// @see SetKVP
	float GetKVP()const;
	/// @see SetKVP
	DcsString GetKVPAsString()const;

	///
	/// Image Orientation : Tag (0020, 0037), VM = 6, VR = DS [required]
	///		a) Param 1-3, Direction Cosines for first row 
	///		b) Param 4-6, Direction Cosines for first column
	///
	bool SetImageOrientation(	const float fDirectionCosinesRowX,
								const float fDirectionCosinesRowY,
								const float fDirectionCosinesRowZ,

								const float fDirectionCosinesColumnX,
								const float fDirectionCosinesColumnY,
								const float fDirectionCosinesColumnZ);

	/// @see SetImageOrientation
	bool SetImageOrientation(const Vector3D<float>& ptRowOrientation, const Vector3D<float>& ptColumnOrientation);

	/// @see SetImageOrientation
	bool GetImageOrientation(	float &fDirectionCosinesRowX,
								float &fDirectionCosinesRowY,
								float &fDirectionCosinesRowZ,

								float &fDirectionCosinesColumnX,
								float &fDirectionCosinesColumnY,
								float &fDirectionCosinesColumnZ) const;
	/// @see SetImageOrientation
	bool GetImageRowOrientation(float& fDirectionCosinesRowX,
								float& fDirectionCosinesRowY,
								float& fDirectionCosinesRowZ) const;
	/// @see SetImageOrientation
	bool GetImageColumnOrientation(	float& fDirectionCosinesColumnX,
									float& fDirectionCosinesColumnY,
									float& fDirectionCosinesColumnZ) const;
	/// @see SetImageOrientation
	bool GetImageOrientation(	DcsString &strDirectionCosinesRowX,
								DcsString &strDirectionCosinesRowY,
								DcsString &strDirectionCosinesRowZ,

								DcsString &strDirectionCosinesColumnX,
								DcsString &strDirectionCosinesColumnY,
								DcsString &strDirectionCosinesColumnZ) const;

	/// @see SetImageOrientation
	Vector3D<float> GetRowOrientation() const;

	/// @see SetImageOrientation
	Vector3D<float> GetColumnOrientation() const;

	/// Image Position in MM (center of top left voxel) : Tag (0020, 0032), VM = 3, VR = DS [required]
	bool SetImagePosition(const float fX, const float fY, const float fZ);
	/// @see SetImagePosition
	bool SetImagePosition(const SDICOS::Point3D<float>& pos);
	/// @see SetImagePosition
	bool GetImagePosition(float &fX, float &fY, float &fZ) const;
	/// @see SetImagePosition
	bool GetImagePosition(DcsString &strX, DcsString &strY, DcsString &strZ) const;
	/// @see SetImagePosition
	SDICOS::Point3D<float> GetImagePosition() const;

	/// X-Ray Tube Current in uA : Tag (0018, 8151), VR = DS [required]
	bool SetXRayTubeCurrent(const float fCurrent);
	/// @see SetXRayTubeCurrent
	float GetXRayTubeCurrent()const;
	/// @see SetXRayTubeCurrent
	DcsString GetXRayTubeCurrentAsString()const;

	/// Exposure Time in uS : Tag (0018, 8150), VR = DS [optional]
	bool SetExposureTime(const float fTime);
	/// @see SetExposureTime
	float GetExposureTime()const;
	/// @see SetExposureTime
	DcsString GetExposureTimeAsString()const;
	/// Delete Exposure Time
	void DeleteExposureTime();

	/// Exposure in uA*s : Tag (0018, 1153), VR = IS [optional]
	bool SetExposure(const S_INT32 nExposure);
	/// @see SetExposure
	S_INT32 GetExposure()const;
	/// @see SetExposure
	DcsString GetExposureAsString()const;
	/// Delete Exposure
	void DeleteExposure();

	/// Exposure Control Mode : Tag (0018, 7060), VR = CS [optional]
	bool SetExposureControlMode(const EXPOSURE_CONTROL_MODE nMode);
	/// @see SetExposureControlMode
	EXPOSURE_CONTROL_MODE GetExposureControlMode() const;
	/// @see SetExposureControlMode
	DcsString GetExposureControlModeAsString() const;
	/// Delete Exposure Control Mode
	void DeleteExposureControlMode();

	/// Exposure Control Mode Description : Tag (0018, 7062), VR = LT [optional]
	bool SetExposureControlModeDescription(const DcsLongText &strDescription);
	/// @see SetExposureControlModeDescription
	DcsString GetExposureControlModeDescription()const;
	/// Delete Exposure Control Mode Description
	void DeleteExposureControlModeDescription();

	/// Exposure Status : Tag (0018, 7064), VR = CS [optional]
	bool SetExposureStatus(const EXPOSURE_STATUS nStatus);
	/// @see SetExposureStatus
	EXPOSURE_STATUS GetExposureStatus()const;
	/// @see SetExposureStatus
	DcsString GetExposureStatusAsString()const;
	/// Delete Exposure Status
	void DeleteExposureStatus();

	/// Phototimer Setting : Tag (0018, 7065), VR = DS [optional]
	///	@param fSetting Positive percentage = more exposure, Negative percantage = less exposure
	bool SetPhototimerSetting(const float fSetting);
	/// @see SetPhototimerSetting
	float GetPhototimerSetting()const;
	/// @see SetPhototimerSetting
	DcsString GetPhototimerSettingAsString()const;
	/// Delete Phototimer Setting
	void DeletePhototimerSetting();

	/// Focal Nominal Spot Size in mm : Tag (0018, 1190), VR = DS [optional]
	bool SetFocalNominalSpotSize(const Array1D<float> &arrayFocalSpotSize);
	/// @see SetFocalNominalSpotSize
	bool GetFocalNominalSpotSize(Array1D<float> &arrayFocalSpotSize)const;
	/// @see SetFocalNominalSpotSize
	bool GetFocalNominalSpotSize(Array1D<DcsString> &arrayFocalSpotSize)const;
	/// Delete Focal Nominal Spot Size
	void DeleteFocalNominalSpotSize();

	/// Anode Target Material : Tag (0018, 1191), VR = CS [optional]
	bool SetAnodeTargetMaterial(const ANODE_TARGET_MATERIAL nMaterial);
	/// @see SetAnodeTargetMaterial
	ANODE_TARGET_MATERIAL GetAnodeTargetMaterial()const;
	/// @see SetAnodeTargetMaterial
	DcsString GetAnodeTargetMaterialAsString()const;
	/// Delete Anode Target Material
	void DeleteAnodeTargetMaterial();

	/// Rectification Type : Tag (0018, 1156), VR = CS [optional]
	bool SetRectificationType(const RECTIFICATION_TYPE nType);
	/// @see SetRectificationType
	RECTIFICATION_TYPE GetRectificationType()const;
	/// @see SetRectificationType
	DcsString GetRectificationTypeAsString()const;
	/// Delete Rectification Type
	void DeleteRectificationType();

	/// Generator ID : Tag (0018, 1005), VR = LO [optional]
	bool SetGeneratorID(const DcsLongString &strID);
	/// @see SetGeneratorID
	DcsString GetGeneratorID()const;
	/// Delete Generator ID
	void DeleteGeneratorID();

protected:
	class ImplXRayGeneration;
	ImplXRayGeneration	*m_pImplXRayGeneration; ///< Internal implementation
};

}//namespace DXTypes
}//namespace SDICOS

#endif