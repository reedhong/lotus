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