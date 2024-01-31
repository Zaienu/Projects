#include "definitions.h"
#include "GameData.h"
#include "Particle.h"
#include "SpriteManager.h"

Particle::Particle(sf::Vector2f _pos, float _timer)
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	m_pos.x = _pos.x + (rand() % 50 - 25);
	m_pos.y = _pos.y + (rand() % 50 - 25);
	m_timer = _timer;
	SpriteSettings particleSettings =
	{
		"/GameStates/Game/Smoke.png",
		"Smoke",
		true,
		{0.25f, 0.25f },
	};
	Sprite->FillVectors(particleSettings);
	m_sprite = particleSettings.name;
	speed = 5;
}

void Particle::Update()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	m_timer -= GD->m_frameTime;
	m_pos.y -= speed * GD->m_frameTime;
	Sprite->SetPos(m_sprite, m_pos);
}

void Particle::Display()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteDrawParameters particleDraw =
	{
		m_sprite,
		0,
		m_pos,
		&GD->m_window
	};
	Sprite->BlitSprite(particleDraw);
}

Particle::~Particle()
{

}