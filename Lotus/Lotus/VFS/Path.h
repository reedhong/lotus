/********************************************************************
	created:	2012/08/11
	filename: 	Path.h
	author:		reedhong
	
	purpose:	Â·¾¶²Ù×÷
*********************************************************************/

#ifndef __Lotus_Path_H__
#define __Lotus_Path_H__

#include "Main/Prerequisites.h"

namespace Lotus {
	class Path
	{
	public:
		static String join(const String& path1, const String& path2);
	};
}

#endif