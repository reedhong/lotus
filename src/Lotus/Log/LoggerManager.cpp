#include <sstream>
#include <cstdarg>
using namespace std;

#include "LoggerManager.h"

namespace Lotus
{
	template<> LoggerManager* Singleton<LoggerManager>::msInstance = 0;

	LoggerManager::LoggerManager()
	{
		mDefaultLog = 0;
	}

	LoggerManager::~LoggerManager()
	{
		map<string, Logger*>::iterator iter = mLogs.begin();
		for(; iter != mLogs.end(); ++iter){
			LOTUS_DELETE iter->second;
		}
		mDefaultLog = 0;
	}

	Logger* LoggerManager::createLog(const string& name, const string& path,  bool defaultLog, bool console)
	{
		Logger* newLog = LOTUS_NEW Logger(path, name, console);
		if( !mDefaultLog || defaultLog )
		{
			mDefaultLog = newLog;
		}
		mLogs.insert( make_pair( name, newLog ) );
		return newLog;
	}

	Logger* LoggerManager::getLog(string name)
	{

		map<string, Logger*>::iterator iter = mLogs.find(name);
		if (iter != mLogs.end()){
			return iter->second;
		}else{
			ASSERT(0);
			return NULL;
		}
	}

	void LoggerManager::log(LogLevel level, const char* fmt,  ...)
	{
		ASSERT(mDefaultLog != NULL);
		static char sBuf[MaxLogLen];
		sBuf[MaxLogLen-1] = 0;
		va_list args;
		va_start(args, fmt);
		vsnprintf (sBuf, MaxLogLen-1, fmt, args);
		va_end(args);

		mDefaultLog->log(level,  sBuf);
	}

	/** Closes and removes a named log. */
	void LoggerManager::destroyLog(const string& name)
	{
		map<string, Logger*>::iterator iter = mLogs.find(name);
		if (iter != mLogs.end())
		{
			if (mDefaultLog == iter->second)
			{
				mDefaultLog = 0;
			}
			LOTUS_DELETE iter->second;
			mLogs.erase(iter);
		}

		// Set another default log if this one removed
		if (!mDefaultLog && !mLogs.empty())
		{
			mDefaultLog = mLogs.begin()->second;
		}
	}

}