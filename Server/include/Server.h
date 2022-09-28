#pragma once
#include <iostream>

#include "SFML/Network/TcpListener.hpp"
#include "SFML/Network/TcpSocket.hpp"
#include "SFML/Network/Packet.hpp"
#include "MyPacket.h"
#include "ServerStates.h"
#include "GameRules.h"

class Server
{
public:
	Server();

	void Run();
	void StartUp();
	void WaitBeginSet();
	void Client1PlaysFirst();
	void Client2PlaysFirst();
	void SendResults();

private:

	sf::TcpListener listener_;
	sf::TcpSocket client1_;
	sf::TcpSocket client2_;

	ServerStates state_ = ServerStates::StartUp;

	sf::Packet serverPacket_;

	bool client1WasFirstLastSet_ = false;

	bool client1Ready_ = false;
	bool client2Ready_ = false;

	int client1Score_ = 0;
	int client2Score_ = 0;

	RPSStates client1Move_;
	RPSStates client2Move_;
};
