/********************************************************************
	created:	2012/08/10 
	filename: 	Quaternion.h
	author:		reedhong 
	
	purpose:	四元数，实现3D中的角位移
*********************************************************************/

#ifndef __Lotus_Quaternion_H__
#define __Lotus_Quaternion_H__

#include "Main/Prerequisites.h"
#include "Math.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "Angle.h"

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

		inline Quaternion(const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis)
		{
			this->fromAxes(xaxis, yaxis, zaxis);
		}

		/*
		 * 四元数表示旋转后的角位移
		 * 可以用一个轴+角度，表示任意旋转  3D数学基础中的8.2.3有详细阐述，所以二者某种意义上是等价的
		 */
		Quaternion(const Radian& rfAngle, const Vector3& rkAxis)
		{
			this->fromAngleAxis(rfAngle, rkAxis);
		}

		inline float operator [] ( const size_t i ) const
		{
			ASSERT( i < 4 );
			return *(&w+i);
		}

		inline float& operator [] ( const size_t i )
		{
			ASSERT( i < 4 );
			return *(&w+i);
		}
		
		inline Quaternion& operator= (const Quaternion& rkQ)
		{
			w = rkQ.w;
			x = rkQ.x;
			y = rkQ.y;
			z = rkQ.z;
			return *this;
		}

		Quaternion operator+ (const Quaternion& rkQ) const
		{
			return Quaternion(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
		}

		Quaternion operator- (const Quaternion& rkQ) const
		{
			return Quaternion(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
		}

		Quaternion operator* (const Quaternion& rkQ) const
		{
			return Quaternion
				(
				w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
				w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
				w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
				w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
				);
		}
		Quaternion operator* (float fScalar) const
		{
			return Quaternion(fScalar*w,fScalar*x,fScalar*y,fScalar*z);
		}

		friend Quaternion operator* (float fScalar, const Quaternion& rkQ)
		{
			return Quaternion(fScalar*rkQ.w,fScalar*rkQ.x,fScalar*rkQ.y,
				fScalar*rkQ.z);
		}

		/// Rotation of a vector by a quaternion
		Vector3 operator* (const Vector3& v) const
		{
			// nVidia SDK implementation
			Vector3 uv, uuv;
			Vector3 qvec(x, y, z);
			uv = Vector3::cross(qvec,v);
			uuv = Vector3::cross(qvec,uv);
			uv *= (2.0f * w);
			uuv *= 2.0f;
			return v+uv+uuv;
		}

		Quaternion operator- () const
		{
			return Quaternion(-w,-x,-y,-z);
		}

		inline bool operator== (const Quaternion& rhs) const
		{
			return (rhs.x == x) && (rhs.y == y) &&
				(rhs.z == z) && (rhs.w == w);
		}
		inline bool operator!= (const Quaternion& rhs) const
		{	
			return !operator==(rhs);
		}

		// functions of a quaternion
		/// Returns the dot product of the quaternion
		float Quaternion::Dot (const Quaternion& rkQ) const
		{
			return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
		}

		float Norm () const
		{
			return w*w+x*x+y*y+z*z;
		}

		/// Normalises this quaternion, and returns the previous length
		float normalize(void)
		{
			float len = w*w+x*x+y*y+z*z;
			float factor = 1.0f / Math::sqrt(len);
			*this = *this * factor;
			return len;
		}
		
		// apply to non-zero quaternion
		Quaternion Inverse () const 
		{
			float fNorm = w*w+x*x+y*y+z*z;
			if ( fNorm > 0.0 )
			{
				float fInvNorm = 1.0f/fNorm;
				return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
			}
			else
			{
				// return an invalid result to flag the error
				return ZERO;
			}
		}

		Quaternion Quaternion::UnitInverse () const
		{
			// assert:  'this' is unit length
			return Quaternion(w,-x,-y,-z);
		}

		void identity()
		{
			w = 1.0f;
			x=y=z = 0.0f;
		}

		Quaternion Exp () const;
		Quaternion Log () const;
		/** Returns the X orthonormal axis defining the quaternion. Same as doing
			xAxis = Vector3::UNIT_X * this. Also called the local X-axis
		*/
        Vector3 xAxis(void) const;

        /** Returns the Y orthonormal axis defining the quaternion. Same as doing
			yAxis = Vector3::UNIT_Y * this. Also called the local Y-axis
		*/
        Vector3 yAxis(void) const;

		/** Returns the Z orthonormal axis defining the quaternion. Same as doing
			zAxis = Vector3::UNIT_Z * this. Also called the local Z-axis
		*/
        Vector3 zAxis(void) const;
			
		void fromRotationMartix(const Matrix3& kRot);
		Matrix3 toRotationMatrix() const;

		void fromAngleAxis (const Radian& rfAngle, const Vector3& rkAxis);
		void toAngleAxis (Radian& rfAngle, Vector3& rkAxis) const;

		void fromAxes (const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
		void toAxes (Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const;
		void toAxes (Vector3* akAxis) const;

		inline  friend std::ostream& operator <<
			( std::ostream& o, const Quaternion& q )
		{
			o << "Quaternion(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
			return o;
		}

		//////////////////////////////////////////////////////////////////////////
		// 静态
		// special values
		static const Quaternion ZERO;
		static const Quaternion IDENTITY;

	    /** Performs Spherical linear interpolation between two quaternions, and returns the result.
			Slerp ( 0.0f, A, B ) = A
			Slerp ( 1.0f, A, B ) = B
			@return Interpolated quaternion
			@remarks
			Slerp has the proprieties of performing the interpolation at constant
			velocity, and being torque-minimal (unless shortestPath=false).
			However, it's NOT commutative, which means
			Slerp ( 0.75f, A, B ) != Slerp ( 0.25f, B, A );
			therefore be careful if your code relies in the order of the operands.
			This is specially important in IK animation.
		*/
        static Quaternion Slerp (float fT, const Quaternion& rkP,
            const Quaternion& rkQ, bool shortestPath = false);

		/** @see Slerp. It adds extra "spins" (i.e. rotates several times) specified
			by parameter 'iExtraSpins' while interpolating before arriving to the
			final values
		*/
        static Quaternion SlerpExtraSpins (float fT,
            const Quaternion& rkP, const Quaternion& rkQ,
            int iExtraSpins);


  // setup for spherical quadratic interpolation
        static void Intermediate (const Quaternion& rkQ0,
            const Quaternion& rkQ1, const Quaternion& rkQ2,
            Quaternion& rka, Quaternion& rkB);

        // spherical quadratic interpolation
        static Quaternion Squad (float fT, const Quaternion& rkP,
            const Quaternion& rkA, const Quaternion& rkB,
            const Quaternion& rkQ, bool shortestPath = false);

        /** Performs Normalised linear interpolation between two quaternions, and returns the result.
			nlerp ( 0.0f, A, B ) = A
			nlerp ( 1.0f, A, B ) = B
			@remarks
			Nlerp is faster than Slerp.
			Nlerp has the proprieties of being commutative (@see Slerp;
			commutativity is desired in certain places, like IK animation), and
			being torque-minimal (unless shortestPath=false). However, it's performing
			the interpolation at non-constant velocity; sometimes this is desired,
			sometimes it is not. Having a non-constant velocity can produce a more
			natural rotation feeling without the need of tweaking the weights; however
			if your scene relies on the timing of the rotation or assumes it will point
			at a specific angle at a specific weight value, Slerp is a better choice.
		*/
        static Quaternion nlerp(float fT, const Quaternion& rkP, 
            const Quaternion& rkQ, bool shortestPath = false);
	};
}

#endif