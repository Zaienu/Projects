#include "Definitions.h"
#include "GameData.h"
#include "Victory.h"

void Load_Victory();
void Update_Victory();
void Display_Victory();
void Unload_Victory();

void Victory()
{
	GameData* GD = GameData::Get_Instance();
	Load_Victory();
	while (GD->m_state == VICTORY)
	{
		Update_Victory();
		Display_Victory();
	}
	Unload_Victory();
}

void Load_Victory()
{
	GameData* GD = GameData::Get_Instance();
}

void MousePressed_Victory(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.mouseButton.button == sf::Mouse::Left)
	{

	}
	else if (_event.mouseButton.button == sf::Mouse::Right)
	{

	}
}

void MouseMoved_Victory(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();
}

void KeyPressed_Victory(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.key.code == sf::Keyboard::A)
	{
		GD->m_state = MENU;
	}
}

void Update_Victory()
{
	GameData* GD = GameData::Get_Instance();
	sf::Event event;
	while (GD->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			MousePressed_Victory(event);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			KeyPressed_Victory(event);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			MouseMoved_Victory(event);
		}
		if (event.type == sf::Event::Closed)
		{
			GD->m_window.close();
		}
		//Events
	}
	//Update RT
}

void Display_Victory()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_window.clear(sf::Color::Cyan);
	//Display
	GD->m_window.display();
}

void Unload_Victory()
{
	GameData* GD = GameData::Get_Instance();
}