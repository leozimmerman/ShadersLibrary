#version 120

uniform samplerCube envMap;


varying vec3 reflectVec;

void main()
{
    gl_FragColor = textureCube(envMap, reflectVec);
}
