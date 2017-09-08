// Sources:
// https://coderbyte.com/challenges
// https://www.reddit.com/r/dailyprogrammer/
//

#include "stdafx.h"
#include "simplemenu.h"
#include <string>

const std::string loremipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin pharetra, nisl id laoreet porta, sapien risus luctus nibh, et dapibus velit nisi ac tortor.";

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

int FirstReverse();					//https://coderbyte.com/language/First%20Reverse
int FirstFactorial();				//https://coderbyte.com/language/First%20Factorial
int LongestWord();					//https://coderbyte.com/language/Longest%20Word
int LetterChanges();				//https://coderbyte.com/language/Letter%20Changes
int SimpleAdding();					//https://coderbyte.com/language/Simple%20Adding
int LetterCapitalize();				//https://coderbyte.com/language/Letter%20Capitalize
int SimpleSymbols();				//https://coderbyte.com/language/Simple%20Symbols

int main()
{
	std::string challenges[]
	{
		"Day#1\tFirst Reverse",
		"Day#2\tFirst Factorial",
		"Day#3\tLongest word in sentence",
		"Day#4\tLetter changes",
		"Day#5\tSimple adding",
		"Day#5\tLetter captitalize",
		"Day#6\tSimpleSymbols"
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
		case 4: SimpleAdding(); break;
		case 5: LetterCapitalize(); break;
		case 6: SimpleSymbols(); break;
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
	//date of creation: 06.09.2017
}

int SimpleAdding()
{
	std::cout << "Input real number:";
	unsigned int input, sum=0;
	std::cin >> input;
	for (int i = input; i > 0; i--)
	{
		sum += i;
	};
	std::cout << "Sum = " << sum;
	_getch();
	return 0;
	//date of creation: 07.09.2017
};

int LetterCapitalize() 
{
	std::string str{};	// = loremipsum;
	std::cout << "Input text: ";
	getline(std::cin, str);
	for (int i = 0; i<str.length(); i++)
	{
		if (isalpha(str.at(i))) str.at(i) = toupper(str.at(i));
		while (' '!=str.at(i) && i<(str.length()-1))	i++;
	};
	std::cout << "Output text:\n" << str;
	_getch();
	return 0;
	//date of creation: 07.09.2017
}

int SimpleSymbols()
{
	std::cout << "\nInput string, letters must be padded with + sign:";
	std::string str{};				//= "f++d+";//= "+d+=3=+s+";
	getline(std::cin, str);
	std::cout << "\nString correct?: ";
	bool state = false;
	for (int i = 0; i < str.length(); i++)
	{
		if (isalpha(str.at(i)))
		{
			if (0 == i) break;
			if ('+' == str.at(i - 1) && '+' == str.at(i + 1)) { state = true; }
			else { state = false; break;};
		};
	};
	if (true == state) { str = "true";} else str = "false";
	std::cout << str;
	_getch();
	return 0;
	//date of creation: 08.09.2017
};

//TODO: Continue practicing and developping programming skills
//Created by: Marcin Nowak