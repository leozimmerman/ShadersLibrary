
#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

in vec4 position;
in vec3 normal;

out vec4 v_eye, ambientGlobal;
out vec3 v_normal, interp_eyePos;

void main() {
    ambientGlobal = material.emission;
    v_eye = modelViewMatrix * position;
    v_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    interp_eyePos = vec3(-v_eye);
    gl_Position = modelViewProjectionMatrix * position;
}
