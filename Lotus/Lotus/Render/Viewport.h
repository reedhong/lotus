/********************************************************************
	created:	2012/08/12
	filename: 	Viewport.h
	author:		reedhong
	
	purpose:	�˴�ѧϰKlayGE, Ogre��camera֮��̫��������
*********************************************************************/

#ifndef __Lotus_Viewport_H__
#define __Lotus_Viewport_H__

namespace Lotus {
	class Viewport 
	{
	public:
		int mWidth;
		int mHeight;
		void setWH(int w, int h)
		{
			mWidth = w;
			mHeight = h;
		}
	};
}

#endif
