// * Name: cameraManager.cpp
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 11/06/2017
// * Copyright (c) 2017 Stenden University

#include "cameraManager.h"

void CameraManager::setup(Camera_Configuration camera_config)
{
	cout << "Setting Up Camera Manager";
    use_mask_ = camera_config.use_mask;
	
	// Check whether the mask should be generated
    if (use_mask_)
	{
		// Get the Mask Coordinates
        for (unsigned long i = 0; i < camera_config.mask_coordinates.size(); i++)
		{
            cv::Point p = cv::Point(int(camera_config.mask_coordinates[i].x),int(camera_config.mask_coordinates[i].y));
            mask_points_.push_back(p);
		}
		
        mask_ = cvCreateMat(camera_config.camera_height, camera_config.camera_width, CV_8UC1);
        combined_mask_ = cvCreateMat(camera_config.camera_height, camera_config.camera_width, CV_8UC1);
		
		// Fill the Mat with black
        for(int i=0; i<mask_.cols; i++)
            for(int j=0; j<mask_.rows; j++)
                mask_.at<uchar>(cv::Point(i,j)) = 0;
		
		vector<cv::Point> polyright;
        approxPolyDP(mask_points_, polyright, 1.0, true);
        fillConvexPoly(mask_,&polyright[0],int(polyright.size()),255,8,0);
	}
	
	// Setup the Background MOG2
    mog2_subtractor_ = new BackgroundSubtractorMOG2(camera_config.history,
                                         camera_config.mog_threshold,
                                         camera_config.track_shadows
										 );
	// This is the ratio of the shadow detection. I.e how many times lighter the shadow needs to be to be considered a blob.
    mog2_subtractor_->setDouble("fTau", double(camera_config.shadow_pixel_ratio));
	
#ifdef USE_VIDEO
	cout << " - Using Video" << endl;
    video_player.load("pivideoEdit.mp4");
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
        copy(video_player, video_matrix_);
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
	
    if (!video_matrix_.empty())
	{
		// Blur the original image
         GaussianBlur(video_matrix_, blur_);
		
		// Process the MOG
        if (use_mask_)
		{
            video_matrix_.copyTo(combined_mask_, mask_);
            mog2_subtractor_->operator()(combined_mask_, processed_mog_);
		}
		else
		{
            mog2_subtractor_->operator()(video_matrix_,processed_mog_);
		}
		
		// Get the background image
        mog2_subtractor_->getBackgroundImage(background_);

        // Copy the MOG's output before processing the mat is shadow is to be displayed
        if(show_shadows_) copy(processed_mog_, unprocessed_mog_);
		
        // Image processing to get a clear view of the differences
        // from the background image
        threshold(processed_mog_, threshold_);
        blur(processed_mog_, blur_);
        dilate(processed_mog_, dilate_amount_);
        erode(processed_mog_, erode_amount_);
        dilate(processed_mog_, dilate_amount_);
        GaussianBlur(processed_mog_, blur_*2);
        threshold(processed_mog_, threshold_ /2);
        erode(processed_mog_, erode_amount_/2);
    }
}

void CameraManager::draw()
{
	ofPushMatrix();
	ofSetColor(255, 255, 255);
    drawMat(video_matrix_, 0, 0,video_matrix_.cols,video_matrix_.rows);
    drawMat(processed_mog_, video_matrix_.cols, 0,video_matrix_.cols,video_matrix_.rows);
    ofDrawBitmapStringHighlight("Input Image", (video_matrix_.cols/2)-45,video_matrix_.rows+20);
    ofDrawBitmapStringHighlight("Processed Image", ((video_matrix_.cols/2)*3)-65,video_matrix_.rows+20);
	
    if(show_shadows_)
	{
        drawMat(unprocessed_mog_, video_matrix_.cols*2, 0,video_matrix_.cols,video_matrix_.rows);
        ofDrawBitmapStringHighlight("Shadows Image", ((video_matrix_.cols/2)*5)-45,video_matrix_.rows+20);
	}
	else
	{
        drawMat(background_, video_matrix_.cols*2, 0,video_matrix_.cols,video_matrix_.rows);
        ofDrawBitmapStringHighlight("Background", ((video_matrix_.cols/2)*5)-45,video_matrix_.rows+20);
	}
	ofPopMatrix();
}

Mat CameraManager::getImage()
{
    return processed_mog_;
}
