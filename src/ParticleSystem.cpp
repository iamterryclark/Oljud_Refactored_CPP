#include "ParticleSystem.h"


void ParticleSystem::setup() {

	//Parameter default are set from doing tests
	particleParams.setName("Particle Gui");
	particleParams.add(velX.set("velX: ", 1.0, 0.0, 2.0 ));
	particleParams.add(velY.set("velY: ", 1.0, 0.0, 2.0 ));
	particleParams.add(accX.set("accX: ", 1.0, 0.0, 2.0 ));
	particleParams.add(accY.set("accY: ", 1.0, 0.0, 2.0 ));
	particleGui.setup(particleParams);
}

void ParticleSystem::update() {
	
	for (auto &p : particles) p->update(); //I then look through all of the arraylist which increases in size and display
	deleteParticles(); //checking if the particle should be removed based on the opacity.
}

//Reference: Information about using parameters and also sending information via osc was from the ofxGui examples located in openframeworks 'oscParametersSender'

void ParticleSystem::addParticles(ofVec2f &_origin) {
	//I created a variety of sizes, velocity and accelerations in order to produce a realistic burner

	for (int i = 1; i < 4; i++) {
		//Main Burner
		//					            location,          size,                velocity,       acceleration       life 
		//Main Burner2
		particles.push_back(new Particle(_origin, ofGetWidth() / 130, ofVec2f(0.3, 0.3) , ofVec2f(0.35, 0.35), 150));

		//Mid Burner
		particles.push_back(new Particle(_origin, ofGetWidth() / 140, ofVec2f(0.4, 0.4), ofVec2f(0.3, 0.3), 255));

		//Spray
		particles.push_back(new Particle(_origin, ofGetWidth() / (160 + (20 * i)), ofVec2f(0.4, 0.4), ofVec2f(0.4, 0.4), 200 + (i * 4)));
	}
}

void ParticleSystem::display() {
	for (auto &p : particles) p->display();
}

void ParticleSystem::deleteParticles() {
	//I needed to use a lambda function here in order to return when a particle has died
	auto it = remove_if(particles.begin(), particles.end(), [this](Particle* particles) { return particles->kill(); });
	//I believe 'this' means the function of remove_if and then I pass it the pointer class particles. I think check the particle
	//and return true if opactiy is 0;
	
	//I needed to delete the empty space at the end of the array list as otherwise I was getting errors
	//This is due to the way arraylists work, you are apparently not able to delete something in the middle of the array
	//This would happen sometimes as the particles are all pushing back into the array with a different starting life point
	
	//delete it; //I think i need this to try and delete the heap memory as the below only deletes the pointer.
	particles.erase(it, particles.end());
	
}
