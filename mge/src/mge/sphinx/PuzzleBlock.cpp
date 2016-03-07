#include "PuzzleBlock.hpp"
#include "mge/core/Timer.hpp"
#include "mge/Materials/LitTextureMaterial.hpp"

PuzzleBlock::PuzzleBlock(std::string pModelName, std::string pTextureName, std::string pObjectName):GameObject(pObjectName)
{
    _targetForward = GameObject::getForward();
    _targetUp = GameObject::getUp();

<<<<<<< HEAD
     _material = std::shared_ptr<TextureMaterial>(new TextureMaterial(Texture::load("mge/textures/" + pTextureName)));
=======
     _material = new LitTextureMaterial(Texture::load("mge/textures/" + pTextureName));
>>>>>>> refs/remotes/origin/master
    _meshRenderer = new MeshRenderer(pModelName, _material, this);
}

PuzzleBlock::~PuzzleBlock()
{
    //dtor
}

float PuzzleBlock::getProgress()
{
    glm::vec3 forwardDelta = _targetForward - GameObject::getForward();
    glm::vec3 upDelta = _targetUp - GameObject::getUp();

    float progressFraction = (glm::length(forwardDelta) / 2.0f + glm::length(upDelta) / 2.0f) * 0.5f;

    return 1.0f - progressFraction;
}

void PuzzleBlock::printStatus()
{
    std::cout << "===================================================" << std::endl;
    std::cout << "puzzleBlock status of: " << getName() << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "position:          " << getWorldPosition() << std::endl;
    std::cout << "TODO: print scale" << std::endl;
    std::cout << "forward direction: " << getForward() << std::endl;
    std::cout << "up direction:      " << getUp() << std::endl;
    std::cout << std::endl;
}

void PuzzleBlock::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);

//    if (Input::getKey(0))
//    {
//        roll(1.0f * pStep);
//    }
}
