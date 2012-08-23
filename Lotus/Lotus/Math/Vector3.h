/********************************************************************
	created:	2012/08/10 
	filename: 	Vector.h
	author:		reedhong 	
	purpose:	向量相关操作
*********************************************************************/

#ifndef __Lotus_Vector3_H__
#define __Lotus_Vector3_H__

#include "Main/Prerequisites.h"
#include "Math.h"

namespace Lotus {
	class Vector3 
	{
	public:		
		float x, y, z;
	public:
		 Vector3() {}

		~Vector3() {}

		// 拷贝构造函数
		Vector3(const Vector3& a): x(a.x), y(a.y), z(a.z) {}

		Vector3(float rx, float ry, float rz): x(rx), y(ry), z(rz) {}
		
		Vector3& operator = (const Vector3& a)
		{
			x = a.x; y = a.y; z = a.z;
			return *this;
		}

		bool operator ==(const Vector3& a) const
		{
			 return (x == a.x) && (y == a.y) && (z == a.z);
		}

		bool operator !=(const Vector3&a) const
		{
			return (x != a.x) || ( y != a.y ) || ( z != a.z);
		}

		void zero()
		{
			x = y = z = 0.0f;
		}

		Vector3 operator - () const 
		{
			return Vector3(-x, -y, -z);
		}

		Vector3 operator +(const Vector3 &a) const
		{
			return Vector3(x+a.x, y+a.y, z+a.z);
		}

		Vector3 operator -(const Vector3 &a) const
		{
			return Vector3(x-a.x, y-a.y, z-a.z);
		}

		// 与标量的乘除法
		Vector3 operator *(float a) const 
		{
			return Vector3(x*a, y*a, z*a);
		}

		Vector3 operator /(float a) const 
		{			
			ASSERT(fabs(a) > Math::EPSINON);
			float oneVerA = 1.0f/a; 
			return Vector3(x*oneVerA, y*oneVerA, z*oneVerA);
		}

		Vector3& operator +=(const Vector3 &a)
		{
			x += a.x; y += a.y; z += a.z;
			return *this;
		}

		Vector3& operator -=(const Vector3 &a)
		{
			x -= a.x; y -= a.y; z -= a.z;
			return *this;
		}

		Vector3& operator *=(float a)  
		{
			x *= a;  y *= a;  z *= a;
			return *this;
		}

		Vector3& operator /=(float a)  
		{			
			ASSERT(fabs(a) > Math::EPSINON);
			float oneVerA = 1.0f/a; 
			x *= oneVerA; y *= oneVerA;  z *= oneVerA;
			return *this;
		}

		inline float operator [] ( const size_t i ) const
		{
			ASSERT( i < 3 );

			return *(&x+i);
		}

		inline float& operator [] ( const size_t i )
		{
			ASSERT( i < 3 );

			return *(&x+i);
		}

		inline friend Vector3 operator + (const Vector3& lhs, const float rhs)
		{
			return Vector3(
				lhs.x + rhs,
				lhs.y + rhs,
				lhs.z + rhs);
		}

		inline friend Vector3 operator + (const float lhs, const Vector3& rhs)
		{
			return Vector3(
				lhs + rhs.x,
				lhs + rhs.y,
				lhs + rhs.z);
		}

		inline friend Vector3 operator - (const Vector3& lhs, const float rhs)
		{
			return Vector3(
				lhs.x - rhs,
				lhs.y - rhs,
				lhs.z - rhs);
		}

		inline friend Vector3 operator - (const float lhs, const Vector3& rhs)
		{
			return Vector3(
				lhs - rhs.x,
				lhs - rhs.y,
				lhs - rhs.z);
		}

		// 向量规范化
		void normalize()
		{
			float magSq = x*x + y*y + z*z;
			if( magSq >Math::EPSINON ){
				float oneOverMag = 1.0f/sqrt(magSq);
				x *= oneOverMag;
				y *= oneOverMag;
				z *= oneOverMag;
			}
		}

		// 向量点乘, 重载标准的乘法运算符
		float operator *(const Vector3&a)
		{
			return x*a.x + y*a.y + z*a.z;
		}

		inline float squaredLength () const
		{
			return x * x + y * y + z * z;
		}
		/** Returns true if this vector is zero length. */
		inline bool isZeroLength(void) const
		{
			float sqlen = (x * x) + (y * y) + (z * z);
			return (sqlen < Math::EPSINON);

		}

     /** Gets the shortest arc quaternion to rotate this vector to the destination
            vector.
        @remarks
            If you call this with a dest vector that is close to the inverse
            of this vector, we will rotate 180 degrees around the 'fallbackAxis'
			(if specified, or a generated axis if not) since in this case
			ANY axis of rotation is valid.
        */
        Quaternion getRotationTo(const Vector3& dest,
			const Vector3& fallbackAxis = Vector3::ZERO) const;
	
		// 向量求模
		static float mag(const Vector3 &a)
		{
			return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
		}


		// 向量叉乘
		static Vector3 cross(const Vector3& a, const Vector3& b)
		{
			return Vector3(a.y*b.z - a.z*b.y,  a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
		}


		// 计算两点间的距离
		static float distance(const Vector3& a,  const Vector3& b)
		{
			float dx = a.x - b.x;
			float dy = a.y - b.y;
			float dz = a.z - b.z;

			return sqrt(dx*dx + dy*dy + dz*dz);
		}

		static const Vector3 ZERO;
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;
		static const Vector3 NEGATIVE_UNIT_X;
		static const Vector3 NEGATIVE_UNIT_Y;
		static const Vector3 NEGATIVE_UNIT_Z;
		static const Vector3 UNIT_SCALE;

		inline  friend std::ostream& operator <<
			( std::ostream& o, const Vector3& v )
		{
			o << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
			return o;
		}
	}; // end Vector3
}

#endif