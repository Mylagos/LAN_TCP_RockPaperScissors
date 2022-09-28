#pragma once

enum class AsciiArt : int
{
	None = 0,
	YourRock = 1,
	YourPaper = 2,
	YourScissors = 3,
	EnemyRock = 4,
	EnemyPaper = 5,
	EnemyScissors = 6
};


inline static const char** GetAsciiArt(AsciiArt value) {
	switch (value) {
	case AsciiArt::None:
		return nullptr;
	case AsciiArt::YourRock:
		{
			static const char* YourRock[7] = {
				"    _______       ",
				"---'   ____)      ",
				"      (_____)     ",
				"      (_____)     ",
				"      (____)      ",
				"---.__(___)       ",
				"   1.Rock         "
				};
			return YourRock;
		}
	case AsciiArt::YourPaper:
		{
			static const char* YourPaper[7] = {
				"    _______       ",
				"---'   ____)____  ",
				"          ______) ",
				"          _______)",
				"         _______) ",
				"---.__________)   ",
				"   2.Paper       "
				};
			return YourPaper;
		}
	case AsciiArt::YourScissors:
		{
			static const char* YourScissors[7] = {
				"    _______       ",
				"---'   ____)____  ",
				"          ______) ",
				"       __________)",
				"      (____)      ",
				"---.__(___)       ",
				"  3.Scissors      "
				};
			return YourScissors;
		}
	case AsciiArt::EnemyRock:
		{
			static const char* EnemyRock[7] = {
				"       _______    ",
				"      (____   '---",
				"     (_____)      ",
				"     (_____)      ",
				"      (____)      ",
				"       (___)__.---",
				"         1.Rock   "
				};
			return EnemyRock;
		}
	case AsciiArt::EnemyPaper:
		{
			static const char* EnemyPaper[7] = {
				"       _______    ",
				"  ____(____   '---",
				" (______          ",
				"(_______          ",
				" (_______         ",
				"   (__________.---",
				"        2.Paper   "
				};
			return EnemyPaper;
		}
	case AsciiArt::EnemyScissors:
		{
			static const char* EnemyScissors[7] = {
				"       _______    ",
				"  ____(____   '---",
				" (______          ",
				"(__________       ",
				"      (____)      ",
				"       (___)__.---",
				"      3.Scissors  "
				};
			return EnemyScissors;
		}
	}
}


namespace asc
{
	static std::vector<std::string> AsciiToRpsState(RPSStates rpsState)
	{
		auto ascii = static_cast<AsciiArt>(rpsState);
		std::vector<std::string> yourMove;
		for (int i = 0; i < 7; i++)
		{
			yourMove.emplace_back(static_cast<std::string>(GetAsciiArt(ascii)[i]));
		}
		return yourMove;
	}

	static std::vector<std::string> AsciiToRpsState(RPSStates rpsState, bool isEnemy)
	{
		int enemy = 3 + static_cast<int>(rpsState);
		AsciiArt ascii = static_cast<AsciiArt>(enemy);
		std::vector<std::string> yourMove;
		for (int i = 0; i < 7; i++)
		{
			yourMove.emplace_back(static_cast<std::string>(GetAsciiArt(ascii)[i]));
		}
		return yourMove;
	}

	inline const char* UiRock[7] = {
		"    _______    ",
		"---'   ____)   ",
		"      (_____)  ",
		"      (_____)  ",
		"      (____)   ",
		"---.__(___)    ",
		" 1.Rock (r)    "
	};
	inline const char* UiPaper[7] = {
		"    _______         ",
		"---'   ____)____    ",
		"          ______)   ",
		"          _______)  ",
		"         _______)   ",
		"---.__________)     ",
		"  2.Paper (p)       "
	};
	inline const char* UiScissors[7] = {
		"    _______       ",
		"---'   ____)____  ",
		"          ______) ",
		"       __________)",
		"      (____)      ",
		"---.__(___)       ",
		" 3.Scissors (s)   "
	};

	inline const char* ScoreWin[11] = {
		"       ooooo  oooo",
		"         888  88 ooooooo  oooo  oooo",
		"           888 888     888 888   888",
		"           888 888     888 888   888",
		"          o888o  88ooo88    888o88 8o",
		"",
		"       oooo     oooo                      oo ",
		"        88   88  88  ooooooo  oo oooooo  8888 ",
		"         88 888 88 888     888 888   888 8888 ",
		"          888 888  888     888 888   888  88  ",
		"           8   8     88ooo88  o888o o888o oo  "
	};
	inline const char* ScoreLose[11] = {
		"      ooooo  oooo                                     ",
		"        888  88 ooooooo  oooo  oooo                   ",
		"          888 888     888 888   888                   ",
		"          888 888     888 888   888                   ",
		"         o888o  88ooo88    888o88 8o                  ",
		"                                                      ",
		"      ooooo                                o8   ",
		"       888          ooooooo    oooooooo8 o888oo ",
		"       888        888     888 888ooooooo  888   ",
		"       888      o 888     888         888 888   ",
		"      o888ooooo88   88ooo88   88oooooo88   888o"
	};
	inline const char* ScoreDraw[5] = {
		"   ooooooooo                                       ",
		"    888    88o oo oooooo   ooooooo oooo  o  oooo   ",
		"    888    888  888    888 ooooo888 888 888 888    ",
		"    888    888  888      888    888  888888888 ooo ",
		"   o888ooo88   o888o      88ooo88 8o  88   88  888 "
	};

}