/********************************************************************
	created:	2012/08/12
	filename: 	CameraController.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "CameraController.h"

namespace Lotus {
	CameraController::CameraController():mRotationScaler(0.05f),
		mMoveScaler(-1)
	{

	}

	CameraController::~CameraController()
	{
		
	}

	void CameraController::setScalers(float rotationScaler, float moveScaler)
	{
		mRotationScaler = rotationScaler;
		mMoveScaler = mMoveScaler;
	}

	void CameraController::attachCamera(CameraPtr camera)
	{
		mCameraPtr = camera;
	}

	void CameraController::detachCamera()
	{		
		mCameraPtr.setNull();
	}
	
	//////////////////////////////////////////////////////////////////////////
	// FirstPersonCameraController
	FirstPersonCameraController::FirstPersonCameraController()
	{

	}

	FirstPersonCameraController::~FirstPersonCameraController()
	{

	}

	void FirstPersonCameraController::attachCamera(CameraPtr   camera)
	{
		CameraController::attachCamera(camera);
	}

	void FirstPersonCameraController::move(float x, float y, float z)
	{
		if (mCameraPtr.isNull())
			return ;

		Vector3 movement(x, y, z);
		movement *= mMoveScaler;

		//Vector3 new_eye_pos = mCameraPtr->mEye ;// TODO:+ MathLib::transform_quat(movement, inv_rot_);

		mCameraPtr->lookAt(mCameraPtr->mEye+movement, movement + mCameraPtr->mCenter, 
			mCameraPtr->mUp);
	
	}

	void FirstPersonCameraController::rotate(float yaw, float pitch, float roll)
	{

	}

	void FirstPersonCameraController::	handleAction(CameraAction action)
	{
		//float elapsed_time = InputEngine::Instance()->elapsedTime();
		if (mCameraPtr.isNull())
			return ;

		float second = 0.1f;
		float elapsed_time = 1.0f;
		float const scaler = elapsed_time * 10;

		switch (action)
		{
		case eTurnLeftRight:
			this->rotate(second * scaler, 0, 0);
			break;

		case eTurnUpDown:
			this->rotate(0, second * scaler, 0);
			break;

		case eRollLeft:
			this->rotate(0, 0, -scaler);
			break;

		case eRollRight:
			this->rotate(0, 0, scaler);
			break;

		case eForward:
			this->move(0, 0, scaler);
			break;

		case eBackward:
			this->move(0, 0, -scaler);
			break;

		case eMoveLeft:
			this->move(-scaler, 0, 0);
			break;

		case eMoveRight:
			this->move(scaler, 0, 0);
			break;
		}
	}


}