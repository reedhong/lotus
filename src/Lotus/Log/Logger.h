/*
 * »’÷æ¿‡
 * created by reedhong 2012.07.17
 */

#ifndef __LOTUS_LOG_H__
#define __LOTUS_LOG_H__


#include "Platform/Platform.h"

namespace Lotus
{	
	enum LogLevel
	{
		eLogCritical=50,
		eLogError = 40,
		eLogWarning = 30,
		eLogInfo = 20,
		eLogDebug = 10,
		eLogNotSet = 0, 
	};
	
	class Logger
	{
	public:
		Logger(const String&  path, const String& name, bool console=false, LogLevel level=eLogError);
		~Logger();

		void log(LogLevel level, const char* fmt, ...);

		void setLevel(LogLevel level){
			mLogLevel = level;
		}
		void EnableConsole(){ mConsole = TRUE;}
		void DisableConsole(){ mConsole = FALSE;}
	private:
		LogLevel		mLogLevel;
		bool				mConsole;
		FILE*				mFile;
		String				mName;
	};
}

#endif