// * Name: configurationManager.h
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 05/06/2017
// * Copyright (c) 2017 Stenden University

#ifndef ConfigurationManager_h
#define ConfigurationManager_h

#include <stdio.h>
#include "ofxJSON.h"
#include "ofMain.h"
#include "configuration.h"

class ConfigurationManager
{
	public:
	
		//! Load the Config file
		void loadConfiguration(string file);
	
		//! Print to the Console
		void printConfiguration();
	
		//! Get the Configs
		Configuration getConfiguration();
	
	private:
		ofxJSONElement configFile;
		Configuration config;
};
#endif /* ConfigurationManager_h */
