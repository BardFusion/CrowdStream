// * Name: cameraManager.cpp
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 11/06/2017
// * Copyright (c) 2017 Stenden University

#include "cameraManager.h"

void CameraManager::setup(Camera_Configuration camera_config)
{
	cout << "Setting Up Camera Manager";
    useMask_ = camera_config.bUseMask;
	
	// Check whether the mask should be generated
    if (useMask_)
	{
		// Get the Mask Coordinates
        for (unsigned long i = 0; i < camera_config.mask_coordinates.size(); i++)
		{
            cv::Point p = cv::Point(int(camera_config.mask_coordinates[i].x),int(camera_config.mask_coordinates[i].y));
            mask_points_.push_back(p);
		}
		
        mask = cvCreateMat(camera_config.camera_height, camera_config.camera_width, CV_8UC1);
        combined_mask = cvCreateMat(camera_config.camera_height, camera_config.camera_width, CV_8UC1);
		
		// Fill the Mat with black
		for(int i=0; i<mask.cols; i++)
			for(int j=0; j<mask.rows; j++)
				mask.at<uchar>(cv::Point(i,j)) = 0;
		
		vector<cv::Point> polyright;
        approxPolyDP(mask_points_, polyright, 1.0, true);
        fillConvexPoly(mask,&polyright[0],int(polyright.size()),255,8,0);
	}
	
	// Setup the Background MOG2
    pMOG2 = new BackgroundSubtractorMOG2(camera_config.history,
                                         camera_config.mog_threshold,
                                         camera_config.track_shadows
										 );
	// This is the ratio of the shadow detection. I.e how many times lighter the shadow needs to be to be considered a blob.
    pMOG2->setDouble("fTau", double(camera_config.shadow_pixel_ratio));
	
#ifdef USE_VIDEO
	cout << " - Using Video" << endl;
    video_player.load("testFootageOFFICIAL-ONE-EDIT.mp4");
    video_player.setLoopState(OF_LOOP_NORMAL);
    video_player.play();
#endif
	
#ifdef USE_WEBCAM
	cout << " - Using Web Camera" << endl;
	videoGrabber.setVerbose(true);
    videoGrabber.setup(camera_config.camerawidth, camera_config.cameraheight);
#endif
	
#ifdef USE_PI_CAM
	cout << " - Using Pi Camera" << endl;
    piCamera.setup(camera_config.camerawidth,camera_config.cameraheight,true);
    piCamera.setFlips(camera_config.bFlipH,camera_config.bFlipV);
#endif
	
    threshold_ = camera_config.threshold;
    show_shadows_ = camera_config.show_shadows;
    dilate_amount_ = camera_config.dilate;
    erode_amount_ = camera_config.erode;
    blur_ = camera_config.blur;
}

void CameraManager::update()
{
#ifdef USE_VIDEO
    video_player.update();
	
    if (video_player.isFrameNew())
	{
        copy(video_player, video_matrix);
	}
#endif

#ifdef USE_WEBCAM
	videoGrabber.update();
	
	if (videoGrabber.isFrameNew())
	{
		copy(videoGrabber, videoMatrix);
	}
#endif

#ifdef USE_PI_CAM
	videoMatrix = piCamera.grab();
#endif
	
    if (!video_matrix.empty())
	{
		// Blur the original image
        GaussianBlur(video_matrix, blur_);
		
		// Process the MOG
        if (useMask_)
		{
            video_matrix.copyTo(combined_mask, mask);
            pMOG2->operator()(combined_mask, processed_mog);
		}
		else
		{
            pMOG2->operator()(video_matrix,processed_mog);
		}
		
		// Get the background image
		pMOG2->getBackgroundImage(background);
		
		// If you want to see the effect of the shadow ratio threshold. Set the showshadow config to true
		// Copy the MOG's output before processing the mat
		
        if(show_shadows_) copy(processed_mog, unprocessed_mog);
		
		// Image processing
        threshold(processed_mog,threshold_);
        blur(processed_mog,blur_);
        dilate(processed_mog,dilate_amount_);
        erode(processed_mog,erode_amount_);
        dilate(processed_mog,dilate_amount_);
        GaussianBlur(processed_mog, blur_*2);
		
		// Leave these two
        threshold(processed_mog,50);
        erode(processed_mog,2);
	}
}

void CameraManager::draw()
{
	ofPushMatrix();
	ofSetColor(255, 255, 255);
    drawMat(video_matrix, 0, 0,video_matrix.cols,video_matrix.rows);
    drawMat(processed_mog, video_matrix.cols, 0,video_matrix.cols,video_matrix.rows);
    ofDrawBitmapStringHighlight("Input Image", (video_matrix.cols/2)-45,video_matrix.rows+20);
    ofDrawBitmapStringHighlight("Processed Image", ((video_matrix.cols/2)*3)-65,video_matrix.rows+20);
	
    if(show_shadows_)
	{
        drawMat(unprocessed_mog, video_matrix.cols*2, 0,video_matrix.cols,video_matrix.rows);
        ofDrawBitmapStringHighlight("Shadows Image", ((video_matrix.cols/2)*5)-45,video_matrix.rows+20);
	}
	else
	{
        drawMat(background, video_matrix.cols*2, 0,video_matrix.cols,video_matrix.rows);
        ofDrawBitmapStringHighlight("Background", ((video_matrix.cols/2)*5)-45,video_matrix.rows+20);
	}
	ofPopMatrix();
}

Mat CameraManager::getImage()
{
    return processed_mog;
}
