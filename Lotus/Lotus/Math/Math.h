/********************************************************************
	created:	2012/08/08 
	filename: 	Math.h
	author:		reedhong 
	
	purpose:	��ѧ��ص�
*********************************************************************/

#ifndef __Lotus_Math_H__
#define __Lotus_Math_H__

#include <math.h>

namespace Lotus {
	float const  EPSINON = 0.00001; 
	float const PI		= 3.141592f;			// PI
	float const PI2		= 6.283185f;			// PI * 2
	float const PIdiv2	= 1.570796f;			// PI / 2

	float const DEG90	= 1.570796f;			// 90 ��
	float const DEG270	= -1.570796f;			// 270 ��
	float const DEG45	= 0.7853981f;			// 45 ��
	float const DEG5	= 0.0872664f;			// 5 ��
	float const DEG10	= 0.1745329f;			// 10 ��
	float const DEG20	= 0.3490658f;			// 20 ��
	float const DEG30	= 0.5235987f;			// 30 ��
	float const DEG60	= 1.047197f;			// 60 ��
	float const DEG120	= 2.094395f;			// 120 ��

	float const DEG40	= 0.6981317f;			// 40 ��
	float const DEG80	= 1.396263f;			// 80 ��
	float const DEG140	= 2.443460f;			// 140 ��
	float const DEG160	= 2.792526f;			// 160 ��

	float const SQRT2	= 1.414213f;			// ��2
	float const SQRT_2	= 0.7071068f;			// 1 / SQRT2
	float const SQRT3	= 1.732050f;			// ��3

	float const DEG2RAD	= 0.01745329f;			// �ǶȻ���������
	float const RAD2DEG	= 57.29577f;			// ���Ȼ��Ƕ�����
}

#endif