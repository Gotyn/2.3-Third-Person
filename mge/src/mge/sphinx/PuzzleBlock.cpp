#include "PuzzleBlock.hpp"

PuzzleBlock::PuzzleBlock(std::string pModelName, std::string pTextureName):GameObject("puzzleBlock")
{
    _targetForward = GameObject::getForward();

    //add behaviours
    _rotatingBehavour = new RotatingBehaviour();
    this->addBehaviour(_rotatingBehavour);

     _material = new TextureMaterial(Texture::load("mge/textures/" + pTextureName));
    _meshRenderer = new MeshRenderer(pModelName, _material);
    this->addBehaviour(_meshRenderer);
}

PuzzleBlock::~PuzzleBlock()
{
    //dtor
}

float PuzzleBlock::getProgress()
{
    glm::vec3 delta = _targetForward - GameObject::getForward();
    return 1.0f - glm::length(delta) / 2.0f;
}

void PuzzleBlock::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);

//    std::cout << getProgress() << std::endl;
}
