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

	void Math::decomposition(Vector3& position, Vector3& scale, Quaternion& orientation) const
	{

	}


	/* 
	 * 实现算法来自Ogre中makeViewMatrix
	 */
	Matrix4 Matrix4::MakeMatrix4(const Vector3& position, const Quaternion& orientation)
	{
		Matrix4 m4;

		// View matrix is:
		//
		//  [ Lx  Uy  Dz  Tx  ]
		//  [ Lx  Uy  Dz  Ty  ]
		//  [ Lx  Uy  Dz  Tz  ]
		//  [ 0   0   0   1   ]
		//
		// Where T = -(Transposed(Rot) * Pos)

		// This is most efficiently done using 3x3 Matrices
		Matrix3 rot;
		orientation.toRotationMatrix(rot);

		// Make the translation relative to new axes
		Matrix3 rotT = rot.transpose();
		Vector3 trans = -rotT * position;

		// Make final matrix
		m4 = Matrix4::IDENTITY;
		m4 = rotT; // fills upper 3x3
		m4[0][3] = trans.x;
		m4[1][3] = trans.y;
		m4[2][3] = trans.z;
	}
}