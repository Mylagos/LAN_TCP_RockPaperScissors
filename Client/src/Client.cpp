#include "Client.h"

Client::Client()
{
}

void Client::Run()
{
	bool isRunning = true;
	while(isRunning)
	{
		switch (state_)
		{
		case ClientStates::Connecting:
			StartupInterface();
			break;
		case ClientStates::AcceptMatch:
			system("Color 07");
			AcceptMatch();
			break;
		case ClientStates::AcceptMatchWaiting:
			WaitingForOtherAccept();
			break;
		case ClientStates::Playing:
			YourTurnInterface();
			break;
		case ClientStates::WaitingAsPlayer1:
			WaitingAsP1();
			break;
		case ClientStates::WaitingAsPlayer2:
			playedLast = true;
			WaitingAsP2();
			break;
		case ClientStates::ClimaxAcceptMatch:
			SetClimax();
			break;
		}
	}
}

void Client::DisplayScores()
{
	std::cout << "Your score : " << displayYourScore_ << "\t\t\t Opponent's score : " << displayTheirScore_ << std::endl << std::endl;
}

void Client::StartupInterface()
{
	bool ipCheckOkay = false;
	bool portCheckOkay = false;
	std::string input;
	system("Color 06");
	while (!ipCheckOkay)
	{
		std::cout << "You wish to connect to : " << ip_ << "\nIs that right? (y/input ip)\n";
		std::cin >> input;
		if (input != "y")
		{
			if (input.size() >= 10 && input.size() <= 15)
			{
				if (input[3] != '.' && input[7] != '.' && (input[9] != '.' || input[10] != '.' || input[11] != '.'))
					std::cout << "Ip entered does not appear to be valid.";
				else
				{
					ip_ = input;
					std::cout << "\n\n";
				}
			}
			else
				std::cout << "Invalid ip Address, please try again\n\n"
				;
		}
		else
			ipCheckOkay = true;
	}


	while (!portCheckOkay)
	{
		std::cout << "\nYou wish to connect via port : " << port_
			<< "\nIs that right ? (y / input port number)"
			<< "\nBe aware that the default server port is 7777. Do not change unless specified by op.\n";
		std::cin >> input;
		if (input != "y")
		{
			bool portHasLetters = false;

			for (const char i : input)
				if (!isdigit(i))
					portHasLetters = true;

			if (!portHasLetters && (stoi(input) > 1024 && stoi(input) < 65536))
			{
				port_ = std::stoi(input);
				std::cout << "\n\n";
			}

			else
				std::cout << "Port is invalid or our of range, please select a port between 1024 and 65535\n\n";
		}
		else portCheckOkay = true;
	}
	std::cout << "\nIf the server is on, press (enter) to connect\n";
	std::cin.ignore();
	std::cin.get();
	std::cout << "Connecting...\n";
	const auto status = socket_.connect(ip_, port_, sf::seconds(10.0f));
	if (status != sf::Socket::Done)
	{
		std::cout << "\nError!: Request timed out\n\n";
		return;
	}

	std::cout << "Successfully connected\n\n";
	std::cout << "Waiting for another player to connect\n\n";

	if (socket_.receive(clientPacket_) == sf::Socket::Done)
	{
		std::cout << "Other player found\n";
		MyPacket packetState;
		clientPacket_ >> packetState;
		clientPacket_.clear();
		if (packetState.type == MyPacketType::BothConnected)
			state_ = ClientStates::AcceptMatch;
		else
			std::cout << "Package isn't the right type\n\n";
	}
	else
		std::cout << "Didn't receive package\n\n";
}

void Client::AcceptMatch()
{
	system("cls");
	DisplayScores();

	std::cout
		<< "\n\n\n"
		<< "                    [Join Match?]\n"
		<< "\n\n\n";

	std::cout << std::endl;
	std::cout << "Press (enter) to join match" << std::endl;
	std::cin.get();
	MyPacket myPacket(MyPacketType::Ready);
	clientPacket_ << myPacket;
	socket_.send(clientPacket_);
	clientPacket_.clear();
	state_ = ClientStates::AcceptMatchWaiting;
}

