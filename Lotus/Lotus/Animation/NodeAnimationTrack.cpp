/********************************************************************
	created:	2012/08/31 
	filename: 	NodeAnimationTrack.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "NodeAnimationTrack.h"

namespace Lotus {
	//////////////////////////////////////////////////////////////////////////
	// NodeAnimationTrack
	NodeAnimationTrack::NodeAnimationTrack(Animation* parent, unsigned short handle):AnimationTrack(parent, handle)
	{

	}

	NodeAnimationTrack::~NodeAnimationTrack()
	{

	}

	TransformKeyFrame* NodeAnimationTrack::createNodeKeyFrame(float timePos)
	{
		return 0;
	}

	KeyFrame* NodeAnimationTrack::createKeyFrameImpl(float time)
	{
		return 0;
	
	}
	void NodeAnimationTrack::getInterpolatedKeyFrame(const TimeIndex& timeIndex, KeyFrame* kf) const
	{

	}

} // end Lotus