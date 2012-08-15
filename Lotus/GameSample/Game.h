/********************************************************************
	created:	2012/08/11
	filename: 	Game.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_Game_H__
#define __Lotus_Game_H__

class Game
{
public:
	Game();
	~Game();
public:
	void startup(int width,int height,float scale = 1.0f);

	void resize(int w, int h);

	void end();

	void frame();

	void pause();

	void resume();
};

#endif