
#version 330

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
uniform int lightsNumber;

in vec4 position;
in vec4 v_eye, ambientGlobal;
in vec3 v_normal, interp_eyePos;

out vec4 fragColor;

vec4 directional_light( in int lightIndex, in vec3 normal) {
    vec4 outputColor = vec4(0.0);
    vec3 eyeVector, lightDir;
    vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
    float intensity;
    eyeVector = normalize(interp_eyePos);
    lightDir = normalize(lights.light[lightIndex].position.xyz);
    ambient = material.ambient * lights.light[lightIndex].ambient;
    outputColor += ambient;
    intensity = max(dot(normal, lightDir), 0.0);
    if (intensity > 0.0) {
        vec3 halfVector;
        float NdotHV;
        diffuse = lights.light[lightIndex].diffuse * material.diffuse;
        outputColor += diffuse * intensity;
        halfVector = normalize(lightDir + eyeVector);
        NdotHV = max(dot(normal, halfVector), 0.0);
        specular = pow(NdotHV, material.shininess) * material.specular * lights.light[lightIndex].specular;
        outputColor += specular;
    }
    outputColor.w = 1.0;
    return outputColor;
}

vec4 point_light( in int lightIndex, in vec3 normal) {
    vec3 lightDir;
    vec4 pointLightColor;
    float intensity, dist;

    pointLightColor = vec4(0.0);
    lightDir = vec3(lights.light[lightIndex].position - v_eye);
    dist = length(lightDir);
    intensity = max(dot(normal, normalize(lightDir)), 0.0);
    if (intensity > 0.0) {
        float att, NdotHV;
        vec4 diffuse, specular, ambient = vec4(0.0);
        vec3 halfVector;

        att = 1.0 / (lights.light[lightIndex].constant_attenuation + lights.light[lightIndex].linear_attenuation * dist + lights.light[lightIndex].quadratic_attenuation * dist * dist);
        diffuse = material.diffuse * lights.light[lightIndex].diffuse;
        ambient = material.ambient * lights.light[lightIndex].ambient;
        pointLightColor += att * (diffuse * intensity + ambient);
        halfVector = normalize(lightDir - vec3(v_eye));
        NdotHV = max(dot(normal, halfVector), 0.0);
        specular = pow(NdotHV, material.shininess) * material.specular * lights.light[lightIndex].specular;
        pointLightColor += att * specular;
    }
    return pointLightColor;
}

vec4 spot_light( in int lightIndex, in vec3 normal) {
    vec3 lightDir;
    vec4 spotLightColor;
    float intensity, dist;

    spotLightColor = vec4(0.0);
    lightDir = vec3(lights.light[lightIndex].position - v_eye);
    dist = length(lightDir);
    intensity = max(dot(normal, normalize(lightDir)), 0.0);
    if (intensity > 0.0) {
        float spotEffect, att, NdotHV;
        vec4 diffuse, specular, ambient = vec4(0.0);
        vec3 halfVector;

        spotEffect = dot(normalize(lights.light[lightIndex].spot_direction), normalize(-lightDir));
        if (spotEffect > lights.light[lightIndex].spot_cos_cutoff) {
            spotEffect = pow(spotEffect, lights.light[lightIndex].spot_exponent);
            att = spotEffect / (lights.light[lightIndex].constant_attenuation + lights.light[lightIndex].linear_attenuation * dist + lights.light[lightIndex].quadratic_attenuation * dist * dist);
            diffuse = material.diffuse * lights.light[lightIndex].diffuse;
            ambient = material.ambient * lights.light[lightIndex].ambient;
            spotLightColor += att * (diffuse * intensity + ambient);
            halfVector = normalize(lightDir - vec3(v_eye));
            NdotHV = max(dot(normal, halfVector), 0.0);
            specular = pow(NdotHV, material.shininess) * material.specular * lights.light[lightIndex].specular;
            spotLightColor += att * specular;
        }
    }
    return spotLightColor;
}

vec4 calc_lighting_color( in vec3 normal) {
    vec4 lightingColor = vec4(0.0);

    for (int i = 0; i < lightsNumber; i++) {
        if (lights.light[i].position.w == 0.0) {
            lightingColor += directional_light(i, normal);
        } else {
            if (lights.light[i].spot_cutoff <= 90.0) {
                lightingColor += spot_light(i, normal);
            } else {
                lightingColor += point_light(i, normal);
            }
        }
    }
    return lightingColor;
}

void main() {
    vec3 n;

    fragColor = ambientGlobal;
    n = normalize(v_normal);
    fragColor += calc_lighting_color(n);
    fragColor.w = 1.0;
}
