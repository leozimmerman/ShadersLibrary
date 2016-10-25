

#version 330

in vec2 varyingtexcoord;

out vec4 fragColor;

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;

void main(void) {
    
    vec4 colorMap = texture(tex0, varyingtexcoord);
    fragColor = colorMap;
    
}
