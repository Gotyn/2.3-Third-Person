#include "Prop.hpp"

Prop::Prop(std::string pModelName, std::string pTextureName, std::string pObjectName):GameObject(pObjectName)
{
    _material = new TextureMaterial(Texture::load("mge/textures/" + pTextureName));
    _meshRenderer = new MeshRenderer(pModelName, _material, this);
}

Prop::~Prop()
{
    //dtor
}

void Prop::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);
}
