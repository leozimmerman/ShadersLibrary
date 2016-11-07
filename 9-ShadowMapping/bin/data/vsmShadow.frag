//http://www.fabiensanglard.net/shadowmappingVSM/

#version 330

uniform sampler2D  tex_shadowMap;
uniform float u_variance;

in vec3 v_normal;
in vec4 v_vertInLightSpace;
in vec3 v_lightDir;
in vec4 v_position;
in vec4 v_color;

out vec4 fragColor;


void main() {
    
    
    // get projected shadow value
    vec4 depth = v_vertInLightSpace / v_vertInLightSpace.w;
    depth.y = 1.0 - depth.y;
    
    float shadow = 1.0;
    
    float distance = depth.z;
    
    // We retrive the two moments previously stored (depth and depth*depth)
    vec2 moments = texture(tex_shadowMap, depth.xy).rg;
    
    // Surface is fully lit. as the current fragment is before the light occluder
    if (distance <= moments.x){
        
        shadow =  1.0 ;
        
    }else{
        // The fragment is either in shadow or penumbra. We now use chebyshev's upperBound to check
        // How likely this pixel is to be lit (p_max)
        float variance = moments.y - (moments.x*moments.x);
        
        //variance = max(variance, 0.00002);
        variance = max(variance, u_variance);
        
        float d = distance - moments.x;
        float p_max = variance / (variance + d*d);
        shadow = p_max;
    }
    
    //----------------------------
    
    //Lights:
    vec3 normal     = normalize(v_normal);
    vec3 lightDir   = v_lightDir;
    float lambert = max(dot(normal, normalize(lightDir) ), 0.0);
    
    vec4 diffuse =  v_color * clamp( lambert, 0.0, 1.0 )* shadow;
    
    fragColor = vec4(diffuse.xyz, 1.0);
    
}
