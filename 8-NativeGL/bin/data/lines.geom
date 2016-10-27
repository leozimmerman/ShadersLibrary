#version 410 core

layout(points) in;

layout(line_strip, max_vertices = 2) out;

void main(void)
{
    
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    vec4 modPosition = gl_in[0].gl_Position;
    modPosition.x += 50.0;
    gl_Position = modPosition;
    EmitVertex();

    EndPrimitive();
}

