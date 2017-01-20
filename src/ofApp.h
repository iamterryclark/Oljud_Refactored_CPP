#pragma once

#include "ofMain.h"
#include "ofxOscSender.h"
#include "jointClass.h"
#include "ParticleSystem.h"
#include "Gestures.h"
#include "OSCSend.h"

#define HOST "localhost"
#define PORT 9000

class ofApp : public ofBaseApp {

public:
	ofApp();
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	//My Classes
    JointClass jc; //Skeleton Data
	Gestures gestures; //Gestures are created here
	OSCSend  oscMsg; //Send gestures by osc
	ParticleSystem *systems[2];

	

	//External Library Classes
	//ofEasyCam camera, world;
	//ofxOscSender sender;

	/*ofParameter<int> camerax, cameray, cameraz;
	ofParameter<int> worldx, worldy, worldz;

	ofParameterGroup cameraParams, worldParams;
	ofxPanel worldGui, cameraGui;
	*/

};
