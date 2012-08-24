/********************************************************************
	created:	2012/08/12
	filename: 	CameraController.h
	author:		reedhong
	
	purpose:	ÉãÏñ»ú¿ØÖÆÆ÷, ²Ã¼ô×ÔKlayGE
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
			eForward,
			eBackward,
			eMoveLeft,
			eMoveRight
		};
	public:
		FirstPersonCameraController();
		virtual ~FirstPersonCameraController();

		void handleAction(CameraAction action);

	};

	class ThirdPersonCameraController: public CameraController
	{
	public:
		enum CameraAction
		{
			eForward,
			eBackward,
			eMoveLeft,
			eMoveRight
		};
	public:
		ThirdPersonCameraController();
		virtual ~ThirdPersonCameraController();

		void handleAction(CameraAction action);

	};

}

#endif
