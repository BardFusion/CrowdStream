// * Name: ofApp.cpp
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 04/06/2017
// * Copyright (c) 2017 Stenden University


#include "ofApp.h"

void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(25);
	
    cout << "----------------- Project AirMore -----------------" << endl;
	
	configManager.loadConfiguration("config.json");
	
    log_to_csv_ = configManager.getConfiguration().use_csv_logging;
	
    cameraManager.setup(configManager.getConfiguration().camera_config);
    trackingManager.setup(configManager.getConfiguration().tracking_config);

    if (log_to_csv_) csvManager.setup("csvlogs");
	
    ofAddListener(trackingManager.blob_in_, this, &ofApp::blobIn);
    ofAddListener(trackingManager.blob_out_, this, &ofApp::blobOut);
}

void ofApp::exit()
{
    if (log_to_csv_) csvManager.close();
		
    ofRemoveListener(trackingManager.blob_in_, this, &ofApp::blobIn);
    ofRemoveListener(trackingManager.blob_out_, this, &ofApp::blobOut);
}

void ofApp::update()
{
	cameraManager.update();
    trackingManager.update(cameraManager.getImage());
}

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

void ofApp::keyPressed(int key)
{

}

void ofApp::keyReleased(int key)
{

}

void ofApp::blobIn(int &val)
{
	peopleIn += val;
    if (val > 0)
    {
        cout << val << " Person(s) Came In" << ", Count: " << (peopleIn-peopleOut) << endl;
    }

    if (log_to_csv_) csvManager.addRecord(ofToString(val), ofGetTimestampString("%Y-%m-%d %H:%M:%S"));
}

void ofApp::blobOut(int &val)
{
    peopleOut += val;
    if (peopleOut > peopleIn)
    {
        cout << "Error, correcting out " << peopleOut << " --> " << peopleIn << endl;
        peopleOut = peopleIn;
    }
    else if (val > 0)
    {
        cout << val << " Person(s) Went Out" << ", Count: " << (peopleIn-peopleOut) << endl;
    }

    if (log_to_csv_) csvManager.addRecord(ofToString(val), ofGetTimestampString("%Y-%m-%d %H:%M:%S"));
}
