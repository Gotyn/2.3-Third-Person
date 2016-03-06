#ifndef RENDERPIPELINE_H
#define RENDERPIPELINE_H

class World;
class GameObject;
class Camera;

#include "mge/materials/DepthMapper.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/RenderPipeline.hpp"

class RenderPipeline
{
    public:
        RenderPipeline();
        virtual ~RenderPipeline();

        //render whole world
        void render (World* pWorld);

        //render specific game object within the world (using world's light settings etc)
        void render (World* pWorld, GameObject* pGameObject, Camera* pCamera, bool pRecursive, bool pShadowMap);

    protected:

    private:
        void initializeDepthmap();
        void showShadowMap();

        const GLuint SHADOW_WIDTH = 800, SHADOW_HEIGHT = 600;
        AbstractMaterial* _depthMapperMaterial;
        ShaderProgram* _depthPreview;
        GLuint _depthMapFBO;
        GLuint _depthMap;
};

#endif // RENDERPIPELINE_H
