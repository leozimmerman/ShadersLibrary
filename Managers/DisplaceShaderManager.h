//
//  DisplaceShaderManager
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#pragma once

#include "LightShaderManager.h"


class DisplaceShaderManager : public LightShaderManager {

public:
    
    void begin();
    void end();
    
    void setBumpMapTexture(ofImage * p_img){ bumpTex = p_img; }
    void setMaxHeight(float h){maxHeight = h;}
    
    
private:
    
    ofImage * bumpTex;
    float maxHeight;
    
};
