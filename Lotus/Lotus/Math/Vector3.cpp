/********************************************************************
	created:	2012/08/14 
	filename: 	Vector.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "Vector3.h"
#include "Quaternion.h"

namespace Lotus 
{
	const Vector3 Vector3::ZERO( 0, 0, 0 );
	const Vector3 Vector3::UNIT_X( 1, 0, 0 );
	const Vector3 Vector3::UNIT_Y( 0, 1, 0 );
	const Vector3 Vector3::UNIT_Z( 0, 0, 1 );
	const Vector3 Vector3::NEGATIVE_UNIT_X( -1,  0,  0 );
	const Vector3 Vector3::NEGATIVE_UNIT_Y(  0, -1,  0 );
	const Vector3 Vector3::NEGATIVE_UNIT_Z(  0,  0, -1 );
	const Vector3 Vector3::UNIT_SCALE(1, 1, 1);

	Quaternion Vector3::getRotationTo(const Vector3& dest, const Vector3& fallbackAxis)  const
	{
		// Based on Stan Melax's article in Game Programming Gems
		Quaternion q;
		// Copy, since cannot modify local
		Vector3 v0 = *this;
		Vector3 v1 = dest;
		v0.normalize();
		v1.normalize();

		float d = v0*v1;
		// If dot == 1, vectors are the same
		if (d >= 1.0f)
		{
			return Quaternion::IDENTITY;
		}
		if (d < (1e-6f - 1.0f))
		{
			if (fallbackAxis != Vector3::ZERO)
			{
				// rotate 180 degrees about the fallback axis
				q.fromAngleAxis(Radian(Math::PI), fallbackAxis);
			}
			else
			{
				// Generate an axis
				Vector3 axis =cross(UNIT_X, *this);
				if (axis.isZeroLength()) // pick another if colinear
					axis = cross(UNIT_Y, *this);
				axis.normalize();
				q.fromAngleAxis(Radian(Math::PI), axis);
			}
		}
		else
		{
			float s = Math::sqrt( (1+d)*2 );
			float invs = 1 / s;

			Vector3 c = cross(v0, v1);

			q.x = c.x * invs;
			q.y = c.y * invs;
			q.z = c.z * invs;
			q.w = s * 0.5f;
			q.normalize();
		}
		return q;
	}
}

