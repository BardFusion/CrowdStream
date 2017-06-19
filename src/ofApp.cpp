// * Name: ofApp.cpp
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 04/06/2017
// * Copyright (c) 2017 Stenden University


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(25);
	
    cout << "----------------- Project AirMore -----------------" << endl;
	
	configManager.loadConfiguration("config.json");
	
	_logToCsv = configManager.getConfiguration().useCsvLogging;
	_logToServer = configManager.getConfiguration().useHttp;
	
	cameraManager.setup(configManager.getConfiguration().cameraConfig);
	trackingManager.setup(configManager.getConfiguration().trackingConfig);
	
	if (_logToServer) httpManager.setup(configManager.getConfiguration().httpConfig);
	if (_logToCsv) csvManager.setup("csvlogs");
	
	ofAddListener(trackingManager.blobIn, this, &ofApp::blobIn);
	ofAddListener(trackingManager.blobOut, this, &ofApp::blobOut);
}

//--------------------------------------------------------------
void ofApp::exit()
{
	if (_logToServer) httpManager.close();
	if (_logToCsv) csvManager.close();
		
	ofRemoveListener(trackingManager.blobIn, this, &ofApp::blobIn);
	ofRemoveListener(trackingManager.blobOut, this, &ofApp::blobOut);
}

//--------------------------------------------------------------
void ofApp::update()
{
	cameraManager.update();
	trackingManager.update(cameraManager.getImage());
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofPushMatrix();
	ofScale(1,1);
	cameraManager.draw();
	trackingManager.draw();
	ofPopMatrix();
	
	stringstream ss;
    ss << "Project AirMore" << endl << endl;
	ss << "People In: " << peopleIn;
	ss << " People Out: " << peopleOut;
    ss << " Count: " << (peopleIn-peopleOut);
    ss << " FPS: " << int(ofGetFrameRate()) << endl;
    ofDrawBitmapStringHighlight(ss.str(), int(ofGetWidth() * 0.05), int(ofGetHeight() * 0.8));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::blobIn(int &val)
{
	peopleIn += val;
    if (val > 0)
    {
        cout << val << " Person(s) Came In" << ", Count: " << (peopleIn-peopleOut) << endl;
    }
	
	if (_logToServer) httpManager.post(ofToString(val));
	if (_logToCsv) csvManager.addRecord(ofToString(val), ofGetTimestampString("%Y-%m-%d %H:%M:%S"));
}

//--------------------------------------------------------------
void ofApp::blobOut(int &val)
{
	peopleOut += abs(val);
    if (abs(val) > 0)
    {
        cout << abs(val) << " Person(s) Went Out" << ", Count: " << (peopleIn-peopleOut) << endl;
    }
	
	if (_logToServer) httpManager.post(ofToString(val));
	if (_logToCsv) csvManager.addRecord(ofToString(val), ofGetTimestampString("%Y-%m-%d %H:%M:%S"));
}
