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

		const String& getName() const;
		float getLength() const;
		void setLength(float len);

		//////////////////////////////////////////////////////////////////////////
		// ≤Â÷µ
		InterpolationMode getInterpolationMode(void) const
		{
			return mInterpolationMode;
		}

		void setInterpolationMode(InterpolationMode im)
		{
			mInterpolationMode = im;
		}

		RotationInterpolationMode getRotationInterpolationMode(void) const
		{
			return mRotationInterpolationMode;
		}
		void setRotationInterpolationMode(RotationInterpolationMode im)
		{
			mRotationInterpolationMode = im;
		}


	protected:
		String		mName;
		float		mLength;
		InterpolationMode mInterpolationMode;
		RotationInterpolationMode mRotationInterpolationMode;

		//////////////////////////////////////////////////////////////////////////
		// ¥Ê¥¢track
		


	};
}

#endif