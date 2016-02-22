#include "MeshRenderer.hpp"
#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"

MeshRenderer::MeshRenderer(std::string pFilename, AbstractMaterial* pMaterial):AbstractBehaviour()
{
    _mesh = Mesh::load (config::MGE_MODEL_PATH+pFilename);
    //_material = new ColorMaterial (glm::vec3(1.0f,1.0f,1.0f));
    _material = pMaterial;
}

MeshRenderer::~MeshRenderer()
{
    delete _material;
}

void MeshRenderer::update( float step )
{
    if (_mesh == NULL || _material == NULL)
        return;

    if (World::Instance()->getMainCamera() != NULL)
        _material->render(World::Instance(), _owner, _mesh, World::Instance()->getMainCamera());
}

void MeshRenderer::setMaterial(AbstractMaterial* pMaterial)
{
    _material = pMaterial;
}

AbstractMaterial* MeshRenderer::getMaterial() const
{
    return _material;
}

void MeshRenderer::setMesh(std::string pFilename)
{
    _mesh = Mesh::load (config::MGE_MODEL_PATH+pFilename);
}

void MeshRenderer::setMesh(Mesh* pMesh)
{
	_mesh = pMesh;
}

Mesh * MeshRenderer::getMesh() const
{
    return _mesh;
}
