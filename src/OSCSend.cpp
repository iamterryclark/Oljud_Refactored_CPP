#include "OSCSend.h"

//Reference : https://github.com/lian/ofx-dev/blob/master/addons/ofxOsc/examples/oscSendExample/src/testApp.cpp

OSCSend::OSCSend(JointClass *_jointClass)
{
	jointClass = _jointClass;
	sender.setup(HOST, PORT);
}


OSCSend::~OSCSend()
{
}

void OSCSend::run() {
	lHand = jointClass->leftHand;
	rHand = jointClass->rightHand;

	lHandMapX = ofMap(lHand.x, -1, 1, lHandXTo, lHandXFrom);
	lHandMapY = ofMap(lHand.y, -1, 1, lHandYTo, lHandYFrom);
	lHandMapZ = ofMap(lHand.z, -1, 1, lHandZTo, lHandZFrom);

	rHandMapX = ofMap(rHand.x, -1, 1, rHandXTo, rHandXFrom);
	rHandMapY = ofMap(rHand.y, -1, 1, rHandYTo, rHandYFrom);
	rHandMapZ = ofMap(rHand.z, -1, 1, rHandZTo, rHandZFrom);

	lHandMapDist = ofMap(lHand.distance(rHand), 0, 1000, lHandDistTo, lHandDistFrom);

	cout << "Left Hand: " << ofVec3f(lHandMapX, lHandMapY, lHandMapZ) << endl;
	cout << "Right Hand: " << ofVec3f(rHandMapX, rHandMapY, rHandMapZ) << endl;
	cout << "Hand Distance: " << lHandMapDist << endl;
}

void OSCSend::sceneInstruments() {
	if (drumReset) {
		ofxOscBundle sceneInstruments;
		ofxOscMessage message;
		message.setAddress("/live/device");
		message.addIntArg(8); //track
		message.addIntArg(2); //device
		message.addIntArg(4); //parameter drum grid
		message.addIntArg(12); //value 12 - 0
		sceneInstruments.addMessage(message);
		message.clear();

		message.setAddress("/live/device");
		message.addIntArg(8); //track
		message.addIntArg(2); //device
		message.addIntArg(2); //parameter drum interval
		message.addIntArg(7); //value 7 - 0
		sceneInstruments.addMessage(message);

		if(ofGetFrameNum() % timeDelay == 0); //Set time delay of bundle being sent
			sender.sendBundle(sceneInstruments); //Send to osc address
		
		drumReset = false;
	}

	if (scene == 0) {
		lHandZTo = 127;
		lHandZFrom = 0;

		rHandXTo = -1;
		rHandXFrom = 1;

		/* ------------- */

		//Begin Bundle - First Message
		ofxOscBundle sceneInstruments;
		ofxOscMessage message;
		message.setAddress("/live/pan");
		message.addIntArg(5);//add track number (instrument) to alter
		message.addIntArg(rHandMapX); //add mapped int for Volume -1 to 1
		sceneInstruments.addMessage(message);//Send this specific message to bundle
		message.clear();// After putting message into bundle clear the message

		//Start Second Message etc
		message.setAddress("/live/device");
		message.addIntArg(5); //
		message.addIntArg(0); //
		message.addIntArg(7); //parameter arp rate
		message.addIntArg(int(lHandMapZ)); //value 14 - 0
		sceneInstruments.addMessage(message);

		if (ofGetFrameNum() % timeDelay == 0); //Set time delay of bundle being sent
			sender.sendBundle(sceneInstruments); //Send to osc address
	}

	if (scene == 1) {
		lHandZTo = 1;
		lHandZFrom = 12;

		rHandXTo = 6;
		rHandXFrom = 1;

		/* ------------- */

		ofxOscBundle sceneInstruments;
		ofxOscMessage message;
		message.setAddress("/live/device");
		message.addIntArg(8); //track
		message.addIntArg(2); //device
		message.addIntArg(4); //parameter drum grid
		message.addIntArg(lHandMapZ); //value 12 - 0
		sceneInstruments.addMessage(message);
		message.clear();

		message.setAddress("/live/device");
		message.addIntArg(8); //track
		message.addIntArg(2); //device
		message.addIntArg(2); //parameter drum interval
		message.addIntArg(rHandMapX); //value 6 - 1
		sceneInstruments.addMessage(message);

		if (ofGetFrameNum() % timeDelay == 0); //Set time delay of bundle being sent
			sender.sendBundle(sceneInstruments); //Send to osc address
	}

	if (scene == 2) {
		lHandZTo = 1;
		lHandZFrom = 0;

		rHandZTo = 1;
		rHandZFrom = 0;

		rHandYTo = 0;
		rHandYFrom = 127;

		lHandDistTo = 16;
		lHandDistFrom = 0;

		/* ------------- */

		//Bass Volume
		ofxOscBundle sceneInstruments;
		ofxOscMessage message;
		message.setAddress("/live/volume");
		message.addIntArg(0); //track
		message.addIntArg(lHandMapZ); //add mapped int for Volume
		sceneInstruments.addMessage(message);//Send this specific message to bundle
		message.clear();// After putting message into bundle clear the message

		//Synth Volume
		message.setAddress("/live/volume");
		message.addIntArg(1); //track
		message.addIntArg(rHandMapZ);
		sceneInstruments.addMessage(message);
		message.clear();// After putting message into bundle clear the message

		//Synth Modulation
		message.setAddress("/live/device");
		message.addIntArg(1); //track
		message.addIntArg(0); //device
		message.addIntArg(1); //parameter
		message.addIntArg(rHandMapY); //value 0 - 127
		sceneInstruments.addMessage(message);
		message.clear();// After putting message into bundle clear the message

						//Drum BitCrush needs 2 messages!!!! clear above message if implemented 
		message.setAddress("/live/device");
		message.addIntArg(9); //track
		message.addIntArg(1); //device
		message.addIntArg(2); //parameter drum grid
		message.addIntArg((int)lHandMapDist); //value 0 - 16
		sceneInstruments.addMessage(message);

		if (ofGetFrameNum() % timeDelay == 0); //Set time delay of bundle being sent
			sender.sendBundle(sceneInstruments); //Send to osc address
	}

	if (scene == 3) {
		lHandZTo = 1;
		lHandZFrom = 0;

		rHandZTo = 1;
		rHandZFrom = 0;

		rHandYTo = 0;
		rHandYFrom = 124;

		rHandXTo = 1;
		rHandXFrom = -1;

		/* ------------- */

		//Bass Volume
		ofxOscBundle sceneInstruments;
		ofxOscMessage message;
		message.setAddress("/live/volume");
		message.addIntArg(0); //track
		message.addIntArg(lHandMapZ); //add mapped int for Volume
		sceneInstruments.addMessage(message);//Send this specific message to bundle
		message.clear();// After putting message into bundle clear the message

						//Space Synth Volume
		message.setAddress("/live/volume");
		message.addIntArg(3); //track
		message.addIntArg(rHandMapZ); //add mapped int for Volume
		sceneInstruments.addMessage(message);//Send this specific message to bundle
		message.clear();// After putting message into bundle clear the message

						//Space Synth Modulation
		message.setAddress("/live/device");
		message.addIntArg(3); //track
		message.addIntArg(0); //device
		message.addIntArg(7); //parameter 
		message.addIntArg(rHandMapY); //value 0 - 124
		sceneInstruments.addMessage(message);
		message.clear();

		//Space Synth Pan
		message.setAddress("/live/pan");
		message.addIntArg(3); //track
		message.addIntArg(rHandMapX);//value
		sceneInstruments.addMessage(message);

		if (ofGetFrameNum() % timeDelay == 0); //Set time delay of bundle being sent
			sender.sendBundle(sceneInstruments); //Send to osc address
	}
}

