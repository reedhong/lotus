/********************************************************************
	created:	2012/08/29 
	filename: 	Endian.cpp
	author:		reedhong 
	
	purpose:	
*********************************************************************/

#include "Endian.h"

namespace Lotus {
	const  Endian::endian_un Endian::value = {short(1)};
	const bool Endian::s_IsLittleEndian = value.sb.isLittleEndian;
}