/********************************************************************
	created:	2012/08/29 
	filename: 	KeyFrame.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "KeyFrame.h"
#include "AnimationTrack.h"


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
	TransformKeyFrame::TransformKeyFrame(const AnimationTrack* parent, float time):KeyFrame(parent, time)
	{
	}

	void TransformKeyFrame::setTranslate(const Vector3& trans)
	{
		mTranslate = trans;
		if(mParentTrack){
			mParentTrack->_keyFrameDataChanged();
		}
	}

	const Vector3& TransformKeyFrame::getTranslate() const 
	{
		return mTranslate;
	}

	void TransformKeyFrame::setScale(const Vector3& scale)
	{
		mScale = scale;
		if(mParentTrack){
			mParentTrack->_keyFrameDataChanged();
		}
	}

	const Vector3& TransformKeyFrame::getScale() const 
	{
		return mScale;
	}

	void TransformKeyFrame::setRotation(const Quaternion& rot)
	{
		mRotate = rot;
		if(mParentTrack){
			mParentTrack->_keyFrameDataChanged();
		}
	}

	const Quaternion& TransformKeyFrame::getRotation() const 
	{
		return mRotate;
	}

	KeyFrame* TransformKeyFrame::_clone(AnimationTrack* newParent) const 
	{
		TransformKeyFrame* newKf = LOTUS_NEW TransformKeyFrame(newParent, mTime);
		newKf->mTranslate = mTranslate;
		newKf->mScale = mScale;
		newKf->mRotate = mRotate;

		return newKf;
	}
}