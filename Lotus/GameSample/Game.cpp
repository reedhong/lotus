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
#include "Render/Camera.h"

#include <GL/glew.h>
#include "Input/InputEngine.h"

using namespace Lotus;

static void  drawGrid()
{
	for(float i = -500; i <= 500; i += 5)
	{
		glBegin(GL_LINES);
		glColor3ub(150, 190, 150);						
		glVertex3f(-500, 0, i);					
		glVertex3f(500, 0, i);
		glVertex3f(i, 0,-500);							
		glVertex3f(i, 0, 500);
		glEnd();
	}
}

void Draw_Character() // This object will symbolize our character
{
	//glScalef(0.3f,1.0f,0.3f);
	glTranslatef(0,1.0f,0);
	glBegin(GL_TRIANGLES);				
	glColor3f(1.0f,0.0f,0.0f);				
	glVertex3f( 0.0f, 1.0f, 0.0f);			
	glVertex3f(-1.0f,-1.0f, 1.0f);			
	glVertex3f( 1.0f,-1.0f, 1.0f);		
	glVertex3f( 0.0f, 1.0f, 0.0f);						
	glVertex3f( 1.0f,-1.0f, 1.0f);					
	glVertex3f( 1.0f,-1.0f, -1.0f);					
	glVertex3f( 0.0f, 1.0f, 0.0f);					
	glVertex3f( 1.0f,-1.0f, -1.0f);					
	glVertex3f(-1.0f,-1.0f, -1.0f);						
	glVertex3f( 0.0f, 1.0f, 0.0f);					
	glVertex3f(-1.0f,-1.0f,-1.0f);					
	glVertex3f(-1.0f,-1.0f, 1.0f);			
	glEnd();
}

Game::Game()
{
	InputEngine* inputEngine = new InputEngine();
	InputEngine::Instance()->setKeyListener(this);
	InputEngine::Instance()->setMotionListener(this);

	Camera* camera = new Camera();
	mCameraPtr = SharedPtr<Camera>(camera);
	mMove = Vector3::ZERO;
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
#if 1
	Camera camera;
	mCameraPtr->project(45.0, (GLfloat)w/(GLfloat)h, 1.0, 1000.0);
	mCameraPtr->setProjectMatrix();
	//mCameraPtr->lookAt(Vector3(5,10,10),  Vector3( 0.0,0.0,0.0), Vector3(0.0,1.0,0.0));
	//mCameraPtr->setPosition(Vector3(5,10,10));
	//mCameraPtr->lookAt(Vector3(0,0,0));
	mCameraPtr->setPosition(Vector3(1, 2.5f, 5));
	mCameraPtr->lookAt(Vector3(0, 2.5f, 0));
	mCameraPtr->setViewMatrix();
	//mCameraPtr->lookAt(Vector3(0, 2.5f, 5),  Vector3(0, 2.5f, 0), Vector3(0, 1, 0));
	mCameraController.attachCamera(mCameraPtr);
#else
	gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 1000.0);
#endif
	GLfloat mat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, mat);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Game::end()
{

}

void Game::frame()
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();		
#if 0
	//gluLookAt(0, 2.5f, 5,  00, 2.5f, 0, 0.0,1.0,0.0);
	gluLookAt(5,10,10, 0, 0 ,0,0, 1, 0);
#else
	//Matrix4 m4 = Matrix4::MakeViewMatrix(mCameraPtr->getPostition(), 
	//	mCameraPtr->getOrientation());
	
	//glLoadMatrixf(m4.transpose()._m);

	//mCameraPtr->lookAt(mCameraPtr->mEye,  mCameraPtr->mCenter, 
	//	mCameraPtr->mUp);
	mCameraPtr->setViewMatrix();
#endif
	GLfloat mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	Root::Instance()->renderOneFrame();
	drawGrid();
	
	glPushMatrix();
	glTranslatef(mMove.x, 0, mMove.z);
	Draw_Character();
	glPopMatrix();


	glBegin(GL_QUADS);						
		glColor3f(0.0f,1.0f,0.0f);			
		glVertex3f( 1.0f, 1.0f,-1.0f);		
		glVertex3f(-1.0f, 1.0f,-1.0f);		
		glVertex3f(-1.0f, 1.0f, 1.0f);		
		glVertex3f( 1.0f, 1.0f, 1.0f);		
		glColor3f(1.0f,0.5f,0.0f);			
		glVertex3f( 1.0f,-1.0f, 1.0f);		
		glVertex3f(-1.0f,-1.0f, 1.0f);		
		glVertex3f(-1.0f,-1.0f,-1.0f);		
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glColor3f(1.0f,0.0f,0.0f);			
		glVertex3f( 1.0f, 1.0f, 1.0f);		
		glVertex3f(-1.0f, 1.0f, 1.0f);		
		glVertex3f(-1.0f,-1.0f, 1.0f);		
		glVertex3f( 1.0f,-1.0f, 1.0f);		
		glColor3f(1.0f,1.0f,0.0f);			
		glVertex3f( 1.0f,-1.0f,-1.0f);		
		glVertex3f(-1.0f,-1.0f,-1.0f);		
		glVertex3f(-1.0f, 1.0f,-1.0f);		
		glVertex3f( 1.0f, 1.0f,-1.0f);		
		glColor3f(0.0f,0.0f,1.0f);			
		glVertex3f(-1.0f, 1.0f, 1.0f);		
		glVertex3f(-1.0f, 1.0f,-1.0f);		
		glVertex3f(-1.0f,-1.0f,-1.0f);		
		glVertex3f(-1.0f,-1.0f, 1.0f);		
		glColor3f(1.0f,0.0f,1.0f);			
		glVertex3f( 1.0f, 1.0f,-1.0f);		
		glVertex3f( 1.0f, 1.0f, 1.0f);		
		glVertex3f( 1.0f,-1.0f, 1.0f);		
		glVertex3f( 1.0f,-1.0f,-1.0f);		
	glEnd();

	glFlush();

	InputEngine::Instance()->update();
}

void Game::pause()
{

}

void Game::resume()
{

}


bool Game::captureKey(const KeyEvent& event)
{
	unsigned char key = event.mKey;


	float const scaler = 0.1f;
	float const angle = 0.03;
	switch(key){
		case 'A':
		case 'a':
			{
			//mCameraPtr->rotate(Vector3(mMove.x, 1, mMove.z), Radian(angle));
			mCameraPtr->setFixedYawAxis(false);
			mCameraPtr->yaw(Radian(angle));//, Vector3(mMove.x, 1, mMove.z));
			}
			//mRotate += Radian(angle);
			break;
		case 'D':
		case 'd':
			mCameraPtr->yaw(Radian(-angle));//, Vector3(mMove.x, 1, mMove.z));
			mCameraPtr->setFixedYawAxis(false);
			//mRotate += Radian(-angle);
			break;
		case 'W':
		case 'w':
			{
				mCameraPtr->moveRelative(Vector3(0,0, -scaler));			
				Vector3 trans =mCameraPtr->getOrientation()* Vector3(0,0, -scaler);
				mMove += trans;
			}
			break;
		case 'S':
		case 's':
			{
				mCameraPtr->moveRelative(Vector3(0,0, scaler));
				Vector3 trans =mCameraPtr->getOrientation()* Vector3(0,0, scaler);
				mMove += trans;
			}
			break;

	}
	return true;
}

bool Game::captureMotion(const MotionEvent& event)
{
	return true;
}
