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
#ifndef STRATOVAN_DICOS_TEMPLATE_CLASSES_COMMON_H_
#define STRATOVAN_DICOS_TEMPLATE_CLASSES_COMMON_H_

#include "SDICOS/ImagePixelModule.h"
#include "SDICOS/Point3D.h"
#include "SDICOS/Vector3D.h"
#include "SDICOS/MemoryPolicy.h"
#include "SDICOS/Volume.h"

namespace SDICOS
{

///
/// \class SectionCommon
/// \brief Attributes Common to all types of scan data
///
class SectionCommon
{
public:
	/// Constructor
	SectionCommon();
		
	/// Construct with an identifier
	SectionCommon(const S_UINT32 sectionId);

	/// Copy constructor
	/// Note that SectionId is not copied.
	SectionCommon(const SectionCommon &sec);

	/// Destructor
	virtual ~SectionCommon();

	/// Reset to default values
	virtual void FreeMemory();

	/// Copy operator
	/// Note that SectionId is not copied
	SectionCommon& operator=(const SectionCommon &sec);
	/// Comparison operator
	bool operator==(const SectionCommon &sec)const;
	/// Comparison operator
	bool operator!=(const SectionCommon &section)const;

	/// Set a unique identifier for the section. Defaults to 0.
	/// This is not part of the DICOS file but available for users to identify volume sections at runtime.
	void SetSectionId(const SDICOS::S_UINT32 sectionId);

	/// Get a unique identifier for this section.
	/// @return Section Id set during construction or with SetSectionId()
	SDICOS::S_UINT32 GetSectionId() const;

	/// Set the memory allocation policy for the Section to indicate whether or not the Section's
	/// volume data object is responsible for deleting its slices.
	/// This is a convenience function around GetPixelData().SetMemoryPolicy()
	/// Slices added to the volume using Volume16Bit::AddSignedSlice() or Volume16Bit::AddUnsignedSlice())
	/// are governed by this memory policy.
	/// @param memoryPolicy Memory Allocation and Deletion Policy
	void SetMemoryPolicy(const SDICOS::MemoryPolicy::VOLUME_MEMORY_POLICY memoryPolicy);

	/// CT and AIT3D Pixel data can be signed/unsigned 8/16/34/64-bit integer or float
	Volume& GetPixelData();
	const Volume& GetPixelData()const;

	/// Returns the pixel data's type
	Volume::IMAGE_DATA_TYPE GetPixelDataType() const;

	/// Get the width of the volume
	SDICOS::S_UINT32 GetWidth() const;

	/// Get the height of the volume
	SDICOS::S_UINT32 GetHeight() const;

	/// Get the depth (number of slices) in the volume.
	SDICOS::S_UINT32 GetDepth() const;

	/// Convenience method that returns Width*Depth
	SDICOS::S_UINT32 GetSliceSize() const;

	/// Get the number of bytes in a slice
	S_UINT32 GetSliceSizeInBytes() const;

	/// Pixel data spacing in mm.
	/// Default value set to (1,1,1)
	void SetSpacingInMM(const float fColumn, const float fRow, const float fSlice);
	/// @see SetSpacingInMM
	float GetRowSpacing()const;
	/// @see SetSpacingInMM
	float GetColumnSpacing()const;
	/// @see SetSpacingInMM
	float GetSliceSpacing()const;
	/// Get spacing in the format (Column Spacing, Row Spacing, Slice Spacing)
	const Point3D<float>& GetSpacingInMM()const;

	/// Set slice thickness
	void SetSliceThickness(const float fSliceThickness);
	/// @see SetSliceThickness
	float GetSliceThickness()const;

	/// Top left coordinate of first frame in pixel data.  Set Z coordinate to 0 for 2D images.
	/// Default value set to (0,0,0)
	void SetPositionInMM(const Point3D<float> &pt);
	
	/// Top left coordinate of first frame in pixel data.  Set Z coordinate to 0 for 2D images.
	/// Default value set to (0,0,0)
	void SetPositionInMM(const float fX, const float fY, const float fZ);
	
	/// @see SetPositionInMM
	const Point3D<float>& GetPositionInMM()const;
	
	/// @see GetPositionInMM
	float GetXPosition() const;
	/// @see GetPositionInMM
	float GetYPosition() const;
	/// @see GetPositionInMM
	float GetZPosition() const;
	
	/// Set scanning plane's directional cosines
	/// @param ptRowOrientation The physical space direction vector for traversing a row of voxels in increasing order. Default is (1,0,0)
	/// @param ptColumnOrientation The physical space direction vector for traversing a column of voxels in increasing order. Default is (0,1,0)
	void SetPlaneOrientation(const Vector3D<float> &ptRowOrientation, const Vector3D<float> &ptColumnOrientation);	
	/// @see SetPlaneOrientation
	const Vector3D<float>& GetRowOrientation()const;
	/// @see SetPlaneOrientation
	const Vector3D<float>& GetColumnOrientation()const;

	/// Set which direction along the slice orientation vector, determined by left hand coordinate's
	/// RowOrientation X ColumnOrientation, the slices are stacked.
	/// bPositive = true: Slices follow the RowOrientation X ColumnOrientation direction (i.e. Volume[nSlice] follows the positioning (RowOrientation X ColumnOrientation) * nSlice * Spacing)
	/// bPositive = false: Slices follow the -(RowOrientation X ColumnOrientation) direction. (i.e. Volume[nSlice] follows the positioning -(RowOrientation X ColumnOrientation) * nSlice * Spacing)
	/// Default is positive.
	/// @see SetPlaneOrientation
	void SetSlicingDirection(const bool bPositive);
	/// Returns true if volume slices follow the RowOrientation X ColumnOrientation direction.
	/// Ex. Volume[nSlice] follows the positioning (RowOrientation X ColumnOrientation) * nSlice * Spacing
	bool IsSlicingDirection()const;
	/// Returns true if slices follow the -(RowOrientation X ColumnOrientation) direction.
	/// Ex. Volume[nSlice] follows the positioning -(RowOrientation X ColumnOrientation) * nSlice * Spacing
	bool IsOppositeSlicingDirection()const;

	/// Compare two sections using the Z component of their position
	/// @return true/false true if psectionA.z > psectionB.z
	static bool CmpSectionsByZPosition(const SectionCommon* psectionA, const SectionCommon* psectionB);
private:
	class SectionCommonImpl;
	SectionCommonImpl *m_pSectionCommonImpl;
};

}//namespace SDICOS

#endif