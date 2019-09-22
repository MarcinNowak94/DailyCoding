#include "stdafx.h"
#include "coderbyte.h"
#include "helper_functions.h"

const std::string loremipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin pharetra, nisl id laoreet porta, sapien risus luctus nibh, et dapibus velit nisi ac tortor.";

int FirstReverse(){
	std::string teststring = "Hello World and Coders";
	std::string reversedstring{};
	for (size_t i = teststring.length() - 1; i >= 0; reversedstring.push_back(teststring.at(i--)));
	std::cout << "'" << teststring << "' reversed is '" << reversedstring;
	return EXIT_SUCCESS;

	//date of creation: 03.09.2017
	//https://coderbyte.com/language/First%20Reverse
};

int FirstFactorial(int num) {
	if (num == 0) return 1;
	else return (FirstFactorial(num - 1)*num);
}
int FirstFactorial(){
	int minimal = 3;
	int maximal = 15;
	int rndnumber = random(minimal, maximal);
	std::cout << "Factorial of " << rndnumber << " is " << FirstFactorial(rndnumber) << ".";
	return EXIT_SUCCESS;

	//date of creation: 04.09.2017
	//https://coderbyte.com/language/First%20Factorial

};

int LongestWord(){
	std::string sen = loremipsum;
	std::string temp{}, longest{};
	for (int letter = 0; letter < sen.length(); letter++)	{
		temp.clear();
		while (sen.at(letter) != ' ' && isalnum(sen.at(letter))) {
			temp.push_back(sen.at(letter));
			letter++;
			if (letter >= sen.length()) break;
		};
		if (temp.length() > longest.length()) longest = temp;
	};
	std::cout << "Longest word in sentence '" << sen << "' is: " << longest;
	return EXIT_SUCCESS;

	//date of creation: 05.09.2017
	//https://coderbyte.com/language/Longest%20Word
}

int LetterChanges() {
	std::string input = loremipsum;
	for (int letter = 0; letter < input.length(); letter++)	{
		if (isalpha(input.at(letter))) {
			input.at(letter) += 1;
			if (isvovel(input.at(letter)) && islower(input.at(letter))) input.at(letter) = toupper(input.at(letter));
		};
	};
	std::cout << input;
	return EXIT_SUCCESS;

	//date of creation: 06.09.2017
	//https://coderbyte.com/language/Letter%20Changes
}

int SimpleAdding(){
	int minimal = 3;
	int maximal = 50;
	int rndnumber = random(minimal, maximal);
	unsigned int sum = 0;

	for (int i = rndnumber; i > 0; i--) sum += i;
	std::cout << "Sum of " << rndnumber << " is " << sum;
	return EXIT_SUCCESS;

	//date of creation: 07.09.2017
	//https://coderbyte.com/language/Simple%20Adding
};

int LetterCapitalize(){
	std::string str = loremipsum;
	for (int letter = 0; letter<str.length(); letter++)	{
		if (isalpha(str.at(letter))) str.at(letter) = toupper(str.at(letter));
		while (' ' != str.at(letter) && letter<(str.length() - 1))	letter++;
	};
	std::cout << "Input text:\n"
		      << loremipsum
			  << "\nOutput text:\n" 
		      << str << '\n';
	return EXIT_SUCCESS;

	//date of creation: 07.09.2017
	//https://coderbyte.com/language/Letter%20Capitalize
}

int SimpleSymbols() {
	//std::cout << "\nInput string, letters must be padded with + sign:";
	std::string str = "f++d+"; //= "+d+=3=+s+";
	std::cout << "\nString correct?: ";
	bool state = false;
	for (int letter = 0; letter < str.length(); letter++)	{
		if (isalpha(str.at(letter))) {
			if (0 == letter) break;
			if ('+' == str.at(letter - 1) && '+' == str.at(letter + 1)) { state = true; }
			else { state = false; break; };
		};
	};
	if (true == state) { str = "true"; }
	else str = "false";
	std::cout << str;
	return EXIT_SUCCESS;

	//date of creation: 08.09.2017
	//https://coderbyte.com/language/Simple%20Symbols
};

int chknms(int & num1, int & num2){
	if (num1 > num2) return false;
	if (num1 == num2) return -1;
	return true;
};
int CheckNums(){
	int number1 = random();
	int number2 = random();
	std::cout << "Number1=" << number1 << ", Number2=" << number2 << ". Is Number1<Number2 ? " << chknms(number1, number2);
	return EXIT_SUCCESS;

	//date of creation: 09.09.2017
	//https://coderbyte.com/language/Check%20Nums
};

int TimeConvert(){
	int num = random(1, 3600);
	int hrs = 0;
	std::cout << num << "=";
	while (num >= 60) { num -= 60; hrs++; };
	std::cout << hrs << ":" << num;
	return EXIT_SUCCESS;

	//date of creation: 10.09.2017
	//https://coderbyte.com/language/Time%20Convert
};

int AlphabetSoup(){
	char helper = ' ';
	std::string str = loremipsum;
	if (0==str.length()) {
		std::cout << "Provide string\a";
		return EXIT_FAILURE;
	};

	unsigned short move;
	do	{
		move = 0;
		for (int letter = 0; letter<str.length() - 1; letter++) {
			if ((tolower(str.at(letter))) >(tolower(str.at(letter + 1)))) {
				helper = str.at(letter);
				str.at(letter) = str.at(letter + 1);
				str.at(letter + 1) = helper;
				move++;
			};
		};
	} while (0 != move);
	std::cout << str;
	return EXIT_SUCCESS;
	
	//date of creation: 11.09.2017
	//https://coderbyte.com/language/Alphabet%20Soup
}