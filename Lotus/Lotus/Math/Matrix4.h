/********************************************************************
	created:	2012/08/10 
	filename: 	Matrix4.h
	author:		reedhong 
	
	purpose:	matrix operator, just for opengl
	@par
	The generic form M * V which shows the layout of the matrix 
	entries is shown below:
	<pre>
	[ m[0][0]  m[0][1]  m[0][2]  m[0][3] ]   {x}
	| m[1][0]  m[1][1]  m[1][2]  m[1][3] | * {y}
	| m[2][0]  m[2][1]  m[2][2]  m[2][3] |   {z}
	[ m[3][0]  m[3][1]  m[3][2]  m[3][3] ]   {1}
	</pre>
	按行存储，右手坐标系，右乘
	注: 虽然最终存储到OpenGL中的矩阵是按列存储的，但如果实现的时候也按照列去存储
	中间容易出现问题，市面上大多数的公式都是按照行来搞的，非常容易绕，所以这个地方
	的实现最终也是按照行来存储，在最终存入OpenGL的时候来一个转置就搞定
*********************************************************************/

#ifndef __Lotus_Matrix4_H__
#define __Lotus_Matrix4_H__

#include "Main/Prerequisites.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Quaternion.h"

namespace Lotus {

	class Matrix4
	{
	public:
		static const Matrix4 ZERO;
		static const Matrix4 ZEROAFFINE;
		static const Matrix4 IDENTITY;
		static const int SIZE = 16;
	public:
		union{
			float					_m[SIZE];
			float					m[4][4];
		};
	public:
		
		inline Matrix4(){}
		inline Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33 )
		{
			set(
				m00,  m01,  m02,  m03,
				m10,  m11,  m12,  m13,
				m20,  m21,  m22,  m23,
				m30,  m31,  m32,  m33 
				);
 		}

