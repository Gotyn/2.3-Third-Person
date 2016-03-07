#include "PuzzleBlock.hpp"
#include "mge/core/Timer.hpp"
#include "mge/Materials/LitTextureMaterial.hpp"
#include "mge/util/Utils.hpp"

PuzzleBlock::PuzzleBlock(std::string pModelName, std::string pTextureName, std::string pObjectName):GameObject(pObjectName)
{
    _targetForward = GameObject::getForward();
    _targetUp = GameObject::getUp();

    _material = std::shared_ptr<LitTextureMaterial>(new LitTextureMaterial(Texture::load("mge/textures/" + pTextureName)));

    _meshRenderer = new MeshRenderer(pModelName, _material, this);

    //randomize block rotation
    randomize();
}

PuzzleBlock::~PuzzleBlock()
{
    //dtor
}

void PuzzleBlock::randomize()
{
    rotate(Utils::randomRange(0.0f, 6.28319f), glm::vec3(1,0,0));
    rotate(Utils::randomRange(0.0f, 6.28319f), glm::vec3(0,1,0));
    rotate(Utils::randomRange(0.0f, 6.28319f), glm::vec3(0,0,1));
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
