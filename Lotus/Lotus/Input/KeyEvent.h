/********************************************************************
	created:	2012/08/21 
	filename: 	KeyEvent.h
	author:		reedhong 
	
	purpose:	�����¼�
*********************************************************************/

#ifndef __Lotus_KeyEvent_H__
#define __Lotus_KeyEvent_H__

namespace Lotus {

	class KeyEvent
	{
	public:
		unsigned char	mKey;		
		long					mTime; // �¼�����ʱ�䣺 ΢��
	public:
		KeyEvent(): mKey(0), mTime(0){}
		KeyEvent(unsigned char key, long time):mKey(key), mTime(time) {}
		~KeyEvent() {}
		KeyEvent(const KeyEvent & event)
		{
			this->mKey = event.mKey;
			this->mTime = event.mTime;
		}
		KeyEvent& operator= (const KeyEvent& event)
		{
			this->mKey = event.mKey;
			this->mTime = event.mTime;
			return *this;
		}
	};

	class  KeyListener
	{
	public:
		virtual ~KeyListener() {}
		virtual bool captureKey( const KeyEvent &event ) = 0;
	};

}

#endif