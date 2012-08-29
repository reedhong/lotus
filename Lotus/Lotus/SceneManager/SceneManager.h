/********************************************************************
	created:	2012/08/10 
	filename: 	SceneManager.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_SceneManager_H__
#define __Lotus_SceneManager_H__

#include "General/Prerequisites.h"

#include "SceneManager.h"
#include "Render/Camera.h"
#include "Entity.h"
#include "Render/RenderSystem.h"

namespace Lotus {
	class SceneManager 
	{
	protected:
		Camera*		mCamera;
		vector<Entity*>	mEntities;
		RenderSystem*	mRender;
	public:
		SceneManager();
		virtual ~SceneManager();
		
		virtual bool  _renderScene();
		virtual Entity*  createEntity(const String& entityName, const String& meshName);
		virtual Entity*  createEntity(const String& meshName);
		virtual void setRender(RenderSystem* render);

	};
}


#endif