#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofBackground(40);
    //ofSetLogLevel(OF_LOG_VERBOSE);

    shadow.setup(ofGetWidth(), ofGetHeight());
    shadow.setBias( 0.01 );
    
    setupPrimitives();
    
    setupGui();

    printGLInfo();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle( ofToString(ofGetFrameRate()) );
    
    shadow.setLightPosition( ofVec3f(cos(ofGetElapsedTimef()*0.6) * 100, g_y, g_z) );
    shadow.setLightLookAt( ofVec3f(0,0,0), ofVec3f(0,1,0) );

    //range of the shadow camera:
    shadow.setRange(g_nearClip, g_farClip);

    shadow.setIntensity(g_intensity);
    shadow.setVariance( 2.0 / pow(10, g_variance) );
    shadow.setBlurFactor( g_blurFactor );
}

//--------------------------------------------------------------
void ofApp::draw(){

    //Render Depth Map
    ofEnableDepthTest();
    shadow.beginDepthPass();
        drawScene();
    shadow.endDepthPass();
    ofDisableDepthTest();


    //Render Scene
    ofEnableDepthTest();
    cam.begin();
  
    ofDrawAxis(1000);
    shadow.lightCam.draw();
    
    shadow.beginRenderPass( cam );
        drawScene();
    shadow.endRenderPass();
    
    cam.end();
    ofDisableDepthTest();
    
    //Draw Depth Map
    shadow.drawShadowMap(10, ofGetHeight()-310, 300, 300);
    
    
    gui.draw();
    ofDrawBitmapString(shadow.getShaderName(), 20, ofGetHeight()-30);
    
}

//--------------------------------------------------------------
void ofApp::drawScene() {
    
    for (int i=0; i<boxes.size(); i++){
        
        float x = sin( ofGetElapsedTimef() * 0.1 * i) * 100;
        float y = cos( ofGetElapsedTimef() * 0.1 * i) * 50;
        float z = - 10 + i * 10;
        
        boxes[i].setPosition(x, y, z);
        boxes[i].draw();
        
    }
    

    sphere.draw();
    floor.draw();
    wall.draw();
   
}

//--------------------------------------------------------------
void ofApp::setupPrimitives(){
    
    sphere.setRadius(30);
    sphere.getMesh().setColorForIndices(0, sphere.getMesh().getNumIndices(), ofColor::red);

    floor.set(500, 2, 250 );
    floor.setPosition(0, -70, -10);
    floor.getMesh().setColorForIndices(0, floor.getMesh().getNumIndices(), ofColor::yellow);
    
    wall.set(600, 300, 2 );
    wall.setPosition(0, 10, -100);
    wall.getMesh().setColorForIndices(0, wall.getMesh().getNumIndices(), ofColor::yellow);
    
    
    for (int i=0; i<10; i++){
        ofBoxPrimitive box;
        float size = 10 + i;
        box.set(size);
        box.getMesh().setColorForIndices(0, box.getMesh().getNumIndices(), ofColor::blue);
        boxes.push_back(box);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        
        case ' ':
            cout<<"***************************"<<endl;
            shadow.reloadShaders();
            break;
        
        case '1':
            shadow.setShader("simpleShadow");
            break;
        
        case '2':
            shadow.setShader("poissonSampling");
            break;
        
        case '3':
            shadow.setShader("esmShadow");
            break;
        
        case '4':
            shadow.setShader("vsmShadow");
            break;

        default:
        break;
    }
    
}
//--------------------------------------------------------------
void ofApp::setupGui(){
    
    gui.setup();
    
    lightCamParameters.setName("Light Cam");
    lightCamParameters.add(g_nearClip.set("near clip", 1, 0.0, 50));
    lightCamParameters.add(g_farClip.set("far clip", 300, 20, 1500));
    lightCamParameters.add(g_y.set("Y", 20, 0, 500));
    lightCamParameters.add(g_z.set("Z", 200, 0, 1000));
    
    uniforms.setName("Uniforms");
    uniforms.add(g_intensity.set("intensity (poisson)", 0.5, 0.0, 1.0));
    uniforms.add(g_variance.set("variance (VSM)", 4, 1, 6));
    uniforms.add(g_blurFactor.set("blur factor", 4.0, 0.0, 10.0));
    
    gui.add(lightCamParameters);
    gui.add(uniforms);

}
//--------------------------------------------------------------
void ofApp::printGLInfo(){
    
    cout<<"IsGLProgrammableRederer: "<< ofIsGLProgrammableRenderer() <<endl;
    cout<<"GL-Version-Major: "<< ofGetGLRenderer()->getGLVersionMajor() <<endl;
    cout<<"GL-Version-Minor: "<< ofGetGLRenderer()->getGLVersionMinor() <<endl;
    cout<<"GLSL Version: "<<ofGLSLVersionFromGL(ofGetGLRenderer()->getGLVersionMajor(), ofGetGLRenderer()->getGLVersionMinor())<<endl;
    
}
