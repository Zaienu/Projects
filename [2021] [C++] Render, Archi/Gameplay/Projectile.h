#ifndef PROJECTILE__H
#define PROJECTILE__H

class Projectile
{

	friend class Player;
	friend class GameplayManager;
private:

	bool m_destroyed;
	sf::Vector2f m_pos;
	sf::Vector2f m_nextPos;
	sf::Vector2f m_speed;
	int m_radius;
	float m_angle;
	float m_rotation;
	int m_impulse;
	std::string m_sprite;

public:

	Projectile(sf::Vector2f _pos, float _angle, int _impulse);
	sf::Vector2f Get_Pos();
	sf::Vector2f Get_NextPos();
	int Get_Radius();
	void Update();
	void Display();
	~Projectile();
};

#endif