/********************************************************************
	created:	2012/08/08 
	filename: 	Dir.h
	author:		reedhong 
	
	purpose:	虚拟文件目录项操作
*********************************************************************/

#ifndef __Lotus_Dir_H__
#define __Lotus_Dir_H__

#include "Main/Prerequisites.h"

namespace Lotus {
	class Dir 
	{
	protected:
		String		mPath;
	public :
		Dir() {}
		~Dir() {}
		
		bool exists(const String& path);
	};

	typedef SharedPtr<Dir> DirPtr;
}

#endif