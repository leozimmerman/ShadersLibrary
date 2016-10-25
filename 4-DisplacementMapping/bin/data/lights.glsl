
//#version 330

struct Light {
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float constant_attenuation;
    float linear_attenuation;
    float quadratic_attenuation;
    vec3 spot_direction;
    float spot_cutoff;
    float spot_cos_cutoff;
    float spot_exponent;
};

uniform Lights {
    Light light[8];
}
lights;
