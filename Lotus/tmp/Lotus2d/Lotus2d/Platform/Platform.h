/********************************************************************
	created:	2012/09/11
	filename: 	Platform.h
	author:		reedhong
	
	purpose:	平台相关
*********************************************************************/

#ifndef __LOTUS2D_PLATFORM_H__
#define __LOTUS2D_PLATFORM_H__

#include "Base/Config.h"

namespace LOTUS2D {
	/* Initial platform/compiler-related stuff to set.
	*/
#define LOTUS2D_PLATFORM_WIN32 1
#define LOTUS2D_PLATFORM_LINUX 2
#define LOTUS2D_PLATFORM_APPLE 3
//#define LOTUS2D_PLATFORM_SYMBIAN 4
#define LOTUS2D_PLATFORM_APPLE_IOS 5
#define LOTUS2D_PLATFORM_ANDROID 6
//#define LOTUS2D_PLATFORM_NACL 7

#define LOTUS2D_COMPILER_MSVC 1
#define LOTUS2D_COMPILER_GNUC 2
#define LOTUS2D_COMPILER_BORL 3
#define LOTUS2D_COMPILER_WINSCW 4
#define LOTUS2D_COMPILER_GCCE 5
#define LOTUS2D_COMPILER_CLANG 6

#define LOTUS2D_ENDIAN_LITTLE 1
#define LOTUS2D_ENDIAN_BIG 2

#define LOTUS2D_ARCHITECTURE_32 1
#define LOTUS2D_ARCHITECTURE_64 2

	/* Finds the compiler type and version.
	*/
#if defined( __GCCE__ )
#   define LOTUS2D_COMPILER LOTUS2D_COMPILER_GCCE
#   define LOTUS2D_COMP_VER _MSC_VER
	//#	include <staticlibinit_gcce.h> // This is a GCCE toolchain workaround needed when compiling with GCCE 
#elif defined( __WINSCW__ )
#   define LOTUS2D_COMPILER LOTUS2D_COMPILER_WINSCW
#   define LOTUS2D_COMP_VER _MSC_VER
#elif defined( _MSC_VER )
#   define LOTUS2D_COMPILER LOTUS2D_COMPILER_MSVC
#   define LOTUS2D_COMP_VER _MSC_VER
#elif defined( __clang__ )
#   define LOTUS2D_COMPILER LOTUS2D_COMPILER_CLANG
#   define LOTUS2D_COMP_VER (((__clang_major__)*100) + \
	(__clang_minor__*10) + \
	__clang_patchlevel__)
#elif defined( __GNUC__ )
#   define LOTUS2D_COMPILER LOTUS2D_COMPILER_GNUC
#   define LOTUS2D_COMP_VER (((__GNUC__)*100) + \
	(__GNUC_MINOR__*10) + \
	__GNUC_PATCHLEVEL__)
#elif defined( __BORLANDC__ )
#   define LOTUS2D_COMPILER LOTUS2D_COMPILER_BORL
#   define LOTUS2D_COMP_VER __BCPLUSPLUS__
#   define __FUNCTION__ __FUNC__ 
#else
#   pragma error "No known compiler. Abort! Abort!"

#endif

	/* See if we can use __forceinline or if we need to use __inline instead */
#if LOTUS2D_COMPILER == LOTUS2D_COMPILER_MSVC
#   if LOTUS2D_COMP_VER >= 1200
#       define FORCEINLINE __forceinline
#   endif
#elif defined(__MINGW32__)
#   if !defined(FORCEINLINE)
#       define FORCEINLINE __inline
#   endif
#else
#   define FORCEINLINE __inline
#endif

	/* Finds the current platform */

#if defined( __SYMBIAN32__ ) 
#   define LOTUS2D_PLATFORM LOTUS2D_PLATFORM_SYMBIAN
#elif defined( __WIN32__ ) || defined( _WIN32 )
#   define LOTUS2D_PLATFORM LOTUS2D_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
	// Device                                                     Simulator
	// Both requiring OS version 4.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 40000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 40000
