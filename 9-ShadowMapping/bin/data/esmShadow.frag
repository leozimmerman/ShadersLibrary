#version 330

uniform sampler2D  tex_shadowMap;

uniform float u_linearDepthConstant;
uniform float u_bias;
uniform vec3  u_lightPosInWorldSpace;

in vec3 v_normal;
in vec4 v_vertInLightSpace;
in vec3 v_lightDir;
in vec4 v_position;
in vec4 v_color;

out vec4 fragColor;

void main( void ) {
    
    // Shadow:
    vec3 depth = v_vertInLightSpace.xyz / v_vertInLightSpace.w;
    depth.y = 1.0 - depth.y;
    
    float lightDepth = length(v_position.xyz - u_lightPosInWorldSpace) * u_linearDepthConstant;
    
    float shadow = 1.0;
    
    if ( depth.z > 0.0 ) {
        
        float c = 10.0; // shadow coeffecient - change this to to affect shadow darkness/fade
        float texel = texture( tex_shadowMap, depth.xy ).r;
        shadow = clamp( exp( -c * (lightDepth - texel)), 0.0, 1.0 );
        
    }
    
    
    //Lights:
    vec3 normal     = normalize(v_normal);
    vec3 lightDir   = v_lightDir;
    float lambert = max(dot(normal, normalize(lightDir) ), 0.0);
    
    
    //vec4 diffuse = v_color * clamp( lambert, 0.0, 1.0 ) + v_color * shadow;
    vec4 diffuse =  v_color * clamp( lambert, 0.0, 1.0 )* shadow;
    
    
    fragColor = vec4(diffuse.xyz, 1.0);
    
    
}
