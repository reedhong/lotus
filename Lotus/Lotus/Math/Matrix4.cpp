/********************************************************************
	created:	2012/08/15
	filename: 	Matrix.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Matrix4.h"

namespace Lotus {
	const Matrix4 Matrix4::ZERO(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0 );

	const Matrix4 Matrix4::ZEROAFFINE(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 1 );

	const Matrix4 Matrix4::IDENTITY(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 );
}