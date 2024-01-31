#include "GameData.h"
#include "Wave.h"

Wave::Wave()
{
	ReadWaveFile();
}

Wave::~Wave()
{

}

bool SecureLoad(WaveSettings _newWave)
{
	if (_newWave.waveNumber != 0.0f &&
		_newWave.waveTimer != 0.0f &&
		_newWave.enemySpawnVector.size() > 0)
	{
		return true;
	}
	return false;
}

void Wave::ReadWaveFile()
{
	std::ifstream m_file("../Assets/File/Wave.txt", std::ios::beg);

	if (m_file.is_open())
	{
		while (!m_file.eof())
		{
			WaveSettings newWave;
			m_file >> statType;

			if (statType == "WAVE")
			{
				m_file >> newWave.waveNumber;
				m_file >> statType;

				if (statType == "TIME")
				{
					m_file >> newWave.waveTimer;
					m_file >> statType;
				}

				if (statType == "SPAWNER")
				{
					while (statType != "ENDWAVESETTING")
					{
						EnemySpawnSettings newSpawnEnemy;

						m_file >> newSpawnEnemy.spawnerId;
						m_file >> statType;
						m_file >> newSpawnEnemy.enemyType;
						m_file >> statType;
						m_file >> newSpawnEnemy.nb_Enemy;
						m_file >> statType;
						m_file >> newSpawnEnemy.timeSpawn;

						newSpawnEnemy.timeInitSpawn = newSpawnEnemy.timeSpawn;
						m_file >> statType;

						newWave.enemySpawnVector.push_back(newSpawnEnemy);
					}
				}
			}
			if (SecureLoad(newWave))
			{
				m_waveVector.push_back(newWave);
			}
		}
	}
	m_file.close();
}

WaveSettings Wave::GetWave(int _id)
{
	return m_waveVector.at(_id);
}

EnemySpawnSettings Wave::GetEnemySpawn(int _id, int _idEnemy)
{
	return m_waveVector.at(_id).enemySpawnVector.at(_idEnemy);
}

int Wave::GetNbWave()
{
	return m_waveVector.size();
}

int Wave::GetNbEnemySpawn(int _id)
{
	return m_waveVector.at(_id).enemySpawnVector.size();
}