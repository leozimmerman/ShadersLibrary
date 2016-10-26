//
//  ShaderManager.cpp
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#include "ShaderManager.h"

void ShaderManager::load(string shaderName){
    
    m_shader.load(shaderName);
    _shaderName = shaderName;
    
}
//--------------------------------------------------------------

void ShaderManager::begin(){
    
    m_shader.begin();
    
    setupLights();
    setupMaterial();
    
}
//--------------------------------------------------------------
void ShaderManager::end(){
    
    m_shader.end();
    
   
}
//--------------------------------------------------------------
void ShaderManager::reload(){
    
    setGeometryShader(currentKey);
    
}
//--------------------------------------------------------------
void ShaderManager::setGeometryShader(int key){
    
    currentKey = key;
    
    switch (key) {
        
        case ' ':
            reload();
            break;
            
        case '0':
            m_shader.unload();
            m_shader.setGeometryInputType(GL_TRIANGLES);
            m_shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
            m_shader.setGeometryOutputCount(3);
            m_shader.load("passthrough.vert", "passthrough.frag", "passthrough.geom");
            currentGLInputType = GL_TRIANGLES;
            currentGLOutputType = GL_TRIANGLE_STRIP;
            _shaderName = "passtrough";
            break;
            
        case '1':
            m_shader.unload();
            m_shader.setGeometryInputType(GL_TRIANGLES);
            m_shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
            m_shader.setGeometryOutputCount(6);
            m_shader.load("duplicate.vert", "duplicate.frag", "duplicate.geom");
            currentGLInputType = GL_TRIANGLES;
            currentGLOutputType = GL_TRIANGLE_STRIP;
            _shaderName = "duplicate";
            break;
        
        case '2':
            m_shader.unload();
            m_shader.setGeometryInputType(GL_POINTS);
            m_shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
            m_shader.setGeometryOutputCount(24);
            m_shader.load("cubes.vert", "cubes.frag", "cubes.geom");
            currentGLInputType = GL_POINTS;
            currentGLOutputType = GL_TRIANGLE_STRIP;
            _shaderName = "cubes";
            break;
            
        case '3':
            m_shader.unload();
            m_shader.setGeometryInputType(GL_LINES);
            m_shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
            m_shader.setGeometryOutputCount(24);
            m_shader.load("cubelines.vert", "cubelines.frag", "cubelines.geom");
            currentGLInputType = GL_LINES;
            currentGLOutputType = GL_TRIANGLE_STRIP;
            _shaderName = "cubelines";
            break;
            
        case '4':
            m_shader.unload();
            m_shader.setGeometryInputType(GL_TRIANGLES);//GL_POINTS, GL_TRIANGLES
            m_shader.setGeometryOutputType(GL_LINE_STRIP);//GL_TRIANGLE_STRIP
            m_shader.setGeometryOutputCount(6);
            m_shader.load("normals.vert", "normals.frag", "normals.geom");
            currentGLInputType = GL_TRIANGLES;
            currentGLOutputType = GL_LINE_STRIP;
            _shaderName = "normals";
            break;
            

        
        default:
            break;
    }
}
//--------------------------------------------------------------
void ShaderManager::toggleTexture(ofImage *p_img){
    
    if (texture() == NULL) {
        useTexture(p_img);
    }
    else {
        removeTexture();
    }
}
//--------------------------------------------------------------
void ShaderManager::toggleLight(ofLight *p_light, bool state){

    bool isUsingLight = usingLight(p_light);
    
    if (state && !isUsingLight){
        useLight(p_light);
    }else if (!state && isUsingLight){
        removeLight(p_light);
    }
    
}
//--------------------------------------------------------------
bool ShaderManager::usingLight(ofLight * p_light){
    
    vector<ofLight *>::iterator light;
    
    light = std::find(m_lights.begin(), m_lights.end(), p_light);
    if (light != m_lights.end())
    {
        return true;
    }
    else {
        return false;
    }
}