void OSCSend::nextScene() {
	//scene changer
	scene++;
	scene = abs(scene % 4); //Switch between only 4 scenes
	ofxOscMessage myMessage;
	myMessage.setAddress("/live/play/scene");
	myMessage.addIntArg(scene);
	sender.sendMessage(myMessage);
}

void OSCSend::prevScene() {
	//scene changer
	scene--;
	scene = abs(scene % 4); //Switch between only 4 scenes
	ofxOscMessage myMessage;
	myMessage.setAddress("/live/play/scene");
	myMessage.addIntArg(scene);
	sender.sendMessage(myMessage);
}

void OSCSend::playScene() {
	ofxOscMessage message;
	message.setAddress("/live/play");
	sender.sendMessage(message);
}

void OSCSend::beatRepeat() {
	lHandZTo = 6;
	lHandZFrom = 1;

	rHandXTo = 12;
	rHandXFrom = 0;

	rHandYTo = 12;
	rHandYFrom = 0;

	ofxOscBundle beatRepeatBundle;
	ofxOscMessage message;
	
	message.setAddress("/live/master/device");
	message.addIntArg(0);
	message.addIntArg(2); //This is the interval
	message.addIntArg((int)lHandMapZ); //Value of the interval
	beatRepeatBundle.addMessage(message);
	message.clear();

	message.setAddress("/live/master/device");
	message.addIntArg(0);
	message.addIntArg(4); //This is the grid
	message.addIntArg((int)rHandMapX); //Value of the interval
	beatRepeatBundle.addMessage(message);
	message.clear();

	message.setAddress("/live/master/device");
	message.addIntArg(0);
	message.addIntArg(11); //This is the pitch
	message.addIntArg((int)rHandMapY); //Value of the interval
	beatRepeatBundle.addMessage(message);

	if (ofGetFrameNum() % timeDelay == 0); //Set time delay of bundle being sent
		sender.sendBundle(beatRepeatBundle); //Send to osc address
}

void OSCSend::beatReapeatChance(int percent) {
	ofxOscMessage message;
	message.setAddress("/live/master/device");
	message.addIntArg(0);
	message.addIntArg(0); //This is the chance perameter
	message.addIntArg(percent); //Value of the interval
	sender.sendMessage(message);
}