#       define LOTUS2D_PLATFORM LOTUS2D_PLATFORM_APPLE_IOS
#   else
#       define LOTUS2D_PLATFORM LOTUS2D_PLATFORM_APPLE
#   endif
#elif defined(__ANDROID__)
#	define LOTUS2D_PLATFORM LOTUS2D_PLATFORM_ANDROID
#elif defined( __native_client__ ) 
#   define LOTUS2D_PLATFORM LOTUS2D_PLATFORM_NACL
#   ifndef LOTUS2D_STATIC_LIB
#       error LOTUS2D must be built as static for NaCl (LOTUS2D_STATIC=true in CMake)
#   endif
#   ifdef LOTUS2D_BUILD_RENDERSYSTEM_D3D9
#       error D3D9 is not supported on NaCl (LOTUS2D_BUILD_RENDERSYSTEM_D3D9 false in CMake)
#   endif
#   ifdef LOTUS2D_BUILD_RENDERSYSTEM_GL
#       error OpenGL is not supported on NaCl (LOTUS2D_BUILD_RENDERSYSTEM_GL=false in CMake)
#   endif
#   ifndef LOTUS2D_BUILD_RENDERSYSTEM_GLES2
#       error GLES2 render system is required for NaCl (LOTUS2D_BUILD_RENDERSYSTEM_GLES2=false in CMake)
#   endif
#else
#   define LOTUS2D_PLATFORM LOTUS2D_PLATFORM_LINUX
#endif

	/* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define LOTUS2D_ARCH_TYPE LOTUS2D_ARCHITECTURE_64
#else
#   define LOTUS2D_ARCH_TYPE LOTUS2D_ARCHITECTURE_32
#endif

	// For generating compiler warnings - should work on any compiler
	// As a side note, if you start your message with 'Warning: ', the MSVC
	// IDE actually does catch a warning :)
#define LOTUS2D_QUOTE_INPLACE(x) # x
#define LOTUS2D_QUOTE(x) LOTUS2D_QUOTE_INPLACE(x)
#define LOTUS2D_WARN( x )  message( __FILE__ "(" QUOTE( __LINE__ ) ") : " x "\n" )

	//----------------------------------------------------------------------------
	// Windows Settings
#if LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_WIN32

	// If we're not including this from a client build, specify that the stuff
	// should get exported. Otherwise, import it.
#	if defined( LOTUS2D_STATIC_LIB )
	// Linux compilers don't have symbol import/export directives.
#   	define _LOTUS2DExport
#   	define _LOTUS2DPrivate
#   else
#   	if defined( LOTUS2D_NONCLIENT_BUILD )
#       	define _LOTUS2DExport __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define _LOTUS2DExport
#           else
#       	    define _LOTUS2DExport __declspec( dllimport )
#           endif
#   	endif
#   	define _LOTUS2DPrivate
#	endif
	// Win32 compilers use _DEBUG for specifying debug builds.
	// for MinGW, we set DEBUG
#   if defined(_DEBUG) || defined(DEBUG)
#       define LOTUS2D_DEBUG_MODE 1
#   else
#       define LOTUS2D_DEBUG_MODE 0
#   endif

	// Disable unicode support on MingW for GCC 3, poorly supported in stdlibc++
	// STLPORT fixes this though so allow if found
	// MinGW C++ Toolkit supports unicode and sets the define __MINGW32_TOOLBOX_UNICODE__ in _mingw.h
	// GCC 4 is also fine
#if defined(__MINGW32__)
# if LOTUS2D_COMP_VER < 400
#  if !defined(_STLPORT_VERSION)
#   include<_mingw.h>
#   if defined(__MINGW32_TOOLBOX_UNICODE__) || LOTUS2D_COMP_VER > 345
#    define LOTUS2D_UNICODE_SUPPORT 1
#   else
#    define LOTUS2D_UNICODE_SUPPORT 0
#   endif
#  else
#   define LOTUS2D_UNICODE_SUPPORT 1
#  endif
# else
#  define LOTUS2D_UNICODE_SUPPORT 1
# endif
#else
#  define LOTUS2D_UNICODE_SUPPORT 1
#endif

#endif // LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_WIN32

	//----------------------------------------------------------------------------
	// Symbian Settings
#if LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_SYMBIAN
#   define _LOTUS2DExport 
#	define LOTUS2D_UNICODE_SUPPORT 1
#   define LOTUS2D_DEBUG_MODE 0
#   define _LOTUS2DPrivate
#	  define CLOCKS_PER_SEC  1000
	//  pragma def were found here: http://www.inf.pucrs.br/~eduardob/disciplinas/SistEmbarcados/Mobile/Nokia/Tools/Carbide_vs/WINSCW/Help/PDF/C_Compilers_Reference_3.2.pdf
#	  pragma warn_unusedarg off
#	  pragma warn_emptydecl off
#	  pragma warn_possunwant off
	// A quick define to overcome different names for the same function
#   define stricmp strcasecmp
#   ifdef DEBUG
#       define LOTUS2D_DEBUG_MODE 1
#   else
#       define LOTUS2D_DEBUG_MODE 0
#   endif
#endif
	//----------------------------------------------------------------------------
	// Android Settings
	/*
	#if LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_ANDROID
	#   define _LOTUS2DExport 
	#	define LOTUS2D_UNICODE_SUPPORT 1
	#   define LOTUS2D_DEBUG_MODE 0
	#   define _LOTUS2DPrivate
	#	  define CLOCKS_PER_SEC  1000
	//  pragma def were found here: http://www.inf.pucrs.br/~eduardob/disciplinas/SistEmbarcados/Mobile/Nokia/Tools/Carbide_vs/WINSCW/Help/PDF/C_Compilers_Reference_3.2.pdf
	#	  pragma warn_unusedarg off
	#	  pragma warn_emptydecl off
	#	  pragma warn_possunwant off
	// A quick define to overcome different names for the same function
	#   define stricmp strcasecmp
	#   ifdef DEBUG
	#       define LOTUS2D_DEBUG_MODE 1
	#   else
	#       define LOTUS2D_DEBUG_MODE 0
	#   endif
	#endif
	*/
	//----------------------------------------------------------------------------
	// Linux/Apple/iOs/Android/Symbian/NaCl Settings
