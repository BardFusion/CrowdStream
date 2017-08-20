// * Name: trackingHistory.h
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 12/06/2017
// * Copyright (c) 2017 Stenden University

#ifndef TrackingHistory_h
#define TrackingHistory_h

#include "ofMain.h"

struct TrackingData
{
    TrackingData(int size, bool direction)
    {
        this->size = size;
        this->direction = direction;
    }

    int size;
    bool direction;
};

class TrackingHistory
{
    private:
        deque <TrackingData> tracking_history_;
        int min_size_;
        int mid_size_;
        int max_size_;
        int start_position_y_;

    public:
        void setup(int min_size,int mid_size, int max_size,int start_position_y)
        {
            min_size_ = min_size;
            mid_size_ = mid_size;
            max_size_ = max_size;
            start_position_y_ = start_position_y;
            tracking_history_.clear();
        }

        void addNewData(int size,bool direction)
        {
            tracking_history_.push_front(TrackingData(size,direction));
        }

        void draw(int width)
        {
            if(tracking_history_.size() > 15)
            {
                tracking_history_.pop_back();
            }

            ofPushStyle();
            ofSetLineWidth(2);
            // Draw the Center Line
            ofSetColor(ofColor::yellow);
            ofDrawLine(0,start_position_y_,width,start_position_y_);

            // Draw the Center X
            ofSetColor(ofColor::yellow);
            ofDrawLine(float(width*0.5),start_position_y_-5,float(width*0.5),start_position_y_+5);

            // Draw Min Size Guide
            ofSetColor(ofColor::cyan);
            ofDrawLine((float(width*0.5))-(min_size_/2),start_position_y_-10,(float(width*0.5))-(min_size_/2),start_position_y_+10);
            ofDrawLine((float(width*0.5))+(min_size_/2),start_position_y_-10,(float(width*0.5))+(min_size_/2),start_position_y_+10);

            // Draw Mid Size Guide
            ofSetColor(ofColor::purple);
            ofDrawLine((float(width*0.5))-(mid_size_/2),start_position_y_-10,(float(width*0.5))-(mid_size_/2),start_position_y_+10);
            ofDrawLine((float(width*0.5))+(mid_size_/2),start_position_y_-10,(float(width*0.5))+(mid_size_/2),start_position_y_+10);

            // Draw Max Size Guide
            ofSetColor(ofColor::limeGreen);
            ofDrawLine((float(width*0.5))-(max_size_/2),start_position_y_-10,(float(width*0.5))-(max_size_/2),start_position_y_+10);
            ofDrawLine((float(width*0.5))+(max_size_/2),start_position_y_-10,(float(width*0.5))+(max_size_/2),start_position_y_+10);
            ofPopStyle();

            // Draw Size Guides these are in 25pixel increments.
            int division = width/50;
            for (int i = 0; i < division; i++)
            {
                ofSetLineWidth(1);
                ofSetColor(ofColor::white);
                ofDrawLine((float(width*0.5))-(((1+i)*50)/2),start_position_y_-5,(float(width*0.5))-(((1+i)*50)/2),start_position_y_+5);
                ofDrawLine((float(width*0.5))+(((1+i)*50)/2),start_position_y_-5,(float(width*0.5))+(((1+i)*50)/2),start_position_y_+5);
            }

            ofPushStyle();
            ofSetLineWidth(2);
            for(unsigned long i = 0; i < tracking_history_.size(); i++)
            {
                if (tracking_history_[i].direction)
                {
                    ofSetColor(ofColor::green);
                }
                else
                {
                    ofSetColor(ofColor::red);
                }
                ofDrawLine((float(width*0.5))-(tracking_history_[i].size/2),(unsigned long)start_position_y_+(i*5),(float(width*0.5))+(tracking_history_[i].size/2),(unsigned long)start_position_y_+(i*5));
            }
            ofPopStyle();
        }
};

#endif /* TrackingHistory_h */
