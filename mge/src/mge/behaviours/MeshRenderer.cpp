#include "MeshRenderer.hpp"
#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"

MeshRenderer::MeshRenderer(std::string pFilename):AbstractBehaviour()
{
    _mesh = Mesh::load (config::MGE_MODEL_PATH+pFilename);
    _material = new ColorMaterial (glm::vec3(1.0f,1.0f,1.0f));
}

MeshRenderer::~MeshRenderer()
{
    delete _material;
}

void MeshRenderer::update( float step )
{
    if (_mesh == NULL || _material == NULL)
        return;

    _material->render(_owner->getWorld(), _owner, _mesh, _owner->getWorld()->getMainCamera());
}

void MeshRenderer::setMaterial(AbstractMaterial* pMaterial)
{
    _material = pMaterial;
}

AbstractMaterial* MeshRenderer::getMaterial() const
{
    return _material;
}

void MeshRenderer::setMesh(Mesh* pMesh)
{
	_mesh = pMesh;
}

Mesh * MeshRenderer::getMesh() const
{
    return _mesh;
}
