#include "stdafx.h"
#include "dailyprogrammer.h"
#include "Helper_functions.h"
#include <sstream>							//stream manipulation
#include <algorithm>
//#include "..\Includes\rapidjson\rapidjson.h"	//JSON builder and parser
//#include "..\Includes\rapidjson\document.h"
//#include "..\Includes\curl\curl.h"			//libcurl	HTTP requests

void clock(std::string time)
{
	std::string digits[] { "oh", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
	std::string decimal[] { "\b", "ten", "twenty", "thirty", "fourty", "fifty" };
	std::string suffix[] {"am", "pm"};
	std::cout << time<< ": ";
	std::string final = "It's ";
	int hours = std::stoi(time.substr(0, 2));
	int minutes = std::stoi(time.substr(3, 4));
	if (0 == hours) { final.append(digits[12]); } else final.append(digits[hours % 12]);
	final.append(" ");
	if (0 == minutes) { final.append("\b"); }
	else if (minutes > 9 && minutes < 20) { final.append(digits[minutes]); }
	else if (0 == minutes % 10) { final.append(decimal[minutes / 10]); }
	else { final.append(decimal[minutes / 10]); final.append(" "); final.append(digits[minutes % 10]); };
	final.append(" " + suffix[hours / 12] + '\n');
	std::cout << final;
	//temp - t test tospeech functionality
	char* solution;
	solution = new char[final.size()];
	/*for (size_t i = 0; i < final.length(); i++)
	{
		solution[i] = final[i];
	};*/
	//tospeech(solution);
	tospeech(final);
	return;
};
int Talking_Clock()
{
	//https://www.reddit.com/r/dailyprogrammer/comments/6jr76h/20170627_challenge_321_easy_talking_clock/
	/*
	Description
		No more hiding from your alarm clock!You've decided you want your computer to keep you updated on the time so you're never late again.A talking clock takes a 24 - hour time and translates it into words.

		Input Description
		An hour(0 - 23) followed by a colon followed by the minute(0 - 59).

		Output Description
		The time in words, using 12 - hour format followed by am or pm.

		Sample Input data
		00:00
		01 : 30
		12 : 05
		14 : 01
		20 : 29
		21 : 00

		Sample Output data
		It's twelve am
		It's one thirty am
		It's twelve oh five pm
		It's two oh one pm
		It's eight twenty nine pm
		It's nine pm
	*/
	std::string sample[] =
	{
	"00:00",
	"01:30",
	"12:05",
	"14:01",
	"20:29",
	"21:00"
	};
	for (int i = 0; i < sizeof(sample) / sizeof(sample[0]); i++) {	clock(sample[i]);	};
	std::string randomtime;
	for (size_t i = 0; i < 10; i++)
	{
		do
		{
			randomtime.clear();
			randomtime.append(std::to_string(random(0, 12)));
			randomtime.append(":");
			randomtime.append(std::to_string(random(0, 59)));
		} while (randomtime.length()<5);
		clock(randomtime);
	};	
	std::cout << "Press any key to continue...\n";
	_getch();
	return 0;
	//date of creation: 26.09.2017
};

struct packet
{
	int message_ID;			//which message this packet is a part of
	int packet_ID;			//the index of this packet in the message (zero-indexed)
	int num_of_packets;		//total number of packets in the message
	std::string message{};	//part of message
};
static std::vector<packet> message;
int Assembler(std::string incoming_packet)
{	
	packet incoming;
	size_t elementpos = 0;
	//Tokenize incoming data and assign values to packet data type
	//get message_ID
	incoming.message_ID = std::stoi(incoming_packet.substr(elementpos, incoming_packet.find_first_of(' ')));		
	if(elementpos!=incoming_packet.length()) elementpos = incoming_packet.find_first_not_of(' ', incoming_packet.find_first_of(' '));					//next non-blank character
	//get packet_ID
	incoming.packet_ID = std::stoi(incoming_packet.substr(elementpos, incoming_packet.find(' ', elementpos)));		
	if (elementpos != incoming_packet.length()) elementpos = incoming_packet.find_first_not_of(' ', incoming_packet.find(' ', elementpos));					//next non-blank character
	//get num_of_packets
	incoming.num_of_packets = std::stoi(incoming_packet.substr(elementpos, incoming_packet.find(' ', elementpos)));	
	//turn rest of string into message
	if (elementpos != incoming_packet.length()) if ((elementpos = incoming_packet.find_first_not_of(' ', incoming_packet.find(' ', elementpos))) != -1)		//next non-blank character
	{incoming.message = incoming_packet.substr(elementpos, incoming_packet.length());}
	else incoming.message = ' ';

	//storing and sorting
	if (message.size()>=1)
	{
		for (size_t i = 0; i < message.size(); i++)
		{
			if (incoming.message_ID == message.at(i).message_ID) 
			{
				if (incoming.packet_ID < message.at(i).packet_ID) { message.insert(message.begin() + i, incoming); break;}
				else if (i == message.size() - 1) { message.insert(message.begin() + i + 1, incoming); break; };
			}
			else if(incoming.message_ID<message.at(i).message_ID) { message.insert(message.begin()+i--,incoming); break;};
		};
	}
	else message.push_back(incoming);
	return 0;
};
void Display()
{
	std::cout << "\nPacket messages: \n";
	for (size_t i = 0; i < message.size(); i++)
	{
		std::cout << message[i].message_ID << '\t' << message[i].packet_ID << '\t' << message[i].message << "\n";
	};
};
int Packet_Assembler()
{
	//https://www.reddit.com/r/dailyprogrammer/comments/72ivih/20170926_challenge_333_easy_packet_assembler/
	/*
	Description
		When a message is transmitted over the internet, it is split into multiple packets, each packet is transferred individually,
		and the packets are reassembled into the original message by the receiver. Because the internet exists in the real world,
		and because the real world can be messy, packets do not always arrive in the order in which they are sent.For today's challenge,
		your program must collect packets from stdin, assemble them in the correct order, and print the completed messages to stdout.

		The point of reading from stdin is to simulate incoming packets.For the purposes of this challenge,
		assume there is a potentially unlimited number of packets.Your program should not depend on knowing how many packets there are in total.
		Simply sorting the input in its entirety would technically work, but defeats the purpose of this exercise.

	Input description
		Each line of input represents a single packet.Each line will be formatted as X Y Z some_text, where X Y and Z are positive integer
		and some_text is an arbitrary string.
		X represents the message ID(ie which message this packet is a part of).
		Y represents the packet ID(ie the index of this packet in the message) (packets are zero - indexed, so the first packet in a message will have Y = 0,
		the last packet in a message will have Y = Z - 1).
		Z represents the total number of packets in the message.

		It is guaranteed that there will be no duplicate packets or message IDs.
	
	Example input
		6220    1   10  Because he's the hero Gotham deserves, 
		6220    9   10
		5181    5   7   in time, like tears in rain.Time to die.
		6220    3   10  So we'll hunt him. 
		6220    5   10  Because he's not a hero. 
		5181    6   7
		5181    2   7   shoulder of Orion.I watched C - beams
		5181    4   7   Gate.All those moments will be lost
		6220    6   10  He's a silent guardian. 
		5181    3   7   glitter in the dark near the Tannhäuser
		6220    7   10  A watchful protector.
		5181    1   7   believe.Attack ships on fire off the
		6220    0   10  We have to chase him.
		5181    0   7   I've seen things you people wouldn't
		6220    4   10  Because he can take it.
		6220    2   10  but not the one it needs right now.
		6220    8   10  A Dark Knight.

	Example output
		5181    0   7   I've seen things you people wouldn't
		5181    1   7   believe.Attack ships on fire off the
		5181    2   7   shoulder of Orion.I watched C - beams
		5181    3   7   glitter in the dark near the Tannhäuser
		5181    4   7   Gate.All those moments will be lost
		5181    5   7   in time, like tears in rain.Time to die.
		5181    6   7
		6220    0   10  We have to chase him.
		6220    1   10  Because he's the hero Gotham deserves, 
		6220    2   10  but not the one it needs right now.
		6220    3   10  So we'll hunt him. 
		6220    4   10  Because he can take it.
		6220    5   10  Because he's not a hero. 
		6220    6   10  He's a silent guardian. 
		6220    7   10  A watchful protector.
		6220    8   10  A Dark Knight.
		6220    9   10
	*/
	std::string messages[] =
	{
		"6220    1   10  Because he's the hero Gotham deserves,",
		"6220    9   10   ",
		"5181    5   7   in time, like tears in rain.Time to die.",
		"6220    3   10  So we'll hunt him.",
		"6220    5   10  Because he's not a hero.",
		"5181    6   7    ",
		"5181    2   7   shoulder of Orion.I watched C - beams",
		"5181    4   7   Gate.All those moments will be lost",
		"6220    6   10  He's a silent guardian. ",
		"5181    3   7   glitter in the dark near the Tannhäuser",
		"6220    7   10  A watchful protector.",
		"5181    1   7   believe.Attack ships on fire off the",
		"6220    0   10  We have to chase him.",
		"5181    0   7   I've seen things you people wouldn't",
		"6220    4   10  Because he can take it.",
		"6220    2   10  but not the one it needs right now.",
		"6220    8   10  A Dark Knight.",
	};
	std::string challenge_input[] =
	{
		"7469    1   7   believe.Attack ships on fire off the",
		"9949    6   10  He's a silent guardian." ,
		"2997    9   19  Force is a pathway to many abilities some",
		"6450    2   11  is a vestige of the vox populi, now vacant, vanished.However, this valorous",
		"6450    10  11 ",
		"6450    8   11  veers most verbose, so let me simply add that it's my very good honour to meet ",
		"6450    5   11 and voracious violation of volition!The only verdict is vengeance; a vendetta",
		"9949    1   10  Because he's the hero Gotham deserves, ",
		"6450    1   11 and villain by the vicissitudes of fate.This visage, no mere veneer of vanity,",
		"2997    13  19  he did.Unfortunately, he taught his",
		"9949    8   10  A Dark Knight.",
		"1938    4   17  by the iniquities of the selfish and the",
		"1938    0   17  You read the Bible, Brett ? Well there's ",
		"2997    0   19  Did you ever hear the tragedy of Darth",
		"2997    1   19  Plagueis the Wise ? I thought not.It's not a",
		"1938    8   17  of darkness, for he is truly is brother's ",
		"2997    14  19  apprentice everything he knew, then his",
		"6450    3   11  visitation of a bygone vexation stands vivified, and has vowed to vanquish these",
		"1938    12  17  who attempt to poison and destroy my",
		"6450    9   11  you and you may call me V.",
		"7469    2   7   shoulder of Orion.I watched C - beams",
		"2997    10  19  consider to be unnatural.He became so",
		"1938    1   17  this passage I got memorized, sorta fits",
		"2997    5   19  Force to influence the midichlorians to",
		"1938    6   17  in the name of charity and good will,",
		"7469    0   7   I've seen things you people wouldn't",
		"9949    4   10  Because he can take it.",
		"6450    7   11  vindicate the vigilant and the virtuous.Verily, this vichyssoise of verbiage",
		"9949    0   10  We have to chase him.",
		"9949    7   10  A watchful protector.",
		"2997    3   19  legend.Darth Plagueis was a Dark Lord of the",
		"6450    6   11  held as a votive, not in vain, for the value and veracity of such shall one day",
		"2997    8   19  cared about from dying.The dark side of the",
		"1938    10  17  And I will strike down upon thee with",
		"1938    11  17  great vengeance and furious anger those",
		"1938    7   17  shepherds the weak through the valley",
		"1938    2   17  this occasion.Ezekiel 25:17 ? \"The path" ,
		"2997    18  19",
		"9949    9   10",
		"1938    14  17  the Lord when I lay my vengeance upon",
		"1938    15  17  thee." ,
		"1938    9   17  keeper and the finder of lost children.",
		"1938    13  17  brothers.And you will know my name is",
		"9949    2   10  but not the one it needs right now.",
		"2997    16  19  he could have others from death, but not",
		"2997    7   19  dark side that he could even keep the once he",
		"1938    5   17  tyranny of evil men.Blessed is he who,",
		"2997    17  19  himself.",
		"2997    6   19  create life...He had such a knowledge of the",
		"2997    12  19  losing his power.Which eventually, of course,",
		"7469    4   7   Gate.All those moments will be lost",
		"2997    2   19  story the Jedi would tell you.It's a Sith",
		"1938    16  17",
		"2997    4   19  Sith so powerful and so wise, he could use the",
		"1938    3   17  of the righteous man is beset on all sides",
		"2997    11  19  powerful...The only thing he was afraid of was",
		"7469    6   7 ",
		"2997    15  19  apprentice killed him in his sleep.Ironic,",
		"7469    5   7   in time, like tears in rain.Time to die.",
		"9949    3   10  So we'll hunt him. ",
		"7469    3   7   glitter in the dark near the Tannhäuser",
		"6450    4   11  venal and virulent vermin vanguarding vice and vouchsafing the violently vicious",
		"6450    0   11  Voilà!In view, a humble vaudevillian veteran, cast vicariously as both victim",		//character à is not present in current codingpage
		"9949    5   10  Because he's not a hero. "
	};
	for (size_t i = 0; i < sizeof(challenge_input)/sizeof(challenge_input[0]); i++)
	{
		Assembler(challenge_input[i]);
	};
	Display();
	message.clear();
	_getch();
	return 0;
	//date of creation: 26-28.09.2017
}

bool fill(std::istream & input, int & amount, int & length, std::vector<std::vector<int>> & tab)
{
	input >> amount;
	input >> length;
	int temp = 0;
	for (int seq = 0; seq<amount; seq++)
	{
		std::cout << "\n ";
		std::vector<int> row;
		tab.push_back(row);
		for (int num = 0; num<length; num++)
		{
			input >> temp;
			tab[seq].push_back(temp); std::cout << tab[seq][num] << "\t";
		};
	};
	return true;
};
void sequences(std::istream & input, int difference=1)
{
	int numofseq;
	int seqlen;
	std::vector<std::vector<int>> seqtab;
	int seqtotal = 0;
	int everyseq = 0;
	//parsing input
	fill(input, numofseq, seqlen, seqtab);
	std::cout << "\nSearching for sequences of " << difference << ":";
	for (int seq = 0; seq<numofseq; seq++)
	{
		for (int num = 0; num<seqlen; num++)
		{
			for (int n = num; n<seqtab[seq].size(); n++)
			{
				if (seqtab[seq][num] + difference == seqtab[seq][n] || seqtab[seq][num]-difference== seqtab[seq][n])
				{ seqtotal += (n - num);};
			};
		};
		std::cout << "\nsequence " << seq  << ": " << seqtotal;
		everyseq += seqtotal;
		seqtotal = 0;
	};
	std::cout << "\nTotal length of sequences: " << everyseq;
	return;
};
int Consecutive_Distance_Rating()
{
	//https://www.reddit.com/r/dailyprogrammer/comments/759fha/20171009_challenge_335_easy_consecutive_distance/
	/* "6 11
		31 63 53 56 96 62 73 25 54 55 64
		77 39 35 38 41 42 76 73 40 31 10
		30 63 57 87 37 31 58 83 34 76 38
		18 62 55 92 88 57 90 10 11 96 12
		26 8 7 25 52 17 45 64 11 35 12
		89 57 21 55 56 81 54 100 22 62 50"*/
	//initializing stream as test input specification
	std::istringstream str("6 11 31 63 53 56 96 62 73 25 54 55 64 77 39 35 38 41 42 76 73 40 31 10 30 63 57 87 37 31 58 83 34 76 38 18 62 55 92 88 57 90 10 11 96 12 26 8 7 25 52 17 45 64 11 35 12 89 57 21 55 56 81 54 100 22 62 50");
	std::cin.rdbuf(str.rdbuf());
	std::cout << "\nDefault version: ";
	sequences(std::cin);
	std::cout << "\n\nBonus version: ";
	std::istringstream str2("6 11 31 63 53 56 96 62 73 25 54 55 64 77 39 35 38 41 42 76 73 40 31 10 30 63 57 87 37 31 58 83 34 76 38 18 62 55 92 88 57 90 10 11 96 12 26 8 7 25 52 17 45 64 11 35 12 89 57 21 55 56 81 54 100 22 62 50");
	std::cin.rdbuf(str2.rdbuf());
	sequences(std::cin, 2);
	_getch();
	return 0;
	//date of creation: 19.10.2017
};

void calc(std::istream & procedure)
{
	int a = 0, b = 0, result = 0;
	char operation;
	procedure >> a; procedure >> operation; procedure >> b;
	std::cout << "\n" << a << " " << operation << " " << b << " =";
	switch (operation)
	{
	case '+': {std::cout << (a + b); return; }; break;
	case '-': {std::cout << (a + (-b)); return; }; break;
	case '*': 
	{
		if (0 == b) {std::cout << 0; return; };
		if (0 > b) { for (int amount = 0; amount < -b; amount++, result += a); std::cout << -result; return; };
		for (int amount = 0; amount < b; amount++, result += a);
		std::cout << result;
		return;
	}; break;
	case '/': 
	{
		if (b == 0) { std::cout << "Not-defined\n"; return; };
		if ((Absolute(a) + -Absolute(b)) < 0) { std::cout << 0; return; };
		if (Absolute(a) < Absolute(b)) { std::cout << "Non-integral answer\n"; return; };
		if (a < 0)
		{
			a = -a;
			do
			{
				a += -Absolute(b);
				result++;
			} while (a > 0);
			std::cout << -result;
			return;
		};
		do
		{
			if (a < Absolute(b)) { std::cout << "Non-integral answer\n"; break; }; //need to figure out a way to not return value while breaking 
			a += -Absolute(b);
			result++;
		} while (a > 0);
		std::cout << (b < 0 ? -result : result);
		return;
		//TODO: Revisit 
	}; break;
	case '^': 
	{
		if (b < 0) { std::cout << "Non-integral answer\n"; return; };
		if (b == 0) { std::cout << 1; return; };
		bool isnegative = false;
		if (a < 0) { a = -a; isnegative = true; };
		int number = a;
		for (int amount = 0; amount < Absolute(b)-1; amount++)
		{
			for (int amount2 = 0; amount2 < number; amount2++, result+=a);
			a = result;
			result = 0;
		};
		std::cout << (isnegative == true ? -a : a);
		return;
	}; break;
	default: std::cout <<"\n\aUnknown Operator '" << operation << "'!";
	}; return;
}
int Adding_Calculator()
{
	//https://www.reddit.com/r/dailyprogrammer/comments/6ze9z0/20170911_challenge_331_easy_the_adding_calculator/
	std::istringstream str("12 + 25 -30 + 100 100 - 30 100 - -30 -25 - 29 -41 - -10 9 * 3 9 * -4 -4 * 8 -12 * -9 100 / 2 75 / -3 -75 / 3 7 / 3 0 / 0 5 ^ 3 -5 ^ 3 -8 ^ 3 -1 ^ 1 1 ^ 1 0 ^ 5 5 ^ 0 10 ^ -3");
	std::cin.rdbuf(str.rdbuf());
	while (std::cin)
	{
		calc(std::cin);
	};
	_getch();
	return 0;
	//date of creation: 30.11.2017
};

void checkRepetitions(std::string input[], int amountofinputs)
{
	int sequence = 0;
	do
	{
		int startpos = 0;
		std::vector<std::string> answers(1);
		answers.at(0) = '\0';
		std::cout << "Sequence #" << sequence << '\t' << input[sequence] << ":\n";
		do
		{
			int offset = 2;
			do
			{
				int timespresent = 1;
				std::string number = input[sequence].substr(startpos, offset);
				for (int i = startpos+1; i < input[sequence].length(); i++)
				{
					if (number == input[sequence].substr(i, offset)) timespresent++;
				};
				if (timespresent != 1) 
				{
					bool isalreadyfound = 0;
					for (int i = 0; i < answers.size(); i++) if (number == answers.at(i)) isalreadyfound=1;
					if (!isalreadyfound) { std::cout << number << ':' << timespresent << '\n'; answers.push_back(number);};
				}	//output according to specification
				offset++;
			} while (offset<=input[sequence].length()-1);
			startpos++;
		} while (startpos!=input[sequence].length()-3);
		sequence++;
		//std::cout << "Amount of repeating numbers: " << answers.size()-1 << '\n';
	} while (sequence<=amountofinputs);
	return;
};
int Repeating_Numbers()
{
	//https://www.reddit.com/r/dailyprogrammer/comments/7eh6k8/20171121_challenge_341_easy_repeating_numbers/
	std::string input[] =
	{
		"82156821568221",
		"11111011110111011",
		"98778912332145",
		"124489903108444899"
	};
	checkRepetitions(input, (sizeof(input) / sizeof(input[0]))-1);
	std::cout << "Press any key to continue...";
	_getch();
	return 0;
	//date of creation: 04.12.2017
};

int MozartsMusicalDice()
{
	//https://www.reddit.com/r/dailyprogrammer/comments/7i1ib1/20171206_challenge_343_intermediate_mozarts/
	std::ifstream file;
	std::string filename = "mozart-dice-starting.txt";
	file.open(filename);
	if (!file.is_open()) { std::cout << "Failed to open " << filename << "!\a\n"; _getch(); return EXIT_FAILURE; };
	struct note
	{
		std::string name = {};
		float beat = NULL;
		float duration = NULL;
	};
	std::vector<std::vector<note>> measure;
	{
		std::string tempname = {};
		float tempbeat = NULL;
		float tempduration = NULL;
		note temp = { tempname, tempbeat, tempduration };
		const int measurelength = 3;

		float measurestartbeat = 0;	//initializing measurestart before reading
		do
		{
			std::vector<note> tempmeasure;
			measurestartbeat = tempbeat;
			do
			{
				file >> tempname;
				file >> tempbeat;
				file >> tempduration;
				temp = { tempname, tempbeat, tempduration };
				temp.beat -= measurestartbeat;	//normalizing beat timing
				//std::cout << '\t' << temp.name << '\t' << temp.beat << '\t' << temp.duration << '\n';
				tempmeasure.emplace_back(temp);
				if (file.eof()) break;
			} while (temp.beat + temp.duration <= measurelength);
			measure.emplace_back(tempmeasure);
			//std::cout << "Measure " << measure.size() << ": " << measure.back().size() << " notes\n";
		} while (!file.eof());
	};	//scoped all temporary variables
	file.close();
	//-----------------------------------------------------pick 16 measures according to scheme
	int scheme[16][11] =
	{
	{96, 32, 69, 40, 148, 104, 152, 119, 98, 3, 54},
	{22, 6, 95, 17, 74, 157, 60, 84, 142, 87, 130},
	{141, 128, 158, 113, 163, 27, 171, 114, 42, 165, 10 },
	{41, 63, 13, 85, 45, 167, 53, 50, 156, 61, 103},
	{105, 146, 153, 161, 80, 154, 99, 140, 75, 135, 28 },
	{122, 46, 55, 2, 97, 68, 133, 86, 129, 47, 37},
	{11, 134, 110, 159, 36, 118, 21, 169, 62, 147, 106 },
	{30, 81, 24, 100, 107, 91, 127, 94, 123, 33, 5},
	{70, 117, 66, 90, 25, 138, 16, 120, 65, 102, 35 },
	{121, 39, 136, 176, 143, 71, 155, 88, 77, 4, 20},
	{26, 126, 15, 7, 64, 150, 57, 48, 19, 31, 108 },
	{9, 56, 132, 34, 125, 29, 175, 166, 82, 164, 92},
	{112, 174, 73, 67, 76, 101, 43, 51, 137, 144, 12 },
	{49, 18, 58, 160, 136, 162, 168, 115, 38, 59, 124},
	{109, 116, 145, 52, 1, 23, 89, 72, 149, 173, 44 },
	{14, 83, 79, 170, 93, 151, 172, 111, 8, 78, 131}
	};
	std::string outfilename = "output.txt";
	std::ofstream outputfile;
	outputfile.open(outfilename);
	if (!outputfile.is_open()) { std::cout << "Failed to open outputfile!\a"; _getch(); return EXIT_FAILURE; };
	float beat = 0;
	for (int i = 0, diceresult=2; i < 16; i++)
	{
		diceresult = (random(1, 6)+random(1, 6))-1;	//ommitting impossible '1' roll 
		std::cout <<"\t"<< i+1 << " measure " << scheme[i][diceresult] << '\n' << '\a';
		for (int j = 0; j < measure.at(scheme[i][diceresult]).size(); j++)
		{
			std::cout << measure.at(scheme[i][diceresult]).at(j).name << ' '
				<< beat + measure.at(scheme[i][diceresult]).at(j).beat << ' ' << measure.at(scheme[i][diceresult]).at(j).duration << '\n';
		};
		for (int j = 0; j < measure.at(scheme[i][diceresult]).size(); j++)
		{
			//save to file or send directly to http://ufx.space/stuff/mozart-dice/ 
			outputfile << measure.at(scheme[i][diceresult]).at(j).name << ' '
				<< beat+measure.at(scheme[i][diceresult]).at(j).beat << ' ' << measure.at(scheme[i][diceresult]).at(j).duration << '\n';
		};
		beat += 3;
	};
	outputfile.close();
	//Stretchgoal: convert output directly to midi/mp3 file 
	std::cout << "Press any key to continue...";
	_getch();
	return EXIT_SUCCESS;
	//date of creation: 01.03.2017
};

int LightRoom()
{
	struct occupancy
	{
		int enter = NULL;
		int leave = NULL;
	};
	occupancy exampleinput[] ={ {1, 3}, {2,3},{4,5} };								//Output: 3
	occupancy testinput1[] = { {2,4}, {3, 6}, {1, 3}, {6,8} };						//Output: 7
	occupancy testinput2[] = { {6,8}, {5,8}, {8,9}, {5,7}, {4,7} };					//Output: 5
	occupancy* example[] = { exampleinput, testinput1, testinput2 };

	int testinputlength[] = { 3,4,5 };												//TODO:need to calculate those programatically

	/*for (int i = 0; i < (sizeof(example) / sizeof((*example)[0])); i++)
	{
		std::cout << "Size of Example #" << i << "\nexample:\t\t" << sizeof(example) << "\texample[i]:\t" << sizeof(example[i])
			<< "\nexample/example[i]:\t" << sizeof(example)/sizeof(example[i]) << "\texample[i][0]:\t" << sizeof(example[i][0])
			<< "\n\n";
	}*/

	for (int i = 0; i < (sizeof(example)/sizeof((*example)[0])); i++)				//iterating through examples
	{
		int earliest = INT_MAX, latest = -INT_MAX, lighton = 0;
		earliest = 100;
		latest = -100;
		occupancy temp{};
		std::vector<occupancy> gaps;
		for (int j = 0; j < testinputlength[i]; j++)								//iterating through occupancies
		{
			//std::cout << "Enter " << example[i][j].enter << ", leave " << example[i][j].leave << ", difference:  " << example[i][j].leave - example[i][j].enter <<".\n";
			if (j == 0) { lighton = example[i][j].leave - example[i][j].enter; earliest = example[i][j].enter; latest = example[i][j].leave; continue; };
			if (example[i][j].enter > latest || (example[i][j].enter < earliest && example[i][j].leave < earliest))
			{
				if (gaps.size()==0)
				{
					if (example[i][j].enter > latest) 
					{	
						temp.enter = latest; temp.leave = example[i][j].enter;
						gaps.emplace_back(temp);
						lighton += example[i][j].leave - example[i][j].enter; continue;
					};
					temp.enter = example[i][j].leave; temp.leave = earliest;
					gaps.emplace_back(temp);
					lighton+= example[i][j].leave - example[i][j].enter; continue;
				};
				for (int k = 0; k < gaps.size(); k++)
				{
					if (gaps.at(k).enter > example[i][j].enter && gaps.at(k).leave > example[i][j].leave) { lighton += example[i][j].leave - gaps.at(k).enter; gaps.at(k).enter = example[i][j].leave; continue; };
					if (gaps.at(k).enter < example[i][j].enter && gaps.at(k).leave < example[i][j].leave) { lighton += gaps.at(k).leave - example[i][j].enter; gaps.at(k).leave = example[i][j].enter; continue; };
					if (gaps.at(k).enter < example[i][j].enter && gaps.at(k).leave > example[i][j].leave) 
					{ 
						lighton += (gaps.at(k).leave - example[i][j].leave) - (example[i][j].enter - gaps.at(k).enter);
						temp.enter = example[i][j].leave; temp.leave = gaps.at(k).leave;
						gaps.emplace_back(temp);
						gaps.at(k).leave = example[i][j].enter;
						continue;
					};
				};
			};
			if (example[i][j].enter < earliest) { lighton+=earliest-example[i][j].enter; earliest = example[i][j].enter; };
			if (example[i][j].leave > latest) { lighton += example[i][j].leave - latest; latest = example[i][j].leave; };
		};
			std::cout << "In case#" << i << " lightbulb was on for " << lighton << ".\n";
	};

	std::cout << "Press any key to continue ...";
	_getch();
	return EXIT_SUCCESS;
	//https://www.reddit.com/r/dailyprogrammer/comments/7qn07r/20180115_challenge_347_easy_how_long_has_the/
	//Date of creation: 05.03.2018
}; 

std::vector<std::vector<int>> guess;
void computepermutations(std::vector<int> & values)
{
	do
	{
		guess.emplace_back(values);
	} while (std::next_permutation(values.begin(), values.end()));
};
std::string SolveCryptaritmethic(const std::string & input)
{
	std::string answer="Nothing here yet!";

	//process input into data and operators
	std::vector<std::vector<char>> word;		//collection of letters and words
	word.emplace_back();
	std::vector<char> operators;				//collection of operators
	struct assume { char letter; int value; };
	std::vector<assume> characters;
	//extract letters from data 
	for (int  i = 0; i < input.length(); i++)
	{
		bool found = false;
		if (isblank(input.at(i))) continue;
		if (isalpha(input.at(i)))
		{
			if (0 == word.size()) { word.emplace_back();  word.back().emplace_back(input.at(i)); continue; };
			for (int j = 0; j < word.size(); j++)
			{
				for (int k = 0; k < word[j].size(); k++)
				{
					if (word[j][k] == input.at(i)) { found = true; break; };
				};
			};
			if (found == false) { assume temp{ input.at(i),NULL }; characters.emplace_back(temp); }
			word.back().emplace_back(input.at(i));
			continue;
		};
		if ('+'== input.at(i) || '-'== input.at(i) || '='==input.at(i))
		{
			switch (input.at(i))
			{
			case '-': operators.emplace_back(input.at(i)); word.emplace_back(); break;
			case '+': operators.emplace_back(input.at(i)); word.emplace_back(); break;
			case '=': operators.emplace_back(input.at(i)); word.emplace_back(); i++; break;
			default: break;
			};
		};
	};
	/*for (int i = 0; i < word.size(); i++)
	{
		for (int j = 0; j < word.at(i).size(); j++)
		{
			std::cout << word.at(i).at(j);
		};
		if(i<operators.size()) std::cout << ' ' << operators[i] << ' ';
	};
	std::cout << "\nDifferent characters: ";
	for (int i = 0; i < characters.size(); i++)
	{
		std::cout << characters.at(i).letter; std::cout << ", ";
	};
	std::cout << '\n';*/
	//assume values of letters & check assumption
	bool assumption = false;
	
	std::vector<int> possiblevalue{ 1,2,3,4,5,6,7,8,9,0 };
	const long permutations = 3628800;
	if (guess.capacity()==0)
	{
		std::cout << "Guess size before resizing: " << guess.capacity() << "\n";
		guess.reserve(sizeof(possiblevalue)*permutations);
		std::cout << "Guess size after resizing: " << guess.capacity() << "\n";
		computepermutations(possiblevalue);
	};
	std::cout << "There are " << guess.size() << " combinations\n";
	//do {
	
	for (int it = 0; it < guess.size(); it++)
	{
		answer.clear();
		for (int i = 0; i < characters.size(); i++)
		{
			//assume values - bruteforce, need not to repeat assumptions. IDEA: Map already used/unused values ?
			// TODO: make brutforce algorithm (checking all permutations assumed values to n-long character set)
			/*placeholder*/ characters[i].value = guess[it][i];
			//prepare answer
			answer += (char)' \'';
			answer += characters[i].letter;
			answer += "\'=";
			answer += std::to_string(characters[i].value);
		};
		//std::cout << "Tested solution: " << answer << '\n';
		std::string temp;

		int* number;
		number = new int[word.size()];
		for (int i = 0; i < word.size(); i++)
		{
			temp.clear();
			for (int j = 0; j < word[i].size(); j++)
			{
				for (int k = 0; k < characters.size(); k++)
				{
					if (characters[k].letter == word[i][j]) { temp += std::to_string(characters[k].value); break; };
				};
			};
			//std::cout << temp << "\n";
			number[i] = std::stoi(temp);
		};
		for (int i = 0, sum = number[i]; i < operators.size(); i++)
		{
			//std::cout << "sum = " << sum << "\n";
			if (operators[i] == '+') { sum += number[i + 1]; continue; };
			if (operators[i] == '-') { sum -= number[i + 1]; continue; };
			if (operators[i] == '*') { sum *= number[i + 1]; continue; };
			if (operators[i] == '/') { sum /= number[i + 1]; continue; };
			if (operators[i] == '=') { if (sum == number[i + 1]) { assumption = true; delete[] number; return answer; }; break; };
		};
		delete[] number;
	};
	//} while (assumption==false );
	return answer;
};
int Cryptarithmetic_Solver()
{
	std::string example[]
	{
		"SEND + MORE == MONEY",
		"THIS + IS + HIS == CLAIM",
		"WHAT + WAS + THY == CAUSE",
		"HIS + HORSE + IS == SLAIN",
		"HERE + SHE == COMES",
		"FOR + LACK + OF == TREAD",
		"I + WILL + PAY + THE == THEFT"
	};
	for (int i = 0; i < (sizeof(example) / sizeof(*example)); i++)
	{
		std::cout << example[i] << " answer:\n" << SolveCryptaritmethic(example[i]) << "\n\n\a";
	};
	std::cout << "Press any key to continue...";
	_getch();
	return EXIT_SUCCESS;
	//https://www.reddit.com/r/dailyprogrammer/comments/7p5p2o/20180108_challenge_346_easy_cryptarithmetic_solver/
	//Date of creation: 07.03.18
}

std::string DisplayBowlingFrame(std::vector<int> input)
{
	const int frames = 10;	//bowling game consists of 10 frames
	const int pins = 10;	//in which player has 2 attempts to knock down 10 pins
	//If the player knocks down all 10 pins on the first roll, that should be displayed as X, and the next number will be the first roll of the next frame.
	//If the player doesn't knock down any pins, that should be displayed as -
	//If the player gets a spare (knocks down the remaining pins on the second roll of the frame, that should be displayed as /

	std::string bowlingframe={};
	//enum struck {-,1,2,3,4,5,6,7,8,9,X};
	//std::cout << "Array " << &input << ", size= " << input.size() << '\n';
	for (int i = 0, frame=0; i < input.size() && frame<10 ; i++, frame++)
	{
		//if (input[i] == 0) bowlingframe.append("-");
		if (input[i] == pins) { bowlingframe.append("X  "); continue; };
		if (input[i] + input[i + 1] == pins) { bowlingframe.append(std::to_string(input[i]) + "/ "); i++; continue; };
		bowlingframe.append(std::to_string(input[i])); bowlingframe.append(std::to_string(input[++i]) + " ");
	};
	return bowlingframe;
};
int BowlingFramesDisplay()
{
	//TODO:	Fix - output needs to be strictly formatted
	std::vector<std::vector<int>> examples=
	{																	//Outputs:
		{6, 4, 5, 3, 10, 10, 8, 1, 8, 0, 10, 6, 3, 7, 3, 5, 3},			// 6/ 53 X  X  81 8- X  63 7/ 53
		{9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0 },	// 9- 9- 9- 9- 9- 9- 9- 9- 9- 9-
		{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},				// X  X  X  X  X  X  X  X  X  XXX
		{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},// 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/5
		{10, 3, 7, 6, 1, 10, 10, 10, 2, 8, 9, 0, 7, 3, 10, 10, 10},		// X  3/ 61 X  X  X  2/ 9- 7/ XXX
		{9, 0, 3, 7, 6, 1, 3, 7, 8, 1, 5, 5, 0, 10, 8, 0, 7, 3, 8, 2, 8}// 9- 3/ 61 3/ 81 5/ -/ 8- 7/ 8/8
	};
	for (int i = 0; i < examples.size(); i++)
	{
		std::cout << DisplayBowlingFrame(examples[i]) << '\n';
	};
	std::cout << "\aPress any key to continue...";
	_getch();
	return EXIT_SUCCESS;
 //https://www.reddit.com/r/dailyprogrammer/comments/7so37o/20180124_challenge_348_intermediate_bowling/
};

std::string Decode_AlphabetCipher(const std::string & keyword, const std::string & message, bool decode)
{
	const std::string chart[] =
	{ "abcdefghijklmnopqrstuvwxyz",
		"bcdefghijklmnopqrstuvwxyza",
		"cdefghijklmnopqrstuvwxyzab",
		"defghijklmnopqrstuvwxyzabc",
		"efghijklmnopqrstuvwxyzabcd",
		"fghijklmnopqrstuvwxyzabcde",
		"ghijklmnopqrstuvwxyzabcdef",
		"hijklmnopqrstuvwxyzabcdefg",
		"ijklmnopqrstuvwxyzabcdefgh",
		"jklmnopqrstuvwxyzabcdefghi",
		"klmnopqrstuvwxyzabcdefghij",
		"lmnopqrstuvwxyzabcdefghijk",
		"mnopqrstuvwxyzabcdefghijkl",
		"nopqrstuvwxyzabcdefghijklm",
		"opqrstuvwxyzabcdefghijklmn",
		"pqrstuvwxyzabcdefghijklmno",
		"qrstuvwxyzabcdefghijklmnop",
		"rstuvwxyzabcdefghijklmnopq",
		"stuvwxyzabcdefghijklmnopqr",
		"tuvwxyzabcdefghijklmnopqrs",
		"uvwxyzabcdefghijklmnopqrst",
		"vwxyzabcdefghijklmnopqrstu",
		"wxyzabcdefghijklmnopqrstuv",
		"xyzabcdefghijklmnopqrstuvw",
		"yzabcdefghijklmnopqrstuvwx",
		"zabcdefghijklmnopqrstuvwxy"
	};
	int asciioffset = 97;	//offset of lower case letters in ascii encoding
	std::string solution{};
	if (!decode)
	{
		for (int letter = 0; letter < message.length(); letter++)
		{ solution += chart[(int)keyword[letter % keyword.length()] - asciioffset][(int)message[letter] - asciioffset]; }
	}
	else
	{
		for (int letter = 0; letter < message.length(); letter++)
		{	solution += chart[0][chart[(int)keyword[letter % keyword.length()] - asciioffset].find(message[letter])];	};
	};
	return solution;
};
int AlphabetCipher()
{
	std::string answer{};
	std::string input[][2] =			//TODO: Find out why - if dimension y is not specified VC throws an error "Array cannot contain elements of this type" (type is resolved to const char*)
	{ 
		{ "snitch", "thepackagehasbeendelivered" },
		{ "bond", "theredfoxtrotsquietlyatmidnight" },
		{ "train", "murderontheorientexpress" },
		{ "garden", "themolessnuckintothegardenlastnight" },

		{ "cloak", "klatrgafedvtssdwywcyty" },
		{ "python", "pjphmfamhrcaifxifvvfmzwqtmyswst" },
		{ "moore", "rcfpsgfspiecbcc" }
	};
	std::string output[] =
	{
		"lumicjcnoxjhkomxpkwyqogywq",
		"uvrufrsryherugdxjsgozogpjralhvg",
		"flrlrkfnbuxfrqrgkefckvsa",
		"zhvpsyksjqypqiewsgnexdvqkncdwgtixkx",

		"iamtheprettiestunicorn",
		"alwayslookonthebrightsideoflife",
		"foryoureyesonly"
	};
	bool decode=false;
	//bonus does not work correctly need to figure out decoding
	for (int i = 0; i < sizeof(output)/sizeof(*output); i++)
	{
		Timer timer;		//execution time
		if (i == 4) decode = true;
		std::cout << "\n\nCodeword:\t" << input[i][0] << "\nmessage:\t" << input[i][1];
		answer = Decode_AlphabetCipher(input[i][0], input[i][1], decode);
		std::cout << "\nAnswer:\t\t" << answer << " is ";
		if (answer == output[i]) { std::cout << "correct."; }
		else { std::cout << "incorrect."; };
	};

	std::cout << "\n\nPress any key to continue ...";
	_getch();
	_getch();	//TODO: Needs fix each key press is registered as two after one of last updates. FIX: change default keyboard character encoding? 
	return 0;

	//https://www.reddit.com/r/dailyprogrammer/comments/879u8b/20180326_challenge_355_easy_alphabet_cipher/
	//date of creation: 15-16.07.2018
}


/*
//-----------------------------------------------------------------------------------------------------------------
namespace
{
	std::size_t callback(
		const char* in,
		std::size_t size,
		std::size_t num,
		std::string* out)
	{
		const std::size_t totalBytes(size * num);
		out->append(in, totalBytes);
		return totalBytes;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------
struct Lattitude
{
	float Value{};
	enum direction { N = 0, S = 1 };
	direction Direction{};
};
struct Longitude
{
	float Value{};
	enum direction { E = 0, W = 1 };
	direction Direction{};
};
struct Coordinates
{
	Lattitude Lattitude{};
	Longitude Longitude{};
};
*/
int ClosestAirbornePlane()
{
	std::cout << "\n\aThis project is posptponed untill i figure out how to link libraries (mainly CURL)"
		<< "\n\nPress any key to continue ...";
	_getch();
	_getch();
	return 0;
	/*
	//Get data from https://opensky-network.org/api/states/all
	//(needs library, suggested libcurl https://curl.haxx.se/libcurl/ ) 
	
	//Learning JSON as per https://stackoverflow.com/questions/24884490/using-libcurl-and-jsoncpp-to-parse-from-https-webserver
	//https://github.com/Tencent/rapidjson/blob/master/example/tutorial/tutorial.cpp
	//Test data:	http://date.jsontest.com/
	//Loop through JSON entries and store the nearest one using Euclidean distance https://en.wikipedia.org/wiki/Euclidean_distance
	//Display full info of the closest airborne aeroplane
	
	//Bonus: Geodesic distance formula for more accuracy: https://en.wikipedia.org/wiki/Great-circle_distance
	//Private bonus: Get current device location ( https://developers.google.com/maps/documentation/geolocation/intro - need to investigate this)

	//Test data
	const std::string url("http://date.jsontest.com/");
	//---------------------------------------------------------------------------------------------------------------------------------------------
	CURL* curl = curl_easy_init();
	// Set remote URL.
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	// Don't bother trying IPv6, which would increase DNS resolution time.
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	// Don't wait forever, time out after 10 seconds.
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	// Follow HTTP redirects if necessary.
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	// Response information.
	int httpCode(0);
	std::unique_ptr<std::string> httpData(new std::string());
	// Hook up data handling function.
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

	// Hook up data container (will be passed as the last parameter to the
	// callback handling function).  Can be any pointer type, since it will
	// internally be passed as a void pointer.
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

	// Run our HTTP GET command, capture the HTTP response code, and clean up.
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	curl_easy_cleanup(curl);

	if (httpCode == 200)
	{
		std::cout << "\nGot successful response from " << url << std::endl;

		std::cout << "\nData: " << *httpData << "\a";
		_getch();
		_getch();
		// Response looks good - done using Curl now.  Try to parse the results
		// and print them out.

		//different JSONAPI than used in my project - needs to change
		//Json::Value jsonData;
		//Json::Reader jsonReader;
		
		/*
		rapidjson::Document document;

		//in situ parsing
		if (document.ParseInsitu(string variable).HasParseError())
			return 1;


		if (jsonReader.parse(*httpData, jsonData))
		{
			std::cout << "Successfully parsed JSON data" << std::endl;
			std::cout << "\nJSON data received:" << std::endl;
			std::cout << jsonData.toStyledString() << std::endl;

			const std::string dateString(jsonData["date"].asString());
			const std::size_t unixTimeMs(
				jsonData["milliseconds_since_epoch"].asUInt64());
			const std::string timeString(jsonData["time"].asString());

			std::cout << "Natively parsed:" << std::endl;
			std::cout << "\tDate string: " << dateString << std::endl;
			std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;
			std::cout << "\tTime string: " << timeString << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Could not parse HTTP data as JSON" << std::endl;
			std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
			return 1;
		}
		
	}
	else
	{
		std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
		return 1;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------

	Coordinates EiffelTower =		{{48.8584, Lattitude::direction::N},
									{2.2945, Longitude::direction::E } };
	Coordinates JohnFKennedyAirport { { 40.6413, Lattitude::direction::N },
									{73.7781, Longitude::direction::W } };
	std::cout << "\nEiffelTower\nLat:\t" << EiffelTower.Lattitude.Value << " " << EiffelTower.Lattitude.Direction
		<< "\nLon:\t" << EiffelTower.Longitude.Value << " " << EiffelTower.Longitude.Direction
		<< "\n\nJFKAirport\nLat:\t" << JohnFKennedyAirport.Lattitude.Value << " " << JohnFKennedyAirport.Lattitude.Direction
		<< "\nLon:" << JohnFKennedyAirport.Longitude.Value << " " << JohnFKennedyAirport.Longitude.Direction;
	_getch();
	std::cout << "\n\nPress any key to continue...";
	_getch();
	return 0;
	//https://www.reddit.com/r/dailyprogrammer/comments/8i5zc3/20180509_challenge_360_intermediate_find_the/
	//Date of creation: 17.07.2018
	*/
};

std::string Tally(const std::string tally)
{
	const int ASCIIoffset = 'a';
	//TODO: do not initialize so program could count points for n players instead of fixed amount of 5 
	std::vector<int> score(5);

	//Counting score
	for each (char character in tally)
	{
		if (!islower(character))
		{
			score.at(tolower(character) - ASCIIoffset)--; continue;
		};
		score.at(character - ASCIIoffset)++;
	};

	//prepare answer
	//TODO: sort scores in ascending order
	//std::sort(score.begin(), score.end());	//this could work if there was a way not to lose track of player scores
	std::string result{};
	for (int player = 0; player < score.size(); player++)
	{
		//std::cout << char(i + offset) << " : " << score.at(i) << ',';
		result += (char)(player + ASCIIoffset);
		result += " : " + std::to_string(score.at(player)) + ", ";
	};
	return result;
};
int TallyProgram()
{

	std::string input[] =
	{
		"abcde",
		"dbbaCEDbdAacCEAadcB",
		"EbAAdbBEaBaaBBdAccbeebaec"			//c : 3, d : 2, a : 1, e :1, b : 0  
	};
	std::string output[] =
	{
		"a : 1, b : 1, c : 1, d : 1, e : 1",
		"b : 2, d : 2, a : 1, c : 0, e : -2",
		"c : 3, d : 2, a : 1, e : 1, b : 0"

	};

	for (int i = 0; i < (sizeof(input)/sizeof(input[0])); i++)
	{
		std::cout << "\n\nInput:\t\t" << input[i] 
			<< "\nRestlt:\t\t" << Tally(input[i])
			<< "\nExpected:\t" << output[i];
	};

	std::cout << "\n\nPress any key to continue ...";
	_getch();
	_getch(); 
	return EXIT_SUCCESS;
	//https://www.reddit.com/r/dailyprogrammer/comments/8jcffg/20180514_challenge_361_easy_tally_program/
	//Date of creation: 12.08.2018
}