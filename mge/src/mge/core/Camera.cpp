#include <iostream>
using namespace std;

#include <glm.hpp>
#include "mge/core/Camera.hpp"

Camera::Camera(glm::mat4 pProjectionMatrix) : _projection(pProjectionMatrix)
{
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

