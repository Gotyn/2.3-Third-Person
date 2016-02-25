#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/World.hpp"

class Mesh;

class MeshRenderer : public AbstractBehaviour
{
    public:
        MeshRenderer(std::string pFilename, std::shared_ptr<AbstractMaterial> pMaterial, GameObject* pOwner = nullptr);
        virtual ~MeshRenderer();

        virtual void update( float step );
        void addBehaviourToGO(GameObject* pGameObject);

        void setMesh(std:: string pFilename);
        void setMesh(Mesh* pMesh);
		Mesh* getMesh() const;

		void setMaterial (std::shared_ptr<AbstractMaterial> pMaterial);
		std::shared_ptr<AbstractMaterial> getMaterial() const;

    protected:
        Mesh* _mesh;
        std::shared_ptr<AbstractMaterial>  _material;

    private:
};

#endif // MESHRENDERER_H
