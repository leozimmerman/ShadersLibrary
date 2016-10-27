#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    printGLInfo();

    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofBackground(40);
    
    shader.setGeometryInputType(GL_POINTS);
    shader.setGeometryOutputType(GL_LINE_STRIP);
    shader.setGeometryOutputCount(2);
    
    shader.setupShaderFromFile(GL_VERTEX_SHADER, "lines.vert");
    shader.setupShaderFromFile(GL_FRAGMENT_SHADER, "lines.frag");
    shader.setupShaderFromFile(GL_GEOMETRY_SHADER_EXT, "lines.geom");
    shader.linkProgram();
 
    
    ofBoxPrimitive box;
    box.set(300);
    ofMesh mesh = box.getMesh();
    verts = mesh.getVertices();
    
    GLint vertexLocation = shader.getAttributeLocation("position");
    
    //Generate & Bind Buffer:
    glGenBuffers(1, &verticesVboID);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVboID);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(ofVec3f),  &verts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Generate & Bind Vertex Array:
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVboID);
    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(ofVec3f), 0);
    glBindVertexArray(0);
    
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
    
    glBindVertexArray(vaoID);
    glDrawArrays(GL_POINTS, 0, verts.size());
    
    shader.end();

    cam.end();
    ofDisableDepthTest();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
 
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
//--------------------------------------------------------------

void ofApp::printGLInfo(){
    
    cout<<"IsGLProgrammableRederer: "<< ofIsGLProgrammableRenderer() <<endl;
    cout<<"GL-Version-Major: "<< ofGetGLRenderer()->getGLVersionMajor() <<endl;
    cout<<"GL-Version-Minor: "<< ofGetGLRenderer()->getGLVersionMinor() <<endl;
    cout<<"GLSL Version: "<<ofGLSLVersionFromGL(ofGetGLRenderer()->getGLVersionMajor(), ofGetGLRenderer()->getGLVersionMinor())<<endl;

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
