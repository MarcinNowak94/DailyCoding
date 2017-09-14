#include "stdafx.h"
#include "idea_bag.h"
#include "helper_functions.h"

int Distance_between_two_cities()
{
	struct city
	{
		std::string name;
		int lattitude;
		int longitude;
	};
	city City1{ "City1", random(-90,90), random(-180,180) };
	city City2{ "City2", random(-90,90), random(-180,180) };
	std::cout << "Distance between :\n" << City1.name << "(" << City1.lattitude << " lat., " << City1.longitude << "lon.) and \n"
		<< City2.name << "(" << City2.lattitude << " lat., " << City2.longitude << "lon.) is "
		<< sqrt((abs(City1.lattitude - City2.lattitude))*(abs(City1.lattitude - City2.lattitude)) + (abs(City1.longitude - City2.longitude))*(abs(City1.longitude - City2.longitude))) << " units.";
	_getch();
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
	_getch();
	return 0;
	//date of creation: 14.09.2017
};