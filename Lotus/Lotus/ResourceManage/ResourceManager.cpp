#include "ResourceManager.h"

namespace Lotus{

	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{
		removeAll();
	}

	ResourcePtr ResourceManager::create(const String& name, const String& path)
	{
		ResourcePtr ret = ResourcePtr(createImpl(name, path));		
		return ret;
	}

	ResourceManager::ResourceCreateOrRetrieveResult ResourceManager::createOrRetrieve(const String& name, 
		const String& path)
	{
		ResourcePtr res = getByName(name);
		bool created = false;
		if (res.isNull())
		{
			created = true;
			res = create(name, path);
		}

		return ResourceCreateOrRetrieveResult(res, created);
	}

	ResourcePtr ResourceManager::load(const String& name, const String& path)
	{
		ResourcePtr r = createOrRetrieve(name,path).first;
		// ensure loaded
		r->load();
		return r;
	}

	void ResourceManager::unload(const String& name)
	{
		ResourcePtr res = getByName(name);
		if (!res.isNull())
		{
			// Unload resource
			res->unload();
		}
	}

	void ResourceManager::unloadAll()
	{
		ResourceMap::iterator i, iend;
		iend = mResources.end();
		for (i = mResources.begin(); i != iend; ++i){			
			i->second->unload();
		}	
	}

	void ResourceManager::remove(const String& name)
	{
		ResourceMap::iterator nameIt = mResources.find(name);
		if (nameIt != mResources.end())
		{
			mResources.erase(nameIt);
		}
	}

	void ResourceManager::removeAll()
	{
		mResources.clear();
	}

	bool ResourceManager::resourceExists(const String& name)
	{
		return !getByName(name).isNull();
	}

	ResourcePtr ResourceManager::getByName(const String& name)
	{
		ResourcePtr res;
		ResourceMap::iterator it = mResources.find(name);
		if( it != mResources.end())
		{
			res = it->second;
		}
		return res;
	}
}