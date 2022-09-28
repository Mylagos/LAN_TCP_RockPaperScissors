#pragma once
#include <iostream>
#include <array>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"

#include "ClientStates.h"
#include "MyPacket.h"
#include "AsciiArt.h"

class Client
{
public:
	Client();

	void Run();

	void StartupInterface();

	void DisplayScores();

	void AcceptMatch();
	void WaitingForOtherAccept();
	void YourTurnInterface();
	void WaitingAsP1();
	void WaitingAsP2();
	void SetClimax();

	RPSStates ChoseMove(std::string) const;
private:
	sf::TcpSocket socket_;
	std::string ip_ = "localhost";
	unsigned short port_ = 7777;
	sf::Packet clientPacket_;
	sf::Packet resultsPacket_;
	int playerNumber_ = 0;

	int displayYourScore_ = 0;
	int displayTheirScore_ = 0;
	sf::Clock myClock_;

	ClientStates state_ = ClientStates::Connecting;
	bool playedLast = false;

	RPSStates movePlayedThisSet_;
	std::vector<std::string> movePlayedForAnim2_;
	int animationIterator_ = 0;
};


