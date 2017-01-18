/*

Reference: 
- Refactored from some example code I found on github (https://github.com/jasonrwalters/OF_Kinect.git) a set of prorams using the ofKinectForindows2 Library.
- Help setting up kinect with openFrameworks -> https://web.archive.org/web/20150915072025/http://rbarraza.com/adding-ofxkinectforwindows2-to-a-new-or-existing-of-project/

*/
 #include "JointClass.h"

void JointClass::setup() { //Using setup to initialise the kinect at the start of the sketch
	//connect to the Kinect
	kinect.open();

	//initialize kinect mapped Body source
	kinect.initColorSource();
	kinect.initBodySource();
	kinect.initDepthSource();
}

void JointClass::update() {
	//Make sure we update the kinect streams to get new information every frame
	kinect.update(); 
}

void JointClass::getJointPosition() {
	//Get all the useful joints data from the kinect, data returns back between -1 nd 1 which is actually good for shaders and coloring etc
	//I will remap these for ableton in the OSC class
	
	for (int i = 0; i < bodies; i++) {
		// check to see if a body is tracked...
		if (this->kinect.getBodySource()->getBodies()[i].tracked) {

			//Get the bodies tracked, although i am unable to just get one body index [0] at the moment
			auto b = this->kinect.getBodySource()->getBodies()[i];

			//Check to see if hands are tracked, this was taken fro the oscHands example in the ofKinectforWindows2

			//My code here
			//Get  all the necessary joint information to create basic rigid gestures.
			middle = b.joints[JointType_SpineMid].getPosition();
			leftHand = b.joints[JointType_HandLeft].getPosition();
			leftElbow = b.joints[JointType_ElbowLeft].getPosition();
			leftShoulder = b.joints[JointType_ShoulderLeft].getPosition();
			rightHand = b.joints[JointType_HandRight].getPosition();
			rightElbow = b.joints[JointType_ElbowLeft].getPosition();
			rightShoulder = b.joints[JointType_ShoulderLeft].getPosition();


			//Mapped the jonit coordinates to the screen space
			mappedMiddle = ofVec3f(
				ofMap(middle.x, -1, 1, 0, ofGetWidth()),
				ofMap(middle.y, 1, -1, 0, ofGetHeight()),
				ofMap(middle.z, -1, 1, -200, 200));

			mappedLeftHand = ofVec3f(
				ofMap(leftHand.x, -1, 1, 0, ofGetWidth()),
				ofMap(leftHand.y, 1, -1, 0, ofGetHeight()),
				ofMap(leftHand.z, -1, 1, -200, 200));

			mappedLeftElbow = ofVec3f(
				ofMap(leftElbow.x, -1, 1, 0, ofGetWidth()),
				ofMap(leftElbow.y, 1, -1, 0, ofGetHeight()),
				ofMap(leftElbow.z, -1, 1, -200, 200));

			mappedLeftShoulder = ofVec3f(
				ofMap(leftShoulder.x, -1, 1, 0, ofGetWidth()),
				ofMap(leftShoulder.y, 1, -1, 0, ofGetHeight()),
				ofMap(leftShoulder.z, -1, 1, -200, 200));

			mappedRightHand = ofVec3f(
				ofMap(rightHand.x, -1, 1, 0, ofGetWidth()),
				ofMap(rightHand.y, 1, -1, 0, ofGetHeight()),
				ofMap(rightHand.z, -1, 1, -200, 200));

			mappedRightElbow = ofVec3f(
				ofMap(rightElbow.x, -1, 1, 0, ofGetWidth()),
				ofMap(rightElbow.y, 1, -1, 0, ofGetHeight()),
				ofMap(rightElbow.z, -1, 1, -200, 200));

			mappedRightShoulder = ofVec3f(
				ofMap(rightShoulder.x, -1, 1, 0, ofGetWidth()),
				ofMap(rightShoulder.y, 1, -1, 0, ofGetHeight()),
				ofMap(rightShoulder.z, -1, 1, -200, 200));

			// left hand state
			switch (b.leftHandState) {
			case HandState_Unknown:
			case HandState_NotTracked:
				lHandState = "Not Tracked";
				//cout << lHandState << endl;
				break;
			case HandState_Open:
				lHandState = "Open";
				//cout << lHandState << endl;
				break;
			case HandState_Closed:
				lHandState = "Closed";
				//cout << lHandState << endl;
				break;
			case HandState_Lasso:
				lHandState = "Lasso";
				//cout << lHandState << endl;
				break;
			default: break;
			}
			switch (b.rightHandState) {
			case HandState_Unknown:
			case HandState_NotTracked:
				rHandState = "Not Tracked";
				//cout << rHandState << endl;
				break;
			case HandState_Open:
				rHandState = "Open";
				//cout << rHandState << endl;
				break;
			case HandState_Closed:
				rHandState = "Closed";
				//cout << rHandState << endl;
				break;
			case HandState_Lasso:
				rHandState = "Lasso";
				//cout << rHandState << endl;
				break;
			default: break;
			}

		}
	}

	//Debug Checker for this mapped Coordinates of left and right hand
	/*if (ofGetFrameNum() % 100 == 0) {
		cout << "Left: " << mappedLeftHand << endl;
		cout << "Right: " << mappedRightHand << endl;
	}*/
}