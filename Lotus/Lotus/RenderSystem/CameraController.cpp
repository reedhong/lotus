/********************************************************************
	created:	2012/08/12
	filename: 	CameraController.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "CameraController.h"

namespace Lotus {
	CameraController::CameraController():mRotationScaler(1.0f),
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

	void FirstPersonCameraController::	handleAction(CameraAction action)
	{
		//float elapsed_time = InputEngine::Instance()->elapsedTime();
		if (mCameraPtr.isNull())
			return ;

		

		float second = 0.1f;
		float elapsed_time = 0.05f;
		float const scaler = elapsed_time * 10;
		float const angle = 0.03;

		switch (action)
		{
		case eForward:
			mCameraPtr->moveRelative(Vector3(0,0, scaler)*mMoveScaler);			
			break;

		case eBackward:
			mCameraPtr->moveRelative(Vector3(0,0, -scaler)*mMoveScaler);
			break;

		case eMoveLeft:
			mCameraPtr->yaw(Radian(angle*mRotationScaler));
			break;

		case eMoveRight:
			mCameraPtr->yaw(Radian(-angle*mRotationScaler));
			break;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// third controller
	// FirstPersonCameraController
	ThirdPersonCameraController::ThirdPersonCameraController()
	{

	}

	ThirdPersonCameraController::~ThirdPersonCameraController()
	{

	}

	void ThirdPersonCameraController::	handleAction(CameraAction action)
	{
		//float elapsed_time = InputEngine::Instance()->elapsedTime();
		if (mCameraPtr.isNull())
			return ;

		float second = 0.1f;
		float elapsed_time = 0.05f;
		float const scaler = elapsed_time * 10;
		float const angle = 0.03;

		switch (action)
		{
		case eForward:
			mCameraPtr->moveRelative(Vector3(0,0, scaler)*mMoveScaler);			
			break;

		case eBackward:
			mCameraPtr->moveRelative(Vector3(0,0, -scaler)*mMoveScaler);
			break;

		case eMoveLeft:
			mCameraPtr->yaw(Radian(angle*mRotationScaler));
			break;

		case eMoveRight:
			mCameraPtr->yaw(Radian(-angle*mRotationScaler));
			break;
		}
	}
}