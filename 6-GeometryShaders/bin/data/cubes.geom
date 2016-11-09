// Copyright (C) 2016 Leo Zimmerman [http://www.leozimmerman.com.ar]

#version 330

// A triangle with three points come in
layout(points) in;

// Out of three triangle points, we create a triangle strip with two triangles
layout(triangle_strip, max_vertices = 24) out;

#pragma include "lights.glsl"
#pragma include "material.glsl"

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

uniform float u_size;

in vec3 g_normal[1];

out vec4 v_eye;
out vec3 interp_eye;

out vec3 v_normal;

const vec3 cubeVerts[8] = vec3[8](
                                  //front face
                                  vec3(-0.5 , -0.5, 0.5),//LB 0
                                  vec3(-0.5 , 0.5, 0.5), //LT 1
                                  vec3(0.5 , -0.5, 0.5), //RB 2
                                  vec3(0.5 , 0.5, 0.5),  //RT 3
                                  //back face
                                  vec3(-0.5 , -0.5, -0.5), //LB 4
                                  vec3(-0.5 , 0.5, -0.5),  //LT 5
                                  vec3(0.5 , -0.5, -0.5),  //RB 6
                                  vec3(0.5 , 0.5, -0.5)    //RT 7
                                  );

const vec3 normals[6] = vec3[6](
                                vec3(0.0 , 0.0, 1.0),//front face - 0
                                vec3(1.0 , 0.0, 0.0),//right face - 1
                                vec3(-1.0 , 0.0, 0.0),//left face - 2
                                vec3(0.0 , 0.0, -1.0),//back face - 3
                                vec3(0.0 , -1.0, 0.0),//bottom face - 4
                                vec3(0.0 , 1.0, 0.0)//top face - 5
                                );

const int  cubeIndices[24]  = int [24](0,2,1,3,//front face
                                       2,6,3,7,//right face
                                       4,0,5,1,//left face
                                       6,4,7,5,//back face
                                       4,6,0,2,//bottom face
                                       1,3,5,7);//top face




void main(void) {
    
    vec4 position = gl_in[0].gl_Position;
    
    for (int j=0; j<6; j++) {
        
        for (int i=(j*4); i<(j+1)*4; i++) {
            
            int iv = cubeIndices[i];
            
            vec4 cube_vert = position + vec4(cubeVerts[iv] ,0) * u_size;
            
            vec4 view_position = modelViewMatrix * cube_vert;
            
            v_eye = view_position;
            interp_eye = vec3(-v_eye);
        
            //v_normal = normalize(g_normal[0] * normals[j]);
            //v_normal = normals[j];
            v_normal = vec3(normalMatrix * vec4(normals[j], 0));
            
            gl_Position = projectionMatrix * view_position;
            EmitVertex();
            
        }
        EndPrimitive();
        
    }
    
    
}


