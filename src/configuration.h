// * Name: configuration.h
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 12/06/2017
// * Copyright (c) 2017 Stenden University

#ifndef Configuration_h
#define Configuration_h

#include "ofMain.h"

struct Camera_Configuration
{
    int camera_width;
    int camera_height;
	int history;
    int mog_threshold;
	int threshold;
    int dilate;
    int erode;
	int blur;
	
    float shadow_pixel_ratio;
	
    bool track_shadows;
	bool bFlipH;
	bool bFlipV;
	bool bUseMask;
    bool show_shadows;
	
    vector<ofPoint> mask_coordinates;
};


struct Tracking_Configuration
{
	int threshold;
    int min_area;
    int max_area;
	
    float blob_dying_time;
	int persistance;
    int max_distance;
    int min_size_one;
    int min_size_two;
    int min_size_three;
	int history;
	
    ofPoint start_position;
    ofPoint end_position;
    int camera_width;
    int camera_height;
	
    bool flip_vertically;
	int offset;
};

struct Configuration
{
    bool use_csv_logging;
    Camera_Configuration camera_config;
    Tracking_Configuration tracking_config;
};

struct Post_Data
{
    Post_Data(string count, string timestamp)
	{
        this->count = count;
        this->timestamp = timestamp;
	}
	
    string count;
    string timestamp;
};

#endif /* Configuration_h */
