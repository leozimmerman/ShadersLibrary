#pragma once

#include "ofMain.h"

#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    
    void setupVbos();

    void setupGui();

    
    void drawScene();
    
    void printGLInfo();
	
	ofMaterial material;
    
    ofEasyCam cam;
		
    ofShader shader;
    
    ofVbo sphereVbo, boxVbo, cylinderVbo;
    
    float radius;
    ofVec3f center;
    
    ofxPanel gui;
    
    ofParameter<int> tessLevelInner, tessLevelOuter;
    
    
    
};
