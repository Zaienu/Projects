#include "Definitions.h"
#include "GameData.h"
#include "HighScores.h"
#include "Button.h"
#include "SpriteManager.h"
#include "Scores.h"

void Load_HighScores();
void Update_HighScores();
void Display_HighScores();
void Unload_HighScores();

void HighScores()
{
	GameData* GD = GameData::Get_Instance();
	Load_HighScores();
	while (GD->m_state == HIGHSCORES)
	{
		Update_HighScores();
		Display_HighScores();
	}
	Unload_HighScores();
}

void Load_HighScoresBackground()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteSettings bgHS =
	{
		"GameStates/Scores/Background",
		"Scores_Background",
		false,
		{1,1}
	};
	GD->m_hsBG = bgHS.name;
	Sprite->FillVectors(bgHS);
}

void Load_HighScoresFrame()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteSettings frameHS =
	{
		"GameStates/Scores/Frame",
		"Scores_Frame",
		false,
		{1,1}
	};
	GD->m_hsFrame = frameHS.name;
	Sprite->FillVectors(frameHS);
}

void Load_HighScoresButtons(std::string _button, sf::Vector2f _pos)
{
	GameData* GD = GameData::Get_Instance();
	ButtonSettings buttonSettings =
	{
		{"GameStates/Menus/Buttons/" + _button + "ButtonIdle", "GameStates/Menus/Buttons/" + _button + "ButtonHovered"},
		{ _button + "_ButtonIdle", _button + "_ButtonHovered" },
		{ "Click", "Hover"},
		{ _pos.x, _pos.y},
	};
	Button* button = new Button(buttonSettings);
	GD->m_buttons.push_back(button);
}

void Goto_Menu2();

void Load_HighScoresActions()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_buttonsActions.clear();
	GD->m_buttonsActions.resize(1);
	GD->m_buttonsActions = { Goto_Menu2 };
}

void Load_HighScores()
{
	GameData* GD = GameData::Get_Instance();
	Load_HighScoresBackground();
	Load_HighScoresFrame();
	Load_HighScoresButtons("Back", { SWIDTH - 125, SHEIGHT - 50});
	Load_HighScoresActions();
}

void Goto_Menu2()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_state = MENU;
}

void Press_HighScoresButtons()
{
	GameData* GD = GameData::Get_Instance();

	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->MousePressed(GD->m_buttonsActions[i]);
	}

}

void MousePressed_HighScores(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.mouseButton.button == sf::Mouse::Left)
	{
		Press_HighScoresButtons();
	}
	else if (_event.mouseButton.button == sf::Mouse::Right)
	{

	}
}

void Hover_HighScoresButtons(sf::Vector2i _mousePos)
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->MouseMoved(_mousePos);
	}
}

void MouseMoved_HighScores(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	sf::Vector2i mousePos;
	mousePos = sf::Mouse::getPosition(GD->m_window);
	Hover_HighScoresButtons(mousePos);
}

void KeyPressed_HighScores(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.key.code == sf::Keyboard::A)
	{
		GD->m_state = GAMEOVER;
	}
}

void Update_HighScoresButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->Update();
	}
}

void Update_HighScores()
{
	GameData* GD = GameData::Get_Instance();
	sf::Event event;
	while (GD->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			MousePressed_HighScores(event);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			KeyPressed_HighScores(event);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			MouseMoved_HighScores(event);
		}
		if (event.type == sf::Event::Closed)
		{
			GD->m_window.close();
		}
		//Events
	}
	GD->m_frameTime = GD->m_clock.restart().asSeconds();
	Update_HighScoresButtons();
	//Update RT
}

void Display_HighScorePicture(std::string _name)
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteDrawParameters pictureParameters =
	{
		_name,
		0,
		{0,0},
		&GD->m_window
	};
	Sprite->BlitSprite(pictureParameters);
}

void Display_HighScoresButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->Display();
	}
}

void Display_HighScores()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_window.clear(sf::Color::Magenta);
	//Display
	Display_HighScorePicture(GD->m_hsBG);
	Display_HighScorePicture(GD->m_hsFrame);
	Display_HighScoresButtons();
	Scores::Display();
	GD->m_window.display();
}

void Unload_HighScoresButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->~Button();
	}
	GD->m_buttons.clear();
}

void Unload_HighScores()
{
	GameData* GD = GameData::Get_Instance();
	Unload_HighScoresButtons();
}