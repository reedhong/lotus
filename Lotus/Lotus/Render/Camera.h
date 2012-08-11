/********************************************************************
	created:	2012/08/10 
	filename: 	Camera.h
	author:		reedhong 
	
	purpose:	ÉãÏñ»ú
*********************************************************************/

#ifndef __Lotus_Camera_H__
#define __Lotus_Camera_H__

#include "Main/SharedPtr.h"

namespace Lotus {
	class Camera 
	{
	public:
		Camera();
		~Camera();
	};

	typedef SharedPtr<Camera> CameraPtr;
}

#endif