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

bool isValidDate(const int & day, const int & month, const int & year)
{
	//checking basic validity
	if ((day < 1 || day>31) || (month < 1 || month>12) || (year < 2001 || year>2099)) return false;
	//assessing length of month in given year
	int monthlength[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) monthlength[1]++;
	if (!(day <= monthlength[month - 1])) return false;
	return true;
};
int Date_Checker()
{
	char exit = 'y';
	do
	{
		std::cout << "Input date from years 2001-2099 to check:\n";
		//ensuring parameters are correct
		int day,month, year;
		day = month = year = 0;
		/*std::cout << "Day: ";
		std::cin >> day;
		std::cout << "Month: ";
		std::cin >> month;
		std::cout << "Year: ";
		std::cin >> year;*/
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

int DiceGame()
{
	double first=0, second=0;
	int gamelength = 5, roundlength = 10, diceroll = 0, dice1 = 0, dice2 = 1;

	for (int i = 1; i < gamelength+1; i++)
	{
		//first players round
		for (int j = 1; j < roundlength+1; j++)
		{
			dice1 = random(1, 6);
			dice2 = random(1, 6);
			if (j==1 && (dice1 + dice2 == 7 || dice1 + dice2 == 11)) break;
			if (j==1 && (dice1 + dice2 == 2 || dice1 + dice2 == 12)) 
			{
				for (int k = 1; k < roundlength+1; k++)	{first += (12 / k+1);};
				break;
			};
			if (dice1 + dice2 == 5) break;
			first += (dice1 + dice2 / j);
		};
		//second players round
		for (int j = 1; j < roundlength+1; j++)
		{
			dice1 = random(1, 6);
			dice2 = random(1, 6);
			if (j == 1 && (dice1 + dice2 == 7 || dice1 + dice2 == 11)) break;
			if (j == 1 && (dice1 + dice2 == 2 || dice1 + dice2 == 12))
			{
				for (int k = 1; k < roundlength+1; k++)	{second += (12 / k);};
				break;
			};
			if (dice1 + dice2 == 5) break;
			second += (dice1 + dice2 / j);
		};
	};
	std::cout << "\n\aEnd of match.\nFinal results:\t First: " << first << ".\tSecond: " << second << ".\nWinner: ";
	if (first < second) { std::cout << "First.\n"; }
	else { std::cout << "Second.\n"; };

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

	result: display amount of points each player recieved and winner.
	*/
	std::cout << "\aPress any key to continue...";
	_getch();
	return EXIT_SUCCESS;
}

enum codetype {EAN_8=1, EAN_13=2};
int CheckEAN(std::string barcode, int type)
{
	
	std::cout << barcode << " length: " << barcode.length() << ", ean-8? " << (type == EAN_8) << ", EAN-13? " << (type == EAN_13) << ".\n";
	if (type==EAN_8)
	{
		int checksum = std::stoi(barcode.substr(8,1));
		int possiblechecksum = std::stoi(barcode.substr(7,1));
		std::cout << "checksum= " << checksum << ", possibly=" << possiblechecksum << "\n";
		int sum = 0;
		for (int i = 7; i > 0; i--)
		{
			std::cout << "number " << barcode.substr(i, 1);
			if (i % 2 == 0) { sum += std::stoi(barcode.substr(i, 1)) * 3; std::cout << "sum=" << sum << "\n"; continue; }
			else { sum += std::stoi(barcode.substr(i, 1)); std::cout << "sum=" << sum << "\n"; continue; };
		};
		if ((checksum + (sum % 10)) % 10 == 10) { return std::stoi(barcode.substr(0, 8)); } else 				//if EAN-8 code is not right check one position earlier (possibly omitted 0)
		{
			int sum = 0;
			for (int i = 6; i > 0; i--)
			{
				std::cout << "number " << barcode.substr(i, 1);
				if (i % 2 != 0) { sum += std::stoi(barcode.substr(i, 1)) * 3; std::cout << "sum=" << sum << "\n"; continue; }
				else { sum += std::stoi(barcode.substr(i, 1)); std::cout << "sum=" << sum << "\n"; continue; };
			};
		};
		if ((possiblechecksum + (sum % 10)) % 10 != 10) { std::cout << "Barcode " << barcode << " is not valid EAN-8\a"; return EXIT_FAILURE; }
		else { return std::stoi('0'+barcode.substr(0, 7)); };		//returning valid EAN-8 with omitted 0
	};
	if (type == EAN_13)
	{
		int checksum = std::stoi(barcode.substr(13, 1));
		int possiblechecksum = std::stoi(barcode.substr(12, 1));
		std::cout << "checksum= " << checksum << ", possibly=" << possiblechecksum << "\n";
		int sum = 0;
		for (int i = 12; i > 0; i--)
		{
			std::cout << "number " << barcode.substr(i, 1);
			if (i % 2 == 0) { sum += std::stoi(barcode.substr(i, 1)) * 3; std::cout << "sum=" << sum << "\n"; continue; }
			else { sum += std::stoi(barcode.substr(i, 1)); std::cout << "sum=" << sum << "\n"; continue; };
		};
		if ((checksum + (sum % 10)) % 10 == 10) { return std::stoi(barcode.substr(0, 13)); }
		else 				//if EAN-13 code is not right check one position earlier (possibly omitted 0)
		{
			int sum = 0;
			for (int i = 11; i > 0; i--)
			{
				std::cout << "number " << barcode.substr(i, 1);
				if (i % 2 != 0) { sum += std::stoi(barcode.substr(i, 1)) * 3; std::cout << "sum=" << sum << "\n"; continue; }
				else { sum += std::stoi(barcode.substr(i, 1)); std::cout << "sum=" << sum << "\n"; continue; };
			};
		};
		if ((possiblechecksum + (sum % 10)) % 10 != 10) { std::cout << "Barcode " << barcode << " is not valid EAN-13\a"; return EXIT_FAILURE; }
		else { return std::stoi('0' + barcode.substr(0, 11)); };		//returning valid EAN-8 with omitted 0
	}
	std::cout << "Undefined!\a\n";
	return EXIT_FAILURE;
	//all eventual errors in input should be signaled with exceptions
}
int BarcodeChecker()
{
	
	std::string barcode1 = "69207020772112";	//code 692070207721 with addon 12
	std::string barcode2 = "075678164125";		//scanner can sometimes ommit predecating 0, real barcode: 0075678164125
	std::cout << "\nBarcode1 (" << barcode1 << ") EAN-8 code is " << CheckEAN(barcode1, 1) << ".\n";
	_getch();
	std::cout << "\nBarcode1 (" << barcode1 << ") EAN-13 code is " << CheckEAN(barcode1, 2) << ".\n";
	_getch();
	std::cout << "\nBarcode2 (" << barcode2 << ") EAN-8 code is " << CheckEAN(barcode1, 1) << ".\n";
	_getch();
	std::cout << "\nBarcode2 (" << barcode2 << ") EAN-13 code is " << CheckEAN(barcode1, 2) << ".\n";
	std::cout << "Press any key to continue...\a";
	_getch();
	return EXIT_SUCCESS;
	//https://pl.wikipedia.org/wiki/EAN
	//http://barcode-coder.com/en/ean-13-specification-102.html
}