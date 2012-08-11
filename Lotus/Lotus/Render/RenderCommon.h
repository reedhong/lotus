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

#if ENABLE_GL_CHECK==1
#define GL_CHECK_ERROR \
	{ \
	int e = glGetError(); \
	if (e != 0) \
	{ \
	const char * errorString = ""; \
	switch(e) \
	{ \
	case GL_INVALID_ENUM:       errorString = "GL_INVALID_ENUM";        break; \
	case GL_INVALID_VALUE:      errorString = "GL_INVALID_VALUE";       break; \
	case GL_INVALID_OPERATION:  errorString = "GL_INVALID_OPERATION";   break; \
	case GL_OUT_OF_MEMORY:      errorString = "GL_OUT_OF_MEMORY";       break; \
	default:                                                            break; \
		} \
		LoggerManager::Instance()->log(eLogError, "OpenGL ES2 error 0x%04X %s in %s at line %i\n", e, errorString, __PRETTY_FUNCTION__, __LINE__);\
		} \
		}
#else
	#define GL_CHECK_ERROR {}
#endif
}

#endif