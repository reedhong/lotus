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
		
		void lookAt(const Vector3& eye);

		void setPosition(const Vector3& vec);
		const Vector3& getPostition(void ) const;

		void setDirection(const Vector3& vec);
		Vector3 getDirection(void) const;
		Vector3 getUp(void) const;

		// �ƶ�����
		void move(const Vector3& vec);
	
		//////////////////////////////////////////////////////////////////////////
		// ������ת����
        /** Rolls the camera anticlockwise, around its local z axis.
        */
        void roll(const Radian& angle);

        /** Rotates the camera anticlockwise around it's local y axis.
        */
        void yaw(const Radian& angle);

        /** Pitches the camera up/down anticlockwise around it's local z axis.
        */
        void pitch(const Radian& angle);

        /** Rotate the camera around an arbitrary axis.
        */
        void rotate(const Vector3& axis, const Radian& angle);

        /** Rotate the camera around an arbitrary axis using a Quaternion.
        */
        void rotate(const Quaternion& q);
		/// end rotate

		void project(float fov, float aspect, float near, float far);
		
	public:
		// �۲��������
		Matrix4			mViewMatrix4;	// ��ͼ����

		Vector3			mPosition;
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