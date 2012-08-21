/********************************************************************
	created:	2012/08/16 
	filename: 	Vector4.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_Vector4_H__
#define __Lotus_Vector4_H__

#include "Main/Prerequisites.h"
#include "Math.h"

namespace Lotus {

	class Vector4
	{
	public:
		float x, y, z, w;
	public:
		inline Vector4() {}
		~Vector4() {}
		// 拷贝构造函数
		Vector4(const Vector4& a): x(a.x), y(a.y), z(a.z), w(a.w) {}

		Vector4(float rx, float ry, float rz, float rw): x(rx), y(ry), z(rz), w(rw) {}

		Vector4& operator = (const Vector4& a)
		{
			x = a.x; y = a.y; z = a.z; w = a.w;
			return *this;
		}

		bool operator ==(const Vector4& a) const
		{
			return (x == a.x) && (y == a.y) && (z == a.z) && (w == a.w);
		}

		bool operator !=(const Vector4&a) const
		{
			return !operator==(a);
		}

		void zero()
		{
			x = y = z = w= 0.0f;
		}

		Vector4 operator - () const 
		{
			return Vector4(-x, -y, -z, -w);
		}

		Vector4 operator +(const Vector4 &a)
		{
			return Vector4(x+a.x, y+a.y, z+a.z, w+a.w);
		}

		Vector4 operator -(const Vector4 &a)
		{
			return Vector4(x-a.x, y-a.y, z-a.z, w-a.w);
		}

		// 与标量的乘除法
		Vector4 operator *(float a) const 
		{
			return Vector4(x*a, y*a, z*a, w*a);
		}

		Vector4 operator /(float a) const 
		{			
			ASSERT(fabs(a) > Math::EPSINON);
			float oneVerA = 1.0f/a; 
			return Vector4(x*oneVerA, y*oneVerA, z*oneVerA, w*oneVerA);
		}

		Vector4& operator +=(const Vector4 &a)
		{
			x += a.x; y += a.y; z += a.z; w+= a.w;
			return *this;
		}

		Vector4& operator -=(const Vector4 &a)
		{
			x -= a.x; y -= a.y; z -= a.z; w -= a.w;
			return *this;
		}

		Vector4& operator *=(float a)  
		{
			x *= a;  y *= a;  z *= a; w *= a;
			return *this;
		}

		Vector4& operator /=(float a)  
		{			
			ASSERT(fabs(a) > Math::EPSINON);
			float oneVerA = 1.0f/a; 
			x *= oneVerA; y *= oneVerA;  z *= oneVerA; w*= oneVerA;
			return *this;
		}

		// 向量规范化
		void normalize()
		{
			float magSq = x*x + y*y + z*z + w*w;
			if( magSq >Math::EPSINON ){
				float oneOverMag = 1.0f/sqrt(magSq);
				x *= oneOverMag;
				y *= oneOverMag;
				z *= oneOverMag;
				w *= oneOverMag;
			}
		}

		// 向量点乘, 重载标准的乘法运算符
		float operator *(const Vector4&a)
		{
			return x*a.x + y*a.y + z*a.z;
		}

		// 向量求模
		static float mag(const Vector4 &a)
		{
			return sqrt(a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w);
		}

#if 0

		// 向量叉乘
		static Vector4 corss(const Vector4& a, const Vector4& b)
		{
			return Vector4(a.y*b.z - a.z*b.y,  a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
		}
#endif

		inline  friend std::ostream& operator <<
			( std::ostream& o, const Vector4& v )
		{
			o << "Vector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
			return o;
		}

		static const Vector4 ZERO;
	}; // end Vector4
} // end Lotus
#endif