/*
 * ����ģʽ
 * �̳е������࣬��һ���ط������������ط���ͨ��Instance��õ���, �ͷŹ����ɴ�������
 * ���һ���������Ҫ����msInstance=0;
 * ���TestSingleton.cpp
 * created by reedhong fishwarter@gmail.com 2012.07.16
 */

#ifndef __Lotus_Singleton_H__
#define __Lotus_Singleton_H__

#include "Macro.h"

namespace Lotus{
	template <typename T> class Singleton
	{
	private:
		Singleton(const Singleton<T> &);
		Singleton& operator=(const Singleton<T> &);
	protected:
		static T* msInstance;
	public:
		Singleton(){
			ASSERT(!msInstance);  // ������ָö���ֻ������һ��
			msInstance = static_cast<T*>(this);
		}

		~Singleton(){
			ASSERT(msInstance);
			msInstance = 0;
		}
		static T* Instance(){
			ASSERT(msInstance);
			return msInstance;
		}
	};
	
}

#endif