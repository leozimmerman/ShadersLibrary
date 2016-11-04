#pragma once

#include "ofMain.h"
#include "GeometryShaderManager.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed  (int key);
    
    void setupLights();
    void setupVbos();
    void setupGui();
    
    void updateLights();
    void updateMaterial();
    
    void drawScene();
    void drawLights();
    
    void printGLInfo();
    
    ofLight pointLight;
	ofLight spotLight;
	ofLight directionalLight;
	
	ofMaterial material;
    
    ofEasyCam cam;
		
    ofSpherePrimitive sphere;
    ofCylinderPrimitive cylinder;
    ofBoxPrimitive box;
    ofVbo sphereVbo, boxVbo, cylinderVbo;
    
    float radius;
    ofVec3f center;
    
    GeometryShaderManager shaderManager;
    
    ofxPanel gui;
    
    ofParameter<float> cubeSize;
    
    ofParameterGroup lightParameters;
    ofParameter<bool> bPointLight,  bSpotLight, bDirLight;
    ofParameter<int> spotCutOff; //0-90 degrees
    ofParameter<int> spotConcentration;// 0 - 128
    
    ofParameterGroup materialParameters;
    ofParameter<ofFloatColor> diffuse;
    ofParameter<ofFloatColor> ambient;
    ofParameter<ofFloatColor> specular;
    ofParameter<ofFloatColor> emissive;
    ofParameter<float> shininess;//0-128

    void pointLightChanged(bool & bPointLight);
    void spotLightChanged(bool & bSpotLight);
    void dirLightChanged(bool & bDirLight);
    

    
    
};
