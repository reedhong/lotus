#include  <sstream>
using namespace std;

#include "Convert.h"
#include "String/StringUtil.h"
#include "Main/Macro.h"

namespace Lotus {
	String Convert::Int2String(int32 ival)
	{
		ostringstream oss;
		oss << ival;

		return oss.str();
	}

	int32 Convert::String2Int(const String& strval)
	{
		return atoi(strval.c_str());
	}

	float Convert::String2Float(const String& strval)
	{
		return (float)atof(strval.c_str());
	}

	String Convert::Float2String(float f)
	{
		ostringstream oss;
		oss << f;

		return oss.str();
	}

	bool Convert::String2Bool(const String& strval)
	{
		String str = strval;
		StringUtil::toLowerCase(str);
		if( str == string("true")){
			return TRUE;
		}else if(str == string("false")){
			return FALSE;
		}else if( str == string("0")){
			return FALSE;
		}else if( str == string("1")){
			return TRUE;
		}else{
			ASSERT(0); // ERROR
			return FALSE;
		}
		
	}
}