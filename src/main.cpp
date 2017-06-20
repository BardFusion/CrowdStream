// * Name: main.cpp
// * Project: AirMore
// * Author: Project group - IT2B
// * Creation Date: 06/06/2017
// * Copyright (c) 2017 Stenden University

//--------------------------
// Specifies whether to use a
// GUI or just console output
//#define USE_GUI_FULLSCREEN
#define USE_GUI_WINDOWED
//#define USE_CONSOLE

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 384

#include "ofMain.h"
#include "ofApp.h"
#include "ofAppNoWindow.h"

//========================================================================
int main( ){
#ifdef USE_CONSOLE
        ofAppNoWindow window;
        ofSetupOpenGL(&window, WINDOW_WIDTH, WINDOW_HEIGHT, OF_FULLSCREEN);
#endif

#ifdef USE_GUI_FULLSCREEN
        ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, OF_FULLSCREEN);
#endif

#ifdef USE_GUI_WINDOWED
        ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, OF_WINDOW);
#endif

    // Start the application in either fullscreen, windowed
    // or console only mode as specified in ofMain.h
	ofRunApp(new ofApp());

}
