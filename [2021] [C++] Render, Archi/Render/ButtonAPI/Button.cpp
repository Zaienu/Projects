#include "Definitions.h"
#include "GameData.h"
#include "SpriteManager.h"
#include "Button.h"
#include "SoundManager.h"

void Button::CreateHitbox()
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	m_hitbox = Sprite->GetSprite(m_spriteNames[0]).getGlobalBounds();
}

void addSprite(SpriteSettings _settings, sf::Vector2f _pos)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	Sprite->FillVectors(_settings);
	Sprite->SetPos(_settings.name, _pos);
}

void addSound(std::string _string)
{
	SoundManager* Sound = SoundManager::Get_Instance();
	Sound->FillVectors(EFFECT, _string);
}

Button::Button(ButtonSettings _settings)
{
	for (int i = 0; i < 2; i++)
	{
		m_spriteNames[i] = _settings.spriteNames[i];
		m_spritePaths[i] = _settings.spritePaths[i];
		m_soundNames[i] = _settings.soundName[i];
		std::string path;
		std::string name;
		i == 0 ? path = _settings.spritePaths[0] : path = _settings.spritePaths[1];
		i == 0 ? name = _settings.spriteNames[0] : name = _settings.spriteNames[1];
		SpriteSettings spriteSettings =
		{
			path,
			name,
			1,
			{1,1}
		};
		m_pos = _settings.pos;
		addSprite(spriteSettings, m_pos);
		addSound(m_soundNames[i]);
	}
	CreateHitbox();
	m_currStatus = BUTTON_IDLE;
	m_prevStatus = BUTTON_IDLE;
}

void Button::MousePressed(void (*TabPtrFct)())
{
	SoundManager* Sound = SoundManager::Get_Instance();
	if (m_currStatus == BUTTON_HOVERED)
	{
		TabPtrFct();
		Sound->ManageEffect(m_soundNames[0], true);
	}
}

template <typename T>
void Button::MousePressed(void (*TabPtrFct)(T))
{
	SoundManager* Sound = SoundManager::Get_Instance();
	if (m_currStatus == BUTTON_HOVERED)
	{
		TabPtrFct();
		Sound->ManageEffect(m_soundNames[0], true);
	}
}
template <typename T>
void Button::MousePressed(void (*TabPtrFct)(T, T))
{
	SoundManager* Sound = SoundManager::Get_Instance();
	if (m_currStatus == BUTTON_HOVERED)
	{
		TabPtrFct();
		Sound->ManageEffect(m_soundNames[0], true);
	}
}

STATUS Button::isInsideOfButton(sf::Vector2i _pos)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	sf::Sprite tempSprite = Sprite->GetSprite(m_spriteNames[0]);
	if (m_hitbox.contains(_pos.x, _pos.y))
	{
		return BUTTON_HOVERED;
	}
	else
	{
		return BUTTON_IDLE;
	}
}

void Button::MouseMoved(sf::Vector2i _pos)
{
	GameData* GD = GameData::Get_Instance();
	m_currStatus = isInsideOfButton(_pos);
}

void Button::Update()
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	if (m_currStatus != m_prevStatus)
	{
		Sound->ManageEffect(m_soundNames[1], true);
		m_prevStatus = m_currStatus;
	}
}

void Button::Display()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteDrawParameters spriteDrawParameters =
	{
		m_spriteNames[0],
		0,
		m_pos,
		&GD->m_window,
	};
	switch (m_currStatus)
	{
	case BUTTON_IDLE:
		spriteDrawParameters.name = m_spriteNames[0];
		Sprite->BlitSprite(spriteDrawParameters);
		CreateHitbox();
		break;
	case BUTTON_HOVERED:
		spriteDrawParameters.name = m_spriteNames[1];
		Sprite->BlitSprite(spriteDrawParameters);
		break;
	default: std::cout << "Error in the Button's Switch" << std::endl; break;
	}
}

Button::~Button()
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < 2; i++)
	{
		Sprite->DeleteSprite(m_spriteNames[i]);
	}
}