/********************************************************************
	created:	2012/08/29 
	filename: 	Skeleton.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_Skeleton_H__
#define __Lotus_Skeleton_H__

#include "Resource.h"

namespace Lotus {
	class Skeleton: public Resource
	{
	public:
		Skeleton(ResourceManager* creator, const String& name,  const String&path);
		virtual ~Skeleton();
		virtual void loadImpl();
		virtual void unloadImpl();
		virtual size_t calculateSize(void) const;
	};
}

#endif