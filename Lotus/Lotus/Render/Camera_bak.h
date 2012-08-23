/********************************************************************
	created:	2012/08/10 
	filename: 	Camera.h
	author:		reedhong 
	
	purpose:	�����
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
		// �۲��������
		Vector3			mEye;
		Vector3			mCenter;
		Vector3			mUp;
		Matrix4			mViewMatrix4;	// ��ͼ����


		Vector3			mPostion;
		Quaternion	mOrientation;
		

		// ͶӰ�������ԣ� �˴�ֱ�Ӳ�ȡ͸��ͶӰ�ļ������û���������ͶӰ
		float				mFov;		// �ӳ�
		float				mAspect;
		float				mNear;
		float				mFar;
		Matrix4			mProjectMatrix4;	// ͶӰ����

	};

	typedef SharedPtr<Camera> CameraPtr;
}

#endif