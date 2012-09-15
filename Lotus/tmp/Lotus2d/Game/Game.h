/********************************************************************
	created:	2012/09/11
	filename: 	Game.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Game_H__
#define __Game_H__

#include "RenderSystem/Texture.h"

using namespace Lotus2d;

class Game 
{
public:
	Game();
	~Game();
	static Game * Instance(void);
public:
	void startup(int width,int height,float scale=1.0);
	void frame();

private:
	Texture* mTexture;
};

#endif 
