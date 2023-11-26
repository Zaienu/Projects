#ifndef PARTICLE__H
#define PARTICLE__H

#include "definitions.h"

class Particle
{
	friend ParticleManager;
private:
	sf::Vector2f m_pos;
	float m_timer;
	std::string m_sprite;
	int speed;
public:
	Particle(sf::Vector2f _pos, float _timer);
	void Update();
	void Display();
	~Particle();
};

#endif