/********************************************************************
	created:	2012/08/21 
	filename: 	Vector2.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_Vector2_H__
#define __Lotus_Vector2_H__


#include "General/Prerequisites.h"
#include "Math.h"

namespace Lotus {
	class Vector2 
	{
	public:
		float x, y;
	public:
		inline Vector2() {}
		~Vector2() {}
		// ¿½±´¹¹Ôìº¯Êý
		Vector2(const Vector2& a): x(a.x), y(a.y) {}

		Vector2(float rx, float ry): x(rx), y(ry){}

		Vector2& operator = (const Vector2& a)
		{
			x = a.x; y = a.y; 
			return *this;
		}

		inline float operator [] ( const size_t i ) const
		{
			ASSERT( i < 2 );

			return *(&x+i);
		}

		inline float& operator [] ( const size_t i )
		{
			ASSERT( i < 2 );

			return *(&x+i);
		}

		bool operator ==(const Vector2& a) const
		{
			return (x == a.x) && (y == a.y);
		}

		bool operator !=(const Vector2&a) const
		{
			return (x != a.x) || ( y != a.y ) ;
		}

		void zero()
		{
			x = y =  0.0f;
		}

		Vector2 operator - () const 
		{
			return Vector2(-x, -y);
		}

		Vector2 operator +(const Vector2 &a)
		{
			return Vector2(x+a.x, y+a.y);
		}

		Vector2 operator -(const Vector2 &a)
		{
			return Vector2(x-a.x, y-a.y);
		}

		static const Vector2 ZERO;
	}; // end Vector2
}

#endif
