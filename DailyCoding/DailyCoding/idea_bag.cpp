#include "stdafx.h"
#include "idea_bag.h"
#include "helper_functions.h"

int Distance_between_two_cities(){
	struct city {
		std::string name;
		int lattitude;
		int longitude;
	};
	city cities[] = { { "City1", random(-90,90), random(-180,180) },
					  { "City2", random(-90,90), random(-180,180) } };
	
	std::cout << "\n\nDistance between :\n"
		<< cities[0].name << "(" << cities[0].lattitude << " lat., " << cities[0].longitude << "lon.) and \n"
		<< cities[1].name << "(" << cities[1].lattitude << " lat., " << cities[1].longitude << "lon.) is "
		<< sqrt((abs(cities[0].lattitude - cities[1].lattitude))*(abs(cities[0].lattitude - cities[1].lattitude)) + 
		        (abs(cities[0].longitude - cities[1].longitude))*(abs(cities[0].longitude - cities[1].longitude))) << " units.";

	return 0;
	//date of creation: 13.09.2017
};

int Happy_Numbers()
{
	unsigned int num, temp, iterations;
	for (int i = 0; i < 8; i++)
	{
		iterations = 0;
		num = random();
		temp = num;
		while (1!=num && iterations<=100)
		{
			num = (((num/100)*(num/100)) + (num / 10)*(num / 10)) + ((num % 10)*(num % 10));
			iterations++;
		};
		if (100 == iterations) { i--; continue; };
		std::cout << "\nHappy number #" << i+1 << ": " << temp;
	};
	return 0;
	//date of creation: 14.09.2017
};

int Coin_Flipper()
{
	unsigned int amount_of_flips = random();
	std::cout << "\nStatistics for flipping coin " << amount_of_flips << " time/s :\n";
	unsigned int heads, tails;
	heads = tails = 0;
	for (unsigned int  i = 1; i <= amount_of_flips; i++)
	{
		if (0 == random(0, 1)) { heads++; std::cout << "Head\t"; }
		else { tails++; std::cout << "Tail\t"; };
		if (i % 10 == 0) std::cout << "\n";
	};
	std::cout << "\nHeads: " << heads << "(" << (heads*100)/amount_of_flips << "%), Tails: " << tails << "(" << (tails*100)/amount_of_flips << "%).";
	return 0;
	//date of creation: 15.09.2017
};

int Fibonacci()
{
	int number = random();
	std::cout << "Fibonacci sequence to " << number << ":\n";
	for (size_t i = 1; i <= number; i++, i+=i)
	{
		std::cout << ' ' << i;
	};
	return 0;
	//date of creation: 16.09.2017
};