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

const int menulimit = 25;

int run(int(*function)()) {
	int retval=EXIT_FAILURE;
	{	Timer timer;
		if (nullptr == function) { 
			std::cout << "Such function does not exist yet!"
					  << "\nPress any key to continue...\n\a";
			_getch(); 
			return retval;
		};
		retval=function(); 
	};
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
	const size_t ranges_size = (sizeof(ranges) / sizeof(*ranges));
	struct Function
	{
		int(*function)() = {};
		std::string name = {};
	};

	//Add functions here 
	Function functions[][menulimit] = {
		{
		 {&FirstReverse,				"#1\tFirst Reverse"},
		 {&FirstFactorial,				"#2\tFirst Factorial"},
		 {&LongestWord,					"#3\tLongest word in sentence"},
		 {&LetterChanges,				"#4\tLetter changes"},
		 {&SimpleAdding,				"#5\tSimple adding"},
		 {&LetterCapitalize,			"#6\tLetter captitalize"},
		 {&SimpleSymbols,				"#7\tSimple Symbols"},
		 {&CheckNums,					"#8\tChecknums"},
		 {&TimeConvert,					"#9\tTime convert"},
		 {&AlphabetSoup,				"#10\tAlphabet soup"},
		 {&Distance_between_two_cities, "#11\tDistance between two cities"},
		 {&Happy_Numbers,				"#12\tHappy numbers"},
		 {&Coin_Flipper,				"#13\tCoin flipper"},
		 {&Fibonacci,					"#14\tFibonacci sequence"},
		 {&Talking_Clock,				"#15\tTalking clock"},
		 {&Packet_Assembler,			"#16\tPacket Assembler"},
		 {&Consecutive_Distance_Rating, "#17\tSequences"},
		 {&Adding_Calculator,			"#18\tAdding Calculator"},
		 {&Repeating_Numbers,			"#19\tRepeating Numbers"},
		 {&FizzBuzz,					"#20\tFizzBuzz"},
		 {&Date_Checker,				"#21\tDateChecker"},
		 {&DiceGame,					"#22\tDicegame"},
		 {&BarcodeChecker,				"#23\tBarcodeChecker"},
		 {&MozartsMusicalDice,			"#24\tMozart's Musical Dice"},
		 {&LightRoom,					"#25\tLight Room"}
		},{
		 {&Cryptarithmetic_Solver,		"#26\tCryptarithmetic Solver"},
		 {&BowlingFramesDisplay,		"#27\tBowling Frames Display"},
		 {&AlphabetCipher,				"#28\tAlphabet Cipher"},
		 {&ClosestAirbornePlane,		"#29\tClosest Airborne Plane << NOT READY"},
		 {&TallyProgram,				"#30\tTallyProgram"}
		}	
	};
	
	//Simplemenu needs string array to display options
	//This bit grabs all functions and stores it in array
	std::string challenges[ranges_size][menulimit]{};
	for (size_t range = 0; range < ranges_size; range++) {
		for (size_t function = 0; function < menulimit; function++) {
			challenges[range][function] = functions[range][function].name;
		};
	};
	
	//input for menu and submenus
	int input[2]{};

	//menu 
	do
	{
		input[0] = simplemenu(ranges, "Pick range");
		input[1] = 0;
		while((input[0] != ranges_size) && (input[1] != menulimit)) {
				input[1] = simplemenu(challenges[input[0]], "Pick challange solution");
				if (!(input[1] < menulimit)) break;							//end if user chose exit
				run(functions[input[0]][input[1]].function);
		};
	} while (input[0]!= ranges_size);
	std::cout << "\n\a\tFarewell!\n"
		<< "Press any key to exit...";
	_getch();
	return 0;
	//date of creation: 03.09.2017
}

//TODO: Continue practicing and developping programming skills
//Created by: Marcin Nowak	https://github.com/marcinnowak94