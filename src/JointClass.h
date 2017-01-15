#pragma once

#include "ofMain.h"
#include "ofxKinectForWindows2.h"
#include "ParticleSystem.h"

#define bodies 6

typedef ofxKFW2::Data::Body Body;

class JointClass
{
public:
	JointClass();
	~JointClass();

	void setup();
	void update();
	void getJointPosition(Body b);
	void updateSystemsOrigin();
	void drawJoints3D();

	ofVec3f middle;
	ofVec3f leftHand, leftElbow, leftShoulder;
	ofVec3f rightHand, rightElbow, rightShoulder;

	ofxKFW2::Device kinect;
	ICoordinateMapper* m_pCoordinateMapper;
	DepthSpacePoint m_pDepthCoordinates[1920 * 1080];

	string lHandState;
	string rHandState;

};

