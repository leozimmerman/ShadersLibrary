//
//  ShaderManager.hpp
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#pragma once

#include "LightShaderManager.h"

class GeometryShaderManager : public LightShaderManager {

public:
    
    void reload();
    
    void setGeometryShader(int key);

    
    GLenum getGLInputType(){return currentGLInputType; }
    GLenum getGLOutputType(){return currentGLOutputType; }
    
private:
    
    int currentKey;
    
    GLenum currentGLInputType;
    GLenum currentGLOutputType;
  
    
};
