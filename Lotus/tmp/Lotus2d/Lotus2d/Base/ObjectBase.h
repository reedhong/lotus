/*
* ==============================================================================
*  Name        : ObjectBase.h
*  
*/

#ifndef __Lotus2d_ObjectBase_H__
#define __Lotus2d_ObjectBase_H__

/*
����C++��ʹ�� new�ı���Ӹû��������������Ա�֤�ڴ����Ĺ������߱��麯�����C++����
*/
class ObjectBase
	{
	public:
	   		
		inline void* operator new( size_t aSize );
	   		
		inline void operator delete( void* aPtr );

		inline void* operator new [] (size_t aSize );

		inline void operator delete [] ( void* aPtr );
		
		virtual ~ObjectBase()				{}
	protected:
	   
		ObjectBase()						{}

		
	
	private:
	};
// implementation
#include <ObjectBase.inl>


#endif