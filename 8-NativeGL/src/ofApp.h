#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);

    
    
    void setupGui();
    
    void printGLInfo();
    
    ofEasyCam cam;
    
    ofShader shader;
    
    vector<ofVec3f> verts;
    
     GLuint verticesVboID;
     GLuint vaoID;
    
    
};
