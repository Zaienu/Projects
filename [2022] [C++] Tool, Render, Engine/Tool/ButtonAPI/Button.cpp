#include "Definitions.h"
#include "GameData.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "Button.h"

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
	GameData* GD = GameData::Get_Instance();
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
			{1.0f,1.0f}
		};
		m_pos = _settings.pos;
		addSprite(spriteSettings, m_pos);
		addSound(m_soundNames[i]);
	}
	CreateHitbox();
	m_currStatus = BUTTON_IDLE;
	m_prevStatus = BUTTON_IDLE;
}

bool Button::isInsideOfButton(sf::Vector2i _pos)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	sf::Sprite tempSprite = Sprite->GetSprite(m_spriteNames[0]);
	if (m_hitbox.contains(_pos.x, _pos.y))
	{
		return true;
	}
	return false;
}

sf::Vector2f Button::GetPos()
{
	sf::Vector2f result = m_pos;
	return result;
}

STATUS Button::isHovered(sf::Vector2i _pos)
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

void Button::SetIdle()
{
	m_currStatus = BUTTON_IDLE;
}

void Button::BestowAction(void(*ptr)())
{
	Fct = ptr;
}

void Button::MousePressed(sf::Vector2i _pos)  
{
	SoundManager* Sound = SoundManager::Get_Instance();
	if (m_currStatus == BUTTON_HOVERED && isInsideOfButton(_pos))
	{
		Fct();
		Sound->ManageSound(EFFECT, m_soundNames[0], true);
	}
};

void Button::MouseMoved(sf::Vector2i _pos)
{
	GameData* GD = GameData::Get_Instance();
	m_currStatus = isHovered(_pos);
}


void Button::Update()
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	if (m_currStatus != m_prevStatus)
	{
		Sound->ManageSound(EFFECT, m_soundNames[1], true);
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