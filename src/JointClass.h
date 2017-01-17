#pragma once

#include "ofMain.h"
#include "ofxKinectForWindows2.h"
#include "ParticleSystem.h"

#define bodies 6


class JointClass
{
public:
	JointClass();
	~JointClass();
	void setup();
	void update();
	void getJointPosition();

	ofVec3f middle, mappedMiddle;
	ofVec3f leftHand, mappedLeftHand;
	ofVec3f leftElbow, mappedLeftElbow;
	ofVec3f leftShoulder, mappedLeftShoulder;
	ofVec3f rightHand, mappedRightHand;
	ofVec3f rightElbow, mappedRightElbow;
	ofVec3f rightShoulder, mappedRightShoulder;

	ofxKFW2::Device kinect;
	ICoordinateMapper* m_pCoordinateMapper;
	DepthSpacePoint m_pDepthCoordinates[1280 * 720];

};

