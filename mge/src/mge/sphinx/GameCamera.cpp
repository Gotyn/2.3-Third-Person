#include "GameCamera.hpp"
#include "core/World.hpp"
#include "behaviours/RotatingBehaviour.hpp"

GameCamera::GameCamera(): GameObject("camera", glm::vec3(0, 0, 5))
{
    Camera* cb = new Camera();
    addBehaviour(cb);
    World::Instance()->setMainCamera(cb);

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
