/*
 * 相应资源的管理类
 * created by reedhong 2012.08.06
 */

#ifndef __Lotus_ResourceManager_H__
#define __Lotus_ResourceManager_H__

#include "Resource.h"

namespace Lotus {

	class ResourceManager
	{
	public:
		ResourceManager();
		virtual ~ResourceManager();
		virtual ResourcePtr create(const String& name, const String& path);
		virtual Resource* createImpl(const String& name, const String& path) = 0;
		typedef std::pair<ResourcePtr, bool> ResourceCreateOrRetrieveResult;
		virtual ResourceCreateOrRetrieveResult createOrRetrieve(const String& name, 
			const String& path);

		virtual ResourcePtr load(const String& name, const String& path);

		virtual void unload(const String& name);
		virtual void unloadAll();

		virtual void remove(const String& name);
		virtual void removeAll(void);
		
		virtual bool resourceExists(const String& name);
		virtual ResourcePtr getByName(const String& name);

		const String& getResourceType(void) const { return mResourceType; }

	public:
		// TODO: 暂时用map顶上
		typedef map< String, ResourcePtr > ResourceMap;
	protected:
		ResourceMap mResources;
		String mResourceType; 
	};
}

#endif
