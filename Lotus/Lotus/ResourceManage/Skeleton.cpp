/********************************************************************
	created:	2012/08/29 
	filename: 	Skeleton.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "Skeleton.h"

namespace Lotus {
	Skeleton::Skeleton(ResourceManager* creator, const String& name,  const String&path):Resource(creator, name, path)
	{

	}
	
	Skeleton::~Skeleton()
	{
		unload(); 
	}

	void Skeleton::loadImpl()
	{

	}

	void Skeleton::unloadImpl()
	{

	}

	size_t Skeleton::calculateSize(void) const
	{
		return 0;
	}

}