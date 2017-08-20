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
        config.use_csv_logging = configFile["CrowdStream"]["AppConfig"]["usecsvlogging"].asBool();
		
        config.camera_config.camera_width = configFile["CrowdStream"]["CameraConfig"]["camerawidth"].asInt();
        config.camera_config.camera_height = configFile["CrowdStream"]["CameraConfig"]["cameraheight"].asInt();
	
        config.camera_config.dilate = configFile["CrowdStream"]["CameraConfig"]["dilate"].asInt();
        config.camera_config.erode = configFile["CrowdStream"]["CameraConfig"]["erode"].asInt();
        config.camera_config.blur = configFile["CrowdStream"]["CameraConfig"]["blur"].asInt();
        config.camera_config.threshold = configFile["CrowdStream"]["CameraConfig"]["threshold"].asInt();
		
        config.camera_config.mog_threshold = configFile["CrowdStream"]["CameraConfig"]["mogthreshold"].asInt();
        config.camera_config.history = configFile["CrowdStream"]["CameraConfig"]["history"].asInt();
        config.camera_config.track_shadows = configFile["CrowdStream"]["CameraConfig"]["trackshadows"].asInt();
        config.camera_config.shadow_pixel_ratio = configFile["CrowdStream"]["CameraConfig"]["shadowPixelRatio"].asFloat();
		
        config.camera_config.flip_horizontal = configFile["CrowdStream"]["CameraConfig"]["fliphorizontally"].asBool();
        config.camera_config.flip_vertical = configFile["CrowdStream"]["CameraConfig"]["flipveritcally"].asBool();
        config.camera_config.use_mask = configFile["CrowdStream"]["CameraConfig"]["usemask"].asBool();
        config.camera_config.show_shadows = configFile["CrowdStream"]["CameraConfig"]["showshadowimage"].asBool();

		vector<ofPoint> pts;
        int maskSize = int(configFile["CrowdStream"]["CameraConfig"]["MaskArea"].size());
		for (int i = 0 ; i < maskSize; i++) {
            ofPoint pt = ofPoint(configFile["CrowdStream"]["CameraConfig"]["MaskArea"][i]["coordx"].asInt(),configFile["CrowdStream"]["CameraConfig"]["MaskArea"][i]["coordy"].asInt());
			pts.push_back(pt);
		}
        config.camera_config.mask_coordinates = pts;
		
		// Tracking Configuration
        config.tracking_config.threshold = configFile["CrowdStream"]["TrackingConfig"]["threshold"].asInt();
        config.tracking_config.min_area = configFile["CrowdStream"]["TrackingConfig"]["minarea"].asInt();
        config.tracking_config.max_area = configFile["CrowdStream"]["TrackingConfig"]["maxarea"].asInt();
        config.tracking_config.start_position = ofPoint(configFile["CrowdStream"]["TrackingConfig"]["startposx"].asInt(),configFile["CrowdStream"]["TrackingConfig"]["startposy"].asInt());
        config.tracking_config.offset = configFile["CrowdStream"]["TrackingConfig"]["offset"].asInt();
        config.tracking_config.flip_vertically = configFile["CrowdStream"]["TrackingConfig"]["flipvertically"].asBool();
		
        config.tracking_config.persistance = configFile["CrowdStream"]["TrackingConfig"]["persistance"].asInt();
		
        config.tracking_config.history = config.camera_config.history;
		
        config.tracking_config.blob_dying_time = configFile["CrowdStream"]["TrackingConfig"]["blobdyingtime"].asFloat();
		
        config.tracking_config.min_size_one = configFile["CrowdStream"]["TrackingConfig"]["minsizeone"].asInt();
        config.tracking_config.min_size_two = configFile["CrowdStream"]["TrackingConfig"]["minsizetwo"].asInt();
        config.tracking_config.min_size_three = configFile["CrowdStream"]["TrackingConfig"]["minsizethree"].asInt();
        config.tracking_config.max_distance = configFile["CrowdStream"]["TrackingConfig"]["maxdistance"].asInt();
		
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
