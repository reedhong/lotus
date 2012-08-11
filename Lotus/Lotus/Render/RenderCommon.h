/********************************************************************
	created:	2012/08/11
	filename: 	RenderCommon.h
	author:		reedhong
	
	purpose:	渲染用到的一些公共东西
*********************************************************************/

#ifndef __Lotus_RenderCommon_H__
#define __Lotus_RenderCommon_H__

#include "Main/Config.h"
#include "Log/LoggerManager.h"

namespace Lotus {

	/** Defines the frame buffer types. */
	enum FrameBufferType {
		FBT_COLOUR  = 0x1,
		FBT_DEPTH   = 0x2,
		FBT_STENCIL = 0x4
	};
}

#endif