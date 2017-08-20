// * Name: ofApp.h
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 01/06/2017
// * Copyright (c) 2017 Stenden University

#pragma once

#include "ofMain.h"
#include "configurationManager.h"
#include "cameraManager.h"
#include "trackingManager.h"
#include "csvManager.h"

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
		CsvManager csvManager;
	
		void blobIn(int &val);
		void blobOut(int &val);
	
        bool log_to_csv_;
        bool log_to_server_;
		int peopleIn;
		int peopleOut;
};
