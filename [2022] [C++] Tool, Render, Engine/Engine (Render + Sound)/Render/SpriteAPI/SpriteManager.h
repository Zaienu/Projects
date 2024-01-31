#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

class SpriteManager
{
private:

	std::vector <Sprite> m_SpriteVec;
	bool CheckName(std::string _name);
	SpriteManager();
	~SpriteManager();

public:

	static SpriteManager* Get_Instance();
	sf::Sprite LoadSprite(SpriteSettings _settings);
	void FillVectors(SpriteSettings _settings);
	sf::Sprite GetSprite(std::string _name);
	sf::Vector2f GetSize(std::string _name);
	void SetPos(std::string _name, sf::Vector2f _pos);
	sf::Vector2f GetPos(std::string _name);
	void SetColor(std::string _name, sf::Color _color);
	sf::Color GetColor(std::string _name);
	void SetOrigin(std::string _name, int _choice);
	sf::Vector2f GetOrigin(std::string _name);
	void SetScale(std::string _name, sf::Vector2f _scale);
	sf::Vector2f GetScale(std::string _name);
	void BlitSprite(SpriteDrawParameters _parameters);
	void DeleteSprite(std::string _name);
	void DeleteVector();

};

#endif