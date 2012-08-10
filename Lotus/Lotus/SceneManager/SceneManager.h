/********************************************************************
	created:	2012/08/10 
	filename: 	SceneManager.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_SceneManager_H__
#define __Lotus_SceneManager_H__

#include "Main/Prerequisites.h"

#include "SceneManager.h"
#include "Camera.h"
#include "Entity.h"

namespace Lotus {
	class SceneManager 
	{
	protected:
		Camera*		mCamera;
		vector<Entity*>	mEntities;
	public:
		SceneManager();
		virtual ~SceneManager();
		
		virtual bool  _renderScene();
		virtual Entity*  createEntity(const String& entityName, const String& meshName);
		virtual Entity*  createEntity(const String& meshName);

	};
}


#endif