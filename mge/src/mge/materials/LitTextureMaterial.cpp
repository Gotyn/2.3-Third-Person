#include <glm.hpp>

#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

//init static members
ShaderProgram* LitTextureMaterial::_shader = NULL;
ShaderProgram* LitTextureMaterial::_depthShader = NULL;

LitTextureMaterial::LitTextureMaterial(Texture * pDiffuseTexture):_diffuseTexture(pDiffuseTexture)
{
    _lazyInitializeShader();
}

LitTextureMaterial::~LitTextureMaterial() {}

void LitTextureMaterial::_lazyInitializeShader()
{
    if (!_shader)
    {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"texture.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"texture.fs");
        _shader->finalize();
    }

    if (!_depthShader)
    {
        _depthShader = new ShaderProgram();
        _depthShader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"simpleDepthShader.vs");
        _depthShader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"simpleDepthShader.fs");
        _depthShader->finalize();
    }
}

void LitTextureMaterial::setDiffuseTexture (Texture* pDiffuseTexture)
{
    _diffuseTexture = pDiffuseTexture;
}

void LitTextureMaterial::changeDiffuseTexture (std::string pFilename)
{
    setDiffuseTexture(Texture::load("mge/textures/" + pFilename));
}

void LitTextureMaterial::render(World* pWorld, GameObject* pGameObject, Mesh* pMesh, Camera* pCamera)
{
    if (!_diffuseTexture) return;

    //create a framebuffer object for rendering the depth map
    GLuint depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    //next we create a 2D texture that we'll use as the framebuffer's depth buffer
    const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    GLuint depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //with the generated depth texture we can attach it as the framebuffer's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    _depthShader->use();

    //light space transform
    GLfloat near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f), glm::vec3(1.0));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    //pass in matrices
    glUniformMatrix4fv(_depthShader->getUniformLocation("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
    glUniformMatrix4fv ( _depthShader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform() ) );


    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // --- end of shadowmap render --- //
_shader->use();

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    glUniform1i (_shader->getUniformLocation("textureDiffuse"), 0);

    //pass in all MVP matrices separately
    glUniformMatrix4fv ( _shader->getUniformLocation("projectionMatrix"),   1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _shader->getUniformLocation("viewMatrix"),         1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getOwner()->getWorldTransform())));
    glUniformMatrix4fv ( _shader->getUniformLocation("modelMatrix"),        1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform() ) );

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );
}

void LitTextureMaterial::renderScene(ShaderProgram* pShader)
{

}
