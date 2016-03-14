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

        GLuint getShadowMap();

        glm::mat4 lightSpaceMatrix;
    protected:

    private:
        void initializeLightSpaceMatrix();
        void initializeDepthmap();
        void initializeRenderBuffer();
        void initializeScreenQuad();
        void showShadowMap();

        const GLuint SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
        std::shared_ptr<AbstractMaterial> _depthMapperMaterial;
        ShaderProgram* _depthPreview;
        ShaderProgram* _screenShader;
        GLuint _framebuffer;
        GLuint _texColorBuffer;
        GLuint _rbo;
        GLuint _depthMapFBO;
        GLuint _depthMap;

        //screen quad
        GLfloat _quadVertices[24];
        GLuint _quadVAO;
        GLuint _quadVBO;
};

#endif // RENDERPIPELINE_H
