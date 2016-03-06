#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/World.hpp"
#include "mge/core/RenderPipeline.hpp"

class Mesh;

class MeshRenderer : public AbstractBehaviour
{
    public:
        MeshRenderer(std::string pFilename, AbstractMaterial* pMaterial, GameObject* pOwner = nullptr);
        virtual ~MeshRenderer();
        virtual void update( float step );
        void render();
        void render(AbstractMaterial* pMaterial);
        void addBehaviourToGO(GameObject* pGameObject);

        void setMesh(std:: string pFilename);
        void setMesh(Mesh* pMesh);
		Mesh* getMesh() const;

		void setMaterial (AbstractMaterial* pMaterial);
		AbstractMaterial* getMaterial() const;

    protected:
        Mesh* _mesh;
        AbstractMaterial* _material;

    private:
};

#endif // MESHRENDERER_H
