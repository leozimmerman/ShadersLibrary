#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

in vec4 position;
in vec3 normal;
in vec2 texcoord;

out vec4 v_vertex;
out vec3 v_normal;
out vec2 varyingtexcoord;

out vec4 lightDirections[8];


uniform int lightsNumber;

void main() {
  
    
    v_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    varyingtexcoord = vec2(texcoord.x, texcoord.y);
    
    vec4 spaceVertex = modelViewMatrix * position;
    
    for (int i=0; i<lightsNumber; i++){
        lightDirections[i] = lights.light[i].position - spaceVertex;
    }
   
    v_vertex = -spaceVertex;
    
    
    
    gl_Position = modelViewProjectionMatrix * position;
}
