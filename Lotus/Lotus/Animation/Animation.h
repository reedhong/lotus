/********************************************************************
	created:	2012/08/29 
	filename: 	Animation.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_Animation_H__
#define __Lotus_Animation_H__

#include "General/Prerequisites.h"

namespace Lotus {
	class Animation
	{
	public:
		enum InterpolationMode
		{
			eIM_LINER,
			eIM_SPLINE
		};

		enum RotationInterpolationMode
		{
			eRIM_LINER,
			eRIM_SPHERICAL
		};

		Animation(const String& name, float length);
		virtual ~Animation();

	protected:
		String		mName;
		float		mLength;
		InterpolationMode mInterpolationMode;
		RotationInterpolationMode mRotationInterpolationMode;


	};
}

#endif