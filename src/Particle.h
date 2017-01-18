#pragma once

#include <ofMain.h>

class Particle
{
public:
	Particle(ofVec3f _location, int _rad, ofVec3f _vel, ofVec3f _acc, float _life);
	void update();
	void display();
	bool kill();

	int rad;
	ofVec3f loc;
	ofVec3f acc;
	ofVec3f vel;
	ofVec3f noiseVector;
	ofVec3f center;

	float life;
	float angle;
	float red, green, blue;
	float t;
	float noiseTime;
	float noise;
	float dist;
	int x, y;
	
};

