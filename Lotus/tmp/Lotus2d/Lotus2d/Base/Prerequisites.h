/********************************************************************
	created:	2012/08/08 
	filename: 	Prerequisites.h
	author:		reedhong 
	
	purpose:	һЩԤ����Ҫ�����Ĺ���ͷ
*********************************************************************/

#ifndef __Lotus_Prerequisites_H__
#define __Lotus_Prerequisites_H__

#include "Platform/Platform.h"
#include "SharedPtr.h"
#include "Macros.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

namespace Lotus2d {

#define String string
#ifndef TRUE
	#define  TRUE true
#endif
#ifndef FALSE
	#define FALSE false
#endif
#define snprintf _snprintf


} // end Lotus2d

#endif