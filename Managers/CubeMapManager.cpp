//
//  ShaderManager.cpp
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#include "CubeMapManager.h"


//--------------------------------------------------------------

void CubeMapManager::begin(){
    

    if(cubemap != NULL) cubemap->bind();
    
    shader.begin();
    
    if(cubemap != NULL){
        shader.setUniform1i("envMap", 0);
        shader.setUniform1f("reflectivity", 0.8);
    }

    setupLights();
    setupMaterial();
    
}
//--------------------------------------------------------------
void CubeMapManager::end(){
    
    shader.end();
    
    if(cubemap != NULL) cubemap->unbind();
    
}

//--------------------------------------------------------------
void CubeMapManager::drawCubeMapEnvironment(float size){
    
    //NOT WORKING:
    
    if(cubemap == NULL){ return; }
    
    cubemap->bind();
    cubemap->drawSkybox(size);
    cubemap->unbind();
    
}
