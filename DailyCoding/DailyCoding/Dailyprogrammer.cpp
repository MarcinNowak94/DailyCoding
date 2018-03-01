#include "stdafx.h"
#include "dailyprogrammer.h"
#include "Helper_functions.h"
#include <sstream> //stream manipulation

void clock(std::string time)
{
	std::string digits[] { "oh", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
	std::string decimal[] { "\b", "ten", "twenty", "thirty", "fourty", "fifty" };
	std::string suffix[] {"am", "pm"};
	std::cout << '\n' << time<< ": ";
	std::string final = "It's ";
	int hours = std::stoi(time.substr(0, 2));
	int minutes = std::stoi(time.substr(3, 4));
	if (0 == hours) { final.append(digits[12]); } else final.append(digits[hours % 12]);
	final.append(" ");
	if (0 == minutes) { final.append("\b"); }
	else if (minutes > 9 && minutes < 20) { final.append(digits[minutes]); }
	else if (0 == minutes % 10) { final.append(decimal[minutes / 10]); }
	else { final.append(decimal[minutes / 10]); final.append(" "); final.append(digits[minutes % 10]); };
	final.append(" ");
	final.append(suffix[hours / 12]);
	std::cout << final;
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
	//clock("00:00");
	//clock("01:30");
	//clock("12:05");
	//clock("14:01");
	//clock("20:29");
	//clock("21:00");
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
	_getch();
	return 0;
	//date of creation: 26.09.2017
};

static struct packet
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
	int elementpos = 0;
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
		"6450    0   11  Voilà!In view, a humble vaudevillian veteran, cast vicariously as both victim",
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