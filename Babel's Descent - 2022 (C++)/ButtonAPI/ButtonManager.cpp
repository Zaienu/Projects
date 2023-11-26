#include "Definitions.h"
#include "GameData.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "Button.h"
#include "ButtonManager.h"

ButtonManager::ButtonManager(ButtonList _bL)
{
	for (int id = 0; id < _bL.names.size(); id++)
	{
		ButtonSettings buttonSettings =
		{
			{"GameStates/Menu/Buttons/" + _bL.names[id] + "Idle", "GameStates/Menu/Buttons/" + _bL.names[id] + "Hovered"},
			{_bL.names[id] + "Idle", _bL.names[id] + "Hovered"},
			{ "click.wav", "hover.wav"},
			{_bL.pos[id]},
		};
		//Do a switch to determine which gamestates requests a button
		Button* button = new Button(buttonSettings);
		button->BestowAction(_bL.pointerVec[id]);
		buttonVec.push_back(button);
	}
}

void ButtonManager::SetIdle()
{
	for (int id = 0; id < buttonVec.size(); id++)
	{
		buttonVec[id]->SetIdle();
	}
}

std::vector <Button*> ButtonManager::GetVector()
{
	return buttonVec;
}

void ButtonManager::MousePressed()
{
	GameData* GD = GameData::Get_Instance();
	sf::Vector2i mousePos = sf::Mouse::getPosition(GD->m_window);
	for (int id = 0; id < buttonVec.size(); id++)
	{
		buttonVec[id]->MousePressed(mousePos);
	}
}

void ButtonManager::MouseMoved()
{
	GameData* GD = GameData::Get_Instance();
	sf::Vector2i mousePos = sf::Mouse::getPosition(GD->m_window);
	for (int id = 0; id < buttonVec.size(); id++)
	{
		buttonVec[id]->MouseMoved(mousePos);
	}
}

void ButtonManager::Update()
{
	for (int id = 0; id < buttonVec.size(); id++)
	{
		buttonVec[id]->Update();
	}
}

void ButtonManager::Display()
{
	for (int id = 0; id < buttonVec.size(); id++)
	{
		buttonVec[id]->Display();
	}
}

ButtonManager::~ButtonManager()
{
	for (int id = buttonVec.size() - 1; id > 0 ; id--)
	{
		delete buttonVec[id];
	}
	buttonVec.clear();
}