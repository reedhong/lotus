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

		mMeshManager = LOTUS_NEW MeshManager();
		mSkeletonManager = LOTUS_NEW SkeletonManager();
	}

	Root::~Root()
	{
		LOTUS_DELETE mLoggerManager;
		LOTUS_DELETE mTimer;
		LOTUS_DELETE mVFS;
		LOTUS_DELETE mSceneMgr;
		LOTUS_DELETE mMeshManager;
		LOTUS_DELETE mSkeletonManager;
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