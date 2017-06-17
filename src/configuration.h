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
	int camerawidth;
	int cameraheight;
	int history;
	int mogThreshold;
	int threshold;
	int dilateAmount;
	int erodeAmount;
	int blur;
	
	float shadowPixelRatio;
	
	bool bTrackShadows;
	bool bFlipH;
	bool bFlipV;
	bool bUseMask;
	bool bShowShadowImage;
	
	vector<ofPoint> maskCoord;
};


struct Tracking_Configuration
{
	int threshold;
	int minarea;
	int maxarea;
	
	float blobdyingtime;
	int persistance;
	int maxdistance;
	int minsizeone;
	int minsizetwo;
	int minsizethree;
	int history;
	
	ofPoint startPos;
	ofPoint endPos;
	int camerawidth;
	int cameraheight;
	
	bool flipvertically;
	int offset;
};

struct HTTP_Configuration
{
	int port;
	string postserver;
	string postextension;
	string secretkey;
	int maxretries;
	bool keepbackups;
};

struct Configuration
{
	bool useHttp;
	bool useCsvLogging;
	Camera_Configuration cameraConfig;
	Tracking_Configuration trackingConfig;
	HTTP_Configuration httpConfig;
};

struct Post_Data
{
	Post_Data(string count,string timestamp)
	{
		_count = count;
		_timestamp = timestamp;
	}
	
	string _count;
	string _timestamp;
};

#endif /* Configuration_h */
