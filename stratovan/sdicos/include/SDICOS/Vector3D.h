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
#ifndef S_STRATOVAN_DICOS_VECTOR_3D_H__
#define S_STRATOVAN_DICOS_VECTOR_3D_H__

#include "SDICOS/Point3D.h"
#include "SDICOS/ToolsLight.h"

namespace SDICOS
{

template< class CType >
class Vector3D : public Point3D< CType >
{
public:
	typedef Vector3D<CType>		ThisClass;
	typedef Point3D<CType>		ParentClass;

	Vector3D(CType cx = 0, CType cy = 0, CType cz = 0) : ParentClass(cx, cy, cz) {}
	Vector3D(const CType pBuf[3]) : ParentClass(pBuf[0], pBuf[1], pBuf[2]) {}
	Vector3D(const ParentClass &rhs) : ParentClass(rhs) {}

	template <typename NEW_TYPE>
	Vector3D<NEW_TYPE> Cast()const
	{
		return Vector3D<NEW_TYPE>( NEW_TYPE(ParentClass::x), NEW_TYPE(ParentClass::y), NEW_TYPE(ParentClass::z) );
	}

	ThisClass& operator=(const ParentClass &rhs)		{ ParentClass::operator=(rhs); return *this; }

	inline bool operator== (const ThisClass &rhs)const		{return ParentClass::operator==(rhs);}
	inline bool operator!= (const ThisClass &rhs)const		{return ParentClass::operator!=(rhs);}

	inline CType Magnitude()const
	{
		return Sqrt(ParentClass::x*ParentClass::x + ParentClass::y*ParentClass::y + ParentClass::z*ParentClass::z);
	}
	inline CType MagnitudeSquared()const
	{
		return (ParentClass::x*ParentClass::x + ParentClass::y*ParentClass::y + ParentClass::z*ParentClass::z);
	}

	inline void Normalize(CType fWorkingRange = GetDefaultWorkingRange<CType>())	// Specialized below for: float, double, and long double
	{
		CType Mag = Magnitude();
		//ASSERT(0 != Mag);
		if(IsNotZero(Mag, fWorkingRange))
		{
			Mag = CType(1) / Mag;
			ParentClass::x *= Mag;
			ParentClass::y *= Mag;
			ParentClass::z *= Mag;
		}
	}

	// Returns the cosine of the angle between this vector and vB.
	// Use acos(CosOfAngle(vB)) to obtain the angle between the two vectors.
	inline CType CosOfAngle(const ThisClass &vB)const
	{
		const ThisClass &vA = *this;
		CType fVal = (CType)(vA.x*vB.x+vA.y*vB.y+vA.z*vB.z)/(Sqrt((vA.x*vA.x+vA.y*vA.y+vA.z*vA.z)*(vB.x*vB.x+vB.y*vB.y+vB.z*vB.z)));
		return Clamp(fVal, CType(-1), CType(1));
	}

	inline CType SinOfAngle(const ThisClass &vB)const
	{
		const ThisClass &vA = *this;
		ThisClass		vC;
		vC.SetAsACrossB(vA, vB);
		return vC.Magnitude() / (Sqrt((vA.x*vA.x+vA.y*vA.y+vA.z*vA.z)*(vB.x*vB.x+vB.y*vB.y+vB.z*vB.z)));
	}

	// Returns the dot product between this vector and vB.
	inline CType Dot(const ThisClass &vB)const
	{
		const ThisClass &vA = *this;
		return (vA.x*vB.x + vA.y*vB.y + vA.z*vB.z);
	}

	// Sets this vector to the normal of the points pt1, pt2, pt3.
	inline void SetAsNormal(	const ParentClass &pt1,
								const ParentClass &pt2,
								const ParentClass &pt3)
	{
		ThisClass vA, vB;
		vA = pt2 - pt1;
		vB = pt3 - pt1;
		SetAsACrossB(vA, vB);
	}

	// Sets this vector to the vA crossed with vB.
	inline void SetAsACrossB(const ThisClass &vA, const ThisClass &vB)
	{
		ParentClass::x = vA.y*vB.z - vA.z*vB.y;
		ParentClass::y = vA.z*vB.x - vA.x*vB.z;
		ParentClass::z = vA.x*vB.y - vA.y*vB.x;
	}

	// Returns the projection multiplier for the projection of A onto B.
	inline CType ProjectionMultiplier(const ThisClass &vB)const
						{
							const ThisClass &vA = *this;
							return vA.Dot(vB) / vB.MagnitudeSquared();
						}

	// Sets this vector to the projection of A onto B.
	inline void SetAsProjection(const ThisClass &vA, const ThisClass &vB)
						{
							CType fVal = vA.ProjectionMultiplier(vB);
							ParentClass::x = vB.x * fVal;
							ParentClass::y = vB.y * fVal;
							ParentClass::z = vB.z * fVal;
						}

	inline ThisClass	ProjectToXY()const	{return ThisClass(ParentClass::x, ParentClass::y, 0);}
	inline ThisClass	ProjectToXZ()const	{return ThisClass(ParentClass::x, 0, ParentClass::z);}
	inline ThisClass	ProjectToYZ()const	{return ThisClass(0, ParentClass::y, ParentClass::z);}

	inline bool HasZeroMagnitude()const	{ return SDICOS::IsZero( MagnitudeSquared() ); }

};

}//namespace SDICOS

#endif