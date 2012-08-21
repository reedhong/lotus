/********************************************************************
	created:	2012/08/21 
	filename: 	MotionEvent.h
	author:		reedhong 
	
	purpose:  ����¼�
*********************************************************************/

#ifndef __Lotus_MotionEvent_H__
#define __Lotus_MotionEvent_H__

namespace Lotus {

	class MotionEvent
	{
	public:
		unsigned char	mType;			
		int						mX;		// ʱ�䷢��������
		int						mY;	
		long					mTime; // �¼�����ʱ�䣺 ΢��

	public:
		MotionEvent(): mType(0), mX(0), mY(0), mTime(0){}
		MotionEvent(unsigned char type, int x, int y,  long time): 
			mType(type), mX(x), mY(y), mTime(time){}
		~MotionEvent() {}
		MotionEvent(const MotionEvent & event)
		{
			this->mType = event.mType;
			this->mTime = event.mTime;
			this->mX = event.mX;
			this->mY = event.mY;
		}
		MotionEvent& operator= (const MotionEvent& event)
		{
			this->mType = event.mType;
			this->mTime = event.mTime;
			this->mX = event.mX;
			this->mY = event.mY;
			return *this;
		}
	};

	class  MotionListener
	{
	public:
		virtual ~MotionListener() {}
		virtual bool captureMotion( const MotionEvent &arg ) = 0;
	};
}

#endif

