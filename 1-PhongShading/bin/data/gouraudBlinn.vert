
#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform int lightsNumber;

in vec4 position;
in vec3 normal;

out vec4 ambientGlobal, diffuse, ambient, specular;

vec4 v_eye;

void directional_light( in int lightIndex, in vec3 normal, inout vec4 diffuse, inout vec4 ambient, inout vec4 specular) {
    vec3 eyeVector, lightDir;
    float intensity;
    eyeVector = vec3(-v_eye);
    lightDir = normalize(lights.light[lightIndex].position.xyz);
    ambient += material.ambient * lights.light[lightIndex].ambient;
    intensity = max(dot(normal, lightDir), 0.0);
    if (intensity > 0.0) {
        vec3 halfVector;
        float NdotHV;
        diffuse += lights.light[lightIndex].diffuse * material.diffuse * intensity;
        halfVector = normalize(lightDir + eyeVector);
        NdotHV = max(dot(normal, halfVector), 0.0);
        specular += pow(NdotHV, material.shininess) * material.specular * lights.light[lightIndex].specular;
    }
}
void point_light( in int lightIndex, in vec3 normal, inout vec4 diffuse, inout vec4 ambient, inout vec4 specular) {
    vec3 lightDir;
    float intensity, dist;
    lightDir = vec3(lights.light[lightIndex].position - v_eye);
    dist = length(lightDir);
    intensity = max(dot(normal, normalize(lightDir)), 0.0);
    if (intensity > 0.0) {
        float att, NdotHV;
        vec3 halfVector;
        att = 1.0 / (lights.light[lightIndex].constant_attenuation + lights.light[lightIndex].linear_attenuation * dist + lights.light[lightIndex].quadratic_attenuation * dist * dist);
        diffuse += att * (material.diffuse * lights.light[lightIndex].diffuse * intensity);
        ambient += att * (material.ambient * lights.light[lightIndex].ambient);
        halfVector = normalize(lightDir - vec3(v_eye));
        NdotHV = max(dot(normal, halfVector), 0.0);
        specular += att * pow(NdotHV, material.shininess) * material.specular * lights.light[lightIndex].specular;
    }
}

void spot_light( in int lightIndex, in vec3 normal, inout vec4 diffuse, inout vec4 ambient, inout vec4 specular) {
    vec3 lightDir;
    float intensity, dist;
    lightDir = vec3(lights.light[lightIndex].position - v_eye);
    dist = length(lightDir);
    intensity = max(dot(normal, normalize(lightDir)), 0.0);
    if (intensity > 0.0) {
        float spotEffect, att, NdotHV;
        vec3 halfVector;
        spotEffect = dot(normalize(lights.light[lightIndex].spot_direction), normalize(-lightDir));
        if (spotEffect > lights.light[lightIndex].spot_cos_cutoff) {
            spotEffect = pow(spotEffect, lights.light[lightIndex].spot_exponent);
            att = spotEffect / (lights.light[lightIndex].constant_attenuation + lights.light[lightIndex].linear_attenuation * dist + lights.light[lightIndex].quadratic_attenuation * dist * dist);
            diffuse += att * material.diffuse * lights.light[lightIndex].diffuse * intensity;
            ambient += att * material.ambient * lights.light[lightIndex].ambient;
            halfVector = normalize(lightDir - vec3(v_eye));
            NdotHV = max(dot(normal, halfVector), 0.0);
            specular += att * pow(NdotHV, material.shininess) * material.specular * lights.light[lightIndex].specular;
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
    vec3 v_normal;
    diffuse = vec4(0.0);
    ambient = vec4(0.0);
    specular = vec4(0.0);
    ambientGlobal = material.emission;
    v_eye = modelViewMatrix * position;
    v_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    calc_lighting_color(v_normal, diffuse, ambient, specular);
    gl_Position = modelViewProjectionMatrix * position;
}
