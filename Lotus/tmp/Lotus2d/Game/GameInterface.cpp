/********************************************************************
	created:	2012/09/11
	filename: 	GameInterface.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/
#include "GameInterface.h"
#include "Game.h"

#include "Engine.h"

using namespace  Lotus2d;

void gameStartup(int width,int height,float scale)
{
	Game::Instance()->startup(width, height, scale);

}

void gameEnd()
{

}

void gameFrame()
{
	Game::Instance()->frame();
}

void gamePause()
{

}

void gameResume()
{

}