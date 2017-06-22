// * Name: trackingManager.h
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
    private:
        ofxCv::ContourFinder contour_finder_;
        ofxCv::RectTrackerFollower<Blob> tracker_;
        ofRectangle center_rectangle_;

        TrackingHistory tracking_history_;
        bool flip_vertically_;

        int one_blob_;
        int two_blob_;
        int three_blob_;
        int history_length_;
        int camera_width_;
        int camera_height_;

	public:
		//! Setup the tracker
        void setup(Tracking_Configuration tracking_config);
	
		//! Pass the Camera image into the tracker
        void update(Mat processed_image);
	
		//! Draw the Tracker
        void draw();
	
		//! Close the Tracker
        void close();
	
        ofEvent<int> blob_in_;
        ofEvent<int> blob_out_;
};

#endif /* TrackingManager_h */
