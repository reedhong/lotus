/********************************************************************
	created:	2012/08/10 
	filename: 	Quaternion.h
	author:		reedhong 
	
	purpose:	ËÄÔªÊý
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
		inline Quaternion (): w(1), x(0), y(0), z(0)
		{


		}
		inline Quaternion (float fW,float fX, float fY, float fZ)
			: w(fW), x(fX), y(fY), z(fZ)
		{
		}
	};
}

#endif