void Client::WaitingForOtherAccept()
{
	system("cls");
	DisplayScores();
	std::cout
		<< "\n\n\n"
		<< "                      [Accepted]"
		<< "\n\n\n\n";
	std::cout << std::endl << "Waiting for other player to accept..." << std::endl;

	if (socket_.receive(clientPacket_) == sf::Socket::Done)
	{
		bool loop = true;
		animationIterator_ = 0;
		myClock_.restart();
		while (loop == true)
		{
			if (myClock_.getElapsedTime().asSeconds() > 1.5)
			{
				system("cls");
				DisplayScores();
				if (animationIterator_ == 0)
				{
					std::cout
						<< "\n\n\n"
						<< "              [ROCK WINS OVER SCISSORS]"
						<< "\n\n\n\n\n";
				}
				if (animationIterator_ == 1)
				{
					std::cout
						<< "\n\n\n"
						<< "               [PAPER WINS OVER ROCK]"
						<< "\n\n\n\n\n";
				}
				if (animationIterator_ >= 2)
				{
					std::cout
						<< "\n\n\n"
						<< "              [SCISSORS WINS OVER PAPER]"
						<< "\n\n\n\n\n";
				}
				if(animationIterator_ == 3)
					loop = false;
				myClock_.restart();
				animationIterator_++;
			}
		}
		MyPacket packetState;
		clientPacket_ >> packetState;
		clientPacket_.clear();
		if (packetState.type == MyPacketType::YouPlay)
			state_ = ClientStates::Playing;
		else if (packetState.type == MyPacketType::YouWait)
			state_ = ClientStates::WaitingAsPlayer2;
		else
		{
			std::cout << "Package isn't the right type\n\n";
			return;
		}
	}
	else
		std::cout << "Didn't receive package\n\n";
	animationIterator_ = 0;
}

void Client::YourTurnInterface()
{
	system("cls");
	DisplayScores();
	std::string input;
	for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
	{
		std::cout << asc::UiRock[i] << asc::UiPaper[i] << asc::UiScissors[i] << std::endl;
	}

	std::cout << std::endl << "What do you want to play?" << std::endl;
	std::cin >> input;

	const RPSStates myMove = ChoseMove(input);

	if(myMove != RPSStates::None)
	{
		movePlayedForAnim2_.clear();
		movePlayedForAnim2_ = asc::AsciiToRpsState(myMove);

		movePlayedThisSet_ = myMove;

		const PlayedPacket myPacket(myMove);
		clientPacket_ << myPacket;
		socket_.send(clientPacket_);
		clientPacket_.clear();

		if (playedLast != true)
			state_ = ClientStates::WaitingAsPlayer1;
		else
		{
			playedLast = false;
			state_ = ClientStates::ClimaxAcceptMatch;
		}
	}
}

void Client::WaitingAsP1()
{
	if (myClock_.getElapsedTime().asSeconds() > 1)
	{
		std::cout << std::flush;
		system("cls");
		std::string idleString = "Waiting for opponent's turn";

		DisplayScores();

		if (animationIterator_ == 0)
		{
			idleString += ".";
			for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
			{
				std::cout << movePlayedForAnim2_.at(i) << "\t\t   " << GetAsciiArt(AsciiArt::EnemyRock)[i] << std::endl;
			}
		}
		if (animationIterator_ == 1)
		{
			idleString += "..";
			for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
			{
				std::cout << movePlayedForAnim2_.at(i) << "\t\t   " << GetAsciiArt(AsciiArt::EnemyPaper)[i] << std::endl;
			}
		}
		if (animationIterator_ == 2)
		{
			idleString += "...";
			for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
			{
				std::cout << movePlayedForAnim2_.at(i) << "\t\t   " << GetAsciiArt(AsciiArt::EnemyScissors)[i] << std::endl;
			}
		}

		

		std::cout << std::endl << idleString << std::endl;

		animationIterator_++;
		if (animationIterator_ > 2)
			animationIterator_ = 0;

		myClock_.restart();

	}
		socket_.setBlocking(false);
		if (socket_.receive(clientPacket_) == sf::Socket::Done)
		{
			socket_.setBlocking(false);
			MyPacket packetState;
			clientPacket_ >> packetState;
			if (packetState.type == MyPacketType::Results)
				state_ = ClientStates::ClimaxAcceptMatch;
		}
}

