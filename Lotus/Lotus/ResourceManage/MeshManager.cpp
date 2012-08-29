/********************************************************************
	created:	2012/08/29 
	filename: 	MeshManager.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "MeshManager.h"

namespace Lotus {
	MeshManager::MeshManager()
	{

	}

	MeshManager::MeshManager()
	{

	}

	Resource* MeshManager::createImpl(const String& name, const String& path)
	{
		return Mesh(this, name, path);
	}
}