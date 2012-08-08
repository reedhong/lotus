/*
 * 日志管理类
 * created by reedhong 2012.07.17
 */
#ifndef __LOTUS_LOG_MANAGER_H__
#define __LOTUS_LOG_MANAGER_H__

#include <string>
#include <map>

using namespace std;
#include "Platform/Platform.h"
#include "Main/Singleton.h"
#include "Logger.h"

namespace Lotus
{
	class LoggerManager: public Singleton<LoggerManager>
	{
	public:
		static const int MaxLogLen  = 2048;
		LoggerManager();
		~LoggerManager();
		Logger* createLog(const string& name, const string& path,  bool defaultLog=FALSE, bool console=FALSE);
		Logger* getLog(string name);
		void log(LogLevel level, const char* fmt,  ...);
		/** Closes and removes a named log. */
		void destroyLog(const string& name);
		/** Closes and removes a log. */
		void destroyLog(Logger* log);

	private:
		map<string, Logger* >		mLogs;
		Logger*								mDefaultLog;
	};
}

#endif