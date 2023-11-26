#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

class TextManager
{
private:

	std::vector <Text> m_TextVec;
	bool CheckName(std::string _name);
	TextManager();
	~TextManager();
public:
	static TextManager* Get_Instance();
	sf::Text LoadText(TextSettings _settings);
	void FillVectors(TextSettings _settings);
	void SetPos(std::string _name, sf::Vector2f _pos);
	sf::Vector2f GetPos(std::string _name);
	void SetScale(std::string _name, sf::Vector2f _scale);
	sf::Vector2f GetScale(std::string _name);
	void SetString(std::string _name, std::string _string);
	void BlitText(TextDrawParameters _parameters);
	void DeleteText(std::string _name);
	void DeleteVector();

};

#endif
