#ifndef __LOTUS_PLATFORM_H__
#define __LOTUS_PLATFORM_H__

#include "Main/Config.h"
#include <string>
using namespace std;

namespace Lotus {
	/* Initial platform/compiler-related stuff to set.
	*/
#define LOTUS_PLATFORM_WIN32 1
#define LOTUS_PLATFORM_LINUX 2
#define LOTUS_PLATFORM_APPLE 3
#define LOTUS_PLATFORM_SYMBIAN 4
#define LOTUS_PLATFORM_APPLE_IOS 5
#define LOTUS_PLATFORM_ANDROID 6
#define LOTUS_PLATFORM_NACL 7

#define LOTUS_COMPILER_MSVC 1
#define LOTUS_COMPILER_GNUC 2
#define LOTUS_COMPILER_BORL 3
#define LOTUS_COMPILER_WINSCW 4
#define LOTUS_COMPILER_GCCE 5
#define LOTUS_COMPILER_CLANG 6

#define LOTUS_ENDIAN_LITTLE 1
#define LOTUS_ENDIAN_BIG 2

#define LOTUS_ARCHITECTURE_32 1
#define LOTUS_ARCHITECTURE_64 2

	/* Finds the compiler type and version.
	*/
#if defined( __GCCE__ )
#   define LOTUS_COMPILER LOTUS_COMPILER_GCCE
#   define LOTUS_COMP_VER _MSC_VER
	//#	include <staticlibinit_gcce.h> // This is a GCCE toolchain workaround needed when compiling with GCCE 
#elif defined( __WINSCW__ )
#   define LOTUS_COMPILER LOTUS_COMPILER_WINSCW
#   define LOTUS_COMP_VER _MSC_VER
#elif defined( _MSC_VER )
#   define LOTUS_COMPILER LOTUS_COMPILER_MSVC
#   define LOTUS_COMP_VER _MSC_VER
#elif defined( __clang__ )
#   define LOTUS_COMPILER LOTUS_COMPILER_CLANG
#   define LOTUS_COMP_VER (((__clang_major__)*100) + \
	(__clang_minor__*10) + \
	__clang_patchlevel__)
#elif defined( __GNUC__ )
#   define LOTUS_COMPILER LOTUS_COMPILER_GNUC
#   define LOTUS_COMP_VER (((__GNUC__)*100) + \
	(__GNUC_MINOR__*10) + \
	__GNUC_PATCHLEVEL__)
#elif defined( __BORLANDC__ )
#   define LOTUS_COMPILER LOTUS_COMPILER_BORL
#   define LOTUS_COMP_VER __BCPLUSPLUS__
#   define __FUNCTION__ __FUNC__ 
#else
#   pragma error "No known compiler. Abort! Abort!"

#endif

	/* See if we can use __forceinline or if we need to use __inline instead */
#if LOTUS_COMPILER == LOTUS_COMPILER_MSVC
#   if LOTUS_COMP_VER >= 1200
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
#   define LOTUS_PLATFORM LOTUS_PLATFORM_SYMBIAN
#elif defined( __WIN32__ ) || defined( _WIN32 )
#   define LOTUS_PLATFORM LOTUS_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
	// Device                                                     Simulator
	// Both requiring OS version 4.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 40000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 40000
