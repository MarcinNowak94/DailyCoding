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