#include "PuzzleBlock.hpp"
#include "mge/core/Timer.hpp"

PuzzleBlock::PuzzleBlock(std::string pModelName, std::string pTextureName):GameObject("puzzleBlock")
{
    _targetForward = GameObject::getForward();

    //add behaviours
//    _rotatingBehavour = new RotatingBehaviour();
//    this->addBehaviour(_rotatingBehavour);

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

float PuzzleBlock::pitch(float pAmount)
{
    rotate(pAmount * Timer::deltaTime(), glm::vec3(1,0,0));
}

float PuzzleBlock::roll(float pAmount)
{
    rotate(pAmount * Timer::deltaTime(), glm::vec3(0,0,-1));
}

void PuzzleBlock::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);

//    if (Input::getKey(0))
//    {
//        roll(1.0f * pStep);
//    }
}
