#include "stdafx.h"
#include "other.h"
#include "Helper_functions.h"

int FizzBuzz()
{
	std::cout << "FizzBuzz game results for numbers 1 up to 100-150(picked at random):\n";
	for (int i = 1; i < random(100, 150); i++)
	{
		if (i % 15 == 0) { std::cout << i << ":\tFizzBuzz\n"; continue; };
		if (i % 5 == 0) { std::cout << i << ":\tBuzz\n"; continue; };
		if (i % 3 == 0) { std::cout << i << ":\tFizz\n"; continue; };
		std::cout << i << "\n";
	};
	std::cout << "/aPress any key to continue...";
	_getch();
	return EXIT_SUCCESS;
};