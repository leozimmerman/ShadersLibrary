#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    printGLInfo();

//    ofSetLogLevel(OF_LOG_VERBOSE);
//    ofSetVerticalSync(true);
//	ofSetFrameRate(60);
    ofBackground(40);
    
    
    
    shader.setGeometryInputType(GL_TRIANGLES);
    shader.setGeometryOutputType(GL_LINE_STRIP);
    shader.setGeometryOutputCount(4);
    
    shader.setupShaderFromFile(GL_VERTEX_SHADER, "tessQuads.vert");
    shader.setupShaderFromFile(GL_FRAGMENT_SHADER, "tessQuads.frag");
    shader.setupShaderFromFile(GL_GEOMETRY_SHADER_EXT, "tessQuads.geom");
    shader.setupShaderFromFile(GL_TESS_CONTROL_SHADER, "tessQuads.cont");
    shader.setupShaderFromFile(GL_TESS_EVALUATION_SHADER, "tessQuads.eval");
    shader.linkProgram();
    glPatchParameteri(GL_PATCH_VERTICES, 4);
    // We work with 4 points per patch.

    
    setupVbos();
    
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
    
    shader.begin();
    
    shader.setUniform1f("u_tessLevelInner", tessLevelInner);
    shader.setUniform1f("u_tessLevelOuter", tessLevelOuter);
    
    drawScene();
    shader.end();
    
    

    cam.end();
    ofDisableDepthTest();

    
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
     
        
        case '1':
            shader.unload();
            shader.setupShaderFromFile(GL_VERTEX_SHADER, "tessTriang.vert");
            shader.setupShaderFromFile(GL_FRAGMENT_SHADER, "tessTriang.frag");
            shader.setupShaderFromFile(GL_GEOMETRY_SHADER_EXT, "tessTriang.geom");
            shader.setupShaderFromFile(GL_TESS_CONTROL_SHADER, "tessTriang.cont");
            shader.setupShaderFromFile(GL_TESS_EVALUATION_SHADER, "tessTriang.eval");
            shader.linkProgram();
            glPatchParameteri(GL_PATCH_VERTICES, 3);
            break;
            
        case '2':
            shader.unload();
            shader.setupShaderFromFile(GL_VERTEX_SHADER, "tessQuads.vert");
            shader.setupShaderFromFile(GL_FRAGMENT_SHADER, "tessQuads.frag");
            shader.setupShaderFromFile(GL_GEOMETRY_SHADER_EXT, "tessQuads.geom");
            shader.setupShaderFromFile(GL_TESS_CONTROL_SHADER, "tessQuads.cont");
            shader.setupShaderFromFile(GL_TESS_EVALUATION_SHADER, "tessQuads.eval");
            shader.linkProgram();
            glPatchParameteri(GL_PATCH_VERTICES, 4);
            break;
     

		default:
			break;
	}
}

//--------------------------------------------------------------

void ofApp::drawScene(){
    
    //SPHERE
    ofSetColor(255, 255, 255, 255);
    ofPushMatrix();
    ofTranslate(center.x, center.y, center.z-300);
    ofRotate(ofGetElapsedTimef() * .8 * RAD_TO_DEG, 0, 1, 0);
    sphereVbo.drawElements(GL_PATCHES, sphereVbo.getNumIndices());
    ofPopMatrix();
    
    //CYLINDER
    ofPushMatrix();
    ofTranslate(300, 300, cos(ofGetElapsedTimef()*1.4) * 300.f);
    ofRotate(ofGetElapsedTimef()*.6 * RAD_TO_DEG, 1, 0, 0);
    ofRotate(ofGetElapsedTimef()*.8 * RAD_TO_DEG, 0, 1, 0);
    cylinderVbo.drawElements(GL_PATCHES,  cylinderVbo.getNumIndices());
    ofPopMatrix();
    
    //BOX
    ofPushMatrix();
    ofTranslate(center.x, center.y, -1200);
    ofRotate(ofGetElapsedTimef() * .2 * RAD_TO_DEG, 0, 1, 0);
    boxVbo.drawElements(GL_PATCHES,  boxVbo.getNumIndices());
    ofPopMatrix();
    
    
}
//--------------------------------------------------------------
void ofApp::setupVbos(){
    
    ofIcoSpherePrimitive sphere;
    //ofSpherePrimitive sphere;
    ofCylinderPrimitive cylinder;
    ofBoxPrimitive box;
    ofPlanePrimitive plane;
    
    
    radius		= 180.f;
    center.set(0, 0, 0);
    
    sphere.setRadius(radius);
    sphere.setResolution(1);
    ofVboMesh sphereMesh = sphere.getMesh();
    sphereVbo.setMesh(sphereMesh, GL_DYNAMIC_DRAW);
    
    box.set(850);
    box.setResolution(1);
    ofVboMesh boxMesh = box.getMesh();
    boxVbo = boxMesh.getVbo();
    
    cylinder.set(70, 150);
    ofVboMesh cylinderMesh = cylinder.getMesh();
    cylinderVbo = cylinderMesh.getVbo();

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
    
    gui.setup();
    
    gui.add(tessLevelInner.set("INNER tess lev.", 1.0, 1.0, 5.0));
    gui.add(tessLevelOuter.set("OUTER tess lev, ", 1.0, 1.0, 5.0));
    
   
}
