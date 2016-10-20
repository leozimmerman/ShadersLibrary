#version 330

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix; //ofMatrix4x4::getTransposedOf(m_cam->getModelViewMatrix().getInverse());

uniform samplerCube envMap;


in vec3 reflectVec;


out vec4 fragColor;

void main(){

    fragColor = texture(envMap, reflectVec);
    
    
}


