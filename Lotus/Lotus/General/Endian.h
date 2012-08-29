/********************************************************************
	created:	2012/08/29 
	filename: 	Endian.h
	author:		reedhong 
	
	purpose:	×Ö½ÚÐò
*********************************************************************/

#ifndef __Lotus_Endian_H__
#define __Lotus_Endian_H__

namespace Lotus{
	class Endian
	{
		union endian_un{
			struct{
				bool	isLittleEndian;
				bool	tmp;
			}sb;
			short iValue;
		};	
		static const  endian_un value; 
	public:
		
		static const bool s_IsLittleEndian;

		static void FlipEndian(void * pData, size_t size, size_t count)
		{
			for(unsigned int index = 0; index < count; index++)
			{
				FlipEndian((void *)((size_t)pData + (index * size)), size);
			}
		}

		static void FlipEndian(void * pData, size_t size)
		{
			char swapByte;
			for(unsigned int byteIndex = 0; byteIndex < size/2; byteIndex++)
			{
				swapByte = *(char *)((size_t)pData + byteIndex);
				*(char *)((size_t)pData + byteIndex) = *(char *)((size_t)pData + size - byteIndex - 1);
				*(char *)((size_t)pData + size - byteIndex - 1) = swapByte;
			}
		}
		
		
	};
}

#endif