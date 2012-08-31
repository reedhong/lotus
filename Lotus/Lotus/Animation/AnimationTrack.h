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
	//////////////////////////////////////////////////////////////////////////
	// ������
	class AnimationTrack
	{
	public:
		AnimationTrack(Animation* parent, unsigned short handle);
		virtual ~AnimationTrack();
		unsigned short getHandle(void) const { return mHandle;}
		Animation *getParent() const { return mParent; }	
		
		virtual unsigned short getNumKeyFrames(void) const;
		virtual KeyFrame* getKeyFrame(unsigned short index) const;

		// ���ʱ��timeindex����λ�õ�keyframe
		virtual float getKeyFramesAtTime(const TimeIndex& timeIndex, KeyFrame** keyFrame1, KeyFrame** keyFrame2,
			unsigned short* firstKeyIndex = 0) const;

		// ���ʱ������ڵĲ�ֵkeyframe
		virtual void getInterpolatedKeyFrame(const TimeIndex& timeIndex, KeyFrame*kf) const = 0;		
	
		virtual KeyFrame* createKeyFrame(float timePos);
		/** Removes a KeyFrame by it's index. */
		virtual void removeKeyFrame(unsigned short index);

		/** Removes all the KeyFrames from this track. */
		virtual void removeAllKeyFrames(void);

	protected:
		vector<KeyFrame* > mKeyFrames;
		Animation*		mParent;
		unsigned short mHandle;

		/// Create a keyframe implementation - must be overridden
		virtual KeyFrame* createKeyFrameImpl(float time) = 0;

	};
}

#endif