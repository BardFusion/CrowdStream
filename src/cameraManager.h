// * Name: cameraManager.h
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 10/06/2017
// * Copyright (c) 2017 Stenden University

#ifndef CameraManager_h
#define CameraManager_h

#define USE_VIDEO
//#define USE_WEBCAM
//#define USE_PI_CAM

#include <stdio.h>
#include "ofMain.h"
#include "configuration.h"
#include "../../../../addons/ofxCv/src/ofxCv.h"

#ifdef USE_PI_CAM
	#include "ofxCvPiCam.h"
#endif

using namespace cv;
using namespace ofxCv;

class CameraManager
{
    private:

    #ifdef USE_VIDEO
        ofVideoPlayer video_player;
    #endif

    #ifdef USE_WEBCAM
        ofVideoGrabber videoGrabber;
    #endif

    #ifdef USE_PI_CAM
        ofxCvPiCam piCamera;
    #endif

        Mat video_matrix_;
        Mat processed_mog_;
        Mat mask_;
        Mat combined_mask_;
        Mat background_;
        Mat unprocessed_mog_;

        BackgroundSubtractorMOG2 *mog2_subtractor_;

        vector<cv::Point> mask_points_;
        bool use_mask_;
        bool show_shadows_;
        int threshold_;
        int dilate_amount_;
        int erode_amount_;
        int blur_;

	public:
		//! Setup
        void setup(Camera_Configuration camera_config);
	
		//! Update
		void update();
	
		//! Draw
		void draw();
	
		//! Get Image 
        Mat getImage();
};

#endif /* CameraManager_h */
