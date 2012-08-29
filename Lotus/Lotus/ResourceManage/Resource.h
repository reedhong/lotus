/*
 * 资源基类
 * created by reedhong 2012.08.06
 */

#ifndef __Lotus_Resource_H__
#define __Lotus_Resource_H__


#include "General/Prerequisites.h"

namespace Lotus{
	class ResourceManager;
	class Resource
	{
	public:	
		Resource(ResourceManager* creator, String name, String path);
		virtual ~Resource();

		// 典型的策略模式(strategy)
		virtual void  load();
		virtual void reload();
		virtual void unload();

		// load
		virtual void preLoadImpl() {} 
		virtual void loadImpl() = 0;
		virtual void postLoadImpl() {}
		
		// unload
		virtual void preUnloadImpl() {}
		virtual void unloadImpl()  = 0;
		virtual void postUnloadImpl() {}
		
		virtual size_t calculateSize(void) const = 0;

	protected:
		bool							mIsLoaded;
		ResourceManager*	mCreator;
		String							mName;
		String							mPath;
		size_t							mSize;

	};
	typedef SharedPtr<Resource> ResourcePtr;
} // end Lotus
#endif