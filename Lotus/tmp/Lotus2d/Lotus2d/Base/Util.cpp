/********************************************************************
	created:	2012/09/16
	filename: 	Util.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include "Util.h"

namespace Lotus2d {
	// todo: 暂时只能解决windows中的情况
	char* Util::getFileNameNoExt(char* szPath)
	{
		if (!szPath) return NULL;
		int endpos = 0;
		int len = strlen(szPath);
		char *p = szPath + len;
		while (len){
			if(*p == '.'){
				endpos = len;	
			}else if (*p == '\\'){
					break;
				}
				p--; len--;
		}

		if(len < endpos){
			char *pnew = new char[endpos - len];
			strncpy (pnew,szPath + len + 1,endpos - len - 1);
			*(pnew + (endpos - len - 1)) = '\0';
			return pnew;
		}
		return NULL;
	}
}