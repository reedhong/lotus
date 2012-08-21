/********************************************************************
	created:	2012/08/21 
	filename: 	InputEngine.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "InputEngine.h"

namespace Lotus {
	template<> InputEngine* Singleton<InputEngine>::msInstance = NULL;
	InputEngine::InputEngine():mKeyListener(NULL), mMotionListenr(NULL)
	{		
	}

	InputEngine::~InputEngine()
	{

	}

	void InputEngine::addEvent(unsigned char key)
	{
		KeyEvent event(key, mTimer.getMicroseconds());
		mKeyEvents.push_back(event);
	}
		
	void InputEngine::addEvent(unsigned char status, int x, int y)
	{
		MotionEvent event(status, x ,y, mTimer.getMicroseconds());
		mMotionEvents.push_back(event);
	}

	void InputEngine::addEvent(const KeyEvent &event)
	{
		mKeyEvents.push_back(event);
	}

	void InputEngine::addEvent(const MotionEvent& event)
	{
		mMotionEvents.push_back(event);
	}

	void InputEngine::update()
	{
		vector<KeyEvent>::iterator keyIter = mKeyEvents.begin();
		for(; keyIter != mKeyEvents.end(); ++keyIter){
			mKeyListener->captureKey(*keyIter);
		}
		mKeyEvents.clear();

		vector<MotionEvent>::iterator motionIter = mMotionEvents.begin();
		for(; motionIter != mMotionEvents.end();  ++motionIter){
			mMotionListenr->captureMotion(*motionIter);
		}
		mMotionEvents.clear();
	}
}