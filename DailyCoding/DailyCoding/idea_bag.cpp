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
		<< sqrt(pow(abs(cities[0].lattitude - cities[1].lattitude), 2) + 
		        pow(abs(cities[0].longitude - cities[1].longitude), 2)) << " units.";

	return 0;
	//date of creation: 13.09.2017
};

int Happy_Numbers(){
	unsigned int num, temp, iteration;
	for (int i = 0; i < 8; i++)	{
		iteration = 0;
		temp = num = random();
		while (1!=num && iteration<=100) {
			num = (pow((num / 100),2) + 
				   pow((num / 10) ,2) + 
				   pow((num % 10) ,2));
			iteration++;
		};
		if (100 == iteration) { i--; continue; };
		std::cout << "\nHappy number #" << i+1 << ": " << temp;
	};
	return EXIT_SUCCESS;
	//date of creation: 14.09.2017
};

int Coin_Flipper() {
	unsigned int flips = random();
	unsigned int heads, tails;
	heads = tails = 0;
	std::cout << "\nStatistics for flipping coin " << flips << " time/s :\n";
	
	for (unsigned int  flip = 1; flip <= flips; flip++)	{
		if (0 == random(0, 1))	{ heads++; std::cout << "Head\t"; }
		else					{ tails++; std::cout << "Tail\t"; };
		if (flip % 10 == 0) std::cout << "\n";
	};
	std::cout << "\nHeads: " << heads << "(" << (heads*100)/flips << "%), Tails: " << tails << "(" << (tails*100)/flips << "%).";
	return EXIT_SUCCESS;
	//date of creation: 15.09.2017
};

int Fibonacci() {
	int number = random();
	std::cout << "Fibonacci sequence of " << number << ":\n";
	for (size_t i = 1; i <= number; i++, i+=i) { std::cout << ' ' << i; };
	return EXIT_SUCCESS;
	//date of creation: 16.09.2017
};