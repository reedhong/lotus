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
#include <string>
#include <vector>
#include <map>
#include <list>

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


// ��������
typedef vector<String> StringVector;
typedef SharedPtr<StringVector> StringVectorPtr;



// Ԥ������
class Archive;

class Matrix3;
class Quaternion;
class Vector3;

} // end Lotus

#endif