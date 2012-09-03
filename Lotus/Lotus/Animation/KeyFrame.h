/********************************************************************
	created:	2012/08/29 
	filename: 	KeyFrame.h
	author:		reedhong 
	
	purpose:	关键帧
*********************************************************************/

#ifndef __Lotus_KeyFrame_H__
#define __Lotus_KeyFrame_H__

#include "General/Prerequisites.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

namespace Lotus {
	/*
	 * 抽象的关键帧，可以为骨骼节点，也可以为顶点
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


	//////////////////////////////////////////////////////////////////////////

	class TransformKeyFrame: public KeyFrame
	{
	public:
		TransformKeyFrame(const AnimationTrack* parent, float time);
		~TransformKeyFrame() {};

		void setTranslate(const Vector3& trans);
		const Vector3& getTranslate() const ;

		void setScale(const Vector3& scale);
		const Vector3& getScale() const;

		void setRotation(const Quaternion& rot);
		const Quaternion& getRotation() const ;

		KeyFrame* _clone(AnimationTrack* newParent) const;
	protected:
		Vector3				mTranslate;
		Vector3				mScale;
		Quaternion		mRotate;
	};

}

#endif