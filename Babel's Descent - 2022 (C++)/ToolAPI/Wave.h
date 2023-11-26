#ifndef WAVE_H
#define WAVE_H

#include "Definitions.h"

class Wave
{
private:
	std::string statType;
	std::vector<WaveSettings> m_waveVector;
public:
	Wave();
	~Wave();

	void ReadWaveFile();

	WaveSettings GetWave(int _id);
	EnemySpawnSettings GetEnemySpawn(int _id, int _idEnemy);

	int GetNbWave();
	int GetNbEnemySpawn(int _id);
};

#endif // !WAVE_H
