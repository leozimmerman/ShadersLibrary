#version 330


uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 viewMatrix;

in vec4 position;
in vec3 normal;

out vec3 reflectVec;

void main()
{
    vec3 V = vec3(modelViewMatrix * position);
    vec3 N = normalize(vec3(normalMatrix) * normal);
    
    reflectVec = reflect(V, N);

    gl_Position = modelViewProjectionMatrix * position;
}



