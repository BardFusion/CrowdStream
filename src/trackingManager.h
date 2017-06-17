// * Name: TrackingManager.h
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 06/06/2017
// * Copyright (c) 2017 Stenden University

#ifndef TrackingManager_h
#define TrackingManager_h

#include <stdio.h>
#include "ofMain.h"
#include "../../../../addons/ofxCv/src/ofxCv.h"
#include "blob.h"
#include "configuration.h"
#include "trackingHistory.h"

using namespace cv;
using namespace ofxCv;

class TrackingManager
{
	public:
		//! Setup the tracker
		void setup(Tracking_Configuration _trackingConfig);
	
		//! Pass the Camera image into the tracker
		void update(Mat processedMat);
	
		//! Draw the Tracker
		void draw();
	
		//! Close the Tracker
		void close();
	
		ofEvent<int> blobIn;
		ofEvent<int> blobOut;
	
	private:
		ofxCv::ContourFinder contourFinder;
		ofxCv::RectTrackerFollower<Blob> tracker;
		ofRectangle centerRect;
	
		TrackingHistory trackingHistory;
		bool _flipVertically;
	
		int _oneBlob;
		int _twoBlob;
		int _threeBlob;
		int _historyLength;
		int _camerawidth;
		int _cameraheight;
};

#endif /* TrackingManager_h */
