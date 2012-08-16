/********************************************************************
	created:	2012/08/10 
	filename: 	Camera.cpp
	author:		reedhong 
	
	purpose:	Camera
*********************************************************************/

#include <GL/glew.h>
#include "Camera.h"

namespace Lotus {
	Camera::Camera()
	{
		
	}

	Camera::~Camera()
	{

	}

	void Camera::lookAt(const Vector3& eye,  const Vector3& center, const Vector3& up)
	{
		mEye = eye; mCenter = center; mUp = up;

		Vector3 forward = mCenter - mEye;
		forward.normalize();

		Vector3 side = Vector3::corss(forward, mUp);
		side.normalize();

		Vector3 newUp = Vector3::corss(side, forward);
		//yVec3.normalize();
		// 由于右乘，所以是这么个放防止
		mViewMatrix4.set(
			side.x, side.y,  side.z, mEye*side,
			newUp.x, newUp.y, newUp.z, mEye*newUp,
			-forward.x, -forward.y, -forward.z, mEye*forward,
			0, 0, 0, 1
			//0,0,0,1
			);
		glMultMatrixf(mViewMatrix4.m);
		// 平移相当于上面的： mEye*side,mEye*newUp,mEye*forward,
		//glTranslatef(-mEye.x, -mEye.y, -mEye.z);
		printf("x");
	}

	void Camera::project(float fov, float aspect, float near, float far)
	{

	}
}
