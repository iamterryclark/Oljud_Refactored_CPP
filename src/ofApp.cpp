#include "ofApp.h"


ofApp::ofApp() {
	for (auto & system : systems) {
		system = new ParticleSystem();
	}
}

ofApp::~ofApp() {
	for (auto & system : systems) {
		delete system;
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	//Resets window size
	ofSetWindowShape(1920, 1080);
	ofBackground(0);
	
	// initial camera values
	camera.setDistance(1);
	
	jointClass.setup();

	for (auto & system : systems) {
		system->setup();
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	// update the kinect streams and joint information
	jointClass.update();

	//update all particle system origins
	for (auto & system : systems) {
		system->update();
	}
	systems[0]->addParticles(jointClass.leftHand);
	
}

//--------------------------------------------------------------

void ofApp::draw() {

	camera.begin();
	ofPushStyle();
	ofScale(10, 10, -100);
	
	jointClass.drawJoints3D();

	ofPopStyle();
	camera.end();

	for (auto & system : systems) {
		system->display();
	}
	
	
	//gestures.run();
	//oscMsg.run();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

