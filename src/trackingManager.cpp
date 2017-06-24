// * Name: trackingManager.cpp
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 12/06/2017
// * Copyright (c) 2017 Stenden University

#include "trackingManager.h"

void TrackingManager::setup(Tracking_Configuration tracking_config)
{
	cout << "Setting Up Tracking Manager" << endl;
    contour_finder_.setMinAreaRadius(tracking_config.min_area);
    contour_finder_.setMaxAreaRadius(tracking_config.max_area);
    contour_finder_.setThreshold(tracking_config.threshold);
    tracker_.setMaximumDistance(tracking_config.max_distance);
    tracker_.setPersistence((unsigned int)tracking_config.persistance);

    one_blob_ = tracking_config.min_size_one;
    two_blob_ = tracking_config.min_size_two;
    three_blob_ = tracking_config.min_size_three;
    flip_vertically_ = tracking_config.flip_vertically;
    history_length_ = tracking_config.history;
    camera_width_ = tracking_config.camera_width;
    camera_height_ = tracking_config.camera_height;
	
    tracking_history_.setup(one_blob_,two_blob_,three_blob_,int(tracking_config.start_position.y));
	
    center_rectangle_ = ofRectangle(0, tracking_config.start_position.y-(tracking_config.offset/2), camera_width_, tracking_config.offset);
}

void TrackingManager::update(Mat processed_image)
{
    if(!processed_image.empty())
	{
        // Allow for camera to setup during a set amount of time
        if (ofGetFrameNum() > (unsigned long)history_length_)
		{
            contour_finder_.findContours(processed_image);
            tracker_.track(contour_finder_.getBoundingRects());
		}
	}
	
    vector<Blob> &blobs = tracker_.getFollowers();
    int blob_count = 0;

    for(unsigned long i = 0; i < blobs.size(); i++)
	{
        if (center_rectangle_.inside(blobs[i].getCurrentPosition().x, blobs[i].getCurrentPosition().y) && !blobs[i].evaluating_)
		{            
            if (blobs[i].getCurrentPosition().y < blobs[i].getOriginPosition().y)
            {
                int blob_width = blobs[i].getWidth();
                if (blob_width > three_blob_)
                {
                    blob_count = 3;
                }

                if ((blob_width > two_blob_) && (blob_width < three_blob_))
                {
                    blob_count = 2;
                }

                if ((blob_width > one_blob_) && (blob_width < two_blob_))
                {
                    blob_count = 1;
                }

                tracking_history_.addNewData(blobs[i].getWidth(), true);
                ofNotifyEvent(blob_in_, blob_count, this);
                blobs[i].kill();
            }
            else if (blobs[i].getCurrentPosition().y > blobs[i].getOriginPosition().y)
            {
                int blob_count = 0;
                int blob_width = blobs[i].getWidth();
                if (blob_width > three_blob_)
                {
                    blob_count = 3;
                }

                if ((blob_width > two_blob_) && (blob_width < three_blob_))
                {
                    blob_count = 2;
                }

                if ((blob_width > one_blob_) && (blob_width < two_blob_))
                {
                    blob_count = 1;
                }

                tracking_history_.addNewData(blobs[i].getWidth(), false);
                ofNotifyEvent(blob_out_, blob_count, this);
                blobs[i].kill();
            }
            blobs[i].evaluating_ = true;
		}
        else if(blobs[i].evaluating_)
		{
            blobs[i].evaluating_ = false;
		}
	}
}

void TrackingManager::draw()
{
	ofSetLineWidth(1);
	ofFill();
    vector<Blob> &followers = tracker_.getFollowers();
    for(unsigned long i = 0; i < followers.size(); i++)
	{
		followers[i].draw();
	}
	ofSetColor(ofColor::red);
    contour_finder_.draw();
	
	ofNoFill();
	ofSetColor(255, 255, 255);
    ofDrawRectangle(center_rectangle_);
	
    tracking_history_.draw(camera_width_);
}
