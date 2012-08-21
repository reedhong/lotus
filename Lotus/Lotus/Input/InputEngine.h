/********************************************************************
	created:	2012/08/21 
	filename: 	InputEngine.h
	author:		reedhong 
	
	purpose:	����һ���򵥵��������棬���������¼�
	�¼���ʱ������:
	1. ����¼�: MotionEvent: ���ͣ�ʱ�䣬����
	2. �����¼�: KeyEvent�� ����, ʱ�䣬ֵ
	�����ط���ƴ��ڵ������ǣ�
	��Ϸ���ڲ�ͬ��״̬���¼��������ǳ�����������ܹ������Щ�����أ�
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
		 * ��Ӽ����¼�
		 */
		void addEvent(unsigned char key);

		/*
		 * ��ӵ���¼�
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

		/** ���´���**/
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