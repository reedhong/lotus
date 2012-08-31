/********************************************************************
	created:	2012/08/29 
	filename: 	AnimationTrack.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "AnimationTrack.h"
#include "Animation.h"

namespace Lotus {
	namespace {
		// Locally key frame search helper
		struct KeyFrameTimeLess
		{
			bool operator() (const KeyFrame* kf, const KeyFrame* kf2) const
			{
				return kf->getTime() < kf2->getTime();
			}
		};
	}
	AnimationTrack::AnimationTrack(Animation* parent, unsigned short handle):mParent(parent), mHandle(handle)
	{

	}

	AnimationTrack::~AnimationTrack()
	{
		removeAllKeyFrames();
	}

	unsigned short AnimationTrack::getNumKeyFrames(void) const
	{
		return (unsigned short)mKeyFrames.size();
	}

	KeyFrame* AnimationTrack::getKeyFrame(unsigned short index) const
	{
		ASSERT(index < mKeyFrames.size());

		return mKeyFrames[index];
	}

	// 获得时间timeindex所在位置的keyframe
	float AnimationTrack::getKeyFramesAtTime(const TimeIndex& timeIndex, KeyFrame** keyFrame1, KeyFrame** keyFrame2,
		unsigned short* firstKeyIndex) const
	{
			return 0.0f;
	}

	KeyFrame* AnimationTrack::createKeyFrame(float timePos)
	{
		KeyFrame* kf = createKeyFrameImpl(timePos);

		// Insert just before upper bound
		// 这种写法真的优美好多
		vector<KeyFrame *>::iterator i =
			std::upper_bound(mKeyFrames.begin(), mKeyFrames.end(), kf, KeyFrameTimeLess());
		mKeyFrames.insert(i, kf);
		
		// TODO:
		return kf;



	}
	/** Removes a KeyFrame by it's index. */
	void AnimationTrack::removeKeyFrame(unsigned short index)	
	{
		ASSERT( index < (unsigned short)mKeyFrames.size() );

		vector<KeyFrame *>::iterator i = mKeyFrames.begin();
		i += index;

		LOTUS_DELETE *i;
		mKeyFrames.erase(i);

		// TODO
	}

	/** Removes all the KeyFrames from this track. */
	void AnimationTrack::removeAllKeyFrames(void)
	{
		vector<KeyFrame *>::iterator i = mKeyFrames.begin();

		for (; i != mKeyFrames.end(); ++i)
		{
			LOTUS_DELETE *i;
		}
		
		// TODO:
		//_keyFrameDataChanged();
		//mParent->_keyFrameListChanged();

		mKeyFrames.clear();
	}

}