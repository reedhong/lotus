/********************************************************************
	created:	2012/08/29 
	filename: 	MeshManager.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "MeshManager.h"
#include "Mesh.h"

namespace Lotus {
	MeshManager::MeshManager()
	{

	}

	MeshManager::~MeshManager()
	{

	}

	Resource* MeshManager::createImpl(const String& name, const String& path)
	{
		return LOTUS_NEW Mesh(this, name, path);
	}
}