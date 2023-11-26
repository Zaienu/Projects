#include "Definitions.h"
#include "SoundManager.h"

//---------------------------------------------------READ ME------------------------------------------------------------------
//Don't forget the Instance !

SoundManager::SoundManager()
{
	m_MusicVolume = 100.0f;
	m_EffectVolume = 100.0f;
	m_SoundVector.resize(2);
}

SoundManager* SoundManager::Get_Instance()
{
	static SoundManager instance;
	return &instance;
}

sf::Sound SoundManager::LoadSound(std::string _sName)
{
	sf::Sound tempSound;
	sf::SoundBuffer* tempBuffer = new sf::SoundBuffer();
	tempBuffer->loadFromFile("../Assets/Sounds/" + _sName + ".ogg");
	tempSound.setBuffer(*tempBuffer);

	return tempSound;
}

bool SoundManager::CheckName(std::string _name, SoundType _type)
{
	if (m_SoundVector[_type].empty())
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < m_SoundVector[_type].size(); i++)
		{
			if (m_SoundVector[_type][i].name == _name)
			{
				return 0;
			}
		}
		return 1;
	}
}

void SoundManager::FillVectors(SoundType _type, std::string _name)
{
	if (CheckName(_name, _type))
	{
		std::string temp;
		_type == MUSIC ? temp = "Musics" : temp = "Effects";
		//be careful, the file must be a ".ogg".
		std::string file = temp;
		file += "/" + _name;                          // Musics/Whatever      Effects/Whatever
		sf::Sound tempSound = SoundManager::LoadSound(file); //../Assets/Sounds/Musics/Whatever.ogg
		Sound sound = { tempSound, _name };

		//Fills the corresponding array.

		m_SoundVector[_type].push_back(sound);
	}
}
//Apply the new volume to the entire array of the desired type (Music/Effect)
void SoundManager::ApplyVolume(SoundType _type)
{
	float temp;
	_type == MUSIC ? temp = m_MusicVolume : temp = m_EffectVolume;
	for (int i = 0; i < m_SoundVector[_type].size(); i++)
	{
		m_SoundVector[_type][i].sound.setVolume(temp);
	}
}
//Obtain the Music's Volume value
float SoundManager::GetMusicVolume()
{
	return m_MusicVolume;
}
//Obtain the Music's Volume value
float SoundManager::GetEffectVolume()
{
	return m_EffectVolume;
}
//Add a float value to the Music's Volume value
void SoundManager::SetMusicVolume(float _value)
{
	m_MusicVolume = _value;
}
//Add a float value to the Effec's Volume value
void SoundManager::SetEffectVolume(float _value)
{
	m_EffectVolume = _value;
}
void SoundManager::SetSpecificMusicVolume(std::string _name, float _value)
{
	for (int i = 0; i < m_SoundVector[MUSIC].size(); i++)
	{
		if (m_SoundVector[MUSIC][i].name == _name)
		{
			m_SoundVector[MUSIC][i].sound.setVolume(_value);
		}
	}
}
void SoundManager::FinishMusicTransition(std::string _name)
{
	for (int i = 0; i < m_SoundVector[MUSIC].size(); i++)
	{
		if (m_SoundVector[MUSIC][i].name == _name)
		{
			m_SoundVector[MUSIC][i].sound.stop();
			m_SoundVector[MUSIC][i].sound.setVolume(m_MusicVolume);
		}
	}
}
//Decide whether the music should be looped or not (Name, (true/false))
void SoundManager::SetMusicLoop(std::string _name, bool _isLooped)
{
	for (int i = 0; i < m_SoundVector[MUSIC].size(); i++)
	{
		if (m_SoundVector[MUSIC][i].name == _name)
		{
			m_SoundVector[MUSIC][i].sound.setLoop(_isLooped);
		}
	}
}
//Play or stop the music (Name, (true/false))
void SoundManager::ManageMusic(std::string _name, bool _isPlayed)
{
	for (int i = 0; i < m_SoundVector[MUSIC].size(); i++)
	{
		if (m_SoundVector[MUSIC][i].name == _name &&
			_isPlayed == true &&
			m_SoundVector[MUSIC][i].sound.getStatus() !=
			sf::SoundSource::Status::Playing)
		{
			m_SoundVector[MUSIC][i].sound.play();
		}
		else if (m_SoundVector[MUSIC][i].name == _name &&
			_isPlayed == false &&
			m_SoundVector[MUSIC][i].sound.getStatus() ==
			sf::SoundSource::Status::Playing)
		{
			m_SoundVector[MUSIC][i].sound.stop();
		}
	}
}
//Pause the music (Name, (True/False))
void SoundManager::PauseMusic(std::string _name, bool _isPaused)
{
	for (int i = 0; i < m_SoundVector[MUSIC].size(); i++)
	{
		if (m_SoundVector[MUSIC][i].name == _name &&
			_isPaused == true &&
			m_SoundVector[MUSIC][i].sound.getStatus() !=
			sf::SoundSource::Status::Paused)
		{
			m_SoundVector[MUSIC][i].sound.pause();
		}
		else
		{
		}
	}
}
//Play or stop the music (Name, (true/false))
void SoundManager::ManageEffect(std::string _name, bool _isPlayed)
{
	for (int i = 0; i < m_SoundVector[EFFECT].size(); i++)
	{
		if (m_SoundVector[EFFECT][i].name == _name &&
			_isPlayed == true &&
			m_SoundVector[EFFECT][i].sound.getStatus() !=
			sf::SoundSource::Status::Playing)
		{
			m_SoundVector[EFFECT][i].sound.play();
		}
		else if (m_SoundVector[EFFECT][i].name == _name &&
			_isPlayed == false &&
			m_SoundVector[EFFECT][i].sound.getStatus() ==
			sf::SoundSource::Status::Playing)
		{
			m_SoundVector[EFFECT][i].sound.stop();
		}
	}
}
SoundManager::~SoundManager()
{
	for (int i = 0; i < m_SoundVector.size(); i++)
	{
		for (int j = 0; j < m_SoundVector[i].size(); j++)
		{
			delete m_SoundVector[i][j].sound.getBuffer();
		}
		m_SoundVector[i].clear();
	}
}