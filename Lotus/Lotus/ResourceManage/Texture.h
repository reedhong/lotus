/********************************************************************
	created:	2012/08/10 
	filename: 	Texture.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_Texture_H__
#define __Lotus_Texture_H__

#include "Resource.h"

namespace Lotus {
	class Texture: public Resource 
	{
	public:
		Texture(ResourceManager* creator, const String& name,  const String&path);
		virtual ~Texture() {}
	};
}

#endif