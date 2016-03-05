#include <iostream>
#include <GL/glew.h>

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
}

RenderPipeline::~RenderPipeline()
{
    //dtor
}

void RenderPipeline::render (World* pWorld) {
    render (pWorld, pWorld, pWorld->getMainCamera(), true);
}

void RenderPipeline::render (World* pWorld, GameObject * pGameObject, Camera * pCamera, bool pRecursive)
{
    MeshRenderer* meshRenderer = pGameObject->getBehaviour<MeshRenderer>();

    if (meshRenderer != NULL)
    {
        std::cout << "found a renderer on: " << pGameObject->getName() << std::endl;
    }

//    AbstractMaterial* material = pGameObject->getMaterial();
//
//    //our material (shader + settings) determines how we actually look
//    if (pGameObject->getMesh() && material != NULL) {
//        material->render(pWorld, pGameObject, pCamera);
//    }

    if (!pRecursive) return;

    int childCount = pGameObject->getChildCount();
    if (childCount < 1) return;

    //note that with a loop like this, deleting children during rendering is not a good idea :)
    for (int i = 0; i < childCount; i++) {
        render (pWorld, pGameObject->getChildAt(i), pCamera, pRecursive);
    }
}
