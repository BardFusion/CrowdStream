// * Name: blob.h
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 07/06/2017
// * Copyright (c) 2017 Stenden University

#ifndef BLOB_H
#define BLOB_H

#include <stdio.h>
#include "ofMain.h"
#include "../../../../addons/ofxCv/src/ofxCv.h"

class Blob : public ofxCv::RectFollower
{    
    private:

        ofVec2f current_position_;
        ofVec2f origininal_position_;
        int blob_width_ = 0;
        int blob_height_ = 0;

	public:
		void setup(const cv::Rect &track)
		{
            current_position_ = ofxCv::toOf(track).getCenter();
            origininal_position_ = ofxCv::toOf(track).getCenter();
            evaluating_ = false;
		}

		void update(const cv::Rect &track)
		{
            current_position_ = ofxCv::toOf(track).getCenter();
            blob_width_ = int(ofxCv::toOf(track).width);
            blob_height_ = int(ofxCv::toOf(track).height);
		}

		void draw()
		{
			ofPushStyle();
			
            if(evaluating_) {
				ofSetColor(255);
			}
			else {
				ofSetColor(0,255,0);
			}
			
            ofDrawCircle(current_position_, 5);
			ofSetColor(255,0,0);
            ofDrawCircle(origininal_position_, 5);
			ofPopStyle();
		}

		void kill()
		{
			dead = true;
        }

		ofVec2f getCurrentPosition()
		{
            return current_position_;
        }

		ofVec2f getOriginPosition()
		{
            return origininal_position_;
        }

		int getWidth()
		{
            return blob_width_;
		}
	
        bool evaluating_ = false;
};


#endif /* BLOB_H */
