/********************************************************************
	created:	2012/08/21 
	filename: 	InputEngine.h
	author:		reedhong 
	
	purpose:	抽象一个简单的输入引擎，负责处理交互事件
	事件暂时分两种:
	1. 点击事件: MotionEvent: 类型，时间，坐标
	2. 键盘事件: KeyEvent： 类型, 时间，值
	整个地方设计存在的问题是：
	游戏处于不同才状态，事件处理差异非常大，如何做到能够规避这些差异呢？
*********************************************************************/

#ifndef __Lotus_InputEngine_H__
#define __Lotus_InputEngine_H__


#include "Main/Prerequisites.h"
#include "Main/Timer.h"
#include "Main/Singleton.h"

#include "KeyEvent.h"
#include "MotionEvent.h"

namespace Lotus {		

	class InputEngine: public Singleton<InputEngine>
	{
	public:
		InputEngine();
		~InputEngine();
		
		/*
		 * 添加键盘事件
		 */
		void addEvent(unsigned char key);

		/*
		 * 添加点击事件
		 */
		void addEvent(unsigned char status, int x, int y);

		void addEvent(const KeyEvent &event);
		void addEvent(const MotionEvent& event);

		void setKeyListener(KeyListener* listener)
		{
			mKeyListener = listener;
		}
		void setMotionListener(MotionListener* listener)
		{
			mMotionListenr = listener;
		}

		/** 更新处理**/
		void update();

	private:
		KeyListener*				mKeyListener;
		MotionListener*		mMotionListenr;

		vector<KeyEvent>			mKeyEvents;		
		vector<MotionEvent>	mMotionEvents;
		Timer									mTimer;
	};
}


#endif