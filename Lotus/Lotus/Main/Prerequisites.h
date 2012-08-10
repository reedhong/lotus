/********************************************************************
	created:	2012/08/08 
	filename: 	Prerequisites.h
	author:		reedhong 
	
	purpose:	一些预先需要包含的公共头
*********************************************************************/

#ifndef __Lotus_Prerequisites_H__
#define __Lotus_Prerequisites_H__

#include "Platform/Platform.h"
#include "SharedPtr.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace Lotus {

#define String string
#ifndef TRUE
	#define  TRUE true
#endif
#ifndef FALSE
	#define FALSE false
#endif
#define snprintf _snprintf

#if LOTUS_DOUBLE_PRECISION == 1
	/** Software floating point type.
	@note Not valid as a pointer to GPU buffers / parameters
	*/
    typedef double Real;
#else
	/** Software floating point type.
	@note Not valid as a pointer to GPU buffers / parameters
	*/
    typedef float Real;
#endif

// 类型声明
typedef vector<String> StringVector;
typedef SharedPtr<StringVector> StringVectorPtr;



// 预先声明
class Archive;

} // end Lotus

#endif