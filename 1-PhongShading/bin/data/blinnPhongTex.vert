// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

in vec4 position;
in vec3 normal;
in vec2 texcoord;

out vec4 v_eye;
out vec3 v_normal, interp_eyePos;
out vec2 varyingtexcoord;

void main() {
    
    
    v_eye = modelViewMatrix * position;
    v_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    interp_eyePos = vec3(-v_eye);
    varyingtexcoord = vec2(texcoord.x, texcoord.y);
    gl_Position = modelViewProjectionMatrix * position;
    
}
