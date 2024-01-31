#include "Definitions.h"
#include "GameData.h"
#include "GameOver.h"
#include "Scores.h"

#include "SoundManager.h"
#include "TextManager.h"
#include "SpriteManager.h"
#include "Button.h"

void Load_GameOver();
void Update_GameOver();
void Display_GameOver();
void Unload_GameOver();

void GameOver()
{
	GameData* GD = GameData::Get_Instance();
	Load_GameOver();
	while (GD->m_state == GAMEOVER)
	{
		Update_GameOver();
		Display_GameOver();
	}
	Unload_GameOver();
}

void Load_GameOverTheme()
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	Sound->FillVectors(MUSIC, "MenuMusic");
	Sound->ManageMusic("MenuMusic", true);
	Sound->SetMusicLoop("MenuMusic", true);
}

void Load_GameOverBackground()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteSettings bgGameOver =
	{
		"GameStates/Victory/Background",
		"GameOver_Background",
		false,
		{1,1}
	};
	GD->m_goBG = bgGameOver.name;
	Sprite->FillVectors(bgGameOver);
}

void Load_GameOverButtons(std::string _button, sf::Vector2f _pos)
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

void Goto_Menu3();

void Load_GameOverActions()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_buttonsActions.clear();
	GD->m_buttonsActions.resize(1);
	GD->m_buttonsActions = { Goto_Menu3 };
}

void Load_InputBoxes(sf::Vector2f _pos)
{
	GameData* GD = GameData::Get_Instance();
	GD->m_InputBoxes.clear();
	for (int i = 0; i < GD->m_playerNb; i++)
	{
		sf::RectangleShape rectangle;
		rectangle.setSize({ 200, 50 });
		rectangle.setPosition({ _pos.x, _pos.y + 75 * i });
		rectangle.setFillColor(sf::Color::White);
		rectangle.setOutlineThickness(4);

		InputBox* inputBox = new InputBox();
		inputBox->rectangle = rectangle;
		inputBox->edit = false;
		inputBox->currentWord = "INPUT NAME..";

		GD->m_InputBoxes.push_back(inputBox);
	}
}

void Load_PlayersText()
{
	GameData* GD = GameData::Get_Instance();
	TextManager* Text = TextManager::Get_Instance();
	for (int i = 0; i < GD->m_playerNb; i++)
	{
		TextSettings textSettings =
		{
			"Poggers-Bold",
			"Player" + std::to_string(i),
			sf::Color::Black,
			25
		};
		Text->FillVectors(textSettings);
		GD->m_playerText.push_back(textSettings.name);
	}
}

void Load_GameOver()
{
	GameData* GD = GameData::Get_Instance();
	Load_GameOverBackground();
	Load_GameOverButtons("Menu", { SWIDTH - 125, SHEIGHT - 50 });
	Load_InputBoxes({(float)(SWIDTH/2 - 100), SHEIGHT/2});
	Load_GameOverActions();
	Load_PlayersText();
	Load_GameOverTheme();
}

void Goto_Menu3()
{
	GameData* GD = GameData::Get_Instance();
	Scores::SaveScoreFile();
	GD->m_state = MENU;
}

void Press_GameOverButtons()
{
	GameData* GD = GameData::Get_Instance();

	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->MousePressed(GD->m_buttonsActions[i]);
	}
}

void Click_InputBoxes(sf::Vector2f _mousePos)
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_playerNb; i++)
	{
		if (GD->m_InputBoxes[i]->rectangle.getGlobalBounds().contains(_mousePos))
		{
			GD->m_InputBoxes[i]->edit = true;
			GD->m_InputBoxes[i]->currentWord = "";
			GD->m_boxId = i;
		}
		else
		{
			GD->m_InputBoxes[i]->edit = false;
			GD->m_InputBoxes[i]->currentWord = "INPUT NAME..";
		}
	}
}

void MousePressed_GameOver(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(GD->m_window);
		Press_GameOverButtons();
		Click_InputBoxes({ (float)mousePos.x, (float)mousePos.y });
	}
	else if (_event.mouseButton.button == sf::Mouse::Right)
	{

	}
}

