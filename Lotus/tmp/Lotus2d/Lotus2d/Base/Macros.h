/********************************************************************
	created:	2012/09/11
	filename: 	Macros.h
	author:		reedhong
	
	purpose:	¹«¹²ºê
*********************************************************************/

#ifndef __Lotus_Macro_H__
#define __Lotus_Macro_H__
#include <assert.h>
#include "Platform/Platform.h"

namespace Lotus2d
{

#ifdef LOTUS2D_DEBUG_MODE
#define ASSERT(c) if (c) 0; else assert(c)
#else
#define ASSERT(c) 0
#endif

#define LOTUS_NEW	new
#define LOTUS_DELETE	delete



}

#endif