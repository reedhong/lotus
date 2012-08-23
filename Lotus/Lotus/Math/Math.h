/********************************************************************
	created:	2012/08/08 
	filename: 	Math.h
	author:		reedhong 
	
	purpose:	数学相关的
						Ogre中数字的计算设计了缓存机制，后续可以考虑引入
*********************************************************************/

#ifndef __Lotus_Math_H__
#define __Lotus_Math_H__

#include <cmath>
//using namespace  std;

namespace Lotus {	
	
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix3;
	class Matrix4;
	class Radian;
	class Degree;
	class Angle;
	class Quaternion;



	class Math{
	public:
		static float  EPSINON;
		static float PI;
		static float Deg2Rad;
		static float Rad2Deg;
	public:
		Math();
		~Math();

	public:
		//////////////////////////////////////////////////////////////////////////
		// 封装一些常用的数学函数，为后续扩展或者加速做准备
		static float abs(float f)
		{
			return std::abs(f);
		}

		static float fabs(float f)
		{
			return std::fabs(f);
		}
		static float cos(float f)
		{
			return std::cos(f);
		}

		static float acos(float fValue)
		{
			if ( -1.0 < fValue )
			{
				if ( fValue < 1.0 )
					return std::acos(fValue);
				else
					return 0.0;
			}
			else
			{
				return PI;
			}
		}

		static float sin(float f)
		{
			return std::sin(f);
		}

		static float tan(float f)
		{
			return std::tan(f);
		}

		static float  atan2(float s, float c)
		{
			return std::atan2(s, c);
		}

		static float sqrt(float f)
		{
			return std::sqrt(f);
		}

		static float inv_sqrt(float f)
		{
			return 1.0f/std::sqrt(f);
		}

		static bool floatEqual( float a, float b, float tolerance = EPSINON )
		{
			if (fabs(b-a) <= tolerance)
				return true;
			else
				return false;
		}
		static inline float DegreesToRadians(float degrees) { return degrees * Deg2Rad; }
		static inline float RadiansToDegrees(float radians) { return radians * Rad2Deg; }

		static inline bool isNaN(float f)
		{
			// std::isnan() is C99, not supported by all compilers
			// However NaN always fails this next test, no other number does.
			return f != f;
		}
	}; // end Math
} // end Lotus
#endif