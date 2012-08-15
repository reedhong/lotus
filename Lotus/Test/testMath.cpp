/********************************************************************
	created:	2012/08/15
	filename: 	testMath.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/
#include <iostream>
using namespace std;

#include "test.h"
#include "Math/Math.h"
#include "Math/Matrix3.h"
#include "Math/Matrix4.h"

using namespace Lotus;

void testMath()
{
	Matrix3  matrix3(
		1.1,2.0, 3.0, 
		5.0, 6.0, 7.0, 
		9.0, 10.0, 11.0);
	float f = matrix3.m.m11;
	cout << matrix3._m[0] << endl;

	Matrix3  m3 = matrix3;
	m3.transposeSelf();
	cout << m3.m.m11 << endl;;

}