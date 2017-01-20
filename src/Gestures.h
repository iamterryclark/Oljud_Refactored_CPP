#pragma once

#include <ofMain.h>
#include "OSCSend.h"
#include "JointClass.h"

class Gestures
{
public:
	
	Gestures(JointClass *_jointClass, OSCSend *_oscMsg);
	void setup();
	void run();
	bool gestureCheck(ofVec3f v1, ofVec3f v2);
	void loadingGestureIcon(int count);

	ofColor loadingCol;

	bool gesture1On, gesture2On, gesture3On, gesture4On, gesture5On, gestureTestOn;
	int  gesture1Count, gesture2Count, gesture3Count, gesture4Count, gesture5Count, gestureTestCount;
	int  gestureMaxTime;

	ofTrueTypeFont text;

	ofVec3f lHand, lElbow, lShoulder;
	ofVec3f rHand, rElbow, rShoulder;

	JointClass *jointClass;
	OSCSend *oscMsg;
};

