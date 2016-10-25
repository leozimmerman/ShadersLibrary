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
    
//    if (!m_shader.isLoaded() || m_needsReload) {
//        reload();
//        m_needsReload = false;
//    }
//    
    m_shader.begin();
    
    if (m_tex != NULL){
        m_shader.setUniformTexture("tex", (*m_tex), 1);
        m_tex->bind();
    }
    
    setupLights();
    setupMaterial();
    
}
//--------------------------------------------------------------
void ShaderManager::end(){
    
    m_shader.end();
    
    if (m_tex != NULL){
        m_tex->unbind();
    }
}
//--------------------------------------------------------------
void ShaderManager::reload(){
    
     m_shader.load(_shaderName);
    
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
