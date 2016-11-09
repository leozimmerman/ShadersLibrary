// Copyright (C) 2016 Leo Zimmerman [http://www.leozimmerman.com.ar]

#version 330

layout(lines) in;

layout(triangle_strip, max_vertices = 24) out;

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

uniform float u_size;

in vec3 g_normal[2];

out vec4 v_eye;
out vec3 interp_eye;

out vec3 v_normal;


const int  cubeIndices[24]  = int [24](0,2,1,3,//front face
                                       2,6,3,7,//right face
                                       4,0,5,1,//left face
                                       6,4,7,5,//back face
                                       4,6,0,2,//bottom face
                                       1,3,5,7);//top face




void main(void) {
    
    
    
    vec3 p0 = gl_in[0].gl_Position.xyz;
    vec3 p1 = gl_in[1].gl_Position.xyz;
    
    vec3 up = vec3(0, 0, 1);	// arbitrary up vector
    
    vec3 dir = normalize(p1 - p0);			// normalized direction vector from p0 to p1
    vec3 ancho = normalize(cross(dir, up));	// ancho vector
    vec3 norm = cross(ancho, dir);
    
    vec3 alto = norm;
    vec3 normals[6] = vec3[6](normalize(dir),//front face - 0
                               normalize(ancho),//right face - 1
                               normalize(ancho * -1.),//left face - 2
                               normalize(dir * -1.),//back face - 3
                               normalize(alto * -1.),//bottom face - 4
                               normalize(alto)//top face - 5
                               );
    
    ancho*= u_size;
    alto *= u_size;
    
    //--------------------------------------------------------------------
    vec3 cubeVerts[8] = vec3[8](
                                p0 - ancho - alto, //LB 0
                                p0 - ancho + alto, //LT 1
                                p0 + ancho - alto, //RB 2
                                p0 + ancho + alto, //RT 3
                                //back face
                                p1 - ancho - alto, //LB 4
                                p1 - ancho + alto, //LT 5
                                p1 + ancho - alto, //RB 6
                                p1 + ancho + alto//RT 7
                                );
    
    for (int j=0; j<6; j++) {
        
        for (int i=(j*4); i<(j+1)*4; i++) {
            
            int iv = cubeIndices[i];
            vec3 cube_vert = cubeVerts[iv];
            
            vec4 view_position = modelViewMatrix * vec4(cube_vert, 1.0);
    
            v_eye = view_position;
            interp_eye = vec3(-v_eye);
            
            v_normal = vec3(normalMatrix * vec4(normals[j], 0));
            
            gl_Position = projectionMatrix * view_position;
            EmitVertex();
        }
        EndPrimitive();
    }
    

    
    
}


