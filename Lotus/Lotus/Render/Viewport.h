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
		int	left;
		int	top;
		int	width;
		int	height;
		void set(int l, int t, int w, int h)
		{
			left = l;
			top = t;
			width = w;
			height = h;
		}
	};
}

#endif
