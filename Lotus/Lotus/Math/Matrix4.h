/********************************************************************
	created:	2012/08/10 
	filename: 	Matrix4.h
	author:		reedhong 
	
	purpose:	matrix operator, just for opengl
*********************************************************************/

#ifndef __Lotus_Matrix4_H__
#define __Lotus_Matrix4_H__

#include "Main/Prerequisites.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Lotus {
	/*
	 *  OpenGL是按列存储的，小心了
	 */
	class Matrix4
	{
	public:
		static const Matrix4 ZERO;
		static const Matrix4 ZEROAFFINE;
		static const Matrix4 IDENTITY;
		static const int SIZE = 16;
	public:
		struct 		Matrix4Struct
		{
			float m11, m21,m31, m41;
			float m12, m22, m32, m42;
			float m13, m23, m33, m43;
			float m14, m24, m34, m44;
		};
		union{
			float					m[SIZE];
			Matrix4Struct 	ms;
		};
	public:
		
		inline Matrix4(){}
		inline Matrix4(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
		{
			m[0] = m11;
			m[1] = m21;
			m[2] = m31;
			m[3] = m41;
			m[4] = m12;
			m[5] = m22;
			m[6] = m32;
			m[7] = m42;
			m[8] = m13;
			m[9] = m23;
			m[10] = m33;
			m[11] = m43;
			m[12] = m14;
			m[13] = m24;
			m[14] = m34;
			m[15] = m44;
 		}

		~Matrix4(){}
		inline void set(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
		{
			m[0] = m11;
			m[1] = m21;
			m[2] = m31;
			m[3] = m41;
			m[4] = m12;
			m[5] = m22;
			m[6] = m32;
			m[7] = m42;
			m[8] = m13;
			m[9] = m23;
			m[10] = m33;
			m[11] = m43;
			m[12] = m14;
			m[13] = m24;
			m[14] = m34;
			m[15] = m44;
		}
	inline Matrix4 (const Matrix4& rkMatrix)
		{
			memcpy(m,rkMatrix.m,SIZE*sizeof(float));
		}

		// assignment and comparison
		inline Matrix4& operator= (const Matrix4& rkMatrix)
		{
			memcpy(m,rkMatrix.m,SIZE*sizeof(float));
			return *this;
		}

		/** Tests 2 matrices for equality.
         */
        bool operator== (const Matrix4& rkMatrix) const
		{
			return  (memcmp((const void *)this->m, rkMatrix.m, sizeof(float)*SIZE) ==0);
		}

        /** Tests 2 matrices for inequality.
         */
        inline bool operator!= (const Matrix4& rkMatrix) const
		{
			return !operator==(rkMatrix);
		}

		 // arithmetic operations
        /** Matrix addition.
         */
        Matrix4 operator+ (const Matrix4& rkMatrix) const
		{
			Matrix4 kSum;
			for(int i = 0; i <SIZE; i++){
				kSum.m[i] = this->m[i] + rkMatrix.m[i];
			}
			return kSum;
		}

        /** Matrix subtraction.
         */
        Matrix4 operator- (const Matrix4& rkMatrix) const
		{
			Matrix4 kDiff;
			for(int i = 0; i <SIZE; i++){
				kDiff.m[i] = this->m[i] - rkMatrix.m[i];
			}
			return kDiff;
		}

		Matrix4 operator- () const
		{
			Matrix4 kNeg;

			for(int i = 0; i <SIZE; i++){
				kNeg.m[i] = -this->m[i];
			}

			return kNeg;
		}

   /** Matrix concatenation using '*'. 矩阵*矩阵
         */
        Matrix4 operator* (const Matrix4& rkMatrix) const
		{
			Matrix4 kProd;
			kProd.m[0] = this->m[0]*rkMatrix.m[0]+this->m[4]*rkMatrix.m[1]
				+this->m[8]*rkMatrix.m[2] + +this->m[12]*rkMatrix.m[3];
			kProd.m[4] = this->m[0]*rkMatrix.m[4]+this->m[4]*rkMatrix.m[5]
				+this->m[8]*rkMatrix.m[6] + +this->m[12]*rkMatrix.m[7];
			kProd.m[8] = this->m[0]*rkMatrix.m[8]+this->m[4]*rkMatrix.m[9]
				+this->m[8]*rkMatrix.m[10] + +this->m[12]*rkMatrix.m[11];
			kProd.m[12] = this->m[0]*rkMatrix.m[12]+this->m[4]*rkMatrix.m[13]
				+this->m[8]*rkMatrix.m[14] + +this->m[12]*rkMatrix.m[15];

			kProd.m[1] = this->m[1]*rkMatrix.m[0]+this->m[5]*rkMatrix.m[1]
				+this->m[9]*rkMatrix.m[2] + +this->m[13]*rkMatrix.m[3];
			kProd.m[5] = this->m[1]*rkMatrix.m[4]+this->m[5]*rkMatrix.m[5]
				+this->m[9]*rkMatrix.m[6] + +this->m[13]*rkMatrix.m[7];
			kProd.m[9] = this->m[1]*rkMatrix.m[8]+this->m[5]*rkMatrix.m[9]
				+this->m[9]*rkMatrix.m[10] + +this->m[13]*rkMatrix.m[11];
			kProd.m[13] = this->m[1]*rkMatrix.m[12]+this->m[5]*rkMatrix.m[13]
				+this->m[9]*rkMatrix.m[14] + +this->m[13]*rkMatrix.m[15];

			kProd.m[2] = this->m[2]*rkMatrix.m[0]+this->m[6]*rkMatrix.m[1]
				+this->m[10]*rkMatrix.m[2] + +this->m[14]*rkMatrix.m[3];
			kProd.m[6] = this->m[2]*rkMatrix.m[4]+this->m[6]*rkMatrix.m[5]
				+this->m[10]*rkMatrix.m[6] + +this->m[14]*rkMatrix.m[7];
			kProd.m[10] = this->m[2]*rkMatrix.m[8]+this->m[6]*rkMatrix.m[9]
				+this->m[10]*rkMatrix.m[10] + +this->m[14]*rkMatrix.m[11];
			kProd.m[14] = this->m[2]*rkMatrix.m[12]+this->m[6]*rkMatrix.m[13]
				+this->m[10]*rkMatrix.m[14] + +this->m[14]*rkMatrix.m[15];

			kProd.m[3] = this->m[3]*rkMatrix.m[0]+this->m[7]*rkMatrix.m[1]
				+this->m[11]*rkMatrix.m[2] + +this->m[15]*rkMatrix.m[3];
			kProd.m[7] = this->m[3]*rkMatrix.m[4]+this->m[7]*rkMatrix.m[5]
				+this->m[11]*rkMatrix.m[6] + +this->m[15]*rkMatrix.m[7];
			kProd.m[11] = this->m[3]*rkMatrix.m[8]+this->m[7]*rkMatrix.m[9]
				+this->m[11]*rkMatrix.m[10] + +this->m[15]*rkMatrix.m[11];
			kProd.m[15] = this->m[3]*rkMatrix.m[12]+this->m[7]*rkMatrix.m[13]
				+this->m[11]*rkMatrix.m[14] + +this->m[15]*rkMatrix.m[15];
		

			return kProd;
		}



   /// Matrix * vector [3x3 * 3x1 = 3x1]  矩阵*向量
        Vector3 operator* (const Vector3& v) const
		{
			float fInvW = 1.0f/(m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]);
			float x = (v.x*this->m[0] + v.y*this->m[4] +v.z*this->m[8]+m[12]) * fInvW;
			float y = (v.x*this->m[1] + v.y*this->m[5] +v.z*this->m[9]+m[13]) * fInvW;
			float z = (v.x*this->m[2] + v.y*this->m[6] +v.z*this->m[10]+m[14]) * fInvW;

			return Vector3(x, y, z);
		}

		Vector4 operator* (const Vector4& v) const
		{
			float x = v.x*m[0] + v.y*m[4] +v.z*m[8]+v.w*m[12];
			float y = v.x*m[1] + v.y*m[5] +v.z*m[9]+v.w*m[13];
			float z = v.x*m[2] + v.y*m[6] +v.z*m[10]+v.w*m[14];
			float w = v.x*m[3] + v.y*m[7] +v.z*m[11]+v.w*m[15];
			return Vector4(x, y, z,w);
		}

        /// Matrix * scalar  标量*矩阵
        Matrix4 operator* (float fScalar) const
		{
			Matrix4 kProd;

			for(int i = 0; i <SIZE; i++){
				kProd.m[i] = fScalar* this->m[i];
			}

			return kProd;
		}

		// 矩阵转置
		Matrix4 transpose () const
		{
			Matrix4 kTranspose = *this;
			kTranspose.transposeSelf();

			return kTranspose;
		}
		
		// 转置自己
		void transposeSelf()  
		{
			std::swap<float>(m[1], m[2]);
			std::swap<float>(m[2], m[8]);
			std::swap<float>(m[3], m[12]);
			std::swap<float>(m[6], m[9]);
			std::swap<float>(m[7], m[13]);
			std::swap<float>(m[11], m[14]);			
		}

		// 逆矩阵
		// 如果不存在，则返回ZERO
		Matrix4 inverse(float fEPSILON = EPSINON) const 
		{
			Matrix4 rkInverse;

			// 先求伴随矩阵的转置
			rkInverse.m[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
			+ m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
			rkInverse.m[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
			- m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
			rkInverse.m[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15]
			+ m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
			rkInverse.m[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
			- m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
			rkInverse.m[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
			- m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
			rkInverse.m[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
			+ m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
			rkInverse.m[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
			- m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
			rkInverse.m[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
			+ m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
			rkInverse.m[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
			+ m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
			rkInverse.m[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
			- m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
			rkInverse.m[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
			+ m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
			rkInverse.m[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
			- m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
			rkInverse.m[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
			- m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
			rkInverse.m[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
			+ m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
			rkInverse.m[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
			- m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
			rkInverse.m[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
			+ m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];



			float fDet =m[0]*rkInverse.m[0] + m[1]*rkInverse.m[4] + m[2]*rkInverse.m[8] + m[3]*rkInverse.m[12];

			if ( abs(fDet) <= EPSINON )
				return ZERO;

			float fInvDet = 1.0f/fDet;
			for(int i = 0; i < SIZE; i++){
				rkInverse.m[i] *= fInvDet;
			}

			return rkInverse;
		}


		// 行列式
		inline float determinant() const 
		{
			Matrix4 rkInverse;

			// 先求伴随矩阵的转置
			rkInverse.m[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
			+ m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
			rkInverse.m[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
			- m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
			rkInverse.m[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15]
			+ m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
			rkInverse.m[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
			- m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
			rkInverse.m[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
			- m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
			rkInverse.m[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
			+ m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
			rkInverse.m[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
			- m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
			rkInverse.m[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
			+ m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
			rkInverse.m[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
			+ m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
			rkInverse.m[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
			- m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
			rkInverse.m[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
			+ m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
			rkInverse.m[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
			- m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
			rkInverse.m[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
			- m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
			rkInverse.m[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
			+ m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
			rkInverse.m[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
			- m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
			rkInverse.m[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
			+ m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];



			float fDet =m[0]*rkInverse.m[0] + m[1]*rkInverse.m[4] + m[2]*rkInverse.m[8] + m[3]*rkInverse.m[12];

			return fDet;
		}

		inline  friend std::ostream& operator <<
			( std::ostream& o, const Matrix4& mat )
		{
			o << "Matrix4:\n(" 
				<< mat.m[0] << ", " << mat.m[4] << ", " << mat.m[8] << ", " << mat.m[12] <<",\n " 
				<< mat.m[1] << ", " << mat.m[5] << ", " << mat.m[9] << ", " << mat.m[13]<< ", \n" 
				<< mat.m[2] << ", " << mat.m[6] << ", " << mat.m[10] << ", " << mat.m[14]<< ", \n" 
				<< mat.m[3] << ", " << mat.m[7] << ", " << mat.m[11] << ", " << mat.m[15]<< ")\n";
			return o;
		}
	};	// end Matrix4
} // end Lotus

#endif