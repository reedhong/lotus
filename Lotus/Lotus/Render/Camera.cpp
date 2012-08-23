/********************************************************************
	created:	2012/08/10 
	filename: 	Camera.cpp
	author:		reedhong 
	
	purpose:	Camera
*********************************************************************/

#include <GL/glew.h>
#include "Camera.h"

namespace Lotus {
	Camera::Camera():mOrientation(Quaternion::IDENTITY),
		mPosition(Vector3::ZERO)
	{
		
	}

	Camera::~Camera()
	{

	}


	void Camera::lookAt(const Vector3& eye)
	{
		 this->setDirection(eye - mPosition);
	}

	void Camera::setPosition(const Vector3& vec)
	{
		mPosition = vec;
	}

	const Vector3& Camera::getPostition(void ) const
	{
		return mPosition;
	}

	void Camera::setDirection(const Vector3& vec)
	{
		// eye和position在同一个位置
		if(vec == Vector3::ZERO) return ;
		// Remember, camera points down -Z of local axes!
		// Therefore reverse direction of direction vector before determining local Z
		Vector3 zAdjustVec = -vec;
		zAdjustVec.normalize();

		Quaternion targetWorldOrientation;

		Vector3 axes[3];
		//updateView();
		mOrientation.toAxes(axes);
		Quaternion rotQuat;
		if ( (axes[2]+zAdjustVec).squaredLength() <  0.00005f) 
		{
			// Oops, a 180 degree turn (infinite possible rotation axes)
			// Default to yaw i.e. use current UP
			rotQuat.fromAngleAxis(Radian(Math::PI), axes[1]);
		}
		else
		{
			// Derive shortest arc to new direction
			rotQuat = axes[2].getRotationTo(zAdjustVec);

		}
		targetWorldOrientation = rotQuat * mOrientation;
		
		mOrientation = targetWorldOrientation;

		Matrix4 m4 = Matrix4::MakeViewMatrix(mPosition, mOrientation);
	}

	Vector3 Camera::getDirection(void)  const
	{
		// Direction points down -Z by default
		return mOrientation * -Vector3::UNIT_Z;
	}

	Vector3 Camera::getUp(void) const
	{
		return mOrientation * Vector3::UNIT_Y;
	}

    /** Rolls the camera anticlockwise, around its local z axis.
    */
    void Camera::roll(const Radian& angle)
	{

	}

    /** Rotates the camera anticlockwise around it's local y axis.
    */
    void Camera::yaw(const Radian& angle)
	{

	}

    /** Pitches the camera up/down anticlockwise around it's local z axis.
    */
    void Camera::pitch(const Radian& angle)
	{

	}


    /** Rotate the camera around an arbitrary axis.
    */
    void Camera::rotate(const Vector3& axis, const Radian& angle)
	{

	}

    /** Rotate the camera around an arbitrary axis using a Quaternion.
    */
    void Camera::rotate(const Quaternion& q)
	{

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
