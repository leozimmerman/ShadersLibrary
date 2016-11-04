//
//  LightShaderManager.hpp
//  multilight
//
//  Created by Leo on 10/12/16.

/*
 Class based on: https://github.com/Scylardor/ofxShadersFX/blob/master/src/ofxShadersFX_LightingShader.h
 */

#pragma once

#include "ofMain.h"


class LightShaderManager {

public:
    
    void load(string shaderName);
    
    void begin();
    void end();
    void reload();

    void setMaterial(ofMaterial * p_mat){ mat = p_mat; }
    void setCamera(ofCamera * p_cam) { cam = p_cam; }
    void setTexture(ofImage * p_img) {tex = p_img; }
    void useLight(ofLight * p_light);
    void removeLight(ofLight * p_light);
    
    void toggleLight(ofLight * p_light, bool state);
    void toggleTexture(ofImage * p_img);
    
    string shaderName(){return _shaderName;}
    
    bool usingLight(ofLight* p_light);
    
    void setupLights();
    vector<string> generateLightPropsNames();
    void setLightPosition(size_t p_lightIndex, vector<unsigned char> & p_buffer, const GLint * p_offsets);
    void setLightColors(size_t p_lightIndex, vector<unsigned char> & p_buffer, const GLint * p_offsets);
    void setLightAttenuation(size_t p_lightIndex, vector<unsigned char> & p_buffer, const GLint * p_offsets);
    void setLightSpotProperties(size_t p_lightIndex, vector<unsigned char> & p_buffer, const GLint * p_offsets);
    void setupFixedPipelineLights();
    
    void setupMaterial();
    void setMaterialProperties(vector<unsigned char> & p_buffer, const GLint * p_offsets);
    
    ofShader* getShader() {return &shader; }
    
protected:
    
    ofShader shader;
    
    vector<ofLight *> lights;
    
    ofMaterial defaultMat;
    ofCamera * cam;
    ofMaterial * mat;
    ofImage * tex;
    
    ofMatrix4x4 normalMatrix;
    
    string _shaderName;
    
    static const size_t MAX_LIGHTS = 8;
    static const size_t LIGHT_PROPS_NUMBER = 11; // Number of light properties in the shaders
    
};
