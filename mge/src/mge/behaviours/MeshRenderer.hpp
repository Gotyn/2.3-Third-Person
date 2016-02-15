#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/World.hpp"

class Mesh;

class MeshRenderer : public AbstractBehaviour
{
    public:
        MeshRenderer(std::string pFilename);
        virtual ~MeshRenderer();

        virtual void update( float step );

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
