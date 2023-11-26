#ifndef BUTTON__H
#define BUTTON__H

enum STATUS
{
	BUTTON_IDLE,
	BUTTON_HOVERED,
};

class Button
{
private :

	std::string m_spritePaths[2];
	std::string m_spriteNames[2];
	std::string m_soundNames[2];
	sf::Vector2f m_pos;
	STATUS m_currStatus;
	STATUS m_prevStatus;
	sf::FloatRect m_hitbox;

public:

	void CreateHitbox();
	Button(ButtonSettings _settings);
	STATUS isInsideOfButton(sf::Vector2i _pos);
	void MousePressed(void (*TabPtrFct)());
	template <typename T>
	void MousePressed(void (*TabPtrFct)(T));
	template <typename T>
	void MousePressed(void (*TabPtrFct)(T, T));
	void MouseMoved(sf::Vector2i _pos);
	void Update();
	void Display();
	~Button();

};

#endif