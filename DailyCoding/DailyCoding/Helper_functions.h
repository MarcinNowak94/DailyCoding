#include <random>
#include <chrono>

#pragma once
#ifndef ISVOVEL_H
#define ISVOVEL_H

bool isvovel(const char & character);

#endif // !ISVOVEL_H

#ifndef RANDOM_H
#define RANDOM_H

template<class T=int>
T random(T Min = 1, T Max = 100)
{
	std::random_device rd;	//random number
	std::mt19937 Random(rd()); //using random number as seed for generator
	std::uniform_int_distribution<T> Range(Min, Max); //defining range of random numbers
	return Range(Random);
	//date of creation: 03.09.2017
	//Created by: Marcin Nowak
};

#endif // !RANDOM_H

#ifndef ABSOULTE_H
#define ABSOLUTE_h

template<class T=int>
inline T Absolute(T number) { return number > 0 ? number : -number; };

#endif

#ifndef SPEAK_H
#define SPEAK_H

int speak(const std::wstring & text);

#endif // !SPEAK_H
#ifndef TOSPEECH_H
#define TOSPEECH_H

//Temporary(?) solution to template problem
//void tospeech(char* & text)
//{
//	std::wstring sapiinput{};
//	for (int letter = 0; text[letter] != '\0'; letter++) { sapiinput += (wchar_t)text[letter]; };
//	speak(sapiinput);
//};

template <class T>
void tospeech(T& text)
{
	//cast any text input to wstring
	std::wstring sapiinput = L"No data was provided!";
	if (typeid(text) == typeid(std::string)) { speak(std::wstring(text.begin(), text.end())); };	//if text is char* this line produces error - need to fix this
	/*if (typeid(text) == typeid(char*)) 
	{
		std::cout << "Passed parameter is char*, this part of code should not work - there is another function specialisation for this. THIS IS AN ERROR!\n";
	};*/
};


#endif // !TOSPEECH_H

#ifndef TIMER_H
#define TIMIER_H
struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	};
	~Timer()
	{
		duration = std::chrono::high_resolution_clock::now() - start;
		std::cout << "\nExecution time:\t"<< duration.count()*1000.0f << " ms";
	};
	//Credit to Yan Chernikov:	https://www.youtube.com/watch?v=oEx5vGNFrLk
};
#endif // !TIMER_H