#pragma once

#include <ofMain.h>
#include "Particle.h"

class ParticleSystem {

public:
	void setup();
	void addParticles(ofVec3f origin);
	void update();
	void display();
	void deleteParticles();
	vector<Particle> particles;
};