#       define LOTUS_PLATFORM LOTUS_PLATFORM_APPLE_IOS
#   else
#       define LOTUS_PLATFORM LOTUS_PLATFORM_APPLE
#   endif
#elif defined(__ANDROID__)
#	define LOTUS_PLATFORM LOTUS_PLATFORM_ANDROID
#elif defined( __native_client__ ) 
#   define LOTUS_PLATFORM LOTUS_PLATFORM_NACL
#   ifndef LOTUS_STATIC_LIB
#       error LOTUS must be built as static for NaCl (LOTUS_STATIC=true in CMake)
#   endif
#   ifdef LOTUS_BUILD_RENDERSYSTEM_D3D9
#       error D3D9 is not supported on NaCl (LOTUS_BUILD_RENDERSYSTEM_D3D9 false in CMake)
#   endif
#   ifdef LOTUS_BUILD_RENDERSYSTEM_GL
#       error OpenGL is not supported on NaCl (LOTUS_BUILD_RENDERSYSTEM_GL=false in CMake)
#   endif
#   ifndef LOTUS_BUILD_RENDERSYSTEM_GLES2
#       error GLES2 render system is required for NaCl (LOTUS_BUILD_RENDERSYSTEM_GLES2=false in CMake)
#   endif
#else
#   define LOTUS_PLATFORM LOTUS_PLATFORM_LINUX
#endif

	/* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define LOTUS_ARCH_TYPE LOTUS_ARCHITECTURE_64
#else
#   define LOTUS_ARCH_TYPE LOTUS_ARCHITECTURE_32
#endif

	// For generating compiler warnings - should work on any compiler
	// As a side note, if you start your message with 'Warning: ', the MSVC
	// IDE actually does catch a warning :)
#define LOTUS_QUOTE_INPLACE(x) # x
#define LOTUS_QUOTE(x) LOTUS_QUOTE_INPLACE(x)
#define LOTUS_WARN( x )  message( __FILE__ "(" QUOTE( __LINE__ ) ") : " x "\n" )

	//----------------------------------------------------------------------------
	// Windows Settings
#if LOTUS_PLATFORM == LOTUS_PLATFORM_WIN32

	// If we're not including this from a client build, specify that the stuff
	// should get exported. Otherwise, import it.
#	if defined( LOTUS_STATIC_LIB )
	// Linux compilers don't have symbol import/export directives.
#   	define _LOTUSExport
#   	define _LOTUSPrivate
#   else
#   	if defined( LOTUS_NONCLIENT_BUILD )
#       	define _LOTUSExport __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define _LOTUSExport
#           else
#       	    define _LOTUSExport __declspec( dllimport )
#           endif
#   	endif
#   	define _LOTUSPrivate
#	endif
	// Win32 compilers use _DEBUG for specifying debug builds.
	// for MinGW, we set DEBUG
#   if defined(_DEBUG) || defined(DEBUG)
#       define LOTUS_DEBUG_MODE 1
#   else
#       define LOTUS_DEBUG_MODE 0
#   endif

	// Disable unicode support on MingW for GCC 3, poorly supported in stdlibc++
	// STLPORT fixes this though so allow if found
	// MinGW C++ Toolkit supports unicode and sets the define __MINGW32_TOOLBOX_UNICODE__ in _mingw.h
	// GCC 4 is also fine
#if defined(__MINGW32__)
# if LOTUS_COMP_VER < 400
#  if !defined(_STLPORT_VERSION)
#   include<_mingw.h>
#   if defined(__MINGW32_TOOLBOX_UNICODE__) || LOTUS_COMP_VER > 345
#    define LOTUS_UNICODE_SUPPORT 1
#   else
#    define LOTUS_UNICODE_SUPPORT 0
#   endif
#  else
#   define LOTUS_UNICODE_SUPPORT 1
#  endif
# else
#  define LOTUS_UNICODE_SUPPORT 1
# endif
#else
#  define LOTUS_UNICODE_SUPPORT 1
#endif

#endif // LOTUS_PLATFORM == LOTUS_PLATFORM_WIN32

	//----------------------------------------------------------------------------
	// Symbian Settings
#if LOTUS_PLATFORM == LOTUS_PLATFORM_SYMBIAN
#   define _LOTUSExport 
#	define LOTUS_UNICODE_SUPPORT 1
#   define LOTUS_DEBUG_MODE 0
#   define _LOTUSPrivate
#	  define CLOCKS_PER_SEC  1000
	//  pragma def were found here: http://www.inf.pucrs.br/~eduardob/disciplinas/SistEmbarcados/Mobile/Nokia/Tools/Carbide_vs/WINSCW/Help/PDF/C_Compilers_Reference_3.2.pdf
#	  pragma warn_unusedarg off
#	  pragma warn_emptydecl off
#	  pragma warn_possunwant off
	// A quick define to overcome different names for the same function
#   define stricmp strcasecmp
#   ifdef DEBUG
#       define LOTUS_DEBUG_MODE 1
#   else
#       define LOTUS_DEBUG_MODE 0
#   endif
#endif
	//----------------------------------------------------------------------------
	// Android Settings
	/*
	#if LOTUS_PLATFORM == LOTUS_PLATFORM_ANDROID
	#   define _LOTUSExport 
	#	define LOTUS_UNICODE_SUPPORT 1
	#   define LOTUS_DEBUG_MODE 0
	#   define _LOTUSPrivate
	#	  define CLOCKS_PER_SEC  1000
	//  pragma def were found here: http://www.inf.pucrs.br/~eduardob/disciplinas/SistEmbarcados/Mobile/Nokia/Tools/Carbide_vs/WINSCW/Help/PDF/C_Compilers_Reference_3.2.pdf
	#	  pragma warn_unusedarg off
	#	  pragma warn_emptydecl off
	#	  pragma warn_possunwant off
	// A quick define to overcome different names for the same function
	#   define stricmp strcasecmp
	#   ifdef DEBUG
	#       define LOTUS_DEBUG_MODE 1
	#   else
	#       define LOTUS_DEBUG_MODE 0
	#   endif
	#endif
	*/
	//----------------------------------------------------------------------------
	// Linux/Apple/iOs/Android/Symbian/NaCl Settings
