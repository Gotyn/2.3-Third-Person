#include <glm.hpp>

#include "mge/materials/LitColorMaterial.h"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

ShaderProgram* LitColorMaterial::_shader = NULL;
ShaderProgram* LitColorMaterial::_shadowShader = NULL;

GLint LitColorMaterial::_uModelMatrix = 0;
GLint LitColorMaterial::_uViewMatrix = 0;
GLint LitColorMaterial::_uPerspectiveMatrix = 0;
GLint LitColorMaterial::_uT_MVP = 0;

GLint LitColorMaterial::uGlobalAmbientIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uDiffuseColorIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uDirectionalLightColorIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uLightPositionIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uLightDirectionIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uConeAnglesIndex[MAX_LIGHTS_NUM];

GLint LitColorMaterial::uCameraPosIndex = 0;
GLint LitColorMaterial::_aVertex = 0;
GLint LitColorMaterial::_aNormal = 0;
GLint LitColorMaterial::_aUV = 0;
GLint LitColorMaterial::lightsUniforArraySize = 0;

glm::vec3 LitColorMaterial::ambientColors[MAX_LIGHTS_NUM];
glm::vec3 LitColorMaterial::lightColors[MAX_LIGHTS_NUM];
glm::vec3 LitColorMaterial::lightPositions[MAX_LIGHTS_NUM];
glm::vec3 LitColorMaterial::lightDirections[MAX_LIGHTS_NUM];
float LitColorMaterial::ambientIntensities[MAX_LIGHTS_NUM];
float LitColorMaterial::coneAngles[MAX_LIGHTS_NUM];

int LitColorMaterial::tempSize = 0;
World* LitColorMaterial::_myWorld;

LitColorMaterial::LitColorMaterial(glm::vec3 pDiffuseColor, World* pWorld, Texture * pDiffuseTexture): _diffuseTexture(pDiffuseTexture)
{
    _diffuseColor = pDiffuseColor;
    _myWorld = pWorld;
    _lazyInitializeShader();
}

LitColorMaterial::~LitColorMaterial()
{
    //dtor
}

void LitColorMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

string LitColorMaterial::uniName(string propertyName, int lightIndex) {
    std::stringstream ss;
    ss << "pointLights[" << lightIndex << "]." << propertyName;
    std::string uniformName = ss.str();
    return uniformName;
}

void LitColorMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader && !_shadowShader)
    {
        //create shader for lights
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"litcolor.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"litcolor.fs");
        _shader->finalize();

        //create shader for shadows
        _shadowShader = new ShaderProgram();
        _shadowShader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"shadowMap.vs");
        _shadowShader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"shadowMap.fs");
        _shadowShader->finalize();

        //SHADOW SHADER: cachee all the uniform and attribute indexes
        _uT_MVP = _shadowShader->getUniformLocation("T_MVP");
        _aVertex = _shadowShader->getAttribLocation("vertex");

        //LIGHT SHADER: cachee all the uniform and attribute indexes
        _uModelMatrix       = _shader->getUniformLocation("modelMatrix");
        _uViewMatrix        = _shader->getUniformLocation("viewMatrix");
        _uPerspectiveMatrix = _shader->getUniformLocation("perspectiveMatrix");

        uCameraPosIndex                 = _shader->getUniformLocation ("cameraPos"); //eye|camera|view position
        lightsUniforArraySize           = _shader->getUniformLocation ("uniformArraySize");
        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV     = _shader->getAttribLocation("uv");

        tempSize = _myWorld->sceneLights().size();
        if (tempSize > 0) {
            for (int i = 0; i < MAX_LIGHTS_NUM; ++i)
            {
                uGlobalAmbientIndex[i]          = _shader->getUniformLocation (uniName("globalAmbient",i));
                uDiffuseColorIndex[i]           = _shader->getUniformLocation (uniName("diffuseColor",i));
                uDirectionalLightColorIndex[i]  = _shader->getUniformLocation (uniName("directionalLightColor",i));
                uLightPositionIndex[i]          = _shader->getUniformLocation (uniName("lightPosition",i));
                uLightDirectionIndex[i]         = _shader->getUniformLocation (uniName("lightDirection",i));
                uConeAnglesIndex[i]             = _shader->getUniformLocation (uniName("coneAngles",i));
            }
        }
    }
}

void LitColorMaterial::render(World* pWorld, GameObject* pGameObject, Mesh* pMesh, Camera* pCamera)
{
    if (!_diffuseTexture) return;

    _shadowShader->use();
    // --------------------- SHADOW IMPLEMENTATION STARTS HERE ----------------------- //

    // --------------------- SHADOW IMPLEMENTATION ENDS HERE ----------------------- //


    _shader->use();
    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    glUniform1i (_shader->getUniformLocation("textureDiffuse"), 0);

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 modelMatrix       = pGameObject->getWorldTransform();
    glm::mat4 viewMatrix        = glm::inverse(pCamera->getOwner()->getWorldTransform());
    glm::mat4 perspectiveMatrix = pCamera->getProjection();
    glm::vec3 cameraPos         = pCamera->getOwner()->getWorldPosition();

    glUniformMatrix4fv ( _uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv ( _uViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv ( _uPerspectiveMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
    glUniform3fv (uCameraPosIndex, 1, glm::value_ptr(cameraPos));
    //get current amount of lights
    tempSize = pWorld->sceneLights().size();
    //send current amount of lights
    glUniform1i (lightsUniforArraySize, tempSize);
    //set the material color
    if(tempSize > 0 && tempSize <= MAX_LIGHTS_NUM) {
        for (int i = 0; i < tempSize; ++i)
        {
            //update material colors and lights data
            ambientColors[i]        = pWorld->sceneLights().at(i)->getAmbientColor();
            ambientIntensities[i]   = pWorld->sceneLights().at(i)->getAmbientIntensity();
            lightColors[i]          = pWorld->sceneLights().at(i)->getDirectionalLightColor();
            lightPositions[i]       = pWorld->sceneLights().at(i)->getLightPosition();
            lightDirections[i]      = pWorld->sceneLights().at(i)->getLightDirection();
            coneAngles[i]           = pWorld->sceneLights().at(i)->getConeAngle();

            glUniform3fv (uGlobalAmbientIndex[i], 1, glm::value_ptr(ambientColors[i] * ambientIntensities[i]));
            glUniform3fv (uDiffuseColorIndex[i], 1, glm::value_ptr(_diffuseColor));
            glUniform3fv (uDirectionalLightColorIndex[i], 1, glm::value_ptr(lightColors[i]));
            glUniform3fv (uLightPositionIndex[i], 1, glm::value_ptr(lightPositions[i]));
            glUniform3fv (uLightDirectionIndex[i], 1, glm::value_ptr(lightDirections[i]));
            glUniform1f (uConeAnglesIndex[i], coneAngles[i]);
        }
    }
    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
