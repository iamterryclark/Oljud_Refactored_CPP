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

ofApp::ofApp() : oscMsg(&jc), gestures(&jc, &oscMsg) {

	//Initialise the particle systems to the heap in order to save on memory and keep the program quick
	for (auto & system : systems) {
		//using the namespace 'new' means that this will go to the heap
		system = new ParticleSystem();
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(50); //Framerate without this is far to quick.
	ofBackground(0);

	//Initial setup of Kinect and body source , to obtain skeleton points
	jc.setup();
	gestures.setup();

	for (auto & system : systems) {
		system->setup();
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	//Update the kinect streams and joint information
	jc.update();
	jc.getJointPosition();

	//Update all particle system origins
	for (auto & system : systems) {
		system->update();
	}

	if (jc.lHandState == "Open")
		//Add particles to the origin of both hands so that particles eject from here
		systems[0]->addParticles(ofVec2f(jc.mappedLeftHand.x, jc.mappedLeftHand.y));
	if (jc.rHandState == "Open")
		systems[1]->addParticles(ofVec2f(jc.mappedRightHand.x, jc.mappedRightHand.y));


	gestures.run();
	oscMsg.run();
	
}

//--------------------------------------------------------------

void ofApp::draw() {	
	for (auto & system : systems) {
		system->display();
		
	}

	systems[0]->particleGui.draw();
	systems[1]->particleGui.draw();
}


void ofApp::exit() {
	//When creating something on the heap it must be deleted in order to stop using unused memory
	//'system' is also a pointer object and therefore we mut also mull pointer this as otherwise there will be a dangling pointer.
	for (auto & system : systems) { //quickhand for loop used here using system as a referenece to the many systems
		delete system;
		system = nullptr;
	}
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

