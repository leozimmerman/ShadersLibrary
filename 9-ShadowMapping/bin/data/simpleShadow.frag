#version 330

uniform sampler2D  tex_shadowMap;
uniform float u_bias;

in vec3 v_normal;
in vec4 v_vertInLightSpace;
in vec3 v_lightDir;

out vec4 fragColor;

void main( void ) {
    
    vec4 myColor = vec4(1.0, 1.0, 0.0, 1.0);//yellow
    
    //Shadows:
    vec3 tdepth = v_vertInLightSpace.xyz / v_vertInLightSpace.w;
    vec4 depth  = vec4( tdepth.xyz, v_vertInLightSpace.w );
    
    depth.y = 1.0 - depth.y;
    vec2 UVCoords = depth.xy;
    
    float texel = texture( tex_shadowMap, UVCoords.xy).r;
    
    
    float shadow = 1.0;
    
    if( texel < depth.z - u_bias ) {
        shadow = 0.5;
    }
    // are you behind the shadow view? //
    if( v_vertInLightSpace.z < 1.0) {
        shadow = 1.0;
    }
    
    
    //Lights:
    vec3 normal     = normalize(v_normal);
    vec3 lightDir   = v_lightDir;
    float lambert = max(dot(normal, normalize(lightDir) ), 0.0);
    
    vec4 diffuse = myColor * clamp( lambert, 0.0, 1.0 ) * shadow;
    
    fragColor = vec4(diffuse.xyz, 1.0);
    
    
}
