/********************************************************************
	created:	2012/08/29 
	filename: 	Resource.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "Resource.h"
#include "ResourceManager.h"

namespace Lotus{

	Resource::Resource(ResourceManager* creator, String name, String path):
		mCreator(creator), mName(name), mPath(path), mIsLoaded(false), mSize(0)
	{

	}

	Resource::~Resource()
	{

	}

	void  Resource::load()
	{
		if(!mIsLoaded){
			preLoadImpl();
			loadImpl();
			postLoadImpl();
			mSize = calculateSize();
			mIsLoaded = true;
		}

	}

	void Resource::reload()
	{
		if( mIsLoaded){
			unload();
			load();
		}
	}

	void Resource::unload()
	{
		if( mIsLoaded){
			preUnloadImpl();
			unloadImpl();
			postUnloadImpl();
			mIsLoaded = false;
		}
	}

} // end Lotus