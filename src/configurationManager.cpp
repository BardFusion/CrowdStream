// * Name: configurationManager.cpp
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 04/06/2017
// * Copyright (c) 2017 Stenden University

#include "configurationManager.h"

void ConfigurationManager::loadConfiguration(string file)
{
	cout << "Loading Configuration";
	if (!configFile.open(file))
	{
		cout << " - Could not find the Configuration File!" << endl;
		return;
	}
	else
	{
		cout << " - Configuration File Found!" << endl;
		
        // App Settings
        config.use_csv_logging = configFile["Footfall"]["AppConfig"]["usecsvlogging"].asBool();
		
        config.camera_config.camera_width = configFile["Footfall"]["CameraConfig"]["camerawidth"].asInt();
        config.camera_config.camera_height = configFile["Footfall"]["CameraConfig"]["cameraheight"].asInt();
	
        config.camera_config.dilate = configFile["Footfall"]["CameraConfig"]["dilate"].asInt();
        config.camera_config.erode = configFile["Footfall"]["CameraConfig"]["erode"].asInt();
        config.camera_config.blur = configFile["Footfall"]["CameraConfig"]["blur"].asInt();
        config.camera_config.threshold = configFile["Footfall"]["CameraConfig"]["threshold"].asInt();
		
        config.camera_config.mog_threshold = configFile["Footfall"]["CameraConfig"]["mogthreshold"].asInt();
        config.camera_config.history = configFile["Footfall"]["CameraConfig"]["history"].asInt();
        config.camera_config.track_shadows = configFile["Footfall"]["CameraConfig"]["trackshadows"].asInt();
        config.camera_config.shadow_pixel_ratio = configFile["Footfall"]["CameraConfig"]["shadowPixelRatio"].asFloat();
		
        config.camera_config.flip_horizontal = configFile["Footfall"]["CameraConfig"]["fliphorizontally"].asBool();
        config.camera_config.flip_vertical = configFile["Footfall"]["CameraConfig"]["flipveritcally"].asBool();
        config.camera_config.use_mask = configFile["Footfall"]["CameraConfig"]["usemask"].asBool();
        config.camera_config.show_shadows = configFile["Footfall"]["CameraConfig"]["showshadowimage"].asBool();

		vector<ofPoint> pts;
        int maskSize = int(configFile["Footfall"]["CameraConfig"]["MaskArea"].size());
		for (int i = 0 ; i < maskSize; i++) {
			ofPoint pt = ofPoint(configFile["Footfall"]["CameraConfig"]["MaskArea"][i]["coordx"].asInt(),configFile["Footfall"]["CameraConfig"]["MaskArea"][i]["coordy"].asInt());
			pts.push_back(pt);
		}
        config.camera_config.mask_coordinates = pts;
		
		// Tracking Configuration
        config.tracking_config.threshold = configFile["Footfall"]["TrackingConfig"]["threshold"].asInt();
        config.tracking_config.min_area = configFile["Footfall"]["TrackingConfig"]["minarea"].asInt();
        config.tracking_config.max_area = configFile["Footfall"]["TrackingConfig"]["maxarea"].asInt();
        config.tracking_config.start_position = ofPoint(configFile["Footfall"]["TrackingConfig"]["startposx"].asInt(),configFile["Footfall"]["TrackingConfig"]["startposy"].asInt());
        config.tracking_config.offset = configFile["Footfall"]["TrackingConfig"]["offset"].asInt();
        config.tracking_config.flip_vertically = configFile["Footfall"]["TrackingConfig"]["flipvertically"].asBool();
		
        config.tracking_config.persistance = configFile["Footfall"]["TrackingConfig"]["persistance"].asInt();
		
        config.tracking_config.history = config.camera_config.history;
		
        config.tracking_config.blob_dying_time = configFile["Footfall"]["TrackingConfig"]["blobdyingtime"].asFloat();
		
        config.tracking_config.min_size_one = configFile["Footfall"]["TrackingConfig"]["minsizeone"].asInt();
        config.tracking_config.min_size_two = configFile["Footfall"]["TrackingConfig"]["minsizetwo"].asInt();
        config.tracking_config.min_size_three = configFile["Footfall"]["TrackingConfig"]["minsizethree"].asInt();
        config.tracking_config.max_distance = configFile["Footfall"]["TrackingConfig"]["maxdistance"].asInt();
		
        config.tracking_config.camera_width = config.camera_config.camera_width;
        config.tracking_config.camera_height = config.camera_config.camera_height;
	}
}

Configuration ConfigurationManager::getConfiguration()
{
	return config;
}

void ConfigurationManager::printConfiguration()
{
	cout << configFile.getRawString() << endl;
}
