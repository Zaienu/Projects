#ifndef GAMEDATA__H
#define GAMEDATA__H

#include "definitions.h"

class Player;
class Map;
class ParticleManager;
class Button;
class Scores;
class GameplayManager;

class GameData
{
private:
	GameData();
	~GameData();

public:
	static GameData* Get_Instance();

	States m_state = MENU;

	sf::Clock m_clock;
	sf::RenderWindow m_window;
	sf::Event m_event;
	float m_frameTime;

	std::vector <void (*)()> m_buttonsActions;
	std::vector <Button*> m_buttons;

	//Managers
	ParticleManager* m_ParticleManager;
	/// <MENU>
	std::string m_menuBG;
	/// </MENU>

	/// <GAME>
	std::vector <GameplayManager*> m_Gameplay;
	sf::Vector2f m_wind;
	std::vector <int> m_scores;
	int m_playerNb = 4;
	//Caméra basique
	float m_camX;
	float m_camY;
	/// </GAME>

	/// <SETTINGS>
	std::string m_settingsBG;
	std::string m_settingsBar;
	std::string m_settingsFrame;
	/// </SETTINGS>

	/// <HIGHSCORES>
	std::string m_hsBG;
	std::string m_hsFrame;
	std::vector <Scores*> m_scoreList;
	/// </HIGHSCORES>

	/// GAMEOVER
	std::string m_goBG;
	std::vector <std::string> m_playerText;
	std::vector <InputBox*> m_InputBoxes;
	int m_boxId = NULL;
	/// </GAMEOVER>


};


#endif