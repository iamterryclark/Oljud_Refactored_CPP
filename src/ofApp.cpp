#include "ofApp.h"

/*  INTRODUCTION:
	This is a refactor from my previous code in Processing from my paired creative project. 
	I wanted to try using the kinect full pointcloud drawn at every nth pixel and thresholded in 
	the z axis so that it only saw the points of the person. I wanted to use this as the origin of 
	many particle systems. I also wanted to use skeleton tracking to interact with ableton overall 
	creating a interaction performance tool for music artists to use live.

	ISSUES:
	The above had many issues I was not expecting to have as this ofKinectForWindows2 library is very different 
	from the one used in processing. I found that I needed to further explore coordinate spaces and understand
	how the kinect and the pointcloud are in different coordinate spaces and how to link them together.
	This unfortunately resulted in a poor looking visual for now. However I aim to remap the skeleton data to work with 
	ableton and to get music to be manipulated and gesutres to be defined and working.
	
*/

ofApp::ofApp() {

	//Initialise the particle systems to the heap in order to save on memory and keep the program quick
	for (auto & system : systems) {
		//using the namespace 'new' means that this will go to the heap
		system = new ParticleSystem();
	}
}

ofApp::~ofApp() {
	//When creating something on the heap it must be deleted in order to stop using unused memory
	//'system' is also a pointer object and therefore we mut also mull pointer this as otherwise there will be a dangling pointer.
	for (auto & system : systems) { //quickhand for loop used here using system as a referenece to the many systems
		delete system;
		system = nullptr;
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	//Resets window size 
	ofSetWindowShape(1280, 720);
	ofSetFrameRate(60); //Framerate without this is far to quick.
	ofBackground(0);
	
	// initial camera values
	camera.setDistance(1);
	
	//Initial setup of Kinect and body source , to obtain skeleton points
	jointClass.setup();
	gestures.setup();

	for (auto & system : systems) {
		system->setup();
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	//Update the kinect streams and joint information
	jointClass.update();

	//Update all particle system origins
	for (auto & system : systems) {
		system->update();
	}

	//Add particles to the origin of both hands so that particles eject from here
	systems[0]->addParticles(jointClass.mappedLeftHand);
	systems[1]->addParticles(jointClass.mappedRightHand);	

	gestures.run(&jointClass);
}

//--------------------------------------------------------------

void ofApp::draw() {

	camera.begin();
	ofPushStyle();
	ofScale(10, 10, -20);
	
	jointClass.getJointPosition();

	ofPopStyle();
	camera.end();

	for (auto & system : systems) {
		system->display();
	}
	
	
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

