
#version 330

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

in vec4 position;

out vec4 v_position;

void main( void )
{
    v_position = modelViewMatrix * position;
    gl_Position = modelViewProjectionMatrix * position;
}
