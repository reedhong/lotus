/********************************************************************
	created:	2012/08/11
	filename: 	Game.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Game.h"
#include "Main/Timer.h"
#include "Main/Root.h"
#include "Render/OpenGL/GLRenderSystem.h"

#include <GL/glew.h>

using namespace Lotus;

Game::Game()
{

}

Game::~Game()
{

}

void Game::startup(int width,int height,float scale)
{
	Root* root  = new Root("./main.cfg", "root.log");
	GLRenderSystem* render = new GLRenderSystem();
	root->setRender(render);
	
	glViewport(0,0,800,600);						// 重置当前的视口

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);

}

void Game::end()
{

}

void Game::frame()
{
	gluLookAt(0,0,100, 0, 0, 0, 0, 1, 0);
	glLoadIdentity();		
	Root::Instance()->renderOneFrame();
}

void Game::pause()
{

}

void Game::resume()
{

}
