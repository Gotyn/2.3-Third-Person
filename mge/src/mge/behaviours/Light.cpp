#include "Light.hpp"
#include "GameObject.hpp"

Light::Light(GameObject* pOwner)
{
    addBehaviourToGO(pOwner);

    _innerCone = 15.0f;
    _outerCone = 29.0f;
}

Light::~Light()
{

}

float Light::getInnerCone() const
{
    return _innerCone;
}

float Light::getOuterCone() const
{
    return _outerCone;
}

void Light::addBehaviourToGO(GameObject* pGameObject)
{
    pGameObject->addBehaviour(this);
}

void Light::update(float step)
{
    getOwner()->yaw(20.0f * step);
}
