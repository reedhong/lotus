/*
* ==============================================================================
*  Name        : ObjectBase.h
*  
*/

#ifndef __Lotus2d_ObjectBase_H__
#define __Lotus2d_ObjectBase_H__

/*
所有C++类使用 new的必须从该基础类型派生，以保证内存分配的管理；并具备虚函数表的C++特性
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