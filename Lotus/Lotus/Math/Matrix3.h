/********************************************************************
	created:	2012/08/10 
	filename: 	Matrix3.h
	author:		reedhong 
	
	purpose:	matrix operator, just for opengl
*********************************************************************/

#ifndef __Lotus_Matrix3_H__
#define __Lotus_Matrix3_H__

#include "Main/Prerequisites.h"
#include "Vector.h"

namespace Lotus {
	/*
	 *  OpenGL是按列存储的，小心了
	 */
	class Matrix3
	{
	public:
		static const Matrix3 ZERO;
		static const Matrix3 IDENTITY;
	public:
		union{
			float		_m[9];
			struct 		M
			{
				float m11, m21,m31;
				float m12, m22, m32;
				float m13, m23, m33;
			}m;
		};
	public:

		inline Matrix3(){}
		inline Matrix3(
			float m11, float m12, float m13,
			float m21, float m22,float  m23,
			float m31, float m32, float m33)
		{
			_m[0] = m11;
			_m[1] = m21;
			_m[2] = m31;
			_m[3] = m12;
			_m[4] = m22;
			_m[5] = m32;
			_m[6] = m13;
			_m[7] = m23;
			_m[8] = m33;
		}
		~Matrix3(){}

		inline Matrix3 (const Matrix3& rkMatrix)
		{
			memcpy(_m,rkMatrix._m,9*sizeof(float));
		}

		// assignment and comparison
		inline Matrix3& operator= (const Matrix3& rkMatrix)
		{
			memcpy(_m,rkMatrix._m,9*sizeof(float));
			return *this;
		}

		        /** Tests 2 matrices for equality.
         */
        bool operator== (const Matrix3& rkMatrix) const
		{
			return  (memcmp((const void *)this->_m, rkMatrix._m, sizeof(float)*9) ==0);
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
			for(int i = 0; i <9; i++){
				kSum._m[i] = this->_m[i] + rkMatrix._m[i];
			}
			return kSum;
		}

        /** Matrix subtraction.
         */
        Matrix3 operator- (const Matrix3& rkMatrix) const
		{
			Matrix3 kDiff;
			for(int i = 0; i <9; i++){
				kDiff._m[i] = this->_m[i] - rkMatrix._m[i];
			}
			return kDiff;
		}

		Matrix3 operator- () const
		{
			Matrix3 kNeg;

			for(int i = 0; i <9; i++){
				kNeg._m[i] = -this->_m[i];
			}

			return kNeg;
		}

        /** Matrix concatenation using '*'. 矩阵*矩阵
         */
        Matrix3 operator* (const Matrix3& rkMatrix) const
		{
			return ZERO;
		}


        /// Matrix * vector [3x3 * 3x1 = 3x1]  矩阵*向量
        Vector3 operator* (const Vector3& rkVector) const
		{
			return Vector3::ZeroVector;
		}

        /// Matrix * scalar  标量*矩阵
        Matrix3 operator* (float fScalar) const
		{
			Matrix3 kProd;

			for(int i = 0; i <9; i++){
				kProd._m[i] = fScalar* this->_m[i];
			}

			return kProd;
		}

		// 矩阵转置
		Matrix3 transpose () const
		{
			Matrix3 kTranspose;

			kTranspose.m.m11 = this->m.m11;
			kTranspose.m.m12 = this->m.m21;
			kTranspose.m.m13 = this->m.m31;

			kTranspose.m.m21 = this->m.m12;
			kTranspose.m.m22 = this->m.m22;
			kTranspose.m.m23 = this->m.m32;

			kTranspose.m.m31 = this->m.m13;
			kTranspose.m.m32 = this->m.m23;
			kTranspose.m.m33 = this->m.m33;

			return kTranspose;
		}
		
		// 转置自己
		void transposeSelf()  
		{
			std::swap<float>(m.m12, m.m21);
			std::swap<float>(m.m13, m.m31);
			std::swap<float>(m.m23, m.m32);
		}

		// 逆矩阵
		void inverse() const 
		{
			
		}


	};	// end Matrix3

} // end Lotus

#endif