#include "Definitions.h"
#include "GameData.h"
#include "Menu.h"

#include "SoundManager.h"
#include "TextManager.h"
#include "SpriteManager.h"
#include "Button.h"

void Load_Menu();
void Update_Menu();
void Display_Menu();
void Unload_Menu();

void Menu()
{
	GameData* GD = GameData::Get_Instance();
	Load_Menu();
	while (GD->m_state == MENU)
	{
		Update_Menu();
		Display_Menu();
	}
	Unload_Menu();
}

void Menu_LoadTheme()
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	Sound->FillVectors(MUSIC, "MenuMusic");
	Sound->ManageMusic("MenuMusic", true);
	Sound->SetMusicLoop("MenuMusic", true);
}

void Load_MenuBackground()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteSettings bgMenu =
	{
		"GameStates/Menus/Background",
		"Menu_Background",
		false,
		{1,1}
	};
	GD->m_menuBG = bgMenu.name;
	Sprite->FillVectors(bgMenu);
}

void Load_MenuButtons(std::string _button, int _pos)
{
	GameData* GD = GameData::Get_Instance();
	ButtonSettings buttonSettings =
	{
		{"GameStates/Menus/Buttons/" + _button + "ButtonIdle", "GameStates/Menus/Buttons/" + _button + "ButtonHovered"},
		{ _button +"_ButtonIdle", _button + "_ButtonHovered" },
		{ "Click", "Hover"},
		{ 800, (float)(200 + 100 * _pos)},
	};
	Button* button = new Button(buttonSettings);
	GD->m_buttons.push_back(button);
}

void Load_Selector(std::string _button, sf::Vector2f _pos)
{
	GameData* GD = GameData::Get_Instance();
	ButtonSettings buttonSettings =
	{
		{"GameStates/Menus/Buttons/" + _button + "ArrowIdle", "GameStates/Menus/Buttons/" + _button + "ArrowHovered"},
		{ _button + "_ButtonIdle", _button + "_ButtonHovered" },
		{ "Click", "Hover"},
		{ _pos},
	};
	Button* button = new Button(buttonSettings);
	GD->m_buttons.push_back(button);
}

void Goto_Game();
void Goto_Settings();
void Goto_HighScores();
void Leave_Game();
void More_Players();
void Less_Players();

void Load_MenuActions()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_buttonsActions.clear();
	GD->m_buttonsActions.resize(6);
	GD->m_buttonsActions = { Goto_Game, Goto_Settings, Goto_HighScores, Leave_Game, More_Players, Less_Players };
}


void Load_Menu()
{
	GameData* GD = GameData::Get_Instance();
	Load_MenuBackground();
	Load_MenuButtons("Play", 0);
	Load_MenuButtons("Settings", 1);
	Load_MenuButtons("HighScores", 2);
	Load_MenuButtons("Quit", 3);
	Load_Selector("Up", { 600, 150 });
	Load_Selector("Down", { 600, 250 });
	Load_MenuActions();
	Menu_LoadTheme();
}

void Goto_Game()
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	Sound->ManageMusic("MenuMusic", false);
	GD->m_state = GAME;

}

void Goto_Settings()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_state = SETTINGS;
}

void Goto_HighScores()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_state = HIGHSCORES;
}

void Leave_Game()
{
	GameData* GD = GameData::Get_Instance();
	exit(0);
}

void More_Players()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_playerNb++;
	GD->m_playerNb > 4 ? GD->m_playerNb = 4 : NULL;
}

void Less_Players()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_playerNb--;
	GD->m_playerNb < 2 ? GD->m_playerNb = 2 : NULL;
}

void Press_MenuButtons()
{
	GameData* GD = GameData::Get_Instance();

	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->MousePressed(GD->m_buttonsActions[i]);
	}

}

void MousePressed_Menu(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.mouseButton.button == sf::Mouse::Left)
	{
		Press_MenuButtons();
	}
	else if (_event.mouseButton.button == sf::Mouse::Right)
	{

	}
}

void Hover_MenuButtons(sf::Vector2i _mousePos)
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->MouseMoved(_mousePos);
	}
}

void MouseMoved_Menu(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	sf::Vector2i mousePos;
	mousePos = sf::Mouse::getPosition(GD->m_window);
	Hover_MenuButtons(mousePos);
}

void KeyPressed_Menu(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.key.code == sf::Keyboard::A)
	{
		GD->m_state = GAME;
	}
}

void Update_MenuButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->Update();
	}
}

void Update_Menu()
{
	GameData* GD = GameData::Get_Instance();
	sf::Event event;
	while (GD->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			MousePressed_Menu(event);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			KeyPressed_Menu(event);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			MouseMoved_Menu(event);
		}
		if (event.type == sf::Event::Closed)
		{
			GD->m_window.close();
		}
		//Events
	}
	//Update RT
	GD->m_frameTime = GD->m_clock.restart().asSeconds();
	Update_MenuButtons();
}

void Display_MenuBackground()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteDrawParameters bgParameters =
	{
		GD->m_menuBG,
		0,
		{0, 0},
		&GD->m_window
	};
	Sprite->BlitSprite(bgParameters);
}

void Display_MenuButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->Display();
	}
}

void Display_PlayerNumber()
{
	GameData* GD = GameData::Get_Instance();
	TextManager* Text = TextManager::Get_Instance();
	TextSettings textSettings =
	{
		"Poggers-Bold",
		"Player_Number",
		sf::Color::Cyan,
		50
	};
	Text->FillVectors(textSettings);
	Text->SetString(textSettings.name, std::to_string(GD->m_playerNb));
	TextDrawParameters textDraw =
	{
		textSettings.name,
		0,
		{590, 165},
		&GD->m_window
	};
	Text->BlitText(textDraw);
}

void Display_Menu()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_window.clear(sf::Color::Red);
	//Display
	Display_MenuBackground();
	Display_MenuButtons();
	Display_PlayerNumber();
	GD->m_window.display();
}

void Unload_MenuButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->~Button();
	}
	GD->m_buttons.clear();
}

void Unload_Menu()
{
	GameData* GD = GameData::Get_Instance();
	Unload_MenuButtons();
}