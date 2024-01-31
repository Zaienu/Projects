#include "GameData.h"
#include "Wave.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "Enemies.h"
#include "Towers.h"
#include "WaveManager.h"

//A function to crate a sprite
void addSpriteWave(SpriteSettings _settings, sf::Vector2f _pos)
{
	SpriteManager* sprite = SpriteManager::Get_Instance();
	sprite->FillVectors(_settings);
	sprite->SetPos(_settings.name, _pos);
}

void LoadSpriteWave(SpriteSettings* _sprite, std::string _path, std::string _name, bool _centered, sf::Vector2f _pos)
{
	_sprite->path = _path;
	_sprite->name = _name;
	_sprite->isCentered = _centered;
	_sprite->scale = { 1, 1 };

	addSpriteWave(*_sprite, _pos);
}

WaveManager::WaveManager()
{
	SpriteManager* sprite = SpriteManager::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();

	m_wave = new Wave();

	m_currentNbWave = -1;
	LoadWave();
	m_timerName = "timerName";
	m_timerPos = { WIDTH / 2, 20 };
	LoadSpriteWave(&m_timerCounter, "GameStates/Game/Hud/Timer", m_timerName, false, m_timerPos);
	m_progressTimer.setPosition({ m_timerPos.x - 604 / 2.0f + 2.0f, 10 });
}

WaveManager::~WaveManager()
{

}

void WaveManager::LoadWave()
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();

	Sound->ManageSound(MUSIC, "Battle.ogg", false);
	m_currentNbWave++;
	m_currentWave = m_wave->GetWave(m_currentNbWave);
	m_timerValue = m_currentWave.waveTimer;
	for (int i = 0; i < GD->m_tower.size(); i++)
	{
		GD->m_tower[i]->SetActivation(true);
		GD->m_tower.at(i)->ResetTrapAnimation();
	}
	//m_currentWave.waveTimer = 0;
	for (int i = 0; i < m_wave->GetNbEnemySpawn(m_currentNbWave); i++)
	{
		m_enemyWave.push_back(m_wave->GetEnemySpawn(m_currentNbWave, i));
	}
}

void WaveManager::ResetWave()
{
	GameData* GD = GameData::Get_Instance();

	m_currentWave.waveTimer = 0;
	if (GD->m_enemyVector.size() > 0)
	{
		GD->m_enemyVector.clear();
		m_enemyWave.clear();
	}
	else if (m_currentNbWave < m_wave->GetNbWave() - 1)
	{
		m_enemyWave.clear();
		LoadWave();
	}
}

void WaveManager::ResetTimer()
{
	GameData* GD = GameData::Get_Instance();

	m_currentWave.waveTimer = 0;
}

int WaveManager::GetCurrentNbWave()
{
	return m_currentNbWave;
}

void WaveManager::Update()
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	SpriteManager* sprite = SpriteManager::Get_Instance();

	if (m_currentWave.waveTimer > 0 && m_currentNbWave < m_wave->GetNbWave())
	{
		m_currentWave.waveTimer -= GD->m_frameTime;
		if (m_currentWave.waveTimer > 0)
		{
			m_progressTimer.setFillColor(hsv(120 * (m_currentWave.waveTimer / (604 - 2)), 1, 1));
		}
		m_progressTimer.setSize({ (60 / m_timerValue) * (10 * m_currentWave.waveTimer), 20.0f });
	}

	if (m_currentWave.waveTimer <= 0)
	{
		Sound->ManageSound(MUSIC, "Battle.ogg", true);
		Sound->SetSoundLoop(MUSIC, "Battle.ogg", true);
		Sound->ApplyVolume(MUSIC);
		for (int i = 0; i < m_enemyWave.size(); i++)
		{
			MapSpawner indexSpawner = GD->m_mapSpawner_Param[m_enemyWave[i].spawnerId];
			if (m_enemyWave[i].timeSpawn <= 0 && m_enemyWave[i].nb_Enemy > 0)
			{
				m_enemyWave[i].timeSpawn = m_enemyWave[i].timeInitSpawn;
				m_enemyWave[i].nb_Enemy--;
				//Call Enemies Constructor : 
				Enemies* newEnemies =
					new Enemies({ indexSpawner.pos.x, indexSpawner.pos.y },
						m_monsterName[m_enemyWave[i].enemyType],
						indexSpawner.path, indexSpawner.id);
				GD->m_enemyVector.push_back(newEnemies);
			}
			else
			{
				m_enemyWave[i].timeSpawn -= GD->m_frameTime;
			}
		}
	}

	for (int i = m_enemyWave.size() - 1; i >= 0; i--)
	{
		if (m_enemyWave[i].nb_Enemy <= 0)
		{
			m_enemyWave.erase(m_enemyWave.begin() + i);
		}
	}

	if (GD->m_enemyVector.size() == 0 && m_enemyWave.size() <= 0 &&
		m_currentWave.waveTimer <= 0 && m_currentNbWave < m_wave->GetNbWave())
	{
		if (m_currentWave.waveTimer <= 0 && m_currentNbWave >= m_wave->GetNbWave() - 1)
		{
			Sound->ManageSound(MUSIC, "Battle.ogg", false);
			GD->m_constructionMode = false;
			GD->m_mode = MOVE;
			GD->m_state = VICTORY;
		}
		else if (m_currentWave.waveTimer <= 0 && m_currentNbWave < m_wave->GetNbWave() - 1)
		{
			LoadWave();
		}
	}
}

void WaveManager::Display()
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* sprite = SpriteManager::Get_Instance();

	GD->m_window.setView(GD->m_camHud);
	GD->m_window.draw(m_progressTimer);
	SpriteDrawParameters spriteParameters =
	{
		m_timerCounter.name,
		0,
		m_timerPos,
		&GD->m_window
	};
	sprite->SetOrigin(m_timerCounter.name, CENTER);
	sprite->BlitSprite(spriteParameters);
}