
#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform int lightsNumber;

in vec4 position;
in vec3 normal;
in vec2 texcoord;

out vec4 ambientGlobal, diffuse, ambient, specular;
out vec2 varyingtexcoord;

vec4 eyeSpaceVertexPos;

void directional_light( in int lightIndex, in vec3 normal, inout vec4 diffuse, inout vec4 ambient, inout vec4 specular) {
    vec3 lightDir;
    float intensity;
    lightDir = normalize(lights.light[lightIndex].position.xyz);
    ambient += material.ambient * lights.light[lightIndex].ambient;
    intensity = max(dot(normal, lightDir), 0.0);
    if (intensity > 0.0) {
        vec3 reflection;
        vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
        vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);
        diffuse += lights.light[lightIndex].diffuse * material.diffuse * intensity;
        reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
        specular += pow(max(dot(reflection, eyeVector), 0.0), material.shininess) * material.specular * lights.light[lightIndex].specular;
    }
}
void point_light( in int lightIndex, in vec3 normal, inout vec4 diffuse, inout vec4 ambient, inout vec4 specular) {
    vec3 lightDir;
    float intensity, dist;
    lightDir = vec3(lights.light[lightIndex].position - eyeSpaceVertexPos);
    dist = length(lightDir);
    intensity = max(dot(normal, normalize(lightDir)), 0.0);
    if (intensity > 0.0) {
        float att;
        vec3 reflection;
        vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
        vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);
        att = 1.0 / (lights.light[lightIndex].constant_attenuation + lights.light[lightIndex].linear_attenuation * dist + lights.light[lightIndex].quadratic_attenuation * dist * dist);
        diffuse += att * intensity * material.diffuse * lights.light[lightIndex].diffuse;
        ambient += att * material.ambient * lights.light[lightIndex].ambient;
        reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
        specular += pow(max(dot(reflection, eyeVector), 0.0), material.shininess) * material.specular * lights.light[lightIndex].specular;
    }
}
void spot_light( in int lightIndex, in vec3 normal, inout vec4 diffuse, inout vec4 ambient, inout vec4 specular) {
    vec3 lightDir;
    float intensity, dist;
    lightDir = vec3(lights.light[lightIndex].position - eyeSpaceVertexPos);
    dist = length(lightDir);
    intensity = max(dot(normal, normalize(lightDir)), 0.0);
    if (intensity > 0.0) {
        float spotEffect, att;
        vec3 reflection;
        vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
        vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);
        spotEffect = dot(normalize(lights.light[lightIndex].spot_direction), normalize(-lightDir));
        if (spotEffect > lights.light[lightIndex].spot_cos_cutoff) {
            spotEffect = pow(spotEffect, lights.light[lightIndex].spot_exponent);
            att = spotEffect / (lights.light[lightIndex].constant_attenuation + lights.light[lightIndex].linear_attenuation * dist + lights.light[lightIndex].quadratic_attenuation * dist * dist);
            diffuse += att * intensity * material.diffuse * lights.light[lightIndex].diffuse;
            ambient += att * material.ambient * lights.light[lightIndex].ambient;
            reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
            specular += att * pow(max(dot(reflection, eyeVector), 0.0), material.shininess) * material.specular * lights.light[lightIndex].specular;
        }
    }
}
vec4 calc_lighting_color( in vec3 normal, inout vec4 diffuse, inout vec4 ambient, inout vec4 specular) {
    vec4 lightingColor = vec4(0.0);
    for (int i = 0; i < lightsNumber; i++) {
        if (lights.light[i].position.w == 0.0) {
            directional_light(i, normal, diffuse, ambient, specular);
        } else {
            if (lights.light[i].spot_cutoff <= 90.0) {
                spot_light(i, normal, diffuse, ambient, specular);
            } else {
                point_light(i, normal, diffuse, ambient, specular);
            }
        }
    }
    return lightingColor;
}
void main() {
    vec3 vertex_normal;
    diffuse = vec4(0.0);
    ambient = vec4(0.0);
    specular = vec4(0.0);
    ambientGlobal = material.emission;
    eyeSpaceVertexPos = modelViewMatrix * position;
    vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    calc_lighting_color(vertex_normal, diffuse, ambient, specular);
    varyingtexcoord = vec2(texcoord.x, texcoord.y);
    gl_Position = modelViewProjectionMatrix * position;
}
