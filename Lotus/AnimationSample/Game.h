/********************************************************************
	created:	2012/09/03
	filename: 	Game.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Lotus_Game_H__
#define __Lotus_Game_H__

#include "Input/KeyEvent.h"
#include "Input/MotionEvent.h"
#include "Render/Camera.h"
#include "Render/CameraController.h"
#include "General/Root.h"

using namespace Lotus;

typedef enum{
	Touch_Down = 0,
	Touch_Move,
	Touch_End
};

class Game: public KeyListener, MotionListener
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
	
	virtual bool captureKey( const KeyEvent &event );
	virtual bool captureMotion(const MotionEvent& event);
private:
	CameraPtr	mCameraPtr;
	FirstPersonCameraController	mCameraController;
	Vector3		mMove;
	Radian		mRotate;
	Root*			mRoot;

};

#endif