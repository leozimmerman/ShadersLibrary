#version 330


// A triangle with three points come in
layout(triangles) in;

// Out of three triangle points, we create a triangle strip with two triangles
layout(triangle_strip, max_vertices = 3) out;

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

in vec3 g_normal[3];

out vec4 v_eye;
out vec3 interp_eye;

out vec3 v_normal;

void main(void)
{

    for (int i=0; i < gl_in.length(); i++){
        
        v_eye = modelViewMatrix *  gl_in[i].gl_Position;
        interp_eye = vec3(-v_eye);
        v_normal = g_normal[i];
        
        gl_Position =  modelViewProjectionMatrix * gl_in[i].gl_Position;

        EmitVertex();
        
    }
    
    EndPrimitive();
    
}
