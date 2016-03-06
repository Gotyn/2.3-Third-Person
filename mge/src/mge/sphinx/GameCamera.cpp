#include "GameCamera.hpp"
#include "mge/core/World.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"

GameCamera::GameCamera(glm::vec3 pPosition): GameObject("camera", pPosition)
{
    Camera* cb = new Camera(glm::perspective (glm::radians(60.0f), 4.0f/3.0f, 0.1f, 1000.0f), this);

    std::cout << "game camera created" << std::endl;
}

GameCamera::~GameCamera()
{
    //dtor
}

void GameCamera::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);
}
