#include "Gestures.h"

//Would like to upgrade this to use eclidean distance

Gestures::Gestures(JointClass *_jointClass, OSCSend *_oscMsg) {
	jointClass = _jointClass;
	oscMsg = _oscMsg;
}


void Gestures::setup() {
	loadingCol = ofColor(60, 100, 250);
	gestureMaxTime = 15;
}

void Gestures::run() {
	/*This all runs in is a loop as we need to check where the individual parts
	  of the body are every frame in order to track.*/

	//Get vectors from the joint class which takes kinect input.
	lHand = jointClass->leftHand;
	lElbow = jointClass->leftElbow;
	lShoulder = jointClass->leftShoulder;

	rHand = jointClass->rightHand;
	rElbow = jointClass->rightElbow;
	rShoulder = jointClass->rightShoulder;

	//for debug
	if (ofGetFrameNum() % 100 == 0) {
		cout << "------ For Guestures from JointClass --------" << endl;
		cout << "lHand: " << lHand << endl;
		cout << "lElbow: " << lElbow << endl;
		cout << "lShoulder" << lShoulder << endl;

		cout << "rHand" << rHand << endl;
		cout << "rElbow" << rElbow << endl;
		cout << "rShoulder" << rShoulder << endl;
		cout << " " << endl;
	}

	//Return a boolean to see if the vectors are close enough to activate a guesture
	//gesture1On = gestureCheck(lHand, rShoulder); //Play
	gesture2On = gestureCheck(rHand, lShoulder); //Stop

	gesture3On = gestureCheck(lHand, rElbow); //Next Scene
	gesture4On = gestureCheck(rHand, lElbow); //Previous Scene 

	gesture5On = gestureCheck(lHand, rHand); //Beat Repeat
	//gestureTestOn = gestureCheck(ofVec3f(0,19,0),ofVec3f(0,0,0));

	/*if (gesture1On) {
		//If left hand and right should are close
		++gesture1Count; //Use a ticker to count the seconds

		//Reset all other guestures to stop other action being called as well
		gesture2Count = 0;
		gesture3Count = 0;
		gesture4Count = 0;
		gesture5Count = 0;

		//Use an icon to help show when the guesture is activated and pass it the ticker
		loadingGestureIcon(gesture1Count);
		ofSetColor(loadingCol); //Use a color to show the text over the top
		ofFill(); // Fill it, I realise I might not need this for text

		//If the ticker equals the maximum guesture time I want..
		if (gesture1Count == gestureMaxTime) {
			//Send my OSC
			oscMsg->drumReset = true;
			oscMsg->playScene(); //Start audio track on ableton
			gesture1Count = 0;
			cout << "G1 max time reached" << endl;
		}
	}*/

	//   Could not Implement this gesture just yet 

	if (gesture3On) {
		gesture3Count++;

		gesture1Count = 0;
		gesture2Count = 0;
		gesture4Count = 0;
		gesture5Count = 0;

		loadingGestureIcon(gesture3Count);
		ofSetColor(loadingCol);
		ofFill();
		ofDrawBitmapString(">>", ofGetWidth()/2 - 10, ofGetHeight()/2);
		ofDrawBitmapString("|", ofGetWidth()/2 + 10, ofGetHeight()/2 - 2);
		if (gesture3Count == gestureMaxTime) {
			oscMsg->drumReset = true;
			oscMsg->nextScene(); // Go forward to the next part of the song i.e chorus
			gesture3Count = 0; //Count reset
			cout << "G3 max time reached" << endl;
			
		}
	}

	if (gesture4On) {
		gesture4Count++;

		gesture1Count = 0;
		gesture2Count = 0;
		gesture3Count = 0;
		gesture5Count = 0;

		loadingGestureIcon(gesture4Count);
		ofSetColor(loadingCol);
		ofFill();
		//textSize(50);
		ofDrawBitmapString("<<", ofGetWidth()/2 - 10, ofGetHeight()/2);
		//textSize(30);
		ofDrawBitmapString("|", ofGetWidth()/2 + 10, ofGetHeight()/2 - 2);
		if (gesture4Count == gestureMaxTime) {
			oscMsg->drumReset = true;
			oscMsg->prevScene(); // Go back to the previous part of the song i.e verse
			gesture4Count = 0; //Count reset
			cout << "G4 max time reached" << endl;
			cout << "track changed << scene:" + oscMsg->scene << endl;
		}
	}

	if (gesture5On) {
		gesture5Count++;

		gesture1Count = 0;
		gesture2Count = 0;
		gesture3Count = 0;
		gesture4Count = 0;

		loadingGestureIcon(gesture5Count);
		ofSetColor(loadingCol);
		ofFill();
		//textSize(30);

		//Drum Glitch time!
		ofDrawBitmapString("Beat Repeat", ofGetWidth()/2, ofGetHeight()/2);
		if (gesture5Count == gestureMaxTime) {
			if (oscMsg->isBeatRepeatOn) {
				oscMsg->beatReapeatChance(0);// Send once turn on beat Repeater and switch ableton device 'chance' to 0
			}
			else if (!oscMsg->isBeatRepeatOn) {
				oscMsg->beatReapeatChance(1);// Send once
			}
			oscMsg->drumReset = true;
			oscMsg->isBeatRepeatOn = !oscMsg->isBeatRepeatOn; //Main switch boolean to turn beat repeat on and off

			gesture5Count = 0; //Count reset*/
			cout << "G5 max time reached" << endl;
		}
	}
	
	if (oscMsg->isBeatRepeatOn) {
		oscMsg->beatRepeat();
		ofSetColor(loadingCol);
		ofFill();
	}

	if (!oscMsg->isBeatRepeatOn) {
		oscMsg->sceneInstruments();
	}

	if (gestureTestOn) {
		gestureTestCount++;
		if (gestureTestCount == gestureMaxTime)
			gestureTestCount = 0; //Count reset*/
			cout << "GTest max time reached" << endl;
	}

}

bool Gestures::gestureCheck(ofVec3f v1, ofVec3f v2) {
	ofVec3f diffVec = v1 - v2;
	float magnitude = sqrt(pow(diffVec.x, 2) + pow(diffVec.y, 2) + pow(diffVec.z, 2)); //Had to write this out long hand instead of useing processing's '.mag' vector function

	//For Debug
	if (ofGetFrameNum() % 100 == 0) {
		cout << "------- For Gestures - Magnitude -------" << endl;
		cout << "Magnitude: " << magnitude << endl;
		cout << " " << endl;
	}

	if (magnitude < 0.026) { //When the guesture has been held for a duration of time
		return true; //Guesture is activated
	} else {
		return false;//Guesture is not activated
	}

	
}

//Loading visual function
void Gestures::loadingGestureIcon(int count) {
	float countMap = ofMap(count, 0, gestureMaxTime, 0, 360);
	ofPushMatrix();
		ofTranslate(0, 0, 600);
		ofPushStyle();
			ofSetColor(loadingCol);
			ofSetLineWidth(20);
			//arc(width/2, height/2, 70,70, radians(0), radians(countmap)); // Need to work out arc in openFrameworks again.
		ofPopStyle();
	ofPopMatrix();
}