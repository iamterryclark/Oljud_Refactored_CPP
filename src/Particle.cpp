#include "Particle.h"

Particle::Particle(ofVec3f _loc, int _rad, ofVec3f _vel, ofVec3f _acc, float _life) : loc(_loc), rad(_rad), vel(_vel), acc(_acc), life(_life) {

	vel = ofVec3f(ofRandom(-vel.x, vel.x), ofRandom(-vel.y, vel.y), ofRandom(-vel.z, vel.z));
	acc = ofVec3f(_acc);

	//This picks a random point in time of the noise wave
	noiseTime = ofRandom(1000);

	//I need to then calculate each particle's 90 degree vector equivilant in order to change the movement from left to right
	// creating a wiggle effect
	noiseVector = vel.rotate(0, 0, 90);
	center = ofVec3f(0, 0, 0);

	//Sets RGB values for the colouring to be taken away as the particle goes out from the center.
	red = 255;
	green = 255;
	blue = 255;
}

void Particle::setup() {

	//This picks a random point in time of the noise wave
	noiseTime = ofRandom(1000);

	//I need to then calculate each particle's 90 degree vector equivilant in order to change the movement from left to right
	// creating a wiggle effect
	noiseVector = vel.rotate(0, 0, 90);
	center = ofVec3f(0, 0, 0);

	//Sets RGB values for the colouring to be taken away as the particle goes out from the center.
	red = 255;
	green = 255;
	blue = 255;
}

void Particle::update() {
	//Accerletation is then added to Velocity in order to produce the power and projection from the center
	vel = vel + acc;
	//cout << vel << endl;

	//The results are then added to location to move the particles in x and y
	loc = loc + vel;

	//Incrementing noiseTime will cycle through the intialised wave of noise
	noiseTime += 0.006;

	//I then calculate the distance from the center of the screen and the particle location
	//so that I can then map the distnce between its perpendicular plane
	dist = loc.distance(center);
	float distMap = ofMap(dist, 0, ofGetWidth() / 2, 0, 300);

	//The value of noise is the mapped to the place of -300 to 300
	noise = ofMap(ofNoise(noiseTime), -1, 1, -distMap, distMap);

	//setting the magnitude of the vector to the mapped noise creates the illusion that the
	//particle is wiggling around the screen althought its just changeing magnitude.
	noiseVector.set(noise);

	//Set the color of each particle and as the sketch is translated to the center and thus 0,0 of itself i needed to
	//get the location from above a certain amount and below a certain amount.

	if (dist > 30) {
		green -= ofGetMouseX() / 100;
		blue -= ofGetMouseY() / 100;
	}

	//Life is then slowly decreased and killed later in the program
	life -= 0.6;
}

void Particle::display() {



	ofSetColor(red, green, blue, life);
	ofFill();

	//to display the effect of noise of the particle I needed to add it to the location vector
	ofDrawCircle(loc.x + noiseVector.x, loc.y + noiseVector.y, loc.z + noiseVector.z, rad / 2);
}

bool Particle::kill() {
	if (life < 0.0) {
		return true;
	}
	else {
		return false;
	}
}