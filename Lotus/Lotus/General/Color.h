/********************************************************************
	created:	2012/08/10 
	filename: 	Color.h
	author:		reedhong 
	
	purpose:	color
*********************************************************************/

#ifndef __Lotus_Color_H__
#define __Lotus_Color_H__

namespace Lotus {
	class Color
	{	
	public:
		static const Color ZERO;
		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
	public:
		float r,g,b,a;
	public:	
		explicit Color( float red = 1.0f,
			float green = 1.0f,
			float blue = 1.0f,
			float alpha = 1.0f ) : r(red), g(green), b(blue), a(alpha)
		{ }
	};
}

#endif