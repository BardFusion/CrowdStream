// * Name: ofApp.h
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 01/06/2017
// * Copyright (c) 2017 Stenden University

#pragma once

#include "ofMain.h"
#include "ConfigurationManager.h"
#include "CameraManager.h"
#include "TrackingManager.h"
#include "HTTPManager.h"
#include "CsvManager.h"

class ofApp : public ofBaseApp
{
	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		
		ConfigurationManager configManager;
		CameraManager cameraManager;
		TrackingManager trackingManager;
		HTTPManager httpManager;
		CsvManager csvManager;
	
		void blobIn(int &val);
		void blobOut(int &val);
	
		bool _logToCsv;
		bool _logToServer;
		int peopleIn;
		int peopleOut;
};
