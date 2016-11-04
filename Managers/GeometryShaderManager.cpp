//
//  ShaderManager.cpp
//  multilight
//
//  Created by Leo on 10/12/16.
//
//

#include "GeometryShaderManager.h"


//--------------------------------------------------------------
void GeometryShaderManager::reload(){
    setGeometryShader(currentKey);
}
//--------------------------------------------------------------
void GeometryShaderManager::setGeometryShader(int key){
    
    currentKey = key;
    
    switch (key) {
        
        case ' ':
            reload();
            break;
            
        case '0':
            shader.unload();
            shader.setGeometryInputType(GL_TRIANGLES);
            shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
            shader.setGeometryOutputCount(3);
            shader.load("passthrough.vert", "passthrough.frag", "passthrough.geom");
            currentGLInputType = GL_TRIANGLES;
            currentGLOutputType = GL_TRIANGLE_STRIP;
            _shaderName = "passtrough";
            break;
            
        case '1':
            shader.unload();
            shader.setGeometryInputType(GL_TRIANGLES);
            shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
            shader.setGeometryOutputCount(6);
            shader.load("duplicate.vert", "duplicate.frag", "duplicate.geom");
            currentGLInputType = GL_TRIANGLES;
            currentGLOutputType = GL_TRIANGLE_STRIP;
            _shaderName = "duplicate";
            break;
        
        case '2':
            shader.unload();
            shader.setGeometryInputType(GL_POINTS);
            shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
            shader.setGeometryOutputCount(24);
            shader.load("cubes.vert", "cubes.frag", "cubes.geom");
            currentGLInputType = GL_POINTS;
            currentGLOutputType = GL_TRIANGLE_STRIP;
            _shaderName = "cubes";
            break;
            
        case '3':
            shader.unload();
            shader.setGeometryInputType(GL_LINES);
            shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
            shader.setGeometryOutputCount(24);
            shader.load("cubelines.vert", "cubelines.frag", "cubelines.geom");
            currentGLInputType = GL_LINES;
            currentGLOutputType = GL_TRIANGLE_STRIP;
            _shaderName = "cubelines";
            break;
            
        case '4':
            shader.unload();
            shader.setGeometryInputType(GL_TRIANGLES);//GL_POINTS, GL_TRIANGLES
            shader.setGeometryOutputType(GL_LINE_STRIP);//GL_TRIANGLE_STRIP
            shader.setGeometryOutputCount(6);
            shader.load("normals.vert", "normals.frag", "normals.geom");
            currentGLInputType = GL_TRIANGLES;
            currentGLOutputType = GL_LINE_STRIP;
            _shaderName = "normals";
            break;
            
        
        default:
            break;
    }
}

