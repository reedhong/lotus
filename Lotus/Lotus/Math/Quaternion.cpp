/********************************************************************
	created:	2012/08/23 
	filename: 	Quaternion.cpp
	author:		reedhong 
	
	purpose:	四元数
*********************************************************************/

#include "Quaternion.h"

namespace Lotus {
	const Quaternion Quaternion::ZERO(0,0,0,0);
	const Quaternion Quaternion::IDENTITY(1,0,0,0);

	Quaternion Quaternion::Exp () const
	{
		// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
		// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
		// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

		Radian fAngle ( Math::sqrt(x*x+y*y+z*z) );
		float fSin = Math::sin(fAngle.valueRadians());

		Quaternion kResult;
		kResult.w = Math::cos(fAngle.valueRadians());

		if ( Math::fabs(fSin) >= Math::EPSINON )
		{
			float fCoeff = fSin/(fAngle.valueRadians());
			kResult.x = fCoeff*x;
			kResult.y = fCoeff*y;
			kResult.z = fCoeff*z;
		}
		else
		{
			kResult.x = x;
			kResult.y = y;
			kResult.z = z;
		}

		return kResult;
	}

	Quaternion Quaternion::Log () const
	{
		// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
		// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
		// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

		Quaternion kResult;
		kResult.w = 0.0;

		if ( Math::fabs(w) < 1.0 )
		{
			Radian fAngle ( Math::acos(w) );
			float fSin = Math::sin(fAngle.valueRadians());
			if ( Math::fabs(fSin) >= Math::EPSINON )
			{
				float fCoeff = fAngle.valueRadians()/fSin;
				kResult.x = fCoeff*x;
				kResult.y = fCoeff*y;
				kResult.z = fCoeff*z;
				return kResult;
			}
		}

		kResult.x = x;
		kResult.y = y;
		kResult.z = z;

		return kResult;
	}


	Vector3 Quaternion::xAxis(void) const
	{
		float fTy  = 2.0f*y;
		float fTz  = 2.0f*z;
		float fTwy = fTy*w;
		float fTwz = fTz*w;
		float fTxy = fTy*x;
		float fTxz = fTz*x;
		float fTyy = fTy*y;
		float fTzz = fTz*z;

		return Vector3(1.0f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
	}

	Vector3 Quaternion::yAxis(void) const
	{
		float fTx  = 2.0f*x;
		float fTy  = 2.0f*y;
		float fTz  = 2.0f*z;
		float fTwx = fTx*w;
		float fTwz = fTz*w;
		float fTxx = fTx*x;
		float fTxy = fTy*x;
		float fTyz = fTz*y;
		float fTzz = fTz*z;

		return Vector3(fTxy-fTwz, 1.0f-(fTxx+fTzz), fTyz+fTwx);
	}

	Vector3 Quaternion::zAxis(void) const
	{
		float fTx  = 2.0f*x;
		float fTy  = 2.0f*y;
		float fTz  = 2.0f*z;
		float fTwx = fTx*w;
		float fTwy = fTy*w;
		float fTxx = fTx*x;
		float fTxz = fTz*x;
		float fTyy = fTy*y;
		float fTyz = fTz*y;

		return Vector3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
	}

	void Quaternion::fromRotationMartix(const Matrix3& kRot)
	{
		float fTrace = kRot[0][0]+kRot[1][1]+kRot[2][2];
		float fRoot;

		if ( fTrace > 0.0 )
		{
			// |w| > 1/2, may as well choose w > 1/2
			fRoot = Math::sqrt(fTrace + 1.0f);  // 2w
			w = 0.5f*fRoot;
			fRoot = 0.5f/fRoot;  // 1/(4w)
			x = (kRot[2][1]-kRot[1][2])*fRoot;
			y = (kRot[0][2]-kRot[2][0])*fRoot;
			z = (kRot[1][0]-kRot[0][1])*fRoot;
		}
		else
		{
			// |w| <= 1/2
			static size_t s_iNext[3] = { 1, 2, 0 };
			size_t i = 0;
			if ( kRot[1][1] > kRot[0][0] )
				i = 1;
			if ( kRot[2][2] > kRot[i][i] )
				i = 2;
			size_t j = s_iNext[i];
			size_t k = s_iNext[j];

			fRoot = Math::sqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + 1.0f);
			float* apkQuat[3] = { &x, &y, &z };
			*apkQuat[i] = 0.5f*fRoot;
			fRoot = 0.5f/fRoot;
			w = (kRot[k][j]-kRot[j][k])*fRoot;
			*apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
			*apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
		}
	}

