#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    printGLInfo();

    //ofSetLogLevel(OF_LOG_VERBOSE);
    //ofSetVerticalSync(true);
	//ofSetFrameRate(60);
    ofBackground(40);
    
    logoImage.load("of.png");
    logoImage.mirror(true, false);
    
    shaderManager.load("phong");
    
    shaderManager.setMaterial(&material);
    shaderManager.setCamera(&cam);
    shaderManager.useLight(&spotLight);
    shaderManager.useLight(&directionalLight);
    shaderManager.useLight(&pointLight);
    
    setupPrimitives();
    setupLights();
    setupGui();
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    updateLights();
    updateMaterial();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    cam.begin();
    
    ofDrawAxis(1000);
    
    shaderManager.begin();
        drawScene();
    shaderManager.end();
    
    drawLights();

    cam.end();
    ofDisableDepthTest();

    
    gui.draw();
    ofDrawBitmapString(shaderManager.shaderName(), 20, ofGetHeight()-30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            cout<<"***********************"<<endl;
            cout<<"-- RELOAD: "<<endl;
            shaderManager.reload();
            break;
        
        case '0':
            shaderManager.load("blank");
            break;
        case '1':
            shaderManager.load("phong");
            break;
        case '2':
            shaderManager.load("phongTex");
            break;
        case '3':
            shaderManager.load("blinnPhong");
            break;
        case '4':
            shaderManager.load("blinnPhongTex");
            break;
        case '5':
            shaderManager.load("gouraudPhong");
            break;
        case '6':
            shaderManager.load("gouraudPhongTex");
            break;
        case '7':
            shaderManager.load("gouraudBlinn");
            break;
        case '8':
            shaderManager.load("gouraudBlinnTex");
            break;
     

		default:
			break;
	}
}

//--------------------------------------------------------------

void ofApp::drawScene(){
    
    //SPHERE
    ofPushMatrix();
    ofTranslate(center.x, center.y, center.z-300);
    ofRotate(ofGetElapsedTimef() * .8 * RAD_TO_DEG, 0, 1, 0);
        sphere.draw();
    ofPopMatrix();
    
    //BOX-SMALL
    ofPushMatrix();
    ofTranslate(300, 300, cos(ofGetElapsedTimef()*1.4) * 300.f);
    ofRotate(ofGetElapsedTimef()*.6 * RAD_TO_DEG, 1, 0, 0);
    ofRotate(ofGetElapsedTimef()*.8 * RAD_TO_DEG, 0, 1, 0);
    cylinder.draw();
    ofPopMatrix();
    
    //BOX-BIG
    ofPushMatrix();
    ofTranslate(center.x, center.y, -900);
    ofRotate(ofGetElapsedTimef() * .2 * RAD_TO_DEG, 0, 1, 0);
    box.draw();
    ofPopMatrix();
    
    
}

//--------------------------------------------------------------
void ofApp::setupPrimitives(){
    
    ofSetSphereResolution(128);
    radius		= 180.f;
    center.set(0, 0, 0);
    
    sphere.setRadius(radius);
    sphere.mapTexCoordsFromTexture(logoImage.getTexture());
    
    box.set(850);
    box.mapTexCoordsFromTexture(logoImage.getTexture());
    
    cylinder.set(70, 150);
    cylinder.mapTexCoordsFromTexture(logoImage.getTexture());
    

}
//--------------------------------------------------------------
void ofApp::setupLights(){
    
    
    pointLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
    pointLight.setPointLight();
    
    spotLight.setDiffuseColor( ofColor(255.f, 0.f, 0.f));
    spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    spotLight.setSpotlight();
    spotLight.setSpotlightCutOff( 50 );
    spotLight.setSpotConcentration( 45 );
    
    directionalLight.setDiffuseColor(ofColor(0.f, 0.f, 255.f));
    directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setDirectional();
    directionalLight.setOrientation( ofVec3f(0, 90, 0) );

}
//--------------------------------------------------------------
void ofApp::updateLights(){
    
    pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
                           sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
                           -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
    
    spotLight.setOrientation( ofVec3f( 0, cos(ofGetElapsedTimef()) * RAD_TO_DEG, 0) );
    spotLight.setPosition( mouseX, mouseY, 200);
    
    spotLight.setSpotConcentration(spotConcentration);
    spotLight.setSpotlightCutOff(spotCutOff);
    
}
//--------------------------------------------------------------
void ofApp::updateMaterial(){
    
    material.setColors(diffuse, ambient, specular, emissive);
    material.setShininess(shininess);
    
}

