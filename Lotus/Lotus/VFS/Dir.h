/********************************************************************
	created:	2012/08/08 
	filename: 	Dir.h
	author:		reedhong 
	
	purpose:	虚拟文件目录项操作
*********************************************************************/

#ifndef __Lotus_Dir_H__
#define __Lotus_Dir_H__

#include "General/Prerequisites.h"

namespace Lotus {
	class Dir 
	{
	protected:
		String		mPath;
	public :
		Dir(String path):mPath(path) {}
		~Dir() {}
	};

	typedef SharedPtr<Dir> DirPtr;
}

#endif