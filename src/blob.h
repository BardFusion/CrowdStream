// * Name: Blob.h
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

        ofVec2f _currentPos;
        ofVec2f _originPos;
        int _blobWidth = 0;
        int _blobHeight = 0;

	public:

		//--------------------------------------------------------------
		void setup(const cv::Rect &track)
		{
			_currentPos = ofxCv::toOf(track).getCenter();
			_originPos = ofxCv::toOf(track).getCenter();
			_evaluating = false;
		}
		//--------------------------------------------------------------
		void update(const cv::Rect &track)
		{
			_currentPos = ofxCv::toOf(track).getCenter();
            _blobWidth = int(ofxCv::toOf(track).width);
            _blobHeight = int(ofxCv::toOf(track).height);
		}
		//--------------------------------------------------------------
		void draw()
		{
			ofPushStyle();
			
			if(_evaluating) {
				ofSetColor(255);
			}
			else {
				ofSetColor(0,255,0);
			}
			
			ofDrawCircle(_currentPos, 5);
			ofSetColor(255,0,0);
			ofDrawCircle(_originPos, 5);
			ofPopStyle();
		}
		//--------------------------------------------------------------
		void kill()
		{
			dead = true;
		}
	
		//--------------------------------------------------------------
		ofVec2f getCurrentPosition()
		{
			return _currentPos;
		}
	
		//--------------------------------------------------------------
		ofVec2f getOriginPosition()
		{
			return _originPos;
		}
	
		//--------------------------------------------------------------
		int getWidth()
		{
			return _blobWidth;
		}
	
        bool _evaluating = false;
};


#endif /* BLOB_H */
