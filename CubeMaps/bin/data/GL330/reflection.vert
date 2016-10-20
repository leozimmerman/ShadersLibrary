#version 330

// Indices of refraction
const float Air = 1.0;
const float Glass = 1.51714;

// Air to glass ratio of the indices of refraction (Eta)
const float Eta = Air / Glass;

// see http://en.wikipedia.org/wiki/Refractive_index Reflectivity
const float R0 = ((Air - Glass) * (Air - Glass)) / ((Air + Glass) * (Air + Glass));

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 viewMatrix;

in vec4 position;
in vec3 normal;

out vec3 reflectVec;

void main()
{
    vec3 V = vec3(modelViewMatrix * position);
    vec3 N = normalize(vec3(normalMatrix) * normal);
    
    reflectVec = reflect(V, N);
    
//    mat4 inverseViewMatrix = inverse(viewMatrix);
//    reflectVec *= mat3(inverseViewMatrix);
    
    gl_Position = modelViewProjectionMatrix * position;
}



