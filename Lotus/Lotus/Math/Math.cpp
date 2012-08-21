/********************************************************************
	created:	2012/08/08 
	filename: 	Math.cpp
	author:		reedhong 
	
	purpose:	数学相关的
*********************************************************************/

#include "Math.h"

namespace Lotus {
	float Math::EPSINON = 0.00001f;
	float Math::PI =  4.0f * atan(1.0f);
	float Math::Deg2Rad = PI/180.0f;
	float Math::Rad2Def = 180.0f/PI;

	Math::Math()
	{

	}

	Math::~Math()
	{

	}
}
