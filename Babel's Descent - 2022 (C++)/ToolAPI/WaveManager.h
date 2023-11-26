#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "Definitions.h"

class Wave;

class WaveManager
{
private:
	int m_currentNbWave;

	Wave* m_wave;
	WaveSettings m_currentWave;
	std::vector<EnemySpawnSettings> m_enemyWave;

	std::vector<std::string> m_monsterName =
	{
		"Magic_Bomber", "Magic_Buffer", "Magic_Healer", "Magic_Tank", "Fly_Exploder", "Soldier", "Crawler"
	};

	SpriteSettings m_timerCounter;
	std::string m_timerName;
	sf::Vector2f m_timerPos;
	sf::RectangleShape m_progressTimer;
	float m_timerValue;
	float m_timer;
public:
	WaveManager();
	~WaveManager();

	void LoadWave();
	void ResetWave();
	void ResetTimer();
	int GetCurrentNbWave();
	void Update();
	void Display();
};

#endif // !WAVEMANAGER_H
