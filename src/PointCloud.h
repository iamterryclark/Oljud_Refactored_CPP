//Here I use the Kinect 2.0 SDK in order to capture the depth value information and then convert this to a point cloud
//
#pragma once

#include "ofMain.h"
#include "ParticleSystem.h"

class PointCloud
{
public:
	PointCloud();
	~PointCloud();
	void setup();
	void update();
	void draw();

	ParticleSystem system;
};



