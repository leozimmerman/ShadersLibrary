#version 150

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform sampler2DRect tex;
uniform sampler2DRect normalMapTex;

uniform int lightsNumber;

in vec2 varyingtexcoord;
in vec4 v_vertex;
in vec3 v_normal;

in vec4 lightDirections[8];


out vec4 fragColor;

//------------------------------------------------
// http://www.thetenthplanet.de/archives/1180
mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv)
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );
    
    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
    
    // construct a scale-invariant frame
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord )
{
    // assume N, the interpolated vertex normal and
    // V, the view vector (vertex to eye)
    vec3 map = texture(normalMapTex, texcoord ).xyz;
    map = map * 255./127. - 128./127.;
    mat3 TBN = cotangent_frame(N, -V, texcoord);
    return normalize(TBN * map);
}
//-------------------------------------

void main(void)
{
    vec2 uv = varyingtexcoord.xy;
    
    for (int i=0; i<lightsNumber; i++){
        
        vec3 N = normalize(v_normal.xyz);
        vec3 L = normalize(lightDirections[i].xyz);
        vec3 V = normalize(v_vertex.xyz);
        vec3 PN = perturb_normal(N, V, uv);
        
        vec4 tex01_color = texture(tex, uv).rgba;
        
        vec4 final_color = vec4(0.15, 0.15, 0.15, 1.0) * tex01_color;
        
        float lambertTerm = dot(PN, L);
        if (lambertTerm > 0.0)
        {
            final_color += lights.light[i].diffuse * material.diffuse * lambertTerm * tex01_color;
            
            vec3 E = normalize(v_vertex.xyz);
            vec3 R = reflect(-L, PN);
            float specular = pow( max(dot(R, E), 0.0), material.shininess);
            final_color += lights.light[i].specular * material.specular * specular;
        }
        fragColor.rgb += final_color.rgb;
    }
    
    fragColor.a = 1.0;
}
