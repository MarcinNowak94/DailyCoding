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
#include "other.h"
#include "Helper_functions.h"

const std::string loremipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin pharetra, nisl id laoreet porta, sapien risus luctus nibh, et dapibus velit nisi ac tortor.";

int run(int(*function)()) {
	int retval{};
	{ Timer timer; 
	retval=function(); }; 
	std::cout << "\nPress any key to continue...\n\a";
	_getch();
	return retval;
};

int main()
{
	std::string ranges[]{
		"01-25",
		"26-50"
	};

	int (*function_batch1[])() = {
		&FirstReverse, 
		&FirstFactorial, 
		&LongestWord,
		&LetterChanges,
		&SimpleAdding,
		&LetterCapitalize,
		&SimpleSymbols,
		&CheckNums,
		&TimeConvert,
		&AlphabetSoup,
		&Distance_between_two_cities,
		&Happy_Numbers,
		&Coin_Flipper,
		&Fibonacci,
		&Talking_Clock,
		&Packet_Assembler,
		&Consecutive_Distance_Rating,
		&Adding_Calculator,
		&Repeating_Numbers,
		&FizzBuzz,
		&Date_Checker,
		&DiceGame,
		&BarcodeChecker,
		&MozartsMusicalDice,
		&LightRoom
		};
	int (*function_batch2[])() = {
		&Cryptarithmetic_Solver,
		&BowlingFramesDisplay,
		&AlphabetCipher,
		&ClosestAirbornePlane,
		&TallyProgram
	};

	std::string challenges1to25[]
	{
		"#1\tFirst Reverse",
		"#2\tFirst Factorial",
		"#3\tLongest word in sentence",
		"#4\tLetter changes",
		"#5\tSimple adding",
		"#6\tLetter captitalize",
		"#7\tSimple Symbols",
		"#8\tChecknums",
		"#9\tTime convert",
		"#10\tAlphabet soup",
		"#11\tDistance between two cities",
		"#12\tHappy numbers",
		"#13\tCoin flipper",
		"#14\tFibonacci sequence",
		"#15\tTalking clock",
		"#16\tPacket Assembler",
		"#17\tSequences",
		"#18\tAdding Calculator",
		"#19\tRepeating Numbers",
		"#20\tFizzBuzz",
		"#21\tDateChecker",
		"#22\tDicegame",
		"#23\tBarcodeChecker",
		"#24\tMozart's Musical Dice",
		"#25\tLight Room"
	};
	std::string challenges26to50[]
	{
		"#26\tCryptarithmetic Solver",
		"#27\tBowling Frames Display",
		"#28\tAlphabet Cipher",
		"#29\tClosest Airborne Plane << NOT READY",
		"#30\tTallyProgram"
	};
	int input[2]{};		//input for menu and submenus
	do
	{
		input[0] = simplemenu(ranges, "Pick range");
		switch (input[0])
		{
		case 0: {
			do
			{
				input[1] = simplemenu(challenges1to25, "Pick challange solution");
				if (!(input[1] < (sizeof(challenges1to25) / sizeof(*challenges1to25)))) break;
				run(function_batch1[input[1]]);
			} while (input[1] != (sizeof(challenges1to25) / sizeof(*challenges1to25)));
		}; break;
		case 1: {
			do
			{
				input[1] = simplemenu(challenges26to50, "Pick challange solution");
				if (!(input[1] < (sizeof(challenges26to50) / sizeof(*challenges26to50)))) break;
				run(function_batch2[input[1]]);
			} while (input[1] != (sizeof(challenges26to50) / sizeof(*challenges26to50)));
		}; break;
		default: break;
		};
	} while (input[0]!=(sizeof(ranges)/sizeof(*ranges)));
	std::cout << "\n\a\tFarewell!\n"
		<< "Press any key to exit...";
	_getch();
	return 0;
	//date of creation: 03.09.2017
}

//TODO: Continue practicing and developping programming skills
//Created by: Marcin Nowak	https://github.com/marcinnowak94