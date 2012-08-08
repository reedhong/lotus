/* 
 * 一些转换功能接口
 * created by reedhong 2012.07.22 
 */

#ifndef __Lotus_Convert_H__
#define __Lotus_Config_H__

#include "Main/Prerequisites.h"

namespace Lotus {
	class Convert
	{
	public:
		static String Int2String(int32 ival);
		static int32 String2Int(const String& strval);

		static String Float2String(float f);
		static float String2Float(const String& strval);

		// true, false, TRUE, FALSE, 0 , 1
		static bool String2Bool(const String& strval);
	};
}

#endif
