//References: https://forum.openframeworks.cc/t/passing-raw-kinect-depth-data-to-a-shader/21798/2
//            https://www.youtube.com/watch?v=cfyot_pOz64
//I was unable to get the pointcloud information exactly how I wanted. I wanted to try and get the points of the cloud in XYZ space.
//In order to do this I need more time to study the different coordinate spaces and work out how to get an accurate pointcloud
//I then was going to threshold the z axis of the points in order to only show the person and crop out other object like walls and other room object that might be in the way
//For now I wanted to demonstrate the particle system with custom behaviour of last years project.

#include "PointCloud.h"

#define DEPTH_WIDTH 512
#define DEPTH_HEIGHT 424
#define DEPTH_SIZE DEPTH_WIDTH * DEPTH_HEIGHT

#define COLOR_WIDTH 1920
#define COLOR_HEIGHT 1080

PointCloud::PointCloud() {

}

PointCloud::~PointCloud() {

}

//--------------------------------------------------------------
void PointCloud::setup() {

	//kinect.open();
	//kinect.initDepthSource();
	
}

//--------------------------------------------------------------
void PointCloud::update() {
	//kinect.update();

}

//--------------------------------------------------------------
void PointCloud::draw() {
	//ofBackground(0);

	//vector<unsigned short> depthXYZ = kinect.getDepthSource()->getPixels(); //

	//cout << rawdepth.size() << endl;
	/*ofVec3f realWorldPoint = ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	ofSetColor(255, 0, 0);
	ofDrawCircle(realWorldPoint, 2);*/

	/*int rawDepthIndex = 0;

	for (int x = 0; x < DEPTH_WIDTH; x += steps) {
		for (int y = 0; y < DEPTH_HEIGHT; y +=steps) {
			//int offset = x + y * DEPTH_WIDTH;
			ofVec3f realWorldPoint = depthToPointCloudPos(x, y, rawdepth[rawDepthIndex++].z);
			cout << realWorldPoint << endl;
		}
	}*/

	system.addParticles();


}


/*void PointCloud::generateDepthDisplayImage() {

	// MAKE SURE WE HAVE A DEPTH SOURCE BEFORE WE ATTEMPT TO MANIPULATE
	if (nullptr == kinect.getDepthSource()) return;

	unsigned short* rawdepth = kinect.getDepthSource()->getPixels();

	int rawindex = 0;
	int displayindex = 0;

	for (int y = 0; y < DEPTH_HEIGHT; y++) {
		for (int x = 0; x < DEPTH_WIDTH; x++) {
			unsigned char greyValue = depthToPointCloudPos(x, y, rawdepth[rawindex++]);

			depthDisplay.getPixels()[displayindex++] = greyValue;
			depthDisplay.getPixels()[displayindex++] = greyValue;
			depthDisplay.getPixels()[displayindex++] = greyValue;
		}
	}

	depthDisplayImage.setFromPixels(depthDisplay);

}

/*void PointCloud::updateRawDepthLookupTable() {

	// IF YOU WANT NEAR TO BE BLACK AND FAR TO BE WHITE, SWITCH THESE
	unsigned char nearColor = 255;
	unsigned char farColor = 0;

	// HOW FAR BACK WE WANT TO GRADIENT BEFORE HITTING THE MAX DISTANCE.
	// EVERYTHING PAST THE MAX DISTANCE WILL BE CLAMPPED TO 'farColor'
	unsigned int maxDepthLevels = 5001;
	depthLookupTable.resize(maxDepthLevels);

	depthLookupTable[0] = 0;
	for (unsigned int i = 1; i < maxDepthLevels; i++)
	{
		depthLookupTable[i] = ofMap(i, nearClipping, farClipping, nearColor, farColor, true);
	}
}*/

