
#version 330

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

in vec4 position;
in vec3 normal;
in vec2 texcoord;

out vec2 varyingtexcoord;

uniform sampler2DRect texColor;
uniform sampler2DRect texBumpMap;
uniform float maxHeight;

void main(void) {
    vec4 bumpColor = texture(texBumpMap, texcoord);
    float df = 0.30 * bumpColor.r + 0.59 * bumpColor.g + 0.11 * bumpColor.b;
    vec3 v_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    
    vec4 newVertexPos = vec4(normal * df * float(maxHeight), 0.0) + position;

    varyingtexcoord = vec2(texcoord.x, texcoord.y);
    gl_Position = modelViewProjectionMatrix * newVertexPos;
}
