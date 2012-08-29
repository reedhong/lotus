/********************************************************************
	created:	2012/08/10 
	filename: 	Mesh.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_Mesh_H__
#define __Lotus_Mesh_H__

#include "Resource.h"

namespace Lotus {
	class Mesh: public Resource
	{
		friend class SubMesh;
	public:
		Mesh(ResourceManager* creator, const String& name,  const String&path);
		virtual ~Mesh();
		virtual void loadImpl();
		virtual void unloadImpl();
		virtual size_t calculateSize(void) const;
	private:
		vector<SubMesh *>	mSubMeshes;
	};
}

#endif