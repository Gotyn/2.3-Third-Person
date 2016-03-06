#ifndef DEPTHMAPPER_H
#define DEPTHMAPPER_H

#include "mge/materials/AbstractMaterial.hpp"

class DepthMapper : public AbstractMaterial
{
    public:
        DepthMapper(GLuint pDepthMapFBO, GLuint pDepthMap, int pShadowWidth, int pShadowHeight);
        virtual ~DepthMapper();

        virtual void render(World* pWorld, GameObject* pGameObject, Mesh* pMesh, Camera* pCamera);

    protected:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();
        GLuint _depthMapFBO;
        GLuint _depthMap;

    private:
        int _shadowWidth, _shadowHeight;
};

#endif // DEPTHMAPPER_H
