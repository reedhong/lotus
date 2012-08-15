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
}

void Game::resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Game::end()
{

}

#define MAX_LEN 100
void Game::frame()
{
	glLoadIdentity();		
	gluLookAt(5,10,10,  0.0,0.0,0.0, 0.0,1.0,0.0);
	
	Root::Instance()->renderOneFrame();
#if 1
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES); // x : R
	glVertex3i(-MAX_LEN,0,0);
	glVertex3i(MAX_LEN,0,0);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES); // y : G
	glVertex3i(0,MAX_LEN,0);
	glVertex3i(0,-MAX_LEN,0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES); // z: B
	glVertex3i(0,0,-MAX_LEN);
	glVertex3i(0,0,MAX_LEN);
	glEnd();
#if 0
	GLColor(0xFF000000);
	//glLineWidth(5);
	glBegin(GL_LINES); // point
	glVertex3i(m_camera.x,m_camera.y,m_camera.z);
	glVertex3i((int)m_pointX, (int)m_pointY, (int)m_pointZ);
	glEnd();
	GLColor(0xFFFFFF00);
	glBegin(GL_LINES); // camera
	//gluLookAt(m_camera.x,  m_camera.y, m_camera.z,m_camera.x,  m_camera.y, 0, 0,1,0);
	glVertex3i(m_camera.x,m_camera.y,m_camera.z);
	glVertex3i(m_camera.x,m_camera.y, 100);
	glEnd();
#endif
#if 1
	glColor3f(0.8, 0.8, 0.8);
	//glPushMatrix();
	//int MAX_LEN = 5120;

	for(int i = -MAX_LEN; i <= MAX_LEN; i += 1)
	{
		if( i ==0) continue;
		glBegin(GL_LINES);				
		glVertex3f(-MAX_LEN, 0, i);					
		glVertex3f(MAX_LEN, 0, i);
		glVertex3f(i, 0, -MAX_LEN);							
		glVertex3f(i, 0,MAX_LEN);
		glEnd();
	}
	//glPopMatrix();
#endif

	glFlush();
#endif
	glFlush();
}

void Game::pause()
{

}

void Game::resume()
{

}
