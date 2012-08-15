/********************************************************************
	created:	2012/08/10 
	filename: 	Vector.h
	author:		reedhong 
	
	purpose:	������ز���
*********************************************************************/

#ifndef __Lotus_Vector_H__
#define __Lotus_Vector_H__

#include "Main/Prerequisites.h"
#include "Math.h"

namespace Lotus {
	class Vector2 
	{
	public:
		float x, y;
	public:
		inline Vector2() {}
		~Vector2() {}
	}; // end Vector2

	class Vector3 
	{
	public:
		float x, y, z;
	public:
		 Vector3() {}

		~Vector3() {}

		// �������캯��
		Vector3(const Vector3& a): x(a.x), y(a.y), z(a.z) {}

		Vector3(float rx, float ry, float rz): x(rz), y(ry), z(rz) {}
		
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

		Vector3 operator +(const Vector3 &a)
		{
			return Vector3(x+a.x, y+a.y, z+a.z);
		}

		Vector3 operator -(const Vector3 &a)
		{
			return Vector3(x-a.x, y-a.y, z-a.z);
		}

		// ������ĳ˳���
		Vector3 operator *(float a) const 
		{
			return Vector3(x*a, y*a, z*a);
		}

		Vector3 operator /(float a) const 
		{			
			ASSERT(fabs(a) > EPSINON);
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
			ASSERT(fabs(a) > EPSINON);
			float oneVerA = 1.0f/a; 
			x *= oneVerA; y *= oneVerA;  z *= oneVerA;
			return *this;
		}

		// �����淶��
		void normalize()
		{
			float magSq = x*x + y*y + z*z;
			if( magSq >EPSINON ){
				float oneOverMag = 1.0f/sqrt(magSq);
				x *= oneOverMag;
				y *= oneOverMag;
				z *= oneOverMag;
			}
		}

		// �������, ���ر�׼�ĳ˷������
		float operator *(const Vector3&a)
		{
			return x*a.x + y*a.y + z*a.z;
		}
	
		// ������ģ
		static float mag(const Vector3 &a)
		{
			return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
		}


		// �������
		static Vector3 corss(const Vector3& a, const Vector3& b)
		{
			return Vector3(a.y*b.z - a.z*b.y,  a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
		}


		// ���������ľ���
		static float distance(const Vector3& a,  const Vector3& b)
		{
			float dx = a.x - b.x;
			float dy = a.y - b.y;
			float dz = a.z - b.z;

			return sqrt(dx*dx + dy*dy + dz*dz);
		}

		static const Vector3 ZeroVector;
	}; // end Vector3

	class Vector4
	{
	public:
		float x, y, z, w;
	public:
		inline Vector4() {}
		~Vector4() {}
	}; // end Vector4
}

#endif