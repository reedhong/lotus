/*
 * ²Ã¼õ×ÔOgre
 * created by reedhong 2012.07.18
 */
#ifndef __Lotus_Timer_H__
#define __Lotus_Timer_H__

#include "Platform/Platform.h"

//Bring in the specific platform's header file
#if LOTUS_PLATFORM == LOTUS_PLATFORM_WIN32
# include "Platform/Win32/TimerImp.h"
#elif LOTUS_PLATFORM == LOTUS_PLATFORM_APPLE_IOS
# include "Platform/iOS/TimerImp.h"
#elif LOTUS_PLATFORM == LOTUS_PLATFORM_ANDROID
# include "Platform/Android/TimerImp.h"
#endif

#endif