void Client::WaitingAsP2()
{
	if (myClock_.getElapsedTime().asSeconds() > 1)
	{
		std::cout << std::flush;
		system("cls");

		std::string idleString = "Waiting for opponent's turn";

		DisplayScores();

		if (animationIterator_ == 0)
		{
			idleString += ".";
			for (auto& UiRock : asc::UiRock)
			{
				std::cout << UiRock << "                    " << "                  " << std::endl;
			}
		}
		if (animationIterator_ == 1)
		{
			idleString += "..";
			for (auto& Paper : asc::UiPaper)
			{
				std::cout << "               " << Paper << "                  " << std::endl;
			}
		}
		if (animationIterator_ == 2)
		{
			idleString += "...";
			for (auto& UiScissor : asc::UiScissors)
			{
				std::cout << "               " << "                    " << UiScissor << std::endl;
			}
		}

		std::cout << std::endl << idleString << std::endl;

		animationIterator_++;
		if (animationIterator_ > 2)
			animationIterator_ = 0;

		myClock_.restart();

	}
		socket_.setBlocking(false);
		if (socket_.receive(clientPacket_) == sf::Socket::Done)
		{
			socket_.setBlocking(true);
			MyPacket packetState;
			clientPacket_ >> packetState;
			clientPacket_.clear();
			if (packetState.type == MyPacketType::YouPlay)
				state_ = ClientStates::Playing;
			else
				std::cout << "\nError : Package isn't the right type\n\n";
		}

}

void Client::SetClimax()
{
	if (socket_.receive(clientPacket_) == sf::Socket::Done)
	{
		socket_.setBlocking(true);
		ResultsPacket endSetPacket;
		clientPacket_ >> endSetPacket;
		clientPacket_.clear();


		auto yourMove = asc::AsciiToRpsState(movePlayedThisSet_);
		auto theirMove = asc::AsciiToRpsState(static_cast<RPSStates>(endSetPacket.theirMove), true);
		RPSScore score = GameRules::Score(movePlayedThisSet_, endSetPacket.theirMove);

		std::vector<std::string> ascScore;
		if (score == RPSScore::DRAW)
			for (auto& i : asc::ScoreDraw)
				ascScore.emplace_back(i);
		if (score == RPSScore::WIN)
			for (auto& i : asc::ScoreWin)
				ascScore.emplace_back(i);
		if (score == RPSScore::LOSE)
			for (auto& i : asc::ScoreLose)
				ascScore.emplace_back(i);


		bool loop = true;
		int animationIterator_ = 0;
		while (loop == true)
		{
			if (myClock_.getElapsedTime().asSeconds() > 1.5)
			{
				system("cls");
				DisplayScores();
				if (animationIterator_ == 0)
				{
					std::cout
						<< "\n\n\n"
						<< "              [ROCK WINS OVER SCISSORS]"
						<< "\n\n\n\n\n\n";
				}
				if (animationIterator_ == 1)
				{
					std::cout
						<< "\n\n\n"
						<< "               [PAPER WINS OVER ROCK]"
						<< "\n\n\n\n\n\n";
				}
				if (animationIterator_ == 2)
				{
					std::cout
						<< "\n\n\n"
						<< "              [SCISSORS WINS OVER PAPER]"
						<< "\n\n\n\n\n\n";
				}
				if (animationIterator_ >= 3)
				{
					for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
					{
						std::cout << yourMove.at(i) << "\t\t   " << theirMove.at(i) << std::endl;
					}
				}
				if (animationIterator_ == 6)
				{
					loop = false;
				}
				myClock_.restart();
				animationIterator_++;
			}
		}
		system("cls");
		if (score == RPSScore::WIN)
			displayYourScore_++;
		if (score == RPSScore::LOSE)
			displayTheirScore_++;
		DisplayScores();
		std::cout << std::endl;
		for (const auto& line : ascScore)
		{
			std::cout << line << std::endl;
		}
		std::cout << std::endl << std::endl;
		std::cout
			<< "                    [PLAY AGAIN?]"
			<< std::endl
			<< "                       (enter)"
			<< std::endl;
		std::cin.ignore();
		std::cin.get();

		MyPacket myPacket(MyPacketType::Ready);
		clientPacket_ << myPacket;
		socket_.send(clientPacket_);
		state_ = ClientStates::AcceptMatchWaiting;
	}
}

RPSStates Client::ChoseMove(const std::string myMove) const
{
	if (myMove == std::to_string('r') || myMove == std::to_string(1) ||
		myMove == "Rock" || myMove == "ROCK" || myMove == "rock")
		return RPSStates::ROCK;
	else if (myMove == std::to_string('p') || myMove == std::to_string(2) ||
		myMove == "Paper" || myMove == "PAPER" || myMove == "paper")
		return RPSStates::PAPER;
	else if (myMove == std::to_string('s') || myMove == std::to_string(3) ||
		myMove == "Scissors" || myMove == "SCISSORS" || myMove == "scissors")
		return RPSStates::SCISSORS;
	else
		return RPSStates::None;

}