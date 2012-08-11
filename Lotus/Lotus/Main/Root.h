/*
 * 模仿LOTUS中Root的作用
 * created by reedhong 2012.07.17
 */

#ifndef __Lotus_Root_H__
#define __Lotus_Root_H__

#include "Singleton.h"

#include "Prerequisites.h"
#include "Render/RenderSystem.h"
#include "Log/LoggerManager.h"
#include "VFS/VFS.h"
#include "SceneManager/SceneManager.h"
#include "Timer.h"

namespace Lotus
{
	class Root: public Singleton<Root>
	{
	private:
		RenderSystem*		mRender;

		SceneManager*		mSceneMgr;
		LoggerManager*		mLoggerManager;
		VFS*							mVFS;

		bool							mIsInitialised;
		bool							mQueuedEnd;

		Timer*						mTimer;
		String							mConfigFileName;
	public:
		Root(const String& configFileName, const String& logFileName);
		~Root();

		void startRendering(void);
		bool renderOneFrame();
		void setRender(RenderSystem* render);
	};

}


#endif