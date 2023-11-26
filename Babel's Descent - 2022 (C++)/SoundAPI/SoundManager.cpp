#include "Definitions.h"
#include "SoundManager.h"

//---------------------------------------------------READ ME------------------------------------------------------------------
//Don't forget the Instance !

SoundManager::SoundManager()
{

	MusicVolume = 100.0f;
	AmbianceVolume = 100.0f;
	EffectVolume = 100.0f;

	SoundVector.resize(3);
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
	tempBuffer->loadFromFile("../Assets/Sounds/" + _sName);
	tempSound.setBuffer(*tempBuffer);

	return tempSound;
}

bool SoundManager::CheckName(SoundType _type, std::string _name)
{
	if (_type < 0 && _type > 7)
	{
		std::cout << "SM00 Error has occured" << std::endl;
		exit(0);
	}
	if (SoundVector[_type].empty())
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < SoundVector[_type].size(); i++)
		{
			if (SoundVector[_type][i].name == _name)
			{
				return 0;
			}
		}
		return 1;
	}
}

void SoundManager::FillVectors(SoundType _type, std::string _name)
{
	if (CheckName(_type, _name))
	{
		std::string folder;
		switch (_type)
		{
		case MUSIC: folder = "Musics"; break;
		case AMBIANCE: folder = "Ambiances"; break;
		case EFFECT: folder = "Effects"; break;
		default: std::cout << "SM00 Error has occured" << std::endl; exit(0); break;
		}
		//be careful, the file must be a ".ogg".
		std::string file = folder;
		file += "/" + _name;                          // Musics/Whatever      Effects/Whatever
		sf::Sound tempSound = SoundManager::LoadSound(file); //../Assets/Sounds/Musics/Whatever.ogg
		Sound sound = { tempSound, _name };

		//Fills the corresponding array.

		SoundVector[_type].push_back(sound);
	}
}
//Apply the new volume to the entire array of the desired type (Music/Effect)
void SoundManager::ApplyVolume(SoundType _type)
{
	float volume = NULL;
	switch (_type)
	{
	case MUSIC: volume = MusicVolume; break;
	case AMBIANCE: volume = AmbianceVolume; break;
	case EFFECT: volume = EffectVolume; break;
	default: std::cout << "SM00 Error has occured" << std::endl; exit(0); break;
	}
	for (int i = 0; i < SoundVector[_type].size(); i++)
	{
		SoundVector[_type][i].sound.setVolume(volume);
	}
}
//Obtain the Music's Volume value
float SoundManager::GetSoundVolume(SoundType _type)
{
	float volume = NULL;
	switch (_type)
	{
	case MUSIC: volume = MusicVolume; break;
	case AMBIANCE: volume = AmbianceVolume; break;
	case EFFECT: volume = EffectVolume; break;
	default: std::cout << "SM00 Error has occured" << std::endl; exit(0); break;
	}
	return volume;
}
//Add a float value to the Music's Volume value
void SoundManager::SetSoundVolume(SoundType _type, float _value)
{
	float volume = NULL;
	volume = _value;
	switch (_type)
	{
	case MUSIC: MusicVolume = volume; break;
	case AMBIANCE: AmbianceVolume = volume; break;
	case EFFECT: EffectVolume = volume; break;
	default: std::cout << "SM00 Error has occured" << std::endl; exit(0); break;
	}
}

void SoundManager::SetSpecificSoundVolume(SoundType _type, std::string _name, float _value)
{
	if (_type < 0 && _type > 7)
	{
		std::cout << "SM00 Error has occured" << std::endl;
		exit(0);
	}
	for (int i = 0; i < SoundVector[_type].size(); i++)
	{
		if (SoundVector[_type][i].name == _name)
		{
			SoundVector[_type][i].sound.setVolume(_value);
		}
	}
}
void SoundManager::FinishSoundTransition(SoundType _type, std::string _name)
{
	float volume = NULL;
	switch (_type)
	{
	case MUSIC: volume = MusicVolume; break;
	case AMBIANCE: volume = AmbianceVolume; break;
	case EFFECT: volume = EffectVolume; break;
	default: std::cout << "SM00 Error has occured" << std::endl; exit(0); break;
	}
	for (int i = 0; i < SoundVector[_type].size(); i++)
	{
		if (SoundVector[_type][i].name == _name)
		{
			SoundVector[_type][i].sound.stop();
			SoundVector[_type][i].sound.setVolume(volume);
		}
	}
}
//Decide whether the music should be looped or not (Name, (true/false))
void SoundManager::SetSoundLoop(SoundType _type, std::string _name, bool _isLooped)
{
	if (_type < 0 && _type > 7)
	{
		std::cout << "SM00 Error has occured" << std::endl;
		exit(0);
	}
	for (int i = 0; i < SoundVector[_type].size(); i++)
	{
		if (SoundVector[_type][i].name == _name)
		{
			SoundVector[_type][i].sound.setLoop(_isLooped);
		}
	}
}
//Play or stop the music (Name, (true/false))
void SoundManager::ManageSound(SoundType _type, std::string _name, bool _isPlayed)
{
	if (_type < 0 && _type > 7)
	{
		std::cout << "SM00 Error has occured" << std::endl;
		exit(0);
	}
	for (int i = 0; i < SoundVector[_type].size(); i++)
	{
		if (SoundVector[_type][i].name == _name &&
			_isPlayed == true &&
			SoundVector[_type][i].sound.getStatus() !=
			sf::SoundSource::Status::Playing)
		{
			SoundVector[_type][i].sound.play();
		}
		else if (SoundVector[_type][i].name == _name &&
			_isPlayed == false &&
			SoundVector[_type][i].sound.getStatus() ==
			sf::SoundSource::Status::Playing)
		{
			SoundVector[_type][i].sound.stop();
		}
	}
}
//Pause the music (Name, (True/False))
void SoundManager::PauseSound(SoundType _type, std::string _name, bool _isPaused)
{
	if (_type < 0 && _type > 7)
	{
		std::cout << "SM00 Error has occured" << std::endl;
		exit(0);
	}
	for (int i = 0; i < SoundVector[_type].size(); i++)
	{
		if (SoundVector[_type][i].name == _name &&
			_isPaused == true &&
			SoundVector[_type][i].sound.getStatus() !=
			sf::SoundSource::Status::Paused)
		{
			SoundVector[_type][i].sound.pause();
		}
		else
		{
		}
	}
}
//Play or stop the music (Name, (true/false))

SoundManager::~SoundManager()
{
	for (int i = 0; i < SoundVector.size(); i++)
	{
		for (int j = 0; j < SoundVector[i].size(); j++)
		{
			delete SoundVector[i][j].sound.getBuffer();
		}
		SoundVector[i].clear();
	}
}

///SM00 - Type Error : the wrong SoundType has been entered in a function causing an error.