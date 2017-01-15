#include "ParticleSystem.h"

void ParticleSystem::addParticles(ofVec3f origin) {
	//I created a variety of sizes, velocity and accelerations in order to produce a realistic burner.e
	//7725 Particles rednered

	//Main Burner2
	particles->push_back(Particle(origin, ofGetWidth() / 13, ofVec3f(1.3, 1.3, 1.3), ofVec3f(0, 0.001, 0), 150));
	particles->push_back(Particle(origin, ofGetWidth() / 24, ofVec3f(1.7, 1.7, 1.7), ofVec3f(0, 0.001, 0), 230));
	particles->push_back(Particle(origin, ofGetWidth() / 35, ofVec3f(1.9, 1.9, 1.9), ofVec3f(0, 0.001, 0), 240));

	//Mid Burner
	particles->push_back(Particle(origin, ofGetWidth() / 50, ofVec3f(2, 2, 2), ofVec3f(0, 0.005, 0), 255));
	particles->push_back(Particle(origin, ofGetWidth() / 50, ofVec3f(1.6, 1.6, 1.6), ofVec3f(0, 0.005, 0), 255));

	//Spray
	/*for (int i = 1; i < 15; i++) {
		particles->push_back(Particle(origin, ofGetWidth() / (16 * i), ofVec3f(2.6 - (i / 60), 2.6 - (i / 60), 2.6 - (i / 60)), ofVec3f(0, 0.004, 0), 100 + (i * 20)));
	}*/
}

void ParticleSystem::setup() {
	for (auto it = particles->begin(); it != particles->end(); it++) {
		it->setup();
	}
}

void ParticleSystem::update() {
	//I then look through all of the arraylist which increases in size and display this whilst always
	//checking if the particle should be removed based on the opacity.
	deleteParticles();
	for (auto it = particles->begin(); it != particles->end(); it++) {
		it->update();
	}
}

void ParticleSystem::display() {
	for (auto it = particles->begin(); it != particles->end(); it++) {
		it->display();
	}
}

void ParticleSystem::deleteParticles() {
	auto it = remove_if(particles->begin(), particles->end(), [this](Particle particles) { return particles.kill(); });
	particles->erase(it, particles->end());
}
