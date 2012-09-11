/*
 * ����ģʽ
 * �̳е������࣬��һ���ط������������ط���ͨ��Instance��õ���, �ͷŹ����ɴ�������
 * ���һ���������Ҫ����msInstance=0;
 * ���TestSingleton.cpp
 * created by reedhong fishwarter@gmail.com 2012.07.16
 */

#ifndef __Lotus2d_Singleton_H__
#define __Lotus2d_Singleton_H__

#include "Macros.h"

namespace Lotus2d{
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