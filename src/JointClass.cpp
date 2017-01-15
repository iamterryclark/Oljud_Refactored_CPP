/*

Reference: 
- Refactored from some example code I found on github (https://github.com/jasonrwalters/OF_Kinect.git) a set of prorams using the ofKinectForindows2 Library.
- Help setting up kinect with openFrameworks -> https://web.archive.org/web/20150915072025/http://rbarraza.com/adding-ofxkinectforwindows2-to-a-new-or-existing-of-project/

*/
 #include "JointClass.h"

void JointClass::setup() {
	//connect to the Kinect
	kinect.open();

	//initialize kinect mapped Body source
	kinect.initBodySource();
}

void JointClass::update() {
	//Make sure we update the kinect streams to get new information every frame
	kinect.update(); 
}

void JointClass::getJointPosition(Body b) {
	//Get all the useful joints data from the kinect, data returns back between -1 nd 1 which is actually good for shaders and coloring etc
	//I will remap these for ableton in the OSC class
	middle = b.joints[JointType_SpineMid].getPosition();
	leftHand = b.joints[JointType_HandLeft].getPosition();
	leftElbow = b.joints[JointType_ElbowLeft].getPosition();
	leftShoulder = b.joints[JointType_ShoulderLeft].getPosition();
	rightHand = b.joints[JointType_HandRight].getPosition();
	rightElbow = b.joints[JointType_ElbowLeft].getPosition();
	rightShoulder = b.joints[JointType_ShoulderLeft].getPosition();
}

void JointClass::drawJoints3D() {
	// set color to red
	ofSetColor(255, 0, 0);

	// create a new vector for joint position
	ofVec3f pos;

	// Kinect can detect up to 6 bodies
	for (int i = 0; i < bodies; i++) {

		// if a body is tracked...
		if (this->kinect.getBodySource()->getBodies()[i].tracked) {

			auto b = this->kinect.getBodySource()->getBodies()[i];

			// loop through the joints
			for (std::map<JointType, ofxKFW2::Data::Joint>::iterator it = b.joints.begin(); it != b.joints.end(); ++it) {
				if (it->second.getTrackingState() == TrackingState_Tracked) {
					// get joint's 3D position
					pos = it->second.getPosition();

					// joint and mesh points share the same depth space coordinates
					// so no coordinate mapping is needed.
					ofBox(pos.x, pos.y, pos.z, .05, .05, .05);
				}
			}

			getJointPosition(b);

		}
	}
}