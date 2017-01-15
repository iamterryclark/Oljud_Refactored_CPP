#pragma once

#include <ofMain.h>

class Particle
{
public:
	Particle(ofVec3f location, int rad, ofVec3f vel, ofVec3f acc, float life);

	void setup();
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

