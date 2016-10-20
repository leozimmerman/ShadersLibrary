#version 120

varying vec3 reflectVec;

void main()
{
    vec3 V = vec3(gl_ModelViewMatrix * gl_Vertex);
    vec3 N = normalize(gl_NormalMatrix * gl_Normal);
    
    reflectVec = reflect(V, N);
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
