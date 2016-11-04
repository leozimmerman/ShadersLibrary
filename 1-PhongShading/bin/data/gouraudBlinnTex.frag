

#version 330

uniform sampler2DRect tex;

in vec4 ambientGlobal, diffuse, ambient, specular;

in vec2 varyingtexcoord;

out vec4 fragColor;

void main(void) {
    fragColor = (texture(tex, varyingtexcoord) * (ambientGlobal + diffuse + ambient)) + specular;
}
