/********************************************************************
	created:	2012/08/12
	filename: 	CameraController.h
	author:		reedhong
	
	purpose:	ÉãÏñ»ú¿ØÖÆÆ÷, ²Ã¼ô×ÔKlayGE
*********************************************************************/

#ifndef __Lotus_CameraController_H__
#define __Lotus_CameraController_H__

#include "Camera.h"

namespace Lotus {
	class CameraController 
	{
	public:
		CameraController();
		virtual ~CameraController();

		void setScalers(float rotationScaler, float moveScaler);

		virtual void attachCamera(Camera& camera);
		void detachCamera();

	protected:
		float		mRotationScaler;	// Scaler for rotation
		float		mMoveScaler;		// Scaler for movement

		Camera*		mCameraPtr;
	
	};
}

#endif
