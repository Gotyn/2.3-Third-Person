#include <iostream>
#include <GL/glew.h>

#include "config.hpp"
#include "RenderPipeline.hpp"
#include "World.hpp"
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

    initializeDepthmap();
}

RenderPipeline::~RenderPipeline()
{
    glDeleteFramebuffers(1, &_depthMapFBO);
}

void RenderPipeline::initializeDepthmap()
{
    //create depthmap shader programs
    _depthShader = new ShaderProgram();
    _depthShader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"simpleDepthShader.vs");
    _depthShader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"simpleDepthShader.fs");
    _depthShader->finalize();

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
}

void RenderPipeline::render (World* pWorld)
{
    //TODO: render world to depth map

    //render world normally
    render (pWorld, pWorld, pWorld->getMainCamera(), true);
}

void RenderPipeline::render (World* pWorld, GameObject * pGameObject, Camera * pCamera, bool pRecursive)
{
    MeshRenderer* meshRenderer = pGameObject->getBehaviour<MeshRenderer>();

    if (meshRenderer != NULL)
    {
        meshRenderer->render();
    }

    if (!pRecursive) return;

    int childCount = pGameObject->getChildCount();
    if (childCount < 1) return;

    //note that with a loop like this, deleting children during rendering is not a good idea :)
    for (int i = 0; i < childCount; i++) {
        render (pWorld, pGameObject->getChildAt(i), pCamera, pRecursive);
    }
}
