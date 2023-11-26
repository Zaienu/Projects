#ifndef SOUNDMANAGEMENT__H
#define SOUNDMANAGEMENT__H

#define volumeStep  20.0f

//SoundManaging
class SoundManager
{
private:
	std::vector <std::vector <Sound>>  SoundVector;
	float MusicVolume;
	float AmbianceVolume;
	float EffectVolume;
	SoundManager();
	~SoundManager();
public:
	static SoundManager* Get_Instance();
	sf::Sound LoadSound(std::string _sName);
	bool CheckName(SoundType _type, std::string _name);
	void FillVectors(SoundType _type, std::string _name);
	void ApplyVolume(SoundType _type);
	void SetSoundVolume(SoundType _type, float _value);
	float GetSoundVolume(SoundType _type);
	void SetSpecificSoundVolume(SoundType _type, std::string _name, float _value);
	void FinishSoundTransition(SoundType _type, std::string _name);
	void SetSoundLoop(SoundType _type, std::string _name, bool _isLooped);
	void ManageSound(SoundType _type, std::string _name, bool _isPlayed);
	void PauseSound(SoundType _type, std::string _name, bool _isPaused);
};

#endif
