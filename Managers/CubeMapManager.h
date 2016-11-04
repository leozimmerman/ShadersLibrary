//
//  CubeMapManager
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#pragma once


#include "ofxCubeMap.h"
#include "LightShaderManager.h"

class CubeMapManager : public LightShaderManager {

public:
    
    
    void begin();
    void end();
    
    void drawCubeMapEnvironment(float size);
    
    void useNormalMapTexture(ofImage * p_img);
    void useCubeMap(ofxCubeMap* p_cubemap){cubemap = p_cubemap;}
    
    
private:
    
    ofxCubeMap * cubemap;
    
};
