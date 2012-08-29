/********************************************************************
	created:	2012/08/29 
	filename: 	SkeletonSerializer.h
	author:		reedhong 
	
	purpose:	导入骨骼信息
*********************************************************************/

#ifndef __Lotus_SkeletonSerializer_H__
#define __Lotus_SkeletonSerializer_H__


#include "General/Serializer.h"
#include "General/Stream.h"
#include "Skeleton.h"

namespace Lotus {
	class SkeletonSerializer: public Serializer
	{
	public:
		SkeletonSerializer();
		SkeletonSerializer(StreamPtr stream);
		~SkeletonSerializer();
		void exportSkeleton(const Skeleton* pDest, StreamPtr stream);
		void importSkeleton(StreamPtr& stream, Skeleton* pDest);
	};
}

#endif