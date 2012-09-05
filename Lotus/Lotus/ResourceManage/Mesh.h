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
        /** Shared vertex data.
            @remarks
                This vertex data can be shared among multiple submeshes. SubMeshes may not have
                their own VertexData, they may share this one.
            @par
                The use of shared or non-shared buffers is determined when
                model data is converted to the OGRE .mesh format.
        */
        VertexData *sharedVertexData;
	};
}

#endif