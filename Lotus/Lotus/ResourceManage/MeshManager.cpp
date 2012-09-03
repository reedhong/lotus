/********************************************************************
	created:	2012/08/29 
	filename: 	MeshManager.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "MeshManager.h"
#include "Mesh.h"

namespace Lotus {
	//-----------------------------------------------------------------------
	template<> MeshManager* Singleton<MeshManager>::msInstance = 0;
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