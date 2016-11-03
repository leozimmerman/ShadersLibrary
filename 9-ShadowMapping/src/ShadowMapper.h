
#pragma once
#include "ofMain.h"


class ShadowMapper {

public:
    
    void setup(int w, int h);
    
    void reloadShaders();
    void loadBlurShaders();
    
    void setShader(string name);
    string getShaderName(){return _shadowShaderName;}
    
    void drawShadowMap(int x, int y, int w, int h);
    
    bool isBluring() { return _blurFactor > 0.0; }
    void blurShadowMap();
    
    void setRange( float nearClip, float farClip );

    void setLightPosition( ofVec3f aPos );
    void setLightLookAt( ofVec3f aPos, ofVec3f upVector = ofVec3f(0, 1, 0) );
    
    void beginDepthPass();
    void endDepthPass();
    
    void beginRenderPass( ofCamera& cam );
    void endRenderPass();
    
    void setWidth(float w){ _width = w; }
    void setHeight(float h){ _height = h; }
    
    // bias to reduce shadow acne //
    void setBias(float bias){ _depthBias = bias; }
    void setIntensity(float intensity){ _intensity = intensity; }
    void setBlurFactor(float factor){ _blurFactor = factor; }
    void setVariance(float variance){ _variance = variance; }
    
    ofCamera lightCam;
    
    
protected:
    
    void allocateFbos();
    
    ofMatrix4x4 biasMatrix;
    
    ofFbo shadowFbo;
    ofFbo blurFboH, blurFboV;
    
    ofShader shadowShader;
    ofShader blurHShader, blurVShader;
    ofShader depthShader;
    
    int _width, _height;
    
    float _texelSize;
    
    float _depthBias;
    float _intensity;
    float _linarDepthScalar;
    float _blurFactor;
    float _variance;
    
    string _shadowShaderName;
    
    
};
