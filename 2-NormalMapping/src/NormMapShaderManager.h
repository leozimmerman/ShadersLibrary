//
//  NormMapShaderManager.hpp
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#pragma once

#include "LightShaderManager.h"

class NormMapShaderManager : public LightShaderManager{

public:
    
    
    void begin();
    void end();
    
    void setNormalMapTexture(ofImage * p_img) {normTex = p_img; };
    
private:
    
    ofImage * normTex;
    
};
