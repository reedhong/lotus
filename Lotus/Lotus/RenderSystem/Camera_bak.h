/********************************************************************
	created:	2012/08/10 
	filename: 	Camera.h
	author:		reedhong 
	
	purpose:	摄像机
*********************************************************************/

#ifndef __Lotus_Camera_H__
#define __Lotus_Camera_H__

#include "Main/SharedPtr.h"

#include "Math/Vector3.h"
#include "Math/Matrix4.h"

namespace Lotus {
	class Camera 
	{
	public:
		Camera();
		~Camera();
	
		void lookAt(const Vector3& eye,  const Vector3& center, const Vector3& up);
		void project(float fov, float aspect, float near, float far);
	public:
		// 观察矩阵属性
		Vector3			mEye;
		Vector3			mCenter;
		Vector3			mUp;
		Matrix4			mViewMatrix4;	// 视图矩阵


		Vector3			mPostion;
		Quaternion	mOrientation;
		

		// 投影矩阵属性， 此处直接采取透视投影的计算规则，没有设计正交投影
		float				mFov;		// 视场
		float				mAspect;
		float				mNear;
		float				mFar;
		Matrix4			mProjectMatrix4;	// 投影矩阵

	};

	typedef SharedPtr<Camera> CameraPtr;
}

#endif