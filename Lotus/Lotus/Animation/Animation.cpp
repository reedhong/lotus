/********************************************************************
	created:	2012/08/31 
	filename: 	Animation.cpp
	author:		reedhong 
	
	purpose:	¶¯»­
*********************************************************************/

#include "Animation.h"

namespace Lotus {
	Animation::Animation(const String& name, float length):mName(name), mLength(length)
	{

	}

	Animation::~Animation()
	{

	}

	const String& Animation::getName() const 
	{
		return mName;
	}

	float Animation::getLength() const 
	{
		return mLength;
	}

	void Animation::setLength(float len)
	{
		mLength = len;
	}


}