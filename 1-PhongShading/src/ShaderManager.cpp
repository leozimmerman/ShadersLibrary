//
//  ShaderManager.cpp
//  multilight
//
//  Created by Leo on 10/12/16.




#include "ShaderManager.h"



void ShaderManager::load(string shaderName){
    
    shader.load(shaderName);
    _shaderName = shaderName;
    
}
//--------------------------------------------------------------

void ShaderManager::begin(){
    
    
    shader.begin();
    
    if (tex != NULL){
        shader.setUniformTexture("tex", (*tex), 1);
        tex->bind();
    }
    
    setupLights();
    setupMaterial();
    
}
//--------------------------------------------------------------
void ShaderManager::end(){
    
    shader.end();
    
    if (tex != NULL){
        tex->unbind();
    }
}
//--------------------------------------------------------------
void ShaderManager::reload(){
    
    shader.unload();
    shader.load(_shaderName);
    
}
//--------------------------------------------------------------
void ShaderManager::toggleTexture(ofImage *p_img){
    
    if (tex == NULL) {
        tex = p_img;
    }
    else {
        tex = NULL;
    }
}
//--------------------------------------------------------------
void ShaderManager::toggleLight(ofLight *p_light, bool state){

    bool isUsingLight = usingLight(p_light);
    
    if (state && !isUsingLight){
        useLight(p_light);
    }else if (!state && isUsingLight){
        removeLight(p_light);
    }
    
}
//--------------------------------------------------------------
void ShaderManager::useLight(ofLight * p_light){
    
    const size_t limit = this->MAX_LIGHTS;
    
    if (lights.size() < limit){
        lights.push_back(p_light);
    }
    else{
        ofLogError() << " cannot use more than " << limit << " lights" << endl;
    }
}
//--------------------------------------------------------------
void ShaderManager::removeLight(ofLight * p_light){
    
    vector<ofLight *>::iterator light;
    
    light = std::find(lights.begin(), lights.end(), p_light);
    
    if (light != lights.end()){
        lights.erase(light);
    }else {
        ofLogWarning() << "light isn't in this lighting shader" << endl;
    }
}
//--------------------------------------------------------------
bool ShaderManager::usingLight(ofLight * p_light){
    
    vector<ofLight *>::iterator light;
    
    light = std::find(lights.begin(), lights.end(), p_light);
    
    if (light != lights.end()){
        return true;
    }else {
        return false;
    }
    
}
//--------------------------------------------------------------
void ShaderManager::setupLights(){
    
    shader.setUniform1i("lightsNumber", lights.size());
    
    normalMatrix = ofMatrix4x4::getTransposedOf(cam->getModelViewMatrix().getInverse());
    shader.setUniformMatrix4f("normalMatrix", normalMatrix);
    
    GLuint lights_ubo;
    
    glGenBuffers(1, &lights_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, lights_ubo);
    
    GLuint uniformBlockIndex = glGetUniformBlockIndex (shader.getProgram(), "Lights");
    GLsizei uniformBlockSize(0);
    
    glGetActiveUniformBlockiv (shader.getProgram(), uniformBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);
    
    //If Lights uniform block is not Active, return:
    if (uniformBlockSize == 0) return;
    //--------------------------------------------
    
    vector<string> names = generateLightPropsNames();
    vector<const GLchar *> glnames;
    
    for (vector<string>::iterator str = names.begin(); str != names.end(); ++str)
    {
        glnames.push_back(str->c_str());
    }
    
    const GLchar **glnames_ptr = &glnames[0];
    GLuint indices[glnames.size()];
    
    glGetUniformIndices(shader.getProgram(), glnames.size(), glnames_ptr, indices);
    
    vector<GLint> lightUniformOffsets(glnames.size());
    
    glGetActiveUniformsiv(shader.getProgram(), lightUniformOffsets.size(),
                          indices, GL_UNIFORM_OFFSET, &lightUniformOffsets[0]);
    
    GLint *offsets = &lightUniformOffsets[0];
    const unsigned int uboSize (uniformBlockSize);
    vector<unsigned char> buffer(uboSize);
    
    for (size_t i = 0; i < lights.size(); i++)
    {
        setLightPosition(i, buffer, offsets);
        setLightColors(i, buffer, offsets);
        setLightAttenuation(i, buffer, offsets);
        setLightSpotProperties(i, buffer, offsets);
    }
    glBufferData(GL_UNIFORM_BUFFER, uboSize, &buffer[0], GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lights_ubo);
    glUniformBlockBinding (shader.getProgram(), uniformBlockIndex, 0);

}
//--------------------------------------------------------------
vector<string> ShaderManager::generateLightPropsNames() {
    vector<string> names;
    const char * props[] =
    {
        "].position",
        "].ambient",
        "].diffuse",
        "].specular",
        "].constant_attenuation",
        "].linear_attenuation",
        "].quadratic_attenuation",
        "].spot_direction",
        "].spot_cutoff",
        "].spot_cos_cutoff",
        "].spot_exponent"
    };
    
    for (size_t i = 0; i < lights.size(); i++)
    {
        stringstream ss_lightNumber("");
        string lightNumber;
        
        ss_lightNumber << i;
        lightNumber = ss_lightNumber.str();
        for (size_t s = 0; s < LIGHT_PROPS_NUMBER; s++)
        {
            names.push_back(string("Lights.light[") + lightNumber + string(props[s]));
        }
    }
    return names;
}

