/********************************************************************
	created:	2012/09/11
	filename: 	Render.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Render.h"

namespace Lotus2d{
	Render::Render():mVertexIndex(0), mPrimitiveType(ePRIMITIVE_QUARD)
	{
		for (int i = 0; i < MAX_ARRAY_SIZE * 3 / 2; i+=6 ) {
			int q = i / 6 * 4;
			mQuadIndexes[ i + 0 ] = q + 0;
			mQuadIndexes[ i + 1 ] = q + 1;
			mQuadIndexes[ i + 2 ] = q + 2;
			mQuadIndexes[ i + 3 ] = q + 0;
			mQuadIndexes[ i + 4 ] = q + 2;
			mQuadIndexes[ i + 5 ] = q + 3;
		}
	}
}
