/*
 * 单例模式
 * 继承单例的类，在一处地方创建，其他地方均通过Instance获得调用, 释放工作由创建负责
 * 并且基础的类需要定义msInstance=0;
 * 详见TestSingleton.cpp
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
			ASSERT(!msInstance);  // 这个保持该对象只被创建一次
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