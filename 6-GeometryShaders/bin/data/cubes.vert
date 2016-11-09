// Copyright (C) 2016 Leo Zimmerman [http://www.leozimmerman.com.ar]

#version 330

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

in vec4 position;
in vec3 normal;

out vec3 g_normal;

void main() {
    
    g_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    gl_Position =  position;
    
}
