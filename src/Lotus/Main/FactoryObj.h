/*
 * �������� 
 * ���ã� 1. �������ʵ������һ���ࣻ 2. ����ʵ�����ӳ�
 * created by reedhong fishwarter@gmail.com 2012.07.17
 */
#ifndef __Lotus_FactoryObj_H__
#define __Lotus_FactoryObj_H__
namespace Lotus{
	template<typename T> class FactoryObj
	{
	public:
		virtual ~FactoryObj() {}
		virtual const string& getType() const = 0;
		virtual T* createInstance(const string& name) = 0;
		virtual void destroyInstance(T*) = 0;
	};
}

#endif