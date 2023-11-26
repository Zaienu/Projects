#ifndef ANIMATIONMANAGER__H
#define ANIMATIONMANAGER__H



class AnimationManager
{
private:
	std::vector <Animation> m_AnimVec;
	bool CheckName(std::string _name);
	AnimationManager();
	~AnimationManager();
public:
	static AnimationManager* Get_Instance();
	void FillVectors(AnimSettings _settings);
	sf::Sprite GetSprite(std::string _name);
	void SetPos(std::string _name, sf::Vector2f _pos);
	sf::Vector2f GetPos(std::string _name);
	void SetOrigin(std::string _name, int _choice);
	sf::Vector2f GetOrigin(std::string _name);
	void SetScale(std::string _name, sf::Vector2f _scale);
	sf::Vector2f GetScale(std::string _name);
	sf::Color GetColor(std::string _name);
	void SetColor(std::string _name, sf::Color _color);
	bool Get_Status(std::string _name, ObjectAnimParam* _para);
	void Stop(std::string _name, ObjectAnimParam* _para);
	void Resume(std::string _name, ObjectAnimParam* _para);
	void UpdateAnim(std::string _name, float _timer, ObjectAnimParam* _para);
	void DrawAnim(AnimDrawParameters _parameters, ObjectAnimParam* _para);
	void ResetAnim(std::string _name, ObjectAnimParam* _para);
	void DeleteAnim(std::string _name);
	void DeleteVector();
};

#endif