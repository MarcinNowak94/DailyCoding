#include "stdafx.h"
#include "dailyprogrammer.h"
#include "Helper_functions.h"

void clock(std::string time)
{
	std::string digits[] { "oh", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
	std::string decimal[] { "\b", "ten", "twenty", "thirty", "fourty", "fifty" };
	std::string suffix[] {"am", "pm"};
	std::cout << '\n' << time<< ": ";
	std::string final = "It's ";
	int hours = std::stoi(time.substr(0, 2));
	int minutes = std::stoi(time.substr(3, 4));
	//std::cout << final << digits[hours % 12] << ' ' << decimal[minutes / 10] << ' ' << digits[minutes % 10] << ' ' << suffix[hours / 12] << '\n';
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

int Assembler(std::string incoming_packet)
{
	struct packet
	{
		int message_ID;			//which message this packet is a part of
		int packet_ID;			//the index of this packet in the message (zero-indexed)
		int num_of_packets;		//total number of packets in the message
		std::string message{};	//part of message
	};
	std::cout << "\nRecieved: " << incoming_packet << '\n';
	/*for (size_t i = 0; i < 17; i++)
	{
		std::cout << incoming_packet[i] << "[" << i << "]";
	};*/
	std::vector<packet> message();
	packet incoming;
	int elementpos = 0;
	incoming.message_ID = std::stoi(incoming_packet.substr(elementpos, incoming_packet.find_first_of(' ')));

	if(elementpos!=incoming_packet.length()) elementpos = incoming_packet.find_first_not_of(' ', incoming_packet.find_first_of(' '));					//next non-blank character
	incoming.packet_ID = std::stoi(incoming_packet.substr(elementpos, incoming_packet.find(' ', elementpos)));

	if (elementpos != incoming_packet.length()) elementpos = incoming_packet.find_first_not_of(' ', incoming_packet.find(' ', elementpos));					//next non-blank character
	incoming.num_of_packets = std::stoi(incoming_packet.substr(elementpos, incoming_packet.find(' ', elementpos)));

	if (elementpos != incoming_packet.length()) elementpos = incoming_packet.find_first_not_of(' ', incoming_packet.find(' ', elementpos));					//next non-blank character
	incoming.message = incoming_packet.substr(elementpos, incoming_packet.length());
	std::cout << "\nPacket test:"
		<< "\nMessage ID:\t" << incoming.message_ID
		<< "\nPacket ID:\t" << incoming.packet_ID
		<< "\nnum of p:\t" << incoming.num_of_packets
		<< "\nmessage:\t" << incoming.message;
	return 0;
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
	for (size_t i = 0; i < sizeof(messages)/sizeof(messages[0])-1; i++)
	{
		std::cout << "\nPacket sent to assembler:\n"
			<< messages[i];
		Assembler(messages[i]);
	};
	_getch();
	return 0;
	//date of creation: 26.09.2017
}