/********************************************************************
	created:	2012/09/11
	filename: 	GameInterface.h
	author:		reedhong
	
	purpose:	��Ϸ�߼����ⲿ�ӿ�
*********************************************************************/

#ifndef __Game_Interface_H__
#define __Game_Interface_H__

void gameStartup(int width,int height,float scale=1.0);

void gameEnd();

void gameFrame();

void gamePause();

void gameResume();

#endif
