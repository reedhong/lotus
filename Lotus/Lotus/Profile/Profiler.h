/*
 * ²Ã¼ô×ÔLotus
 * created by reedhong 2012.07.27
 */

#ifndef __Lotus_Profiler_H__
#define __Lotus_Profiler_H__

#if LOTUS_PROFILING == 1
#	define LotusProfile( a ) Lotus::Profile _LotusProfileInstance( (a) )
#	define LotusProfileBegin( a ) Lotus::Profiler::getSingleton().beginProfile( (a) )
#	define LotusProfileEnd( a ) Lotus::Profiler::getSingleton().endProfile( (a) )
#	define LotusProfileGroup( a, g ) Lotus::Profile _LotusProfileInstance( (a), (g) )
#	define LotusProfileBeginGroup( a, g ) Lotus::Profiler::getSingleton().beginProfile( (a), (g) )
#	define LotusProfileEndGroup( a, g ) Lotus::Profiler::getSingleton().endProfile( (a), (g) )
#else
#  define LotusProfile( a )
#  define LotusProfileBegin( a )
#  define LotusProfileEnd( a )
#	define LotusProfileGroup( a, g ) 
#	define LotusProfileBeginGroup( a, g ) 
#	define LotusProfileEndGroup( a, g ) 
#endif

namespace Lotus{

}


#endif