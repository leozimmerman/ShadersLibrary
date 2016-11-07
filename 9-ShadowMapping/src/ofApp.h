#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "ShadowMapper.h"

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    void drawScene();
    
    void setupPrimitives();
    
    void setupGui();
    
    void printGLInfo();
    
    ofEasyCam cam;
    
    ShadowMapper shadow;
    
    ofSpherePrimitive sphere;
    ofBoxPrimitive floor;
    ofBoxPrimitive wall;
    vector<ofBoxPrimitive> boxes;
    
    ofxPanel gui;
    
    ofParameterGroup lightCamParameters;
    ofParameter<float> g_nearClip;
    ofParameter<float> g_farClip;
    ofParameter<int> g_y;
    ofParameter<int> g_z;
    
    ofParameterGroup uniforms;
    ofParameter<float> g_intensity;
    ofParameter<float> g_variance;
    ofParameter<float> g_blurFactor;

    
};
