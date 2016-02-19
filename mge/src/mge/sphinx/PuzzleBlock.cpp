#include "PuzzleBlock.hpp"

PuzzleBlock::PuzzleBlock():GameObject("puzzleBlock")
{
    _targetForward = GameObject::getForward();
    _rotatingBehavour = new RotatingBehaviour();
    this->addBehaviour(_rotatingBehavour);
}

PuzzleBlock::~PuzzleBlock()
{
    //dtor
}

float PuzzleBlock::getProgress()
{
    glm::vec3 delta = _targetForward - GameObject::getForward();
    return glm::length(delta) / 2.0f;
}

void PuzzleBlock::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);

//    std::cout << getProgress() << std::endl;
}
