

#version 330

in vec4 ambientGlobal, diffuse, ambient, specular;

out vec4 fragColor;

void main(void) {
    fragColor = (ambientGlobal + diffuse + ambient) + specular;
}
