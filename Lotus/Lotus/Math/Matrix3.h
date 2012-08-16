/********************************************************************
	created:	2012/08/10 
	filename: 	Matrix3.h
	author:		reedhong 
	
	purpose:	matrix operator, just for opengl
*********************************************************************/

#ifndef __Lotus_Matrix3_H__
#define __Lotus_Matrix3_H__

#include "Main/Prerequisites.h"
#include "Vector3.h"

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
		struct 		Matrix3Struct
		{
			float m11, m21,m31;
			float m12, m22, m32;
			float m13, m23, m33;
		};
		union{
			float					m[SIZE];
			Matrix3Struct	ms;
		};
	public:

		inline Matrix3(){}
		inline Matrix3(
			float m11, float m12, float m13,
			float m21, float m22,float  m23,
			float m31, float m32, float m33)
		{
			m[0] = m11;
			m[1] = m21;
			m[2] = m31;
			m[3] = m12;
			m[4] = m22;
			m[5] = m32;
			m[6] = m13;
			m[7] = m23;
			m[8] = m33;
		}
		~Matrix3(){}

		inline Matrix3 (const Matrix3& rkMatrix)
		{
			memcpy(m,rkMatrix.m,SIZE*sizeof(float));
		}

		// assignment and comparison
		inline Matrix3& operator= (const Matrix3& rkMatrix)
		{
			memcpy(m,rkMatrix.m,SIZE*sizeof(float));
			return *this;
		}

		/** Tests 2 matrices for equality.
         */
        bool operator== (const Matrix3& rkMatrix) const
		{
			return  (memcmp((const void *)this->m, rkMatrix.m, sizeof(float)*SIZE) ==0);
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
				kSum.m[i] = this->m[i] + rkMatrix.m[i];
			}
			return kSum;
		}

        /** Matrix subtraction.
         */
        Matrix3 operator- (const Matrix3& rkMatrix) const
		{
			Matrix3 kDiff;
			for(int i = 0; i <SIZE; i++){
				kDiff.m[i] = this->m[i] - rkMatrix.m[i];
			}
			return kDiff;
		}

		Matrix3 operator- () const
		{
			Matrix3 kNeg;

			for(int i = 0; i <SIZE; i++){
				kNeg.m[i] = -this->m[i];
			}

			return kNeg;
		}

        /** Matrix concatenation using '*'. 矩阵*矩阵
         */
        Matrix3 operator* (const Matrix3& rkMatrix) const
		{
			Matrix3 kProd;
			kProd.m[0] = this->m[0]*rkMatrix.m[0]+this->m[3]*rkMatrix.m[1]
				+this->m[6]*rkMatrix.m[2];
			kProd.m[3] = this->m[0]*rkMatrix.m[3]+this->m[3]*rkMatrix.m[4]
				+this->m[6]*rkMatrix.m[5];
			kProd.m[6] = this->m[0]*rkMatrix.m[6]+this->m[3]*rkMatrix.m[7]
				+this->m[6]*rkMatrix.m[8];

			kProd.m[1] = this->m[1]*rkMatrix.m[0]+this->m[4]*rkMatrix.m[1]
				+this->m[7]*rkMatrix.m[2];
			kProd.m[4] = this->m[1]*rkMatrix.m[3]+this->m[4]*rkMatrix.m[4]
				+this->m[7]*rkMatrix.m[5];
			kProd.m[7] = this->m[1]*rkMatrix.m[6]+this->m[4]*rkMatrix.m[7]
				+this->m[7]*rkMatrix.m[8];

			kProd.m[2] = this->m[2]*rkMatrix.m[0]+this->m[5]*rkMatrix.m[1]
				+this->m[8]*rkMatrix.m[2];
			kProd.m[5] = this->m[2]*rkMatrix.m[3]+this->m[5]*rkMatrix.m[4]
				+this->m[8]*rkMatrix.m[5];
			kProd.m[8] = this->m[2]*rkMatrix.m[6]+this->m[5]*rkMatrix.m[7]
				+this->m[8]*rkMatrix.m[8];

			return kProd;
		}


        /// Matrix * vector [3x3 * 3x1 = 3x1]  矩阵*向量
        Vector3 operator* (const Vector3& rkVector) const
		{
			float x = rkVector.x*this->m[0] + rkVector.y*this->m[3] +rkVector.z*this->m[6];
			float y = rkVector.x*this->m[1] + rkVector.y*this->m[4] +rkVector.z*this->m[7];
			float z = rkVector.x*this->m[2] + rkVector.y*this->m[5] +rkVector.z*this->m[8];

			return Vector3(x, y, z);
		}

        /// Matrix * scalar  标量*矩阵
        Matrix3 operator* (float fScalar) const
		{
			Matrix3 kProd;

			for(int i = 0; i <SIZE; i++){
				kProd.m[i] = fScalar* this->m[i];
			}

			return kProd;
		}

		// 矩阵转置
		Matrix3 transpose () const
		{
			Matrix3 kTranspose = *this;
			kTranspose.transposeSelf();

			return kTranspose;
		}
		
		// 转置自己
		void transposeSelf()  
		{
			std::swap<float>(m[1], m[3]);
			std::swap<float>(m[2], m[6]);
			std::swap<float>(m[5], m[7]);
		}

		// 逆矩阵
		// 如果不存在，则返回ZERO
		inline Matrix3 inverse(float fEPSILON = EPSINON) const 
		{
			Matrix3 rkInverse;

			// 先求伴随矩阵的转置
			 rkInverse.m[0] = m[4]*m[8]- m[5]*m[7];
			 rkInverse.m[1] = m[2]*m[7]- m[1]*m[8];
			 rkInverse.m[2] = m[1]*m[5]- m[2]*m[4];

			 rkInverse.m[3] = m[5]*m[6]- m[3]*m[8];
			 rkInverse.m[4] = m[0]*m[8]- m[2]*m[6];
			 rkInverse.m[5] = m[2]*m[3]- m[0]*m[5];
			 
			 rkInverse.m[6] = m[3]*m[7]- m[4]*m[6];
			 rkInverse.m[7] = m[1]*m[6]- m[0]*m[7];
			 rkInverse.m[8] = m[0]*m[4]- m[1]*m[3];


			float fDet =
				this->m[0]*rkInverse.m[0] +
				this->m[3]*rkInverse.m[1] +
				this->m[6]*rkInverse.m[2];

			if ( abs(fDet) <= EPSINON )
				return ZERO;

			float fInvDet = 1.0f/fDet;
			for(int i = 0; i < SIZE; i++){
				rkInverse.m[i] *= fInvDet;
			}
		}

		// 行列式
		inline float determinant() const 
		{
			return (m[0]*m[4]*m[8]+m[3]*m[7]*m[2]+m[6]*m[1]*m[5]-
				m[0]*m[7]*m[5]-m[3]*m[1]*m[8]-m[6]*m[4]*m[2]);
		}

		inline  friend std::ostream& operator <<
			( std::ostream& o, const Matrix3& mat )
		{
			o << "Matrix3:\n(" << mat.m[0] << ", " << mat.m[3] << ", " << mat.m[6] << ",\n " 
				<< mat.m[1] << ", " << mat.m[4] << ", " << mat.m[7] << ", \n" 
				<< mat.m[2] << ", " << mat.m[6] << ", " << mat.m[8] << ")\n";
			return o;
		}
	};	// end Matrix3

} // end Lotus

#endif