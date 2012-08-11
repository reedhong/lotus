/********************************************************************
	created:	2012/08/10 
	filename: 	SceneManager.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "SceneManager.h"
#include "Render/RenderCommon.h"

namespace Lotus {

	SceneManager::SceneManager()
	{

	}

	SceneManager::~SceneManager()
	{

	}

	bool  SceneManager::_renderScene()
	{
		mRender->clearFrameBuffer(FBT_COLOUR|FBT_DEPTH, 
			Color::White, 1.0f);
		mRender->test();
		mRender->drawCoordinateSystem();
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