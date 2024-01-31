#include "Definitions.h"
#include "GameData.h"
#include "Game.h"
#include "SpriteManager.h"
#include "GameplayManager.h"

void Load_Game();
void Update_Game();
void Display_Game();
void Unload_Game();

void Game()
{
	GameData* GD = GameData::Get_Instance();
	Load_Game();
	while (GD->m_state == GAME)
	{
		Update_Game();
		Display_Game();
	}
	Unload_Game();
}

void Load_Gameplay()
{
	GameData* GD = GameData::Get_Instance();
	GameplayManager* gameplay = new GameplayManager();
	GD->m_Gameplay.push_back(gameplay);
}

void Load_Game()
{
	GameData* GD = GameData::Get_Instance();
	Load_Gameplay();
}

void MousePressed_Game(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	GD->m_Gameplay[0]->MousePressed(_event);
}

void MouseMoved_Game(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();
	GD->m_Gameplay[0]->MouseMoved(_event);
}

void KeyPressed_Game(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	GD->m_Gameplay[0]->KeyPressed(_event);

	if (_event.key.code == sf::Keyboard::A)
	{
		GD->m_state = GAMEOVER;
	}
}

void Update_Game()
{
	GameData* GD = GameData::Get_Instance();
	sf::Event event;
	while (GD->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			MousePressed_Game(event);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			KeyPressed_Game(event);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			MouseMoved_Game(event);
		}
		if (event.type == sf::Event::Closed)
		{
			GD->m_window.close();
		}
		//Events
	}
	GD->m_frameTime = GD->m_clock.restart().asSeconds();
	GD->m_Gameplay[0]->Update();
	//Update RT
}

void Display_Gameplay()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_Gameplay[0]->Display();
}

void Display_Game()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_window.clear(sf::Color::Green);
	//Display
	Display_Gameplay();
	GD->m_window.display();
}

void Unload_Game()
{
	GameData* GD = GameData::Get_Instance();
	delete GD->m_Gameplay[0];
	GD->m_Gameplay.clear();
}