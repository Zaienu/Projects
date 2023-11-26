#include "Definitions.h"
#include "GameData.h"
#include "Settings.h"
#include "SpriteManager.h"
#include "Button.h"
#include "SoundManager.h"

void Load_Settings();
void Update_Settings();
void Display_Settings();
void Unload_Settings();

void Settings()
{
	GameData* GD = GameData::Get_Instance();
	Load_Settings();
	while (GD->m_state == SETTINGS)
	{
		Update_Settings();
		Display_Settings();
	}
	Unload_Settings();
}


void Load_SettingsBackground()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteSettings bgSettings =
	{
		"GameStates/Menus/SettingsBackground",
		"Settings_Background",
		false,
		{1,1}
	};
	GD->m_settingsBG = bgSettings.name;
	Sprite->FillVectors(bgSettings);
}

void Load_SettingsFrame()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteSettings frameSettings =
	{
		"GameStates/Menus/Frame",
		"Settings_Frame",
		false,
		{1,1}
	};
   GD->m_settingsFrame = frameSettings.name;
	Sprite->FillVectors(frameSettings);
}

void Load_SettingsButtons(std::string _button, sf::Vector2f _pos)
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

void Raise_Music();
void Raise_Effect();
void Lower_Music();
void Lower_Effect();
void Goto_Menu1();

void Load_SettingsActions()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_buttonsActions.clear();
	GD->m_buttonsActions.resize(5);
	GD->m_buttonsActions = { Raise_Music, Raise_Effect, Lower_Music, Lower_Effect, Goto_Menu1 };
}

void Load_SettingsSoundBars()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteSettings bgSettings =
	{
		"GameStates/Menus/Buttons/SoundBar",
		"Settings_SoundBar",
		true,
		{1,1}
	};
	GD->m_settingsBar = bgSettings.name;
	Sprite->FillVectors(bgSettings);
}

void Load_Settings()
{
	GameData* GD = GameData::Get_Instance();
	Load_SettingsBackground();
	Load_SettingsFrame();
	Load_SettingsButtons("Raise", { SWIDTH / 2 + 170, 300 });
	Load_SettingsButtons("Raise", { SWIDTH / 2 + 170, 500 });
	Load_SettingsButtons("Lower", { SWIDTH / 2 - 170, 300 });
	Load_SettingsButtons("Lower", { SWIDTH / 2 - 170, 500 });
	Load_SettingsButtons("Back", { SWIDTH - 125, SHEIGHT - 50 });
	Load_SettingsActions();
	Load_SettingsSoundBars();
}

void Raise_Music()
{
	SoundManager* Sound = SoundManager::Get_Instance();
	if (Sound->GetMusicVolume() <= volumeStep * 4)
	{
		Sound->SetMusicVolume((Sound->GetMusicVolume() + volumeStep));
		Sound->ApplyVolume(MUSIC);
	}
}

void Raise_Effect()
{
	SoundManager* Sound = SoundManager::Get_Instance();
	if (Sound->GetEffectVolume() <= volumeStep * 4)
	{
		Sound->SetEffectVolume((Sound->GetEffectVolume() + volumeStep));
		Sound->ApplyVolume(EFFECT);
	}
}

void Lower_Music()
{
	SoundManager* Sound = SoundManager::Get_Instance();
	if (Sound->GetMusicVolume() >= volumeStep)
	{
		Sound->SetMusicVolume((Sound->GetMusicVolume() - volumeStep));
		Sound->ApplyVolume(MUSIC);
	}
}

void Lower_Effect()
{
	SoundManager* Sound = SoundManager::Get_Instance();
	if (Sound->GetEffectVolume() >= volumeStep)
	{
		Sound->SetEffectVolume((Sound->GetEffectVolume() - volumeStep));
		Sound->ApplyVolume(EFFECT);
	}
}

void Goto_Menu1()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_state = MENU;
}

void Press_SettingsButtons()
{
	GameData* GD = GameData::Get_Instance();

	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->MousePressed(GD->m_buttonsActions[i]);
	}

}

void MousePressed_Settings(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.mouseButton.button == sf::Mouse::Left)
	{
		Press_SettingsButtons();
	}
	else if (_event.mouseButton.button == sf::Mouse::Right)
	{

	}
}

void Hover_SettingsButtons(sf::Vector2i _mousePos)
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->MouseMoved(_mousePos);
	}
}

void MouseMoved_Settings(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	sf::Vector2i mousePos;
	mousePos = sf::Mouse::getPosition(GD->m_window);
	Hover_SettingsButtons(mousePos);
}

void KeyPressed_Settings(sf::Event _event)
{
	GameData* GD = GameData::Get_Instance();

	if (_event.key.code == sf::Keyboard::A)
	{
		GD->m_state = MENU;
	}
}

void Update_SettingsButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->Update();
	}
}

void Update_Settings()
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	sf::Event event;
	while (GD->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			MousePressed_Settings(event);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			KeyPressed_Settings(event);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			MouseMoved_Settings(event);
		}
		if (event.type == sf::Event::Closed)
		{
			GD->m_window.close();
		}
		//Events
	}
	GD->m_frameTime = GD->m_clock.restart().asSeconds();
	Update_SettingsButtons();

	//Update RT
}

void Display_SettingsPicture(std::string _name)
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteDrawParameters pictureParameters =
	{
		_name,
		0,
		{0, 0},
		&GD->m_window
	};
	Sprite->BlitSprite(pictureParameters);
}

void Display_SoundBars(SoundType _type)
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();

	int temp;
	_type == MUSIC ? 
	temp = round(Sound->GetMusicVolume() / 20.0f) : 
	temp = round(Sound->GetEffectVolume() / 20.0f);

	float posY;
	_type == MUSIC ? posY = 300 : posY = 500;

	for (int i = 0; i < temp; i++)
	{
		SpriteDrawParameters musicBarsDraw =
		{
			GD->m_settingsBar,
			0,
			{(float)(SWIDTH / 2 - 100 + i * 50), posY},
			&GD->m_window
		};
		Sprite->BlitSprite(musicBarsDraw);
	}
}

void Display_SettingsButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->Display();
	}
}

void Display_Settings()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_window.clear(sf::Color::Magenta);
	//Display
	Display_SettingsPicture(GD->m_settingsBG);
	Display_SettingsPicture(GD->m_settingsFrame);
	Display_SoundBars(MUSIC);
	Display_SoundBars(EFFECT);
	Display_SettingsButtons();
	GD->m_window.display();
}

void Unload_SettingsButtons()
{
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < GD->m_buttons.size(); i++)
	{
		GD->m_buttons[i]->~Button();
	}
	GD->m_buttons.clear();
}

void Unload_Settings()
{
	GameData* GD = GameData::Get_Instance();
	Unload_SettingsButtons();
}