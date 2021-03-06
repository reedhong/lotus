/*
 * 资源管理总控
 * 会存储资源路径的索引
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