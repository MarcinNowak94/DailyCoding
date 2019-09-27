#include "stdafx.h"
#include "other.h"
#include "Helper_functions.h"
#include <iomanip>	//for displaying leading 0

int FizzBuzz() {
	const int max = random(100, 150);

	std::cout << "FizzBuzz game results for numbers 1 up to " << max <<"(picked at random):\n";
	for (int number = 1; number < max; number++){
		if (number % 15 == 0)	{ std::cout << number << ":\tFizzBuzz\n"; continue; };
		if (number % 5  == 0)	{ std::cout << number << ":\tBuzz\n";	  continue; };
		if (number % 3  == 0)	{ std::cout << number << ":\tFizz\n";     continue; };
		std::cout << number << "\n";
	};
	return EXIT_SUCCESS;
};

bool isValidDate(const int & day, const int & month, const int & year) {
	//checking basic validity
	if ((day < 1 || day>31) || (month < 1 || month>12) || (year < 2001 || year>2099)) return false;
	
	//assessing length of month in given year
	int monthlength[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) monthlength[1]++;
	
	if (!(day <= monthlength[month - 1])) return false;
	return true;
};
int Date_Checker() {
	char exit = 'y';
	do	{
		std::cout << "Input date from years 2001-2099 to check:\n";
		int day,month, year;
		day = month = year = 0;
		
		std::cout << "input as dd mm yyyy: ";
		std::cin >> day;
		std::cin >> month;
		std::cin >> year;
		std::cout << "Checking if date " << day << "-" << month << "-" << year << "(dd-mm-yyyy) is valid: " << isValidDate(day, month, year) << "\n";

		std::cout << "Check another date ? Y/N: ";
		exit = _getch();
	} while (exit =='y' && exit =='Y');
	return EXIT_SUCCESS;
};

int DiceGame(){
	/*Specified rules:
	-2 players: first & second
	-5 rounds, order of players: first-second-first etc.
	-player first always begins the game
	-each round player gathers penalty points as specified below
	-players begin with 0 points, player with last amount of points wins

	-each turn player rolls two six faced dice simultaneously max 10 times

	Rulebook:
	-if in first roll player rolls either 7 or 11 he wins the round
	-if in first roll player rolls either 2 or 12 he loses the round and recieves max penalty
	-if players rolls 5(sum of faces) he wins the round
	-if player rolls sum of faces other than specified he gets equal to rolled amount/roll number in this round

	result: display amount of points each player recieved and winner.*/
	
	const int roundlength = 10,
			  gamelength = 5,
			  players = 2;
	double	player[players] = {};
	int	turnsleft = gamelength,
		diceroll = 0,
		dice1 = 0,
		dice2 = 0;
	
	while (0<turnsleft){
		for (int activeplayer = 0; activeplayer < players; activeplayer++) {
			for (int roll = 1; roll <= roundlength; roll++) {
				dice1 = random(1, 6);
				dice2 = random(1, 6);
				if (1 == roll && (7 == dice1 + dice2 || 11 == dice1 + dice2 )) break;
				if (1 == roll && (2 == dice1 + dice2 || 12 == dice1 + dice2 ))	{
					for (int k = 1; k <= roundlength; k++) { player[activeplayer] += (12 / k + 1); };
					break;
				};
				if (dice1 + dice2 == 5) break;
				player[activeplayer] += (dice1 + dice2 / roll);
			};
		};
		--turnsleft;
	};

	std::cout << "\n\aEnd of match.\nFinal results:\t First: " << player[0] << ".\tSecond: " << player[1] << ".\nWinner: ";
	if (player[0] < player[1]) { std::cout << "First.\n"; }
	else { std::cout << "Second.\n"; };

	return EXIT_SUCCESS;
};

enum codetype {EAN_8=0, EAN_13=1};
std::string CheckEAN(std::string barcode, const int &type) {
	int odd, even, sum, checksum, possiblechecksum;
		odd= even= sum= checksum= possiblechecksum = 0;
	int numberoffset = '0';	//ofset for numbers in ascii table	
	if (type==EAN_8) {
		if (barcode.length() < 6) return "too short for EAN-8";
		//checksum = barcode.at(7)-numberoffset;
		//possiblechecksum = barcode.at(6) - numberoffset;		//checksum if 0 is omitted
		for (int i = 7; i >=0 ; i--)
		{
			if (i % 2 != 0) { odd += (barcode.at(i) - numberoffset);} 
			else even += (barcode.at(i) - numberoffset);
		};
		if ((10-((3 * odd + even)% 10))%10==0) {return barcode.substr(0, 8);};
		if ((10 - ((3 * even + odd) % 10)) % 10 == 0) { return '0'+barcode.substr(0, 7); };
		return ("is not valid EAN-8\a");
	};
	if (type == EAN_13)	{
		if (barcode.length() <  12) return ("is too short for EAN-13");
		if (barcode.length() == 12) { /*std::cout << "Warning! Barcode shorter than 13 charcters (length= " << barcode.length() << ")Adding omitted 0\n";*/ barcode = '0' + barcode;};
		//checksum = barcode.at(12) - numberoffset;
		//possiblechecksum = barcode.at(11) - numberoffset;		//checksum if 0 is omitted
		for (int i = 12; i >= 0; i--)
		{
			if (i % 2 != 0) { odd += (barcode.at(i) - numberoffset); }
			else even += (barcode.at(i) - numberoffset);
		};
		if ((10 - ((3 * odd + even) % 10)) % 10 == 0) { return barcode.substr(0, 12); };
		if ((10 - ((3 * even + odd) % 10)) % 10 == 0) { return '0' + barcode.substr(0, 12); };
		return("is not valid EAN-13\a");
	};
	return( "Not defined!\a");
};
int BarcodeChecker()
{
	std::string barcodes[] = { "69207020772112",	//code 692070207721 with addon 12  
								"075678164125" };	//scanner can sometimes ommit predecating 0, real barcode: 0075678164125
	for each (auto barcode in barcodes)
	{
		std::cout << "Barcode (" << barcode << ") EAN-8  code " << CheckEAN(barcode, EAN_8)  << ".\n";
		std::cout << "Barcode (" << barcode << ") EAN-13 code " << CheckEAN(barcode, EAN_13) << ".\n";
	};
	return EXIT_SUCCESS;
	//https://pl.wikipedia.org/wiki/EAN
	//http://barcode-coder.com/en/ean-13-specification-102.html
};