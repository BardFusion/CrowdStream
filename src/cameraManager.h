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
	public:
		//! Setup
		void setup(Camera_Configuration _cameraConfig);
	
		//! Update
		void update();
	
		//! Draw
		void draw();
	
		//! Get Image 
		Mat getImage();
	
	private:
	
#ifdef USE_VIDEO
		ofVideoPlayer videoPlayer;
#endif
	
#ifdef USE_WEBCAM
		ofVideoGrabber videoGrabber;
#endif
	
#ifdef USE_PI_CAM
		ofxCvPiCam piCamera;
#endif
	
		Mat videoMatrix;
		Mat processedMog;
		Mat mask;
		Mat combinedMask;
		Mat background;
		Mat unprocessed_MOG;
	
		BackgroundSubtractorMOG2 *pMOG2;
	
		vector<cv::Point> _maskPts;
		bool _useMask;
		bool _showShadows;
		int _threshold;
		int _dilateAmount;
		int _erodeAmount;
		int _blur;
};

#endif /* CameraManager_h */
