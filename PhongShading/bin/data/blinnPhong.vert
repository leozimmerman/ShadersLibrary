
#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

in vec4 position;
in vec3 normal;

out vec4 eyeSpaceVertexPos, ambientGlobal;
out vec3 vertex_normal, interp_eyePos;

void main() {
    ambientGlobal = material.emission;
    eyeSpaceVertexPos = modelViewMatrix * position;
    vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    interp_eyePos = vec3(-eyeSpaceVertexPos);
    gl_Position = modelViewProjectionMatrix * position;
}
