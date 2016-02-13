#include <glm.hpp>

#include "mge/materials/LitColorMaterial.h"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

ShaderProgram* LitColorMaterial::_shader = NULL;

GLint LitColorMaterial::_uModelMatrix = 0;
GLint LitColorMaterial::_uViewMatrix = 0;
GLint LitColorMaterial::_uPerspectiveMatrix = 0;

GLint LitColorMaterial::uGlobalAmbientIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uDiffuseColorIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uDirectionalLightColorIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uLightPositionIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uLightDirectionIndex[MAX_LIGHTS_NUM];

GLint LitColorMaterial::uCameraPosIndex = 0;
GLint LitColorMaterial::_aVertex = 0;
GLint LitColorMaterial::_aNormal = 0;
GLint LitColorMaterial::_aUV = 0;
GLint LitColorMaterial::lightsUniforArraySize = 0;

glm::vec3 LitColorMaterial::ambientColors[MAX_LIGHTS_NUM];
float LitColorMaterial::ambientIntensities[MAX_LIGHTS_NUM];
glm::vec3 LitColorMaterial::lightColors[MAX_LIGHTS_NUM];
glm::vec3 LitColorMaterial::lightPositions[MAX_LIGHTS_NUM];
glm::vec3 LitColorMaterial::lightDirections[MAX_LIGHTS_NUM];
int LitColorMaterial::tempSize = 0;
World* LitColorMaterial::_myWorld;

LitColorMaterial::LitColorMaterial(glm::vec3 pDiffuseColor, World* pWorld)
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

void LitColorMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader)
    {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"litcolor.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"litcolor.fs");
        _shader->finalize();

        //cachee all the uniform and attribute indexes
        _uModelMatrix       = _shader->getUniformLocation("modelMatrix");
        _uViewMatrix        = _shader->getUniformLocation("viewMatrix");
        _uPerspectiveMatrix = _shader->getUniformLocation("perspectiveMatrix");

        tempSize = _myWorld->sceneLights().size();
        if (tempSize > 0 && tempSize <= MAX_LIGHTS_NUM) {
            for (int i = 0; i < tempSize; ++i)
            {
                switch(i) {
                case 0:
                    uGlobalAmbientIndex[0]          = _shader->getUniformLocation ("pointLights[0].globalAmbient");
                    uDiffuseColorIndex[0]           = _shader->getUniformLocation ("pointLights[0].diffuseColor");
                    uDirectionalLightColorIndex[0]  = _shader->getUniformLocation ("pointLights[0].directionalLightColor");
                    uLightPositionIndex[0]          = _shader->getUniformLocation ("pointLights[0].lightPosition");
                    uLightDirectionIndex[0]         = _shader->getUniformLocation ("pointLights[0].lightDirection");
                    break;
                case 1:
                    uGlobalAmbientIndex[1]          = _shader->getUniformLocation ("pointLights[1].globalAmbient");
                    uDiffuseColorIndex[1]           = _shader->getUniformLocation ("pointLights[1].diffuseColor");
                    uDirectionalLightColorIndex[1]  = _shader->getUniformLocation ("pointLights[1].directionalLightColor");
                    uLightPositionIndex[1]          = _shader->getUniformLocation ("pointLights[1].lightPosition");
                    uLightDirectionIndex[1]         = _shader->getUniformLocation ("pointLights[1].lightDirection");
                    break;
                case 2:
                    uGlobalAmbientIndex[2]          = _shader->getUniformLocation ("pointLights[2].globalAmbient");
                    uDiffuseColorIndex[2]           = _shader->getUniformLocation ("pointLights[2].diffuseColor");
                    uDirectionalLightColorIndex[2]  = _shader->getUniformLocation ("pointLights[2].directionalLightColor");
                    uLightPositionIndex[2]          = _shader->getUniformLocation ("pointLights[2].lightPosition");
                    uLightDirectionIndex[2]         = _shader->getUniformLocation ("pointLights[2].lightDirection");
                    break;
                case 3:
                    uGlobalAmbientIndex[3]          = _shader->getUniformLocation ("pointLights[3].globalAmbient");
                    uDiffuseColorIndex[3]           = _shader->getUniformLocation ("pointLights[3].diffuseColor");
                    uDirectionalLightColorIndex[3]  = _shader->getUniformLocation ("pointLights[3].directionalLightColor");
                    uLightPositionIndex[3]          = _shader->getUniformLocation ("pointLights[3].lightPosition");
                    uLightDirectionIndex[3]         = _shader->getUniformLocation ("pointLights[3].lightDirection");
                    break;
                case 4:
                    uGlobalAmbientIndex[4]          = _shader->getUniformLocation ("pointLights[4].globalAmbient");
                    uDiffuseColorIndex[4]           = _shader->getUniformLocation ("pointLights[4].diffuseColor");
                    uDirectionalLightColorIndex[4]  = _shader->getUniformLocation ("pointLights[4].directionalLightColor");
                    uLightPositionIndex[4]          = _shader->getUniformLocation ("pointLights[4].lightPosition");
                    uLightDirectionIndex[4]         = _shader->getUniformLocation ("pointLights[4].lightDirection");
                    break;
                default:
                    uGlobalAmbientIndex[0]          = _shader->getUniformLocation ("pointLights[0].globalAmbient");
                    uDiffuseColorIndex[0]           = _shader->getUniformLocation ("pointLights[0].diffuseColor");
                    uDirectionalLightColorIndex[0]  = _shader->getUniformLocation ("pointLights[0].directionalLightColor");
                    uLightPositionIndex[0]          = _shader->getUniformLocation ("pointLights[0].lightPosition");
                    uLightDirectionIndex[0]         = _shader->getUniformLocation ("pointLights[0].lightDirection");
                    break;
                }
                //fill in material colors and lights data
                ambientColors[i] = _myWorld->sceneLights().at(i)->getAmbientColor();
                ambientIntensities[i] = _myWorld->sceneLights().at(i)->getAmbientIntensity();
                lightColors[i] = _myWorld->sceneLights().at(i)->getDirectionalLightColor();
                lightPositions[i] = _myWorld->sceneLights().at(i)->getLightPosition();
                lightDirections[i] = _myWorld->sceneLights().at(i)->getLightDirection();
            }
        }

        uCameraPosIndex                 = _shader->getUniformLocation ("cameraPos"); //eye|camera|view position
        lightsUniforArraySize           = _shader->getUniformLocation ("uniformArraySize");
        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV     = _shader->getAttribLocation("uv");
    }
}

void LitColorMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    _shader->use();
    //get current amount of lights
    tempSize = pWorld->sceneLights().size();
    if(tempSize > 0) {
        for(int i = 0; i < tempSize; ++i)
        {
            //update material colors and lights data
            ambientColors[i] = pWorld->sceneLights().at(i)->getAmbientColor();
            ambientIntensities[i] = pWorld->sceneLights().at(i)->getAmbientIntensity();
            lightColors[i] = pWorld->sceneLights().at(i)->getDirectionalLightColor();
            lightPositions[i] = pWorld->sceneLights().at(i)->getLightPosition();
            lightDirections[i] = pWorld->sceneLights().at(i)->getLightDirection();
        }
    }

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 modelMatrix       = pGameObject->getWorldTransform();
    glm::mat4 viewMatrix        = glm::inverse(pCamera->getWorldTransform());
    glm::mat4 perspectiveMatrix = pCamera->getProjection();
    glm::vec3 cameraPos         = pCamera->getWorldPosition();

    glUniformMatrix4fv ( _uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv ( _uViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv ( _uPerspectiveMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
    glUniform3fv (uCameraPosIndex, 1, glm::value_ptr(cameraPos));
    //send current amount of lights
    glUniform1i (lightsUniforArraySize, tempSize);

    //set the material color
    if(tempSize > 0 && tempSize <= MAX_LIGHTS_NUM) {
        for (int i = 0; i < tempSize; ++i)
        {
            glUniform3fv (uGlobalAmbientIndex[i], 1, glm::value_ptr(ambientColors[i] * ambientIntensities[i]));
            glUniform3fv (uDiffuseColorIndex[i], 1, glm::value_ptr(_diffuseColor));
            glUniform3fv (uDirectionalLightColorIndex[i], 1, glm::value_ptr(lightColors[i]));
            glUniform3fv (uLightPositionIndex[i], 1, glm::value_ptr(lightPositions[i]));
            glUniform3fv (uLightDirectionIndex[i], 1, glm::value_ptr(lightDirections[i]));
        }
    }

    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