	Matrix3 Quaternion::toRotationMatrix() const 
	{
		float fTx  = x+x;
		float fTy  = y+y;
		float fTz  = z+z;
		float fTwx = fTx*w;
		float fTwy = fTy*w;
		float fTwz = fTz*w;
		float fTxx = fTx*x;
		float fTxy = fTy*x;
		float fTxz = fTz*x;
		float fTyy = fTy*y;
		float fTyz = fTz*y;
		float fTzz = fTz*z;

		Matrix3 kRot;
		kRot[0][0] = 1.0f-(fTyy+fTzz);
		kRot[0][1] = fTxy-fTwz;
		kRot[0][2] = fTxz+fTwy;
		kRot[1][0] = fTxy+fTwz;
		kRot[1][1] = 1.0f-(fTxx+fTzz);
		kRot[1][2] = fTyz-fTwx;
		kRot[2][0] = fTxz-fTwy;
		kRot[2][1] = fTyz+fTwx;
		kRot[2][2] = 1.0f-(fTxx+fTyy);

		return kRot;
	}

	void Quaternion::fromAngleAxis (const Radian& rfAngle, const Vector3& rkAxis)
	{
		Radian fHalfAngle ( 0.5*rfAngle.valueRadians() );
		float fSin = Math::sin(fHalfAngle.valueRadians());
		w = Math::cos(fHalfAngle.valueRadians());
		x = fSin*rkAxis.x;
		y = fSin*rkAxis.y;
		z = fSin*rkAxis.z;
	}

	void Quaternion::toAngleAxis (Radian& rfAngle, Vector3& rkAxis) const
	{
		float fSqrLength = x*x+y*y+z*z;
		if ( fSqrLength > 0.0 )
		{
			rfAngle = Radian(2.0*Math::acos(w));
			float fInvLength = Math::inv_sqrt(fSqrLength);
			rkAxis.x = x*fInvLength;
			rkAxis.y = y*fInvLength;
			rkAxis.z = z*fInvLength;
		}
		else
		{
			// angle is 0 (mod 2*pi), so any axis will do
			rfAngle = Radian(0.0);
			rkAxis.x = 1.0;
			rkAxis.y = 0.0;
			rkAxis.z = 0.0;
		}
	}

