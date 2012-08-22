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

	Matrix4 Matrix4::MakeMatrix4(const Vector3& postion, const Quaternion& orientation)
	{
		Matrix4 viewMatrix;

		Matrix3 rot = orientation.toRotationMatrix();

		Matrix3 rotT = rot.transpose();
		Vector3 trans = -rotT * postion;

		viewMatrix = Matrix4::IDENTITY;
		//viewMatrix = rotT; // fills upper 3x3

		// TODO:
		//viewMatrix[0][3] = trans.x;
		//viewMatrix[1][3] = trans.y;
		//viewMatrix[2][3] = trans.z;
	
		return viewMatrix;
	}
}