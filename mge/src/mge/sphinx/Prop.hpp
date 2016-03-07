#ifndef PROP_H
#define PROP_H

#include <GameObject.hpp>
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/materials/TextureMaterial.hpp"

class Prop : public GameObject
{
    public:
        Prop(std::string pModelName, std::string pTextureName, std::string pObjectName);
        virtual ~Prop();

        virtual void update(float pStep, const glm::mat4& pParentTransform);

    protected:
    private:
        MeshRenderer* _meshRenderer;
        AbstractMaterial* _material;
};

#endif // PROP_H
