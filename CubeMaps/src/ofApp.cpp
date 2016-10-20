#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    printGLInfo();

    //ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofBackground(40);
    
  
    cubeMap.loadImages("textures/posx.jpg", "textures/negx.jpg",
                       "textures/posy.jpg", "textures/negy.jpg",
                       "textures/posz.jpg", "textures/negz.jpg");
    
    //--------------------------------
    

    
    if(ofIsGLProgrammableRenderer()){
        _shaderName = "GL330/reflection";
    }else{
        _shaderName = "GL120/reflection";
    }
    
    shader.load(_shaderName);
    
    shaderManager.load(_shaderName);
    shaderManager.useCamera(&cam);
    shaderManager.useCubeMap(&cubeMap);
    //--------------------------------
    
    ofSetSphereResolution(128);
    radius		= 180.f;
    center.set(0, 0, 0);
    
    sphere.setRadius(radius);
    
    box.set(850);

    cylinder.set(70, 150);
    
    //------------------------
    setupGui();
    
}



//--------------------------------------------------------------
void ofApp::update() {
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    cam.begin();
    
    ofDrawAxis(1000);

    if(ofIsGLProgrammableRenderer()){
        
        
        shaderManager.drawCubeMapEnvironment(2000);

        shaderManager.begin();
        drawScene();
        shaderManager.end();
    
        
        
    }else{
        
        cubeMap.bind();
        
        cubeMap.drawSkybox(1500);
        
        shader.begin();
        shader.setUniform1i("envMap", 0);
        
        drawScene();
        shader.end();
        cubeMap.unbind();
        
    }
    
   
 
    
    cam.end();
    ofDisableDepthTest();
    
    //gui.draw();
    ofDrawBitmapString(shaderManager.shaderName(), 20, ofGetHeight()-30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            cout<<"\n**********************************\n"<<endl;
            cout<<"- RELOADING SHADER: \n"<<endl;
            //shaderManager.reload();
            shader.load(_shaderName);
            cout<<"\n**********************************\n"<<endl;
            break;
        
        case '1':
            shaderManager.load("normMapPhong");
            break;
        case '2':
            shaderManager.load("normMap");
            break;
            

		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


//--------------------------------------------------------------

void ofApp::drawScene(){
    
    //SPHERE
    ofSetColor(255, 255, 255, 255);
    ofPushMatrix();
    ofTranslate(center.x, center.y, center.z-300);
    ofRotate(ofGetElapsedTimef() * .8 * RAD_TO_DEG, 0, 1, 0);
    
    sphere.draw();
    ofPopMatrix();
    
    //BOX-SMALL
    ofPushMatrix();
    ofTranslate(0, 0, cos(ofGetElapsedTimef()*1.4) * 100.f + 100);
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

void ofApp::printGLInfo(){
     cout<<"------------------------------\n"<<
     "IsGLProgrammableRederer: "<< ofIsGLProgrammableRenderer() <<"\n"<<
     "GL-Version-Major: "<< ofGetGLRenderer()->getGLVersionMajor() <<"\n"<<
    "GL-Version-Minor: "<< ofGetGLRenderer()->getGLVersionMinor() <<"\n" <<
    "GLSL Version: "<<ofGLSLVersionFromGL(ofGetGLRenderer()->getGLVersionMajor(), ofGetGLRenderer()->getGLVersionMinor())<<
    "\n------------------------------"<<endl;

}
//--------------------------------------------------------------
void ofApp::setupGui(){
    
    gui.setup();
    gui.add(reflectivity.set("Reflectivity", 0.8, 0.0, 1.0 ));

}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
