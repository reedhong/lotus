/********************************************************************
	created:	2012/08/29 
	filename: 	MeshManager.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lottus_MeshManager_H__
#define __Lottus_MeshManager_H__

#include "ResourceManager.h"

namespace Lotus {

	class MeshManager: public ResourceManager
	{
	public:
		MeshManager();
		virtual MeshManager();

		virtual Resource* createImpl(const String& name, const String& path);
	};

}

#endif