#version 330



layout(triangles) in;

layout(line_strip, max_vertices = 6) out;

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

uniform float u_size;

in vec3 g_normal[3];


void generateLine(int index) {
    
    gl_Position = modelViewProjectionMatrix * gl_in[index].gl_Position;
    EmitVertex();
    
    gl_Position = modelViewProjectionMatrix * (gl_in[index].gl_Position + vec4(g_normal[index], 0.0f) * u_size*10.0);
    EmitVertex();
    EndPrimitive();
    
}

void main(void) {

    generateLine(0); // First vertex normal
    generateLine(1); // Second vertex normal
    generateLine(2); // Third vertex normal
    
}
