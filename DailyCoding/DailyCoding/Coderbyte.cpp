#include "stdafx.h"
#include "coderbyte.h"
#include "helper_functions.h"


int FirstReverse()
{
	std::string teststring = "Hello World and Coders";
	std::string reversedstring{};
	std::cout << teststring.length();
	for (int i = teststring.length() - 1; i >= 0; reversedstring.push_back(teststring.at(i--)));
	std::cout << "\n'" << teststring << "' reversed is '" << reversedstring << "'\n";
	_getch();
	return 0;

	//date of creation: 03.09.2017
	//https://coderbyte.com/language/First%20Reverse
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
	//https://coderbyte.com/language/First%20Factorial

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
		while (sen.at(i) != ' ' && isalnum(sen.at(i)))
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
	//https://coderbyte.com/language/Longest%20Word
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
			if (isvovel(input.at(i)) && islower(input.at(i))) input.at(i) = toupper(input.at(i));
		};
	};
	std::cout << input;
	_getch();
	return 0;
	//date of creation: 06.09.2017
	//https://coderbyte.com/language/Letter%20Changes
}

int SimpleAdding()
{
	std::cout << "Input real number:";
	unsigned int input, sum = 0;
	std::cin >> input;
	for (int i = input; i > 0; i--)
	{
		sum += i;
	};
	std::cout << "Sum = " << sum;
	_getch();
	return 0;
	//date of creation: 07.09.2017
	//https://coderbyte.com/language/Simple%20Adding
};

int LetterCapitalize()
{
	std::string str{};	// = loremipsum;
	std::cout << "Input text: ";
	getline(std::cin, str);
	for (int i = 0; i<str.length(); i++)
	{
		if (isalpha(str.at(i))) str.at(i) = toupper(str.at(i));
		while (' ' != str.at(i) && i<(str.length() - 1))	i++;
	};
	std::cout << "Output text:\n" << str;
	_getch();
	return 0;
	//date of creation: 07.09.2017
	//https://coderbyte.com/language/Letter%20Capitalize
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
			else { state = false; break; };
		};
	};
	if (true == state) { str = "true"; }
	else str = "false";
	std::cout << str;
	_getch();
	return 0;
	//date of creation: 08.09.2017
	//https://coderbyte.com/language/Simple%20Symbols
};

int chknms(int & num1, int & num2)
{
	if (num1 > num2) return false;
	if (num1 == num2) return -1;
	return true;

};
int CheckNums()
{
	int number1 = random();
	int number2 = random();
	std::cout << "Number1=" << number1 << ", Number2=" << number2 << ". Is Number1<Number2 ? " << chknms(number1, number2);
	_getch();
	return 0;
	//date of creation: 09.09.2017
	//https://coderbyte.com/language/Check%20Nums
};

int TimeConvert()
{
	int num = random(1, 3600);
	int hrs = 0;
	std::cout << num << "=";
	while (num >= 60) { num -= 60; hrs++; };
	std::cout << hrs << ":" << num;
	_getch();
	return 0;
	//date of creation: 10.09.2017
	//https://coderbyte.com/language/Time%20Convert
};

int AlphabetSoup()
{
	char helper = ' ';
	std::string str;
	std::cout << "Input word: ";
	getline(std::cin, str);
	unsigned short move;
	do
	{
		move = 0;
		for (int i = 0; i<str.length() - 1; i++)
		{
			if ((tolower(str.at(i))) >(tolower(str.at(i + 1))))
			{
				helper = str.at(i);
				str.at(i) = str.at(i + 1);
				str.at(i + 1) = helper;
				move++;
			};
		};
	} while (0 != move);
	std::cout << str;
	_getch();
	return 0;
	//date of creation: 11.09.2017
	//https://coderbyte.com/language/Alphabet%20Soup
}