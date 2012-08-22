/********************************************************************
	created:	2012/08/12
	filename: 	CameraController.h
	author:		reedhong
	
	purpose:	摄像机控制器, 裁剪自KlayGE
*********************************************************************/

#ifndef __Lotus_CameraController_H__
#define __Lotus_CameraController_H__

#include "Main/Prerequisites.h"

#include "Camera.h"
#include "Math/Quaternion.h"

namespace Lotus {
	class CameraController 
	{
	public:
		CameraController();
		virtual ~CameraController();

		void setScalers(float rotationScaler, float moveScaler);

		virtual void attachCamera(CameraPtr   camera);
		void detachCamera();

	protected:
		float		mRotationScaler;	// Scaler for rotation
		float		mMoveScaler;		// Scaler for movement

		CameraPtr		mCameraPtr;
	
	};

	class FirstPersonCameraController: public CameraController
	{
	public:
		enum CameraAction
		{
			eTurnLeftRight,
			eTurnUpDown,
			eRollLeft,
			eRollRight,

			eForward,
			eBackward,
			eMoveLeft,
			eMoveRight
		};
	public:
		FirstPersonCameraController();
		virtual ~FirstPersonCameraController();
		virtual void attachCamera(CameraPtr   camera);

		void move(float x, float y, float z);
		void rotate(float yaw, float pitch, float roll);

		void handleAction(CameraAction action);

	private:
		// 此处我们用三元向量标识位置，四元数标识摄像机才方位
		Vector3			mPostition;
		Quaternion	mOrientation;
	};

}

#endif
