/*
 * ��Դ�����ܿ�
 * ��洢��Դ·��������
 * created by reedhong 2012.08.06
 */

#ifndef __Lotus_ResourceManagers_H__
#define __Lotus_ResourceManagers_H__

#include "General/Prerequisites.h"

namespace Lotus {
	class ResourceManagers
	{
	public:
		ResourceManagers();
		~ResourceManagers();
	private:
		// name->path
		map<String, String> mResourceLocationMap;
	};
}

#endif