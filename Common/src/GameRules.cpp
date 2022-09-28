#include"GameRules.h"

RPSScore GameRules::Score(RPSStates uno, RPSStates dos)
{
	if (uno == RPSStates::ROCK && dos == RPSStates::SCISSORS)
		return RPSScore::WIN;
	if (uno == RPSStates::SCISSORS && dos == RPSStates::PAPER)
		return RPSScore::WIN;
	if (uno == RPSStates::PAPER && dos == RPSStates::ROCK)
		return RPSScore::WIN;
	if (uno == RPSStates::ROCK && dos == RPSStates::ROCK)
		return RPSScore::DRAW;
	if (uno == RPSStates::SCISSORS && dos == RPSStates::SCISSORS)
		return RPSScore::DRAW;
	if (uno == RPSStates::PAPER && dos == RPSStates::PAPER)
		return RPSScore::DRAW;
	else
		return RPSScore::LOSE;
}