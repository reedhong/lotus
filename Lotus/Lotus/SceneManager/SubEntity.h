/********************************************************************
	created:	2012/08/10 
	filename: 	SubEntity.h
	author:		reedhong 
	
	purpose:	SubEntity-> SubMesh
*********************************************************************/

#ifndef __Lotus_SubEntity_H__
#define __Lotus_SubEntity_H__

#include "Renderable.h"
#include "ResourceManage/SubMesh.h"

namespace Lotus {
	class SubEntity: public Renderable
	{
	protected:

		/// Pointer to parent.
		Entity* mParentEntity;

		/// Name of Material in use by this SubEntity.
		String mMaterialName;

		/// Cached pointer to material.
		// MaterialPtr mMaterial; TODO

		// Pointer to the SubMesh defining geometry.
		SubMesh* mSubMesh;
	protected:	
		SubEntity(Entity* parent, SubMesh* subMeshBasis);
		virtual ~SubEntity();



	};
}

#endif