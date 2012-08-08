/*
 * 测试日志
 */
#include <iostream>
using namespace std;

#include "Log/LoggerManager.h"
using namespace Lotus;

#include "test.h"

void testLogger()
{
	LoggerManager* logManager = LOTUS_NEW LoggerManager();
	LoggerManager::Instance()->createLog("root", "./root.log", TRUE, TRUE);
	LoggerManager::Instance()->log(eLogError, "%s", "fuck");

	// 暂时不删除，否则Except就没法记录了
	//LOTUS_DELETE logManager;  
}
