#ifndef LITTEXTUREMATERIAL_H
#define LITTEXTUREMATERIAL_H

#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/AbstractMaterial.hpp"

class LitTextureMaterial : public AbstractMaterial
{
    public:
        LitTextureMaterial (Texture* pDiffuseTexture);
        virtual ~LitTextureMaterial ();
        virtual void render(World* pWorld, GameObject* pGameObject, Mesh* pMesh, Camera* pCamera);

        void setDiffuseTexture (Texture* pDiffuseTexture);
        void changeDiffuseTexture (std::string pFilename);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        Texture* _diffuseTexture;
};

#endif // LITTEXTUREMATERIAL_H
