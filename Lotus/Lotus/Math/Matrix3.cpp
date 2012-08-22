/********************************************************************
	created:	2012/08/15
	filename: 	Matrix3.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Matrix3.h"

namespace Lotus {
	const Matrix3 Matrix3::ZERO(
		0, 0, 0,
		0, 0, 0, 
		0, 0, 0);

	const Matrix3 Matrix3::IDENTITY(
		1, 0, 0, 
		0, 1, 0, 
		0, 0, 1);

	void Matrix3::QDUDecomposition (Matrix3& kQ,
		Vector3& kD, Vector3& kU) const
	{
		//http://zh.wikipedia.org/wiki/Gram-Schmidt%E6%AD%A3%E4%BA%A4%E5%8C%96
	}
}