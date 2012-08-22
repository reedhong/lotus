/********************************************************************
	created:	2012/08/10 
	filename: 	Matrix3.h
	author:		reedhong 
	
	purpose:	matrix operator, just for opengl 手右坐标系，按行存储
*********************************************************************/

#ifndef __Lotus_Matrix3_H__
#define __Lotus_Matrix3_H__

#include "Main/Prerequisites.h"
#include "Vector3.h"
#include "Math.h"

namespace Lotus {
	/*
	 *  OpenGL是按列存储的，小心了
	 */
	class Matrix3
	{
	public:
		static const Matrix3 ZERO;
		static const Matrix3 IDENTITY;
		static const int SIZE = 9;
	public:
		union{
			float					_m[SIZE];
			float					m[3][3];
		};
	public:

		inline Matrix3(){}
		inline Matrix3(
			float m00, float m01, float m02,
			float m10, float m11,float  m12,
			float m20, float m21, float m22)
		{
			set(
				 m00,  m01,  m02,
				 m10,  m11,  m12,
				 m20,  m21,  m22);
			
		}

		void set(
			float m00, float m01, float m02,
			float m10, float m11,float  m12,
			float m20, float m21, float m22)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
		}
		~Matrix3(){}

		inline Matrix3 (const Matrix3& rkMatrix)
		{
			memcpy(_m,rkMatrix._m,SIZE*sizeof(float));
		}

		// assignment and comparison
		inline Matrix3& operator= (const Matrix3& rkMatrix)
		{
			memcpy(_m,rkMatrix._m,SIZE*sizeof(float));
			return *this;
		}

		/** Tests 2 matrices for equality.
         */
        bool operator== (const Matrix3& rkMatrix) const
		{
			return  (memcmp((const void *)this->_m, rkMatrix._m, sizeof(float)*SIZE) ==0);
		}

        /** Tests 2 matrices for inequality.
         */
        inline bool operator!= (const Matrix3& rkMatrix) const
		{
			return !operator==(rkMatrix);
		}

		 // arithmetic operations
        /** Matrix addition.
         */
        Matrix3 operator+ (const Matrix3& rkMatrix) const
		{
			Matrix3 kSum;
			for(int i = 0; i <SIZE; i++){
				kSum._m[i] = this->_m[i] + rkMatrix._m[i];
			}
			return kSum;
		}

        /** Matrix subtraction.
         */
        Matrix3 operator- (const Matrix3& rkMatrix) const
		{
			Matrix3 kDiff;
			for(int i = 0; i <SIZE; i++){
				kDiff._m[i] = this->_m[i] - rkMatrix._m[i];
			}
			return kDiff;
		}

		Matrix3 operator- () const
		{
			Matrix3 kNeg;

			for(int i = 0; i <SIZE; i++){
				kNeg._m[i] = -this->_m[i];
			}

			return kNeg;
		}
		inline float* operator[] (size_t iRow) const
		{
			return (float*)m[iRow];
		}
        /** Matrix concatenation using '*'. 矩阵*矩阵
         */
        Matrix3 operator* (const Matrix3& rkMatrix) const
		{
			// TODO: 待优化
			Matrix3 kProd;
			for (size_t iRow = 0; iRow < 3; iRow++)
			{
				for (size_t iCol = 0; iCol < 3; iCol++)
				{
					kProd.m[iRow][iCol] =
						m[iRow][0]*rkMatrix.m[0][iCol] +
						m[iRow][1]*rkMatrix.m[1][iCol] +
						m[iRow][2]*rkMatrix.m[2][iCol];
				}
			}
			return kProd;
		}


        /// Matrix * vector [3x3 * 3x1 = 3x1]  矩阵*向量
        Vector3 operator* (const Vector3& rkVector) const
		{
			float x = rkVector.x*this->m[0][0]+ rkVector.y*this->m[0][1] +rkVector.z*this->m[0][2];
			float y = rkVector.x*this->m[1][0] + rkVector.y*this->m[1][1] +rkVector.z*this->m[1][2];
			float z = rkVector.x*this->m[2][0] + rkVector.y*this->m[2][1] +rkVector.z*this->m[2][2];

			return Vector3(x, y, z);
		}

        /// Matrix * scalar  标量*矩阵
        Matrix3 operator* (float fScalar) const
		{
			Matrix3 kProd;

			for(int i = 0; i <SIZE; i++){
				kProd._m[i] = fScalar* this->_m[i];
			}

			return kProd;
		}

		// 矩阵转置
		Matrix3 transpose () const
		{
			return Matrix3(m[0][0], m[1][0], m[2][0],
				m[0][1], m[1][1], m[2][1],
				m[0][2], m[1][2], m[2][2]);
		}
	

		// 逆矩阵
		// 如果不存在，则返回ZERO
		inline Matrix3 inverse(float fEPSILON = Math::EPSINON) const 
		{
			Matrix3 rkInverse;
			rkInverse[0][0] = m[1][1]*m[2][2] -
				m[1][2]*m[2][1];
			rkInverse[0][1] = m[0][2]*m[2][1] -
				m[0][1]*m[2][2];
			rkInverse[0][2] = m[0][1]*m[1][2] -
				m[0][2]*m[1][1];
			rkInverse[1][0] = m[1][2]*m[2][0] -
				m[1][0]*m[2][2];
			rkInverse[1][1] = m[0][0]*m[2][2] -
				m[0][2]*m[2][0];
			rkInverse[1][2] = m[0][2]*m[1][0] -
				m[0][0]*m[1][2];
			rkInverse[2][0] = m[1][0]*m[2][1] -
				m[1][1]*m[2][0];
			rkInverse[2][1] = m[0][1]*m[2][0] -
				m[0][0]*m[2][1];
			rkInverse[2][2] = m[0][0]*m[1][1] -
				m[0][1]*m[1][0];

			float fDet =
				m[0][0]*rkInverse[0][0] +
				m[0][1]*rkInverse[1][0]+
				m[0][2]*rkInverse[2][0];

			if ( Math::abs(fDet) <= fEPSILON )
				return ZERO;

			float fInvDet = 1.0f/fDet;
			for (size_t iRow = 0; iRow < 3; iRow++)
			{
				for (size_t iCol = 0; iCol < 3; iCol++)
					rkInverse[iRow][iCol] *= fInvDet;
			}

			return rkInverse;
		}

		// 行列式
		inline float determinant() const 
		{
			float fCofactor00 = m[1][1]*m[2][2] -
				m[1][2]*m[2][1];
			float fCofactor10 = m[1][2]*m[2][0] -
				m[1][0]*m[2][2];
			float fCofactor20 = m[1][0]*m[2][1] -
				m[1][1]*m[2][0];

			float fDet =
				m[0][0]*fCofactor00 +
				m[0][1]*fCofactor10 +
				m[0][2]*fCofactor20;

			return fDet;
		}

		inline  friend std::ostream& operator <<
			( std::ostream& o, const Matrix3& mat )
		{
			o << "Matrix3:\n(" << mat.m[0][0] << ", " << mat.m[0][1] << ", " << mat.m[0][2] << ",\n " 
				<< mat.m[1][0] << ", " << mat.m[1][1] << ", " << mat.m[1][2] << ", \n" 
				<< mat.m[2][0] << ", " << mat.m[2][1] << ", " << mat.m[2][2] << ")\n";
			return o;
		}
	};	// end Matrix3

} // end Lotus

#endif