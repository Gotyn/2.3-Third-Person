#include <iostream>
using namespace std;

#include <glm.hpp>
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"

Camera::Camera(glm::mat4 pProjectionMatrix, GameObject* pOwner) : AbstractBehaviour(pOwner), _projection(pProjectionMatrix)
{
    if(World::Instance()->getMainCamera() == nullptr) World::Instance()->setMainCamera(this);
}

Camera::~Camera()
{
	//dtor
}

void Camera::update(float step)
{

}

glm::mat4& Camera::getProjection() {
    return _projection;
}

void Camera::setProjection(const glm::mat4& pProjection) {
    _projection = pProjection;
}

