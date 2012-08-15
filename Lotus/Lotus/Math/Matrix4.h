/********************************************************************
	created:	2012/08/10 
	filename: 	Matrix4.h
	author:		reedhong 
	
	purpose:	matrix operator, just for opengl
*********************************************************************/

#ifndef __Lotus_Matrix4_H__
#define __Lotus_Matrix4_H__

#include "Main/Prerequisites.h"
namespace Lotus {
	/*
	 *  OpenGL是按列存储的，小心了
	 */
	class Matrix4
	{
	public:
		static const Matrix4 ZERO;
		static const Matrix4 ZEROAFFINE;
		static const Matrix4 IDENTITY;
	public:
		union{
			float		_m[16];
			struct 		M
			{
				float m11, m21,m31, m41;
				float m12, m22, m32, m42;
				float m13, m23, m33, m43;
				float m14, m24, m34, m44;
			}m;
		};
	public:
		
		inline Matrix4(){}
		inline Matrix4(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
		{
			_m[0] = m11;
			_m[1] = m21;
			_m[2] = m31;
			_m[3] = m41;
			_m[4] = m12;
			_m[5] = m22;
			_m[6] = m32;
			_m[7] = m42;
			_m[8] = m13;
			_m[9] = m23;
			_m[10] = m33;
			_m[11] = m43;
			_m[12] = m14;
			_m[13] = m24;
			_m[14] = m34;
			_m[15] = m44;
 		}
		~Matrix4(){}
	};	// end Matrix4
} // end Lotus

#endif