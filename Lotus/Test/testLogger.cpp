/*
 * ������־
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

	// ��ʱ��ɾ��������Except��û����¼��
	//LOTUS_DELETE logManager;  
}
