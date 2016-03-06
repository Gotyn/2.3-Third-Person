#include "DepthMapper.hpp"
#include "config.hpp"

//init static members
ShaderProgram* DepthMapper::_shader = NULL;

DepthMapper::DepthMapper(GLuint pDepthMapFBO, GLuint pDepthMap, int pShadowWidth, int pShadowHeight)
                : _depthMapFBO(pDepthMapFBO), _depthMap(pDepthMap), _shadowWidth(pShadowWidth), _shadowHeight(pShadowHeight)
{
    _lazyInitializeShader();
}

DepthMapper::~DepthMapper()
{

}

void DepthMapper::_lazyInitializeShader()
{
    if (!_shader)
    {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"simpleDepthShader.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"simpleDepthShader.fs");
        _shader->finalize();
    }
}

void DepthMapper::render(World* pWorld, GameObject* pGameObject, Mesh* pMesh, Camera* pCamera)
{
//    std::cout << "depthMapper render call" << std::endl;
    _shader->use();

    //with the generated depth texture we can attach it as the framebuffer's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);

    //light space transform
    GLfloat near_plane = 1.0f, far_plane = 10.0f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    //pass in matrices
    glUniformMatrix4fv(_shader->getUniformLocation("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
    glUniformMatrix4fv (_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform() ) );

        pMesh->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );

    glViewport(0, 0, _shadowWidth, _shadowHeight);

    glBindTexture(GL_TEXTURE_2D, _depthMap);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, 800, 600); //todo: change to screen size variables
}

