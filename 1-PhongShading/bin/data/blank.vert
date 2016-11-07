
#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec3 normal;
in vec4 color;
in vec2 texcoord;
// this is the end of the default functionality

uniform mat4 normalMatrix;

out vec4 v_eye;
out vec3 v_normal;

out vec4 v_color;


void main() {
    
    v_color = color;
    
    v_eye = modelViewMatrix * position;
    v_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    
    gl_Position = modelViewProjectionMatrix * position;
    
}
