/********************************************************************
	created:	2012/09/11
	filename: 	Lotus2d.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Engine.h"

namespace Lotus2d {
	Engine::Engine()
	{

	}
	
	Engine::~Engine()
	{

	}

	// instance
	Engine * Engine::Instance(void)
	{
		static Engine s_instance;
		return &s_instance;
	}
}