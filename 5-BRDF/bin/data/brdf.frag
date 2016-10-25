
#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

const float PI = 3.14159;
const float ONE_OVER_PI = 1.0 / PI;

uniform int lightsNumber;

uniform vec2 P;            // Diffuse (x) and specular reflectance (y)
uniform vec2 A;            // Slope distribution in x and y
uniform vec3 Scale;        // Scale factors for intensity computation


in vec4 eyeSpaceVertexPos;
in vec3 vertex_normal;

in vec3 N, L, H, R, T, B;

out vec4 fragColor;

void main(void)
{
    
    float e1, e2, E, cosThetaI, cosThetaR, brdf, intensity;
    
    e1 = dot(H, T) / A.x;
    e2 = dot(H, B) / A.y;
    E = -2.0 * ((e1 * e1 + e2 * e2) / (1.0 + dot(H, N)));
    
    cosThetaI = dot(N, L);
    cosThetaR = dot(N, R);
    
    brdf = P.x * ONE_OVER_PI +
    P.y * (1.0 / sqrt(cosThetaI * cosThetaR)) *
    (1.0 / (4.0 * PI * A.x * A.y)) * exp(E);
    
    intensity = Scale[0] * P.x * ONE_OVER_PI +
    Scale[1] * P.y * cosThetaI * brdf +
    Scale[2] * dot(H, N) * P.y;
    
    vec3 color = intensity * material.specular.rgb;
    
    fragColor = vec4(color, 1.0);
}


