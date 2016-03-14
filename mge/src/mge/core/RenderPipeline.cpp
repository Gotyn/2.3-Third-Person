#include <iostream>
#include <GL/glew.h>

#include "config.hpp"
#include "RenderPipeline.hpp"
#include "World.hpp"
#include "AbstractGame.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/materials/AbstractMaterial.hpp"

RenderPipeline::RenderPipeline()
{
    //    //setup openGL settings
	std::cout << "Initializing render settings..." << std::endl;

    glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE ); // default GL_BACK
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor((float)0x2d/0xff, (float)0x6b/0xff, (float)0xce/0xff, 1.0f );

    std::cout << "Render settings loaded." << std::endl << std::endl;

    initializeScreenQuad();
    initializeRenderBuffer();
    initializeDepthmap();
    initializeLightSpaceMatrix();
}

RenderPipeline::~RenderPipeline()
{
    glDeleteFramebuffers(1, &_depthMapFBO);
}

GLuint RenderPipeline::getShadowMap()
{
    return _depthMap;
}

void RenderPipeline::initializeLightSpaceMatrix()
{
    //light space transform
    GLfloat near_plane = 1.0f, far_plane = 60.0f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    lightSpaceMatrix = lightProjection * lightView;
}

void RenderPipeline::initializeDepthmap()
{
    //create depthmap shader programs
    _depthPreview = new ShaderProgram();
    _depthPreview->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"shadowMap.vs");
    _depthPreview->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"shadowMap.fs");
    _depthPreview->finalize();

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

    _depthMapperMaterial = std::shared_ptr<AbstractMaterial>(new DepthMapper(_depthMapFBO, _depthMap, SHADOW_WIDTH, SHADOW_HEIGHT));
}

void RenderPipeline::initializeRenderBuffer()
{
    //create screen shader program
    _screenShader = new ShaderProgram();
    _screenShader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"screenShader.vs");
    _screenShader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"screenShader.fs");
    _screenShader->finalize();

    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

    // Generate texture
    glGenTextures(1, &_texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, _texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texColorBuffer, 0);

    // Create Render buffer object
    glGenRenderbuffers(1, &_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderPipeline::render (World* pWorld)
{
    //render world to depth map
    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);
    render (pWorld, pWorld, pWorld->getMainCamera(), true, true);
    glCullFace(GL_BACK);

    //show shadowMap (testing only)
//    showShadowMap();

    // First pass
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now
    glEnable(GL_DEPTH_TEST);
    render(pWorld, pWorld, pWorld->getMainCamera(), true, false);

    // Second pass
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glActiveTexture(GL_TEXTURE0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _screenShader->use();
    glBindVertexArray(_quadVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, _texColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

////    render world normally (depricated)
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    render (pWorld, pWorld, pWorld->getMainCamera(), true, false);
}

void RenderPipeline::render (World* pWorld, GameObject * pGameObject, Camera * pCamera, bool pRecursive, bool pShadowMap)
{
    if (!pGameObject->getActive())
        return;

    MeshRenderer* meshRenderer = pGameObject->getBehaviour<MeshRenderer>();

    if (meshRenderer != NULL)
    {
        if (pShadowMap)
            meshRenderer->render(this, _depthMapperMaterial);
        else
            meshRenderer->render(this);
    }

    if (!pRecursive) return;

    int childCount = pGameObject->getChildCount();
    if (childCount < 1) return;

    //note that with a loop like this, deleting children during rendering is not a good idea :)
    for (int i = 0; i < childCount; i++) {
        render (pWorld, pGameObject->getChildAt(i), pCamera, pRecursive, pShadowMap);
    }
}

void RenderPipeline::initializeScreenQuad()
{
    _quadVertices[0] = -1.0f;
    _quadVertices[1] = 1.0f;
    _quadVertices[2] = 0.0f;
    _quadVertices[3] = 1.0f;

    _quadVertices[4] = -1.0f;
    _quadVertices[5] = -1.0f;
    _quadVertices[6] = 0.0f;
    _quadVertices[7] = 0.0f;

    _quadVertices[8] = 1.0f;
    _quadVertices[9] = -1.0f;
    _quadVertices[10] = 1.0f;
    _quadVertices[11] = 0.0f;

    _quadVertices[12] = -1.0f;
    _quadVertices[13] = 1.0f;
    _quadVertices[14] = 0.0f;
    _quadVertices[15] = 1.0f;

    _quadVertices[16] = 1.0f;
    _quadVertices[17] = -1.0f;
    _quadVertices[18] = 1.0f;
    _quadVertices[19] = 0.0f;

    _quadVertices[20] = 1.0f;
    _quadVertices[21] = 1.0f;
    _quadVertices[22] = 1.0f;
    _quadVertices[23] = 1.0f;

    // Setup screen VAO
    glGenVertexArrays(1, &_quadVAO);
    glGenBuffers(1, &_quadVBO);
    glBindVertexArray(_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_quadVertices), &_quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);
}

void RenderPipeline::showShadowMap()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); // We don't care about depth information when rendering a single quad

    // Draw Screen
    _depthPreview->use();
    glBindVertexArray(_quadVAO);
    glBindTexture(GL_TEXTURE_2D, _depthMap);	// Use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
}
