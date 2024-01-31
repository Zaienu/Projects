#ifndef BUTTON__H
#define BUTTON__H
enum STATUS
{
	BUTTON_IDLE,
	BUTTON_HOVERED,
};

class Button
{
private:

	std::string m_spritePaths[2];
	std::string m_spriteNames[2];
	std::string m_soundNames[2];
	sf::Vector2f m_pos;
	STATUS m_currStatus;
	STATUS m_prevStatus;
	sf::FloatRect m_hitbox;
	void(*Fct)();

public:

	void CreateHitbox();
	Button(ButtonSettings _settings);
	bool isInsideOfButton(sf::Vector2i _pos);
	sf::Vector2f GetPos();
	STATUS isHovered(sf::Vector2i _pos);
	void SetIdle();
	void BestowAction(void(*ptr)());
	void MousePressed(sf::Vector2i _pos);
	/*template <class T>
	void MousePressed(void(*_ptr)(T), T _argument)
	{
		SoundManager* Sound = SoundManager::Get_Instance();
		if (m_currStatus == BUTTON_HOVERED)
		{
			std::cout << *
				_argument << std::endl;
			_ptr(_argument);
			Sound->ManageSound(USERINTERFACE, m_soundNames[0], true);
		}
	};*/
	void MouseMoved(sf::Vector2i _pos);
	void Update();
	void Display();
	~Button();

};
#endif