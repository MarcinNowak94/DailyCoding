// Sources:
// https://coderbyte.com/challenges
// https://www.reddit.com/r/dailyprogrammer/
//

#include "stdafx.h"
#include "simplemenu.h"
#include <string>

//helper functions
template<class T>
T random(T Min, T Max)
{
	std::random_device rd;	//random number
	std::mt19937 Random(rd()); //using random number as seed for generator
	std::uniform_int_distribution<T> Range(Min, Max); //defining range of random numbers
	return Range(Random);
	//date of creation: 03.09.2017
	//Created by: Marcin Nowak
};

//
int FirstReverse();					//https://coderbyte.com/language/First%20Reverse
int FirstFactorial();				//https://coderbyte.com/language/First%20Factorial

int main()
{
	std::string challenges[]
	{
		"Day#1\tFirst Reverse",
		"Day#2\tFirst Factorial",
		"EXIT"
	};
	int input = 0;
	do
	{
		input = simplemenu(challenges);
		switch (input)
		{
		case 0: input = FirstReverse(); break;
		case 1: input = FirstFactorial(); break;
		default:break;
		};
	} while (input != (sizeof(challenges) / sizeof(*challenges))-1);
	std::cout << "\n\a\tFarewell!\n"
		<< "Press any key to exit...";
	_getch();
	return 0;
	//date of creation: 03.09.2017
	//Created by: Marcin Nowak
};

int FirstReverse()
{
	std::string teststring = "Hello World and Coders";
	std::string reversedstring{};
	std::cout << teststring.length();
	for (int i = teststring.length()-1; i >= 0; reversedstring.push_back(teststring.at(i--)));
	std::cout <<"\n'"<< teststring << "' reversed is '" << reversedstring <<"'\n";
	_getch();
	return 0;

	//date of creation: 03.09.2017
	//Created by: Marcin Nowak
};

int FirstFactorial(int num)
{
	if (num == 0) return 1;
	else return (FirstFactorial(num - 1)*num);
}
int FirstFactorial()
{
	int minimal = 3;
	int maximal = 15;
	int rndnumber = random(minimal, maximal);
	std::cout << "Factorial of " << rndnumber << " is " << FirstFactorial(rndnumber) << ".\n";
	_getch();
	return 0;
	//date of creation: 04.09.2017
	//Created by: Marcin Nowak
};

//TODO: Continue practicing and developping programming skills