
#include "ShadowMapper.h"

//--------------------------------------------------------------
void ShadowMapper::setup(int w, int h) {
    
    _width = w;
    _height = h;
    
    setRange( 1, 1000 );
    
    biasMatrix = ofMatrix4x4(
                           0.5, 0.0, 0.0, 0.0,
                           0.0, 0.5, 0.0, 0.0,
                           0.0, 0.0, 0.5, 0.0,
                           0.5, 0.5, 0.5, 1.0
                           );
    
    _variance = 10000;
    
    setBias( 0.001 );
    setIntensity( 0.7 );
    
    _shadowShaderName = "esmShadow";

    shadowShader.load(_shadowShaderName);
    loadBlurShaders();
    depthShader.load("linearDepthBuffer");
    
    _texelSize = 1.0f / float(_width);
    _blurFactor = 4.0f;
    
    allocateFbos();
    
}
//--------------------------------------------------------------
void ShadowMapper::setShader(string name){
    
    _shadowShaderName = name;
    reloadShaders();
    
}
//--------------------------------------------------------------
void ShadowMapper::reloadShaders() {
    
    shadowShader.unload();
    blurHShader.unload();
    blurVShader.unload();
    depthShader.unload();
    
    shadowShader.load(_shadowShaderName);
    depthShader.load("linearDepthBuffer");
    loadBlurShaders();
    
}

//--------------------------------------------------------------
void ShadowMapper::loadBlurShaders() {
    
    blurHShader.load( "blur.vert", "blur_h5.frag" );
    blurVShader.load( "blur.vert", "blur_v5.frag" );
    
}

//--------------------------------------------------------------
void ShadowMapper::setRange( float nearClip, float farClip ) {
    
    lightCam.setNearClip( nearClip );
    lightCam.setFarClip( farClip );
    
    _linarDepthScalar = 1.0 / (farClip  - nearClip);
    
   
}

//--------------------------------------------------------------
void ShadowMapper::setLightPosition( ofVec3f aPos ) {
    lightCam.setPosition( aPos );
}

//--------------------------------------------------------------
void ShadowMapper::setLightLookAt( ofVec3f aPos, ofVec3f upVector ) {
    lightCam.lookAt( aPos, upVector );
}

//--------------------------------------------------------------
void ShadowMapper::beginDepthPass() {
    
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    
    shadowFbo.begin();
    ofClear(255);
    
    lightCam.begin();
    
    glEnable( GL_CULL_FACE ); //cull front faces - this helps with artifacts and shadows with exponential shadow mapping
    glCullFace( GL_BACK );
    
    if (_shadowShaderName == "esmShadow"){
        depthShader.begin();
        depthShader.setUniform1f("u_linearDepthConstant", _linarDepthScalar);
    }
}

//--------------------------------------------------------------
void ShadowMapper::endDepthPass() {
    
    if (_shadowShaderName == "esmShadow"){
        depthShader.end();
    }
    
    lightCam.end();
    
    shadowFbo.end();
    
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    
    glCullFace( GL_BACK );
    glDisable( GL_CULL_FACE );
    
    if ( isBluring() ) blurShadowMap();
}

//--------------------------------------------------------------
void ShadowMapper::blurShadowMap() {
    
    //Horizontal blur pass
    blurFboH.begin();
    
    ofClear(255);
    
    blurHShader.begin();
    blurHShader.setUniform1f("sigma", _blurFactor );
    blurHShader.setUniform1f("blurSize", _texelSize  );
    
    shadowFbo.getDepthTexture().draw(0, 0);//tex0
    
    blurHShader.end();
    
    blurFboH.end();
    
    
    // vertical blur pass
    blurFboV.begin();
    
    ofClear(255);
    
    blurVShader.begin();
    blurVShader.setUniform1f("sigma", _blurFactor );
    blurVShader.setUniform1f("blurSize", _texelSize  );
    
    blurFboH.draw(0,0);
    
    blurVShader.end();
    
    blurFboV.end();
    
   
    
}
//--------------------------------------------------------------
void ShadowMapper::beginRenderPass( ofCamera &cam ) {
    
    ofMatrix4x4 inverseCameraMatrix = ofMatrix4x4::getInverseOf( cam.getModelViewMatrix() );
    ofMatrix4x4 shadowTransMatrix = inverseCameraMatrix * lightCam.getModelViewMatrix() * lightCam.getProjectionMatrix() * biasMatrix;
    ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
    
   
    ofVec3f camPosInViewSpace = cam.getPosition() * cam.getModelViewMatrix();
    ofVec3f lightInWorldSpace = lightCam.getPosition() * cam.getModelViewMatrix();
    
    
    shadowShader.begin();
    
    if( isBluring() ){
        shadowShader.setUniformTexture( "tex_shadowMap", blurFboV.getTexture(), 1 );
    }else{
        shadowShader.setUniformTexture( "tex_shadowMap", shadowFbo.getDepthTexture(), 1 );
    }
    
    shadowShader.setUniformMatrix4f("normalMatrix", normalMatrix);
    shadowShader.setUniformMatrix4f("u_shadowMatrix", shadowTransMatrix );
    
    shadowShader.setUniform3fv( "u_lightPosInWorldSpace", &lightInWorldSpace.getPtr()[0] );
    
    shadowShader.setUniform1f("u_bias", _depthBias);
    

    //poisson sampling:
    shadowShader.setUniform1f("u_shadowIntensity", _intensity );
    shadowShader.setUniform1f( "u_width", _width );
    shadowShader.setUniform1f( "u_height", _height );
    //esm:
    shadowShader.setUniform1f("u_linearDepthConstant", _linarDepthScalar );
    //vsm:
    shadowShader.setUniform1f("u_variance", _variance);
}

//--------------------------------------------------------------
void ShadowMapper::endRenderPass() {
    shadowShader.end();
}

//--------------------------------------------------------------
void ShadowMapper::allocateFbos() {
    
    //all fbos set as texture2D -> "uniform sampler2D"
    ofFbo::Settings settings;
    settings.width  = _width;
    settings.height = _height;
    settings.textureTarget = GL_TEXTURE_2D;
    settings.internalformat = GL_RGBA32F_ARB;
    settings.useDepth = true;
    settings.depthStencilAsTexture = true;
    settings.useStencil = true;
//    settings.depthStencilInternalFormat = GL_DEPTH_COMPONENT32;
    shadowFbo.allocate( settings );
    
    
    ofFbo::Settings blurSettings;
    blurSettings.width  = _width;
    blurSettings.height = _height;
    blurSettings.textureTarget = GL_TEXTURE_2D;
    blurSettings.internalformat = GL_RGBA32F_ARB;
    
    blurFboH.allocate(blurSettings);
    blurFboV.allocate(blurSettings);
    
    
}
//--------------------------------------------------------------
void ShadowMapper::drawShadowMap(int x, int y, int w, int h) {
    
    if ( isBluring() ){
        blurFboV.draw(x, y, w, h);
    }else{
        shadowFbo.getDepthTexture().draw(x, y, w, h);
    }
    
}





