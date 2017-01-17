#include "ParticleSystem.h"

void ParticleSystem::addParticles(ofVec3f origin) {
	//I created a variety of sizes, velocity and accelerations in order to produce a realistic burner

	//Main Burner
	//					         location,       size,             velocity,            acceleration      life 
	particles->push_back(Particle(origin, ofGetWidth() / 100, ofVec2f(1.9, 1.9), ofVec2f(0, 0.001), ofRandom(200, 240))); //Inside the pushback function we initialise the individual particles

	//Mid Burner
	particles->push_back(Particle(origin, ofGetWidth() / 150, ofVec2f(2, 2), ofVec2f(0, 0.005), ofRandom(240, 255)));

	//Spray
	particles->push_back(Particle(origin, ofGetWidth() / 250, ofVec2f(2.6, 2.6), ofVec2f(0, 0.004), ofRandom(140, 200)));
}

void ParticleSystem::setup() {

	//Using an iterator for loop in order to access the particles through pointer memory, this is more efficient
	for (auto it = particles->begin(); it != particles->end(); it++) {
		it->setup(); //Setup each particle
	}
}

void ParticleSystem::update() {
	//I then look through all of the arraylist which increases in size and display this whilst always
	//checking if the particle should be removed based on the opacity.
	deleteParticles();
	for (auto it = particles->begin(); it != particles->end(); it++) {
		it->update(); // we update the particles, position and also lifespace here
	}
}

void ParticleSystem::display() {
	for (auto it = particles->begin(); it != particles->end(); it++) {
		it->display(); //Particle.display function called here
	}
}

void ParticleSystem::deleteParticles() {
	//I needed to use a lambda function here in order to return when a particle has died
	auto it = remove_if(particles->begin(), particles->end(), [this](Particle particles) { return particles.kill(); });
	
	//I needed to delete the empty space at the end of the array list as otherwise I was getting errors
	//This is due to the way arraylists work, you are apparently not able to delete something in the middle of the array
	//This would happen sometimes as the particles are all pushing back into the array with a different starting life point
	particles->erase(it, particles->end());
	
}
