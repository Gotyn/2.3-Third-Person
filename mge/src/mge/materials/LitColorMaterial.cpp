#include <glm.hpp>

#include "mge/materials/LitColorMaterial.h"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"

ShaderProgram* LitColorMaterial::_shader = NULL;

GLint LitColorMaterial::_uModelMatrix = 0;
GLint LitColorMaterial::_uViewMatrix = 0;
GLint LitColorMaterial::_uPerspectiveMatrix = 0;

GLint LitColorMaterial::uGlobalAmbientIndex[3] = {0,0,0};
GLint LitColorMaterial::uDiffuseColorIndex[3] = {0,0,0};
GLint LitColorMaterial::uDirectionalLightColorIndex[3] = {0,0,0};
GLint LitColorMaterial::uLightPositionIndex[3] = {0,0,0};
GLint LitColorMaterial::uLightDirectionIndex[3] = {0,0,0};

GLint LitColorMaterial::uCameraPosIndex = 0;
GLint LitColorMaterial::_aVertex = 0;
GLint LitColorMaterial::_aNormal = 0;
GLint LitColorMaterial::_aUV = 0;

LitColorMaterial::LitColorMaterial(glm::vec3 pDiffuseColor, BaseLight* pLights[])
{
    _diffuseColor = pDiffuseColor;
    for(int i = 0; i < 3; ++i)
    {
        ambientColorArr[i] = pLights[i]->getAmbientColor();
        ambientIntensityArr[i] = pLights[i]->getAmbientIntensity();
        lightColorArr[i] = pLights[i]->getDirectionalLightColor();
        lightPositionArr[i] = pLights[i]->getLightPosition();
        lightDirectionArr[i] = pLights[i]->getLightDirection();
    }
    _lazyInitializeShader();
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

        uGlobalAmbientIndex[0]          = _shader->getUniformLocation ("pointLights[0].globalAmbient");
        uDiffuseColorIndex[0]           = _shader->getUniformLocation ("pointLights[0].diffuseColor");
        uDirectionalLightColorIndex[0]  = _shader->getUniformLocation ("pointLights[0].directionalLightColor");
        uLightPositionIndex[0]          = _shader->getUniformLocation ("pointLights[0].lightPosition");
        uLightDirectionIndex[0]         = _shader->getUniformLocation ("pointLights[0].lightDirection");

        uGlobalAmbientIndex[1]          = _shader->getUniformLocation ("pointLights[1].globalAmbient");
        uDiffuseColorIndex[1]           = _shader->getUniformLocation ("pointLights[1].diffuseColor");
        uDirectionalLightColorIndex[1]  = _shader->getUniformLocation ("pointLights[1].directionalLightColor");
        uLightPositionIndex[1]          = _shader->getUniformLocation ("pointLights[1].lightPosition");
        uLightDirectionIndex[1]         = _shader->getUniformLocation ("pointLights[1].lightDirection");

        uGlobalAmbientIndex[2]          = _shader->getUniformLocation ("pointLights[2].globalAmbient");
        uDiffuseColorIndex[2]           = _shader->getUniformLocation ("pointLights[2].diffuseColor");
        uDirectionalLightColorIndex[2]  = _shader->getUniformLocation ("pointLights[2].directionalLightColor");
        uLightPositionIndex[2]          = _shader->getUniformLocation ("pointLights[2].lightPosition");
        uLightDirectionIndex[2]         = _shader->getUniformLocation ("pointLights[2].lightDirection");

        uCameraPosIndex                 = _shader->getUniformLocation ("cameraPos"); //eye|camera|view position
        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV     = _shader->getAttribLocation("uv");
    }
}

LitColorMaterial::~LitColorMaterial()
{
    //dtor
}

void LitColorMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void LitColorMaterial::render(World* pWorld, GameObject* pGameObject, Camera* pCamera) {
    _shader->use();

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 modelMatrix       = pGameObject->getWorldTransform();
    glm::mat4 viewMatrix        = glm::inverse(pCamera->getWorldTransform());
    glm::mat4 perspectiveMatrix = pCamera->getProjection();
    glm::vec3 cameraPos         = pCamera->getWorldPosition();

    glUniformMatrix4fv ( _uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv ( _uViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv ( _uPerspectiveMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
    glUniform3fv (uCameraPosIndex, 1, glm::value_ptr(cameraPos));

    //set the material color
    glUniform3fv (uGlobalAmbientIndex[0], 1, glm::value_ptr(ambientColorArr[0] * ambientIntensityArr[0]));
    glUniform3fv (uDiffuseColorIndex[0], 1, glm::value_ptr(_diffuseColor));
    glUniform3fv (uDirectionalLightColorIndex[0], 1, glm::value_ptr(lightColorArr[0]));
    glUniform3fv (uLightPositionIndex[0], 1, glm::value_ptr(lightPositionArr[0]));
    glUniform3fv (uLightDirectionIndex[0], 1, glm::value_ptr(lightDirectionArr[0]));

    glUniform3fv (uGlobalAmbientIndex[1], 1, glm::value_ptr(ambientColorArr[1] * ambientIntensityArr[1]));
    glUniform3fv (uDiffuseColorIndex[1], 1, glm::value_ptr(_diffuseColor));
    glUniform3fv (uDirectionalLightColorIndex[1], 1, glm::value_ptr(lightColorArr[1]));
    glUniform3fv (uLightPositionIndex[1], 1, glm::value_ptr(lightPositionArr[1]));
    glUniform3fv (uLightDirectionIndex[1], 1, glm::value_ptr(lightDirectionArr[1]));

    glUniform3fv (uGlobalAmbientIndex[2], 1, glm::value_ptr(ambientColorArr[2] * ambientIntensityArr[2]));
    glUniform3fv (uDiffuseColorIndex[2], 1, glm::value_ptr(_diffuseColor));
    glUniform3fv (uDirectionalLightColorIndex[2], 1, glm::value_ptr(lightColorArr[2]));
    glUniform3fv (uLightPositionIndex[2], 1, glm::value_ptr(lightPositionArr[2]));
    glUniform3fv (uLightDirectionIndex[2], 1, glm::value_ptr(lightDirectionArr[2]));

    //now inform mesh of where to stream its data
    pGameObject->getMesh()->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
