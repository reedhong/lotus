/********************************************************************
	created:	2012/08/10 
	filename: 	Mesh.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "Mesh.h"

namespace Lotus {
	Mesh::Mesh(ResourceManager* creator, const String& name,  const String&path):Resource(creator, name, path)
	{

	}

	Mesh::~Mesh()
	{
		unload(); 
	}

	void Mesh::loadImpl()
	{
		MeshSerializer serializer;
	
		StreamPtr data = VFS::Instance()->open(mPath);

		serializer.importMesh(data, this);
	}

	void Mesh::unloadImpl()
	{

	}

	size_t Mesh::calculateSize(void) const
	{
		return 0;
	}
}