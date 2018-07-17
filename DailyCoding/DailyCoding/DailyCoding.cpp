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

const std::string loremipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin pharetra, nisl id laoreet porta, sapien risus luctus nibh, et dapibus velit nisi ac tortor.";

int main()
{
	std::string ranges[]
	{
		"01-25",
		"26-50"
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
		"#28\tAlphabet Cipher"
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
				switch (input[1])
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
				case 15: Packet_Assembler(); break;
				case 16: Consecutive_Distance_Rating(); break;
				case 17: Adding_Calculator(); break;
				case 18: Repeating_Numbers(); break;
				case 19: FizzBuzz(); break;
				case 20: Date_Checker(); break;
				case 21: DiceGame(); break;
				case 22: BarcodeChecker(); break;
				case 23: MozartsMusicalDice(); break;
				case 24: LightRoom();
				default:break;
				};
			} while (input[1] != (sizeof(challenges1to25) / sizeof(*challenges1to25)));
		}; break;
		case 1: {
			do
			{
				input[1] = simplemenu(challenges26to50, "Pick challange solution");
				switch (input[1])
				{
				case 0: Cryptarithmetic_Solver(); break;
				case 1: BowlingFramesDisplay(); break;
				case 2: AlphabetCipher(); break;
				default:break;
				};
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