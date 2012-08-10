/********************************************************************
	created:	2012/08/10 
	filename: 	Vector.h
	author:		reedhong 
	
	purpose:	向量相关操作
*********************************************************************/

#ifndef __Lotus_Vector_H__
#define __Lotus_Vector_H__

#include "Main/Prerequisites.h"

namespace Lotus {
	class Vector2 
	{
	public:
		Real x, y;
	public:
		inline Vector2() {}
		~Vector2() {}
	}; // end Vector2

	class Vector3 
	{
	public:
		Real x, y, z;
	public:
		inline Vector3() {}
		~Vector3() {}
	}; // end Vector3

	class Vector4
	{
	public:
		Real x, y, z, w;
	public:
		inline Vector4() {}
		~Vector4() {}
	}; // end Vector4
}

#endif