#include "stdafx.h"
#include "Helper_functions.h"
//helper functions

bool isvovel(const char & character)
{
	const char vovels[]{ 'a', 'e', 'i', 'o', 'u' };
	for (int i = 0; i < (sizeof(vovels) / sizeof(*vovels)); i++)
	{
		if (character == vovels[i]) return true;
	};
	return false;
	//date of creation: 06.09.2017
};