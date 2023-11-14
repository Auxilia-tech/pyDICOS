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
#ifndef _STRATOVAN_DICOS_POINT3D_H_
#define _STRATOVAN_DICOS_POINT3D_H_

#include "SDICOS/ToolsLight.h"

namespace SDICOS
{

template< class CType >
class Point3D
{
public:
	typedef Point3D<CType> ThisClass;

	Point3D(CType cx = 0, CType cy = 0, CType cz = 0) : x(cx), y(cy), z(cz) {}
	Point3D(const CType pBuf[3]) : x(pBuf[0]), y(pBuf[1]), z(pBuf[2]) {}
	Point3D(const ThisClass& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

	inline void Set(CType cx, CType cy, CType cz)
	{
		x = cx;
		y = cy;
		z = cz;
	}

	template <typename NEW_TYPE>
	Point3D<NEW_TYPE> Cast()const
	{
		return Point3D<NEW_TYPE>( NEW_TYPE(x), NEW_TYPE(y), NEW_TYPE(z) );
	}

	inline bool operator== (const ThisClass &rhs)const		{return IsEqual(x, rhs.x) && IsEqual(y, rhs.y) && IsEqual(z, rhs.z);}
	inline bool operator!= (const ThisClass &rhs)const		{return IsNotEqual(x, rhs.x) || IsNotEqual(y, rhs.y) || IsNotEqual(z, rhs.z);}

	ThisClass&			operator=	(const ThisClass	&pt)		{	x = pt.x;		y = pt.y;		z = pt.z;		return *this;}
	ThisClass			operator+	(ThisClass			pt)const	{	pt.x+=x;		pt.y+=y;		pt.z+=z;		return pt;}
	ThisClass			operator-	(ThisClass			pt)const	{	pt.x=x-pt.x;	pt.y=y-pt.y;	pt.z=z-pt.z;	return pt;}
	ThisClass&			operator+=	(const ThisClass	&pt)		{	x+=pt.x;		y+=pt.y;		z+=pt.z;		return *this;}
	ThisClass&			operator-=	(const ThisClass	&pt)		{	x-=pt.x;		y-=pt.y;		z-=pt.z;		return *this;}
	ThisClass			operator*	(CType a)const					{	ThisClass pt(*this);	pt.x*=a;		pt.y*=a;		pt.z*=a;	return pt;}
	friend ThisClass	operator*	(CType a, ThisClass pt)			{	pt.x*=a;		pt.y*=a;		pt.z*=a;							return pt;}
	ThisClass			operator/	(CType a)const					{	ThisClass pt(*this); pt.x/=a; pt.y/=a; pt.z/=a;						return pt;}
	ThisClass&			operator*=	(CType a)						{	x*=a;			y*=a;			z*=a;								return *this;}
	ThisClass&			operator/=	(CType a)						{	x/=a;		y/=a;			z/=a;									return *this;}

	ThisClass			operator*	(const ThisClass &A)const
	{
		ThisClass pt(*this);
		pt.x*=A.x;
		pt.y*=A.y;
		pt.z*=A.z;
		return pt;
	}
	ThisClass			operator/	(const ThisClass &A)const
	{
		ThisClass pt(*this);
		pt.x/=A.x;
		pt.y/=A.y;
		pt.z/=A.z;
		return pt;
	}
	ThisClass			operator*=	(const ThisClass &A)
	{
		x*=A.x;
		y*=A.y;
		z*=A.z;
		return *this;
	}
	ThisClass			operator/=	(const ThisClass &A)
	{
		x/=A.x;
		y/=A.y;
		z/=A.z;
		return *this;
	}
	ThisClass			operator-	()const
	{
		ThisClass pt(*this);
		pt.x*=CType(-1);
		pt.y*=CType(-1);
		pt.z*=CType(-1);
		return pt;
	}

	bool IsZero() const
	{
		return (SDICOS::IsZero(x) && SDICOS::IsZero(y) && SDICOS::IsZero(z));
	}

	CType	x, y, z;
};

}//namespace SDICOS

#endif
