/********************************************************************
	created:	2012/09/16
	filename: 	Util.h
	author:		reedhong
	
	purpose:	一些功能函数
*********************************************************************/

#ifndef __Lotus2d_Util_H__
#define __Lotus2d_Util_H__

#include "Prerequisites.h"

namespace Lotus2d {
	class Util
	{
	public:
		/*
		* 获取路径中的文件名，剔除掉后缀名
		 */
		static char* getFileNameNoExt(char* szPath);
	};
}

#endif