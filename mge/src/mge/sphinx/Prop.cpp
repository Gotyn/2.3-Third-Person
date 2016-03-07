#include "Prop.hpp"

#include "mge/Materials/LitTextureMaterial.hpp"

Prop::Prop(std::string pModelName, std::string pTextureName, std::string pObjectName):GameObject(pObjectName)
{
<<<<<<< HEAD
    _material = new LitTextureMaterial(Texture::load("mge/textures/" + pTextureName));
    _meshRenderer = new MeshRenderer(pModelName, _material, this);
=======
    _material = std::shared_ptr<TextureMaterial>(new TextureMaterial(Texture::load("mge/textures/" + pTextureName)));
    _meshRenderer = std::shared_ptr<MeshRenderer>(new MeshRenderer(pModelName, _material, this));
>>>>>>> refs/remotes/origin/master
}

Prop::~Prop()
{
    //dtor
}

void Prop::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);
}