#if LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_LINUX || LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_APPLE || LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_APPLE_IOS || \
	LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_ANDROID || LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_NACL

	// Enable GCC symbol visibility
#   if defined( LOTUS2D_GCC_VISIBILITY )
#       define _LOTUS2DExport  __attribute__ ((visibility("default")))
#       define _LOTUS2DPrivate __attribute__ ((visibility("hidden")))
#   else
#       define _LOTUS2DExport
#       define _LOTUS2DPrivate
#   endif

	// A quick define to overcome different names for the same function
#   define stricmp strcasecmp

#   ifdef DEBUG
#       define LOTUS2D_DEBUG_MODE 1
#   else
#       define LOTUS2D_DEBUG_MODE 0
#   endif

#if LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_APPLE
#define LOTUS2D_PLATFORM_LIB "LOTUS2DPlatform.bundle"
#elif LOTUS2D_PLATFORM == LOTUS2D_PLATFORM_APPLE_IOS
#define LOTUS2D_PLATFORM_LIB "LOTUS2DPlatform.a"
#else //LOTUS2D_PLATFORM_LINUX
#define LOTUS2D_PLATFORM_LIB "libLOTUS2DPlatform.so"
#endif

	// Always enable unicode support for the moment
	// Perhaps disable in old versions of gcc if necessary
#define LOTUS2D_UNICODE_SUPPORT 1

#endif

	//----------------------------------------------------------------------------
	// Endian Settings
	// check for BIG_ENDIAN config flag, set LOTUS2D_ENDIAN correctly
#ifdef LOTUS2D_CONFIG_BIG_ENDIAN
#    define LOTUS2D_ENDIAN LOTUS2D_ENDIAN_BIG
#else
#    define LOTUS2D_ENDIAN LOTUS2D_ENDIAN_LITTLE
#endif

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
}



#endif