//--------------------------------------------------------------
void ofApp::drawLights(){
    
    ofPushStyle();
    
    ofSetColor( pointLight.getDiffuseColor() );
    if(bPointLight) pointLight.draw();
    
    ofSetColor(255, 255, 255);
    if(bDirLight) directionalLight.draw();
    
    ofSetColor( spotLight.getDiffuseColor() );
    if(bSpotLight) spotLight.draw();
    
    ofPopStyle();
    
}
//--------------------------------------------------------------

void ofApp::printGLInfo(){
    
    cout<<"IsGLProgrammableRederer: "<< ofIsGLProgrammableRenderer() <<endl;
    cout<<"GL-Version-Major: "<< ofGetGLRenderer()->getGLVersionMajor() <<endl;
    cout<<"GL-Version-Minor: "<< ofGetGLRenderer()->getGLVersionMinor() <<endl;
    cout<<"GLSL Version: "<<ofGLSLVersionFromGL(ofGetGLRenderer()->getGLVersionMajor(), ofGetGLRenderer()->getGLVersionMinor())<<endl;

}
//--------------------------------------------------------------
void ofApp::setupGui(){
    
    bPointLight.addListener(this, &ofApp::pointLightChanged);
    bSpotLight.addListener(this, &ofApp::spotLightChanged);
    bDirLight.addListener(this, &ofApp::dirLightChanged);
    
    bUseTexture.addListener(this, &ofApp::textureToggled);
    
    gui.setup();
    
    lightParameters.setName("Lights");
    lightParameters.add(bPointLight.set("PointLight",true));
    lightParameters.add(bDirLight.set("DirectionalLight", true));
    lightParameters.add(bSpotLight.set("SpotLight", true));
    lightParameters.add(spotCutOff.set("Spot CuttOff", 50, 0, 90));
    lightParameters.add(spotConcentration.set("Spot Concentr.", 45, 0, 128));
    
    
    materialParameters.setName("Material");
    materialParameters.add(shininess.set("shinines", 100, 0, 128));
    
    materialParameters.add(diffuse.set("diffuse", ofFloatColor(0.8, 1.0),
                                       ofFloatColor(0.0), ofFloatColor(1.0)) );
    materialParameters.add(ambient.set("ambient", ofFloatColor(0.2, 1.0),
                                       ofFloatColor(0.0), ofFloatColor(1.0)) );
    materialParameters.add(specular.set("specular", ofFloatColor(1.0, 1.0),
                                        ofFloatColor(0.0), ofFloatColor(0.5)));
    materialParameters.add(emissive.set("emmisive", ofFloatColor(0.0, 1.0),
                                        ofFloatColor(0.0), ofFloatColor(1.0)));
    
    gui.add(lightParameters);
    gui.add(materialParameters);
    gui.add(bUseTexture.set("Use Texture",true));
    
   
}
//--------------------------------------------------------------
void ofApp::pointLightChanged(bool & bPointLight){
    shaderManager.toggleLight(&pointLight, bPointLight);
}
//--------------------------------------------------------------
void ofApp::spotLightChanged(bool & bSpotLight){
    shaderManager.toggleLight(&spotLight, bSpotLight);
}
//--------------------------------------------------------------
void ofApp::dirLightChanged(bool & bDirLight){
   shaderManager.toggleLight(&directionalLight, bDirLight);
}
//--------------------------------------------------------------
void ofApp::textureToggled(bool &bUseTexture){
    shaderManager.toggleTexture(&logoImage);
}

