#include "Root.h"

namespace Lotus{
	template<> Root* Singleton<Root>::msInstance = NULL;

	Root::Root(const String& configFileName, const String& logFileName):
		mRender(NULL), mSceneMgr(NULL), mIsInitialised(false), mQueuedEnd(false)
	{
		mConfigFileName = configFileName;

		mLoggerManager = LOTUS_NEW LoggerManager();
		mLoggerManager->createLog("root", logFileName, true, true);

		mTimer = LOTUS_NEW Timer();
		mVFS = LOTUS_NEW VFS();

		mSceneMgr = LOTUS_NEW SceneManager();
		//mRender->init();
	}

	Root::~Root()
	{
		// TODO:
	}

	void Root::startRendering(void)
	{
		

		// Clear event times
		//clearEventTimes();

		// Infinite loop, until broken out of by frame listeners
		// or break out by calling queueEndRendering()
		mQueuedEnd = false;
		while( !mQueuedEnd )
		{
			//Pump messages in all registered RenderWindow windows
			//WindowEventUtilities::messagePump();

			if (!renderOneFrame())
				break;
		}
	}

	bool Root::renderOneFrame()
	{
		bool bRet = mSceneMgr->_renderScene();
		return bRet;
	}

	void Root::setRender(RenderSystem* render)
	{
		mRender = render;
		ASSERT(mSceneMgr != 0);
		mSceneMgr->setRender(render);
	}
}