/********************************************************************
	created:	2012/08/10 
	filename: 	TextureManager.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_TextureManager_H__
#define __Lotus_TextureManager_H__

#include "ResourceManager.h"
#include "Main/Singleton.h"

namespace Lotus {
	class TextureManager:  public ResourceManager, public Singleton<TextureManager>
	{
	public:
		TextureManager();
		virtual ~TextureManager();
	};
}

#endif