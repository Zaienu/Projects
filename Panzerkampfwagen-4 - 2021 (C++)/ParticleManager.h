#ifndef ParticleManager__H
#define ParticleManager__H

#include "definitions.h"

class Particle;

class ParticleManager
{
private:
	std::vector <Particle*> particles;

public:
	ParticleManager();
	~ParticleManager();
	void Update();
	void Display();
};

#endif