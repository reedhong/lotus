/*
 * ��Դ�����ܿ�
 * ��洢��Դ·��������
 * created by reedhong 2012.08.06
 */

#ifndef __Lotus_ResourceManagers_H__
#define __Lotus_ResourceManagers_H__

#include "VFS/Archive.h"

namespace Lotus {
	class ResourceManagers
	{
	public:
		ResourceManagers();
		~ResourceManagers();
	private:
		map<String, Archive*> mResourceLocationIndex;
	};
}

#endif