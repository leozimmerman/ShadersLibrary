#version 410 core

uniform mat4 modelViewProjectionMatrix;


in vec4 position;

//out vec3 vPosition;

void main(void){
    
	gl_Position = modelViewProjectionMatrix * position;
    
}
