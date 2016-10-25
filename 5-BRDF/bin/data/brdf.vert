

#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

uniform vec4 viewPosition;//??

in vec4 position;
in vec3 normal;

out vec4 eyeSpaceVertex;
out vec3 vertex_normal;

out vec3 N, L, H, R, T, B;


void main() {
    
    //-Tangent space calculation---------
    //http://www.geeks3d.com/20130122/normal-mapping-without-precomputed-tangent-space-vectors/
    
    vec3 n_norm = vec3(normalMatrix) * normal;
    
    vec3 tangent;
    vec3 bitangent;
    vec3 c1 = cross(n_norm, vec3(0.0, 0.0, 1.0));
    vec3 c2 = cross(n_norm, vec3(0.0, 1.0, 0.0));
    if (length(c1) > length(c2))
        tangent = c1;
    else
        tangent = c2;
    tangent     = normalize(tangent);
    bitangent   = normalize(cross(n_norm, tangent));
    
    //---
    
    eyeSpaceVertex = modelViewMatrix * position;
    
    vec4 lightDirection = lights.light[0].position - eyeSpaceVertex; //only one light
    
    //http://www.yaldex.com/open-gl/ch14lev1sec3.html
    
    N = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    L = normalize(lightDirection.xyz);
    
    vec3 V = normalize(vec3(modelViewMatrix * viewPosition - eyeSpaceVertex));
    //vec3 V = eyeSpaceVertex.xyz;
    
    H = normalize(L + V);
    R = normalize(reflect(eyeSpaceVertex.xyz, N));
    T = tangent;//x normal matrix?
    B = bitangent;//x normal matrix?
    
    gl_Position = modelViewProjectionMatrix * position;
    
}

//--------------------------------------------

