/********************************************************************
	created:	2012/08/10 
	filename: 	SceneManager.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "SceneManager.h"

namespace Lotus {

	SceneManager::SceneManager()
	{

	}

	SceneManager::~SceneManager()
	{

	}

	bool  SceneManager::_renderScene()
	{
		return true;
	}

	Entity*  SceneManager::createEntity(const String& entityName, const String& meshName)
	{
		return 0;
	}

	Entity*  SceneManager::createEntity(const String& meshName)
	{
		return 0;
	}

	void SceneManager::setRender(RenderSystem* render)
	{
		mRender = render;
	}
}