#pragma once
#include <iostream>
#include "client.h"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"

#include "TempFunctions.h"

int main()
{
    //std::cout << "Hello World !\n";
    Client client;
    client.Run();
    /*std::cout << "Your score : 0\t\t\t Opponent's score : 0" << std::endl << std::endl;
    for (int i = 0; i < sizeof(&asc::YourRock) - 2; i++)
    {
        std::cout << asc::YourPaper[i] << "\t\t" << asc::TheirRock[i] << std::endl;
    }
    std::cout << std::endl << std::endl << "Paper wins over the rock!" << std::endl
		<< "Press (enter) to continue" << std::endl;
    std::string ooo;
	std::cin >> ooo;*/
    //Client ooo;
    //ooo.StartupInterface();
    return EXIT_SUCCESS;
}