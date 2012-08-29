#include "Logger.h"
#include "General/Macro.h"
#include "General/Timer.h"

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <sstream>
using namespace std;

namespace Lotus
{
	Logger::Logger(const string& path, const String& name, bool console, LogLevel level)
	{
		mConsole = console;
		mLogLevel = eLogDebug;
		mName = name;
		fopen_s(&mFile, path.c_str(), "w+");
		ASSERT(mFile != NULL);
	}

	Logger::~Logger()
	{
		fclose(mFile);
	}

	void Logger::log(LogLevel level, const char* fmt, ...)
	{
		if (level < mLogLevel)
			return;

		ostringstream oss;
		oss << mName << " ";
		switch (level)
		{
		case eLogNotSet:
			return ;
		case eLogDebug : 
			oss << "DEBUG ";
			break;
		case eLogInfo :
			oss << "INFO ";
			break;
		case eLogWarning :
			oss << "WARNING ";
			break;
		case eLogError :
			oss << "ERROR ";
			break;
		case eLogCritical:
			oss << "CRITICAL ";
			break;
		default :
			return;
		}
		oss <<Timer::nowString()  << " " ;
		//! 写入日志文件.
		va_list args;
		va_start(args, fmt);
		oss << fmt << '\n';
		vfprintf(mFile, oss.str().c_str(), args);
		if(mConsole){
			printf(oss.str().c_str(), args);
		}
		va_end(args);

		return;
	}
}