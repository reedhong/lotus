/********************************************************************
	created:	2012/08/12
	filename: 	Viewport.h
	author:		reedhong
	
	purpose:	此处学习KlayGE, Ogre的camera之类太过复杂了
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
