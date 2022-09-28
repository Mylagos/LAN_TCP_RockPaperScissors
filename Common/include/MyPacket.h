#pragma once
#include "GameRules.h"
#include "SFML/Network/Packet.hpp"

enum class MyPacketType : int
{
	None = 0,
	BothConnected, //1
	YouPlay, //2
	YouWait, //3
	Ready, //4
	Played, //5
	Results //6
};

class MyPacket
{
public:
	MyPacket();
	explicit MyPacket(MyPacketType type);
	MyPacketType type;
};

	sf::Packet& operator <<(sf::Packet& packet, const MyPacket& myPacket);
	sf::Packet& operator >>(sf::Packet& packet, MyPacket& myPacket);

class PlayedPacket : public MyPacket
{
public:
	PlayedPacket();
	PlayedPacket(RPSStates myMove);

	RPSStates myMove;
};

sf::Packet& operator <<(sf::Packet& packet, const RPSStates& myMove_);
sf::Packet& operator >>(sf::Packet& packet, RPSStates& myMove);

sf::Packet& operator <<(sf::Packet& packet, const PlayedPacket& myPacket);
sf::Packet& operator >>(sf::Packet& packet, PlayedPacket& myPacket);

class ResultsPacket : public MyPacket
{
public:
	ResultsPacket();
	ResultsPacket(RPSStates theirMove, int yourScore, int theirScore);

	RPSStates theirMove;
	int myScore;
	int theirScore;
};

sf::Packet& operator <<(sf::Packet& packet, const ResultsPacket& myPacket);
sf::Packet& operator >>(sf::Packet& packet, ResultsPacket& myPacket);