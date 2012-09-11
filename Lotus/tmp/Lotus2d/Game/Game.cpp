/********************************************************************
	created:	2012/09/11
	filename: 	Game.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/
#include "Engine.h"
#include "RenderSystem/ES1Render.h"

using namespace  Lotus2d;

#include "Game.h"


Game::Game()
{

}


Game::~Game()
{

}

Game * Game::Instance(void)
{
	static Game s_game;
	return &s_game;
}


void Game::startup(int width,int height,float scale)
{
	int* p = new int;
	ES1Render* render = new ES1Render();
	Engine::Instance()->setRender(render);
	
	//render->setOrthoView(0, (float)width, (float)height, 0, -99999, 99999);
	render->setViewport(0, 0, width, height);

}

void Game::frame()
{
	Engine::Instance()->getRender()->test();
}