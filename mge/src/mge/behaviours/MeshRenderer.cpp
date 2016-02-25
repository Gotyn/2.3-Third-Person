#include "MeshRenderer.hpp"
#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"

MeshRenderer::MeshRenderer(std::string pFilename, std::shared_ptr<AbstractMaterial> pMaterial, GameObject* pOwner) : AbstractBehaviour() {
     addBehaviourToGO(pOwner);
    _mesh = Mesh::load (config::MGE_MODEL_PATH+pFilename);
    _material = pMaterial;
}

MeshRenderer::~MeshRenderer() {
    //delete _material;  //smart pointer takes care of this...
}

void MeshRenderer::addBehaviourToGO(GameObject* pGameObject) {
    pGameObject->addBehaviour(this);
}

void MeshRenderer::update( float step ) {
    if (_mesh == NULL || _material == NULL)
        return;

    if (World::Instance()->getMainCamera() != NULL)
        _material->render(World::Instance(), _owner, _mesh, World::Instance()->getMainCamera());
}

void MeshRenderer::setMaterial(std::shared_ptr<AbstractMaterial> pMaterial) {
    _material = pMaterial;
}

std::shared_ptr<AbstractMaterial> MeshRenderer::getMaterial() const {
    return _material;
}

void MeshRenderer::setMesh(std::string pFilename) {
    _mesh = Mesh::load (config::MGE_MODEL_PATH+pFilename);
}

void MeshRenderer::setMesh(Mesh* pMesh) {
	_mesh = pMesh;
}

Mesh * MeshRenderer::getMesh() const {
    return _mesh;
}
