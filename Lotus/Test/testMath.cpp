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

void testMatrix3Multi()
{
	Matrix3 m1(
		1, -5, 3,
		0, -2, 6,
		7, 2, -4
		);

	Matrix3 m2(
		-8, 6, 1,
		7,  0, -3,
		2, 4, 5
		);

	Matrix3 m = m1*m2;

	cout << m.m[0] << endl;

	Vector3 v1(3,4,5);

	Vector3 v2 = m1*v1;

	cout << v2.x << endl;
}

void testMatrix3Inverse()
{
	Matrix3 m1(
		-4, -3, 3,
		0, 2, -2,
		1, 4, -1
		);


	Matrix3 mInv = m1.inverse();

	cout << mInv.m[0] << endl;
}

void testMatrix3Det()
{
	Matrix3 m(
		3, -2, 0,
		1, 4, -3,
		-1, 0, 2
		);
	float f = m.determinant();
	cout << m << endl;
	cout << f << endl;
}

void testMatrix4Multi()
{
	Matrix4 m(
		0, 4, 8, 12,
		1, 5, 9,13,
		2, 6, 10,14,
		3, 7, 11,15
		);

	Matrix4 mm = m*m;
	Matrix4 tm = m.transpose();

	Matrix4 m2(
		1, 2, 4, 5,
		2, 3, 4,1,
		33, 4, 3,1,
		323, 22, 1,2
		);

	Matrix4 im = m2.inverse();
	cout << mm << endl;
	cout << im << endl;
	float det = m2.determinant();
	cout << m2.transpose() << endl;
}

void testMath()
{
	Matrix3  matrix3(
		1.1,2.0, 3.0, 
		5.0, 6.0, 7.0, 
		9.0, 10.0, 11.0);
	float f = matrix3.ms.m11;
	cout << matrix3.m[0] << endl;

	Matrix3  m3 = matrix3;
	m3.transposeSelf();
	cout << m3.ms.m11 << endl;
	
	testMatrix3Multi();
	testMatrix3Inverse();
	testMatrix3Det();
	testMatrix4Multi();

}