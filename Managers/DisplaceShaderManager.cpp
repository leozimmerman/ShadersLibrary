//
//  ShaderManager.cpp
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#include "DisplaceShaderManager.h"


//--------------------------------------------------------------

void DisplaceShaderManager::begin(){
   
    
    shader.begin();
    
    shader.setUniform1f("maxHeight", maxHeight);
    
    if (tex != NULL){
        shader.setUniformTexture("texColor", (*tex), 1);
        tex->bind();
    }
    
    if (bumpTex != NULL){
        shader.setUniformTexture("texBumpMap", (*bumpTex), 2);
        bumpTex->bind();
    }
    
    setupLights();
    setupMaterial();
    
}
//--------------------------------------------------------------
void DisplaceShaderManager::end(){
    
    shader.end();
    
    if (tex != NULL) tex->unbind();
    if (bumpTex != NULL) bumpTex->unbind();
    
}
