#pragma once

#include "ofMain.h"
#include "ofxShadersFX.h"
#include "ShaderManager.h"
#include "ofxGui.h"
#include "ofxCubeMap.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
  
    void setupGui();
    
    void drawScene();
  
    void printGLInfo();
    
    
    ofEasyCam cam;
		
    ofSpherePrimitive sphere;
    ofCylinderPrimitive cylinder;
    ofBoxPrimitive box;
    
    float radius;
    ofVec3f center;
    
    ShaderManager shaderManager;
    
    ofxPanel gui;
    

    ofParameter<float> reflectivity;//0-128

    
    
    ofxCubeMap cubeMap;
    ofShader shader;
    string _shaderName;
};
