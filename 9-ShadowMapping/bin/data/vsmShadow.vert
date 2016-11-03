

#version 330

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

uniform mat4 u_shadowMatrix;

in vec4 position;
in vec3 normal;


uniform vec3 u_lightPosInWorldSpace;

out vec3 v_normal;
out vec4 v_vertInLightSpace;
out vec3 v_lightDir;
out vec4 v_position;

void main( void ) {
    
    vec4 vertex = modelViewMatrix * position;
    
    v_position = vertex;
    
    v_normal = (normalMatrix * vec4(normal, 0.0)).xyz;
    
    v_lightDir = ( u_lightPosInWorldSpace - vertex.xyz );
    
    v_vertInLightSpace = u_shadowMatrix * vertex;
    
    gl_Position = modelViewProjectionMatrix * position;
    
    
}
