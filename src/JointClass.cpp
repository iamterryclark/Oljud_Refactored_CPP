/*

Reference: 
- Refactored from some example code I found on github (https://github.com/jasonrwalters/OF_Kinect.git) a set of prorams using the ofKinectForindows2 Library.
- Help setting up kinect with openFrameworks -> https://web.archive.org/web/20150915072025/http://rbarraza.com/adding-ofxkinectforwindows2-to-a-new-or-existing-of-project/

*/
 #include "JointClass.h"

JointClass::JointClass() {

}

JointClass::~JointClass() {

}

void JointClass::setup() {
	//connect to the Kinect
	kinect.open();

	//initialize kinect mapped Body source
	kinect.initColorSource();
	kinect.initBodySource();
	kinect.initDepthSource();

	kinect.getSensor()->get_CoordinateMapper(&m_pCoordinateMapper);

}

void JointClass::update() {
	//Make sure we update the kinect streams to get new information every frame
	kinect.update(); 
}

void JointClass::getJointPosition() {
	//Get all the useful joints data from the kinect, data returns back between -1 nd 1 which is actually good for shaders and coloring etc
	//I will remap these for ableton in the OSC class
	
	for (int i = 0; i < bodies; i++) {
		// if a body is tracked...
		if (this->kinect.getBodySource()->getBodies()[i].tracked) {
			auto b = this->kinect.getBodySource()->getBodies()[i];

			middle = b.joints[JointType_SpineMid].getProjected(m_pCoordinateMapper);
			leftHand = b.joints[JointType_HandLeft].getPosition();
			leftElbow = b.joints[JointType_ElbowLeft].getProjected(m_pCoordinateMapper);
			leftShoulder = b.joints[JointType_ShoulderLeft].getProjected(m_pCoordinateMapper);
			rightHand = b.joints[JointType_HandRight].getProjected(m_pCoordinateMapper);
			rightElbow = b.joints[JointType_ElbowLeft].getProjected(m_pCoordinateMapper);
			rightShoulder = b.joints[JointType_ShoulderLeft].getProjected(m_pCoordinateMapper);

			mappedLeftHand = ofVec3f(
							ofMap(leftHand.x, -2, 2, 0, ofGetWidth()),
							ofMap(leftHand.y, -2, 2, 0, ofGetHeight()),
							ofMap(leftHand.z, -2, 2, -200, 200));
			
			/*mappedLeftHand = ofVec3f(
				ofMap(leftHand.x, -2, 2, 0, ofGetWidth()),
				ofMap(leftHand.y, -2, 2, 0, ofGetHeight()),
				ofMap(leftHand.z, -2, 2, -200, 200));
			
			mappedLeftHand = ofVec3f(
				ofMap(leftHand.x, -2, 2, 0, ofGetWidth()),
				ofMap(leftHand.y, -2, 2, 0, ofGetHeight()),
				ofMap(leftHand.z, -2, 2, -200, 200));
			
			mappedLeftHand = ofVec3f(
				ofMap(leftHand.x, -2, 2, 0, ofGetWidth()),
				ofMap(leftHand.y, -2, 2, 0, ofGetHeight()),
				ofMap(leftHand.z, -2, 2, -200, 200));*/
		}
	}

	if (ofGetFrameNum() % 100 == 0) {
		cout << "Left: " << mappedLeftHand << endl;
		cout << "Right: " << mappedLeftHand << endl;
	}
}