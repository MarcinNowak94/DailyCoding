#include <random>

#pragma once
#ifndef ISVOVEL_H
#define ISVOVEL_H

bool isvovel(const char & character);

#endif // !ISVOVEL_H

#ifndef RANDOM_H
#define RANDOM_H

template<class T=int>
T random(T Min = 1, T Max = 100)
{
	std::random_device rd;	//random number
	std::mt19937 Random(rd()); //using random number as seed for generator
	std::uniform_int_distribution<T> Range(Min, Max); //defining range of random numbers
	return Range(Random);
	//date of creation: 03.09.2017
	//Created by: Marcin Nowak
};

#endif // !RANDOM_H

