//https://github.com/McNopper/OpenGL/blob/master/Example07/shader/normmap.frag.glsl

#version 150

#pragma include "lights.glsl"

uniform sampler2DRect tex;
uniform sampler2DRect normalMapTex;

in vec2 varyingtexcoord;

uniform int lightsNumber;

in vec3 texSpaceLight[8];
in vec3 texSpaceEye;

out vec4 fragColor;

void main(void)
{
	// Note: All calculations are in texture space.
	vec4 textureColor = texture(tex, varyingtexcoord);

	// Fixed 0.3 ambient light.
    // (White light)
	vec4 color = 0.25 * textureColor;
    

	// Convert the color information to a normal.
	vec3 normalDX = normalize( texture(normalMapTex, varyingtexcoord).xyz * 2.0 - 1.0 );
	// DirectX: Origin of uv is upper left. OpenGL: Origin of st is lower left. Normal vector points "towards" us in both cases.
	// As normal maps usually are created for DirectX, we have to convert from DirectX to OpenGL tangent space.
	vec3 normal;
	normal.x = dot(vec3(1.0, 0.0, 0.0), normalDX);
	normal.y = dot(vec3(0.0, -1.0, 0.0), normalDX);
	normal.z = dot(vec3(0.0, 0.0, 1.0), normalDX);
	
    for (int i=0; i<lightsNumber; i++){
        
        vec3 light = normalize(texSpaceLight[i]);
        
        float nDotL = max(dot(light, normal), 0.0);
        
        if (nDotL > 0.0)
        {
            vec3 eye = normalize(texSpaceEye);
            
            // Incident vector is opposite light direction vector.
            vec3 reflection = reflect(-light, normal);
            
            float eDotR = max(dot(eye, reflection), 0.0);
            
            color += textureColor * nDotL;
            
            // Fixed 0.1 specular color factor and fixed 20.0 specular exponent.
            color += vec4(0.1, 0.1, 0.1, 0.1) * pow(eDotR, 20.0);
        }
    
    }
    
    color.w = 1.0;///Alpha always 1
    
	fragColor = color;	
}