void Hover_GameOverButtons(sf::Vector2i _mousePos)
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->MouseMoved(_mousePos);
	}
}

void MouseMoved_GameOver(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	sf::Vector2i mousePos;
	mousePos = sf::Mouse::getPosition(GD->m_window);
	Hover_GameOverButtons(mousePos);
}

void KeyPressed_GameOver(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();
	Scores::InputScore(_event, GD->m_boxId);
}

void Update_GameOverInputBoxes()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_playerNb; i++)
	{
		if (GD->m_InputBoxes[i]->edit)
		{
			GD->m_InputBoxes[i]->rectangle.setOutlineColor(sf::Color::Green);
		}
		else
		{
			GD->m_InputBoxes[i]->rectangle.setOutlineColor(sf::Color::Red);
		}
	}
}

void Update_GameOverButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->Update();
	}
}

void Update_GameOver()
{
	GameData* GD = GameData::Get_Instance();
	sf::Event event;
	while (GD->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			MousePressed_GameOver(event);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			KeyPressed_GameOver(event);
		}
		else if (event.type == sf::Event::TextEntered && GD->m_InputBoxes[GD->m_boxId]->edit)
		{
			if ((event.text.unicode < 128 && event.text.unicode > 0) && event.text.unicode != 8)
			{
				GD->m_InputBoxes[GD->m_boxId]->currentWord += event.text.unicode;
			}
			else if (event.text.unicode == 8)
			{
				GD->m_InputBoxes[GD->m_boxId]->currentWord.pop_back();
			}
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			MouseMoved_GameOver(event);
		}
		if (event.type == sf::Event::Closed)
		{
			GD->m_window.close();
		}
		//Events
	}
	GD->m_frameTime = GD->m_clock.restart().asSeconds();
	Update_GameOverInputBoxes();
	Update_GameOverButtons();
	//std::cout << GD->m_boxId << std::endl;
	//Update RT
}

void Display_GameOverBackground()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteDrawParameters bgParameters =
	{
		GD->m_goBG,
		0,
		{0, 0},
		&GD->m_window
	};
	Sprite->BlitSprite(bgParameters);
}

void Display_GameOverInputBoxes()
{
	GameData* GD = GameData::Get_Instance();
	TextManager* Text = TextManager::Get_Instance();
	for (int i = 0; i < GD->m_playerNb; i++)
	{
		GD->m_window.draw(GD->m_InputBoxes[i]->rectangle);
		TextSettings settings =
		{
			"Poggers-Bold",
			"Input" + std::to_string(i),
			sf::Color::Black,
			20,
		};
		Text->FillVectors(settings);
		Text->SetString(settings.name, GD->m_InputBoxes[i]->currentWord);
		TextDrawParameters draw =
		{
			settings.name,
			0,
			{
				GD->m_InputBoxes[i]->rectangle.getPosition().x + 10,
				GD->m_InputBoxes[i]->rectangle.getPosition().y + 5
			},
			&GD->m_window
		};
		Text->SetString(GD->m_playerText[i], "Player " + std::to_string(i + 1));
		TextDrawParameters drawPlayers =
		{
			GD->m_playerText[i],
			0,
			{
				GD->m_InputBoxes[i]->rectangle.getPosition().x - 100,
				GD->m_InputBoxes[i]->rectangle.getPosition().y + 5
			},
			&GD->m_window
		};

		Text->BlitText(draw);
		Text->BlitText(drawPlayers);
	}
}

void Display_GameOverButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->Display();
	}
}

void Display_GameOver()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_window.clear(sf::Color::Magenta);
	//Display
	Display_GameOverBackground();
	Display_GameOverInputBoxes();
	Display_GameOverButtons();
	GD->m_window.display();
}

void Unload_GameOverButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->~Button();
	}
	GD->m_buttons.clear();
}

void Unload_GameOver()
{
	GameData* GD = GameData::Get_Instance();
	Unload_GameOverButtons();
}