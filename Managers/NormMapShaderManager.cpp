//
//  NormMapShaderManager.cpp
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#include "NormMapShaderManager.h"

void NormMapShaderManager::begin(){
    
    LightShaderManager::begin();
    
    if (normTex != NULL){
        shader.setUniformTexture("normalMapTex", (*normTex), 2);
        normTex->bind();
    }
    
}
//--------------------------------------------------------------
void NormMapShaderManager::end(){
    
    LightShaderManager::end();
    
    if (normTex != NULL) normTex->unbind();
    
}


