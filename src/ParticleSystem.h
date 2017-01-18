#pragma once

#include <ofMain.h>
#include "Particle.h"
#include "ofxGui.h"

class ParticleSystem {

public:
	void setup();
	void addParticles(ofVec2f &_origin);
	void update();
	void display();
	void deleteParticles();
	vector<Particle *> particles;

	ofxPanel particleGui;
	ofParameter<float> velX, velY;
	ofParameter<float> accX, accY;
	ofParameterGroup particleParams;
};


