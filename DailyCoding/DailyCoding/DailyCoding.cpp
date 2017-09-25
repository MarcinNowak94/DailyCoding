// Sources:
// https://coderbyte.com/challenges
// https://www.reddit.com/r/dailyprogrammer/
// https://play.google.com/store/apps/details?id=com.alansa.ideabag
// https://play.google.com/store/apps/details?id=com.alansa.ideabag2


#include "stdafx.h"
#include "simplemenu.h"
#include <string>
#include "coderbyte.h"
#include "idea_bag.h"
#include "dailyprogrammer.h"

const std::string loremipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin pharetra, nisl id laoreet porta, sapien risus luctus nibh, et dapibus velit nisi ac tortor.";

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
		"Day#6\tSimple Symbols",
		"Day#7\tChecknums",
		"Day#8\tTime convert",
		"Day#9\tAlphabet soup",
		"Day#11\tDistance between two cities",
		"Day#12\tHappy numbers",
		"Day#13\tCoin flipper",
		"Day#14\tFibonacci sequence",
		"Day#16\tTalking clock",
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
		case 7: CheckNums(); break;
		case 8: TimeConvert(); break;
		case 9: AlphabetSoup(); break;
		case 10: Distance_between_two_cities(); break;
		case 11: Happy_Numbers(); break;
		case 12: Coin_Flipper(); break;
		case 13: Fibonacci(); break;
		case 14: Talking_Clock(); break;
		default:break;
		};
	} while (input != (sizeof(challenges) / sizeof(*challenges)));
	return 0;
	std::cout << "\n\a\tFarewell!\n"
		<< "Press any key to exit...";
	_getch();
	//date of creation: 03.09.2017
}

//TODO: Continue practicing and developping programming skills
//Created by: Marcin Nowak