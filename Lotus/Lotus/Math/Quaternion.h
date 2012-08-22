/********************************************************************
	created:	2012/08/10 
	filename: 	Quaternion.h
	author:		reedhong 
	
	purpose:	四元数，实现3D中的角位移
*********************************************************************/

#ifndef __Lotus_Quaternion_H__
#define __Lotus_Quaternion_H__

#include "Main/Prerequisites.h"

namespace Lotus {
	class Quaternion 
	{
	public:
		float w, x, y, z;
	public:
		Quaternion (): w(1), x(0), y(0), z(0){}

		Quaternion (float fW,float fX, float fY, float fZ)
			: w(fW), x(fX), y(fY), z(fZ){}
		
		Quaternion(const Matrix3& m3)
		{
			this->fromRotationMartix(m3);
		}
		
		void identity()
		{
			w = 1.0f;
			x=y=z = 0.0f;
		}
	
		Matrix3 toRotationMatrix() const 
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

		void fromRotationMartix(const Matrix3& kRot)
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
	};
}

#endif