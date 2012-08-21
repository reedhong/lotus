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
		// 由于右乘，所以这个地方跟3D数学基础上讲的内容要转置一下
		mViewMatrix4.set(
			side.x,			side.y,				side.z,				mEye*side,
			newUp.x,	newUp.y,		newUp.z,		mEye*newUp,
			-forward.x, -forward.y,	-forward.z,		mEye*forward,
			0,					0,						0,						1
			//0,0,0,1
			);
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixf(mViewMatrix4.m);
		// 平移相当于上面的： mEye*side,mEye*newUp,mEye*forward,
		//glTranslatef(-mEye.x, -mEye.y, -mEye.z);
		printf("x");
	}

	void Camera::project(float fov, float aspect, float near, float far)
	{
		// fov 是角度值， tan需要求取其弧度，所以整个地方需要转换一次
		// 整个视角是fov，需要取其一半
		float v = Math::tan((fov/2.0f)*Math::Deg2Rad);
		float h = 1.0f/v;			
		float w =  h/aspect;
		float q, qn;
		// 此公式可以见 3D数学基础 P329
		// 参考Ogre GLESRenderSystem::_makeProjectionMatrix
		// Ogre跟书本中写的有差异，但Ogre获取的值跟使用gluPerspective设置的参数是一直的
		// NB This creates Z in range [-1,1]
		//
		// [ w   0   0   0  ]
		// [ 0   h   0   0  ]
		// [ 0   0   q   qn ]
		// [ 0   0   -1  0  ]

		if(far == 0){
			q = Math::EPSINON - 1;
			qn = near *(Math::EPSINON-2);
		}else{
			q = -(far+near)/(far-near);
			qn = -2*(far*near)/(far-near);
		}
		mViewMatrix4.set(
			w,		0,			0,			0,
			0,			h,			0,			0,
			0,			0,			q,			qn,
			0,			0,			-1,			0
			);
		glMatrixMode(GL_PROJECTION);
		glMultMatrixf(mViewMatrix4.m);
	}
}