//--------------------------------------------------------------
void ShaderManager::setLightPosition(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets){
    
    int offset = offsets[0 + lightIndex * LIGHT_PROPS_NUMBER];
    ofVec3f eyeSpaceLightPos = lights[lightIndex]->getGlobalPosition() * cam->getModelViewMatrix();
    
    if (lights[lightIndex]->getIsDirectional()) {
        ofVec4f dir;
        
        dir = lights[lightIndex]->getLookAtDir();
        dir[3] = 0.0;
        dir = dir * normalMatrix;
        eyeSpaceLightPos = dir;
    }
    
    
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = eyeSpaceLightPos[i];///->TIRA ERROR: buffer size = 0
        offset += sizeof(GLfloat);
    }
    
    if (lights[lightIndex]->getIsDirectional())
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = 0.0; // light is a vector; no position
    }
    else
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = 1.0; // it is a position ; not a vector
    }
    
}
//--------------------------------------------------------------
void ShaderManager::setLightColors(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets) {
    int offset;
    
    // Light ambient color (vec4)
    offset = offsets[1 + lightIndex * LIGHT_PROPS_NUMBER];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = lights[lightIndex]->getAmbientColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = 1.0; // 100% alpha
    // Light diffuse color (vec4)
    offset = offsets[2 + lightIndex * LIGHT_PROPS_NUMBER];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = lights[lightIndex]->getDiffuseColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = 1.0; // 100% alpha
    // Light specular color (vec4)
    offset = offsets[3 + lightIndex * LIGHT_PROPS_NUMBER];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = lights[lightIndex]->getSpecularColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = 1.0; // 100% alpha
}
//--------------------------------------------------------------
void ShaderManager::setLightAttenuation(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets) {
    int offset;
    
    // Light constant attenuation (float)
    offset = offsets[4 + lightIndex * LIGHT_PROPS_NUMBER];
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = lights[lightIndex]->getAttenuationConstant();
    // Light linear attenuation (float)
    offset = offsets[5 + lightIndex * LIGHT_PROPS_NUMBER];
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = lights[lightIndex]->getAttenuationLinear();
    // Light quadratic attenuation (float)
    offset = offsets[6 + lightIndex * LIGHT_PROPS_NUMBER];
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = lights[lightIndex]->getAttenuationQuadratic();
}
//--------------------------------------------------------------
void ShaderManager::setLightSpotProperties(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets) {
    int offset;
    ofVec4f spotDir = ofVec4f(0., 0., -1., 1.);
    
    // it that's a spotlight : compute the 'real' spot direction
    if (lights[lightIndex]->getIsSpotlight())
    {
        ofVec4f dir;
        
        dir = lights[lightIndex]->getLookAtDir();
        dir[3] = 1.0;
        spotDir = dir * normalMatrix;
    }
    else
    {
        spotDir = ofVec4f(0., 0., -1., 1.) * normalMatrix; // a default spot direction (it's useful to compute it only for spotlight)
    }
    // Light spot direction (vec3)
    offset = offsets[7 + lightIndex * LIGHT_PROPS_NUMBER];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = spotDir[i];
        offset += sizeof (GLfloat);
    }
    // Light spot cutoff (float)
    offset = offsets[8 + lightIndex * LIGHT_PROPS_NUMBER];
    if (lights[lightIndex]->getIsSpotlight())
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = lights[lightIndex]->getSpotlightCutOff();
    }
    else
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = 360.0;
    }
    offset = offsets[9 + lightIndex * LIGHT_PROPS_NUMBER];
    if (lights[lightIndex]->getIsSpotlight())
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = cos(ofDegToRad(lights[lightIndex]->getSpotlightCutOff()));
    }
    // Light spot exponent (float)
    offset = offsets[10 + lightIndex * LIGHT_PROPS_NUMBER];
    if (lights[lightIndex]->getIsSpotlight())
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = lights[lightIndex]->getSpotConcentration();
    }
}
//--------------------------------------------------------------
void ShaderManager::setupMaterial(){
    // if no material provided, use the default one
    if (mat == NULL){
        mat = &defaultMat;
    }
    
    GLuint material_ubo;
    
    glGenBuffers(1, &material_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, material_ubo);
    
    const GLchar *uniformNames[5] =
    {
        "Material.ambient",
        "Material.diffuse",
        "Material.specular",
        "Material.emission",
        "Material.shininess"
    };
    
    GLuint uniformIndices[5];
    
    glGetUniformIndices (shader.getProgram(), 5, uniformNames, uniformIndices);
    
    GLint uniformOffsets[5];
    glGetActiveUniformsiv (shader.getProgram(), 5, uniformIndices,
                           GL_UNIFORM_OFFSET, uniformOffsets);
    
    GLuint uniformBlockIndex = glGetUniformBlockIndex (shader.getProgram(),
                                                       "Material");
    GLsizei uniformBlockSize (0);
    
    glGetActiveUniformBlockiv (shader.getProgram(), uniformBlockIndex,
                               GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);
    
    //If Material uniform block is not Active, return:
    if (uniformBlockSize == 0) return;
    //--------------------------------------------
    
    const unsigned int uboSize (uniformBlockSize);
    vector<unsigned char> buffer (uboSize);
    
    setMaterialProperties(buffer, uniformOffsets);
    
    glBufferData (GL_UNIFORM_BUFFER, uboSize, &buffer[0], GL_DYNAMIC_DRAW);
    glBindBufferBase (GL_UNIFORM_BUFFER, 1, material_ubo);
    glUniformBlockBinding (shader.getProgram(), uniformBlockIndex, 1);
    

}
//--------------------------------------------------------------

void ShaderManager::setMaterialProperties(vector<unsigned char> & buffer, const GLint * offsets){
    int offset;
    
    // Sphere material ambient color (vec4)
    offset = offsets[0];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float *> (&buffer[0] + offset)) =
        mat->getAmbientColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float *> (&buffer[0] + offset)) = 1.0; // 100% alpha
    // Sphere material diffuse color (vec4)
    offset = offsets[1];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float *> (&buffer[0] + offset)) =
        mat->getDiffuseColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float *> (&buffer[0] + offset)) = 1.0; // 100% alpha
    // Sphere material specular color (vec4)
    offset = offsets[2];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float *> (&buffer[0] + offset)) =
        mat->getSpecularColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float *> (&buffer[0] + offset)) = 1.0; // 100% alpha
    offset = offsets[3];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float *> (&buffer[0] + offset)) =
        mat->getEmissiveColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float *> (&buffer[0] + offset)) = 1.0; // 100% alpha
    
    // Sphere material shininess (float)
    offset = offsets[4];
    *(reinterpret_cast<float *> (&buffer[0] + offset)) =
    mat->getShininess();
}
