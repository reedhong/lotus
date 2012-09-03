/********************************************************************
	created:	2012/08/29 
	filename: 	SkeletonManager.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lottus_SkeletonManager_H__
#define __Lottus_SkeletonManager_H__

#include "ResourceManager.h"

namespace Lotus {

	class SkeletonManager: public ResourceManager
	{
	public:
		SkeletonManager();
		virtual ~SkeletonManager();

		virtual Resource* createImpl(const String& name, const String& path);
	};

}

#endif