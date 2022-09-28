#pragma once

enum class RPSStates
{
	None=0,
	ROCK,
	PAPER,
	SCISSORS
};
enum class RPSScore
{
	DRAW = 0,
	WIN = 1,
	LOSE = 2
};

class GameRules
{
private:
	int player1Score_;
	int player2Score_;
public:
	static RPSScore Score(RPSStates uno, RPSStates dos);
};