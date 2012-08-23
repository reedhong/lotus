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
		
		void lookAt(const Vector3& eye);

		void setPosition(const Vector3& vec);
		const Vector3& getPostition(void ) const;

		void setDirection(const Vector3& vec);
		Vector3 getDirection(void) const;
		Vector3 getUp(void) const;

		// 移动操作
		void move(const Vector3& vec);
	
		//////////////////////////////////////////////////////////////////////////
		// 各种旋转操作
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
		// 观察矩阵属性
		Matrix4			mViewMatrix4;	// 视图矩阵

		Vector3			mPosition;
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