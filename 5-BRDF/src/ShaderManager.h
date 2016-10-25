//
//  ShaderManager.hpp
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#pragma once

#include "ofxShadersFX_LightingShader.h"

class ShaderManager : public ofxShadersFX::Lighting::LightingShader{

public:
    void load(string shaderName);
    
    void begin();
    void end();
    void reload();

    void toggleLight(ofLight * p_light, bool state);
    void toggleTexture(ofImage * p_img);
    ofShader* shader(){return &m_shader;}
    
    string shaderName(){return _shaderName;}
    
private:
    
    bool usingLight(ofLight* p_light);
    string _shaderName;
    
};
