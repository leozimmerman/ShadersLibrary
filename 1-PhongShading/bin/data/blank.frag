
#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"


uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix; //ofMatrix4x4::getTransposedOf(m_cam->getModelViewMatrix().getInverse());
uniform int lightsNumber; //lights.size()

in vec4 v_eye;
in vec3 v_normal;
in vec4  ambientGlobal;

out vec4 fragColor;

void main() {
    
    fragColor = ambientGlobal;
    
}
