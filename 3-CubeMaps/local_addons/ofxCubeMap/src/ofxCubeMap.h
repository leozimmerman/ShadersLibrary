/*
 *  Inspired by Cinder CubeMap David Wicks on 2/27/09.
 *  Ported to oF by brenfer on 7/2/10.
 *  Updated for of 007 and extended by James George 2/13/11
 *
 *  Made working-happily by Joshy-pants and James George
 * 
 *  Not copyrighted, no rights reserved, long live Christiania.
 *
 *  Edited some more by Andreas Müller. Come on, edit moar!
 * 
 */


/*
 * OpenGL defines the cube faces in this order:
 * 
 * #define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
 * #define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
 *
 * #define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
 * #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
 *
 * #define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
 * #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
 *
 * You can therefore loop through all of them like this
 *
 *
 *   for (int i = 0; i < 6; ++i)
 *   {
 * 	    someFunction( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i );
 *   }
 *
 *
 */


#ifndef	OFX_CUBE_MAP_H
#define OFX_CUBE_MAP_H

#include "ofMain.h"

class ofxCubeMap
{
	public:
		
		ofxCubeMap();

		// Init ---------------------
	
		// These should all be the same size and all power of two, i.e. 256, 512, 1024 (I think).
		void loadImages( string pos_x, string neg_x,
						 string pos_y, string neg_y,
						 string pos_z, string neg_z );
		
		void loadFromOfImages( ofImage pos_x, ofImage neg_x,
							   ofImage pos_y, ofImage neg_y,
							   ofImage pos_z, ofImage neg_z );

		// Drawing ------------------
	
		void initEmptyTextures( int _size, GLuint _channels = GL_RGB, GLuint _storageFormat = GL_UNSIGNED_BYTE );				// Initialize empty textures to draw on later.
		
		void bind();
		void bindToTextureUnit( int pos ); 		// Todo: just overload bind with a default parameter of 0
		void unbind();
	
		void drawSkybox( float _size ); 		// Todo: why does this not bind the cubemap texture?!
	
		// Drawing into -------------
	
		void beginDrawingInto2D( GLuint _face );								// Pass in GL_TEXTURE_CUBE_MAP_POSITIVE_X, etc.
		void endDrawingInto2D();
	
		void beginDrawingInto3D( GLuint _face );								// Gives you camera looking in the direction of the cube face
		void endDrawingInto3D();
		
		// Misc ---------------------
	
		void debugDrawCubemapCameras();
		void debugDrawCubemapFaces( float _faceSize, float _border = 0.0f );

		void drawFace( GLuint _face, float _x, float _y );
		void drawFace( GLuint _face, float _x, float _y, float _w, float _h );
	
		unsigned int getTextureID();
	
		int getWidth();
		int getHeight();
	
		float getFov();
		void  setFov( float _fov );
			
		ofVec2f getNearFar();
		void 	setNearFar( ofVec2f _nearFar );
	
		void setPosition( ofVec3f& _pos );
		void setPosition( float _x, float _y, float _z );
		ofVec3f* getPosition();

		ofMatrix4x4 getProjectionMatrix();
		ofMatrix4x4 getLookAtMatrixForFace( GLuint _face );

	private:
		
		string getDescriptiveStringForFace( GLuint _face );
		void setupSkyBoxVertices();
	
		int size;
	
		unsigned int textureObjectID;
		
		ofFbo fbo;
			
		// swap for an ofMesh when it supports ofVec3f tex coordinates
		vector<ofVec3f> scratchVertices;
		vector<ofVec3f> scratchTexCoords;
		vector<ofIndexType> scratchIndices;
	
		vector<ofVec3f> cubemapVertices;
		vector<ofVec3f> cubemapTexCoords;
	
		float fov;
		float nearZ;
		float farZ;
	
		ofVec3f		cubeMapCamerasRenderPosition;
	
		int boundToTextureUnit;
};

#endif //OFX_CUBE_MAP_H

