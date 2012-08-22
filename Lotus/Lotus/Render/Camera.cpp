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
		// �����ҳˣ���������ط���3D��ѧ�����Ͻ�������Ҫת��һ��
		
		mViewMatrix4.set(
			side.x,			side.y,				side.z,				-side*mEye,
			newUp.x,	newUp.y,		newUp.z,		-newUp*mEye,
			-forward.x, -forward.y,	-forward.z,		forward*mEye,
			0,					0,						0,						1
			//0,0,0,1
			);

		glMatrixMode(GL_MODELVIEW);
		glMultMatrixf(mViewMatrix4.transpose()._m);

		Matrix3 m3 = mViewMatrix4.extractMatrix3();
		Quaternion q = mViewMatrix4.extractQuaternion();
		Matrix3 q2m = q.toRotationMatrix();
		// ƽ���൱�������
#if 0
		// ��ת����* ƽ�ƾ���
		Matrix4  mr( 
			side.x,			side.y,				side.z,				0,
			newUp.x,	newUp.y,		newUp.z,		0,
			-forward.x, -forward.y,	-forward.z,		0,
			0,					0,						0,						1
			);

		Matrix4 mt( 
			1, 0, 0, -mEye.x,
			0,1,0, -mEye.y,
			0,0,1, -mEye.z,
			0,0,0,1);

		Matrix4 m = mr*mt
#endif
			
		//glTranslatef(-mEye.x, -mEye.y, -mEye.z);
		printf("x");
	}

	void Camera::project(float fov, float aspect, float near, float far)
	{
		// fov �ǽǶ�ֵ�� tan��Ҫ��ȡ�仡�ȣ����������ط���Ҫת��һ��
		// �����ӽ���fov����Ҫȡ��һ��
		float v = Math::tan((fov/2.0f)*Math::Deg2Rad);
		float h = 1.0f/v;			
		float w =  h/aspect;
		float q, qn;
		// �˹�ʽ���Լ� 3D��ѧ���� P329
		// �ο�Ogre GLESRenderSystem::_makeProjectionMatrix
		// Ogre���鱾��д���в��죬��Ogre��ȡ��ֵ��ʹ��gluPerspective���õĲ�����һֱ��
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
		mProjectMatrix4.set(
			w,		0,			0,			0,
			0,			h,			0,			0,
			0,			0,			q,			qn,
			0,			0,			-1,			0
			);
		glMatrixMode(GL_PROJECTION);
		glMultMatrixf(mProjectMatrix4.transpose()._m);
	}
}
