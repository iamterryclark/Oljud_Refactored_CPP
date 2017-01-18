#pragma once

#include "ofMain.h"
#include "JointClass.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class OSCSend
{
public:
	OSCSend(JointClass *_jointClass);
	~OSCSend();
	void run();
	void sceneInstruments();
	void nextScene();
	void prevScene();
	void playScene();
	void beatRepeat();
	void beatReapeatChance(int percent);


	ofVec3f lHand, rHand; // main joint varibles

	float lHandMapX, lHandMapY, lHandMapZ;
	float rHandMapX, rHandMapY, rHandMapZ;
	float lHandMapDist;

	int lHandXTo, lHandXFrom, rHandXTo, rHandXFrom;
	int lHandYTo, lHandYFrom, rHandYTo, rHandYFrom;
	int lHandZTo, lHandZFrom, rHandZTo, rHandZFrom;

	int lHandDistTo, lHandDistFrom;

	int scene = 0;
	int timeDelay = 1000;

	bool isBeatRepeatOn, drumReset;

	JointClass *jointClass;
	ofxOscSender sender;
};
