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
		// Factor M = QR = QDU where Q is orthogonal, D is diagonal,
		// and U is upper triangular with ones on its diagonal.  Algorithm uses
		// Gram-Schmidt orthogonalization (the QR algorithm).
		//
		// If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
		//
		//   q0 = m0/|m0|
		//   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
		//   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
		//
		// where |V| indicates length of vector V and A*B indicates dot
		// product of vectors A and B.  The matrix R has entries
		//
		//   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
		//   r10 = 0      r11 = q1*m1  r12 = q1*m2
		//   r20 = 0      r21 = 0      r22 = q2*m2
		//
		// so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
		// u02 = r02/r00, and u12 = r12/r11.

		// Q = rotation	// Ðý×ª
		// D = scaling	// Ëõ·Å
		// U = shear		// ÇÐ±ä

		// D stores the three diagonal entries r00, r11, r22
		// U stores the entries U[0] = u01, U[1] = u02, U[2] = u12

		// build orthogonal matrix Q
		float fInvLength = m[0][0]*m[0][0] + m[1][0]*m[1][0] + m[2][0]*m[2][0];
		if (!Math::floatEqual(fInvLength,0)) fInvLength =Math::inv_sqrt(fInvLength);

		kQ[0][0] = m[0][0]*fInvLength;
		kQ[1][0] = m[1][0]*fInvLength;
		kQ[2][0] = m[2][0]*fInvLength;

		float fDot = kQ[0][0]*m[0][1] + kQ[1][0]*m[1][1] +
			kQ[2][0]*m[2][1];
		kQ[0][1] = m[0][1]-fDot*kQ[0][0];
		kQ[1][1] = m[1][1]-fDot*kQ[1][0];
		kQ[2][1] = m[2][1]-fDot*kQ[2][0];
		fInvLength = kQ[0][1]*kQ[0][1] + kQ[1][1]*kQ[1][1] + kQ[2][1]*kQ[2][1];
		if (!Math::floatEqual(fInvLength,0)) fInvLength =  Math::inv_sqrt(fInvLength);

		kQ[0][1] *= fInvLength;
		kQ[1][1] *= fInvLength;
		kQ[2][1] *= fInvLength;

		fDot = kQ[0][0]*m[0][2] + kQ[1][0]*m[1][2] +
			kQ[2][0]*m[2][2];
		kQ[0][2] = m[0][2]-fDot*kQ[0][0];
		kQ[1][2] = m[1][2]-fDot*kQ[1][0];
		kQ[2][2] = m[2][2]-fDot*kQ[2][0];
		fDot = kQ[0][1]*m[0][2] + kQ[1][1]*m[1][2] +
			kQ[2][1]*m[2][2];
		kQ[0][2] -= fDot*kQ[0][1];
		kQ[1][2] -= fDot*kQ[1][1];
		kQ[2][2] -= fDot*kQ[2][1];
		fInvLength = kQ[0][2]*kQ[0][2] + kQ[1][2]*kQ[1][2] + kQ[2][2]*kQ[2][2];		
		if (!Math::floatEqual(fInvLength,0)) fInvLength =  Math::inv_sqrt(fInvLength);

		kQ[0][2] *= fInvLength;
		kQ[1][2] *= fInvLength;
		kQ[2][2] *= fInvLength;

		// guarantee that orthogonal matrix has determinant 1 (no reflections)
		float fDet = kQ[0][0]*kQ[1][1]*kQ[2][2] + kQ[0][1]*kQ[1][2]*kQ[2][0] +
			kQ[0][2]*kQ[1][0]*kQ[2][1] - kQ[0][2]*kQ[1][1]*kQ[2][0] -
			kQ[0][1]*kQ[1][0]*kQ[2][2] - kQ[0][0]*kQ[1][2]*kQ[2][1];

		if ( fDet < 0.0 )
		{
			for (size_t iRow = 0; iRow < 3; iRow++)
				for (size_t iCol = 0; iCol < 3; iCol++)
					kQ[iRow][iCol] = -kQ[iRow][iCol];
		}

		// build "right" matrix R
		Matrix3 kR;
		kR[0][0] = kQ[0][0]*m[0][0] + kQ[1][0]*m[1][0] +
			kQ[2][0]*m[2][0];
		kR[0][1] = kQ[0][0]*m[0][1] + kQ[1][0]*m[1][1] +
			kQ[2][0]*m[2][1];
		kR[1][1] = kQ[0][1]*m[0][1] + kQ[1][1]*m[1][1] +
			kQ[2][1]*m[2][1];
		kR[0][2] = kQ[0][0]*m[0][2] + kQ[1][0]*m[1][2] +
			kQ[2][0]*m[2][2];
		kR[1][2] = kQ[0][1]*m[0][2] + kQ[1][1]*m[1][2] +
			kQ[2][1]*m[2][2];
		kR[2][2] = kQ[0][2]*m[0][2] + kQ[1][2]*m[1][2] +
			kQ[2][2]*m[2][2];

		// the scaling component
		kD[0] = kR[0][0];
		kD[1] = kR[1][1];
		kD[2] = kR[2][2];

		// the shear component
		float fInvD0 = 1.0f/kD[0];
		kU[0] = kR[0][1]*fInvD0;
		kU[1] = kR[0][2]*fInvD0;
		kU[2] = kR[1][2]/kD[1];
	}
}