		~Matrix4(){}
		inline void set(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33 )
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;
			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}
		inline Matrix4 (const Matrix4& rkMatrix)
		{
			memcpy(_m,rkMatrix._m,SIZE*sizeof(float));
		}

		inline Matrix4(const Matrix3& m3x3)
		{
			operator=(IDENTITY);
			operator=(m3x3);
		}
		// assignment and comparison
		inline Matrix4& operator= (const Matrix4& rkMatrix)
		{
			memcpy(_m,rkMatrix._m,SIZE*sizeof(float));
			return *this;
		}

        /** Assignment from 3x3 matrix.
        */
        inline void operator = ( const Matrix3& mat3 )
        {
            m[0][0] = mat3.m[0][0]; m[0][1] = mat3.m[0][1]; m[0][2] = mat3.m[0][2];
            m[1][0] = mat3.m[1][0]; m[1][1] = mat3.m[1][1]; m[1][2] = mat3.m[1][2];
            m[2][0] = mat3.m[2][0]; m[2][1] = mat3.m[2][1]; m[2][2] = mat3.m[2][2];
        }

		/** Tests 2 matrices for equality.
         */
        bool operator== (const Matrix4& rkMatrix) const
		{
			return  (memcmp((const void *)this->_m, rkMatrix._m, sizeof(float)*SIZE) ==0);
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
				kSum._m[i] = this->_m[i] + rkMatrix._m[i];
			}
			return kSum;
		}

        /** Matrix subtraction.
         */
        Matrix4 operator- (const Matrix4& rkMatrix) const
		{
			Matrix4 kDiff;
			for(int i = 0; i <SIZE; i++){
				kDiff._m[i] = this->_m[i] - rkMatrix._m[i];
			}
			return kDiff;
		}

		Matrix4 operator- () const
		{
			Matrix4 kNeg;

			for(int i = 0; i <SIZE; i++){
				kNeg._m[i] = -this->_m[i];
			}

			return kNeg;
		}
		inline float* operator [] ( size_t iRow )
		{
			assert( iRow < 4 );
			return m[iRow];
		}


		inline const float *operator [] ( size_t iRow ) const
		{
			assert( iRow < 4 );
			return m[iRow];
		}
   /** Matrix concatenation using '*'. 矩阵*矩阵
         */
        Matrix4 operator* (const Matrix4& m2) const
		{
			Matrix4 r;
			r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
			r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
			r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
			r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

			r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
			r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
			r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
			r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

			r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
			r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
			r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
			r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

			r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
			r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
			r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
			r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

			return r;
		}



   /// Matrix * vector [3x3 * 3x1 = 3x1]  矩阵*向量
        Vector3 operator* (const Vector3& v) const
		{
			Vector3 r;

			float fInvW = 1.0f / ( m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] );

			r.x = ( m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] ) * fInvW;
			r.y = ( m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] ) * fInvW;
			r.z = ( m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] ) * fInvW;

			return r;
		}

		Vector4 operator* (const Vector4& v) const
		{
			return Vector4(
				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w, 
				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
				m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
				);
		}

        /// Matrix * scalar  标量*矩阵
        Matrix4 operator* (float fScalar) const
		{
			Matrix4 kProd;

			for(int i = 0; i <SIZE; i++){
				kProd._m[i] = fScalar* this->_m[i];
			}

			return kProd;
		}

		// 矩阵转置
		Matrix4 transpose () const
		{
			return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
				m[0][1], m[1][1], m[2][1], m[3][1],
				m[0][2], m[1][2], m[2][2], m[3][2],
				m[0][3], m[1][3], m[2][3], m[3][3]);
		}
		

		// 逆矩阵
		// 如果不存在，则返回ZERO
		Matrix4 inverse() const 
		{
			float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
			float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
			float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
			float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

			float v0 = m20 * m31 - m21 * m30;
			float v1 = m20 * m32 - m22 * m30;
			float v2 = m20 * m33 - m23 * m30;
			float v3 = m21 * m32 - m22 * m31;
			float v4 = m21 * m33 - m23 * m31;
			float v5 = m22 * m33 - m23 * m32;

			float t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
			float t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
			float t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
			float t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

			float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

			float d00 = t00 * invDet;
			float d10 = t10 * invDet;
			float d20 = t20 * invDet;
			float d30 = t30 * invDet;

			float d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			float d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			float d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			float d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			v0 = m10 * m31 - m11 * m30;
			v1 = m10 * m32 - m12 * m30;
			v2 = m10 * m33 - m13 * m30;
			v3 = m11 * m32 - m12 * m31;
			v4 = m11 * m33 - m13 * m31;
			v5 = m12 * m33 - m13 * m32;

			float d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			float d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			float d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			float d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			v0 = m21 * m10 - m20 * m11;
			v1 = m22 * m10 - m20 * m12;
			v2 = m23 * m10 - m20 * m13;
			v3 = m22 * m11 - m21 * m12;
			v4 = m23 * m11 - m21 * m13;
			v5 = m23 * m12 - m22 * m13;

			float d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			float d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			float d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			float d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			return Matrix4(
				d00, d01, d02, d03,
				d10, d11, d12, d13,
				d20, d21, d22, d23,
				d30, d31, d32, d33);
		}


		// 行列式
		inline float determinant() const 
		{
			return m[0][0] * Minor(*this, 1, 2, 3, 1, 2, 3) -
				m[0][1] * Minor(*this, 1, 2, 3, 0, 2, 3) +
				m[0][2] * Minor(*this, 1, 2, 3, 0, 1, 3) -
				m[0][3] * Minor(*this, 1, 2, 3, 0, 1, 2);
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

		Matrix3 extractMatrix3() const 
		{
			Matrix3 m3x3;
			m3x3.m[0][0] = m[0][0];
			m3x3.m[0][1] = m[0][1];
			m3x3.m[0][2] = m[0][2];
			m3x3.m[1][0] = m[1][0];
			m3x3.m[1][1] = m[1][1];
			m3x3.m[1][2] = m[1][2];
			m3x3.m[2][0] = m[2][0];
			m3x3.m[2][1] = m[2][1];
			m3x3.m[2][2] = m[2][2];
			return m3x3;
		}

		Quaternion extractQuaternion() const 
		{
			Matrix3 m3 = extractMatrix3();
			Quaternion q(m3);
			return q;
		}


		void decomposition(Vector3& position, Vector3& scale, Quaternion& orientation) const;
		


		//////////////////////////////////////////////////////////////////////////
		// static 

		/*
		 * 根据位置和四元向量生成一个4元矩阵
		 */
		static Matrix4 MakeViewMatrix(const Vector3& postion, const Quaternion& orientation);

		/*
		 * 根据三元向量生出平移矩阵
		 */
		static Matrix4 MakeTransMatrix4(const Vector3& v)
		{
			Matrix4 tMatrix = IDENTITY;
			tMatrix.m[0][3] = v.x;
			tMatrix.m[1][3] = v.y;
			tMatrix.m[2][3] = v.z;

			return tMatrix;
		}
	
		/*
		 * 根据三元向量生出缩放矩阵
		 */
		static Matrix4 MakeScaleMatrix4(const Vector3& v)
		{
			Matrix4 sMatrix = IDENTITY;
			sMatrix.m[0][0] = v.x;
			sMatrix.m[1][1] = v.y;
			sMatrix.m[2][2] = v.z;
			return sMatrix;
		}

		static float	Minor(const Matrix4& m, const size_t r0, const size_t r1, const size_t r2, 
			const size_t c0, const size_t c1, const size_t c2)
		{
			return m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
				m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
				m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);
		}
	};	// end Matrix4
} // end Lotus

#endif