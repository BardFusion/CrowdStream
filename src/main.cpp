// * Name: main.cpp
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 06/06/2017
// * Copyright (c) 2017 Stenden University

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(320*3,300,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
