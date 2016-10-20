

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

//ofxShadersFX_LightingShader.cpp -----------------
m_normalMatrix = ofMatrix4x4::getTransposedOf(m_cam->getModelViewMatrix().getInverse());
m_shader.setUniformMatrix4f("normalMatrix", m_normalMatrix);
