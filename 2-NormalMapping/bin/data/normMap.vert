#version 330

#pragma include "lights.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

in vec4 position;
in vec3 normal;

in vec2 texcoord;

out vec2 varyingtexcoord;

uniform int lightsNumber;

out vec3 texSpaceLight[8];
out vec3 texSpaceEye;

void main(void)
{
	varyingtexcoord = texcoord;

	
    //-Tangent space calculation---------
    //http://www.geeks3d.com/20130122/normal-mapping-without-precomputed-tangent-space-vectors/
    
    vec3 n_normal = vec3(normalMatrix) * normal;
    
    vec3 tangent;
    vec3 bitangent;
    vec3 c1 = cross(n_normal, vec3(0.0, 0.0, 1.0));
    vec3 c2 = cross(n_normal, vec3(0.0, 1.0, 0.0));
    if (length(c1) > length(c2))
        tangent = c1;
    else
        tangent = c2;
    tangent     = normalize(tangent);
    bitangent   = normalize(cross(n_normal, tangent));
    
    
	// The inverse brings the light from camera to texture space.
	// tx ty tz   lightDirectionx
	// bx by bz * lightDirectiony
	// nx ny nz   lightDirectionz
    
    // Bring vertex in camera space.
    vec4 spaceVertex = modelViewMatrix * position;
    
    for (int i=0; i<lightsNumber; i++){
        
        vec3 lightDirection = vec3(lights.light[i].position - spaceVertex);
        
        texSpaceLight[i].x = dot(tangent,   lightDirection);
        texSpaceLight[i].y = dot(bitangent, lightDirection);
        texSpaceLight[i].z = dot(n_normal,  lightDirection);
    }
    
	
	// Calculate eye vector, which is in camera space.
	vec3 v_vertex = vec3(-spaceVertex) ;
	
	// Like the light, this brings the eye vector to texture space.
	texSpaceEye.x = dot(v_vertex, tangent);
	texSpaceEye.y = dot(v_vertex, bitangent);
	texSpaceEye.z = dot(v_vertex, n_normal);

	//gl_Position = u_projectionMatrix*vertex;
    gl_Position = modelViewProjectionMatrix * position;
}
