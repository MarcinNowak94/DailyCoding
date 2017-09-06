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
int LongestWord();					//https://coderbyte.com/language/Longest%20Word
int LetterChanges();				//https://coderbyte.com/language/Letter%20Changes

int main()
{
	std::string challenges[]
	{
		"Day#1\tFirst Reverse",
		"Day#2\tFirst Factorial",
		"Day#3\tLongest word in sentence",
		"Day#4\tLetter changes"
	};
	int input = 0;
	do
	{
		input = simplemenu(challenges, "Pick challange solution");
		switch (input)
		{
		case 0: FirstReverse(); break;
		case 1: FirstFactorial(); break;
		case 2: LongestWord(); break;
		case 3: LetterChanges(); break;
		default:break;
		};
	} while (input != (sizeof(challenges) / sizeof(*challenges)));
	std::cout << "\n\a\tFarewell!\n"
		<< "Press any key to exit...";
	_getch();
	return 0;
	//date of creation: 03.09.2017
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
};

int LongestWord() 
{
	/*
	Input:"fun&!! time"
	Output:"time"
	*/
	std::string sen{};//="fun&!! time";
	std::cout << "Input sentence to check: ";
	std::getline(std::cin, sen);
	std::string temp{}, longest{};
	for (int i = 0; i < sen.length(); i++)
	{
		temp.clear();
		while (sen.at(i)!=' ' && isalnum(sen.at(i)))
		{
			temp.push_back(sen.at(i));
			i++;
			if (i >= sen.length()) break;
		};
		if (temp.length() > longest.length()) longest = temp;
	};
	std::cout << "Longest word in sentence '" << sen << "' is: " << longest << "\n";
	_getch();
	return 0;
	//date of creation: 05.09.2017
}

bool isvovel(char character)
{
	const char vovels[]{ 'a', 'e', 'i', 'o', 'u' };
	for (int i = 0; i < (sizeof(vovels)/sizeof(*vovels)); i++)
	{
		if (character == vovels[i]) return true;
	};
	return false;
};
int LetterChanges()
{
	std::string input; // = "fun times!";
	std::cout << "Input phrase:";
	getline(std::cin, input);
	for (int i = 0; i < input.length(); i++)
	{
		if (isalpha(input.at(i)))
		{
			input.at(i) += 1;
			if (isvovel(input.at(i)) && islower(input.at(i))) input.at(i)=toupper(input.at(i));
		};
	};
	std::cout << input;
	_getch();
	return 0;
}

//TODO: Continue practicing and developping programming skills
//Created by: Marcin Nowak