#pragma once
#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
class Globals
{
public:
	static const int screenWidth = 960;
	static const int screenHeight = 720;
	static bool isNumber(char* source)
	{
		for (int i = 0; i < strlen(source); i++)
		{
			if (source[i]<'0' || source[i]>'9')
				return false;
		}
		return true;
	}
	static char* copyString(char* source)
	{
		char *aux = new char[strlen(source)];
		return strcpy(aux, source);
	}

	static int stringToNumber(char* source)
	{ 
		return atoi(source);
	}
	
	static float stringToFloat(char* source)
	{
		return atof(source);
	}
};