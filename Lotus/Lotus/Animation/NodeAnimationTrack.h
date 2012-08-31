/********************************************************************
	created:	2012/08/31 
	filename: 	NodeAnimationTrack.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_NodeAnimationTrack_H__
#define __Lotus_NodeAnimationTrack_H__

#include "General/Prerequisites.h"
#include "Math/SimpleSpline.h"
#include "Math/RotationalSpline.h"

#include "KeyFrame.h"
#include "AnimationTrack.h"

namespace Lotus {
//////////////////////////////////////////////////////////////////////////
	/** Specialised AnimationTrack for dealing with node transforms.
	*/
	class  NodeAnimationTrack : public AnimationTrack
	{
	public:
		NodeAnimationTrack(Animation* parent, unsigned short handle);		
		virtual ~NodeAnimationTrack();

        /** Creates a new KeyFrame and adds it to this animation at the given time index.
        @remarks
            It is better to create KeyFrames in time order. Creating them out of order can result 
            in expensive reordering processing. Note that a KeyFrame at time index 0.0 is always created
            for you, so you don't need to create this one, just access it using getKeyFrame(0);
        @param timePos The time from which this KeyFrame will apply.
        */
        virtual TransformKeyFrame* createNodeKeyFrame(float timePos);
		
		virtual void getInterpolatedKeyFrame(const TimeIndex& timeIndex, KeyFrame* kf) const;

		/** Sets the method of rotation calculation */
		virtual void setUseShortestRotationPath(bool useShortestPath)
		{
			mUseShortestRoationPath = useShortestPath;
		}

		/** Gets the method of rotation calculation */
		virtual bool getUseShortestRotationPath() const
		{
			return mUseShortestRoationPath;
		}

	protected:
		KeyFrame* createKeyFrameImpl(float time);
		
		struct Splines
		{
			SimpleSpline		postionSpline;
			SimpleSpline		scaleSpline;
			RotationalSpline	rotationSpline;
		};
		//Node* mTagetNode;	// track需要绑定到一个Node上去
		mutable Splines*	mSplines;
		mutable bool mSplineBuildNeeded;
		mutable bool mUseShortestRoationPath;

	};

	
}


#endif