

#version 330

in vec2 varyingtexcoord;

out vec4 fragColor;

uniform sampler2DRect texColor;
uniform sampler2DRect texBumpMap;

void main(void) {
    
    vec4 colorMap = texture(texColor, varyingtexcoord);
    fragColor = colorMap;
    
}
