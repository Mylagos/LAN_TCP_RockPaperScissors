#include "server.h"

Server::Server()
{
}

void Server::Run()
{
	system("Color 06");
	if (listener_.listen(7777) != sf::Socket::Done)
		std::cout << "Error!: No idea tbh, no wifi?\n";
	else
		std::cout << "Listening\n";

	if (listener_.accept(client1_) != sf::Socket::Done)
		std::cout << "Error!: No bitches\n";
	else
		std::cout << "Client 1 Connected\n";

	if (listener_.accept(client2_) != sf::Socket::Done)
		std::cout << "Error!: No bitches\n";
	else
		std::cout << "Client 2 Connected\n";

	bool loop = true;
	while (loop)
	{
		switch (state_)
		{
		case ServerStates::StartUp :
			StartUp();
			break;
		case ServerStates::WaitBeginSet:
			WaitBeginSet();
			break;
		case ServerStates::Client1PlaysFirst:
			Client1PlaysFirst();
			client1WasFirstLastSet_ = true;
			break;
		case ServerStates::Client2PlaysFirst:
			Client2PlaysFirst();
			client1WasFirstLastSet_ = false;
			break;
		case ServerStates::SendResults:
			SendResults();
			break;
		}
	}
}

void Server::StartUp()
{

	MyPacket packet(MyPacketType::BothConnected);
	serverPacket_ << packet;
	client1_.send(serverPacket_);
	client2_.send(serverPacket_);
	serverPacket_.clear();
	state_ = ServerStates::WaitBeginSet;
}

void Server::WaitBeginSet()
{
	/*client1_.setBlocking(false);
	client2_.setBlocking(false);*/
	std::cout << "STATE: Wait Begin Set\n";
	if (!client1Ready_)
		std::cout << "Client 1 Not Ready\n";
		if (client1_.receive(serverPacket_) == sf::Socket::Done)
		{
			MyPacket readyPacket;
			serverPacket_ >> readyPacket;
			serverPacket_.clear();
			if (readyPacket.type == MyPacketType::Ready)
			{
				std::cout << "Client 1 Ready\n";
				client1Ready_ = true;
			}
			else
				std::cout << "Wrong packet type from client 1\n";
		}
	if (!client2Ready_)
		std::cout << "Client 2 Not Ready\n";
		if (client2_.receive(serverPacket_) == sf::Socket::Done)
		{
			MyPacket readyPacket;
			serverPacket_ >> readyPacket;
			serverPacket_.clear();
			if (readyPacket.type == MyPacketType::Ready)
			{
				std::cout << "Client 2 Ready\n";
				client2Ready_ = true;
			}
			else
				std::cout << "Wrong packet type from client 2\n";
		}
	if (client1Ready_ && client2Ready_)
	{
		client1_.setBlocking(true);
		client2_.setBlocking(true);
		if (client1WasFirstLastSet_)
			state_ = ServerStates::Client2PlaysFirst;
		else
			state_ = ServerStates::Client1PlaysFirst;
	}
}

void Server::Client1PlaysFirst()
{
	std::cout << "State : Client 1 plays first\n";
	MyPacket youPlayPacket(MyPacketType::YouPlay);
	serverPacket_ << youPlayPacket;
	client1_.send(serverPacket_);
	serverPacket_.clear();

	MyPacket youWaitPacket(MyPacketType::YouWait);
	serverPacket_ << youWaitPacket;
	client2_.send(serverPacket_);
	serverPacket_.clear();

	if (client1_.receive(serverPacket_) == sf::Socket::Done)
	{
		PlayedPacket donePlayPacket;
		serverPacket_ >> donePlayPacket;
		serverPacket_.clear();
		if (donePlayPacket.type == MyPacketType::Played)
			client1Move_ = donePlayPacket.myMove;
	}

	MyPacket youPlayPacket2(MyPacketType::YouPlay);
	serverPacket_ << youPlayPacket2;
	client2_.send(serverPacket_);
	serverPacket_.clear();

	if (client2_.receive(serverPacket_) == sf::Socket::Done)
	{
		PlayedPacket donePlayPacket;
		serverPacket_ >> donePlayPacket;
		serverPacket_.clear();
		if (donePlayPacket.type == MyPacketType::Played)
			client2Move_ = donePlayPacket.myMove;
	}

	MyPacket prepareToGetResults(MyPacketType::Results);
	serverPacket_ << prepareToGetResults;
	client1_.send(serverPacket_);
	serverPacket_.clear();

	state_ = ServerStates::SendResults;
}

void Server::Client2PlaysFirst()
{
	std::cout << "State : Client 2 plays first\n";
	MyPacket youPlayPacket(MyPacketType::YouPlay);
	serverPacket_ << youPlayPacket;
	client2_.send(serverPacket_);
	serverPacket_.clear();

	MyPacket youWaitPacket(MyPacketType::YouWait);
	serverPacket_ << youWaitPacket;
	client1_.send(serverPacket_);
	serverPacket_.clear();

	if (client2_.receive(serverPacket_) == sf::Socket::Done)
	{
		PlayedPacket donePlayPacket;
		serverPacket_ >> donePlayPacket;
		serverPacket_.clear();
		if (donePlayPacket.type == MyPacketType::Played)
			client2Move_ = donePlayPacket.myMove;
	}

	MyPacket youPlayPacket2(MyPacketType::YouPlay);
	serverPacket_ << youPlayPacket2;
	client1_.send(serverPacket_);
	serverPacket_.clear();

	if (client1_.receive(serverPacket_) == sf::Socket::Done)
	{
		PlayedPacket donePlayPacket;
		serverPacket_ >> donePlayPacket;
		serverPacket_.clear();
		if (donePlayPacket.type == MyPacketType::Played)
			client1Move_ = donePlayPacket.myMove;
	}

	MyPacket prepareToGetResults(MyPacketType::Results);
	serverPacket_ << prepareToGetResults;
	client2_.send(serverPacket_);
	serverPacket_.clear();

	state_ = ServerStates::SendResults;
}

void Server::SendResults()
{
	std::cout << "State : Sending results\n";



	ResultsPacket client1Packet(client2Move_, client1Score_, client2Score_);
	serverPacket_ << client1Packet;
	client1_.send(serverPacket_);
	serverPacket_.clear();
	ResultsPacket client2Packet(client1Move_, client2Score_, client1Score_);
	serverPacket_ << client2Packet;
	client2_.send(serverPacket_);
	serverPacket_.clear();
	state_ = ServerStates::WaitBeginSet;
}