	void Quaternion::fromAxes (const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
	{
		Matrix3 kRot;

		kRot[0][0] = xAxis.x;
		kRot[1][0] = xAxis.y;
		kRot[2][0] = xAxis.z;

		kRot[0][1] = yAxis.x;
		kRot[1][1] = yAxis.y;
		kRot[2][1] = yAxis.z;

		kRot[0][2] = zAxis.x;
		kRot[1][2] = zAxis.y;
		kRot[2][2] = zAxis.z;

		fromRotationMartix(kRot);
	}

	void Quaternion::toAxes (Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const
	{
		Matrix3 kRot = toRotationMatrix();

		xAxis.x = kRot[0][0];
		xAxis.y = kRot[1][0];
		xAxis.z = kRot[2][0];

		yAxis.x = kRot[0][1];
		yAxis.y = kRot[1][1];
		yAxis.z = kRot[2][1];

		zAxis.x = kRot[0][2];
		zAxis.y = kRot[1][2];
		zAxis.z = kRot[2][2];
	}

	void Quaternion::toAxes (Vector3* akAxis) const
	{
		Matrix3 kRot = toRotationMatrix();

		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			akAxis[iCol].x = kRot[0][iCol];
			akAxis[iCol].y = kRot[1][iCol];
			akAxis[iCol].z = kRot[2][iCol];
		}
	}

	Quaternion Quaternion::Slerp (float fT, const Quaternion& rkP,
		const Quaternion& rkQ, bool shortestPath)
	{
		float fCos = rkP.Dot(rkQ);	// 两个四元数之间的夹角
		Quaternion rkT;

		// Do we need to invert rotation?
		if (fCos < 0.0f && shortestPath)
		{
			fCos = -fCos;
			rkT = -rkQ;
		}
		else
		{
			rkT = rkQ;
		}

		if (Math::fabs(fCos) < 1 - Math::EPSINON)
		{
			// Standard case (slerp)
			float fSin = Math::sqrt(1 - fCos*fCos);
			Radian fAngle(Math::atan2(fSin, fCos));
			float fInvSin = 1.0f / fSin;
			float fCoeff0 = Math::sin((1.0f - fT) * fAngle.valueRadians()) * fInvSin;
			float fCoeff1 = Math::sin(fT * fAngle.valueRadians()) * fInvSin;
			return fCoeff0 * rkP + fCoeff1 * rkT;
		}
		else
		{
			// There are two situations:
			// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
			//    interpolation safely.
			// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
			//    are an infinite number of possibilities interpolation. but we haven't
			//    have method to fix this case, so just use linear interpolation here.
			Quaternion t = (1.0f - fT) * rkP + fT * rkT;
			// taking the complement requires renormalisation
			t.normalize();
			return t;
		}
	}

	Quaternion Quaternion::SlerpExtraSpins (float fT,
		const Quaternion& rkP, const Quaternion& rkQ, int iExtraSpins)
	{
		float fCos = rkP.Dot(rkQ);
		Radian fAngle ( Math::acos(fCos) );

		if ( Math::fabs(fAngle.valueRadians()) < Math::EPSINON )
			return rkP;

		float fSin = Math::sin(fAngle.valueRadians());
		Radian fPhase ( Math::PI*iExtraSpins*fT );
		float fInvSin = 1.0f/fSin;
		float fCoeff0 = Math::sin((1.0f-fT)*fAngle.valueRadians() - fPhase.valueRadians())*fInvSin;
		float fCoeff1 = Math::sin(fT*fAngle.valueRadians() + fPhase.valueRadians())*fInvSin;
		return fCoeff0*rkP + fCoeff1*rkQ;
	}

	void Quaternion::Intermediate (const Quaternion& rkQ0,
		const Quaternion& rkQ1, const Quaternion& rkQ2,
		Quaternion& rkA, Quaternion& rkB)
	{
		// assert:  q0, q1, q2 are unit quaternions

		Quaternion kQ0inv = rkQ0.UnitInverse();
		Quaternion kQ1inv = rkQ1.UnitInverse();
		Quaternion rkP0 = kQ0inv*rkQ1;
		Quaternion rkP1 = kQ1inv*rkQ2;
		Quaternion kArg = 0.25*(rkP0.Log()-rkP1.Log());
		Quaternion kMinusArg = -kArg;

		rkA = rkQ1*kArg.Exp();
		rkB = rkQ1*kMinusArg.Exp();
	}
	//-----------------------------------------------------------------------
	Quaternion Quaternion::Squad (float fT,
		const Quaternion& rkP, const Quaternion& rkA,
		const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath)
	{
		float fSlerpT = 2.0f*fT*(1.0f-fT);
		Quaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
		Quaternion kSlerpQ = Slerp(fT, rkA, rkB);
		return Slerp(fSlerpT, kSlerpP ,kSlerpQ);
	}

	Quaternion Quaternion::nlerp(float fT, const Quaternion& rkP,
		const Quaternion& rkQ, bool shortestPath)
	{
		Quaternion result;
		float fCos = rkP.Dot(rkQ);
		if (fCos < 0.0f && shortestPath)
		{
			result = rkP + fT * ((-rkQ) - rkP);
		}
		else
		{
			result = rkP + fT * (rkQ - rkP);
		}
		result.normalize();
		return result;
	}
}
