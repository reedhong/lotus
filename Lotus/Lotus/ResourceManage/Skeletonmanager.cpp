/********************************************************************
	created:	2012/08/29 
	filename: 	SkeletonManager.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "SkeletonManager.h"

namespace Lotus {
	SkeletonManager::SkeletonManager()
	{

	}

	SkeletonManager::SkeletonManager()
	{

	}

	Resource* SkeletonManager::createImpl(const String& name, const String& path)
	{
		return Skeleton(this, name, path);
	}
}