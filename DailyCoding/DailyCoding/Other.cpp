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