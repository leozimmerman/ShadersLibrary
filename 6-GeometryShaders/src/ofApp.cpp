#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    printGLInfo();

    //ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofBackground(40);
    
    setupLights();
    
    
    
    ofShader* shader = shaderManager.shader();
    shader->setGeometryInputType(GL_TRIANGLES);//GL_POINTS, GL_TRIANGLES
    shader->setGeometryOutputType(GL_LINE_STRIP);//GL_TRIANGLE_STRIP
    shader->setGeometryOutputCount(6);
    shader->load("normals.vert", "normals.frag", "normals.geom");
    
    
    shaderManager.useLight(&spotLight);
    shaderManager.useLight(&directionalLight);
    shaderManager.useLight(&pointLight);
    shaderManager.useMaterial(&material);
    shaderManager.useCamera(&cam);
    
    //--------------------------------
    
    ofSetSphereResolution(128);
    radius		= 180.f;
    center.set(0, 0, 0);
    
    sphere.setRadius(radius);
    ofVboMesh sphereMesh = sphere.getMesh();
    sphereVbo = sphereMesh.getVbo();
    
    box.set(850);
    ofVboMesh boxMesh = box.getMesh();
    boxVbo = boxMesh.getVbo();
    
    cylinder.set(70, 150);
    ofVboMesh cylinderMesh = cylinder.getMesh();
    cylinderVbo = cylinderMesh.getVbo();
    
    //------------------------
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
    shaderManager.shader()->setUniform1f("u_size", cubeSize);
    
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
    
    ofShader* shader = shaderManager.shader();
    
    switch (key) {
        case ' ':
//            cout<<"*************************************"<<endl;
//            cout<<"RELOAD:"<<endl;
//            shaderManager.shader()->load("normals.vert", "normals.frag", "normals.geom");
//            break;
        
        case '0':
            shader->unload();
            shader->setGeometryInputType(GL_TRIANGLES);
            shader->setGeometryOutputType(GL_TRIANGLE_STRIP);
            shader->setGeometryOutputCount(3);
            shader->load("passthrough.vert", "passthrough.frag", "passthrough.geom");
            currentInputType = GL_TRIANGLES;
            break;
        
        case '1':
            shader->unload();
            shader->setGeometryInputType(GL_TRIANGLES);
            shader->setGeometryOutputType(GL_TRIANGLE_STRIP);
            shader->setGeometryOutputCount(6);
            shader->load("duplicate.vert", "duplicate.frag", "duplicate.geom");
            currentInputType = GL_TRIANGLES;
            break;
        
        case '2':
            shader->unload();
            shader->setGeometryInputType(GL_POINTS);
            shader->setGeometryOutputType(GL_TRIANGLE_STRIP);
            shader->setGeometryOutputCount(24);
            shader->load("cubes.vert", "cubes.frag", "cubes.geom");
            currentInputType = GL_POINTS;
            break;
        
        case '3':
            shader->unload();
            shader->setGeometryInputType(GL_LINES);
            shader->setGeometryOutputType(GL_TRIANGLE_STRIP);
            shader->setGeometryOutputCount(24);
            shader->load("cubelines.vert", "cubelines.frag", "cubelines.geom");
            currentInputType = GL_LINES;
            break;
        
        case '4':
            shader->unload();
            shader->setGeometryInputType(GL_TRIANGLES);//GL_POINTS, GL_TRIANGLES
            shader->setGeometryOutputType(GL_LINE_STRIP);//GL_TRIANGLE_STRIP
            shader->setGeometryOutputCount(6);
            shader->load("normals.vert", "normals.frag", "normals.geom");
            currentInputType = GL_TRIANGLES;
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
    sphereVbo.draw(currentInputType, 0, sphereVbo.getNumIndices());
    ofPopMatrix();
    
    //BOX-SMALL
    ofPushMatrix();
    ofTranslate(300, 300, cos(ofGetElapsedTimef()*1.4) * 300.f);
    ofRotate(ofGetElapsedTimef()*.6 * RAD_TO_DEG, 1, 0, 0);
    ofRotate(ofGetElapsedTimef()*.8 * RAD_TO_DEG, 0, 1, 0);
    cylinderVbo.draw(currentInputType, 0, cylinderVbo.getNumVertices());
    ofPopMatrix();
    
    //BOX-BIG
    ofPushMatrix();
    ofTranslate(center.x, center.y, -1300);
    ofRotate(ofGetElapsedTimef() * .2 * RAD_TO_DEG, 0, 1, 0);
    boxVbo.draw(currentInputType, 0, boxVbo.getNumVertices());
    ofPopMatrix();
    
    
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
    
    ofSetColor( pointLight.getDiffuseColor() );
    if(bPointLight) pointLight.draw();
    
    ofSetColor(255, 255, 255);
    if(bDirLight) directionalLight.draw();
    
    ofSetColor( spotLight.getDiffuseColor() );
    if(bSpotLight) spotLight.draw();
    
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
    gui.add(cubeSize.set("cube size", 5.0, 0.0, 15.0));
    gui.add(lightParameters);
    gui.add(materialParameters);
    
   
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
void ofApp::keyReleased(int key){
    
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
