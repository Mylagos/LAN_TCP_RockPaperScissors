#pragma once
#include <iostream>
#include "client.h"
#include "AsciiArt.h"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"

namespace temp
{
    void FancyWaitingAnimation()
    {
        sf::Clock clock;
        bool loop = true;
        int i = 0;
        while (loop)
        {
            if (clock.getElapsedTime().asSeconds() > 1)
            {
                std::cout << std::flush;
                system("cls");
                std::string idleString = "Waiting for opponent's turn";

                std::cout << "Your score : 0\t\t\t Opponent's score : 0" << std::endl << std::endl;

                if (i == 0)
                    for (auto j : asc::UiRock)
                        std::cout << j << std::endl; idleString += ".";
                if (i == 1)
                    for (auto j : asc::UiPaper)
                        std::cout << j << std::endl; idleString += "..";
                if (i == 2)
                    for (auto j : asc::UiScissors)
                        std::cout << j << std::endl; idleString += "...";

                std::cout << std::endl << idleString << std::endl;

                i++;
                if (i > 2)
                    i = 0;

                clock.restart();
            }

        }
    }

    void YourTurnInterface()
    {
        std::cout << "Your score : 0\t\t\t Opponent's score : 0" << std::endl << std::endl;
        for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
        {
            std::cout << asc::UiRock[i] << asc::UiPaper[i] << asc::UiScissors[i] << std::endl;
        }
        //OPTIONAL MIGHT DELETE DEPENDING ON IMPLEMENTATION
        std::cout << std::endl << "What do you want to use?" << std::endl;
    }

    void WaitingAsP2()
    {
        std::cout << "Your score : 0\t\t\t Opponent's score : 0" << std::endl << std::endl;
        sf::Clock clock;
        bool loop = true;
        int i = 0;
        while (loop)
        {
            if (clock.getElapsedTime().asSeconds() > 1)
            {
                std::cout << std::flush;
                system("cls");
                std::string idleString = "Waiting for opponent's turn";

                std::cout << "Your score : 0\t\t\t Opponent's score : 0" << std::endl << std::endl;

                if (i == 0)
                {
                    idleString += ".";
                    for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
                    {
                        std::cout << asc::UiRock[i] << "                    " << "                  " << std::endl;
                    }
                }
                if (i == 1)
                {
                    idleString += "..";
                    for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
                    {
                        std::cout << "               " << asc::UiPaper[i] << "                  " << std::endl;
                    }
                }
                if (i == 2)
                {
                    idleString += "...";
                    for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
                    {
                        std::cout << "               " << "                    " << asc::UiScissors[i] << std::endl;
                    }
                }

                std::cout << std::endl << idleString << std::endl;

                i++;
                if (i > 2)
                    i = 0;

                clock.restart();
            }
        }
    }

    void WaitingAsP1(RPSStates myMove)
    {
        sf::Clock clock;
        bool loop = true;
        int i = 0;
        std::vector<std::string>  yourMove = asc::AsciiToRpsState(myMove);
        while (loop)
        {
            if(clock.getElapsedTime().asSeconds() > 1)
            {
                std::cout << std::flush;
                system("cls");
        		std::string idleString = "Waiting for opponent's turn";

                std::cout << "Your score : 0\t\t\t Opponent's score : 0" << std::endl << std::endl;

                if (i == 0)
                {
                    idleString += ".";
                    for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
                    {
                        std::cout << yourMove.at(i) << "\t\t   " << GetAsciiArt(AsciiArt::EnemyRock)[i] << std::endl;
                    }
                }
                if (i == 1)
                {
                    idleString += "..";
                    for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
                    {
                        std::cout << yourMove.at(i) << "\t\t   " << GetAsciiArt(AsciiArt::EnemyPaper)[i] << std::endl;
                    }
                }
                if (i == 2)
                {
                    idleString += "...";
                    for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
                    {
                        std::cout << yourMove.at(i) << "\t\t   " << GetAsciiArt(AsciiArt::EnemyScissors)[i] << std::endl;
                    }
                }

				std::cout << std::endl << idleString << std::endl;

				i++;
                if (i > 2)
                    i = 0;

                clock.restart();
            }
        }
    }

    void DisplayScores()
    {
        std::cout << "Your score : 0\t\t\t Opponent's score : 0" << std::endl << std::endl;
    }

    void SetClimax(RPSStates myMove, RPSStates enemyMove)
    {
        sf::Clock clock;
        auto yourMove = asc::AsciiToRpsState(myMove);
        auto theirMove = asc::AsciiToRpsState(enemyMove, true);
        RPSScore score = GameRules::Score(myMove, enemyMove);

        std::vector<std::string> ascScore;
        if(score == RPSScore::DRAW)
            for (int i = 0; i < 5; i++)
                ascScore.emplace_back(asc::ScoreDraw[i]);
        if (score == RPSScore::WIN)
            for (int i = 0; i < 5; i++)
                ascScore.emplace_back(asc::ScoreWin[i]);
        if (score == RPSScore::LOSE)
            for (int i = 0; i < 5; i++)
                ascScore.emplace_back(asc::ScoreLose[i]);
            

        bool loop = true;
        int i = 0;
        while (loop == true)
        {
	        if (clock.getElapsedTime().asSeconds() > 1.5)
	        {
                system("cls");
                DisplayScores();
                if (i==0)
                {
                	std::cout
						<< "\n\n\n"
						<< "               [PAPER WINS OVER ROCK]"
						<< "\n\n\n";
                }
                if (i == 1)
                {
                    std::cout
                        << "\n\n\n"
                        << "              [ROCK WINS OVER SCISSORS]"
                        << "\n\n\n";
                }
                if (i == 2)
                {
                    std::cout
                        << "\n\n\n"
                        << "              [SCISSORS WINS OVER PAPER]"
                        << "\n\n\n";
                }
                if (i==3)
                {
                    for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
                    {
                        std::cout << yourMove.at(i) << "\t\t   " << theirMove.at(i) << std::endl;
                    }
                }
                if (i == 4)
                {
                    for (int i = 0; i < sizeof(&asc::UiPaper) - 1; i++)
                    {
                        std::cout << yourMove.at(i) << "\t\t   " << theirMove.at(i) << std::endl;
                    }
                    loop = false;
                }
                clock.restart();
                i++;
	        }
        }
        system("cls");
        DisplayScores();
        std::cout << std::endl;
        for (int i = 0; i < 5 ; i++)
        {
            std::cout << ascScore.at(i) << std::endl;
        }
        std::cout << std::endl << std::endl;
        std::cout << "Press enter to play again" << std::endl;
        std::cin.get();
    }

    void WaitForSetStart()
    {
        DisplayScores();
        
        std::cout
            << "\n\n\n"
        	<< "                    [Join Match?]"
            << "\n\n\n";
        
        std::cout << std::endl;
        std::cout << "Press (enter) to join match" << std::endl;
        std::cin.get();
        system("cls");
        DisplayScores();
        std::cout
            << "\n\n\n"
            << "                      [Accepted]"
            << "\n\n\n";
        std::cout << "Waiting for other player to accept..." << std::endl;
        std::cin.get();
    }
}