#if LOTUS_PLATFORM == LOTUS_PLATFORM_LINUX || LOTUS_PLATFORM == LOTUS_PLATFORM_APPLE || LOTUS_PLATFORM == LOTUS_PLATFORM_APPLE_IOS || \
	LOTUS_PLATFORM == LOTUS_PLATFORM_ANDROID || LOTUS_PLATFORM == LOTUS_PLATFORM_NACL

	// Enable GCC symbol visibility
#   if defined( LOTUS_GCC_VISIBILITY )
#       define _LOTUSExport  __attribute__ ((visibility("default")))
#       define _LOTUSPrivate __attribute__ ((visibility("hidden")))
#   else
#       define _LOTUSExport
#       define _LOTUSPrivate
#   endif

	// A quick define to overcome different names for the same function
#   define stricmp strcasecmp

#   ifdef DEBUG
#       define LOTUS_DEBUG_MODE 1
#   else
#       define LOTUS_DEBUG_MODE 0
#   endif

#if LOTUS_PLATFORM == LOTUS_PLATFORM_APPLE
#define LOTUS_PLATFORM_LIB "LOTUSPlatform.bundle"
#elif LOTUS_PLATFORM == LOTUS_PLATFORM_APPLE_IOS
#define LOTUS_PLATFORM_LIB "LOTUSPlatform.a"
#else //LOTUS_PLATFORM_LINUX
#define LOTUS_PLATFORM_LIB "libLOTUSPlatform.so"
#endif

	// Always enable unicode support for the moment
	// Perhaps disable in old versions of gcc if necessary
#define LOTUS_UNICODE_SUPPORT 1

#endif

	//----------------------------------------------------------------------------
	// Endian Settings
	// check for BIG_ENDIAN config flag, set LOTUS_ENDIAN correctly
#ifdef LOTUS_CONFIG_BIG_ENDIAN
#    define LOTUS_ENDIAN LOTUS_ENDIAN_BIG
#else
#    define LOTUS_ENDIAN LOTUS_ENDIAN_LITTLE
#endif

	// Integer formats of fixed bit width
	typedef unsigned int uint32;
	typedef unsigned short uint16;
	typedef unsigned char uint8;
	typedef int int32;
	typedef short int16;
	typedef char int8;
	// define uint64 type
#if LOTUS_COMPILER == LOTUS_COMPILER_MSVC
	typedef unsigned __int64 uint64;
	typedef __int64 int64;
#else
	typedef unsigned long long uint64;
	typedef long long int64;
#endif

	#define String string
	#define  TRUE true
	#define FALSE false
	#define snprintf _snprintf
}



#endif