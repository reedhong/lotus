/********************************************************************
	created:	2012/09/11
	filename: 	Game.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/
#include "Engine.h"
#include "RenderSystem/Render.h"
#include "Png/Png.h"
#include "Base/FileStream.h"


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

	Render::Instance()->init(width, height, scale);	
	uint8 header[8];
	FILE* fp = fopen("enemy_xueguai.png", "r");
	fread(header, 1, 8, fp);

	FileStream* stream = new FileStream("enemy_xueguai.png", "r");
	Png* png = Png::loadPng(stream);
	int w = png->m_width;
	int h = png->m_height;
}

void Game::frame()
{
	Render::Instance()->clearScreen(GL_COLOR_WHITE);
	Render::Instance()->setLineWidth(8);
	Render::Instance()->drawRect(10, 10, 200, 100, GL_COLOR_RED);
	Render::Instance()->drawLine(50,50, 400,400, GL_COLOR_GREEN);
}