

uniform mat4 normalMatrix; // ofMatrix4x4::getTransposedOf(m_cam->getModelViewMatrix().getInverse());

//ofShader.cpp ------------
static const string COLOR_ATTRIBUTE="color";
static const string POSITION_ATTRIBUTE="position";
static const string NORMAL_ATTRIBUTE="normal";
static const string TEXCOORD_ATTRIBUTE="texcoord";


//ofGLProgrammableRenderer.cpp --------------------

static const string VIEW_MATRIX_UNIFORM="viewMatrix";
static const string MODELVIEW_MATRIX_UNIFORM="modelViewMatrix";
static const string PROJECTION_MATRIX_UNIFORM="projectionMatrix";
static const string MODELVIEW_PROJECTION_MATRIX_UNIFORM="modelViewProjectionMatrix";
static const string TEXTURE_MATRIX_UNIFORM="textureMatrix";
static const string COLOR_UNIFORM="globalColor";

static const string USE_TEXTURE_UNIFORM="usingTexture";
static const string USE_COLORS_UNIFORM="usingColors";
static const string BITMAP_STRING_UNIFORM="bitmapText";

//LightShaderManager.cpp -----------------
normalMatrix = ofMatrix4x4::getTransposedOf(m_cam->getModelViewMatrix().getInverse());
shader.setUniformMatrix4f("normalMatrix", normalMatrix);

//----------------------------------------------------------
// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec3 normal;
in vec4 color;
in vec2 texcoord;
// this is the end of the default functionality
