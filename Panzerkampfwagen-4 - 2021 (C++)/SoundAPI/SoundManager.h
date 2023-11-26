#ifndef SOUNDMANAGEMENT__H
#define SOUNDMANAGEMENT__H

#define volumeStep  20.0f

//SoundManaging
class SoundManager
{
private:
	std::vector <std::vector <Sound>>  m_SoundVector;
	float m_MusicVolume = 100.0f;
	float m_EffectVolume = 100.0f;
	SoundManager();
	~SoundManager();
public:
	static SoundManager* Get_Instance();
	sf::Sound LoadSound(std::string _sName);
	bool CheckName(std::string _name, SoundType _type);
	void FillVectors(SoundType _type, std::string _name);
	void ApplyVolume(SoundType _type);
	float GetMusicVolume();
	float GetEffectVolume();
	void SetMusicVolume(float _value);
	void SetEffectVolume(float _value);
	void SetSpecificMusicVolume(std::string _name, float _value);
	void FinishMusicTransition(std::string _name);
	void SetMusicLoop(std::string _name, bool _isLooped);
	void ManageMusic(std::string _name, bool _isPlayed);
	void PauseMusic(std::string _name, bool _isPaused);
	void ManageEffect(std::string _name, bool _isPlayed);
};

#endif
