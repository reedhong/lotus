/*
 * 一些公共的宏
 * created by reedhong 2012.07.17
 */

#ifndef __Lotus_Macro_H__
#define __Lotus_Macro_H__
#include <assert.h>
#include "Platform/Platform.h"

namespace Lotus
{
#ifdef LOTUS_DEBUG_MODE
#define ASSERT(c) if (c) 0; else assert(c)
#else
#define ASSERT(c) 0
#endif

#define LOTUS_NEW	new
#define LOTUS_DELETE	delete



}

#endif