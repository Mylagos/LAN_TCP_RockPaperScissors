#include "MyPacket.h"


MyPacket::MyPacket() : MyPacket(MyPacketType::None)
{
}

MyPacket::MyPacket(MyPacketType type)
	: type(type)
{
}

sf::Packet& operator <<(sf::Packet& packet, const MyPacket& myPacket)
{
	const auto type = static_cast<int>(myPacket.type);
	return packet << type;
}

sf::Packet& operator>>(sf::Packet& packet, MyPacket& myPacket)
{
	int type = 0;
	packet >> type;
	myPacket.type = static_cast<MyPacketType>(type);
	return packet;
}

PlayedPacket::PlayedPacket() : MyPacket(MyPacketType::Played), myMove(RPSStates::None)
{
}

PlayedPacket::PlayedPacket(RPSStates myMove)
	: MyPacket(MyPacketType::Played), myMove(myMove)
{
}

sf::Packet& operator<<(sf::Packet& packet, const RPSStates& myMove_)
{
	const auto myMove = static_cast<int>(myMove_);
	return packet << myMove;
}

sf::Packet& operator>>(sf::Packet& packet, RPSStates& myMove)
{
	int move = 0;
	packet >> move;
	myMove = static_cast<RPSStates>(move);
	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, const PlayedPacket& myPacket)
{
	const auto type = static_cast<int>(myPacket.type);
	const auto move = static_cast<int>(myPacket.myMove);
	return packet << type << move;

}

sf::Packet& operator>>(sf::Packet& packet, PlayedPacket& myPacket)
{
	int type = 0;
	int move = 0;
	packet >> type >> move;
	myPacket.type = static_cast<MyPacketType>(type);
	myPacket.myMove = static_cast<RPSStates>(move);
	return packet;
}

ResultsPacket::ResultsPacket() : MyPacket(MyPacketType::Results), theirMove(RPSStates::None), myScore(0), theirScore(0)
{
}

ResultsPacket::ResultsPacket(RPSStates theirMove, int yourScore, int theirScore)
	: MyPacket(MyPacketType::Results), theirMove(theirMove), myScore(yourScore), theirScore(theirScore)
{
}

sf::Packet& operator<<(sf::Packet& packet, const ResultsPacket& myPacket)
{
	const auto type = static_cast<int>(myPacket.type);
	const auto theirMove = static_cast<int>(myPacket.theirMove);
	return packet << type << theirMove << myPacket.myScore << myPacket.theirScore;
}

sf::Packet& operator>>(sf::Packet& packet, ResultsPacket& myPacket)
{
	int type = 0;
	int theirMove = 0;
	packet >> type >> theirMove >> myPacket.myScore >> myPacket.myScore;
	myPacket.type = static_cast<MyPacketType>(type);
	myPacket.theirMove = static_cast<RPSStates>(theirMove);
	return packet;
}
