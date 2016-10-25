#version 330

uniform samplerCube envMap;

in vec3 reflectVec;


out vec4 fragColor;

void main(){

    vec4 cubeMapColor = texture(envMap, reflectVec);
    fragColor = cubeMapColor;

}


