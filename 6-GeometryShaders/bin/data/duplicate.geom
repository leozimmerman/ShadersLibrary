#version 330


layout(triangles) in;

layout(triangle_strip, max_vertices = 6) out;

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

in vec3 g_normal[3];

out vec4 v_eye;
out vec3 interp_eye;

out vec3 v_normal;

void main(void)
{
    mat4 translateMatrix = mat4(1.0);
    
    translateMatrix[3][0] = -500.0;
    
    for (int i=0; i < gl_in.length(); i++){
        
        vec4 view_position = modelViewMatrix * translateMatrix * gl_in[i].gl_Position;
        
        v_eye = view_position;
        interp_eye = vec3(-v_eye);
        v_normal = g_normal[i];
        
        gl_Position =  projectionMatrix * view_position;

        EmitVertex();
        
    }
    
    EndPrimitive();
    
    
    translateMatrix[3][0] = +500.0;
    
    for (int i=0; i < gl_in.length(); i++){
  
        vec4 view_position = modelViewMatrix * translateMatrix * gl_in[i].gl_Position ;
        
        v_eye = view_position;
        interp_eye = vec3(-v_eye);
        v_normal = g_normal[i];
        
        gl_Position =  projectionMatrix * view_position;
        
        EmitVertex();
        
    }
    
    EndPrimitive();
    
    
}
