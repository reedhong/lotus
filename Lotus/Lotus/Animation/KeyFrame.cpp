/********************************************************************
	created:	2012/08/29 
	filename: 	KeyFrame.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "KeyFrame.h"

namespace Lotus {

	KeyFrame::KeyFrame(const AnimationTrack* parent, float time) 
		: mTime(time), mParentTrack(parent)
	{
	}
	//---------------------------------------------------------------------
	KeyFrame* KeyFrame::_clone(AnimationTrack* newParent) const
	{
		return LOTUS_NEW KeyFrame(newParent, mTime);
	}

	//////////////////////////////////////////////////////////////////////////

}
