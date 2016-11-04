#pragma once

#include "ofMain.h"

#include "CubeMapManager.h"
#include "ofxGui.h"
#include "ofxCubeMap.h"

class ofApp : public ofBaseApp{

public:
    
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    
    void setupGui();
    void drawScene();
    void printGLInfo();
    
    ofEasyCam cam;
		
    ofSpherePrimitive sphere;
    ofCylinderPrimitive cylinder;
    ofBoxPrimitive box;
    
    float radius;
    ofVec3f center;
    
    CubeMapManager shaderManager;
    
    ofxPanel gui;

    ofParameter<float> reflectivity;//0-128
    
    ofxCubeMap cubeMap;
    ofShader shader;
    string _shaderName;
};
