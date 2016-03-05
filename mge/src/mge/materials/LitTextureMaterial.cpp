#include <glm.hpp>

#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

//init static members
ShaderProgram* LitTextureMaterial::_shader = NULL;
ShaderProgram* LitTextureMaterial::_depthShader = NULL;
ShaderProgram* LitTextureMaterial::_depthPreview = NULL;

LitTextureMaterial::LitTextureMaterial(Texture * pDiffuseTexture):_diffuseTexture(pDiffuseTexture)
{
    _lazyInitializeShader();

    //create a framebuffer object for rendering the depth map
    glGenFramebuffers(1, &_depthMapFBO);
    glGenTextures(1, &_depthMap);
    glBindTexture(GL_TEXTURE_2D, _depthMap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

LitTextureMaterial::~LitTextureMaterial()
{
    glDeleteFramebuffers(1, &_depthMapFBO);
}

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

    if (!_depthPreview)
    {
        _depthPreview = new ShaderProgram();
        _depthPreview->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"shadowMap.vs");
        _depthPreview->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"shadowMap.fs");
        _depthPreview->finalize();
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

    glEnable(GL_DEPTH_TEST);
    _depthShader->use();

    //with the generated depth texture we can attach it as the framebuffer's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, _depthMap);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);


    //light space transform
    GLfloat near_plane = 1.0f, far_plane = 25.0f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f), glm::vec3(1.0));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    //pass in matrices
    glUniformMatrix4fv(_depthShader->getUniformLocation("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
    glUniformMatrix4fv ( _depthShader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform() ) );

        pMesh->streamToOpenGL(
        _depthShader->getAttribLocation("vertex"),
        _depthShader->getAttribLocation("normal"),
        _depthShader->getAttribLocation("uv")
    );

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, 800, 600); //todo: change to screen size variables

    // --- end of shadowmap render --- //



    // --- depth map preview quad ---

    GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // Positions   // TexCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    // Setup screen VAO
    GLuint quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); // We don't care about depth information when rendering a single quad

    // Draw Screen
    _depthPreview->use();
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, _depthMap);	// Use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);


    // ------------------------------ //

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    _shader->use();
//
//    //setup texture slot 0
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
//    glUniform1i (_shader->getUniformLocation("textureDiffuse"), 0);
//
//    //pass in all MVP matrices separately
//    glUniformMatrix4fv ( _shader->getUniformLocation("projectionMatrix"),   1, GL_FALSE, glm::value_ptr(pCamera->getProjection()));
//    glUniformMatrix4fv ( _shader->getUniformLocation("viewMatrix"),         1, GL_FALSE, glm::value_ptr(glm::inverse(pCamera->getOwner()->getWorldTransform())));
//    glUniformMatrix4fv ( _shader->getUniformLocation("modelMatrix"),        1, GL_FALSE, glm::value_ptr(pGameObject->getWorldTransform() ) );
//
//    //now inform mesh of where to stream its data
//    pMesh->streamToOpenGL(
//        _shader->getAttribLocation("vertex"),
//        _shader->getAttribLocation("normal"),
//        _shader->getAttribLocation("uv")
//    );
}
