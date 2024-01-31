#include "GameData.h"
#include "definitions.h"
#include "Projectile.h"
#include "SpriteManager.h"

Projectile::Projectile(sf::Vector2f _pos, float _angle, int _impulse)
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	m_pos = _pos;
	m_angle = _angle;
	m_rotation = _angle;
	m_impulse = _impulse;
	m_radius = 30;
	m_destroyed = false;
	SpriteSettings ammoSettings =
	{
		"GameStates/Game/Ammo",
		"Ammo",
		true,
		{0.25f, 0.25f}
	};
	Sprite->FillVectors(ammoSettings);
	Sprite->SetOrigin(ammoSettings.name, 1);
	m_sprite = ammoSettings.name;
	m_angle *= PI / 180;
	m_speed.x = cos(m_angle) * 30 * m_impulse;
	m_speed.y = sin(m_angle) * 30 * m_impulse;
}

sf::Vector2f Projectile::Get_Pos()
{
	return m_pos;
}

sf::Vector2f Projectile::Get_NextPos()
{
	return m_nextPos;
}

int Projectile::Get_Radius()
{
	return m_radius;
}

void Projectile::Update()
{
	GameData* GD = GameData::Get_Instance();
	m_pos.x += m_speed.x * GD->m_frameTime;
	m_pos.y += m_speed.y * GD->m_frameTime;
	m_speed.y += (200 + GD->m_wind.y) * GD->m_frameTime; //gravity + wind
	m_speed.x += GD->m_wind.x * GD->m_frameTime; //wind
	m_nextPos.x = m_pos.x + m_speed.x * GD->m_frameTime;
	m_nextPos.y = m_pos.y + m_speed.y * GD->m_frameTime;
	m_rotation = atan2(m_speed.y, m_speed.x) * 180 / PI;
}

void Projectile::Display()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();

	SpriteDrawParameters drawAmmo =
	{
		m_sprite,
		m_rotation,
		m_pos,
		&GD->m_window,
	};
	Sprite->BlitSprite(drawAmmo);
}

Projectile::~Projectile()
{

}