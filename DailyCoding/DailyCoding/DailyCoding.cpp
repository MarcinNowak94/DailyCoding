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
	std::string challenges[]
	{
		"Day#1\tFirst Reverse",
		"Day#2\tFirst Factorial",
		"Day#3\tLongest word in sentence",
		"Day#4\tLetter changes",
		"Day#5\tSimple adding",
		"Day#6\tLetter captitalize",
		"Day#7\tSimple Symbols",
		"Day#8\tChecknums",
		"Day#9\tTime convert",
		"Day#10\tAlphabet soup",
		"Day#11\tDistance between two cities",
		"Day#12\tHappy numbers",
		"Day#13\tCoin flipper",
		"Day#14\tFibonacci sequence",
		"Day#15\tTalking clock",
		"Day#16\tPacket Assembler",
		"Day#17\tSequences",
		"Day#18\tAdding Calculator",
		"Day#19\tRepeating Numbers (////TODO)",
		"Day#20\tFizzBuzz",
		"Day#21\tDateChecker",
		"Day#22\tDicegame",
		"Day#23\tBarcodeChecker"
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
		case 15: Packet_Assembler(); break;
		case 16: Consecutive_Distance_Rating(); break;
		case 17: Adding_Calculator(); break;
		case 18: Repeating_Numbers(); break;
		case 19: FizzBuzz(); break;
		case 20: Date_Checker(); break;
		case 21: DiceGame(); break;
		case 22: BarcodeChecker(); break;		//TODO: FIX
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