/********************************************************************
	created:	2012/08/10 
	filename: 	Camera.h
	author:		reedhong 
	
	purpose:	摄像机
*********************************************************************/

#ifndef __Lotus_Camera_H__
#define __Lotus_Camera_H__

#include "General/SharedPtr.h"

#include "Math/Vector3.h"
#include "Math/Matrix4.h"

namespace Lotus {
	class Camera 
	{
	public:
		Camera();
		~Camera();
		
		void setViewMatrix();
		void setProjectMatrix();
		void lookAt(const Vector3& eye);

		void setPosition(const Vector3& vec);
		const Vector3& getPostition(void ) const;

		void setDirection(const Vector3& vec);
		Vector3 getDirection(void) const;
		Vector3 getUp(void) const;

		Quaternion getOrientation();



		// 移动操作
		void move(const Vector3& vec);
		void moveRelative(const Vector3& vec);
	
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

		        /** Tells the camera whether to yaw around it's own local Y axis or a 
			fixed axis of choice.
            @remarks
                This method allows you to change the yaw behaviour of the camera
				- by default, the camera yaws around a fixed Y axis. This is 
				often what you want - for example if you're making a first-person 
				shooter, you really don't want the yaw axis to reflect the local 
				camera Y, because this would mean a different yaw axis if the 
				player is looking upwards rather than when they are looking
                straight ahead. You can change this behaviour by calling this 
				method, which you will want to do if you are making a completely
				free camera like the kind used in a flight simulator. 
            @param
                useFixed If true, the axis passed in the second parameter will 
				always be the yaw axis no matter what the camera orientation. 
				If false, the camera yaws around the local Y.
            @param
                fixedAxis The axis to use if the first parameter is true.
        */
        void setFixedYawAxis( bool useFixed, const Vector3& fixedAxis = Vector3::UNIT_Y );

		void project(float fov, float aspect, float near, float far);
		
	public:
		// 观察矩阵属性
		Matrix4			mViewMatrix4;	// 视图矩阵

		Vector3			mPosition;
		Quaternion	mOrientation;
		
		/// Whether to yaw around a fixed axis.
		bool mYawFixed;
		/// Fixed axis to yaw around
		Vector3 mYawFixedAxis;

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