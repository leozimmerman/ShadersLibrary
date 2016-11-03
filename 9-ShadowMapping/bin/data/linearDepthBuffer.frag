//https://github.com/jacres/of-ESMShadowMapping
#version 330

uniform float u_linearDepthConstant;

in vec4 v_position;

// can hardcode near/far/depth constant for speed, but passed in as uniform for convenience (u_LinearDepthConstant)
//const float Near = 0.1; // camera z near
//const float Far = 300.0; // camera z far
//const float LinearDepthConstant = 1.0 / (Far - Near);

void main(){
    
    float linearDepth = length(v_position) * u_linearDepthConstant;
    //linearDepth = 0.0;
    
    gl_FragDepth = linearDepth;
    
}


