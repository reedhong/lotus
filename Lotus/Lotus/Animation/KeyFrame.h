/********************************************************************
	created:	2012/08/29 
	filename: 	KeyFrame.h
	author:		reedhong 
	
	purpose:	�ؼ�֡
*********************************************************************/

#ifndef __Lotus_KeyFrame_H__
#define __Lotus_KeyFrame_H__

#include "General/Prerequisites.h"

namespace Lotus {
	/*
	 * ����Ĺؼ�֡������Ϊ�����ڵ㣬Ҳ����Ϊ����
	 */
	class AnimationTrack;
	class  KeyFrame
	{
	public:

		/** Default constructor, you should not call this but use AnimationTrack::createKeyFrame instead. */
		KeyFrame(const AnimationTrack* parent, float time);

		virtual ~KeyFrame() {}

		/** Gets the time of this keyframe in the animation sequence. */
		float getTime(void) const { return mTime; }

		/** Clone a keyframe (internal use only) */
		virtual KeyFrame* _clone(AnimationTrack* newParent) const;


	protected:
		float mTime;
		const AnimationTrack* mParentTrack;
	};

}

#endif