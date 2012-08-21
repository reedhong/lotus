/********************************************************************
	created:	2012/08/08 
	filename: 	Math.h
	author:		reedhong 
	
	purpose:	��ѧ��ص�
						Ogre�����ֵļ�������˻�����ƣ��������Կ�������
*********************************************************************/

#ifndef __Lotus_Math_H__
#define __Lotus_Math_H__

#include <cmath>
//using namespace  std;

namespace Lotus {	
	class Math{
	public:
		static float  EPSINON;
		static float PI;
		static float Deg2Rad;
		static float Rad2Def;
	public:
		Math();
		~Math();

	public:
		//////////////////////////////////////////////////////////////////////////
		// ��װһЩ���õ���ѧ������Ϊ������չ���߼�����׼��
		static float abs(float f)
		{
			return std::abs(f);
		}

		static float cos(float f)
		{
			return std::cos(f);
		}

		static float sin(float f)
		{
			return std::sin(f);
		}

		static float tan(float f)
		{
			return std::tan(f);
		}

		static float sqrt(float f)
		{
			return std::sqrt(f);
		}
	}; // end Math
} // end Lotus
#endif