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
		//float2		rot_x_;
		//float2		rot_y_;
		//float2		rot_z_;
		Quaternion	mQuat;
	};

}

#endif
