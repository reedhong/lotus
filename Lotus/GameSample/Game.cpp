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

using namespace Lotus;

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init()
{
	Root* root  = new Root("./main.cfg", "root.log");
	GLRenderSystem* render = new GLRenderSystem();
	root->setRender(render);

	return true;
}

void Game::start()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (TRUE)
	{
		//		AxProfile::AxProfile_PushNode("Msg");
		//读取出消息队列中的所有消息并处理
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{ 
			//如果是退出消息,退出
			if (msg.message == WM_QUIT)  return;

			//处理其他消息
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		};
		
		if( !Root::Instance()->renderOneFrame() )
			break;
	}
}