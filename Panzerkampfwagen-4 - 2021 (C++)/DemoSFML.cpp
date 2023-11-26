#include "Definitions.h"
#include "GameData.h"

#include "Scores.h"
#include "Menu.h"
#include "Settings.h"
#include "HighScores.h"
#include "Game.h"
#include "GameOver.h"
#include "Victory.h"

int main()
{
	GameData* GD = GameData::Get_Instance();
	std::srand((unsigned int)time(NULL)); rand(); rand(); rand();
	GD->m_window.create(sf::VideoMode(SWIDTH, SHEIGHT), "PANZERKAMPFWAGEN-IV", sf::Style::Default);
	GD->m_clock;
	Scores::LoadScoreFile();
	while (GD->m_window.isOpen())
	{
		switch (GD->m_state)
		{
		case MENU: Menu(); break;
		case SETTINGS: Settings(); break;
		case HIGHSCORES: HighScores(); break;
		case GAME: Game(); break;
		case GAMEOVER: GameOver(); break;
		default: std::cout << "Error in the Main's Switch" << std::endl; break;
		}
	}

}
