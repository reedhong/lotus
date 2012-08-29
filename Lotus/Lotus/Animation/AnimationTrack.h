/********************************************************************
	created:	2012/08/29 
	filename: 	AnimationTrack.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_AnimationTrack_H__
#define __Lotus_AnimationTrack_H__

#include "General/Prerequisites.h"
#include "KeyFrame.h"

namespace Lotus {
	class Animation;
	class TimeIndex
	{
	public:
		float		mTimePos;
		uint32		mKeyIndex;
		static const uint32 INVALID_KEY_INDEX = (uint32)-1;

	public:
		TimeIndex(float timePos)
            : mTimePos(timePos)
            , mKeyIndex(INVALID_KEY_INDEX)
        {
        }

        /** Construct time index object by the given time position and
            global keyframe index.
        @note In normally, you don't need to use this constructor directly, use
            Animation::_getTimeIndex instead.
        */
        TimeIndex(float timePos, uint32 keyIndex)
            : mTimePos(timePos)
            , mKeyIndex(keyIndex)
        {
        }

        bool hasKeyIndex(void) const
        {
            return mKeyIndex != INVALID_KEY_INDEX;
        }

        float getTimePos(void) const
        {
            return mTimePos;
        }

        uint32 getKeyIndex(void) const
        {
            return mKeyIndex;
        }
	};	// end TimeIndex

	//////////////////////////////////////////////////////////////////////////
	
    /** A 'track' in an animation sequence, i.e. a sequence of keyframes which affect a
        certain type of animable object.
	 */

	class AnimationTrack
	{
	public:
		AnimationTrack();
		virtual ~AnimationTrack();
	protected:
		vector<KeyFrame* > mKeyFrames;
		Animation*		mParent;
	};
	



}

#endif