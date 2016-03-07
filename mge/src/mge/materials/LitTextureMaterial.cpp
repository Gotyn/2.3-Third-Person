#include <glm.hpp>

#include "mge/core/RenderPipeline.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

//init static members
ShaderProgram* LitTextureMaterial::_shader = NULL;

LitTextureMaterial::LitTextureMaterial(Texture * pDiffuseTexture):_diffuseTexture(pDiffuseTexture)
{
    _lazyInitializeShader();
}

LitTextureMaterial::~LitTextureMaterial()
{

}

void LitTextureMaterial::_lazyInitializeShader()
{
    if (!_shader)
    {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"litTexture.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"litTexture.fs");
        _shader->finalize();
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

void LitTextureMaterial::render(RenderPipeline* pRenderPipeline, World* pWorld, GameObject* pGameObject, std::shared_ptr<Mesh> pMesh, Camera* pCamera)
{
    if (!_diffuseTexture) return;

    glEnable(GL_DEPTH_TEST);
    _shader->use();

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    glUniform1i (_shader->getUniformLocation("diffuseTexture"), 0);

    //setup texture slot 1 (shadowMap)
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pRenderPipeline->getShadowMap());
    glUniform1i (_shader->getUniformLocation("shadowMap"), 1);

    GLuint lightPos = _shader->getUniformLocation("lightPos");
    GLuint viewPos = _shader->getUniformLocation("viewPos");

    glUniform3fv(lightPos, 1, glm::value_ptr(glm::vec3(0.0f,0.0f,10.0f)));
    glUniform3fv(viewPos, 1, glm::value_ptr(pCamera->getOwner()->getWorldPosition()));

    //pass in all MVP matrices separately
    glUniformMatrix4fv ( _shader->getUniformLocation("projection"),   1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
    glUniformMatrix4fv ( _shader->getUniformLocation("view"),         1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getOwner()->getWorldTransform())));
    glUniformMatrix4fv ( _shader->getUniformLocation("model"),        1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform() ) );
    glUniformMatrix4fv ( _shader->getUniformLocation("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(pRenderPipeline->lightSpaceMatrix ) );

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(
        _shader->getAttribLocation("position"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("texCoords")
    );
}
