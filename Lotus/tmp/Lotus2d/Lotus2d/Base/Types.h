/********************************************************************
	created:	2012/09/14 
	filename: 	Types.h
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "Platform/Platform.h"

#ifndef __Lotus2d_Types_H__
#define __Lotus2d_Types_H__

#ifndef BOOL
	#define BOOL signed char
#endif 

#define TRUE 1
#define FALSE 0

// Integer formats of fixed bit width
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef char int8;
// define uint64 type
#if LOTUS2D_COMPILER == LOTUS2D_COMPILER_MSVC
	typedef unsigned __int64 uint64;
	typedef __int64 int64;
#else
	typedef unsigned long long uint64;
	typedef long long int64;
#endif





#endif
