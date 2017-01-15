#pragma once

//Reference:

#include "ofMain.h"
#include "ofxOscSender.h"
#include "JointClass.h"
#include "ParticleSystem.h"

#define HOST "localhost"
#define PORT 9000

class ofApp : public ofBaseApp {

public:
	ofApp();
	~ofApp();
	void setup();
	void update();
	void draw();

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
	JointClass jointClass; //Skeleton Data
	ParticleSystem *systems[7];
	//Gestures gestures; //Gestures are created here

	//External Library Classes
	ofEasyCam camera;
	//ofxOscSender sender;

};
