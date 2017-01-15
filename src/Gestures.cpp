#include "Gestures.h"

Gestures::Gestures(JointClass* _jointclass):jointClass(_jointclass)
{
	//textalign center
	//ofFill(255);
	//ofSetLineWidth(0);
	text.loadFont("arial.ttf", 32);
	loadingCol = ofColor(60, 100, 250);
	gestureMaxTime = 0;

}


Gestures::~Gestures()
{
}

void Gestures::run() {
	/*This all runs in is a loop as we need to check where the individual parts
	  of the body are every frame in order to track.*/

	//Get vectors from the joint class which takes kinect input.
	//jointClass is a pointer therefore '->' notation is necessary to access the objects variables
	lHand = jointClass->leftHand;
	lElbow = jointClass->leftElbow;
	lShoulder = jointClass->leftShoulder;

	rHand = jointClass->rightHand;
	rElbow = jointClass->rightElbow;
	rShoulder = jointClass->rightShoulder;

	//Return a boolean to see if the vectors are close enough to activate a guesture
	gesture1On = gestureCheck(lHand, rShoulder);
	gesture2On = gestureCheck(rHand, lShoulder);
	gesture3On = gestureCheck(lHand, rElbow);
	gesture4On = gestureCheck(rHand, lElbow);
	gesture5On = gestureCheck(lHand, rHand);

	if (gesture1On) {
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
		text.drawString("PLAY", ofGetWidth()/2, ofGetHeight()/2); //Display it, bang on the center!

		//If the ticker equals the maximum guesture time I want..
		if (gesture1Count == gestureMaxTime) {
			//Send my OSC
			//oscMsg.drumReset = true; //???? Need to find out what I did with this
			//oscMsg.playScene(); //Start audio track on ableton
			gesture1Count = 0;
			cout << "G1 max time reached" << endl;
		}
	}

	//   We could not Implement this gesture just yet 
	//   if (gesture2On) {
	//      gesture2Count++;
	//      text("Gesture 2", width/2, height/2);
	//      if (gesture2Count == gestureMaxTime) {
	//        oscMsg.stopScene();
	//        gesture2Count = 0; //Count reset
	//      }
	//    }

	if (gesture3On) {
		gesture3Count++;

		gesture1Count = 0;
		gesture2Count = 0;
		gesture4Count = 0;
		gesture5Count = 0;

		loadingGestureIcon(gesture3Count);
		ofSetColor(loadingCol);
		ofFill();
		//textSize(50);
		text.drawString("»", ofGetWidth()/2 - 10, ofGetHeight()/2);
		//textSize(30);
		text.drawString("|", ofGetWidth()/2 + 10, ofGetHeight()/2 - 2);
		if (gesture3Count == gestureMaxTime) {
			//oscMsg.drumReset = true;
			//oscMsg.nextScene(); // Go forward to the next part of the song i.e chorus
			gesture3Count = 0; //Count reset
			//cout << "track changed >> scene:" + oscMsg.scene << endl;
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
		text.drawString("«", ofGetWidth()/2 - 10, ofGetHeight()/2);
		//textSize(30);
		text.drawString("|", ofGetWidth()/2 + 10, ofGetHeight()/2 - 2);
		if (gesture4Count == gestureMaxTime) {
			//oscMsg.drumReset = true;
			//oscMsg.prevScene(); // Go back to the previous part of the song i.e verse
			gesture4Count = 0; //Count reset
							   //println("track changed << scene:" + oscMsg.scene);
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
		text.drawString("Beat Repeat", ofGetWidth()/2, ofGetHeight()/2);
		if (gesture5Count == gestureMaxTime) {
			/*if (oscMsg.isBeatRepeatOn) {
				oscMsg.beatReapeatChance(0);// Send once turn on beat Repeater and switch ableton device 'chance' to 0
			}
			else if (!oscMsg.isBeatRepeatOn) {
				oscMsg.beatReapeatChance(1);// Send once
			}
			oscMsg.drumReset = true;
			oscMsg.isBeatRepeatOn = !oscMsg.isBeatRepeatOn;//Main switch boolean to turn beat repeat on and off
			*/
			gesture5Count = 0; //Count reset
		}
	}

	//oscMsg.run();
	
	/*if (oscMsg.isBeatrepeatOn) {
		oscMsg.beatRepeat();
		ofSetColor(loadingCol);
		ofFill();
	}

	if (!oscMsg.isBeatRepeatOn) {
		oscMsg.sceneInstruments();
	}*/

}

bool Gestures::gestureCheck(ofVec2f v1, ofVec2f v2) {
	ofVec2f diffVec = v1 - v2;
	float magnitude = sqrt(pow(diffVec.x, 2) + pow(diffVec.y,2)); //Had to write this out long hand instead of useing processing's '.mag' vector function

	if (magnitude < 130) { //When the guesture has been held for a duration of time
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