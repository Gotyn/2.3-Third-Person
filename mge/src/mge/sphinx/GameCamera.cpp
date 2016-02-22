#include "GameCamera.hpp"
#include "mge/core/World.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"

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
