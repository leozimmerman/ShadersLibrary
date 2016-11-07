//https://github.com/opengl-tutorials/ogl/blob/master/tutorial16_shadowmaps/ShadowMapping.fragmentshader
#version 330

uniform sampler2D tex_shadowMap;

uniform float u_bias;
uniform float u_width;
uniform float u_height;
uniform float u_shadowIntensity;

in vec3 v_normal;
in vec4 v_color;
in vec4 v_vertInLightSpace;
in vec3 v_lightDir;

out vec4 fragColor;

const vec2 poissonDisk[16] = vec2[16] (
                    vec2( -0.94201624, -0.39906216 ),
                    vec2( 0.94558609, -0.76890725 ),
                    vec2( -0.094184101, -0.92938870 ),
                    vec2( 0.34495938, 0.29387760 ),
                    vec2( -0.91588581, 0.45771432 ),
                    vec2( -0.81544232, -0.87912464 ),
                    vec2( -0.38277543, 0.27676845 ),
                    vec2( 0.97484398, 0.75648379 ),
                    vec2( 0.44323325, -0.97511554 ),
                    vec2( 0.53742981, -0.47373420 ),
                    vec2( -0.26496911, -0.41893023 ),
                    vec2( 0.79197514, 0.19090188 ),
                    vec2( -0.24188840, 0.99706507 ),
                    vec2( -0.81409955, 0.91437590 ),
                    vec2( 0.19984126, 0.78641367 ),
                    vec2( 0.14383161, -0.14100790 )
                );


void main( void ) {
    

    //Shadow:
    vec3 tdepth = v_vertInLightSpace.xyz / v_vertInLightSpace.w;
    vec4 depth  = vec4( tdepth.xyz, v_vertInLightSpace.w );
    
    depth.y = 1.0 - depth.y;
    vec2 UVCoords = depth.xy;
    float shadow = 1.0;
    
    int numSamples = 16;
    float shadowDec = 1.0/float(numSamples);
    
    for( int i = 0; i < numSamples; i++ ) {
        
        float texel = texture( tex_shadowMap, UVCoords.xy + (poissonDisk[i]/(u_width*0.75)) ).r;
        
        if( texel < depth.z - u_bias ) {
            shadow -= shadowDec * u_shadowIntensity;
        }
    }
    // are you behind the shadow view? //
    if( v_vertInLightSpace.z < 1.0) {
        shadow = 1.0;
    }
    
    //Lighting:
    vec3 normal     = normalize(v_normal);
    vec3 lightDir   = v_lightDir;
    float lambert = max(dot(normal, normalize(lightDir) ), 0.0);
    
    vec4 diffuse = v_color * clamp( lambert, 0.0, 1.0 ) * shadow;
    
    fragColor = vec4(diffuse.xyz, 1.0);
    
}
