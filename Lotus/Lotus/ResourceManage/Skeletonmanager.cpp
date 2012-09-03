/********************************************************************
	created:	2012/08/29 
	filename: 	SkeletonManager.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "SkeletonManager.h"
#include "Skeleton.h"

namespace Lotus {
	//-----------------------------------------------------------------------
	template<> SkeletonManager* Singleton<SkeletonManager>::msInstance = 0;
	SkeletonManager::SkeletonManager()
	{

	}

	SkeletonManager::~SkeletonManager()
	{

	}

	Resource* SkeletonManager::createImpl(const String& name, const String& path)
	{
		return LOTUS_NEW Skeleton(this, name, path);
	}
}